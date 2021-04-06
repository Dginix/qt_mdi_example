#include "extendedslider.h"
#include <QHBoxLayout>
#include <QDebug>

ExtendedSlider::ExtendedSlider(QString label_name, double def_min, double def_max,
                               double def_val, QWidget *parent) : QWidget(parent)
{
    min = def_min;
    max = def_max;
    value = def_val;

    sliderCoeff = 1000;
    extSliderStep = (max - min)/100.0;

    label = new QLabel(this);
    label->setText(label_name);
    label->setAlignment(Qt::AlignCenter);

    slider = new QSlider(Qt::Horizontal, this);
    slider->setMinimum(min * sliderCoeff);
    slider->setMaximum(max * sliderCoeff);
    slider->setSingleStep(extSliderStep * sliderCoeff);

    spinBox = new QDoubleSpinBox(this);
    spinBox->setMinimum(min);
    spinBox->setMaximum(max);
    spinBox->setSingleStep(extSliderStep);
    spinBox->setValue(value);
    updateValueFromSpinBox();

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
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
    value = (double)slider->value() / sliderCoeff;
    spinBox->setValue(value);
    emit mySignal(value);
}

void ExtendedSlider::updateValueFromSpinBox()
{
    value = spinBox->value();
    slider->setValue(value * sliderCoeff);
    emit mySignal(value);
}






