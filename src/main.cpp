#include "Game/game.hpp"
#include "raylib.h"

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
    auto start = std::chrono::system_clock::now();
    // Update
    //----------------------------------------------------------------------------------
    game.update();
    //----------------------------------------------------------------------------------

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Time to update : " << elapsed_seconds.count() << "seconds"
              << std::endl;

    start = std::chrono::system_clock::now();

    // Draw
    //----------------------------------------------------------------------------------
    game.draw();
    //----------------------------------------------------------------------------------

    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Time to draw : " << elapsed_seconds.count() << "seconds"
              << std::endl;
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
