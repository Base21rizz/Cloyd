#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Vector2 getworldPos() { return worldPos; }

private:
    Texture2D texture;
    Texture2D idle;
    Texture2D run;
    Vector2 screenPos;
    Vector2 worldPos;
    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};
    // Animation variable
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};
};

int main()
{
    // Window
    int windowWidth{384};
    int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Cloyd");

    // Map
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};
    float speed{4.0};

    // Knight Texture loading
    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
    Vector2 knightPos{
        (float)windowWidth / 2.0f - 4.0f * (0.5 * (float)knight.width / 6.0),
        (float)windowHeight / 2.0f - 4.0f * (0.5 * (float)knight.height)};

    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};

    // Animation variable
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};

    // Setting the target FPS
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

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
            // Set mapPos -= direction
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));

            // Characters facing direction
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;

            // Animation selection
            knight = knight_run;
        }
        else
        {
            // Animation selection
            knight = knight_idle;
        }

        // Draw Map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        // Update animation frame
        runningTime += GetFrameTime();
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame > maxFrames)
                frame = 0;
        }

        // Animation of the knight
        Rectangle source{frame * (float)knight.width / 6.f, 0.f, rightLeft * (float)knight.width / 6.f, (float)knight.width / 6.f};
        Rectangle dest{knightPos.x, knightPos.y, 4.0f * (float)knight.width / 6.0f, 4.0f * (float)knight.height};
        DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

        EndDrawing();
    }
    UnloadTexture(map);

    CloseWindow();
}