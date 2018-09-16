#include "PacketAnalyzer.h"
#include <QDebug>

void PacketAnalyzer::Run()
{
  while (true) {
    NetworkPacket in_packet = q->pop_item();
    uint8_t packet_type = in_packet.header.m_packetId;
    float packet_time = in_packet.header.m_sessionTime;
    switch (packet_type) {
    case 0:
      //std::cout << "Motion";
      break;
    case 1:
      //std::cout << "Session";
      break;
    case 2:
      //std::cout << "Lap";
      break;
    case 3:
      //std::cout << "Event";
      break;
    case 4:
      //std::cout << "Participants";
      break;
    case 5:
      //std::cout << "Car Setups";
      break;
    case 6:
    {
      //bytes_in = read_packet(sock, packet_data, 1085, &client, &client_len);
      //PacketCarTelemetryData* telemetryData = reinterpret_cast<PacketCarTelemetryData*>(&in_packet);
      uint8_t player_car_index = in_packet.header.m_playerCarIndex;
      CarTelemetryData* player_car_telemetry = (reinterpret_cast<CarTelemetryData*>(in_packet.data))+player_car_index;
      uint8_t throttle = player_car_telemetry->m_throttle;
      uint8_t brake = player_car_telemetry->m_brake;
      int8_t steer = ((player_car_telemetry->m_steer / 2) + 50);
      double timestamp = static_cast<double>(packet_time);
      emit packetAnalyzed(QPointF(timestamp, throttle), QPointF(timestamp, brake), QPointF(timestamp, steer));
      //TODO: Emit packet analyzed
    }
    break;
    case 7:
      //bytes_in = read_packet(sock, packet_data, 1061, &client, &client_len);
      //std::cout << "Car Status";
      break;
    default:
      qDebug() << "NO SUCH PACKET";
      break;
    }
  }
}
