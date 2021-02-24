#ifndef RENDERER_H
#define RENDERER_H

#include <list>
#include "SDL.h"
#include "player.h"
#include "alien.h"
#include "bullet.h"
#include <memory>

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Player const &player,
              std::list<Alien> const &aliens,
              std::list<std::unique_ptr<Bullet>> const &alien_bullets,
              std::list<std::unique_ptr<Bullet>> const &player_bullets
              ) const;
  void UpdateWindowTitle(int score, int fps, int lives) const;

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif