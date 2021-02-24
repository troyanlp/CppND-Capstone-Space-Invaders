#ifndef ENTITY_H
#define ENTITY_H

#include <algorithm>
#include <iostream>

class Entity {
public:
    Entity(int grid_width, int grid_height, float x, float y) : 
            grid_width_(grid_width), 
            grid_height_(grid_height),
            x_(x),
            y_(y)
    {}

    float x_;
    float y_;

    virtual void Update() = 0;

protected:
    float grid_width_;
    float grid_height_;

    bool ClampCoordinates() {
        x_ = std::clamp(x_, 0.0f, grid_width_ - 1.0f);
        y_ = std::clamp(y_, 0.0f, grid_height_ - 1.0f);
    }
};

#endif