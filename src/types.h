#ifndef VMATH_TYPES
#define VMATH_TYPES

#include <cmath>

namespace VMath {

//------------------------------------------------------------------------------

struct Vector3 {
  float x = 0, y = 0, z = 0;
  bool t = TYPE::VECTOR;
  enum TYPE : bool { VECTOR = false, POINT = true };

  Vector3() = default;  // default constructor
  explicit Vector3(float x, float y, float z) : x(x), y(y), z(z), t(TYPE::VECTOR){};
  explicit Vector3(float x, float y, float z, bool t) : x(x), y(y), z(z), t(t){};

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

struct Quaternion {
  float w = 0, x = 0, y = 0, z = 0;

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
  Vector3 xyzt(bool t) const;
  Vector3 vec(bool t) const { return this->xyzt(t); }

};

Quaternion fromAxisAngle(const Vector3& axis, float angle);

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
  SO3(const Quaternion& Q) : Q(Q), T() {}
  SO3(const Vector3& T) : Q(), T(T) {}
  SO3(const Quaternion& Q, const Vector3& T) : Q(Q), T(T) {}

  static SO3 Translation(const Vector3& T) { return SO3(T); }
  static SO3 Rotation(const Quaternion& Q) { return SO3(Q); }

  SO3 operator*=(const SO3& more_recent);

  SO3 operator*(const SO3& Rhs) const;
  Vector3 operator*(const Vector3& V) const;

  void inv();
  SO3 operator~() const;
};

}  // namespace VMath

#endif  // !VMATH_TYPES
