#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex) : worldPos(pos), Texture(tex)
{
}

void Prop::Render(Vector2 knightPos)
{
    Vector2 screenPos{Vector2Subtract(worldPos, knightPos)};

    DrawTextureEx(Texture, screenPos, 0.f, scale, WHITE);
}
