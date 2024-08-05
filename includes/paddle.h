#pragma once
#include <raylib.h>

class Paddle {

protected:
    void LimitMovement();

public:
    float x, y;
    float width, height;
    int speed;
    bool automatic;
    int player;

    void Draw();
    void Update(int ball_y);
};