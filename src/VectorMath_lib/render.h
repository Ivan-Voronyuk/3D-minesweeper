#ifndef VMATH_RENDER
#define VMATH_RENDER

#include <algorithm>
#include <cmath>
#include <cstdlib>

#include "camera.h"
#include "types.h"

namespace Render {

using namespace Camera;
using namespace VMath;

//------------------------------------------------------------------------------

struct Color {
  unsigned char r, g, b;
};

struct Rect {
  const int x0, y0;
  const int w, h;
};

//------------------------------------------------------------------------------

class Texture {
 private:
  int w = -1, h = -1;
  Color* data = nullptr;
  Color* const operator[](int row) const;

 public:
  const int& width = w;
  const int& height = h;
  Texture() = default;
  Texture(int w, int h);
  Texture(Texture& old) = delete;     // no copy allowed!
  Texture(Texture&& old);             // move constructor
  Texture& operator=(Texture&& old);  // move assignment

  Color get_at(int x, int y) const;
  Color sample_at(int x, int y) const;
  void set_at(int x, int y, const Color& c);
  void copy_rect_to(Rect source, Rect target, Texture& tex) const;
  void copy_rect_from(Texture& tex, Rect source, Rect target);
  void set_rect_with(Rect target, Color* data);
  void memcpy_to(Color* dst) const;
  void memcpy_from(Color* src);

  const unsigned char* unsafe_get_data_view() const { return reinterpret_cast<unsigned char*>(data); }

  ~Texture();

  friend class CubeView;
  friend class Canvas;
};
//------------------------------------------------------------------------------

class Canvas {
 private:
  int w = -1, h = -1;
  float* z = nullptr;
  float* const operator[](int row) const;

 public:
  Texture tex;
  const int& width = w;
  const int& height = h;
  Canvas() = default;
  Canvas(int w, int h);
  Canvas(Canvas& old) = delete;     // no copy allowed!
  Canvas(Canvas&& old);             // move constructor
  Canvas& operator=(Canvas&& old);  // move assignment

  void clear();

  static void DrawLine(Canvas& tex, int x0, int y0, int x1, int y1, Color color);
  static void DrawLine(Canvas& tex, Point3 A, Point3 B, Color color);

  friend class CubeView;
};

//------------------------------------------------------------------------------

struct Triangle {
  const int P1, P2, P3, T1, T2, T3;
};
struct Edge {
  const Triangle A;
  const Triangle B;
};

class CubeView {
 private:
  Texture sides[6];
  CameraTransform* view = nullptr;
  SO3 transform{Vector3{-0.5, -0.5, -0.5}};
  int cube_side;

  const Point3 VERTICES[8]{
      Point3(0, 0, 0),  //
      Point3(1, 0, 0),  //
      Point3(0, 0, 1),  //
      Point3(1, 0, 1),  //
      Point3(0, 1, 0),  //
      Point3(1, 1, 0),  //
      Point3(0, 1, 1),  //
      Point3(1, 1, 1),  //
  };
  const Point3 TEX_COORDS_NORMALIZED[4]{
      Point3(0, 0),
      Point3(1, 0),
      Point3(1, 1),
      Point3(0, 1),
  };
  const Edge TRIANGLE_IDS[6]{
      Triangle{0, 1, 5, 0, 1, 2},  // F
      Triangle{0, 4, 5, 0, 3, 2},  // F
      Triangle{3, 6, 2, 0, 2, 1},  // B
      Triangle{3, 6, 7, 0, 2, 3},  // B
      Triangle{2, 4, 0, 0, 2, 1},  // L
      Triangle{2, 4, 6, 0, 2, 3},  // L
      Triangle{1, 3, 7, 0, 1, 2},  // R
      Triangle{1, 7, 5, 0, 2, 3},  // R
      Triangle{4, 6, 7, 0, 3, 2},  // U
      Triangle{4, 5, 7, 0, 1, 2},  // U
      Triangle{2, 1, 3, 0, 2, 1},  // D
      Triangle{2, 1, 0, 0, 2, 3},  // D
  };

 public:
  enum class SIDES { F, B, L, R, U, D };
  const SO3& current_transform = transform;

  CubeView() = default;             // default init with nullptr. Dubug handles this
  CubeView(CubeView&) = delete;     // no copy allowed
  CubeView(CubeView&&);             // move constructor
  CubeView& operator=(CubeView&&);  // move assignment

  CubeView(int screen_w, int screen_h, int cube_side, float scale);
  CubeView(int screen_w, int screen_h, int cube_side, float scale, float angle);
  Texture& get_side_texture(SIDES side);
  void apply_transform(const SO3& transform);
  void set_size();

  void render(Canvas& canvas) const;
  Canvas render() const;

  Ray raycast(float x, float y) { return view->raycast(Point3(x, y)); }

  ~CubeView();
};

}  // namespace Render

#endif  // !VMATH_RENDER
