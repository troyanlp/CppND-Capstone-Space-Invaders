#include "player.h"
#include <iostream>
#include <algorithm>

void Player::Update() {
    if(!isMoving)
        return;

    isMoving = false;
    x_ = x_ + static_cast<float>(direction_);
        
    ClampCoordinates();
}

void Player::Move(Player::Direction direction) {
    isMoving = true;
    direction_ = direction;
}

void Player::EnableShooting() {
    isShooting = true;
}

std::unique_ptr<Bullet> Player::Shoot() {
    if(!isShooting)
        return nullptr;
    
    isShooting = false;

    return std::make_unique<Bullet>(grid_width_, grid_height_, x_ + 0.4f, y_, Bullet::Direction::kUP);
}

void Player::Hurt() {
    lives--;
}

    
bool Player::BeenShot(std::unique_ptr<Bullet> &bullet) {
    if((bullet->x_ >= x_ - 0.1f   &&  bullet->x_ < x_ + 1.1f) &&
        bullet->y_ > grid_height_ - 1.5f) {
        return true;
    }
    return false;
}


        