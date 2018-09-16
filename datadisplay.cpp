#include "datadisplay.h"

QLineSeries* DataDisplay::getThrottleSeries() const
{
  return m_throttle;
}

QLineSeries* DataDisplay::getBrakeSeries() const {
  return m_brake;
}

QLineSeries* DataDisplay::getSteerSeries() const {
  return m_steer;
}

QChart* DataDisplay::getChart() const
{
  return m_chart;
}

QValueAxis* DataDisplay::getAxisX() const
{
  return m_axisX;
}

QValueAxis* DataDisplay::getAxisY() const
{
  return m_axisY;
}

DataDisplay::DataDisplay(QObject *parent) : QObject(parent)
{
  m_throttle = new QLineSeries(this);
  m_brake = new QLineSeries(this);
  m_steer = new QLineSeries(this);
  m_chart = new QChart();
  m_axisX = new QValueAxis();
  m_axisY = new QValueAxis();
  //m_chart->setTheme(QChart::ChartTheme::ChartThemeDark);

  QPen pen(Qt::green);
  pen.setWidth(3);
  m_throttle->setPen(pen);
  m_throttle->append(QPointF(0.0,0.0));
  //m_throttle->append(QPointF(25.0,25.0));
  m_throttle->setUseOpenGL(true);

  pen = QPen(Qt::red);
  pen.setWidth(3);
  m_brake->setPen(pen);
  m_brake->append(QPointF(0.0, 0.0));
  //m_brake->append(QPointF(25.0, 50.0));
  m_brake->setUseOpenGL(true);

  pen = QPen(Qt::magenta);
  pen.setWidth(3);
  m_steer->setPen(pen);
  m_steer->append(QPointF(0.0, 0.0));
  //m_steer->append(QPointF(25.0,100.0));
  m_steer->setUseOpenGL(true);

  m_chart->addSeries(m_throttle);
  m_chart->addSeries(m_brake);
  m_chart->addSeries(m_steer);
  m_chart->createDefaultAxes();
  m_chart->addAxis(m_axisX, Qt::AlignBottom);
  m_chart->addAxis(m_axisY, Qt::AlignLeft);
  m_chart->axisX()->setRange(0,0);
  m_chart->axisY()->setRange(0,120);
  m_axisX->setTickCount(4+1);
  m_chart->setBackgroundBrush(QBrush(Qt::black));

  m_throttle->attachAxis(m_chart->axisX());
  m_throttle->attachAxis(m_chart->axisY());
  m_brake->attachAxis(m_chart->axisX());
  m_brake->attachAxis(m_chart->axisY());
  m_steer->attachAxis(m_chart->axisX());
  m_steer->attachAxis(m_chart->axisY());

  m_chart->legend()->hide();

  //m_chart->setAnimationOptions(QChart::AnimationOption::SeriesAnimations);

}

void DataDisplay::receiveAnalyzedPacket(QPointF throttle, QPointF brake, QPointF steer)
{
  if(throttle.rx() > 0) {
    m_chart->axisX()->setRange(0, throttle.rx()+10);
    m_axisX->setTickCount(((throttle.rx()+10)/(throttle.rx()+10/25))+1);
  }
  m_throttle->append(throttle);
  m_brake->append(brake);
  m_steer->append(steer);

}
