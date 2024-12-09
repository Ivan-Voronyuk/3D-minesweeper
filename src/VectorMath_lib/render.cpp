#include "render.h"

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "types.h"

using namespace VMath;
using namespace Camera;
using namespace Render;

//----------------------------------- TEXTURE ------------------------------------

Texture::Texture(int w, int h) {
#ifndef NDEBUG
  assert(w > 0);
  assert(h > 0);
#endif  // !NDEBUG
  this->w = w;
  this->h = h;
  data = new Color[w * h];
}
Texture::Texture(Texture&& old) {
  if (this == &old) {
#ifndef NDEBUG
    std::cerr << "[ERROR] creating texture from itself";
#endif  // !NDEBUG
    return;
  }

  this->w = old.w;
  this->h = old.h;
  this->data = old.data;

  old.data = nullptr;
  old.w = -1;
  old.h = -1;
}

Texture& Texture::operator=(Texture&& old) {
  if (this == &old) {
#ifndef NDEBUG
    std::cerr << "[WARNING] assigning texture to itself";
#endif  // !NDEBUG
    return *this;
  }

  delete data;

  this->w = old.w;
  this->h = old.h;
  this->data = old.data;

  old.data = nullptr;
  old.w = -1;
  old.h = -1;

  return *this;
}

Color* const Texture::operator[](int row) const { return this->data + row * w; }

