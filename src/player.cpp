#include "player.h"

void Player::init(float startX, float startY) {
    x = startX;
    y = startY;
    lives = 3;
    invulnerable = false;
    invulnTime = 0.0f;
}

void Player::update(float dt, float screenW) {
    // movement is expected to be applied externally by changing x before clamping
    if (x < 20.0f) x = 20.0f;
    if (x > screenW - 20.0f) x = screenW - 20.0f;

    if (invulnerable) {
        invulnTime -= dt;
        if (invulnTime <= 0.0f) invulnerable = false;
    }
}

void Player::onHit() {
    if (invulnerable) return;
    lives -= 1;
    invulnerable = true;
    invulnTime = 2.0f; // 2 seconds invulnerability after hit
}

void Player::respawn(float startX, float startY) {
    x = startX;
    y = startY;
    invulnerable = true;
    invulnTime = 2.0f;
}
