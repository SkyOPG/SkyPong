#include <ball.h>

void Ball::Draw(){
	DrawCircle(x, y, radius, (Color){243, 213, 91, 255});
}

void Ball::Update(int &cpu_score, int &player_score) {
	std::cout << "Before Update - X: " << x << " Y: " << y << std::endl;
		
	x += speed_x * speed;
	y += speed_y * speed;
    
    std::cout << "After Movement - X: " << x << " Y: " << y << std::endl;

    if (y + radius >= GetScreenHeight() || y - radius <= 0){
            speed_y *= -1;
    }
    if (x + radius >= GetScreenWidth()){
            cpu_score++;
            ResetBall();
    }

    if (x - radius <= 0){
    	player_score++;
        ResetBall();
    }

	if (speed <= 0){
    	ResetBall();
        cpu_score++;
        speed = 1;
    }
}

void Ball::ResetBall(){
    x = GetScreenWidth() / 2;
	y = GetScreenHeight() / 2;

    int speed_choices[2] = {-1, 1};
    speed_x = speed_choices[GetRandomValue(0, 1)] * speed;
    speed_y = speed_choices[GetRandomValue(0, 1)] * speed;
}