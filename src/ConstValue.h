#ifndef UNNAMING_GAME_SRC_CONSTVALUE_H_
#define UNNAMING_GAME_SRC_CONSTVALUE_H_
const uint32_t kMapWidth = 32;
const uint32_t kMapHeight = 32;
const uint32_t kMinRoomWidth = 3;
const uint32_t kMinRoomHeight = 3;
const uint32_t kMaxRoomWidth = 8;
const uint32_t kMaxRoomHeight = 8;
enum BlockType {
  kBlockWall,
  kBlockGround,
  kBlockPath,
  kBlockMax
};
#endif  // UNNAMING_GAME_SRC_CONSTVALUE_H_
