#include "raylib.h"

int main()
{
    int windowWidth{384};
    int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Cloyd");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 mapPos{0.0, 0.0};
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        EndDrawing();
    }
    UnloadTexture(map);
}