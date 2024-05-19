/*******************************************************************************************
 *
 *   raylib [shapes] example - Colors palette
 *
 *   Example originally created with raylib 1.0, last time updated with
 *raylib 2.5
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an
 *OSI-certified, BSD-like license that allows static linking with closed source
 *software
 *
 *   Copyright (c) 2014-2024 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib.h"

#define BLOCK_ROWS (5U)
#define BLOCK_COLS (7U)
#define BLOCK_WIDTH (50U)
#define BLOCK_HEIGHT (30U)

#define PADDLE_HEIGHT (30U)
#define PADDLE_WIDTH (2 * BLOCK_WIDTH)
#define PADDLE_Y_BASE_POS (SCREEN_HEIGHT - PADDLE_HEIGHT)
#define PADDLE_X_BASE_POS ((SCREEN_WIDTH / 2U) - (PADDLE_WIDTH / 2U))

#define BALL_RADIUS (20U)
#define BALL_X_BASE (SCREEN_WIDTH / 2U)
#define BALL_Y_BASE (BLOCK_HEIGHT * BLOCK_COLS + 100)

static Color colors[BLOCK_ROWS * BLOCK_COLS];
static Rectangle colorsRecs[BLOCK_ROWS * BLOCK_COLS];
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 800;

  InitWindow(screenWidth, screenHeight,
             "raylib [shapes] example - colors palette");

  for (int i = 0; i < BLOCK_COLS * BLOCK_ROWS; i++) {
    colors[i] = YELLOW;
  }

  // Fills colorsRecs data (for every rectangle)
  for (int i = 0; i < BLOCK_COLS * BLOCK_ROWS; i++) {
    colorsRecs[i].width = 100.0f;
    colorsRecs[i].height = 50.0f;
    colorsRecs[i].x = 20.0f + colorsRecs[i].width * (i % BLOCK_COLS) +
                      30.0f * (i % BLOCK_COLS);
    colorsRecs[i].y = 80.0f + colorsRecs[i].height * (i / BLOCK_COLS) +
                      20.0f * (i / BLOCK_COLS);
  }

  int colorState[BLOCK_COLS * BLOCK_ROWS] = {
      0}; // Color state: 0-DEFAULT, 1-MOUSE_HOVER

  Vector2 mousePoint = {0.0f, 0.0f};

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    mousePoint = GetMousePosition();

    DrawCircle(mousePoint.x, mousePoint.y, 10.0f, BLUE);
    for (int i = 0; i < BLOCK_COLS * BLOCK_ROWS; i++) {
      if (CheckCollisionCircleRec(mousePoint, 10.0f, colorsRecs[i])) {
        colorState[i] = 1;
        colors[i] = BLUE;
      } else {
        colorState[i] = 0;
        colors[i] = YELLOW;
      }
    }
    //----------------------------------------------------------------------------------
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("raylib colors palette", 28, 42, 20, BLACK);
    DrawText("press SPACE to see all colors", GetScreenWidth() - 180,
             GetScreenHeight() - 40, 10, GRAY);

    for (int i = 0; i < BLOCK_COLS * BLOCK_ROWS; i++) // Draw all rectangles
    {
      // DrawRectangleRec(colorsRecs[i],
      //                  Fade(colors[i], colorState[i] ? 0.6f : 1.0f));

      DrawRectangleRec(colorsRecs[i], colors[i]);
    }

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
