#pragma once
#include <raylib.h>
#include <ball.h>
#include <paddle.h>

const float screen_width = 1280;
const float screen_height = 800;

typedef enum GameScreen { LOADING, TITLE, GAMEVSCPU, GAME, GAMEVSPLAYER, PAUSE, SETTINGS, SECRET, TIMED, NAN } GameScreen;
typedef enum RPCAt { HOME, PAUSED, INGAME, EDITORS, SETTING, TIME, NO } RPCAt;
typedef enum matchMode { VSCPU, VSPLAYER, VSPLAYERONLINE, NONE } matchMode;
typedef enum Theme { NORMAL, RETRO, PARTY } Theme;

const float buttonSize = 200, buttonSpacing = 40, titleFontSize = 60, rotationSpeed = 2.0f;

struct Vector2D {
	int x;
	int y;
};

struct ButtonPressed {
	bool play;
	bool settings;
	bool editor;
	bool toggle1;
	bool toggle2;
	bool toggle3;
	bool rec1;
	bool rec2;
};

void DrawTable(Theme theme);
void LoadTimedScreen(Ball timeBall, Paddle cpu, Paddle player, Theme gameTheme, int players, int cpus);
Vector2D LoadGame(Ball& ball, Theme gameTheme, Paddle& player, Paddle& cpu, int &players, int &cpus);
Ball makeBall();
void GameModeChooser(Theme gameTheme);
Paddle makePaddle(bool automatic, int pllayer);
ButtonPressed checkCollisions(Vector2 mousePosition);
void StartWindow(Image logo, char* name);
void SetTheme(Theme &gameTheme, char* &Themetext);
void KeyEvents(
	GameScreen &windowState, 
	RPCAt& RPC, 
	ButtonPressed isPressed, 
	bool& initted, 
	matchMode& match, 
	GameScreen& pausedFrom, 
	float& voice,
	Sound sretro,
	Theme& gameTheme,
	int& frames,
	Color& color,
	Vector2D& position,
	bool& build,
	int& numbah
);
void LoadingScreen(Texture2D logo, int x, int y, Color& color);