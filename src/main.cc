#include "main.h"
int main() {
  GameMap Main_map;
  srand(time(0));
  for (int i = 0; i < kMapWidth; ++i) {
    for (int j = 0; j < kMapHeight; ++j) {
      Main_map.set_data(i, j, rand() % 10000);
    }
  }
  for (int i = 0; i < kMapWidth; ++i) {
    for (int j = 0; j < kMapHeight; ++j) {
      std::cout << Main_map.data(i, j); 
    }
    std::cout << "\n";
  }
  std::cout << std::flush;
  std::cout << "Hello world!";
}
