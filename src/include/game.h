#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <vector>

#include "block.h"

class Game {
public:
  Game();
  ~Game();

  void start();

private:
  void input();
  void draw();
  void update();
  void get_next_selected();
  inline void stop() { mRunning = false; }

private:
  std::vector<Block> mBlocks;
  size_t mSelected;

private:
  static const int CELL_SIZE = 35;
  static const int WIDTH = 640;
  static const int HEIGHT = 480;
  static const int GRID_SIZE_X = WIDTH / CELL_SIZE - 5;
  static const int GRID_SIZE_Y = HEIGHT / CELL_SIZE;
  static const int GRID_PADDING_X = (WIDTH - (GRID_SIZE_X * CELL_SIZE)) / 2;
  static const int GRID_PADDING_Y = (HEIGHT - (GRID_SIZE_Y * CELL_SIZE)) / 2;

  constexpr static const char APP_NAME[] = "Tetris";
  bool mRunning;

  SDL_Window *mWindow = NULL;
  SDL_Renderer *mRenderer = NULL;

private:
  void draw_grid();
  void draw_blocks();
};
