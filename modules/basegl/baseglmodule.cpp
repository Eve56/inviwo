/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 * Version 0.6b
 *
 * Copyright (c) 2013-2014 Inviwo Foundation
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
 * Main file author: Erik Sund�n
 *
 *********************************************************************************/

#include <modules/basegl/baseglmodule.h>

#include <modules/basegl/processors/background.h>
#include <modules/basegl/processors/drawlines.h>
#include <modules/basegl/processors/drawfreehand.h>
#include <modules/basegl/processors/entryexitpoints.h>
#include <modules/basegl/processors/findedges.h>
#include <modules/basegl/processors/firstivwprocessor.h>
#include <modules/basegl/processors/imageclassify.h>
#include <modules/basegl/processors/imagegrayscale.h>
#include <modules/basegl/processors/imagelayoutgl.h>
#include <modules/basegl/processors/imagemixer.h>
#include <modules/basegl/processors/lightingraycaster.h>
#include <modules/basegl/processors/lightvolumegl.h>
#include <modules/basegl/processors/multiplanar.h>
#include <modules/basegl/processors/positionwidgetprocessor.h>
#include <modules/basegl/processors/redgreenprocessor.h>
#include <modules/basegl/processors/simpleraycaster.h>
#include <modules/basegl/processors/volumeslicegl.h>

namespace inviwo {

BaseGLModule::BaseGLModule() : InviwoModule() {
    setIdentifier("BaseGL");
    registerProcessor(Background);
    registerProcessor(DrawLines);
    registerProcessor(DrawFreeHand);
    registerProcessor(EntryExitPoints);
    registerProcessor(FindEdges);
    registerProcessor(FirstIvwProcessor);
    registerProcessor(ImageClassify);
    registerProcessor(ImageGrayscale);
    registerProcessor(ImageLayoutGL);
    registerProcessor(ImageMixer);
    registerProcessor(LightingRaycaster);
    registerProcessor(LightVolumeGL);
    registerProcessor(MultiPlanar);
    registerProcessor(PositionWidgetProcessor);
    registerProcessor(RedGreenProcessor);
    registerProcessor(SimpleRaycaster);
    registerProcessor(VolumeSliceGL);
}

} // namespace
