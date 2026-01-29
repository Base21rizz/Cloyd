#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;
    screenPos = {static_cast<float>(winWidth) / 2.0f - scale * (0.5 * width),
                 static_cast<float>(winHeight) / 2.0f - scale * (0.5 * height)};
}

void Character::tick(float deltaTime)
{
    BaseCharacter::tick(deltaTime);
    // Animation Variable
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    if (Vector2Length(direction) != 0.0)
    {

        // Set worldPos += direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));

        // Characters facing direction
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;

        // Animation selection
        texture = run;
    }
    else
    {
        // Animation selection
        texture = idle;
    }
}
