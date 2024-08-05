#include <paddle.h>

void Paddle::LimitMovement(){
    if (y <= 0){
        y = 0;
	}
    if (y + height >= GetScreenHeight()){
        y = GetScreenHeight() - height;
    }
}

void Paddle::Draw(){
    DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
}

void Paddle::Update(int ball_y){
    if(automatic){
        if (y + height / 2 > ball_y)
            y -= speed;
        if (y + height / 2 <= ball_y)
            y += speed;
        LimitMovement();
    } else {
        if(player == 1 ? IsKeyDown(KEY_UP): IsKeyDown(KEY_W))
            y -= speed;
        if(player == 1 ? IsKeyDown(KEY_DOWN): IsKeyDown(KEY_S))
            y += speed;
        LimitMovement();
    }
}