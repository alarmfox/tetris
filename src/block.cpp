#include "include/block.h"

void Block::rotate() {
  bool temp[4][4];
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      temp[j][size - 1 - i] = m[i][j];
    }
  }
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      m[i][j] = temp[i][j];
    }
  }
}
