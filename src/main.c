#include "raylib.h"
#include "stdio.h"
#include "time.h"
#include "math.h"
#include "stdlib.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

int getParticlePos(int max);
float float_map(int *input, float Imin, float Imax, float min, float max, float *pointer);

struct particle {
    double x; // position x
    double y; // position y
    //Vector2 trail[20]; // vector trail vill be sett to the position and pased down
} particle;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main(void)
{
    // Initialization
    const int screenWidth  = 1600;
    const int screenHeight = 800;
    Vector2 resolution = {screenWidth, screenHeight};

    const int particleAmount = 5000;
    const int flowResolution = 10;
    const float alpha = 0.05; // rate of change for the vectors
    const float speed = 1.1;

    int perlin_x_offset = 0;
    int perlin_y_offset = 0;

    Color perlin_color = {0,0,0,0};
    Color *perlin_colorptr = &perlin_color;
    int perlinGray = 0;
    int *PerlinGrayPtr = &perlinGray;

    float temp_float = 0.0f;
    float *tempPtr = &temp_float;

    char fpsString[20];
    float fps = 0.0f;

    float angle = 0.0f;
    float *anglePtr = &angle;

    int column = 0;
    int *columnPtr = &column;

    int row = 0;
    int *rowPtr = &row;

    InitWindow(screenWidth, screenHeight, "raylib Flow field");

    Image perlinNoiseMap = GenImagePerlinNoise(screenWidth/flowResolution, screenHeight/flowResolution, perlin_x_offset, perlin_y_offset, 4.0f);

    float FlowGrid[screenWidth/flowResolution][screenHeight/flowResolution];
    for(int column = 0; column < screenWidth/flowResolution; column++) {
        for(int row = 0; row < screenHeight/flowResolution; row++) {
            
            *perlin_colorptr = GetImageColor(perlinNoiseMap, column, row);
            *PerlinGrayPtr = (perlin_color.r + perlin_color.g + perlin_color.b) / 3;
            *anglePtr = float_map(&perlinGray, 0, 255, 0, PI*2, &temp_float);
            
           //*anglePtr = (column / (float)(screenHeight/flowResolution) * PI) * (row / (float)(screenWidth/flowResolution) * PI);
           //printf("%f\n", angle);
            FlowGrid[column][row] = angle;
        }
    }

    struct particle Particles[particleAmount];
    
    //srand(time(0));
    
    for(int i = 0; i < particleAmount; i++){
        Particles[i].x = getParticlePos(screenWidth);
        Particles[i].y = getParticlePos(screenHeight);
    }

    for(int i = 0; i< particleAmount; i++) {
        *anglePtr = FlowGrid[(int)(Particles[i].x/(screenWidth/flowResolution))][(int)(Particles[i].y/(screenHeight/flowResolution))];
        int step_x = speed * cos(angle);
        int step_y = speed * sin(angle);
        Particles[i].x += step_x;
        Particles[i].y += step_y;
    }
    
    //--------------------------------------------------------------------------------------

    

    //--------------------------------------------------------------------------------------
    // all raylib init and window creation is done here
    //--------------------------------------------------------------------------------------
    /*
    Shader shader = LoadShader(NULL, "../assets/shaders/perlin.fs");
    if (shader.id == 0) {
        printf("Failed to load shader!\n");
        return 1;
    }
    else {
        printf("Loaded shader into memory");
    }
    
    
    int timeLoc = GetShaderLocation(shader, "uTime");
    int resLoc  = GetShaderLocation(shader, "uResolution");
    float Start_time = 0.0f;
    */
    

    //SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // update the particle for the new information

        fps = GetFPS();
        snprintf(fpsString, sizeof(fpsString), "FPS: %.2f", fps);

        //perlinNoiseMap = GenImagePerlinNoise(screenWidth/flowResolution, screenHeight/flowResolution, perlin_x_offset, perlin_y_offset, 4.0f);
        


        for(int i = 0; i< particleAmount; i++) {
            *columnPtr = (int)(Particles[i].x/flowResolution);
            *rowPtr = (int)(Particles[i].y/flowResolution);

            *anglePtr = FlowGrid[column][row];
            //*perlin_colorptr = GetImageColor(perlinNoiseMap, column, row);
            //*anglePtr = (perlin_color.r + perlin_color.g + perlin_color.b) / 3;
            //*anglePtr = float_map(&perlinGray, 0, 255, 0, PI*2, &temp_float);
            
            Particles[i].x += speed * cos(angle);
            if(Particles[i].x > screenWidth) {
                Particles[i].x = 1;
            }
            if(Particles[i].x < 1) {
                Particles[i].x = screenWidth-1;
            }

            Particles[i].y += speed * sin(angle);
            if(Particles[i].y > screenHeight) {
                Particles[i].y = 1;
            }
            if(Particles[i].y < 1){
                Particles[0].y = screenHeight - 1;
            }
        }
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            
        ClearBackground(RAYWHITE);
            for(int i = 0; i < particleAmount; i++) {
                //DrawPixel(Particles[i].x, Particles[i].y, BLACK);
                DrawRectangle(Particles[i].x, Particles[i].y, 3, 3, BLACK);
                //DrawCircle(Particles[i].x, Particles[i].y, 2, BLACK);
            }

            DrawText(fpsString, 5, 5, 20, DARKGRAY);
            
            
            
            /*
            for(int column = 0; column < screenWidth/flowResolution; column++) {
                for(int row = 0; row < screenHeight/flowResolution; row++) {
                    *anglePtr = FlowGrid[column][row];
                    int x = column*flowResolution + 10 * cos(angle);
                    int y = row*flowResolution + 10 * sin(angle);
                    DrawLine(column*flowResolution, row*flowResolution, column*flowResolution + 10 * cos(angle), row*flowResolution + 10 * sin(angle), BLACK);
                }
            }
            */
            

            

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

float float_map(int *input, float Imin, float Imax, float min, float max, float *pointer) {
    
    *pointer = (*input - Imin) / (Imax- Imin);

    return min + *pointer * (max - min);
}