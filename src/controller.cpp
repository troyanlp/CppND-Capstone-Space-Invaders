#include "controller.h"
#include <iostream>
#include "SDL.h"

void Controller::HandleInput(bool &running, Player &player) const {SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_LEFT:
          player.Move(Player::Direction::kLeft);
          break;
        case SDLK_RIGHT:
          player.Move(Player::Direction::kRight);
          break;
        case SDLK_SPACE:
          player.EnableShooting();
          break;
        case SDLK_ESCAPE:
          running = false;
          break;
      } 
    }
  }
}