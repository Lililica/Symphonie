#include "Game/game.hpp"
#include "raylib.h"

float previousTimeDrawing = 0.0f;
static const float frameRate = 30.0f;

float previousTimeUpdating = 0.0f;
static const float simulationSpeed = 1200.0f;

int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------

  Game game;

  game.init();

  SetExitKey(KEY_ESCAPE);
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    // if (previousTimeUpdating == 0.0f) {
    //   previousTimeUpdating = GetTime();
    //   game.update();
    // } else {
    //   float currentTime = GetTime();
    //   if (currentTime - previousTimeUpdating >= 1.0f / simulationSpeed) {
    //     previousTimeUpdating = currentTime;
    //     game.update();
    //   }
    // }
    game.update();
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    // if (previousTimeDrawing == 0.0f) {
    //   previousTimeDrawing = GetTime();
    //   game.draw();
    // } else {
    //   float currentTime = GetTime();
    //   if (currentTime - previousTimeDrawing >= 1.0f / frameRate) {
    //     previousTimeDrawing = currentTime;
    //     game.draw();
    //   }
    // }
    game.draw();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
