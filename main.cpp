#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{
    // Window
    int windowWidth{384};
    int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Cloyd");

    // Map
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    // Knight
    Character knight{windowWidth, windowHeight};

    // Setting the target FPS
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getworldPos(), -1.f);

        // Draw Map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
        knight.tick(GetFrameTime());

        // Check Map Bounds
        if (knight.getworldPos().x < 0.f ||
            knight.getworldPos().y < 0.f ||
            knight.getworldPos().x + windowWidth > map.width * mapScale ||
            knight.getworldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        EndDrawing();
    }
    UnloadTexture(map);

    CloseWindow();
}