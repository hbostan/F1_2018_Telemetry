#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts/QChartView>
#include "datadisplay.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  network_packet_queue = new SafeQueue<NetworkPacket>();
  udp_listener = new UDPListener("127.0.0.1", 3333, network_packet_queue);
  packet_analyzer = new PacketAnalyzer(network_packet_queue);

  udp_listener->moveToThread(&listen_thread);
  connect(&listen_thread, SIGNAL(started()), udp_listener, SLOT(Run()));

  packet_analyzer->moveToThread(&analyze_thread);
  connect(&analyze_thread, SIGNAL(started()), packet_analyzer, SLOT(Run()));

  dsp = new DataDisplay();
  chartView = new QChartView(dsp->getChart());
  chartView->setRenderHint(QPainter::Antialiasing);

  ui->gridLayout->addWidget(chartView,0,0);

  QPushButton* closeButton = new QPushButton("Close It!");
  ui->gridLayout->addWidget(closeButton);

  connect(closeButton, SIGNAL(clicked()), this, SLOT(on_closeButton_clicked()));
  connect(packet_analyzer, SIGNAL(packetAnalyzed(QPointF, QPointF, QPointF)), dsp, SLOT(receiveAnalyzedPacket(QPointF, QPointF, QPointF)));

  listen_thread.start();
  analyze_thread.start();
}

void MainWindow::addData(QPointF point) {
  dsp->receiveAnalyzedPacket(point, point, point);
}

MainWindow::~MainWindow()
{
  qDebug() << "Exit listen thread";
  listen_thread.terminate();
  listen_thread.wait();
  qDebug() << "Exit listen thread";
  qDebug() << "Exit analyze thread";
  analyze_thread.terminate();
  analyze_thread.wait();
  qDebug() << "Exit analyze thread";
  delete ui;
}

void MainWindow::on_closeButton_clicked()
{
    qWarning() << "CLICKED BIIIITTTCHHHH!";
    this->close();
}
