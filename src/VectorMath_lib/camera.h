#ifndef VMATH_CAMERA
#define VMATH_CAMERA

#include <cmath>
#include <functional>

#include "types.h"

namespace Camera {
using namespace VMath;

//------------------------------------------------------------------------------

struct Ray {
  const Vector3 direction;
  const Point3 beginning;
};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

class CameraTransform {
 protected:
  float w = -1, h = -1, scale_ = 0;
  Vector3 SCREEN_0_OFFSET{0, 0, 0};  // a real usable value
  SO3 TO_CAMERA_COORDS;
  float internal_scale = 0;
  CameraTransform() = default;

 public:
  const float &width = w, &height = h, &scale = scale_;
  virtual Point3 operator()(Point3) const = 0;
  virtual std::function<Point3(float x, float y)> get_map_tex_coord(Point3 a, Point3 b, Point3 c,  // screen space
                                                                    Point3 A, Point3 B, Point3 C)  // tex space
      const = 0;
  virtual Ray raycast(const Point3& screen_point) const = 0;
  virtual void resize(int w, int h) = 0;
  virtual ~CameraTransform() {}
};

//------------------------------------------------------------------------------

class PerspectiveProjection : public CameraTransform {
 private:
  /*
    float w;
    float h;
    float scale;
  */
  float angle;

 public:
  // const float &wisth = w, &height = h, &scale = s;
  PerspectiveProjection(int screen_width, int screen_height, float angle, float scale);
  Point3 operator()(Point3) const override;
  Ray raycast(const Point3& screen_point) const override;
  std::function<Point3(float x, float y)> get_map_tex_coord(Point3 a, Point3 b, Point3 c,  // screen space
                                                            Point3 A, Point3 B, Point3 C)  // global space
      const override;
  void resize(int w, int h) override;
};

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class OrthogonalProjection : public CameraTransform {
 private:
  /*
    float w;
    float h;
    float scale;
  */

 public:
  // const float &wisth = w, &height = h, &scale = s;
  OrthogonalProjection(int screen_width, int screen_height, float scale);
  Point3 operator()(Point3 p) const override;
  Ray raycast(const Point3& screen_point) const override;
  std::function<Point3(float x, float y)> get_map_tex_coord(Point3 a, Point3 b, Point3 c,  // screen space
                                                            Point3 A, Point3 B, Point3 C)  // global space
      const override;
  void resize(int w, int h) override;
};

}  // namespace Camera
#endif  // !VMATH_CAMERA
