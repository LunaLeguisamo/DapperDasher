#include "raylib.h"

int main()
{
    // Window dimensions
    const int WindowWidth{512};
    const int WindowHeight{380};

    // Initialize window
    InitWindow(WindowWidth, WindowHeight, "Dapper Dasher");

    // acceleration due to gravity (pixels/frame) / frame
    const int gravity{1'000};
    int velocity{0};

    // is the rectangle in air
    bool isInAir{};

    // jump velocity
    const int jumpVel{-600};

    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width / 8, nebula.height / 8};
    Vector2 nebPos{WindowWidth, WindowHeight - nebRec.height};

    // nebula x velocity (pixels/second)
    int nebVel{-600};

    // scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = WindowWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = WindowHeight - scarfyRec.height;

    // animation frame
    int frame{0};

    // amount of time before we update the animation frame
    const float updateTime{1.0 / 12.0};
    float runningTime{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // delta time (time since the last frame)
        const float dT{GetFrameTime()};

        runningTime += dT;

        if (!isInAir)
        {
            if (runningTime >= updateTime)
                {

                    runningTime = 0.0;

                    // update animation frame
                    scarfyRec.x = frame * scarfyRec.width;
                    frame++;
                    if (frame > 5)
                    {
                        frame = 0;
                    }
                }
        }

        // perform ground check
        if (scarfyPos.y >= WindowHeight - scarfyRec.height)
        {
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // apply gravity
            velocity += gravity * dT;
            isInAir = true;
        }

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // update nebula pos
        nebPos.x += nebVel * dT;

        // Update scarffy position
        scarfyPos.y += velocity * dT;

        // draw nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

        // draw scarffy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        // Stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}