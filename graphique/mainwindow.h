#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QTimer>

#include "acquisition.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    Acquisition_USB_4704* mes_Acquisitions;

    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_clicked_3();
    void dessiner();

private:
    Ui::MainWindow *ui;

    QChart *monchart;
    QLineSeries *vitesse;
    QLineSeries *regime;
    QLineSeries *couple;
    QLineSeries *puissance;
    QValueAxis *axe_X,*axe_Y,*axe_Y_regime;
    QChartView *chartView;

    qreal x;
    qreal y;
    qreal c;

    QTimer* myTimer;
};
#endif // MAINWINDOW_H
