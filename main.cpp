#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

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
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}};

    // Goblin
    Enemy goblin{Vector2{800.f, 300.f},
                 LoadTexture("characters/goblin_idle_spritesheet.png"),
                 LoadTexture("characters/goblin_run_spritesheet.png")};

    // SLime
    Enemy slime{Vector2{500.f, 700.f}, LoadTexture("characters/slime_idle_spritesheet.png"),
                LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy *enemies[]{
        &goblin,
        &slime};

    for (auto enemy : enemies)
        enemy->setTarget(&knight);

    // Setting the target FPS
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getworldPos(), -1.f);

        // Draw Mapd
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        // Draw the props
        for (auto prop : props)
        {
            prop.Render(knight.getworldPos());
        }

        if (!knight.getAlive()) // Character's dead
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else // Character's alive
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, BLUE);
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
        for (auto enemy : enemies)
            enemy->tick(GetFrameTime());

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }
    UnloadTexture(map);

    CloseWindow();
}