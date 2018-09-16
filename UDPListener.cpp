#include "UDPListener.h"
#include <QtNetwork/QHostAddress>

UDPListener::UDPListener(QString ip_addr, quint16 port, SafeQueue<NetworkPacket>* q)
  : ip_addr(ip_addr), port(port), q(q) {
}

UDPListener::~UDPListener() {
}

void UDPListener::Run() {
  socket = new QUdpSocket();
  QHostAddress addr(ip_addr);
  if(!socket->bind(addr, port)) {
    qWarning() << "SOCKET BIND FAILED";
  }
  NetworkPacket data;
  qDebug() << "Listening on thread #" << QThread::currentThreadId() << "\n";
  while (true) {
    if(socket->hasPendingDatagrams()) {
      memset(&data, 0, NETWORK_PACKET_SIZE);
      int bytes_read = socket->readDatagram((char *)(&data), NETWORK_PACKET_SIZE);
      if (bytes_read == -1) {
        qDebug() << "Socket read error.\n";
        continue;
      }
      q->push_item(data);
    }
  }
}
