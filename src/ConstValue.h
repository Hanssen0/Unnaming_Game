#ifndef UNNAMING_CONSTVALUE_H_
#define UNNAMING_CONSTVALUE_H_
const int kMapWidth = 32;
const int kMapHeight = 32;
const int kMinRoomWidth = 3;
const int kMinRoomHeight = 3;
const int kMaxRoomWidth = 8;
const int kMaxRoomHeight = 8;
enum BlockType {
  kBlockWall,
  kBlockGround,
  kBlockPath,
  kBlockMax
};
#endif
