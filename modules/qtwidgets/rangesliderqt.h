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

#ifndef IVW_RANGESLIDERQT_H
#define IVW_RANGESLIDERQT_H

#include <modules/qtwidgets/qtwidgetsmoduledefine.h>
#include <warn/push>
#include <warn/ignore/all>
#include <QSplitter>
#include <QResizeEvent>
#include <QFrame>
#include <warn/pop>

#include <functional>

namespace inviwo {

class RangeSliderMiddle;

class IVW_MODULE_QTWIDGETS_API RangeSliderQt : public QSplitter {
#include <warn/push>
#include <warn/ignore/all>
    Q_OBJECT
#include <warn/pop>

public:
    RangeSliderQt(Qt::Orientation orientation=Qt::Horizontal, QWidget* parent=nullptr, bool showTooltip = false);
    virtual ~RangeSliderQt() = default;

public slots:
    int minValue();
    int maxValue();
    int minRange();
    int maxRange();
    int minSeperation();

    void setValue(int, int);
    void setMinValue(int);
    void setMaxValue(int);
    void setMinSeparation(int);

    void setRange(int, int);
    void setMinRange(int);
    void setMaxRange(int);

    virtual bool eventFilter(QObject *obj, QEvent *event) override;
    void setTooltipFormat(std::function<std::string(int, int)> formater);


signals:
    void valuesChanged(int min, int max);
    void valuesSet(int min, int max);

protected:
    void resizeEvent(QResizeEvent* event) override;

    void updateStateFromSliders();
    void updateSlidersFromState();

protected slots:
    void updateSplitterPosition(int pos, int idx);
    void middleMoved(int delta);

private:
    int range_[2];
    int value_[2];
    RangeSliderMiddle* middle_;
    int minSeperation_;
    std::function<std::string(int, int)> formatTooltip_;
};

class IVW_MODULE_QTWIDGETS_API RangeSliderMiddle : public QFrame {
    #include <warn/push>
    #include <warn/ignore/all>
    Q_OBJECT
    #include <warn/pop>
public:
    RangeSliderMiddle(QWidget* parent = nullptr, Qt::Orientation orientation = Qt::Horizontal);
    virtual ~RangeSliderMiddle() = default;

signals:
    void middleMoved(int delta);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    Qt::Orientation orientation_;
    int lastMouseX_;
    bool drag_;
};


}//namespace

#endif // IVW_RANGESLIDERQT_H