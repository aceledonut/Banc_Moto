#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "acquisition_usb_4704.h"
#include <QMainWindow>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    QTimer * myTimer;
    void afficher();
    Acquisition_USB_4704* mes_Acquisitions;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
