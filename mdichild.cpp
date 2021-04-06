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

#include <QtWidgets>
#include "mdichild.h"
#include <QtDebug>

MdiChild::~MdiChild()
{
    delete customPlot;
}

MdiChild::MdiChild(MdiChildType signalType, QWidget *parent) : QWidget(parent), mySignalType(signalType)
{
    setAttribute(Qt::WA_DeleteOnClose);
    mainLayout = new QVBoxLayout(this);
    customPlot = new QCustomPlot(this);

    customPlot->setObjectName(QString::fromUtf8("signal"));
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::black));

    customPlot->axisRect()->setupFullAxesBox();
    customPlot->yAxis->setRange(-1.2, 1.2);
    customPlot->show();

    line_item1 = new QCPItemLine(customPlot);

    switch(mySignalType)
    {
        case MdiChildType::TriangleSignal:
            //if low
            this->setWindowTitle("TriangleSignal");
            warnSlider1 = new ExtendedSlider("low tresh", 0, 5, 0);
            mainLayout->addWidget(warnSlider1);
            connect(warnSlider1, SIGNAL(mySignal(double)), this, SLOT(getValueWarnSlider1(double)));
            break;

        case MdiChildType::SinSignal:
            this->setWindowTitle("SinSignal");
            warnSlider1 = new ExtendedSlider("high tresh", 0, 5, 0);
            mainLayout->addWidget(warnSlider1);
            connect(warnSlider1, SIGNAL(mySignal(double)), this, SLOT(getValueWarnSlider1(double)));
            break;

        case MdiChildType::RandomSignal:
            this->setWindowTitle("RandomSignal");
            break;

        case MdiChildType::OptionSignal:
            this->setWindowTitle("OptionSignal");
            break;

        case MdiChildType::MainWindow: break;
    }

    this->setMinimumSize(300, 150);

    x_data = 0;
    param1 = 1.0;
    param2 = 1.0;


    if(mySignalType == MdiChildType::RandomSignal)
    {
        slider1 = new ExtendedSlider("min", 0, 5, 1);
        slider2 = new ExtendedSlider("max", 0, 5, 1);
    }
    else
    {
        slider1 = new ExtendedSlider("amplitude", 0, 5, 1);
        slider2 = new ExtendedSlider("period", 0, 5, 1);
    }

    indicator1 = new IndicatorWidget("Warning!", this);

    mainLayout->addWidget(customPlot);
    mainLayout->addWidget(slider1);
    mainLayout->addWidget(slider2);
    mainLayout->addWidget(indicator1);

    setLayout(mainLayout);

    workThread = new DataThread(mySignalType);
    connect(workThread, SIGNAL(valueChanged(double,double)), this, SLOT(onDataChanged(double,double)));
    connect(workThread, SIGNAL(finished()), workThread, SLOT(deleteLater()));
    connect(this, SIGNAL(changeParam1(double)), workThread, SLOT(getParam1(double)));
    connect(this, SIGNAL(changeParam2(double)), workThread, SLOT(getParam2(double)));
    workThread->start();

    connect(slider1, SIGNAL(mySignal(double)), this, SLOT(getValueExtSlider1(double)));
    connect(slider2, SIGNAL(mySignal(double)), this, SLOT(getValueExtSlider2(double)));
}

void MdiChild::getValueExtSlider1(double slot_val)
{
    param1 = slot_val;
    emit changeParam1(param1);
}

void MdiChild::getValueExtSlider2(double slot_val)
{
    param2 = slot_val;
    emit changeParam1(param2);
}

void MdiChild::getValueWarnSlider1(double slot_val)
{
    warnVal1 = slot_val;
}

void MdiChild::getValueWarnSlider2(double slot_val)
{
    warnVal2 = slot_val;
}

void MdiChild::onDataChanged(double x, double y)
{
    static double last_x = 0;

    x_data = x;
    y_data = y;

    customPlot->graph(0)->addData(x, y);
    customPlot->xAxis->setRange(x, 10, Qt::AlignRight);
    customPlot->yAxis->setRange(-1, 10, Qt::AlignBottom);

    line_item1->setPen(QPen(Qt::red));

    line_item1->start->setCoords(x - 11, warnVal1);
    line_item1->end->setCoords(x + 11, warnVal1);

    customPlot->replot();

    if(y > warnVal1)
    {
        indicator1->setState(IndicatorWidget::IndicatorState::ON, windowTitle());
    }
    else
    {
        indicator1->setState(IndicatorWidget::IndicatorState::OFF, windowTitle());
    }
}
