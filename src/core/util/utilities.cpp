/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2012-2017 Inviwo Foundation
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

#include <inviwo/core/util/utilities.h>
#include <inviwo/core/util/stdextensions.h>
#include <inviwo/core/common/inviwo.h>
#include <inviwo/core/network/processornetwork.h>
#include <inviwo/core/processors/canvasprocessor.h>

namespace inviwo {
namespace util {

void saveNetwork(ProcessorNetwork* network, std::string filename) {
    try {
        Serializer xmlSerializer(filename);
        network->serialize(xmlSerializer);
        xmlSerializer.writeFile();
    } catch (SerializationException& exception) {
        util::log(exception.getContext(),
                  "Unable to save network " + filename + " due to " + exception.getMessage(),
                  LogLevel::Error);
    }
}

void saveAllCanvases(ProcessorNetwork* network, std::string dir, std::string name,
                     std::string ext) {
    int i = 0;
    for (auto cp : network->getProcessorsByType<inviwo::CanvasProcessor>()) {
        std::stringstream ss;
        ss << dir << "/";

        if (name == "") {
            ss << cp->getIdentifier();
        } else if (name.find("UPN") != std::string::npos) {
            std::string tmp = name;
            replaceInString(tmp, "UPN", cp->getIdentifier());
            ss << tmp;
        } else {
            ss << name << i + 1;
        }
        ss << ext;

        LogInfoCustom("Inviwo", "Saving canvas to: " + ss.str());
        cp->saveImageLayer(ss.str());
        i++;
    }
}

bool isValidIdentifierCharacter(char c, const std::string& extra) {
    return (std::isalnum(c) || c == '_' || c == '-' || util::contains(extra, c));
}

void validateIdentifier(const std::string& identifier, const std::string& type,
                        ExceptionContext context, const std::string& extra) {
    for (const auto& c : identifier) {
        if (!(c >= -1) || !isValidIdentifierCharacter(c, extra)) {
            throw Exception(type + " identifiers are not allowed to contain \"" + c +
                                "\". Found in \"" + identifier + "\"",
                            context);
        }
    }
}

std::string stripIdentifier(std::string identifier) {
    // What we allow: [a-zA-Z_][a-zA-Z0-9_]*
    auto testFirst = [](unsigned char c) -> bool { return !(c == '_' || std::isalpha(c)); };

    auto testRest = [](unsigned char c) -> bool { return !(c == '_' || std::isalnum(c)); };

    while (identifier.size() > 0) {
        const auto& c = identifier[0];
        if (!testFirst(c)) { break; }
        if (std::isdigit(c)) {  // prepend an underscore if first char is a digit
            identifier = "_" + identifier;
            break;
        }
        identifier = identifier.substr(1);
    }

    util::erase_remove_if(identifier, testRest);
    return identifier;
}

}  // namespace util
}  // namespace inviwo
