#include <cassert>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <ios>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "VectorMath_lib/render.h"
#include "VectorMath_lib/types.h"

using namespace VMath;
using namespace Camera;
using namespace Render;

void types() {
  Vector3 V1{1, 2, 3};
  assert(V1.x == 1);
  assert(V1.y == 2);
  assert(V1.z == 3);

  Vector3 V2{4, 5};
  assert(V2.x == 4);
  assert(V2.y == 5);
  assert(V2.z == 0);

  Vector3 Dv{};
  printf("default Vector3: (%f, %f, %f)\n", Dv.x, Dv.y, Dv.z);

  std::cout << "Vector creation passed" << std::endl << std::endl;

  Point3 P1{1, 2, 3};
  assert(P1.x == 1);
  assert(P1.y == 2);
  assert(P1.z == 3);

  Point3 P2{4, 5};
  assert(P2.x == 4);
  assert(P2.y == 5);
  assert(P2.z == 0);

  Vector3 Dp{};
  printf("default Point3: (%f, %f, %f)\n", Dp.x, Dp.y, Dp.z);

  std::cout << "Point creation passed" << std::endl << std::endl;

  Quaternion Q1{1, 2, 3, 4};
  assert(Q1.w == 1);
  assert(Q1.x == 2);
  assert(Q1.y == 3);
  assert(Q1.z == 4);

  Quaternion Dq{};
  printf("default Quaternion: (%f, %f, %f, %f)\n", Dq.w, Dq.x, Dq.y, Dq.z);

  std::cout << "Quaternion createion passed" << std::endl << std::endl;

  Quaternion E1 = Q1 * ~Q1;
  Quaternion E2 = ~Q1 * Q1;

  printf("Q1 * ~Q1 = Quaternion{%f, %f, %f, %f}\n", E1.w, E1.x, E1.y, E1.z);
  printf("~Q1 * Q1 = Quaternion{%f, %f, %f, %f}\n", E2.w, E2.x, E2.y, E2.z);

  SO3 Tx1(Vector3(1, 0, 0));
  SO3 Rz45(Quaternion(std::cos(45. / 360 * 3.1415926535), Vector3(0, 0, 1) * sin(45. / 360 * 3.1415926535)));
  SO3 Tx2 = Tx1 * Tx1;
  SO3 Rz90 = Rz45 * Rz45;
  std::cout << "SO3 createion passed" << std::endl << std::endl;

  std::cout << "SO3 work tests:" << std::endl << std::endl;

  printf("V1 = (x=%f, y=%f, z=%f)\n", V1.x, V1.y, V1.z);
  printf("Tx1 * V1 = (x=%f, y=%f, z=%f)\n", (Tx1 * V1).x, (Tx1 * V1).y, (Tx1 * V1).z);
  printf("Tx1 * V1 = (x=%f, y=%f, z=%f)\n", (Tx2 * V1).x, (Tx2 * V1).y, (Tx2 * V1).z);
  printf("Rz45 * V1 = (x=%f, y=%f, z=%f)\n", (Rz45 * V1).x, (Rz45 * V1).y, (Rz45 * V1).z);
  printf("Rz90 * V1 = (x=%f, y=%f, z=%f)\n", (Rz90 * V1).x, (Rz90 * V1).y, (Rz90 * V1).z);
  printf("\n");
  printf("P1 = (x=%f, y=%f, z=%f)\n", P1.x, P1.y, P1.z);
  printf("Tx1 * P1 = (x=%f, y=%f, z=%f)\n", (Tx1 * P1).x, (Tx1 * P1).y, (Tx1 * P1).z);
  printf("Tx1 * P1 = (x=%f, y=%f, z=%f)\n", (Tx2 * P1).x, (Tx2 * P1).y, (Tx2 * P1).z);
  printf("Rz45 * P1 = (x=%f, y=%f, z=%f)\n", (Rz45 * P1).x, (Rz45 * P1).y, (Rz45 * P1).z);
  printf("~Rz45* P1 = (x=%f, y=%f, z=%f)\n", (~Rz45 * P1).x, (~Rz45 * P1).y, (~Rz45 * P1).z);
  printf("Rz90 * P1 = (x=%f, y=%f, z=%f)\n", (Rz90 * P1).x, (Rz90 * P1).y, (Rz90 * P1).z);

  P1 = Point3{1, 2, 3};
  SO3 R90_x1 = SO3::RotateAroundPoint(90. / 180 * 3.14159265, Vector3(0, 0, 1), Point3(1, 0, 0));
  printf("                P1 = (x=%f, y=%f, z=%f)\n", P1.x, P1.y, P1.z);
  printf("Rz90 over x=1 * P1 = (x=%f, y=%f, z=%f)\n", (R90_x1 * P1).x, (R90_x1 * P1).y, (R90_x1 * P1).z);

  // test for failure
  // Quaternion FQ = ~Quaternion(0, 0, 0, 0);
  // printf("~0 = Quaternion{%f, %f, %f, %f}\n", FQ.w, FQ.x, FQ.y, FQ.z);
}

