#include "Ball.h"

extern const float DT; // Defined in Ball.h


Vector2 Ball::getVelocity() {
    return Vector2Subtract(position, pastPosition);
}


void Ball::handleWallCollisions() {
    Vector2 velocity = getVelocity();
    if ((position.x >= (GetScreenWidth() - radius)) || (position.x <= radius)) {
        pastPosition.x = position.x + velocity.x * DT;
    }
    if ((position.y >= (GetScreenHeight() - radius)) || (position.y <= radius)) {
        pastPosition.y = position.y + velocity.y * DT;
    }
}


void Ball::updatePostion() {
    handleWallCollisions();
    Vector2 velocity = getVelocity();
    pastPosition = position;
    position = Vector2Add(Vector2Add(position, Vector2Scale(velocity, DT)), Vector2Scale(acceleration, DT * DT));
}


void Ball::draw() {
    DrawCircleV(position, (float)radius, color);
    DrawCircleV(pastPosition, 3.0f, RED);
}


void handleBallCollision(Ball &ball1, Ball &ball2) {
    float distance = Vector2Distance(ball1.position, ball2.position);
    if (distance > (ball1.radius + ball2.radius)) {
        return; // No collision
    }
    Vector2 velocity1 = ball1.getVelocity();
    Vector2 velocity2 = ball2.getVelocity();

    // Find unit normal and unit tangent
    Vector2 normalVector = Vector2Subtract(ball2.position, ball1.position);
    Vector2 unitNormal = Vector2Scale(normalVector, 1.0f / distance);
    Vector2 unitTangent = { -unitNormal.y, unitNormal.x };

    // Project velocities onto normal and tangent lines
    float normalVelocity1 = Vector2DotProduct(unitNormal, velocity1);
    float normalVelocity2 = Vector2DotProduct(unitNormal, velocity2);
    float tangentVelocity1 = Vector2DotProduct(unitTangent, velocity1);
    float tangentVelocity2 = Vector2DotProduct(unitTangent, velocity2);

    // Perform 1D elastic collision on normal components
    float massSum = ball1.mass + ball2.mass;
    float newNormalVelocity1 = (normalVelocity1 * (ball1.mass - ball2.mass) + 2 * ball2.mass * normalVelocity2) / massSum;
    float newNormalVelocity2 = (normalVelocity2 * (ball2.mass - ball1.mass) + 2 * ball1.mass * normalVelocity1) / massSum;

    // Create new velocities by adding the new normal and tangent components
    Vector2 newVelocity1 = Vector2Add(Vector2Scale(unitNormal, newNormalVelocity1), Vector2Scale(unitTangent, tangentVelocity1));
    Vector2 newVelocity2 = Vector2Add(Vector2Scale(unitNormal, newNormalVelocity2), Vector2Scale(unitTangent, tangentVelocity2));

    // Resolve any overlap after collisions
    float radiusSum = (float)ball1.radius + (float)ball2.radius;
    float distanceAfterCollision = Vector2Distance(Vector2Add(ball1.position, newVelocity1), Vector2Add(ball2.position, newVelocity2));
    float overlapAfterCollision = radiusSum - distanceAfterCollision;
    if (overlapAfterCollision > 0) {
        ball1.position = Vector2Add(ball1.position, Vector2Scale(unitNormal, -1 * overlapAfterCollision * (ball1.radius / radiusSum)));
        ball2.position = Vector2Add(ball2.position, Vector2Scale(unitNormal, overlapAfterCollision * (ball2.radius / radiusSum)));
    }

    ball1.pastPosition = Vector2Subtract(ball1.position, Vector2Scale(newVelocity1, DT));
    ball2.pastPosition = Vector2Subtract(ball2.position, Vector2Scale(newVelocity2, DT));
}