#include <pong.h>

Paddle makePaddle(bool automatic, int pllayer){
	Paddle player; // main player

	player.width = 25;
	player.height = 120;
	player.x = pllayer == 1 ? screen_width - player.width - 10 : 10;
	player.y = screen_height / 2 - player.height / 2;
	player.speed = 6;
	player.automatic = automatic;
	return player;
}