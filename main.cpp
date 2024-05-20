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
#include <stdint.h>
#define SCREEN_WIDTH (800.0f)
#define SCREEN_HEIGHT (800.0f)

#define BLOCK_ROWS (5U)
#define BLOCK_COLS (7U)
#define BLOCKS_CNT (BLOCK_ROWS * BLOCK_COLS)
#define BLOCK_WIDTH (50U)
#define BLOCK_HEIGHT (30U)

#define PADDLE_HEIGHT (30.0f)
#define PADDLE_WIDTH (130.0f)
#define PADDLE_Y_BASE_POS (SCREEN_HEIGHT - PADDLE_HEIGHT)
#define PADDLE_X_BASE_POS ((SCREEN_WIDTH / 2U) - (PADDLE_WIDTH / 2U))

#define BALL_RADIUS (5.0f)
#define BALL_X_BASE (SCREEN_WIDTH / DEFAULT_BALL_VELOCITY)
#define BALL_Y_BASE (BLOCK_HEIGHT * BLOCK_COLS + 100.0f)

#define DEFAULT_BALL_VELOCITY (5.0f)

static Color colors[BLOCK_ROWS * BLOCK_COLS];
static Rectangle colorsRecs[BLOCK_ROWS * BLOCK_COLS];
static uint32_t recHealth[BLOCK_ROWS * BLOCK_COLS];
static Rectangle paddle = {.x = PADDLE_X_BASE_POS,
                           .y = PADDLE_Y_BASE_POS,
                           .width = PADDLE_WIDTH,
                           .height = PADDLE_HEIGHT};
static Vector2 ball = {.x = BALL_X_BASE, .y = BALL_Y_BASE};
static Vector2 ballVelocity = {.x = DEFAULT_BALL_VELOCITY,
                               .y = DEFAULT_BALL_VELOCITY};

typedef enum {
  COLLISION_LEFT = 0,
  COLLISION_RIGHT,
  COLLISION_UP,
  COLLISION_DOWN,
  COLLISION_NONE,
} CollisionSide;

CollisionSide CheckBallCollisionWithBrick(Vector2 ball, Rectangle brick) {

  // Check left and right
  //
  if ((ball.y - BALL_RADIUS >= brick.y - BALL_RADIUS) &&
      (ball.y + BALL_RADIUS <= brick.y + brick.height + BALL_RADIUS)) {
    // check if collision is from left or right
    //
    if ((ball.x + BALL_RADIUS >= brick.x) &&
        (ball.x + BALL_RADIUS <= brick.x + 10)) {
      return COLLISION_LEFT;
    } else if (((ball.x - BALL_RADIUS) <= (brick.x + brick.width)) &&
               ((ball.x - BALL_RADIUS) >= (brick.x + brick.width - 10))) {
      return COLLISION_RIGHT;
    }
  } else if ((ball.x - BALL_RADIUS >= brick.x) &&
             (ball.x + BALL_RADIUS <= brick.x + brick.width)) {
    if ((ball.y + BALL_RADIUS >= brick.y) &&
        (ball.y + BALL_RADIUS <= brick.y + 10)) {
      return COLLISION_UP;
    } else if (((ball.y - BALL_RADIUS) <= (brick.y + brick.height)) &&
               ((ball.y - BALL_RADIUS) >= (brick.y + brick.height - 10))) {
      return COLLISION_DOWN;
    }
  }

  return COLLISION_NONE;
}

CollisionSide getWallCollisionSide(Vector2 ball) {

  if (ball.x - BALL_RADIUS <= 0.0f && ball.x - BALL_RADIUS >= -1.0f)
    return COLLISION_LEFT;
  if (ball.x + BALL_RADIUS >= SCREEN_WIDTH &&
      ball.x + BALL_RADIUS <= SCREEN_WIDTH + 1.0f)
    return COLLISION_RIGHT;
  if (ball.y - BALL_RADIUS <= 0.0f && ball.y - BALL_RADIUS >= -1.0f)
    return COLLISION_UP;
  if (ball.y + BALL_RADIUS >= SCREEN_HEIGHT &&
      ball.y + BALL_RADIUS <= SCREEN_HEIGHT + 1.0f)
    return COLLISION_DOWN;

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
    recHealth[i] = 2U;
  }

  int colorState[BLOCKS_CNT] = {0}; // Color state: 0-DEFAULT, 1-MOUSE_HOVER

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    //

    int keyPressed = GetKeyPressed();
    if (IsKeyDown(KEY_A))
      paddle.x -= 6;
    if (IsKeyDown(KEY_D))
      paddle.x += 6;

    if (paddle.x <= 0)
      paddle.x = 0;
    if (paddle.x + paddle.width >= SCREEN_WIDTH)
      paddle.x = SCREEN_WIDTH - paddle.width;

    ball.x += ballVelocity.x;
    ball.y += ballVelocity.y;

    switch (getWallCollisionSide(ball)) {
    case COLLISION_UP:
      ballVelocity.y *= -1.0f;
      break;
    case COLLISION_DOWN:
      ballVelocity.y *= -1.0f;
      break;
    case COLLISION_LEFT:
      ballVelocity.x *= -1.0f;
      break;
    case COLLISION_RIGHT:
      ballVelocity.x *= -1.0f;
      break;
    case COLLISION_NONE:
      break;
    default:
      break;
    }
    for (int i = 0; i < BLOCK_COLS * BLOCK_ROWS; i++) {
      if (recHealth[i] == 0) {
        continue;
      }

      CollisionSide collisionSide =
          CheckBallCollisionWithBrick(ball, colorsRecs[i]);

      if (collisionSide != COLLISION_NONE) {
        recHealth[i]--;
      }

      switch (collisionSide) {
      case COLLISION_UP:
        colors[i] = GREEN;
        ballVelocity.y = -DEFAULT_BALL_VELOCITY;
        break;
      case COLLISION_DOWN:
        ballVelocity.y = DEFAULT_BALL_VELOCITY;
        colors[i] = RED;
        break;
      case COLLISION_LEFT:
        colors[i] = BLUE;
        ballVelocity.x = -DEFAULT_BALL_VELOCITY;
        break;
      case COLLISION_RIGHT:
        colors[i] = PINK;
        ballVelocity.x = DEFAULT_BALL_VELOCITY;
        break;
      case COLLISION_NONE:
        colors[i] = YELLOW;
      default:
        break;
      }
    }

    if (ball.x - BALL_RADIUS >= paddle.x &&
        ball.x + BALL_RADIUS <= paddle.x + paddle.width &&
        ball.y + BALL_RADIUS >= paddle.y)
      ballVelocity.y = -DEFAULT_BALL_VELOCITY;
    //----------------------------------------------------------------------------------
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Krezo breakout clone ", 28, 42, 20, BLACK);

    DrawCircle(ball.x, ball.y, BALL_RADIUS, BLUE);
    for (int i = 0; i < BLOCK_COLS * BLOCK_ROWS; i++) // Draw all rectangles
    {
      if (recHealth[i] != 0) {
        DrawRectangleRec(colorsRecs[i], colors[i]);
      }
    }

    DrawRectangleRounded(paddle, 0.9f, 1U, BLUE);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
