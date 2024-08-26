#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include "game.h"
Game::Game() : mSelected(0), mRunning(false) {
  SDL_Init(SDL_INIT_VIDEO);
  mWindow = SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
                             SDL_WINDOW_SHOWN);

  mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

  mBlocks = {
      {
          {
              {1, 0, 0, 0},
              {1, 0, 0, 0},
              {1, 1, 0, 0},
              {0, 0, 0, 0},
          },
          SDL_Color{0xFF, 0x00, 0x00, 0xFF},
          3,
          0,
          0,
          true,
          false,
      },
  };
}

Game::~Game() {
  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);
  SDL_Quit();
}

void Game::start() {
  mRunning = true;
  while (mRunning) {
    draw();
    input();
    SDL_Delay(100);
  }
}

void Game::input() {

  SDL_Event event;
  int x = mBlocks[mSelected].x;
  int size = mBlocks[mSelected].size * CELL_SIZE;
  /* Poll for events */
  while (SDL_PollEvent(&event)) {

    switch (event.type) {
    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
      case SDLK_q:
        stop();
        break;
      case SDLK_TAB:
        get_next_selected();
        break;
      case SDLK_UP:
      case SDLK_r:
        mBlocks[mSelected].rotate();
        break;
      case SDLK_DOWN:
      case SDLK_RETURN:
        update();
        break;
      case SDLK_RIGHT:
      case SDLK_l:
        if ((x + size) < (CELL_SIZE * GRID_SIZE_X) &&
            !mBlocks[mSelected].landed)
          mBlocks[mSelected].x += CELL_SIZE;
        break;
      case SDLK_LEFT:
      case SDLK_h:
        if (x >= CELL_SIZE && !mBlocks[mSelected].landed)
          mBlocks[mSelected].x -= CELL_SIZE;
        break;
      }
      break;

    /* SDL_QUIT event (window close) */
    case SDL_QUIT:
      stop();
      break;

    default:
      break;
    }
  }
}

void Game::draw() {

  // background
  SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0, 0xFF);

  SDL_RenderClear(mRenderer);

  draw_grid();

  draw_blocks();

  SDL_RenderPresent(mRenderer);
}

void Game::draw_grid() {
  SDL_Rect rect;
  rect.w = CELL_SIZE;
  rect.h = CELL_SIZE;

  for (int i = 0; i < GRID_SIZE_X; i++) {
    rect.x = i * CELL_SIZE;
    for (int j = 0; j < GRID_SIZE_Y; j++) {
      rect.y = j * CELL_SIZE;
      SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
      SDL_RenderFillRect(mRenderer, &rect);
      SDL_SetRenderDrawColor(mRenderer, 0xA0, 0xA0, 0xA0, 0xFF);
      SDL_RenderDrawRect(mRenderer, &rect);
    }
  }
}

void Game::draw_blocks() {

  SDL_Rect rect;
  rect.h = rect.w = CELL_SIZE;

  for (auto &block : mBlocks) {
    for (int i = 0; i < block.size; ++i) {
      for (int j = 0; j < block.size; ++j) {
        if (block.m[i][j]) {
          rect.x = block.x + j * CELL_SIZE;
          rect.y = block.y + i * CELL_SIZE;
          SDL_SetRenderDrawColor(mRenderer, block.color.r, block.color.g,
                                 block.color.b, block.color.a);
          SDL_RenderFillRect(mRenderer, &rect);
          if (block.selected) {
            SDL_SetRenderDrawColor(mRenderer, 0x00, 0xFF, 0x00, 0xFF);
            SDL_RenderDrawRect(mRenderer, &rect);
          }
        }
      }
    }
  }
}

void Game::update() {
  int size;
  for (auto &block : mBlocks) {
    size = block.size * CELL_SIZE;
    if ((block.y + size) < (CELL_SIZE * GRID_SIZE_Y))
      block.y += CELL_SIZE;
    if ((block.y + size) >= (CELL_SIZE * GRID_SIZE_Y) && !block.landed) {
      block.landed = true;
      get_next_selected();
    }
  }
}

void Game::get_next_selected() {
  mBlocks[mSelected].selected = false;
  bool found = false;
  for (size_t i = 0; i < mBlocks.size(); ++i) {
    if (!mBlocks[i].landed && i != mSelected && !mBlocks[mSelected].selected) {
      mSelected = i;
      mBlocks[i].selected = true;
    }
  }
  if (!found) {
    mBlocks.push_back({
        {
            {1, 0, 1, 0},
            {1, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0},
        },
        SDL_Color{0xfa, 0xaf, 0x00, 0xff},
        3,
        0,
        0,
        true,
        false,
    });
    mSelected = mBlocks.size() - 1;
  }
}
