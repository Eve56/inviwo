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

#include <warn/push>
#include <warn/ignore/all>
#include <QFile>
#include <warn/pop>
#include <inviwo/qt/applicationbase/inviwoapplicationqt.h>
#include <inviwo/core/common/defaulttohighperformancegpu.h>
#include <inviwo/core/util/commandlineparser.h>
#include <inviwo/core/util/filesystem.h>
#include <inviwo/core/util/logcentral.h>
#include <inviwo/core/util/raiiutils.h>
#include <inviwo/core/network/processornetwork.h>
#include <inviwo/core/util/raiiutils.h>
#include <inviwo/qt/editor/inviwomainwindow.h>
#include <inviwo/core/util/filelogger.h>
#include "inviwosplashscreen.h"
#include <moduleregistration.h>
#include <inviwo/core/util/logerrorcounter.h>

int main(int argc, char** argv) {
    inviwo::LogCentral::init();
    inviwo::util::OnScopeExit deleteLogcentral([]() { inviwo::LogCentral::deleteInstance(); });
    auto logCounter = std::make_shared<inviwo::LogErrorCounter>();    
    inviwo::LogCentral::getPtr()->registerLogger(logCounter);
    inviwo::InviwoApplicationQt inviwoApp("Inviwo v" + IVW_VERSION, argc, argv);
    inviwoApp.setWindowIcon(QIcon(":/icons/inviwo_light.png"));
    inviwoApp.setAttribute(Qt::AA_NativeWindows);
    QFile styleSheetFile(":/stylesheets/inviwo.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QString::fromUtf8(styleSheetFile.readAll());
    inviwoApp.setStyleSheet(styleSheet);
    styleSheetFile.close();

    auto& clp = inviwoApp.getCommandLineParser();

    inviwo::InviwoMainWindow mainWin(&inviwoApp);

    // initialize and show splash screen
    inviwo::InviwoSplashScreen splashScreen(clp.getShowSplashScreen());
    inviwoApp.setProgressCallback([&splashScreen](std::string s) { splashScreen.showMessage(s); });

    splashScreen.show();
    splashScreen.showMessage("Loading application...");

    // Initialize application and register modules
    splashScreen.showMessage("Initializing modules...");
    inviwoApp.registerModules(&inviwo::registerAllModules);
    inviwoApp.processEvents();

    // Do this after registerModules if some arguments were added
    clp.parse(inviwo::CommandLineParser::Mode::Normal);

    // setup main window
    mainWin.updateForNewModules();
    inviwoApp.processEvents();
    splashScreen.showMessage("Loading workspace...");
    inviwoApp.processEvents();
    mainWin.showWindow();
    inviwoApp.processEvents();  // Make sure the gui is done loading before loading workspace

    mainWin.openLastWorkspace(clp.getWorkspacePath());  // open last workspace
    splashScreen.finish(&mainWin);

    inviwoApp.processEvents();
    clp.processCallbacks(); // run any command line callbacks from modules.
    inviwoApp.processEvents();

    inviwo::util::OnScopeExit clearNetwork([&](){
        inviwoApp.getProcessorNetwork()->clear();
    });

    if (auto numErrors = logCounter->getWarnCount()) {
        LogWarnCustom("inviwo.cpp", numErrors << " warnings generated during startup");
    }

    if (auto numErrors = logCounter->getErrorCount()) {
        LogErrorCustom("inviwo.cpp", numErrors << " errors generated during startup");
    }
    

    // process last arguments
    if (!clp.getQuitApplicationAfterStartup()) {
        return inviwoApp.exec();
    }
    else {
        mainWin.exitInviwo(false);
        return 0;
    }
}
