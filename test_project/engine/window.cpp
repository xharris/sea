#include "window.h"

void Window::setSize(int w, int h)
{
  if (IsWindowReady())
  {
    SetWindowSize(w, h);
  }
}