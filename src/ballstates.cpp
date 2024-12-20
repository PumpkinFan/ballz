#include "Ball.h"

// Functions to create different starting configurations of balls

std::vector<Ball> overlapAfterCollisionTest() {
    // State with two balls facing directly at each other
    // Used to test when two balls remain overlap after resolving a
    int radius1 = 40;
    Vector2 position1 = { GetScreenWidth()/2.0f - radius1, GetScreenHeight()/2.0f };
    Vector2 initialVelocity1 = { 1.0f, 0.0f };
    Ball ball1 = { position1, initialVelocity1 };

    Vector2 position2 = { ball1.position.x +  1.0f * ball1.radius, ball1.position.y };
    Vector2 initialVelocity2 = { -1.0f, 0.0f };
    Ball ball2 = { position2, initialVelocity2 };

    std::vector<Ball> startingState = { ball1, ball2 };
    return startingState;
};

std::vector<Ball> threeBallsBouncing() {
    Vector2 ballSpeed1 = { 4.0f, -6.0f };
    Vector2 ballSpeed2 = { 10.0f, 4.0f };

    Ball ball1;
    ball1.position = { GetScreenWidth()/4.0f, GetScreenHeight()/4.0f};
    ball1.pastPosition = Vector2Subtract(ball1.position, Vector2Scale(ballSpeed1, DT));

    Ball ball2;
    ball2.position = { GetScreenWidth()/4.0f, 3.0f*GetScreenHeight() / 4.0f };
    ball2.pastPosition = Vector2Subtract(ball2.position, Vector2Scale(ballSpeed2, DT));
    ball2.color = GREEN;

    Ball ball3;
    ball3.position = { GetScreenWidth()/7.0f, GetScreenHeight()/7.0f };
    ball3.pastPosition = ball3.position;
    ball3.color = ORANGE;
    ball3.mass = 10;

    std::vector<Ball> startingState = { ball1, ball2, ball3 };
    return startingState;
}