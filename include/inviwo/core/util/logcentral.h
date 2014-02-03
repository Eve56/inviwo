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
 * Main file authors: Timo Ropinski, Erik Sund�n
 *
 *********************************************************************************/

#ifndef IVW_LOGGER_H
#define IVW_LOGGER_H

#pragma warning (disable : 4231)

#include <inviwo/core/common/inviwocoredefine.h>
#include <inviwo/core/common/inviwo.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <inviwo/core/util/stringconversion.h>

namespace inviwo {

IVW_CORE_API enum LogLevel {
    Info,
    Warn,
    Error
};

#define LogInfo(message) \
    {   std::ostringstream stream__; stream__ << message; \
        inviwo::LogCentral::instance()->log(parseTypeIdName(std::string(typeid(this).name())), inviwo::Info, __FILE__, __FUNCTION__, __LINE__, stream__.str());}
#define LogWarn(message) \
    {   std::ostringstream stream__; stream__ << message; \
        inviwo::LogCentral::instance()->log(parseTypeIdName(std::string(typeid(this).name())), inviwo::Warn, __FILE__, __FUNCTION__, __LINE__, stream__.str());}
#define LogError(message) \
    {   std::ostringstream stream__; stream__ << message; \
        inviwo::LogCentral::instance()->log(parseTypeIdName(std::string(typeid(this).name())), inviwo::Error, __FILE__, __FUNCTION__, __LINE__, stream__.str());}

#define LogInfoCustom(source, message) \
    {   std::ostringstream stream__; stream__ << message; \
        inviwo::LogCentral::instance()->log(source, inviwo::Info, __FILE__, __FUNCTION__, __LINE__, stream__.str());}
#define LogWarnCustom(source, message) \
    {   std::ostringstream stream__; stream__ << message; \
        inviwo::LogCentral::instance()->log(source, inviwo::Warn, __FILE__, __FUNCTION__, __LINE__, stream__.str());}
#define LogErrorCustom(source, message) \
    {   std::ostringstream stream__; stream__ << message; \
        inviwo::LogCentral::instance()->log(source, inviwo::Error, __FILE__, __FUNCTION__, __LINE__, stream__.str());}

class IVW_CORE_API Logger {

public:
    Logger() {};
    virtual ~Logger() {};

    virtual void log(std::string logSource, unsigned int logLevel, const char* fileName, const char* functionName, int lineNumber,
                     std::string logMsg) = 0;
};

class IVW_CORE_API ConsoleLogger : public Logger {

public:
    ConsoleLogger();
    virtual ~ConsoleLogger();

    virtual void log(std::string logSource, unsigned int logLevel, const char* fileName, const char* functionName, int lineNumber,
                     std::string logMsg);
};


class IVW_CORE_API FileLogger : public Logger {

public:
    FileLogger(std::string logPath);
    virtual ~FileLogger();

    virtual void log(std::string logSource, unsigned int logLevel, const char* fileName, const char* functionName, int lineNumber,
                     std::string logMsg);
private:
    std::ofstream* fileStream_;
};


class IVW_CORE_API LogCentral {

public:
    LogCentral();
    virtual ~LogCentral();

    static LogCentral* instance();

    void setLogLevel(unsigned int logLevel) { logLevel_ = logLevel; }
    unsigned int getLogLevel() { return logLevel_; }

    void registerLogger(Logger* logger);
    void unregisterLogger(Logger* logger);
    void log(std::string logSource, unsigned int logLevel, const char* fileName, const char* functionName, int lineNumber, std::string logMsg);

private:
    unsigned int logLevel_;
    std::vector<Logger*>* loggers_;
};

} // namespace

#endif // IVW_LOGGER_H