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
#include "extendedslider.h"

MdiChild::~MdiChild()
{
    delete customPlot;
}

MdiChild::MdiChild(QString childName, QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle(childName);
    this->setMinimumSize(300, 150);

    x_data = 0;
    amplitude = 1.0;
    period = 1.0;

    mainLayout = new QVBoxLayout(this);
    customPlot = new QCustomPlot();
    amplitudeExtSlider = new ExtendedSlider("amplitude", 0, 5, 1);
    periodExtSlider = new ExtendedSlider("period", 0, 5, 1);

    mainLayout->addWidget(customPlot);
    mainLayout->addWidget(amplitudeExtSlider);
    mainLayout->addWidget(periodExtSlider);
    setLayout(mainLayout);

    customPlot->setObjectName(QString::fromUtf8("bla bla bla"));
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::red));
    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::green));
    customPlot->show();

    customPlot->axisRect()->setupFullAxesBox();
    customPlot->yAxis->setRange(-1.2, 1.2);

    connect(amplitudeExtSlider, SIGNAL(mySignal(double)), this, SLOT(getAmplitude(double)));
    connect(periodExtSlider, SIGNAL(mySignal(double)), this, SLOT(getPeriod(double)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(50); // Interval 0 means to refresh as fast as possible
                          // in msec
}

void MdiChild::resizeEvent(QResizeEvent* event)
{
    //customPlot->resize(mainLayout->contentsRect().width(), height());
}

void MdiChild::realtimeDataSlot()
{
    // TODO depends from timer it mast be equal to 1 sec
    double step = 0.005;
    // TODO solve overflow problem
    x_data += step;
    y_data = triangle_signal(x_data, amplitude, period);
    //y_data = sin_signal(x_data, 2.0, 1.0);

    customPlot->graph(0)->addData(x_data, y_data);
    customPlot->graph(1)->addData(x_data, random_signal(x_data, amplitude, period));


    customPlot->xAxis->setRange(x_data, step * 40, Qt::AlignRight);
    customPlot->yAxis->setRange(-1, 10, Qt::AlignBottom);

    customPlot->replot();
}

double MdiChild::sin_signal(double x, double ampl, double period)
{
    return ampl * sin(2 * M_PI * x * 1.0/period);
}

double MdiChild::triangle_signal(double x, double ampl, double period)
{
    //return 1.0 - fabs(fmod(x, 2.0) - 1.0);
    return ampl/(M_PI) * asin(cos(2 * M_PI * x * 1.0/period));
}

double MdiChild::random_signal(double min, double max)
{
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

void MdiChild::getAmplitude(double slot_val)
{
    amplitude = slot_val;
}

void MdiChild::getPeriod(double slot_val)
{
    period = slot_val;
}
