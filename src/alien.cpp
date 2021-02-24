#include "alien.h"
#include <iostream>
#include <memory>

bool Alien::changeDirection(false);
double Alien::shooting_probability(3);
double Alien::speed(0.04);
Alien::DirectionX Alien::directionX(DirectionX::kLeft);
Alien::DirectionY Alien::directionY(DirectionY::kNone);

std::random_device Alien::device;
std::mt19937 Alien::generator(device());
std::uniform_int_distribution<int> Alien::distribution(0, 8000);

void Alien::Update() {
    float offset_x = static_cast<float>(directionX) * speed;
    x_ = x_ + offset_x;
    y_ = y_ + static_cast<float>(directionY)*2;

    ClampCoordinates();

    if(x_ < speed || x_ == grid_width_ - 1 || directionY == DirectionY::kDown) {
        changeDirection = true;
    }
}

std::unique_ptr<Bullet> Alien::Shoot() {
    if(!canShoot)
        return nullptr;

    int random_number = GenerateRandom();


    if(random_number < shooting_probability) {
        return std::make_unique<Bullet>(grid_width_, grid_height_, x_ + 0.4f, y_, Bullet::Direction::kDown);
    }

    return nullptr;
}

//this method returns true if aliens changed direction to go vertical again
//we need this info to know when to add new aliens to the game

bool Alien::ChangeDirection() {
    if(!changeDirection)
        return false;

    changeDirection = false;

    if(directionY == DirectionY::kDown) {
        directionY = DirectionY::kNone;
        directionX = DirectionX::kLeft;

        IncreaseLevel();
        return true;
    }

    switch(directionX) {
        case DirectionX::kLeft:
            directionX = DirectionX::kRight;
            break;
        case DirectionX::kRight:
            directionY = DirectionY::kDown;
            directionX = DirectionX::kNone;
            return false;
    }
    return false;
}

    
bool Alien::BeenShot(std::unique_ptr<Bullet> &bullet) {

    if((bullet->x_ >= x_ - 0.1f   &&  bullet->x_ < x_ + 1.1f) &&
        bullet->y_ < y_ + 0.9f) {

        return true;
    }
    return false;
}

bool Alien::ReachedPlayer() {
    return y_ > grid_height_ - 2;
}

void Alien::IncreaseLevel() {
    speed += 0.001;
    shooting_probability++;
}

int Alien::GenerateRandom() {
    return distribution(generator);
}