Color Texture::get_at(int x, int y) const {
#ifndef NDEBUG
  if (x < 0 || y < 0 || x >= w || y >= h) throw std::runtime_error("index out of bounds");
  if (!data) throw std::runtime_error("object is not properly initialized!");
#endif  // !NDEBUG
  return data[y * w + x];
}
Color Texture::sample_at(int x, int y) const {
#define CLIP(v, l, r) (v < l ? l : (v > r ? r : v))

#ifndef NDEBUG
  if (y < -h / 10 || y > h * 11 / 10)
    std::cerr << "[WARNING] y OOB in sample_at is too big for rounding error :" << y << "[" << h << "]\n";
  if (x < -w / 10 || x > w * 11 / 10)
    std::cerr << "[WARNING] x OOB in sample_at is too big for rounding error :" << x << "[" << w << "]\n";
  if (!data) throw std::runtime_error("object is not properly initialized!");
#endif  // !NDEBUG
  return data[CLIP(y, 0, h - 1) * w + CLIP(x, 0, w - 1)];
}
void Texture::set_at(int x, int y, const Color& c) {
#ifndef NDEBUG
  if (x < 0 || y < 0 || x >= w || y >= h) throw std::runtime_error("index out of bounds");
  if (!data) throw std::runtime_error("object is not properly initialized!");
#endif  // !NDEBUG
  data[y * w + x] = c;
}
void Texture::copy_rect_to(Rect source, Rect target, Texture& target_tex) const {
#ifndef NDEBUG
  if (!data) throw std::runtime_error("object is not properly initialized!");
  if (source.x0 < 0 || source.y0 < 0 || source.x0 >= w || source.y0 >= h)
    throw std::runtime_error("source out of bounds");
  if (source.x0 + source.w < 0 || source.y0 + source.h < 0 || source.x0 + source.w >= w || source.y0 + source.h >= h)
    throw std::runtime_error("source out of bounds");

  if (target.x0 < 0 || target.y0 < 0 || target.x0 >= target_tex.w || target.y0 >= target_tex.h)
    throw std::runtime_error("target out of bounds");
  if (source.x0 + source.w < 0 || source.y0 + source.h < 0 || source.x0 + source.w > target_tex.w ||
      source.y0 + source.h > target_tex.h)
    throw std::runtime_error("target out of bounds");
  if (source.w != target.w || source.h != target.h) throw std::runtime_error("sizes not equal");
#endif  // !NDEBUG

  for (int delta_row = 0; delta_row < source.h; ++delta_row)
    std::memcpy(target_tex[target.y0 + delta_row] + target.x0,  //
                (*this)[source.y0 + delta_row] + source.x0,     //
                sizeof(Color[source.w]));
}
void Texture::copy_rect_from(Texture& source_tex, Rect source, Rect target) {
#ifndef NDEBUG
  if (source.x0 < 0 || source.y0 < 0 || source.x0 >= source_tex.w || source.y0 >= source_tex.h)
    throw std::runtime_error("source out of bounds");
  if (source.x0 + source.w < 0 || source.y0 + source.h < 0 || source.x0 + source.w > source_tex.w ||
      source.y0 + source.h > source_tex.h)
    throw std::runtime_error("source out of bounds");

  if (target.x0 < 0 || target.y0 < 0 || target.x0 >= this->w || target.y0 >= this->h)
    throw std::runtime_error("target out of bounds");
  if (target.x0 + target.w < 0 || target.y0 + target.h < 0 || target.x0 + target.w > this->w ||
      target.y0 + target.h > this->h)
    throw std::runtime_error("target out of bounds");
  if (source.w != target.w || source.h != target.h) throw std::runtime_error("sizes not equal");
  if (!data) throw std::runtime_error("object is not properly initialized!");
#endif  // !NDEBUG

  for (int delta_row = 0; delta_row < source.h; ++delta_row)
    std::memcpy((*this)[target.y0 + delta_row] + target.x0,     //
                source_tex[source.y0 + delta_row] + source.x0,  //
                sizeof(Color[source.w]));
}
void Texture::set_rect_with(Rect target, Color* data) {
#ifndef NDEBUG
  if (!this->data) throw std::runtime_error("object is not properly initialized!");
  if (data == nullptr) throw std::runtime_error("cannot copy from nullptr data");
#endif  // !NDEBUG

  for (int delta_row = 0; delta_row < target.w; ++delta_row)
    std::memcpy((*this)[target.y0 + delta_row] + target.x0,             //
                data + (target.y0 + delta_row) * target.w + target.x0,  //
                sizeof(Color[target.w]));
}
void Texture::memcpy_to(Color* dst) const {
#ifndef NDEBUG
  if (!data) throw std::runtime_error("object is not properly initialized!");
  if (dst == nullptr) throw std::runtime_error("cannot copy to nullptr dst");
#endif  // !NDEBUG
  std::memcpy(dst, this->data, sizeof(Color[w * h]));
}
void Texture::memcpy_from(Color* src) {
#ifndef NDEBUG
  if (!data) throw std::runtime_error("object is not properly initialized!");
  if (src == nullptr) throw std::runtime_error("cannot copy from nullptr src");
#endif  // !NDEBUG
  std::memcpy(this->data, src, sizeof(Color[w * h]));
}

Texture::~Texture() { delete data; }

//----------------------------------- CANVAS ------------------------------------

Canvas::Canvas(int w, int h) {
#ifndef NDEBUG
  assert(w > 0);
  assert(h > 0);
#endif  // !NDEBUG
  this->w = w;
  this->h = h;
  z = new float[w * h];
  tex = Texture{w, h};
}
Canvas::Canvas(Canvas&& old) {
  if (this == &old) {
#ifndef NDEBUG
    std::cerr << "[ERROR] creating canvas from itself";
#endif  // !NDEBUG
    return;
  }

  this->w = old.w;
  this->h = old.h;
  this->z = old.z;

  old.z = nullptr;
  old.w = -1;
  old.h = -1;

  tex = std::move(old.tex);
}

Canvas& Canvas::operator=(Canvas&& old) {
  if (this == &old) {
#ifndef NDEBUG
    std::cerr << "[WARNING] assigning canvas to itself";
#endif  // !NDEBUG
    return *this;
  }

  delete z;

  this->w = old.w;
  this->h = old.h;
  this->z = old.z;

  old.z = nullptr;
  old.w = -1;
  old.h = -1;

  tex = std::move(old.tex);

  return *this;
}

float* const Canvas::operator[](int row) const { return this->z + row * w; }

