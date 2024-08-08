#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vent.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadButton_clicked();
    void on_smoothButton_clicked();

private:
    Ui::MainWindow *ui;
    VentilationCurve curve;
    void plotCurve(const std::vector<double>& time, const std::vector<double>& values);
};

#endif // MAINWINDOW_H
