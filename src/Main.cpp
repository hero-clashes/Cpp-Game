#include "raylib.h"
#include "Engine/Engine.hpp"
#include "Main_Menu/Main_Menu.hpp"
int main(int argc, char **argv)
{
    // Init the Engine
    Engine engine;

    // Init The Main Menu
    engine.change_state((State *)new Main_Menu);

    // Game loop.
    while (!engine.Should_Exit)
      {
            // Handle input.
            engine.handle_events();
            // Updating
            engine.update();
            // Rendering
            engine.render();
      }
      return 0;
}
