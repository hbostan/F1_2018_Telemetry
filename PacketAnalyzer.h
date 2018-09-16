#ifndef PACKETANALYZER_H
#define PACKETANALYZER_H

#include <QObject>
#include <QPointF>
#include "packets.h"
#include <future>
#include "SafeQueue.h"

class PacketAnalyzer : public QObject {
  Q_OBJECT
private:
  SafeQueue<NetworkPacket>* q;
signals:
  void packetAnalyzed(QPointF throttle, QPointF brake, QPointF steer);

public:
  PacketAnalyzer(SafeQueue<NetworkPacket>* q): q(q) {}
public slots:
  void Run();
  
};

#endif
