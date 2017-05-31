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

#include <inviwo/qt/editor/settingswidget.h>
#include <modules/qtwidgets/properties/propertywidgetqt.h>
#include <modules/qtwidgets/propertylistwidget.h>
#include <modules/qtwidgets/properties/collapsiblegroupboxwidgetqt.h>
#include <inviwo/core/properties/propertywidgetfactory.h>
#include <inviwo/core/common/inviwoapplication.h>
#include <inviwo/core/util/settings/settings.h>

#include <warn/push>
#include <warn/ignore/all>
#include <QLayout>
#include <QFrame>
#include <warn/pop>

namespace inviwo {

SettingsWidget::SettingsWidget(QString title, InviwoMainWindow* mainwindow)
    : InviwoDockWidget(title, mainwindow), mainwindow_(mainwindow) {
    setObjectName("SettingsWidget");
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    scrollArea_ = new QScrollArea();
    scrollArea_->setWidgetResizable(true);
    scrollArea_->setMinimumWidth(300);
    scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea_->setFrameShape(QFrame::NoFrame);
    scrollArea_->setContentsMargins(0, 0, 0, 0);

    mainWidget_ = new QWidget();
    layout_ = new QVBoxLayout(mainWidget_);
    layout_->setAlignment(Qt::AlignTop);
    layout_->setContentsMargins(0, PropertyWidgetQt::spacing, 0, PropertyWidgetQt::spacing);
    layout_->setSpacing(7);
    scrollArea_->setWidget(mainWidget_);

    setWidget(scrollArea_);
}

SettingsWidget::SettingsWidget(InviwoMainWindow* mainwindow)
    : SettingsWidget(tr("Settings"), mainwindow) {}

SettingsWidget::~SettingsWidget() = default;

void SettingsWidget::updateSettingsWidget() {
    auto settings = mainwindow_->getInviwoApplication()->getModuleSettings();

    for (auto& setting : settings) {
        CollapsibleGroupBoxWidgetQt* settingsGroup =
            new CollapsibleGroupBoxWidgetQt(setting->getIdentifier());
        settingsGroup->setParentPropertyWidget(nullptr, this);
        layout_->addWidget(settingsGroup);
        settingsGroup->initState();

        std::vector<Property*> props = setting->getProperties();

        for (auto& prop : props) {
            settingsGroup->addProperty(prop);
            for (auto p : prop->getWidgets()) {
                connect(static_cast<PropertyWidgetQt*>(p),
                        SIGNAL(updateSemantics(PropertyWidgetQt*)), this,
                        SLOT(updatePropertyWidgetSemantics(PropertyWidgetQt*)));
            }
        }

        if (!settingsGroup->isCollapsed()) {
            settingsGroup->toggleCollapsed();
        }
    }
    layout_->addStretch();
}

void SettingsWidget::saveSettings() {
    const auto settings = mainwindow_->getInviwoApplication()->getModuleSettings();
    for (auto& setting : settings) {
        setting->save();
    }
}

void SettingsWidget::updatePropertyWidgetSemantics(PropertyWidgetQt* widget) {
    Property* prop = widget->getProperty();

    QVBoxLayout* listLayout = static_cast<QVBoxLayout*>(widget->parentWidget()->layout());
    int layoutPosition = listLayout->indexOf(widget);

    auto factory = mainwindow_->getInviwoApplication()->getPropertyWidgetFactory();
    auto propertyWidget = static_cast<PropertyWidgetQt*>(factory->create(prop).release());

    if (propertyWidget) {
        prop->deregisterWidget(widget);

        listLayout->removeWidget(widget);
        listLayout->insertWidget(layoutPosition, propertyWidget);
        prop->registerWidget(propertyWidget);

        connect(propertyWidget, SIGNAL(updateSemantics(PropertyWidgetQt*)), this,
                SLOT(updatePropertyWidgetSemantics(PropertyWidgetQt*)));

        propertyWidget->initState();

    } else {
        LogWarn("Could not change semantic for property: " << prop->getClassIdentifier());
    }
}

void SettingsWidget::closeEvent(QCloseEvent *event) {
    saveSettings();
    InviwoDockWidget::closeEvent(event);
}

}  // namespace