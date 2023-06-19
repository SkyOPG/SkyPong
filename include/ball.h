#include <raylib.h>
#include <iostream>
#include <aaa.h>

Color skybloo = Color{ 135, 206, 235, 255 };
Color gren = Color{38, 185, 154, 255};
Color Dark_gren = Color{20, 160, 133, 255};
Color Light_gren = Color{129, 204, 184, 255};
Color yelow = Color{243, 213, 91, 255};
Color bloo = Color{30, 139, 159, 255};

int cpu_score = 0;
int player_score = 0;

class Ball {
public:
      float x = screen_width /2, y = screen_height/2;
    int speed_x = 7, speed_y = 7;
    int radius = 20;

    void Draw()
    {
        DrawCircle(x, y, radius, yelow);
    }

    void Update()
    {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth()) // Cpu wins
        {
            cpu_score++;
            ResetBall();
        }

        if (x - radius <= 0)
        {
            player_score++;
            ResetBall();
        }
    }

    void ResetBall()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speed_choices[2] = {-1, 1};
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
};
class MenuBall : public Ball {
public:
    int radius = 20;
    float x = screen_width/2;
    float y = screen_height/2;
    int speed_x = 7;
    int speed_y = 7;

    void Draw()
    {
        DrawCircle(x, y, radius, yelow);
    }

    void Update()
    {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth()) {
            ResetBall();
        }

        if (x - radius <= 0)
        {
            ResetBall();
        }
    }

    void ResetBall()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speed_choices[2] = {-1, 1};
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
};

class Text : public Ball
{
public:
    float x = 460;
    float y = 340;
    int size = 60;
    int size2 = 40;
    int speed_x = 7;
    int speed_y = 7;

    void Draw() {
        DrawText("SkyPong", x, y, size, bloo);
        DrawText("Play - Space", x + 100, y + 100, size2, LIGHTGRAY);
        DrawText("Settings - S", x, y + 200, size2, LIGHTGRAY);
        DrawText("Quit - Q", x + 100, y + 300, size2, LIGHTGRAY);
    }

    void Update()
    {
        
    }

    void ResetBall()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speed_choices[2] = {-1, 1};
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
};

class Paddle {

protected:
    float width = 25;
    float height = 120;
    float x = screen_width-width-10;
    float y = screen_height/2-height/2;
    int speed = 6;
    float LimitMovement(float ye,float heights)
    {
        if (ye <= 0)
        {
            ye = 0;
        }
        if (ye + heights >= GetScreenHeight())
        {
            ye = GetScreenHeight() - heights;
        }
        return ye;
    }

public:
    void Draw()
    {
        
    }

    void Update()
    {
    }
};

class APaddle : public Paddle  {
public:
    float width = 25;
    float height = 120;
    float x = screen_width-width-10;
    float y = screen_height/2-height/2;
    int speed = 6;
    void Draw() {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }
    void Update() {
        if (IsKeyDown(KEY_UP))
        {
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y = y + speed;
        }
        y = LimitMovement(y, height);
    }
};

class CpuPaddle : public Paddle
{
public:
    float width = 25;
    float height = 120;
    float x = width-10;
    float y = screen_height/2-height/2;
    int speed = 6;
    void Draw() {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }
    void Update(int ball_y) {
        if (y + height / 2 > ball_y)
        {
            y = y - speed;
        }
        if (y + height / 2 <= ball_y)
        {
            y = y + speed;
        }
        y = LimitMovement(y, height);
    }
};

class MenuPaddle : public Paddle
{
public:
float width = 25;
        float height = 120;
        float x = screen_width-width-10;
        float y = screen_height/2-height/2;
        int speed = 6;
void Draw() {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }
    void Update(int ball_y)
    {
        
        if (y + height / 2 > ball_y)
        {
            y = y - speed;
        }
        if (y + height / 2 <= ball_y)
        {
            y = y + speed;
        }
        y = LimitMovement(y, height);
    }
};
class secondMenuPaddle : public Paddle
{
public:
    float width = 25;
        float height = 120;
        float x = width-10;
        float y = screen_height/2-height/2;
        int speed = 6;
        void Draw() {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }
    void Update(int ball_y)
    {
        if (y + height / 2 > ball_y)
        {
            y = y - speed;
        }
        if (y + height / 2 <= ball_y)
        {
            y = y + speed;
        }
        y = LimitMovement(y, height);
    }
};
class Player2Paddle : public Paddle {
    public: 
    float width = 25;
    float height = 120;
    float x = width-10;
    float y = screen_height/2-height/2;
    int speed = 6;
    void Draw() {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }
    void Update()
    {
        if (IsKeyDown(KEY_W))
        {
            y = y - speed;
        }
        if (IsKeyDown(KEY_S))
        {
            y = y + speed;
        }
        y = LimitMovement(y, height);
    }
};