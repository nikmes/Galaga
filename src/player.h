#pragma once

struct Player {
    float x = 0.0f;
    float y = 0.0f;
    float speed = 300.0f;
    int lives = 3;
    bool invulnerable = false;
    float invulnTime = 0.0f;

    void init(float startX, float startY);
    void update(float dt, float screenW);
    void onHit();
    void respawn(float startX, float startY);
};
