#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "player.h"
#include "bullet.h"
#include "alien.h"
#include <list>
#include <memory>

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);

  int GetScore() const;

 private:
  Player player;
  std::list<Alien> aliens;
  std::list<std::unique_ptr<Bullet>> alien_bullets;
  std::list<std::unique_ptr<Bullet>> player_bullets;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> uniform_bool_distribution;
  std::uniform_int_distribution<int> uniform_int_16;
  
  int grid_width;
  int grid_height;

  int score{0};
  bool running{true};

  void Update();
  void RemoveUnusedBullets(std::list<std::unique_ptr<Bullet>> &bullets);
  bool TerminateGame();
  void AddNewAliens(int num_rows, int num_columns);
  bool ZeroAliens();

  void CheckForCollision();
  void PlayerCollisionCheck();
  void AlienCollisionCheck();
  void BulletCollisionCheck();

};

#endif