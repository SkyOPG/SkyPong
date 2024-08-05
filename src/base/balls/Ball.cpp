#include <ball.h>
#include <common.h>

Ball makeBall(){
	Ball ball;
	ball.radius = 20;
	ball.x = screen_width / 2;
	ball.y = screen_height / 2;
	ball.speed_x = 7;
	ball.speed_y = 7;
	ball.speed = 7;
	return ball;
}