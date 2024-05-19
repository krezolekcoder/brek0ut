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

#define SCREEN_WIDTH (800.0f)
#define SCREEN_HEIGHT (800.0f)

#define BLOCK_ROWS (5U)
#define BLOCK_COLS (7U)
#define BLOCKS_CNT (BLOCK_ROWS * BLOCK_COLS)
#define BLOCK_WIDTH (50U)
#define BLOCK_HEIGHT (30U)

#define PADDLE_HEIGHT (30.0f)
#define PADDLE_WIDTH (100.0f)
#define PADDLE_Y_BASE_POS (SCREEN_HEIGHT - PADDLE_HEIGHT)
#define PADDLE_X_BASE_POS ((SCREEN_WIDTH / 2U) - (PADDLE_WIDTH / 2U))

#define BALL_RADIUS (10.0f)
#define BALL_X_BASE (SCREEN_WIDTH / 2.0f)
#define BALL_Y_BASE (BLOCK_HEIGHT * BLOCK_COLS + 100.0f)

static Color colors[BLOCK_ROWS * BLOCK_COLS];
static Rectangle colorsRecs[BLOCK_ROWS * BLOCK_COLS];
static Rectangle paddle;
static Vector2 ball = {.x = BALL_X_BASE, .y = BALL_Y_BASE};
static Vector2 ballVelocity = {.x = 2.0f, .y = 2.0f};

typedef enum {
  COLLISION_BRICK_LEFT = 0,
  COLLISION_BRICK_RIGHT,
  COLLISION_BRICK_UP,
  COLLISION_BRICK_DOWN,
  COLLISION_NONE,
} collision_brick_t;

collision_brick_t CheckBallCollisionWithBrick(Vector2 ball, Rectangle brick) {

  // Check left and right
  //
  if ((ball.y - BALL_RADIUS >= brick.y) &&
      (ball.y + BALL_RADIUS <= brick.y + brick.height)) {
    // check if collision is from left or right
    //
    if ((ball.x + BALL_RADIUS >= brick.x) &&
        (ball.x + BALL_RADIUS <= brick.x + 10)) {
      return COLLISION_BRICK_LEFT;
    } else if (((ball.x - BALL_RADIUS) <= (brick.x + brick.width)) &&
               ((ball.x - BALL_RADIUS) >= (brick.x + brick.width - 10))) {
      return COLLISION_BRICK_RIGHT;
    }
  } else if ((ball.x - BALL_RADIUS >= brick.x) &&
             (ball.x + BALL_RADIUS <= brick.x + brick.width)) {
    if ((ball.y + BALL_RADIUS >= brick.y) &&
        (ball.y + BALL_RADIUS <= brick.y + 10)) {
      return COLLISION_BRICK_UP;
    } else if (((ball.y - BALL_RADIUS) <= (brick.y + brick.height)) &&
               ((ball.y - BALL_RADIUS) >= (brick.y + brick.height - 10))) {
      return COLLISION_BRICK_DOWN;
    }
  }

  return COLLISION_NONE;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
             "raylib [shapes] example - colors palette");

  for (int i = 0; i < BLOCKS_CNT; i++) {
    colors[i] = YELLOW;
  }

  // Fills colorsRecs data (for every rectangle)
  for (int i = 0; i < BLOCKS_CNT; i++) {
    colorsRecs[i].width = 100.0f;
    colorsRecs[i].height = 50.0f;
    colorsRecs[i].x = 20.0f + colorsRecs[i].width * (i % BLOCK_COLS) +
                      30.0f * (i % BLOCK_COLS);
    colorsRecs[i].y = 80.0f + colorsRecs[i].height * (i / BLOCK_COLS) +
                      20.0f * (i / BLOCK_COLS);
  }

  int colorState[BLOCKS_CNT] = {0}; // Color state: 0-DEFAULT, 1-MOUSE_HOVER

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    // ball.x += ballVelocity.x;
    // ball.y += ballVelocity.y;
    //
    // if (CheckCollisionPointLine(ball, (Vector2){.x = 0U, .y = 0U},
    //                             (Vector2){.x = 0U, .y = SCREEN_HEIGHT}, 1)) {
    //   ballVelocity.x *= -1.0f;
    // } else if (CheckCollisionPointLine(
    //                ball, (Vector2){.x = SCREEN_WIDTH, .y = 0U},
    //                (Vector2){.x = SCREEN_WIDTH, .y = SCREEN_HEIGHT}, 1)) {
    //   ballVelocity.x *= -1.0f;
    // } else if (CheckCollisionPointLine(ball, (Vector2){.x = 0U, .y = 0U},
    //                                    (Vector2){.x = SCREEN_WIDTH, .y = 0U},
    //                                    1)) {
    //   ballVelocity.y *= -1.0f;
    // } else if (CheckCollisionPointLine(
    //                ball, (Vector2){.x = 0U, .y = SCREEN_HEIGHT},
    //                (Vector2){.x = SCREEN_WIDTH, .y = SCREEN_HEIGHT}, 1)) {
    //   ballVelocity.y *= -1.0f;
    // }

    Vector2 mousePos = GetMousePosition();

    ball.x = mousePos.x;
    ball.y = mousePos.y;

    for (int i = 0; i < BLOCK_COLS * BLOCK_ROWS; i++) {
      switch (CheckBallCollisionWithBrick(ball, colorsRecs[i])) {
      case COLLISION_BRICK_UP:
        colors[i] = GREEN;
        break;
      case COLLISION_BRICK_DOWN:
        colors[i] = RED;
        break;
      case COLLISION_BRICK_LEFT:
        colors[i] = BLUE;
        break;
      case COLLISION_BRICK_RIGHT:
        colors[i] = PINK;
        break;
      case COLLISION_NONE:
        colors[i] = YELLOW;
      default:
        break;
      }
      // if (CheckCollisionCircleRec(ball, 10.0f, colorsRecs[i])) {
      //   colorState[i] = 1;
      //   colors[i] = BLUE;
      // } else {
      //   colorState[i] = 0;
      //   colors[i] = YELLOW;
      // }
    }
    //----------------------------------------------------------------------------------
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Krezo breakout clone ", 28, 42, 20, BLACK);

    DrawCircle(ball.x, ball.y, BALL_RADIUS, BLUE);
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
