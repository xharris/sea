#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>

#include "raylib.hpp"

class Window
{
  public:

  int width = 800;
  int height = 450;
  const char* title = "Game";

  void setSize(int w, int h);
};

#endif 