#ifndef DATADISPLAY_H
#define DATADISPLAY_H

#include <QObject>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

class DataDisplay : public QObject
{
  Q_OBJECT
private:
  //QLineSeries* m_speed;
  QLineSeries* m_throttle;
  QLineSeries* m_brake;
  QLineSeries* m_steer;
  QChart* m_chart;
  QValueAxis* m_axisX;
  QValueAxis* m_axisY;

public:
  explicit DataDisplay(QObject *parent = nullptr);

  QLineSeries* getThrottleSeries() const;
  QLineSeries* getBrakeSeries() const;
  QLineSeries* getSteerSeries() const;


  QChart* getChart() const;

  QValueAxis* getAxisX() const;
  QValueAxis* getAxisY() const;

signals:

public slots:
  void receiveAnalyzedPacket(QPointF throttle, QPointF brake, QPointF steer);
};

#endif // DATADISPLAY_H
