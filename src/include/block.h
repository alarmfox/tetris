#include <SDL2/SDL_pixels.h>
struct Block {
  bool m[4][4];
  SDL_Color color;
  int size;
  int x, y;
  bool selected;
};
