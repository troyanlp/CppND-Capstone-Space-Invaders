#ifndef SHOOTER_H
#define SHOOTER_H

#include "bullet.h"
#include "entity.h"
#include <memory>
#include <iostream>

class Shooter : public Entity{
public:
    Shooter(int grid_width, int grid_height, int x, int y) :
        Entity(grid_width, grid_height, x, y)
    {}
    
    virtual std::unique_ptr<Bullet> Shoot() = 0;

    virtual bool BeenShot(std::unique_ptr<Bullet> &bullet) {
        
        if(bullet->x_ == this->x_ && bullet->y_ >= this->y_ - 1) {
            return true;
        }

        return false;
    }
};

#endif