void Canvas::DrawLine(Canvas& canvas, int x0, int y0, int x1, int y1, Color color) {
  int L = std::max(std::abs(x1 - x0), std::abs(y1 - y0));
  for (int i = 0; i < L; ++i) {
    const int x = x0 + (x1 - x0) * i / L;
    const int y = y0 + (y1 - y0) * i / L;
    if (x < 0 || x >= canvas.width || y < 0 || y >= canvas.height) break;
    canvas.tex.set_at(x, y, color);
  }
}
void Canvas::DrawLine(Canvas& canvas, Point3 A, Point3 B, Color color) {
  int L = std::max(std::abs(A.x - B.x), std::abs(A.y - B.y));
  for (int i = 0; i < L; ++i) {
    const Point3 p = A + (B - A) * i / L;
    const int x = p.x, y = p.y;
    const float z = p.z;
    if (x < 0 || x >= canvas.width || y < 0 || y >= canvas.height) break;
    if (z > canvas[y][x]) canvas.tex.set_at(x, y, color);
  }
}

void Canvas::clear(const Color c) {
#ifndef NDEBUG
  if (!this->z) throw std::runtime_error("canvas was not properly initialized");
#endif  // !NDEBUG
  std::fill(z, z + w * h, 0);
  std::fill(tex.data, tex.data + w * h, c);
}
//---------------------------------- CUBE VIEW ---------------------------------
CubeView::CubeView(int screen_w, int screen_h, int cube_side, float scale) {
  view = new OrthogonalProjection(screen_w, screen_h, scale);
  this->cube_side = cube_side;
  for (int i = 0; i < 6; ++i) {
    this->sides[i] = Texture(cube_side, cube_side);
  }
}
CubeView::CubeView(int screen_w, int screen_h, int cube_side, float scale, float angle) {
  view = new PerspectiveProjection(screen_w, screen_h, angle, scale);
  this->cube_side = cube_side;
  for (int i = 0; i < 6; ++i) {
    this->sides[i] = Texture(cube_side, cube_side);
  }
}
Texture& CubeView::get_side_texture(SIDES side) { return sides[static_cast<int>(side)]; }
void CubeView::apply_transform(const SO3& transform) { this->transform *= transform; }

