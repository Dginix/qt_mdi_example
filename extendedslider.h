#ifndef EXTENDEDSLIDER_H
#define EXTENDEDSLIDER_H

#include <QWidget>
#include <QSlider>
#include <QDoubleSpinBox>
#include <QLabel>
#include <math.h>

class ExtendedSlider : public QWidget
{
    Q_OBJECT

public:
    explicit ExtendedSlider(QString label_name = "default", double def_min = 0,
                            double def_max = 1, double def_val = 0, QWidget *parent = nullptr);
    QSlider *slider;
    QDoubleSpinBox *spinBox;
    QLabel *label;
    double min, max, value, extSliderStep;
    int sliderCoeff;

signals:
    void mySignal(double sign_val);

private slots:
    void updateValueFromSlider();
    void updateValueFromSpinBox();

};

#endif // EXTENDEDSLIDER_H
