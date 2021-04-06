#ifndef INDICATORWIDGET_H
#define INDICATORWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QBoxLayout>
#include <QDebug>

class IndicatorWidget : public QWidget
{
    Q_OBJECT

public:
    enum IndicatorState
    {
       ON,
       OFF
    };

    explicit IndicatorWidget(QString setWarningMessage = "Warning!", QWidget *parent = nullptr);
    void setState(IndicatorWidget::IndicatorState setTo, QString from);
    QLabel *label;

public slots:

private:
    IndicatorState myState;
    QString warningMessage;
    QString normalMessage;

protected:


signals:

};

#endif // INDICATORWIDGET_H
