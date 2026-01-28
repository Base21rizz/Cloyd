#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

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

    // Prop rock
    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")},
    };

    // Goblin
    Enemy goblin{Vector2{},
                 LoadTexture("characters/goblin_idle_spritesheet.png"),
                 LoadTexture("characters/goblin_run_spritesheet.png")};

    // Setting the target FPS
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getworldPos(), -1.f);

        // Draw Map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        // Draw the props
        for (auto prop : props)
        {
            prop.Render(knight.getworldPos());
        }

        knight.tick(GetFrameTime());

        // Check Map Bounds
        if (knight.getworldPos().x < 0.f ||
            knight.getworldPos().y < 0.f ||
            knight.getworldPos().x + windowWidth > map.width * mapScale ||
            knight.getworldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        // Check Prop Collision
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getworldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }
        goblin.tick(GetFrameTime());
        EndDrawing();
    }
    UnloadTexture(map);

    CloseWindow();
}