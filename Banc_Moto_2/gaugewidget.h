#ifndef GAUGEWIDGET_H
#define GAUGEWIDGET_H

#include <QWidget>

class GaugeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GaugeWidget(QWidget *parent = nullptr);

    void setValue(double value);
    void setMaximum(double maximum);
    void setUnit(const QString &unit);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    double valeur;
    double maximum;
    QString unite;
};

#endif // GAUGEWIDGET_H