Texture read_pnm(const char* fname) {
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

  Texture res{numcols, numrows};

  char* data = new char[numcols * numrows * 3];
  infile.read(data, numrows * numcols * 3);
  res.memcpy_from(reinterpret_cast<Color*>(data));
  delete[] data;

  infile.close();

  return res;
}
void write_pnm(const char* fname, const Texture& tex) {
  std::ofstream ofile(fname);
  ofile << "P6\n";
  ofile << tex.width << " " << tex.height << "\n";
  ofile << "255\n";

  char* data = new char[tex.width * tex.height * 3];
  tex.memcpy_to(reinterpret_cast<Color*>(data));
  ofile.write(data, tex.width * tex.height * 3);
  delete[] data;
}

void print_tex(const char* name, const Texture& tex) {
  printf("%s:\n", name);

  printf("+");
  for (int i = 0; i < tex.width - 1; ++i) printf("--------");
  printf("------+\n");

  for (int row = 0; row < tex.height; ++row) {
    printf("|");
    for (int col = 0; col < tex.width - 1; ++col) {
      Color c = tex.get_at(col, row);
      printf("%06x  ", (c.r << 16) + (c.g << 8) + c.b);
    }
    Color c = tex.get_at(tex.width - 1, row);
    printf("%06x|\n", (c.r << 16) + (c.g << 8) + c.b);
  }
  printf("+");
  for (int i = 0; i < tex.width - 1; ++i) printf("--------");
  printf("------+\n");
}

void texture() {
  Texture A{5, 5};
  print_tex("A", A);
  A.set_at(1, 2, Color{1, 2, 3});
  print_tex("A", A);

  Texture B{10, 16};
  for (unsigned char x = 0; x < 10; ++x)
    for (unsigned char y = 0; y < 16; ++y) B.set_at(x, y, Color{0, x, y});
  print_tex("B", B);

  print_tex("A before copy", A);
  B.copy_rect_to(Rect{0, 0, 2, 2}, Rect{0, 0, 2, 2}, A);
  print_tex("A after copy", A);
  B.copy_rect_to(Rect{0, 0, 3, 3}, Rect{1, 1, 3, 3}, A);
  print_tex("A after another copy", A);

  std::cerr << "Trying to load texture from pnm\n";
  Texture img = read_pnm("./texture.pnm");
  std::cerr << "Finished!\n";

  std::cerr << "Trying copy part of loadedd into B\n\n\n\n";
  print_tex("B", B);
  B.copy_rect_from(img, Rect{0, 0, 10, 16}, Rect{0, 0, 10, 16});
  print_tex("Left corner of image in B", B);

  // write_pnm("B.pnm", B);
}

void render() {
  Texture tex = read_pnm("./texture.pnm");
  CubeView cube{640, 480, 512, 0.5, 90. / 180 * 3.14159265359879};
  cube.get_side_texture(CubeView::SIDES::F)          // A0
      .copy_rect_from(tex,                           //
                      Rect{0, 0 * 512, 512, 512},    //
                      Rect{0, 0, 512, 512});         //
  cube.get_side_texture(CubeView::SIDES::R)          // B0
      .copy_rect_from(tex,                           //
                      Rect{0, 1 * 512, 512, 512},    //
                      Rect{0, 0, 512, 512});         //
  cube.get_side_texture(CubeView::SIDES::U)          // C0
      .copy_rect_from(tex,                           //
                      Rect{0, 2 * 512, 512, 512},    //
                      Rect{0, 0, 512, 512});         //
  cube.get_side_texture(CubeView::SIDES::B)          // A1
      .copy_rect_from(tex,                           //
                      Rect{512, 0 * 512, 512, 512},  //
                      Rect{0, 0, 512, 512});         //
  cube.get_side_texture(CubeView::SIDES::L)          // B1
      .copy_rect_from(tex,                           //
                      Rect{512, 1 * 512, 512, 512},  //
                      Rect{0, 0, 512, 512});         //
  cube.get_side_texture(CubeView::SIDES::D)          // C1
      .copy_rect_from(tex,                           //
                      Rect{512, 2 * 512, 512, 512},  //
                      Rect{0, 0, 512, 512});         //
  Canvas screen = cube.render();
  write_pnm("draw1.pnm", screen.tex);

  screen.clear();
  cube.apply_transform(SO3::Rotation(30 / 180. * 3.1415926535, Vector3{1, 0, 0}));
  cube.render(screen);
  write_pnm("draw2.pnm", screen.tex);

  screen.clear();
  cube.apply_transform(SO3::Rotation(30 / 180. * 3.1415926535, Vector3{0, -1, 0}));
  cube.render(screen);
  write_pnm("draw3.pnm", screen.tex);
}

int main() /* try */ {
  std::cout << "Types tests:" << std::endl << std::endl;
  types();
  std::cout << "\nTypes tests passed\n" << std::endl << std::endl;

  std::cout << "Texture tests:" << std::endl << std::endl;
  texture();
  std::cout << "\nTexture tests passed\n" << std::endl << std::endl;

  std::cout << "Render tests:" << std::endl << std::endl;
  render();
  std::cout << "\nRender tests passed\n" << std::endl << std::endl;

} /* catch (std::exception& e) {
  std::cerr << "[ERROR] The program finished with the following exception:" << std::endl;
  std::cerr << e.what() << std::endl;
  return 1;
} catch (...) {
  std::cerr << "Oops, something went wrong..." << std::endl;
  return 2;
} */
