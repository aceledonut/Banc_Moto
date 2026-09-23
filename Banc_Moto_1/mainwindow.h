#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QPixmap>

#include "bdaqctrl.h"

using namespace Automation::BDaq;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void lectureDI();

private:
    Ui::MainWindow *ui;

    // Carte USB-4704
    InstantDiCtrl *instantDiCtrl;
    InstantDoCtrl *instantDoCtrl;

    // Timer
    QTimer *myTimer;

    // Nombre de ports
    int portCount;

    // Etats
    bool bancDemarre;
    bool roueFixee;
    bool ancienneKey1;

    // Position de la roue
    int positionRoue;
};

#endif // MAINWINDOW_H
