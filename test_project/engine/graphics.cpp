#include "graphics.h"

GraphicsStack::GraphicsStack()
{
  if (stack.size() > 0)
    stack.push(stack.top()); 
  else 
    stack.push(GraphicsState());
  current = &stack.top();
}
// push a copy of the current state on the stack
void GraphicsStack::push() 
{ 
  if (stack.size() > 0)
    stack.push(stack.top()); 
  else 
    stack.push(GraphicsState());
  rlPushMatrix();
  current = &stack.top();
}
void GraphicsStack::pop() 
{
  if (stack.size() > 1)
    stack.pop();
  rlPopMatrix();
  current = &stack.top();
}
void GraphicsStack::reset()
{
  while (!stack.empty())
    stack.pop();
  rlLoadIdentity();
  stack.push(GraphicsState{});
  current = &stack.top();
}

Canvas::Canvas()
{
  tex = LoadRenderTexture(Engine::game.width, Engine::game.height);
}
Canvas::Canvas(int w, int h)
{
  tex = LoadRenderTexture(w, h);
}
Canvas::~Canvas()
{
  UnloadRenderTexture(tex);
}
void Canvas::begin()
{
  BeginTextureMode(tex);
}
void Canvas::end()
{
  EndTextureMode();
}
void Canvas::clear()
{
  ClearBackground(Engine::game.background);
}
void Canvas::clear(Color c)
{
  ClearBackground(c);
}
void Canvas::text(const char *text)
{
  DrawText(text, 0, 0, Engine::game.font_size, Engine::graphics.current->fill);
}
void Canvas::text(const char *text, int x, int y)
{
  DrawText(text, x, y, Engine::game.font_size, Engine::graphics.current->fill);
}
void Canvas::text(const char *text, float x, float y, float w, float h)
{
  DrawTextRec(GetFontDefault(), text, Rectangle{x,y,w,h}, Engine::game.font_size, Engine::game.font_spacing, Engine::game.font_wrap, Engine::graphics.current->fill);
}
void Canvas::circle(int x, int y, float r)
{
  DrawCircle(x, y, r, Engine::graphics.current->fill);
  if (Engine::graphics.current->stroke != blank) 
    DrawCircleLines(x, y, r, Engine::graphics.current->stroke);
}

Color rgb(int r, int g, int b)
{
  return Color{(uchar)r, (uchar)g, (uchar)b, (uchar)255};
}
Color rgb(int r, int g, int b, int a) 
{ 
  return Color{(uchar)r, (uchar)g, (uchar)b, (uchar)a};
}
Color hsv(float h, float s, float v)
{
  return ColorFromHSV(h,s,v); 
}
Color hsv(float h, float s, float v, float a) 
{  
  return ColorAlpha(ColorFromHSV(h,s,v), a);
}
Color hex(int h) 
{ 
  // reformat hex value
  Color c{0,0,0,0};
  if (h == 0x0)
    return c;
  bool is_short = !(h >> 8 > 0x0);
  bool has_alpha = h >> 24 > 0x0;
  if (is_short)
    h = (h << 24) | 0x000000FF;
  else if (!has_alpha)
    h = (h << 8) | 0x000000FF;
  // convert to rgba
  c.r = (h >> 24) & 0xFF;
  c.g = (h >> 16) & 0xFF;
  c.b = (h >> 8) & 0xFF;
  c.a = h & 0xFF;
  return c;
}
// Color color(const char* hex) { return white; }

void fill() { Engine::graphics.current->fill = blank; }
void fill(Color c) { Engine::graphics.current->fill = c; }
void stroke() { Engine::graphics.current->stroke = blank; }
void stroke(Color c) { Engine::graphics.current->stroke = c; }


void translate(float x, float y)
{
  rlTranslatef(x, y, 0);
}
void rotate(float r)
{
  rlRotatef(r, 1.f, 0.f, 0.f);
}
void scale(float x, float y)
{
  rlScalef(x, y, 1.f);
}


// void font(sol::table f)
// {
//   Engine::game.font_size = f["size"].get_or(Engine::game.font_size);
//   Engine::game.font_spacing = f["spacing"].get_or(Engine::game.font_spacing);
//   Engine::game.font_wrap = f["wrap"].get_or(Engine::game.font_wrap);
// }


BImage::BImage(const char* filename)
{
  if (!FileExists(filename))
    Error::throws({"Image not found: ", filename});
  else 
  {
    image = LoadImage(filename);
    changed = true;
  }
}

void BImage::operator()() {
  if (changed || texture.id == 0)
  {
    texture = LoadTextureFromImage(image);
    changed = false;
  }
  DrawTexture(texture, 0, 0, Engine::graphics.current->fill);
}

BImage BImage::create(const char* filename)
{
  return BImage(filename);
}

// BImage* BImage::sprite()
// {
  
//   return this;
// }
