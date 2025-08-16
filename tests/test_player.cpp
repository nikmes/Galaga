#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../src/player.h"

TEST_CASE("Player init and clamping") {
    Player p;
    p.init(100.0f, 200.0f);
    REQUIRE(p.x == 100.0f);
    REQUIRE(p.y == 200.0f);
    p.x = -50.0f;
    p.update(0.016f, 800.0f);
    REQUIRE(p.x == 20.0f);
    p.x = 1000.0f;
    p.update(0.016f, 800.0f);
    REQUIRE(p.x == 800.0f - 20.0f);
}

TEST_CASE("Player invulnerability and lives") {
    Player p;
    p.init(100.0f, 200.0f);
    int startLives = p.lives;
    p.onHit();
    REQUIRE(p.lives == startLives - 1);
    REQUIRE(p.invulnerable == true);
    // hitting while invulnerable should not reduce lives
    p.onHit();
    REQUIRE(p.lives == startLives - 1);
    // simulate time passing
    p.update(2.1f, 800.0f);
    REQUIRE(p.invulnerable == false);
}

TEST_CASE("Respawn sets invulnerability") {
    Player p;
    p.init(400.0f, 300.0f);
    p.respawn(400.0f, 300.0f);
    REQUIRE(p.invulnerable == true);
}
