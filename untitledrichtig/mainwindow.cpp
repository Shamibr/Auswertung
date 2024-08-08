#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QLineSeries>
#include <QChart>
#include <QChartView>

//sing namespace QtCharts;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_loadButton_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, "Open CSV File", "", "CSV Files (*.csv)");
    if (filename.isEmpty()) {
        return;
    }
    qDebug() << "Selected filename:" << filename;


    try {
        curve = VentilationCurve::readCSV(filename.toStdString());
        plotCurve(curve.time, curve.values);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::on_smoothButton_clicked() {
    if (curve.time.empty()) {
        QMessageBox::warning(this, "Warning", "Load a CSV file first.");
        return;
    }

    std::vector<double> smoothed_values = curve.smoothCurve(3);
    plotCurve(curve.time, smoothed_values);
}

void MainWindow::plotCurve(const std::vector<double>& time, const std::vector<double>& values) {
    QLineSeries *series = new QLineSeries();
    for (size_t i = 0; i < time.size(); ++i) {
        series->append(time[i], values[i]);
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Ventilation Curve");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //chartView->setParent(ui->horizontalFrame);
 //   ui->chartLayout->addWidget(chartView);
    ui->horizontalFrame->layout()->addWidget(chartView);
}



