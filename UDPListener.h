#ifndef UDPLISTENER_H
#define UDPLISTENER_H

#include <QObject>
#include <QThread>
#include <QString>
#include <QtNetwork/QUdpSocket>
#include <future>
#include "packets.h"
#include "SafeQueue.h"

constexpr auto NETWORK_PACKET_SIZE = 2048;

class UDPListener : public QObject {
  Q_OBJECT
public:
  UDPListener(QString ip_addr, quint16 port, SafeQueue<NetworkPacket>* q);
  ~UDPListener();
public slots:
  void Run();
  
private:
  QUdpSocket* socket;
  QString ip_addr;
  quint16 port;
  SafeQueue<NetworkPacket>* q;
};

#endif
