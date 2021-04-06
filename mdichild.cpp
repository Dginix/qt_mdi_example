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

void MdiChild::closeEvent(QCloseEvent *e)
{
    e->ignore();
}

MdiChild::MdiChild(MdiChildType signalType, QWidget *parent) : QWidget(parent), mySignalType(signalType)
{
    x_data = 0;
    y_data = 0;

    param1 = 1.0;
    param2 = 1.0;
    this->setMinimumSize(400, 600);

    mainLayout = new QVBoxLayout(this);
    customPlot = new QCustomPlot(this);

    customPlot->setObjectName(QString::fromUtf8("signal"));
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::black));

    customPlot->axisRect()->setupFullAxesBox();
    customPlot->show();

    switch(mySignalType)
    {
        case MdiChildType::TriangleSignal:
            //if low
            this->setWindowTitle("TriangleSignal");

            warnSlider1 = new ExtendedSlider("low tresh", -5, 5, 0);
            mainLayout->addWidget(warnSlider1);
            connect(warnSlider1, SIGNAL(mySignal(double)), this, SLOT(getValueWarnSlider1(double)));

            indicator1 = new IndicatorWidget("Too Low!", this);
            mainLayout->addWidget(indicator1);

            line_item1 = new QCPItemLine(customPlot);
            line_item1->setPen(QPen(Qt::red));
            break;

        case MdiChildType::SinSignal:
            this->setWindowTitle("SinSignal");

            warnSlider1 = new ExtendedSlider("high tresh", -5, 5, 0);
            mainLayout->addWidget(warnSlider1);
            connect(warnSlider1, SIGNAL(mySignal(double)), this, SLOT(getValueWarnSlider1(double)));

            indicator1 = new IndicatorWidget("Too high!", this);
            mainLayout->addWidget(indicator1);

            line_item1 = new QCPItemLine(customPlot);
            line_item1->setPen(QPen(Qt::red));
            break;

        case MdiChildType::RandomSignal:
            this->setWindowTitle("RandomSignal");

            warnSlider1 = new ExtendedSlider("high tresh", -5, 5, 4);
            warnVal1 = 4;
            mainLayout->addWidget(warnSlider1);
            connect(warnSlider1, SIGNAL(mySignal(double)), this, SLOT(getValueWarnSlider1(double)));

            warnSlider2 = new ExtendedSlider("low tresh", -5, 5, -4);
            warnVal2 = -4;
            mainLayout->addWidget(warnSlider2);
            connect(warnSlider2, SIGNAL(mySignal(double)), this, SLOT(getValueWarnSlider2(double)));

            indicator1 = new IndicatorWidget("Warning!", this);
            mainLayout->addWidget(indicator1);

            line_item1 = new QCPItemLine(customPlot);
            line_item1->setPen(QPen(Qt::red));

            line_item2 = new QCPItemLine(customPlot);
            line_item2->setPen(QPen(Qt::green));
            break;

        case MdiChildType::OptionSignal:
            this->setWindowTitle("OptionSignal");
            break;
    }

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


    mainLayout->addWidget(customPlot);
    mainLayout->addWidget(slider1);
    mainLayout->addWidget(slider2);

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
    x_data = x;
    y_data = y;

    customPlot->graph(0)->addData(x, y);
    customPlot->xAxis->setRange(x, 10, Qt::AlignRight);
    customPlot->yAxis->setRange(-1, 10, Qt::AlignBottom);

    // here tasks for indicator
    switch(mySignalType)
    {
        case MdiChildType::TriangleSignal:  warnTaskTriangle(); break;
        case MdiChildType::SinSignal:       warnTaskSin(); break;
        case MdiChildType::RandomSignal:    warnTaskRandom(); break;
        case MdiChildType::OptionSignal:    break;
    }
    customPlot->replot();
}

void MdiChild::warnTaskTriangle(void)
{
    line_item1->start->setCoords(x_data - 11, warnVal1);
    line_item1->end->setCoords(x_data + 11, warnVal1);

    if(y_data > warnVal1)
    {
        indicator1->setState(IndicatorWidget::IndicatorState::ON);
    }
    else
    {
        indicator1->setState(IndicatorWidget::IndicatorState::OFF);
    }
}

void MdiChild::warnTaskSin(void)
{
    line_item1->start->setCoords(x_data - 11, warnVal1);
    line_item1->end->setCoords(x_data + 11, warnVal1);

    if(y_data < warnVal1)
    {
        indicator1->setState(IndicatorWidget::IndicatorState::ON);
    }
    else
    {
        indicator1->setState(IndicatorWidget::IndicatorState::OFF);
    }
}

void MdiChild::warnTaskRandom(void)
{
    static bool wasHigh = false;

    line_item1->start->setCoords(x_data - 11, warnVal1);
    line_item1->end->setCoords(x_data + 11, warnVal1);

    line_item2->start->setCoords(x_data - 11, warnVal2);
    line_item2->end->setCoords(x_data + 11, warnVal2);

    if(y_data > warnVal1)
    {
        wasHigh = true;
        indicator1->setState(IndicatorWidget::IndicatorState::ON);
    }
    else if(wasHigh && y_data < warnVal2)
    {
        wasHigh = false;
        indicator1->setState(IndicatorWidget::IndicatorState::OFF);
    }
}
