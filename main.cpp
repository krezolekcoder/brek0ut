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

typedef struct {
  Vector2 pos;
  Vector2 velocity;
  float radius;
  Color color;
} Ball_t;

typedef struct {
  Rectangle rec;
  Color color;
  uint32_t health;
} Brick_t;

typedef struct {
  Rectangle rec;
  Color color;
  float speed;
} Paddle_t;
// check if collision is from left or right
//
typedef enum {
  COLLISION_LEFT = 0,
  COLLISION_RIGHT,
  COLLISION_UP,
  COLLISION_DOWN,
  COLLISION_NONE,
} CollisionSide;

static Brick_t bricks[BLOCK_ROWS * BLOCK_COLS];
static Paddle_t paddle = {.rec = (Rectangle){.x = PADDLE_X_BASE_POS,
                                             .y = PADDLE_Y_BASE_POS,
                                             .width = PADDLE_WIDTH,
                                             .height = PADDLE_HEIGHT},
                          .color = BLUE,
                          .speed = 5.0f};

static Ball_t ball = {.pos = (Vector2){.x = BALL_X_BASE, .y = BALL_Y_BASE},
                      .velocity = (Vector2){.x = DEFAULT_BALL_VELOCITY,
                                            .y = DEFAULT_BALL_VELOCITY},
                      .radius = BALL_RADIUS,
                      .color = BLUE};

CollisionSide CheckBallCollisionWithBrick(Vector2 ball, Rectangle brick) {
  // check wheter collision is of up/down or left/right
  if ((ball.y - BALL_RADIUS >= brick.y - BALL_RADIUS) &&
      (ball.y + BALL_RADIUS <= brick.y + brick.height + BALL_RADIUS)) {
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

CollisionSide getWallCollisionSide(Ball_t &ball) {

  if (ball.pos.x - ball.radius <= 0.0f && ball.pos.x - ball.radius >= -1.0f)
    return COLLISION_LEFT;
  if (ball.pos.x + ball.radius >= SCREEN_WIDTH &&
      ball.pos.x + ball.radius <= SCREEN_WIDTH + 1.0f)
    return COLLISION_RIGHT;
  if (ball.pos.y - ball.radius <= 0.0f && ball.pos.y - BALL_RADIUS >= -1.0f)
    return COLLISION_UP;
  if (ball.pos.y + ball.radius >= SCREEN_HEIGHT &&
      ball.pos.y + ball.radius <= SCREEN_HEIGHT + 1.0f)
    return COLLISION_DOWN;

  return COLLISION_NONE;
}

static void bricksInitialization(Brick_t *bricks, uint32_t bricks_cnt) {

  for (int i = 0; i < bricks_cnt; i++) {
    bricks[i].color = YELLOW;
    bricks[i].rec = (Rectangle){
        .x = 20.0f + 100.0f * (i % BLOCK_COLS) + 30.0f + (i % BLOCK_COLS),
        .y = 80.0f + 50.0f * (i / BLOCK_COLS) + 20.0f * (i / BLOCK_COLS),
        .width = 100.0f,
        .height = 50.0f};
    bricks[i].health = 2U;
  }
}
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
             "raylib [shapes] example - colors palette");

  bricksInitialization(bricks, BLOCKS_CNT);
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
      paddle.rec.x -= 6;
    if (IsKeyDown(KEY_D))
      paddle.rec.x += 6;

    // update pos
    // DEBUG
    // ball.pos.x = GetMouseX();
    // ball.pos.y = GetMouseY();

    ball.color = BLUE;
    ball.pos.x += ball.velocity.x;
    ball.pos.y += ball.velocity.y;

    // check collisions

    // paddle with walls
    if (paddle.rec.x <= 0)
      paddle.rec.x = 0;
    if (paddle.rec.x + paddle.rec.width >= SCREEN_WIDTH)
      paddle.rec.x = SCREEN_WIDTH - paddle.rec.width;

    // ball with walls
    switch (getWallCollisionSide(ball)) {
    case COLLISION_UP:
      ball.velocity.y = DEFAULT_BALL_VELOCITY;
      ball.color = GREEN;
      break;
    case COLLISION_DOWN:
      ball.velocity.y = -DEFAULT_BALL_VELOCITY;
      ball.color = GREEN;
      break;
    case COLLISION_LEFT:
      ball.velocity.x = DEFAULT_BALL_VELOCITY;
      ball.color = GREEN;
      break;
    case COLLISION_RIGHT:
      ball.velocity.x = -DEFAULT_BALL_VELOCITY;
      ball.color = GREEN;
      break;
    case COLLISION_NONE:
      break;
    default:
      break;
    }

    // ball with bricks
    for (int i = 0; i < BLOCK_COLS * BLOCK_ROWS; i++) {
      if (bricks[i].health == 0) {
        continue;
      }

      CollisionSide collisionSide =
          CheckBallCollisionWithBrick(ball.pos, bricks[i].rec);

      if (collisionSide != COLLISION_NONE) {
        bricks[i].health--;
        ball.color = RED;
      }
      switch (collisionSide) {
      case COLLISION_UP:
        ball.velocity.y = -DEFAULT_BALL_VELOCITY;
        break;
      case COLLISION_DOWN:
        ball.velocity.y = DEFAULT_BALL_VELOCITY;
        break;
      case COLLISION_LEFT:
        ball.velocity.x = -DEFAULT_BALL_VELOCITY;
        break;
      case COLLISION_RIGHT:
        ball.velocity.x = DEFAULT_BALL_VELOCITY;
        break;
      case COLLISION_NONE:
        bricks[i].color = YELLOW;
      default:
        break;
      }
    }

    // ball with paddle
    if (ball.pos.x - ball.radius >= paddle.rec.x &&
        ball.pos.x + ball.radius <= paddle.rec.x + paddle.rec.width &&
        ball.pos.y + ball.radius >= paddle.rec.y) {

      ball.color = PINK;
      ball.velocity.y = -DEFAULT_BALL_VELOCITY;
    }

    //----------------------------------------------------------------------------------
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Krezo breakout clone ", 28, 42, 20, BLACK);

    DrawCircle(ball.pos.x, ball.pos.y, ball.radius, ball.color);
    for (int i = 0; i < BLOCK_COLS * BLOCK_ROWS; i++) {
      if (bricks[i].health != 0) {
        DrawRectangleRec(bricks[i].rec, bricks[i].color);
      }
    }
    DrawRectangleRounded(paddle.rec, 0.9f, 1U, BLUE);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
