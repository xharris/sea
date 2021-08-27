#include "engine.h"

Window Engine::window;
Setting Engine::game;
GraphicsStack Engine::graphics = GraphicsStack();

void Engine::go()
{
  SetTraceLogLevel(LOG_DEBUG);
  if (!load())
    loop(lua);
}

bool Engine::load()
{
  SetTargetFPS(game.fps);
  Engine::game.background = black;

  InitWindow(
    Window::width, Window::height, 
    Window::title
  );

  return false;
}

void Engine::loop()
{  
  while (!WindowShouldClose())
  {
    // variable timestep (game)
    // GetFrameTime();

    // fixed timestep (physac automatically does this)
    // ...

    BeginDrawing();
    rlPushMatrix();
    


    rlPopMatrix();
    EndDrawing();
  }

  CloseWindow();
}