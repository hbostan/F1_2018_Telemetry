#include "mainwindow.h"
#include <QApplication>
#include <QtCharts/QChartView>
#include <QDebug>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  qDebug() << "STARTING";
  MainWindow w;
  w.resize(1500,300);
  w.show();
  //w.addData(QPointF(2,3));
  //w.addData(QPointF(5,24));
  //w.addData(QPointF(15,60));
  //w.addData(QPointF(30,45));
  //w.addData(QPointF(67,11));
  //w.addData(QPointF(106,24));

  qDebug() << "ENDING";
  return a.exec();
}
