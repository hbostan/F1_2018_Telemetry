#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QThread>
#include "datadisplay.h"
#include "SafeQueue.h"
#include "PacketAnalyzer.h"
#include "UDPListener.h"
#include "packets.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void addData(QPointF point);
private slots:
  void on_closeButton_clicked();

private:
  Ui::MainWindow *ui;
  DataDisplay* dsp;
  QChartView* chartView;
  PacketAnalyzer* packet_analyzer;
  UDPListener* udp_listener;
  QThread analyze_thread;
  QThread listen_thread;
  SafeQueue<NetworkPacket>* network_packet_queue;

};

#endif // MAINWINDOW_H
