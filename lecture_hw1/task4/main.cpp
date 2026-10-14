#include <iostream>

int main() {
  // Карта датчиков: слои состоят из строк разной длины (int***).
  // Общая очередь хранит пакеты int[] и маски char[] через void* и метку типа.
  // Применяем пакеты по порядку и выводим полученную карту.
  int layers = 0;
  int rows = 0;
  int packet_count = 0;
  if (!(std::cin >> layers >> rows >> packet_count) || layers <= 0 ||
      layers > 20 || rows <= 0 || rows > 20 || packet_count < 0 ||
      packet_count > 1000) {
    std::cout << "error\n";
    return 0;
  }
  int** widths = new int* [layers] {};
  for (int z = 0; z < layers; ++z) {
    widths[z] = new int[rows];
    for (int y = 0; y < rows; ++y) {
      std::cin >> widths[z][y];
    }
  }
  struct Packet {
    char type;
    int layer;
    int row;
    void* payload;
  };
  Packet* packets = new Packet[packet_count]{};
  for (int i = 0; i < packet_count; ++i) {
    Packet& packet = packets[i];
    std::cin >> packet.type >> packet.layer >> packet.row;
    const int columns = widths[packet.layer][packet.row];
    if (packet.type == 'i') {
      int* readings = new int[columns];
      packet.payload = readings;
      for (int x = 0; x < columns; ++x) {
        std::cin >> readings[x];
      }
    } else {
      char* mask = new char[columns];
      packet.payload = mask;
      for (int x = 0; x < columns; ++x) {
        std::cin >> mask[x];
      }
    }
  }
  int*** map = new int**[layers];
  for (int z = 0; z < layers; ++z) {
    map[z] = new int*[rows];
    for (int y = 0; y < rows; ++y) {
      map[z][y] = new int[widths[z][y]]{};
    }
  }
  for (int i = 0; i < packet_count; ++i) {
    const Packet& packet = packets[i];
    const int columns = widths[packet.layer][packet.row];
    if (packet.type == 'i') {
      const int* readings = (const int*)packet.payload;
      for (int x = 0; x < columns; ++x) {
        map[packet.layer][packet.row][x] = readings[x];
      }
    } else {
      const char* mask = (const char*)packet.payload;
      for (int x = 0; x < columns; ++x) {
        map[packet.layer][packet.row][x] = mask[x] - '0';
      }
    }
  }
  for (int z = 0; z < layers; ++z) {
    std::cout << "layer " << z << '\n';
    for (int y = 0; y < rows; ++y) {
      for (int x = 0; x < widths[z][y]; ++x) {
        if (x > 0) {
          std::cout << ' ';
        }
        std::cout << map[z][y][x];
      }
      std::cout << '\n';
    }
  }
  for (int i = 0; i < packet_count; ++i) {
    if (packets[i].type == 'i') {
      delete[] (int*)packets[i].payload;
    } else {
      delete[] (char*)packets[i].payload;
    }
  }
  delete[] packets;
  for (int z = 0; z < layers; ++z) {
    for (int y = 0; y < rows; ++y) {
      delete[] map[z][y];
    }
    delete[] map[z];
    delete[] widths[z];
  }
  delete[] map;
  delete[] widths;
}
