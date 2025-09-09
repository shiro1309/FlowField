#include "raylib.h"
#include "stdio.h"
#include "time.h"
#include "math.h"
#include "stdlib.h"

int getParticlePos(int max);

struct particle {
    double x; // position x
    double y; // position y
    Vector2 velocity; // used to get speed and direction with max of 1 and min of -1
    Vector2 trail[20]; // vector trail vill be sett to the position and pased down
} particle;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main(void)
{
    // Initialization
    const int screenWidth  = 1600;
    const int screenHeight = 800;
    const int particleAmount = 100;
    const int flowResolution = 100;
    const float alpha = 0.05; // rate of change for the vectors

    float FlowGrid[screenWidth/flowResolution][screenHeight/flowResolution];
    for(int column = 0; column < screenWidth/flowResolution; column++) {
        for(int row = 0; row < screenHeight/flowResolution; row++) {
            float angle = (row / (float)(screenHeight/flowResolution) * PI);
            FlowGrid[column][row] = angle;
        }
    }

    struct particle Particles[particleAmount];
    
    srand(time(0));
    
    for(int i = 0; i < particleAmount; i++){
        Particles[i].x = getParticlePos(screenWidth);
        Particles[i].y = getParticlePos(screenHeight);
    }


    
    //--------------------------------------------------------------------------------------

    InitWindow(screenWidth, screenHeight, "raylib Flow field");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            for(int i = 0; i < particleAmount; i++){
                DrawCircle(Particles[i].x, Particles[i].y, 3, BLACK);
            }


            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

int getParticlePos(int max) {
    return rand() % (max + 1);
}