#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

class Bullet : public Entity{
public:
    enum class Direction{
        kUP = -1,
        kDown = 1
    };

    Bullet(int grid_width, int grid_height, float x, float y, Direction direction) : 
        Entity(grid_width, grid_height, x, y), 
        speed(0.5), 
        direction_(direction)
    {}
    
    void Update();
    bool OutOfScreen();
    bool CollisionDetected(Bullet &bullet);

private:
    float speed;
    Direction direction_;
};

#endif