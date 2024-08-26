#include "include/game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

Game::Game() : mSelected(0), mRunning(false) {
  SDL_Init(SDL_INIT_VIDEO);
  mWindow = SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
                             SDL_WINDOW_SHOWN);

  mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

  mBlocks = {{
                 {
                     {0, 0, 0, 0},
                     {1, 0, 0, 0},
                     {1, 1, 0, 0},
                     {0, 0, 0, 0},
                 },
                 SDL_Color{0xFF, 0x00, 0x00, 0xFF},
                 3,
                 GRID_PADDING_X,
                 GRID_PADDING_Y,
                 true,
             },
             {
                 {
                     {0, 0, 0, 0},
                     {0, 1, 0, 0},
                     {1, 0, 0, 0},
                     {0, 1, 0, 0},
                 },
                 SDL_Color{0xFF, 0x00, 0x00, 0xFF},
                 3,
                 GRID_PADDING_X + CELL_SIZE * 4,
                 GRID_PADDING_Y,
                 false,
             }};
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
    update();
    SDL_Delay(100);
  }
}

void Game::input() {

  SDL_Event event;
  /* Poll for events */
  while (SDL_PollEvent(&event)) {

    switch (event.type) {
    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
      case SDLK_q:
        mRunning = false;
        break;
      case SDLK_TAB:
        mBlocks[mSelected].selected = false;
        mSelected = (mSelected + 1) % mBlocks.size();
        mBlocks[mSelected].selected = true;
        break;
      }
      break;

    /* SDL_QUIT event (window close) */
    case SDL_QUIT:
      mRunning = false;
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

  SDL_SetRenderDrawColor(mRenderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderDrawLine(mRenderer, WIDTH / 2, 0, WIDTH / 2, HEIGHT);

  SDL_SetRenderDrawColor(mRenderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderDrawLine(mRenderer, 0, HEIGHT / 2, WIDTH, HEIGHT / 2);

  for (int i = 0; i < GRID_SIZE_X; i++) {
    rect.x = i * CELL_SIZE + GRID_PADDING_X;
    for (int j = 0; j < GRID_SIZE_Y; j++) {
      rect.y = j * CELL_SIZE + GRID_PADDING_Y;
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
  for (auto &block : mBlocks) {
    // block.y += CELL_SIZE;
  }
}
