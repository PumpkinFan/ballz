#ifndef BALL_H
#define BALL_H

#include "raylib.h"
#include "raymath.h"
#include <vector>

const float DT = 1;

struct Ball {
    Vector2 position;
    Vector2 initialVelocity;
    Vector2 pastPosition = Vector2Subtract(position, Vector2Scale(initialVelocity, DT));
    Vector2 acceleration = { 0.0f, 0.0f };
    int radius = 40;
    int mass = 1;
    Color color = BLUE;

    Vector2 getVelocity();
    void handleWallCollisions();
    void updatePostion();
    void draw();
};

void handleBallCollision(Ball &ball1, Ball &ball2);

std::vector<Ball> overlapAfterCollisionTest();
std::vector<Ball> threeBallsBouncing();

#endif // BALL_H
