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

#include <modules/qtwidgets/properties/texteditorwidgetqt.h>
#include <inviwo/core/common/inviwoapplication.h>
#include <inviwo/core/common/inviwomodule.h>
#include <inviwo/core/util/settings/systemsettings.h>
#include <inviwo/core/util/filesystem.h>
#include <inviwo/core/properties/property.h>
#include <modules/qtwidgets/editablelabelqt.h>

#include <modules/qtwidgets/properties/syntaxhighlighter.h>
#include <modules/qtwidgets/qtwidgetsmoduledefine.h>
#include <modules/qtwidgets/properties/buttonpropertywidgetqt.h>
#include <modules/qtwidgets/properties/filepropertywidgetqt.h>
#include <modules/qtwidgets/properties/propertywidgetqt.h>
#include <modules/qtwidgets/properties/stringpropertywidgetqt.h>


#include <warn/push>
#include <warn/ignore/all>
#include <QTextDocument>
#include <QTextBlock>
#include <QFileInfo>
#include <QVBoxLayout>
#include <QToolButton>
#include <QToolBar>
#include <QTextEdit>
#include <QDesktopServices>
#include <QTextStream>
#include <QMessageBox>
#include <warn/pop>

namespace inviwo {

ModifiedWidget::ModifiedWidget() {
    QVBoxLayout* textEditorLayout = new QVBoxLayout();
    textEditorLayout->setSpacing(0);
    textEditorLayout->setMargin(0);
    toolBar_ = new QToolBar();
    saveButton_ = new QToolButton();
    saveButton_->setIcon(QIcon(":/icons/save.png"));  // Temporary icon
    saveButton_->setToolTip("Save file");
    unDoButton_ = new QToolButton();
    unDoButton_->setIcon(QIcon(":/icons/arrow_left.png"));  // Temporary icon
    unDoButton_->setToolTip("Undo");
    reDoButton_ = new QToolButton();
    reDoButton_->setIcon(QIcon(":/icons/arrow_right.png"));  // Temporary icon
    reDoButton_->setToolTip("Redo");
    reLoadButton_ = new QToolButton();
    reLoadButton_->setIcon(QIcon(":/icons/inviwo_tmp.png"));  // Temporary icon
    reLoadButton_->setToolTip("Reload");
    toolBar_->addWidget(saveButton_);
    toolBar_->addSeparator();
    toolBar_->addWidget(unDoButton_);
    toolBar_->addSeparator();
    toolBar_->addWidget(reDoButton_);
    toolBar_->addSeparator();
    toolBar_->addWidget(reLoadButton_);
    toolBar_->addSeparator();
    textEditor_ = new QTextEdit();
    textEditor_->createStandardContextMenu();
    syntaxHighligther_ = SyntaxHighligther::createSyntaxHighligther<None>(textEditor_->document());
    textEditorLayout->addWidget(toolBar_);
    textEditorLayout->addWidget(textEditor_);
    setLayout(textEditorLayout);
    connect(unDoButton_, SIGNAL(pressed()), textEditor_, SLOT(undo()));
    connect(reDoButton_, SIGNAL(pressed()), textEditor_, SLOT(redo()));
}

void ModifiedWidget::closeEvent(QCloseEvent* event) {
    if (mainParentWidget_->saveDialog())
        event->accept();
    else
        event->ignore();
}

SyntaxHighligther* ModifiedWidget::getSyntaxHighligther() { return syntaxHighligther_; }

void ModifiedWidget::setParent(TextEditorWidgetQt* tmp) {
    mainParentWidget_ = tmp;
}


TextEditorWidgetQt::TextEditorWidgetQt(Property* property) : PropertyWidgetQt(property) {
    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->setSpacing(0);

    btnEdit_ = new QToolButton();
    btnEdit_->setIcon(QIcon(":/icons/edit.png"));

    if (dynamic_cast<FileProperty*>(property_)) {
        fileWidget_ = new FilePropertyWidgetQt(static_cast<FileProperty*>(property_));
        connect(btnEdit_, SIGNAL(clicked()), this, SLOT(editFile()));
        fileWidget_->layout()->addWidget(btnEdit_);
        hLayout->addWidget(fileWidget_);
    } else if (dynamic_cast<StringProperty*>(property_)) {
        stringWidget_ = new StringPropertyWidgetQt(static_cast<StringProperty*>(property_));
        connect(btnEdit_, SIGNAL(clicked()), this, SLOT(editString()));
        stringWidget_->layout()->addWidget(btnEdit_);
        hLayout->addWidget(stringWidget_);
    }

    setLayout(hLayout);

    textEditorWidget_ = new ModifiedWidget();
    textEditorWidget_->setParent(this);
    if (property_->getSemantics().getString() == "ShaderEditor") {
        textEditorWidget_->getSyntaxHighligther()->setSyntax<GLSL>();
    }

    updateFromProperty();
}

TextEditorWidgetQt::~TextEditorWidgetQt() {
    delete textEditorWidget_;
}

// Function loads the file into the textEditor_
void TextEditorWidgetQt::editFile() {
    // fetch settings from the settings menu to determine what editor to use
    InviwoApplication* inviwoApp = InviwoApplication::getPtr();

    if (dynamic_cast<BoolProperty*>(
            inviwoApp->getSettingsByType<SystemSettings>()->getPropertyByIdentifier("txtEditor"))
            ->get()) {
        tmpPropertyValue_ = static_cast<StringProperty*>(property_)->get();
        const QString filePath_ = QString::fromStdString(tmpPropertyValue_);
        QUrl url_ = QUrl(filePath_);
        QDesktopServices::openUrl(url_);
    } else {
        connect(textEditorWidget_->saveButton_, SIGNAL(pressed()), this, SLOT(writeToFile()));
        connect(textEditorWidget_->reLoadButton_, SIGNAL(pressed()), this, SLOT(loadFile()));
        loadFile();
        std::string fileName = static_cast<StringProperty*>(property_)->get();
        std::string extension = filesystem::getFileExtension(fileName);

        textEditorWidget_->show();
    }
}

void TextEditorWidgetQt::loadFile() {
    tmpPropertyValue_ = static_cast<StringProperty*>(property_)->get();
    file_ = new QFile(QString::fromStdString(tmpPropertyValue_));
    file_->open(QIODevice::ReadWrite);
    QTextStream textStream_(file_);
    std::string extension = filesystem::getFileExtension(tmpPropertyValue_);

    textEditorWidget_->textEditor_->setPlainText(textStream_.readAll());
}

//Function writes content of the textEditor_ to the file
bool TextEditorWidgetQt::writeToFile() {
    //Close the file to open it with new flags
    file_->close();
    file_->open(QIODevice::WriteOnly|QIODevice::Truncate);
    QTextStream textStream(file_);
    QFileInfo qfileInfo(file_->fileName());
    QString qfilename(qfileInfo.fileName());
    std::string fileName = qfilename.toLocal8Bit().constData();
    std::string extension = filesystem::getFileExtension(fileName);

    textStream << textEditorWidget_->textEditor_->toPlainText();

    file_->close();
    return true;
}
//Loads string into textEditor
void TextEditorWidgetQt::editString() {
    connect(textEditorWidget_->saveButton_, SIGNAL(pressed()), this, SLOT(writeToString()));
    connect(textEditorWidget_->reLoadButton_, SIGNAL(pressed()), this, SLOT(loadString()));
    loadString();
    textEditorWidget_->show();
}

void TextEditorWidgetQt::loadString() {
    tmpPropertyValue_ = static_cast<StringProperty*>(property_)->get();
    textEditorWidget_->textEditor_->setPlainText(QString::fromStdString(tmpPropertyValue_));
}
bool TextEditorWidgetQt::writeToString() {
    static_cast<StringProperty*>(property_)->set(textEditorWidget_->textEditor_->toPlainText().toLocal8Bit().constData());
    stringWidget_->updateFromProperty();
    return true;
}

bool TextEditorWidgetQt::saveDialog() {
    if (textEditorWidget_->textEditor_->document()->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Application"),
                                   tr("The document has been modified.\n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if (ret == QMessageBox::Save) {
            if (dynamic_cast<FileProperty*>(property_)) return TextEditorWidgetQt::writeToFile();

            if (dynamic_cast<StringProperty*>(property_))
                return TextEditorWidgetQt::writeToString();
        } else if (ret == QMessageBox::Cancel)
            return false;
    }

    return true;
}

void TextEditorWidgetQt::updateFromProperty() {
    StringProperty* stringProp = dynamic_cast<StringProperty*>(property_);
    FileProperty* fileProp = dynamic_cast<FileProperty*>(property_);

    if (stringProp)
        stringWidget_->updateFromProperty();
    else if (fileProp)
        fileWidget_->updateFromProperty();
}

SyntaxHighligther* TextEditorWidgetQt::getSyntaxHighligther() {
    return textEditorWidget_->getSyntaxHighligther();
}

} // namespace


