#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Space Invaders Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Player const &player,
              std::list<Alien> const &aliens,
              std::list<std::unique_ptr<Bullet>> const &alien_bullets,
              std::list<std::unique_ptr<Bullet>> const &player_bullets) const {

  int block_w = screen_width / grid_width;
  int block_h = screen_height / grid_height;

  SDL_Rect block;
  block.w = block_w;
  block.h = block_h;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render player
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0xFF, 0xFF);
  block.x = player.x_ * block.w;
  block.y = player.y_ * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  //render aliens
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0xFF);
  block.w = block_w;
  block.h = block_h;

  for(auto &alien : aliens) {
    block.x = alien.x_ * block.w;
    block.y = alien.y_ * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render player bullets
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  block.w = block_w / 5;
  block.h = block_h / 2;
  for (auto &bullet : player_bullets) {
    block.x = bullet->x_ * block_w;
    block.y = bullet->y_ * block_h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render alien bullets
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  block.w = block_w / 5;
  block.h = block_h / 2;
  for (auto &bullet : alien_bullets) {
    block.x = bullet->x_ * block_w;
    block.y = bullet->y_ * block_h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  SDL_RenderPresent(sdl_renderer);
  
}

void Renderer::UpdateWindowTitle(int score, int fps, int lives) const {
  std::string title{"Score: " + std::to_string(score) + " FPS: " + std::to_string(fps) + " LIVES: " + std::to_string(lives)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
