#include <cmath>
#include <functional>

#include "types.h"

#ifndef VMATH_CAMERA
#define VMATH_CAMERA

namespace VMath {
namespace Camera {

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
  const float &wisth = w, &height = h, &scale = scale_;
  virtual Point3 operator()(Point3) const;
  virtual std::function<Point3(const Point3&)> get_screen2plane(Point3 a, Point3 b, Point3 c,  // screen space
                                                                Point3 A, Point3 B, Point3 C)  // global space
      const;
  virtual Ray raycast(const Point3& screen_point) const;
  virtual void resize(int w, int h);
};

//------------------------------------------------------------------------------

class PerspectiveProjection : CameraTransform {
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
  std::function<Point3(const Point3&)> get_screen2plane(Point3 a, Point3 b, Point3 c,  // screen space
                                                        Point3 A, Point3 B, Point3 C)  // global space
      const override;
  void resize(int w, int h) override;
};

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class OrthogonalProjection : CameraTransform {
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
  std::function<Point3(const Point3&)> get_screen2plane(Point3 a, Point3 b, Point3 c,  // screen space
                                                        Point3 A, Point3 B, Point3 C)  // global space
      const override;
  void resize(int w, int h) override;
};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

class Viewport {
 private:
  int w = -1, h = -1;
  CameraTransform* transform = nullptr;

 public:
  const int& width = w;
  const int& height = h;
  Viewport(int w, int h, float scale);
  Viewport(Viewport&& old);
  const CameraTransform& get_transform();
};

}  // namespace Camera
}  // namespace VMath
#endif  // !VMATH_CAMERA
