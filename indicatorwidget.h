#ifndef INDICATORWIDGET_H
#define INDICATORWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QBoxLayout>

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
    void setState(IndicatorState setTo);

private:
    IndicatorState myState;
    QString *messageToShow;
    QString warningMessage;
    QString normalMessage;

protected:
    void paintEvent(QPaintEvent *) override;


signals:

};

#endif // INDICATORWIDGET_H
