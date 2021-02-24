#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "shooter.h"

class Player : public Shooter{
public:
    enum class Direction { 
        kLeft = -1, 
        kRight = 1 
    };

    Player(int grid_width, int grid_height) : 
        Shooter(grid_width, grid_height, grid_width / 2, grid_height - 1),
        lives(5),
        isMoving(false), 
        direction_(Direction::kLeft),
        isShooting(false)
    {}

    int lives;

    void Update() override;
    void Move(Player::Direction direction);
    void EnableShooting();
    void Hurt();
    bool IsAlive() { return lives > 0; }

    std::unique_ptr<Bullet> Shoot() override;
    
    bool BeenShot(std::unique_ptr<Bullet> &bullet) override;
        
private:
    bool isMoving;
    Direction direction_;
    bool isShooting;

};

#endif