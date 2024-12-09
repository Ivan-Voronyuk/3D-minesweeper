#include <fstream>
#include <iostream>
#include <sstream>

#include "VectorMath_lib/render.h"

#ifndef GAME_H
#define GAME_H

Render::Texture read_pnm(const char* fname);
void write_pnm(const char* fname, const Render::Texture& tex);

class Game {
 private:
 public:
  Render::Canvas canvas;
  Render::CubeView cube;
  Game(int w, int h, float scale, const char* tex_fname);
  void drag_callback(int x0, int y0, int x1, int y1);
  void click_callback(int x0, int y0, char b);
};

#endif  // !GAME_H
