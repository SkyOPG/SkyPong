#include <raylib.h>

extern const float titleFontSize;
extern const float rotationSpeed;
extern const float toggleSize;
extern float textx;
extern float texty;
extern float textsize;
extern bool playButtonPressed;
extern bool settingsButtonPressed;
extern bool editorButtonPressed;
void gamescreen();
void titlescreen_code();
void gamescreen_code();
void vscpu_code();
void pause_code();
void vsplayer_code();
void settings();
void pause();
void title();
void vscpu();
void vsplayer();

typedef enum GameScreen { TITLE, GAMEVSCPU, GAME, GAMEVSPLAYER, PAUSE, SETTINGS, SECRET, NAN } GameScreen;
typedef enum RPCAt { HOME, PAUSED, INGAME, EDITORS, SETTING, NO } RPCAt;
typedef enum matchMode { VSCPU, VSPLAYER, VSPLAYERONLINE, NONE } matchMode;
extern GameScreen pausedFrom;
extern GameScreen windowState;
