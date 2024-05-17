#include "raylib.h"
#include <stdint.h>
#include <stdio.h>

#define SCREEN_WIDTH (640U)
#define SCREEN_HEIGHT (640U)
#define LED_CNT (8U)
#define LED_RADIUSS (SCREEN_WIDTH / LED_CNT)

#define BLOCK_ROWS (6U)
#define BLOCK_COLS (8U)
#define BLOCK_WIDTH (50U)
#define BLOCK_HEIGHT (30U)

#define PADDLE_HEIGHT (30U)
#define PADDLE_WIDTH (2 * BLOCK_WIDTH)
#define PADDLE_Y_BASE_POS (SCREEN_HEIGHT - PADDLE_HEIGHT)
#define PADDLE_X_BASE_POS ((SCREEN_WIDTH / 2U) - (PADDLE_WIDTH / 2U))

#define BALL_RADIUS (20U)
#define BALL_X_BASE (SCREEN_WIDTH / 2U)
#define BALL_Y_BASE (BLOCK_HEIGHT * BLOCK_COLS + 100)

typedef struct BallMovement {
  Vector2 velocity;
} BallMovement_t;

typedef struct Ball {
  float x;
  float y;
  float radius;
} Ball_t;

Rectangle rec_grid[BLOCK_ROWS * BLOCK_COLS];
Rectangle paddle = {.x = PADDLE_X_BASE_POS,
                    .y = PADDLE_Y_BASE_POS,
                    .width = PADDLE_WIDTH,
                    .height = PADDLE_HEIGHT};
Ball_t ball = {.x = BALL_X_BASE, .y = BALL_Y_BASE, .radius = BALL_RADIUS};
BallMovement_t ball_velocity = {.velocity.x = 1.0f, .velocity.y = 1.0f};
static void GridInitialize(void);
static void GridDraw(void);
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
             "raylib [core] example - keyboard input");

  SetTargetFPS(120); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------
  GridInitialize();

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_H))
      paddle.x -= 2;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_L))
      paddle.x += 2;

    if (paddle.x < 0)
      paddle.x = 0;
    if (paddle.x + PADDLE_WIDTH > SCREEN_WIDTH)
      paddle.x = SCREEN_WIDTH - PADDLE_WIDTH;

    ball.x += ball_velocity.velocity.x;
    ball.y += ball_velocity.velocity.y;

    if (ball.x - ball.radius < 0.0f) {
      ball.x = ball.radius;
      ball_velocity.velocity.x *= -1.0f;
    } else if (ball.x + ball.radius > (float)SCREEN_WIDTH) {
      ball.x = (float)(SCREEN_WIDTH - (int)ball.radius);
      ball_velocity.velocity.x *= -1.0f;
    }

    if (ball.y - ball.radius < 0.0f) {
      ball.y = ball.radius;
      ball_velocity.velocity.y *= -1.0f;
    } else if (ball.y + ball.radius > (float)SCREEN_HEIGHT) {
      ball.y = (float)(SCREEN_HEIGHT - (int)ball.radius);
      ball_velocity.velocity.y *= -1.0f;
    }

    // Draw
    //----------------------------------------------------------------------------------
    //
    //
    BeginDrawing();
    ClearBackground(RAYWHITE);

    GridDraw();
    DrawRectangleRounded(paddle, 0.5f, 10, PINK);
    DrawCircle((int)ball.x, (int)ball.y, (int)ball.radius, GREEN);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}

static void GridInitialize(void) {

  for (int i = 0; i < BLOCK_COLS; i++) {
    for (int j = 0; j < BLOCK_ROWS; j++) {
      rec_grid[i * BLOCK_COLS + j].height = BLOCK_HEIGHT;
      rec_grid[i * BLOCK_COLS + j].width = BLOCK_WIDTH;
      rec_grid[i * BLOCK_COLS + j].x = i * (BLOCK_WIDTH + 20) + 50;
      rec_grid[i * BLOCK_COLS + j].y = j * (BLOCK_HEIGHT + 20) + 50;
    }
  }
}

static void GridDraw(void) {

  for (int i = 0; i < BLOCK_COLS; i++) {
    for (int j = 0; j < BLOCK_ROWS; j++) {
      DrawRectangle(rec_grid[i * BLOCK_COLS + j].x,
                    rec_grid[i * BLOCK_COLS + j].y,
                    rec_grid[i * BLOCK_COLS + j].width,
                    rec_grid[i * BLOCK_COLS + j].height, BLUE);
    }
  }
}
