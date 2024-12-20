#include "Ball.h"

// Functions to create different starting configurations of balls

std::array<Ball, 2> overlapAfterCollisionTest() {
    Ball ball1;
    ball1.position = { GetScreenWidth()/2.0f - ball1.radius, GetScreenHeight()/2.0f };
    ball1.initialVelocity = { 1.0f, 0.0f };

    Ball ball2;
    ball2.position = { ball1.position.x + ball1.radius, ball1.position.y };
    ball2.initialVelocity = { -1.0f, 0.0f };

    std::array<Ball, 2> startingState = { ball1, ball2 };
    return startingState;
};