#include "raylib.h"
#include <stdio.h>

#define SCREEN_WIDTH (640U)
#define SCREEN_HEIGHT (640U)
#define LED_CNT (8U)
#define LED_RADIUSS (SCREEN_WIDTH / LED_CNT)

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
             "raylib [core] example - keyboard input");

  SetTargetFPS(120); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------
  Rectangle rec = {.x = 100, .y = 100, .width = 500, .height = 200};
  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    DrawRectangleRounded(rec, 0.4f, 1, BLACK);
    //----------------------------------------------------------------------------------
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
