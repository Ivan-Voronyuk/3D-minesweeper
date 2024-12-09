#include "game.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "VectorMath_lib/render.h"
#include "VectorMath_lib/types.h"

Render::Texture read_pnm(const char* fname) {
  int numrows = 0, numcols = 0, max_size = 0;
  std::ifstream infile(fname, std::ios_base::binary);
  std::stringstream ss;
  std::string inputLine = "";

  // First line : version
  getline(infile, inputLine);
  if (inputLine.compare("P6") != 0)
    std::cerr << "Version error" << std::endl;
  else
    std::cout << "Version : " << inputLine << std::endl;

  do {
    getline(infile, inputLine);
  } while (inputLine[0] == '#');

  // Continue with a stringstream
  ss << inputLine;
  // Third line : size
  ss >> numcols >> numrows;

  std::cout << numcols << " columns and " << numrows << " rows" << std::endl;

  do {
    getline(infile, inputLine);
  } while (inputLine[0] == '#');

  ss << inputLine;
  ss >> max_size;

  Render::Texture res{numcols, numrows};

  char* data = new char[numcols * numrows * 3];
  infile.read(data, numrows * numcols * 3);
  res.memcpy_from(reinterpret_cast<Render::Color*>(data));
  delete[] data;

  infile.close();

  return res;
}
void write_pnm(const char* fname, const Render::Texture& tex) {
  std::ofstream ofile(fname);
  ofile << "P6\n";
  ofile << tex.width << " " << tex.height << "\n";
  ofile << "255\n";

  char* data = new char[tex.width * tex.height * 3];
  tex.memcpy_to(reinterpret_cast<Render::Color*>(data));
  ofile.write(data, tex.width * tex.height * 3);
  delete[] data;
}

Game::Game(int w, int h, float scale, const char* tex_fname)
    : canvas{w, h}, cube{w, h, 512, 0.5, 90. / 180 * 3.1415926535} {
  Render::Texture tex = read_pnm(tex_fname);
  cube.get_side_texture(Render::CubeView::SIDES::F)          // A0
      .copy_rect_from(tex,                                   //
                      Render::Rect{0, 0 * 512, 512, 512},    //
                      Render::Rect{0, 0, 512, 512});         //
  cube.get_side_texture(Render::CubeView::SIDES::R)          // B0
      .copy_rect_from(tex,                                   //
                      Render::Rect{0, 1 * 512, 512, 512},    //
                      Render::Rect{0, 0, 512, 512});         //
  cube.get_side_texture(Render::CubeView::SIDES::U)          // C0
      .copy_rect_from(tex,                                   //
                      Render::Rect{0, 2 * 512, 512, 512},    //
                      Render::Rect{0, 0, 512, 512});         //
  cube.get_side_texture(Render::CubeView::SIDES::B)          // A1
      .copy_rect_from(tex,                                   //
                      Render::Rect{512, 0 * 512, 512, 512},  //
                      Render::Rect{0, 0, 512, 512});         //
  cube.get_side_texture(Render::CubeView::SIDES::L)          // B1
      .copy_rect_from(tex,                                   //
                      Render::Rect{512, 1 * 512, 512, 512},  //
                      Render::Rect{0, 0, 512, 512});         //
  cube.get_side_texture(Render::CubeView::SIDES::D)          // C1
      .copy_rect_from(tex,                                   //
                      Render::Rect{512, 2 * 512, 512, 512},  //
                      Render::Rect{0, 0, 512, 512});         //
}

void Game::drag_callback(int x0, int y0, int x1, int y1) {
  printf("drag_callback(x0=%d, y0=%d, x1=%d, y1=%d)\n", x0, y0, x1, y1);
  if (x0 != x1 || y0 != y1) this->cube.apply_transform(VMath::SO3::Rotation(0.01, VMath::Vector3(y1 - y0, x0 - x1)));
}

void Game::click_callback(int x0, int y0, char b) { printf("click_callback(x0=%d, y0=%d, b='%c')\n", x0, y0, b); }
