#include <raylib.h>
#include <vector>
#include <cmath>

struct Player {
    Vector2 pos;
    float speed = 300.0f;
    int lives = 3;
};

struct Bullet {
    Vector2 pos;
    Vector2 vel;
    bool active = true;
};

struct Enemy {
    Vector2 pos;
    Vector2 home;
    bool alive = true;
    bool diving = false;
    float t = 0.0f;
};

int main() {
    const int screenW = 800;
    const int screenH = 600;
    InitWindow(screenW, screenH, "SpaceInvaders - Galaga Prototype");
    SetTargetFPS(60);

    #include "player.h"
    Player player;
    player.init(screenW/2.0f, screenH - 40.0f);

    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;

    // create formation
    int rows = 3;
    int cols = 8;
    float startX = 100;
    float startY = 80;
    float spacingX = 70;
    float spacingY = 50;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            Enemy e;
            e.home = { startX + c*spacingX, startY + r*spacingY };
            e.pos = e.home;
            enemies.push_back(e);
        }
    }

    int score = 0;
    float timeSinceLastDive = 0.0f;
    float diveInterval = 2.0f;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // input
    float move = 0.0f;
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) move -= 1.0f;
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) move += 1.0f;
    player.x += move * player.speed * dt;
    player.update(dt, (float)screenW);

        if (IsKeyPressed(KEY_SPACE)) {
            Bullet b;
            b.pos = { player.x, player.y - 20 };
            b.vel = { 0, -600 };
            bullets.push_back(b);
        }

        // enemies: occasionally pick one to dive
        timeSinceLastDive += dt;
        if (timeSinceLastDive > diveInterval) {
            timeSinceLastDive = 0.0f;
            // pick a random alive enemy
            int idx = -1;
            for (int i = 0; i < (int)enemies.size(); ++i) if (enemies[i].alive && !enemies[i].diving) { idx = i; break; }
            if (idx >= 0) {
                enemies[idx].diving = true;
                enemies[idx].t = 0.0f;
            }
        }

        // update enemies
        for (auto &e : enemies) {
            if (!e.alive) continue;
            if (e.diving) {
                e.t += dt;
                // dive path: a simple bezier-ish swoop
                float T = e.t;
                Vector2 a = e.home;
                Vector2 b = { e.home.x, e.home.y + 150 };
                Vector2 c = { player.pos.x, player.pos.y - 200 };
                // quadratic bezier
                float u = T / 1.5f; if (u > 1) u = 1;
                float iu = 1 - u;
                e.pos = { iu*iu*a.x + 2*iu*u*b.x + u*u*c.x, iu*iu*a.y + 2*iu*u*b.y + u*u*c.y };
                if (u >= 1.0f) { e.diving = false; e.pos = e.home; }
            } else {
                // small bob to show movement
                e.pos.x = e.home.x + sin((GetTime() + e.home.x)*0.5f) * 8.0f;
            }
        }

        // update bullets
        for (auto &b : bullets) {
            if (!b.active) continue;
            b.pos.x += b.vel.x * dt;
            b.pos.y += b.vel.y * dt;
            if (b.pos.y < -10) b.active = false;
            // check collisions
            for (auto &e : enemies) {
                if (!e.alive) continue;
                if (CheckCollisionPointCircle(b.pos, e.pos, 16)) {
                    e.alive = false;
                    b.active = false;
                    score += 100;
                    break;
                }
            }
        }

        // remove inactive bullets
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet &b){ return !b.active; }), bullets.end());

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Galaga-like Prototype", 10, 10, 20, RAYWHITE);
        DrawText(TextFormat("Score: %d", score), 10, 40, 18, RAYWHITE);

        // draw player
        DrawTriangle({player.pos.x, player.pos.y - 12}, {player.pos.x - 10, player.pos.y + 12}, {player.pos.x + 10, player.pos.y + 12}, SKYBLUE);

        // draw bullets
        for (auto &b : bullets) DrawCircleV(b.pos, 4, YELLOW);

        // draw enemies
        for (auto &e : enemies) {
            if (!e.alive) continue;
            DrawCircleV(e.pos, 14, RED);
            DrawCircleLines((int)e.pos.x, (int)e.pos.y, 14, BLACK);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
