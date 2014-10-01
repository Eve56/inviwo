/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 * Version 0.6b
 *
 * Copyright (c) 2012-2014 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Main file authors: Peter Steneteg
 *
 *********************************************************************************/

#include <modules/python3/pythonincluder.h>

#include "pythonscript.h"

#include <inviwo/core/util/assertion.h>
#include <inviwo/core/util/stringconversion.h>
#include <inviwo/core/util/urlparser.h>

#include <modules/python3/pythonexecutionoutputobservable.h>

#include <modules/python3/pythoninterface/pyvalueparser.h>

#include <traceback.h>
#include <frameobject.h>
#include <modules/python3/pythoninterface/pymodule.h>
#include "pyinviwo.h"

#define BYTE_CODE static_cast<PyObject*>(byteCode_)

namespace inviwo {

    PythonScript::PythonScript()
        : source_("")
        , byteCode_(0)
        , isCompileNeeded_(false)
    {
    }

    PythonScript::~PythonScript() {
        Py_XDECREF(BYTE_CODE);
    }

    bool PythonScript::compile(bool outputInfo) {
        if (outputInfo)
            LogInfo("Compiling script");

        Py_XDECREF(BYTE_CODE);
        byteCode_ = Py_CompileString(source_.c_str(), "", Py_file_input);
        isCompileNeeded_ = !checkCompileError();

        if (isCompileNeeded_) {
            Py_XDECREF(BYTE_CODE);
            byteCode_ = 0;
        }

        return !isCompileNeeded_;
    }

    bool PythonScript::run(bool outputInfo) {
        PyObject* glb = PyInviwo::getPtr()->getMainDictionary();


        if (isCompileNeeded_ && !compile(outputInfo)) {
            LogError("Failed to run script, script could not be compiled");
            return false;
        }

        ivwAssert(byteCode_ != 0, "No byte code");

        if (outputInfo)
            LogInfo("Running compiled script ...");

        PyObject* ret = PyEval_EvalCode(BYTE_CODE, glb, glb);
        bool success = checkRuntimeError();
        Py_XDECREF(ret);
  //      Py_XDECREF(glb);
        return success;
    }

    std::string PythonScript::getSource() const {
        return source_;
    }

    void PythonScript::setSource(const std::string& source) {
        source_ = source;
        isCompileNeeded_ = true;
        Py_XDECREF(BYTE_CODE);
        byteCode_ = 0;
    }

    bool PythonScript::checkCompileError() {
        if (!PyErr_Occurred())
            return true;

        PyObject* errtype, *errvalue, *traceback;
        PyErr_Fetch(&errtype, &errvalue, &traceback);
        std::string log = "";
        int errorLine = -1;
        int errorCol = -1;
        char* msg = 0;
        PyObject* obj = 0;

        if (PyArg_ParseTuple(errvalue, "sO", &msg, &obj)) {
            int line, col;
            char* code = 0;
            char* mod = 0;

            if (PyArg_ParseTuple(obj, "siis", &mod, &line, &col, &code)) {
                errorLine = line;
                errorCol = col;
                log = "[" + toString(line) + ":" + toString(col) + "] " + toString(msg) + ": " + toString(code);
            }
        }

        // convert error to string, if it could not be parsed
        if (log.empty()) {
            LogWarn("Failed to parse exception, printing as string:");
            PyObject* s = PyObject_Str(errvalue);

            if (s && PyValueParser::is<std::string>(s)) {
                log = std::string(PyValueParser::parse<std::string>(s));
                Py_XDECREF(s);
            }
        }

        Py_XDECREF(errtype);
        Py_XDECREF(errvalue);
        Py_XDECREF(traceback);
        LogError(log);
        return false;
    }

    bool PythonScript::checkRuntimeError() {
        if (!PyErr_Occurred())
            return true;

        std::string pyException = "";
        PyObject* pyError_type = 0;
        PyObject* pyError_value = 0;
        PyObject* pyError_traceback = 0;
        PyObject* pyError_string = 0;
        PyErr_Fetch(&pyError_type, &pyError_value, &pyError_traceback);
        int errorLine = -1;
        std::string stacktraceStr;

        if (pyError_traceback) {
            PyTracebackObject* traceback = (PyTracebackObject*)pyError_traceback;

            while (traceback) {
                PyFrameObject* frame = traceback->tb_frame;
                std::string stacktraceLine;

                if (frame && frame->f_code) {
                    PyCodeObject* codeObject = frame->f_code;

                    if (PyValueParser::is<std::string>(codeObject->co_filename))
                        stacktraceLine.append(std::string("  File \"") + PyValueParser::parse<std::string>(codeObject->co_filename) + std::string("\", "));

                    errorLine = PyCode_Addr2Line(codeObject, frame->f_lasti);
                    stacktraceLine.append(std::string("line ") + toString(errorLine));

                    if (PyValueParser::is<std::string>(codeObject->co_name))
                        stacktraceLine.append(std::string(", in ") + PyValueParser::parse<std::string>(codeObject->co_name));
                }

                stacktraceLine.append("\n");
                stacktraceStr = stacktraceLine + stacktraceStr;
                traceback = traceback->tb_next;
            }
        }

        std::stringstream s;
        s << errorLine;
        pyException.append(std::string("[") + s.str() + std::string("] "));

             if (pyError_value && (pyError_string = PyObject_Str(pyError_value)) != 0 && (PyValueParser::is<std::string>(pyError_string))) {
                 pyException.append(PyValueParser::parse<std::string>(pyError_string));
                 Py_XDECREF(pyError_string);
                 pyError_string = 0;
                 }
                 else {
                 pyException.append("<No data available>");
                 }
                 
        pyException.append("\n");

        // finally append stacktrace string
        if (!stacktraceStr.empty()) {
            pyException.append("Stacktrace (most recent call first):\n");
            pyException.append(stacktraceStr);
        }
        else {
            pyException.append("<No stacktrace available>");
            LogWarn("Failed to parse traceback");
        }

        Py_XDECREF(pyError_type);
        Py_XDECREF(pyError_value);
        Py_XDECREF(pyError_traceback);
        LogError(pyException);
        PythonExecutionOutputObservable::getPtr()->pythonExecutionOutputEvent(pyException, sysstderr);
        return false;
    }


} // namespace
