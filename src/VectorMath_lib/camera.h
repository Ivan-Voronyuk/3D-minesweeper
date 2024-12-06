#include <cmath>
#include <functional>

#include "types.h"

#ifndef VMATH_CAMERA
#define VMATH_CAMERA

using namespace VMath;

namespace Camera {

struct Ray {
  const Vector3 normal;
  const Vector3 start;
};

class CameraTransform {
 private:
  CameraTransform();

 public:
  virtual Vector3 operator()(const Vector3&) const;
  virtual std::function<Vector3(const Vector3&)> get_screen2plane(Vector3 A, Vector3 B, Vector3 C,  // global space
                                                                  Vector3 a, Vector3 b, Vector3 c)  // screen space
      const;
  virtual Ray raycast(const Vector3& screen_point) const;
};

class

}  // namespace Camera
#endif  // !VMATH_CAMERA
