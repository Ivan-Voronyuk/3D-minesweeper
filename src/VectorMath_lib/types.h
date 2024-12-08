#ifndef VMATH_TYPES
#define VMATH_TYPES

#include <cmath>

namespace VMath {

//------------------------------------------------------------------------------
struct Vector3 {
  float x = 0, y = 0, z = 0;

  Vector3() = default;  // default constructor
  explicit Vector3(float x, float y, float z = 0) : x(x), y(y), z(z){};

  static const Vector3 ZERO() { return Vector3(0, 0, 0); };

  Vector3& operator+=(const Vector3& other);
  Vector3& operator-=(const Vector3& other);
  Vector3& operator*=(float other);
  Vector3& operator/=(float other);

  Vector3 operator-() const;

  float len() const;
  float L2() const;

  void normalize();
  Vector3 normalized() const;
};

Vector3 operator+(const Vector3& A, const Vector3& B);
Vector3 operator-(const Vector3& A, const Vector3& B);
Vector3 operator*(float k, const Vector3& A);
Vector3 operator*(const Vector3& A, float k);

Vector3 operator/(float k, const Vector3& A);
Vector3 operator/(const Vector3& A, float k);

float dot(const Vector3& A, const Vector3& B);
Vector3 cross(const Vector3& A, const Vector3& B);
Vector3 normalize(const Vector3& V);

//------------------------------------------------------------------------------

struct Point3 {
  float x = 0, y = 0, z = 0;

  Point3() = default;  // default constructor
  explicit Point3(float x, float y, float z = 0) : x(x), y(y), z(z){};

  static const Point3 ZERO() { return Point3(0, 0, 0); };

  Point3& operator+=(const Vector3& other);
  Point3& operator-=(const Vector3& other);
  Point3& operator*=(float other);
  Point3& operator/=(float other);

  Point3 operator-() const;
};
Point3 operator*(float k, const Point3& A);
Point3 operator*(const Point3& A, float k);
Point3 operator/(float k, const Point3& A);
Point3 operator/(const Point3& A, float k);

//------------------------------------------------------------------------------

Point3 operator+(const Point3& A, const Vector3& B);
Point3 operator+(const Vector3& A, const Point3& B);
Point3 operator-(const Point3& A, const Vector3& B);
Vector3 operator-(const Point3& A, const Point3& B);

//------------------------------------------------------------------------------

struct Quaternion {
  float w = 1, x = 0, y = 0, z = 0;

  Quaternion() = default;
  Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z){};
  Quaternion(float w, const Vector3& xyz) : w(w), x(xyz.x), y(xyz.y), z(xyz.z){};
  explicit Quaternion(const Vector3& xyz) : w(0), x(xyz.x), y(xyz.y), z(xyz.z){};

  Quaternion& operator+=(const Quaternion& other);
  Quaternion& operator-=(const Quaternion& other);
  Quaternion& operator*=(float other);
  Quaternion& operator/=(float other);

  Quaternion operator-() const;

  float L2() const;
  float len() const;

  void normalize();
  Quaternion normalized() const;

  void inv();
  Quaternion operator~() const;

  Vector3 xyz() const;
  Vector3 vec() const { return this->xyz(); }
};
Quaternion operator+(const Quaternion& A, const Quaternion& B);
Quaternion operator-(const Quaternion& A, const Quaternion& B);
Quaternion operator/(const Quaternion& A, float other);
Quaternion operator*(const Quaternion& A, float other);
Quaternion operator*(const Quaternion& A, const Quaternion& B);
Quaternion normalize(const Quaternion& Q);

//------------------------------------------------------------------------------

class SO3 {
 private:
  Quaternion Q;
  Vector3 T;

 public:
  SO3() = default;
  SO3(const SO3&) = default;
  SO3(const Quaternion& Q) : Q(Q), T(0, 0, 0) {}
  SO3(const Vector3& T) : Q(1, 0, 0, 0), T(T) {}
  SO3(const Quaternion& Q, const Vector3& T) : Q(Q), T(T) {}

  static SO3 Translation(const Vector3& T) { return SO3(T); }
  static SO3 Rotation(const Quaternion& Q) { return SO3(Q); }
  static SO3 Rotation(float angle, const Vector3& axe) {
    return SO3(Quaternion(std::cos(angle / 2), axe.normalized() * std::sin(angle / 2)));
  }

  static SO3 RotateAroundPoint(float angle, const Vector3& axe, const Point3& point);
  static SO3 RotateAroundPoint(const Quaternion& Q, const Point3& point);

  SO3 operator*=(const SO3& more_recent);

  SO3 operator*(const SO3& Rhs) const;
  Vector3 operator*(const Vector3& V) const;
  Point3 operator*(const Point3& V) const;

  void inv();
  SO3 operator~() const;
};

}  // namespace VMath

#endif  // !VMATH_TYPES
