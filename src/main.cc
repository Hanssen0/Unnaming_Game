#include "main.h"
int main() {
  GameMap test_map;
  GameMapBuilder builder;
  builder.CleanMap(&test_map);
  srand(time(0));
  builder.BuildRooms(&test_map);
  test_map.PrintMap();
  std::cout << std::flush;
}
