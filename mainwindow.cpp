#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <qmath.h>

#define POINT_STREAM_NUM 4

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int i=0; i<POINT_STREAM_NUM; i++) {
        QSharedPointer<PointStream> stream(new PointStream());
        stream->setSamplesPerSeconds(1000/SAMPLE_GENERATION_PERIOD);
        dataPoints << stream;
        ui->plotArea->addPointStream(stream);
    }

    ui->plotArea->setWindowLengthInSeconds(4.0);

    startTimer(SAMPLE_GENERATION_PERIOD);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)

    const double sineFrequency = 1.0; // 2Hz
    //const double phase = 0.0;

    for(int i=0; i<dataPoints.size(); i++) {
        double value = qSin((i*M_PI)/dataPoints.size() +
                            2.0*M_PI*sineFrequency*sampleNumber*(
                                (static_cast<double>(SAMPLE_GENERATION_PERIOD)/1000.0) )
                            );
        //qDebug() << sampleNumber << value;
        QList<QPointF> data;
        data << QPointF(sampleNumber, value);
        dataPoints.at(i)->appendPoints(data);
    }

    sampleNumber++;
}
