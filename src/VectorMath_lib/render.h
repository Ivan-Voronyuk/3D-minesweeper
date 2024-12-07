#ifndef VMATH_RENDER
#define VMATH_RENDER

#include <cmath>

#include "camera.h"
#include "types.h"

using namespace VMath;
using namespace Camera;

namespace Render {

struct Color {
  const char r, g, b;
};

struct Rect {
  const int x0, y0;
  const int w, h;
};

class Texture {
 private:
  int w = -1, h = -1;
  Color* data = nullptr;
  Color* const operator[](int row);

 public:
  Texture(int w, int h);
  Texture(Texture& old);   // copy
  Texture(Texture&& old);  // move

  Color get_at(int x, int y) const;
  void set_at(int x, int y, Color c);
  void copy_rect_to(Rect source, Rect target, Texture tex) const;
  void copy_rect_from(Texture tex, Rect source, Rect target);
  void set_rect_with(Rect target, Color* data);
  void memcpy_to(Color* out) const;

  ~Texture();

  friend class CubeView;
};

class CubeView {
 private:
  Texture sides[6];
  Texture canvas;  // doublebuff ?
  Viewport view;

 public:
  CubeView();
  CubeView(CubeView&);
  CubeView(CubeView&&);
  enum SIDES : int { U, D, L, R, F, B };
  const Texture& out_image = canvas;

  CubeView(int screen_w, int screen_h, int cube_side, float scale);
  Texture& get_side_texture(SIDES side) const;
  void apply_transform(const SO3& transform);
  const Texture& render();
  void resize();

  ~CubeView();
};

}  // namespace Render

#endif  // !VMATH_RENDER