void CubeView::render(Canvas& canvas) const {
  for (int SIDE = 0; SIDE < 6; ++SIDE) {
    Point3 P1 = view->operator()(transform * CubeView::VERTICES[CubeView::TRIANGLE_IDS[SIDE].A.P1]);
    Point3 P2 = view->operator()(transform * CubeView::VERTICES[CubeView::TRIANGLE_IDS[SIDE].A.P2]);
    Point3 P3 = view->operator()(transform * CubeView::VERTICES[CubeView::TRIANGLE_IDS[SIDE].A.P3]);

    if (P1.x == P2.x && P1.y == P2.y) continue;
    if (P2.x == P3.x && P2.y == P3.y) continue;
    if (P1.x == P3.x && P1.y == P3.y) continue;

    Point3 T1 = CubeView::TEX_COORDS_NORMALIZED[CubeView::TRIANGLE_IDS[SIDE].A.T1] * (cube_side - 1);
    Point3 T2 = CubeView::TEX_COORDS_NORMALIZED[CubeView::TRIANGLE_IDS[SIDE].A.T2] * (cube_side - 1);
    Point3 T3 = CubeView::TEX_COORDS_NORMALIZED[CubeView::TRIANGLE_IDS[SIDE].A.T3] * (cube_side - 1);

    auto tex_coord_map = CubeView::view->get_map_tex_coord(P1, P2, P3, T1, T2, T3);

    if (P1.y > P2.y) std::swap(P1, P2);
    if (P1.y > P3.y) std::swap(P1, P3);
    if (P2.y > P3.y) std::swap(P2, P3);
    // P1.y < P2.y < P3.y
    float H1 = P2.y - P1.y;
    float H2 = P3.y - P2.y;
    for (int y = std::max(P1.y, 0.f); y < std::min(P3.y, canvas.h - 1.f); ++y) {
      int x1;
      if (H2 < 1 || y <= P2.y && H1 > 1)
        x1 = P1.x + (P2.x - P1.x) * (y - P1.y) / H1;
      else
        x1 = P2.x + (P3.x - P2.x) * (y - P1.y - H1) / H2;
      int x2 = P1.x + (P3.x - P1.x) * (y - P1.y) / (H1 + H2);

      if (x1 > x2) std::swap(x1, x2);
      for (int x = std::max(x1, 0); x < std::min(x2, canvas.w - 1); ++x) {
        Point3 tex_coords = tex_coord_map(x, y);
        if (tex_coords.z > canvas[y][x]) {
          canvas.tex.set_at(x, y, sides[SIDE].sample_at((int)tex_coords.x, (int)tex_coords.y));
          canvas[y][x] = tex_coords.z;
        }
      }
    }
    //----------------------------------------------------------------------------------------------------
    P1 = view->operator()(transform * CubeView::VERTICES[CubeView::TRIANGLE_IDS[SIDE].B.P1]);
    P2 = view->operator()(transform * CubeView::VERTICES[CubeView::TRIANGLE_IDS[SIDE].B.P2]);
    P3 = view->operator()(transform * CubeView::VERTICES[CubeView::TRIANGLE_IDS[SIDE].B.P3]);

    if (P1.x == P2.x && P1.y == P2.y) continue;
    if (P2.x == P3.x && P2.y == P3.y) continue;
    if (P1.x == P3.x && P1.y == P3.y) continue;

    T1 = CubeView::TEX_COORDS_NORMALIZED[CubeView::TRIANGLE_IDS[SIDE].B.T1] * (cube_side - 1);
    T2 = CubeView::TEX_COORDS_NORMALIZED[CubeView::TRIANGLE_IDS[SIDE].B.T2] * (cube_side - 1);
    T3 = CubeView::TEX_COORDS_NORMALIZED[CubeView::TRIANGLE_IDS[SIDE].B.T3] * (cube_side - 1);

    tex_coord_map = CubeView::view->get_map_tex_coord(P1, P2, P3, T1, T2, T3);

    if (P1.y > P2.y) {
      std::swap(P1, P2);
      std::swap(T1, T2);
    }
    if (P1.y > P3.y) {
      std::swap(P1, P3);
      std::swap(T1, T3);
    }
    if (P2.y > P3.y) {
      std::swap(P2, P3);
      std::swap(T2, T3);
    }
    // P1.y < P2.y < P3.y
    H1 = P2.y - P1.y;
    H2 = P3.y - P2.y;
    for (int y = std::max(P1.y, 0.f); y < std::min(P3.y, canvas.h - 1.f); ++y) {
      int x1;
      if (H2 < 1 || y <= P2.y && H1 > 1)
        x1 = P1.x + (P2.x - P1.x) * (y - P1.y) / H1;
      else
        x1 = P2.x + (P3.x - P2.x) * (y - P1.y - H1) / H2;
      int x2 = P1.x + (P3.x - P1.x) * (y - P1.y) / (H1 + H2);

      if (x1 > x2) std::swap(x1, x2);
      for (int x = std::max(x1, 0); x < std::min(x2, canvas.w - 1); ++x) {
        Point3 tex_coords = tex_coord_map(x, y);
        if (tex_coords.z > canvas[y][x]) {
          canvas.tex.set_at(x, y, sides[SIDE].sample_at((int)tex_coords.x, (int)tex_coords.y));
          canvas[y][x] = tex_coords.z;
        }
      }
    }
  }
}
Canvas CubeView::render() const {
#ifndef NDEBUG
  if (!this->view) throw std::runtime_error("Object is not properly initialized");
#endif  // !NDEBUG
  Canvas canvas{static_cast<int>(this->view->width), static_cast<int>(this->view->height)};
  this->render(canvas);
  return canvas;
}

CubeView::~CubeView() { delete view; }
