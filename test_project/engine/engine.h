#ifndef ENGINE_H
#define ENGINE_H

#include <initializer_list>
#include <sstream>

#include "raylib.hpp"
#include "uuid.h"
#include "graphics.h"
#include "window.h"
#include "fs.h"

class Setting
{
  Color background;
  int fps = 60;
  int width = 800;
  int height = 450;

  float font_size = 12;
  float font_spacing = 0;
  bool font_wrap = false;

  void setFps(int v)
  {
    SetTargetFPS(v);
  };

  void quit()
  {
    CloseWindow();
  }
};

class GraphicsStack;

class Engine {
  public:
  static Setting game;
  static Window window;
  static GraphicsStack graphics;

  // METHODS

  void go();

  private:
  bool load();
  void loop();
};

#endif