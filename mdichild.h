/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MDICHILD_H
#define MDICHILD_H

#include "qcustomplot.h"
#include "extendedslider.h"
#include "mdichildtype.h"
#include "indicatorwidget.h"
#include "datathread.h"
#include <QLabel>
#include <QWidget>

class MdiChild : public QMdiSubWindow
{
    Q_OBJECT

public:
    MdiChildType mySignalType;

    double x_data;
    double y_data;

    explicit MdiChild(MdiChildType signalType = MdiChildType::TriangleSignal, QWidget *parent = nullptr);
    ~MdiChild();

private:
    QWidget *mainWidget;

    QCustomPlot *customPlot;
    QCPItemLine *line_item1;
    QCPItemLine *line_item2;

    QVBoxLayout *mainLayout;

    ExtendedSlider *slider1;
    ExtendedSlider *slider2;

    ExtendedSlider *warnSlider1;
    ExtendedSlider *warnSlider2;

    IndicatorWidget *indicator1;
    IndicatorWidget *indicator2;

    QLabel *label;
    DataThread *workThread;

    void warnTaskTriangle(void);
    void warnTaskSin(void);
    void warnTaskRandom(void);
    void warnTaskOptional(void);

protected:
    double param1;
    double param2;

    double warnVal1;
    double warnVal2;

    void closeEvent(QCloseEvent *e);

public slots:
    void onDataChanged(double,double);

private slots:
    void getValueExtSlider1(double slot_val);
    void getValueExtSlider2(double slot_val);
    void getValueWarnSlider1(double slot_val);
    void getValueWarnSlider2(double slot_val);

signals:
    void changeParam1(double);
    void changeParam2(double);
    void warningSignal(MdiChildType childType);
    void testSignal();
};

#endif
