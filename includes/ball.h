#pragma once
#include <raylib.h>
#include <iostream>

class Ball {
	public:
		float x, y;
		int speed_x, speed_y;
		float speed;
		int radius;
		void Draw();
		void Update(int &cpu_score, int& player_score);
		void ResetBall();
};