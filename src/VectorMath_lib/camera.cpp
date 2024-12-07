#include "camera.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

#include "types.h"

using namespace VMath;
using namespace Camera;

//--------------------------- PERSPECTIVE PROJECTION ---------------------------

PerspectiveProjection::PerspectiveProjection(int screen_width, int screen_height, float angle, float scale) {
  this->angle = angle;
  w = screen_width;
  h = screen_height;
  scale_ = scale;
  float dist = 2 * w / std::tan(angle / 2);
  TO_CAMERA_COORDS = SO3::Translation(Vector3(0, 0, -dist));

  // f calculation:
  // ! assume cube size length equals 1
  // tg A == 1 / dist == min(w, h)*scale / f;
  //
  //   1          min(w, h) * scale
  // ------  ==  -------------------
  //  dist         internal_scale
  internal_scale = std::min(w, h) * scale * dist;
  this->SCREEN_0_OFFSET = Vector3(screen_width / 2.0, screen_height / 2.0, 0);
}

Point3 PerspectiveProjection::operator()(Point3 p) const {
#ifndef NDEBUG
  if (p.z <= 0) throw std::runtime_error("The point is behind the viewer!");
#endif  // !NDEBUG

  p = TO_CAMERA_COORDS * p;  // move camera to zero point
  p /= p.z;                  // Make the perspective
  p *= internal_scale;       // scale to screen space
  p += SCREEN_0_OFFSET;

#ifndef NDEBUG
  if (p.x < 0 || p.x >= w || p.y < 0 || p.y >= h)
    std::cerr << "[WARNING] offscreen point got in PerspectiveProjection(Vector3)\n";
#endif  // !NDEBUG

  return p;
}

Ray PerspectiveProjection::raycast(const Point3& screen_point) const {
  Point3 projection_point = (screen_point - SCREEN_0_OFFSET) / internal_scale;
  projection_point.z = 1;  // focal length

  Vector3 dir = projection_point - Point3::ZERO;  // to direction vector
  dir = ~TO_CAMERA_COORDS * dir;                  // to_global_space
  dir.normalize();                                // direction vector should be normalized

  return Ray{dir,                                //
             ~TO_CAMERA_COORDS * Point3::ZERO};  //
}

std::function<Point3(const Point3&)> PerspectiveProjection::get_screen2plane(Point3 a, Point3 b, Point3 c,  // screen
                                                                             Point3 A, Point3 B, Point3 C) const {
#ifndef NDEBUG
  if (a.z <= 0 || b.z <= 0 || c.z <= 0) throw std::runtime_error("Z not in screen space");
  if (cross(a - b, a - c).L2() < 1e-3) throw std::runtime_error("Triangle with zero space");
#endif  // !NDEBUG
  a *= a.z;
  b *= b.z;
  c *= c.z;
  Vector3 A0 = A - Point3::ZERO;
  Vector3 B0 = B - Point3::ZERO;
  Vector3 C0 = C - Point3::ZERO;
  return [=](const Point3& q) -> Point3 {
    const Vector3 qa = q - a;
    const Vector3 qb = q - b;
    const Vector3 qc = q - c;

    float kA = qb.x * qc.y - qb.y * qc.x;
    float kB = qc.x * qa.y - qc.y * qa.x;
    float kC = qa.x * qb.y - qa.y * qb.x;
    float L = kA + kB + kC;

    return Point3::ZERO + (kA * A0 + kB * B0 + kC * C0) / L;
  };
}

void PerspectiveProjection::resize(int w, int h) {
  this->w = w;
  this->h = h;
  float dist = 2 * w / std::tan(angle / 2);
  internal_scale = std::min(w, h) * scale * dist;
  TO_CAMERA_COORDS = SO3::Translation(Vector3(0, 0, -dist));
  this->SCREEN_0_OFFSET = Vector3(w / 2.0, h / 2.0, 0);
}

//---------------------------- ORTHOGONAL PROJECTION ---------------------------

OrthogonalProjection::OrthogonalProjection(int screen_width, int screen_height, float scale) {
  this->w = screen_width;
  this->h = screen_height;
  this->scale_ = scale;
  this->internal_scale = std::min(screen_width, screen_height) * scale;
  this->TO_CAMERA_COORDS = SO3(Vector3(0, 0, -5));
  this->SCREEN_0_OFFSET = Vector3(screen_width / 2.0, screen_height / 2.0, 0);
}

Point3 OrthogonalProjection::operator()(Point3 p) const {
  p = TO_CAMERA_COORDS * p;  // move camera to zero point
  p *= internal_scale;       // scale to screen space
  p += SCREEN_0_OFFSET;

#ifndef NDEBUG
  if (p.x < 0 || p.x >= w || p.y < 0 || p.y >= h)
    std::cerr << "[WARNING] offscreen point got in PerspectiveProjection(Vector3)\n";
#endif  // !NDEBUG
  return p;
}

Ray OrthogonalProjection::raycast(const Point3& screen_point) const {
  Point3 projection_point = (screen_point - SCREEN_0_OFFSET) / internal_scale;

  Vector3 dir{0, 0, 1};

  return Ray{~TO_CAMERA_COORDS * dir,                //
             ~TO_CAMERA_COORDS * projection_point};  //
}

std::function<Point3(const Point3&)> OrthogonalProjection::get_screen2plane(Point3 a, Point3 b, Point3 c,  // screen
                                                                            Point3 A, Point3 B, Point3 C) const {
#ifndef NDEBUG
  if (a.z <= 0 || b.z <= 0 || c.z <= 0) throw std::runtime_error("Z not in screen space");
  if (cross(a - b, a - c).L2() < 1e-3) throw std::runtime_error("Triangle with zero space");
#endif  // !NDEBUG
  Vector3 A0 = A - Point3::ZERO;
  Vector3 B0 = B - Point3::ZERO;
  Vector3 C0 = C - Point3::ZERO;
  return [=](const Point3& q) -> Point3 {
    const Vector3 qa = q - a;
    const Vector3 qb = q - b;
    const Vector3 qc = q - c;

    float kA = qb.x * qc.y - qb.y * qc.x;
    float kB = qc.x * qa.y - qc.y * qa.x;
    float kC = qa.x * qb.y - qa.y * qb.x;
    float L = kA + kB + kC;

    return Point3::ZERO + (kA * A0 + kB * B0 + kC * C0) / L;
  };
}

//---------------------------------- VIEWPORT ----------------------------------
