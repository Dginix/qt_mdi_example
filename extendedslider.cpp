#include "extendedslider.h"
#include <QHBoxLayout>
#include <QDebug>

ExtendedSlider::ExtendedSlider(QString label_name, double def_min, double def_max,
                               double def_val, QWidget *parent) : QWidget(parent)
{
    min = def_min;
    max = def_max;
    value = def_val;

    label = new QLabel(this);
    label->setText(label_name);
    label->setAlignment(Qt::AlignCenter);

    slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(1000);

    spinBox = new QDoubleSpinBox;
    spinBox->setMinimum(min);
    spinBox->setMaximum(max);
    spinBox->setSingleStep((max-min)/100);

    spinBox->setValue(value);
    updateValueFromSpinBox();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(label);
    mainLayout->addWidget(spinBox);
    mainLayout->addWidget(slider);
    setLayout(mainLayout);

    connect(slider,SIGNAL(valueChanged(int)), this, SLOT(updateValueFromSlider()));
    connect(spinBox,SIGNAL(valueChanged(double)), this, SLOT(updateValueFromSpinBox()));

    setMinimumWidth(50);
    setMaximumHeight(50);
    setMinimumHeight(50);
}

void ExtendedSlider::updateValueFromSlider()
{
    value = (double)slider->value()/(slider->maximum()-slider->minimum())*(max-min)+min;
    spinBox->setValue(value);
    emit mySignal(value);
}

void ExtendedSlider::updateValueFromSpinBox()
{
    value = spinBox->value();
    slider->setValue(value/(max-min)*(slider->maximum()-slider->minimum())+slider->minimum());
    emit mySignal(value);
}






