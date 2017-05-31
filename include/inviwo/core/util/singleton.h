/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2013-2017 Inviwo Foundation
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
 *********************************************************************************/

#ifndef IVW_SINGLETON_H
#define IVW_SINGLETON_H

#include <inviwo/core/common/inviwocoredefine.h>
#include <inviwo/core/util/stdextensions.h>
#include <inviwo/core/util/exception.h>

#include <sstream>
#include <vector>

namespace inviwo {

class SingletonException : public Exception {
public:
    SingletonException(const std::string& message = "",
                       ExceptionContext context = ExceptionContext())
        : Exception(message, context) {}
};

template <class T>
class Singleton {
public:
    Singleton<T>(){};
    Singleton<T>(Singleton<T> const&) = delete;
    void operator=(Singleton<T> const&) = delete;

    /**
     * For Singletons in the inviwo::core init should be called in
     * void InviwoApplication::initialize(registerModuleFuncPtr regModuleFunc).
     *
     */
    static void init() {
        if (instance_ != nullptr) {
            throw SingletonException("Singleton already initialized", IvwContextCustom("Singleton"));
        }
        instance_ = util::defaultConstructType<T>();
        if (instance_ == nullptr) {
            throw SingletonException("Was not able to initialize singleton", IvwContextCustom("Singleton"));
        }
    };

    static void init(T* instance) {
        if (instance_ != nullptr) {
            throw SingletonException("Singleton already initialized", IvwContextCustom("Singleton"));
        }
        if (instance == nullptr) {
            throw SingletonException("Null pointer passed", IvwContextCustom("Singleton"));
        }
        instance_ = instance;
    };

    static T* getPtr() {
        if (instance_ == 0) {
            throw SingletonException(
                "Singleton not initialized. Ensure that init() is called in a thread-safe "
                "environment. ",
                IvwContextCustom("Singleton"));
        }
        return instance_;
    };

    static void deleteInstance() {
        delete instance_;
        instance_ = nullptr;
    };

    virtual ~Singleton() { Singleton<T>::resetInstance(); };

private:
    static void resetInstance() { instance_ = nullptr; };

    static T* instance_;
};

template <class T>
T* Singleton<T>::instance_ = nullptr;

}  // end of namespace

#endif  // IVW_SINGLETON_H
