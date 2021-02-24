#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : player(static_cast<int>(grid_width), static_cast<int>(grid_height)),
      engine(dev()),
      uniform_bool_distribution(0,2),
      uniform_int_16(0,16),
      grid_width(grid_width),
      grid_height(grid_height)
{
  //create aliens
  int num_rows = 3;
  int num_columns = 6;

  AddNewAliens(num_rows, num_columns);
}
  

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;

  while (running) {
    frame_start = SDL_GetTicks();

    controller.HandleInput(running, player);
    Update();
    renderer.Render(player, aliens, alien_bullets, player_bullets);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, player.lives);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update() {
  std::unique_ptr<Bullet> new_bullet = player.Shoot();
  if(new_bullet != nullptr) {
    player_bullets.push_back(std::move(new_bullet));
  }

  for(auto &alien : aliens){
    std::unique_ptr<Bullet> new_bullet = alien.Shoot();
    if(new_bullet != nullptr) {
      alien_bullets.push_back(std::move(new_bullet));
    }
  }

  CheckForCollision();

  player.Update();

  for(auto &alien : aliens) {
    alien.Update();
  }

  for(auto &bullet : alien_bullets) {
    bullet->Update();
  }

  for(auto &bullet : player_bullets) {
    bullet->Update();
  }

  RemoveUnusedBullets(alien_bullets);
  RemoveUnusedBullets(player_bullets);

  if(Alien::ChangeDirection() || ZeroAliens()) AddNewAliens(1, uniform_int_16(engine));

  if(TerminateGame()) running = false;
}

int Game::GetScore() const { return score; }


void Game::PlayerCollisionCheck() {
  for(auto it = alien_bullets.begin(); it != alien_bullets.end(); ) {
    if(player.BeenShot(*it) ) {
      player.Hurt();
      alien_bullets.erase(it++);
    } else {
      it++;
    }
  }
}
  
void Game::AlienCollisionCheck() {
  for(auto i = aliens.begin(); i != aliens.end();) {
    auto &alien = *i;
    for(auto it = player_bullets.begin(); it != player_bullets.end();) {
      if(alien.BeenShot(*it) ) {
        aliens.erase(i++);
        player_bullets.erase(it++);
        score++;
        break;
      } else {
        it++;
      }
    }
    i++;
  }
}

void Game::BulletCollisionCheck() {
  for(auto i = player_bullets.begin(); i != player_bullets.end();) {
    for(auto j = alien_bullets.begin(); j != alien_bullets.end(); ) {
      auto & p_bullet = *i->get();
      auto & a_bullet = *j->get();
      if( p_bullet.CollisionDetected(a_bullet) ){
        player_bullets.erase(i++);
        alien_bullets.erase(j++);
        break;
      } else {
        j++;
      }
    }
    i++;
  }
}

void Game::CheckForCollision() {
  PlayerCollisionCheck();
  AlienCollisionCheck();
  BulletCollisionCheck();
}

void Game::RemoveUnusedBullets(std::list<std::unique_ptr<Bullet>> &bullets) {
  for(auto it = bullets.begin(); it != bullets.end(); ) {
    if(it->get()->OutOfScreen()) {
      bullets.erase(it++);
    } else {
      it++;
    }
  }
}

bool Game::TerminateGame() {
  if(!player.IsAlive())
    return true;

  for(auto &alien : aliens) {
    if(alien.ReachedPlayer())
      return true;
  }
  
  return false;
}

void Game::AddNewAliens(int num_rows, int num_columns) {
  int offset_range = grid_width - (num_columns + num_columns - 1);
  std::uniform_int_distribution<int> uniform(0, offset_range);
  int offset_x = uniform(engine);
  for(int i = 0; i < num_columns; i++) {
    int x = offset_x + 2 * i + 1;
    for(int j = 0; j < num_rows; j++) {
      int y = 2 * j + 1;
      bool able_to_shoot = uniform_bool_distribution(engine);
      aliens.emplace_back(Alien(grid_width, grid_height, x, y,  able_to_shoot));
    }
  }
}

bool Game::ZeroAliens() {
  return aliens.size() == 0;
}