#pragma once

#include "entity.h"
#include "bullet.h"
#include "shooter.h"
#include "stdlib.h"
#include <random>

class Alien : public Shooter{
public:
    enum class DirectionX {
        kLeft = -1,
        kNone = 0,
        kRight = 1
    };
    
    enum class DirectionY {
        kNone = 0,
        kDown = 1
    };

    Alien(int grid_width, int grid_height, int x, int y, bool shoot = false) : 
        Shooter(grid_width, grid_height, x, y), 
        canShoot(shoot)
    {}

    bool canShoot;
    void Update();    
    bool BeenShot(std::unique_ptr<Bullet> &bullet) override;
    bool ReachedPlayer();
    
    std::unique_ptr<Bullet> Shoot() override;

    static bool ChangeDirection();
    static void IncreaseLevel();

private:
    static bool changeDirection;
    static double shooting_probability;
    static double speed;
    static DirectionX directionX;
    static DirectionY directionY;
    static int GenerateRandom();
    
    static std::random_device device;
    static std::mt19937 generator;
    static std::uniform_int_distribution<int> distribution;
};