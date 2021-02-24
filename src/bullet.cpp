#include "bullet.h"
#include <iostream>

void Bullet::Update() {
    y_ = y_ + static_cast<float>(direction_) * speed;
}

bool Bullet::OutOfScreen() {
    if( direction_ == Direction::kDown && y_ >= grid_height_)
        return true;

    if( direction_ == Direction::kUP && y_ < 0.0)
        return true;

    return false;
}

bool Bullet::CollisionDetected(Bullet &bullet) {
    if(abs(x_ - bullet.x_ ) < 0.13 && abs(y_ - bullet.y_ ) < 0.6)
        return true;

    return false; 
}