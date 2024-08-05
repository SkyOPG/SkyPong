#include <pong.h>

Vector2D LoadGame(Ball& ball, Theme gameTheme, Paddle& player, Paddle& cpu, int& players, int& cpus){
        ball.Update(cpus, players);
        player.Update(ball.y);
        cpu.Update(ball.y);

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            ball.speed_x *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
        {
            ball.speed_x *= -1;
        }

        DrawTable(gameTheme);
        ball.Draw();
        cpu.Draw();
        player.Draw();
        DrawText(TextFormat("%i", cpus), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", players), 3 * screen_width / 4 - 20, 20, 80, WHITE);
        return {
            players,
            cpus
        };
}