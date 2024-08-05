#include <raylib.h>
#include <a.h>
#include <string>

void StartWindow(Image logo, char* name){
	init();
	InitWindow(1280, 800, name);
	SetTargetFPS(60);
	SetWindowIcon(logo);
	InitAudioDevice();
	SetExitKey(KEY_NULL);
}