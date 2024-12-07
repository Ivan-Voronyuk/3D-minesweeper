#include "types.h"

#include <cmath>
#include <stdexcept>

using namespace VMath;

//------------------------------------------------------------------------------

Vector3& Vector3::operator+=(const Vector3& other) {
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;
  return *this;
}
Vector3& Vector3::operator-=(const Vector3& other) {
  this->x -= other.x;
  this->y -= other.y;
  this->z -= other.z;
  return *this;
}
Vector3& Vector3::operator*=(float other) {
  this->x *= other;
  this->y *= other;
  this->z *= other;
  return *this;
}
Vector3& Vector3::operator/=(float other) {
  this->x /= other;
  this->y /= other;
  this->z /= other;
  return *this;
}

Vector3 Vector3::operator-() const { return Vector3(-x, -y, -z); }

float Vector3::L2() const { return x * x + y * y + z * z; }
float Vector3::len() const { return std::sqrt(this->L2()); }

void Vector3::normalize() { *this /= this->len(); }
Vector3 Vector3::normalized() const { return *this / this->len(); }

Vector3 VMath::operator+(const Vector3& A, const Vector3& B) { return Vector3(A.x + B.x, A.y + B.y, A.z + B.z); }
Vector3 VMath::operator-(const Vector3& A, const Vector3& B) { return Vector3(A.x - B.x, A.y - B.y, A.z - B.z); }
Vector3 VMath::operator*(float k, const Vector3& A) { return Vector3(A.x * k, A.y * k, A.z * k); }
Vector3 VMath::operator*(const Vector3& A, float k) { return Vector3(A.x * k, A.y * k, A.z * k); }
Vector3 VMath::operator/(float k, const Vector3& A) { return Vector3(A.x / k, A.y / k, A.z / k); }
Vector3 VMath::operator/(const Vector3& A, float k) { return Vector3(A.x / k, A.y / k, A.z / k); }

float VMath::dot(const Vector3& A, const Vector3& B) { return A.x * B.x + A.y * B.y + A.z * B.z; }
Vector3 VMath::cross(const Vector3& A, const Vector3& B) {
  return Vector3(A.y * B.z - A.z * B.y, A.z * B.x - B.z * A.x, A.x * B.y - A.y * B.x);
}

Vector3 VMath::normalize(const Vector3& V) { return V / V.len(); }

//------------------------------------------------------------------------------

Point3& Point3::operator+=(const Vector3& other) {
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;
  return *this;
}
Point3& Point3::operator-=(const Vector3& other) {
  this->x -= other.x;
  this->y -= other.y;
  this->z -= other.z;
  return *this;
}
Point3& Point3::operator*=(float other) {
  this->x *= other;
  this->y *= other;
  this->z *= other;
  return *this;
}
Point3& Point3::operator/=(float other) {
  this->x /= other;
  this->y /= other;
  this->z /= other;
  return *this;
}

Point3 Point3::operator-() const { return Point3(-x, -y, -z); }

Point3 VMath::operator*(float k, const Point3& A) { return Point3(A.x * k, A.y * k, A.z * k); }
Point3 VMath::operator*(const Point3& A, float k) { return Point3(A.x * k, A.y * k, A.z * k); }
Point3 VMath::operator/(float k, const Point3& A) { return Point3(A.x / k, A.y / k, A.z / k); }
Point3 VMath::operator/(const Point3& A, float k) { return Point3(A.x / k, A.y / k, A.z / k); }

//------------------------------------------------------------------------------

Point3 operator+(const Point3& A, const Vector3& B) { return Point3(A.x + B.x, A.y + B.y, A.z + B.z); }
Point3 operator+(const Vector3& A, const Point3& B) { return Point3(A.x + B.x, A.y + B.y, A.z + B.z); }
Point3 operator-(const Point3& A, const Vector3& B) { return Point3(A.x - B.x, A.y - B.y, A.z - B.z); }
Vector3 operator-(const Point3& A, const Point3& B) { return Vector3(A.x - B.x, A.y - B.y, A.z - B.z); }

//------------------------------------------------------------------------------

Quaternion& Quaternion::operator+=(const Quaternion& other) {
  w += other.w;
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}
Quaternion& Quaternion::operator-=(const Quaternion& other) {
  w -= other.w;
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}
Quaternion& Quaternion::operator*=(float other) {
  w *= other;
  x *= other;
  y *= other;
  z *= other;
  return *this;
}
Quaternion& Quaternion::operator/=(float other) {
  w /= other;
  x /= other;
  y /= other;
  z /= other;
  return *this;
}
Quaternion Quaternion::operator-() const { return Quaternion(-w, -x, -y, -z); }

float Quaternion::L2() const { return x * x + y * y + z * z + w * w; }
float Quaternion::len() const { return std::sqrt(this->L2()); }

void Quaternion::normalize() { *this /= this->len(); }
Quaternion Quaternion::normalized() const { return *this / this->len(); }

void Quaternion::inv() {
  x = -x;
  y = -y;
  z = -z;
  *this /= this->L2();
}
Quaternion Quaternion::operator~() const {
  Quaternion res{w, -x, -y, -z};
  return res / res.L2();
}
Vector3 Quaternion::xyz() const { return Vector3(x, y, z); }

Quaternion VMath::operator+(const Quaternion& A, const Quaternion& B) {
  return Quaternion(A.w + B.w, A.x + B.x, A.y + B.y, A.z + B.z);
}
Quaternion VMath::operator-(const Quaternion& A, const Quaternion& B) {
  return Quaternion(A.w - B.w, A.x - B.x, A.y - B.y, A.z - B.z);
}
Quaternion VMath::operator/(const Quaternion& A, float other) {
  return Quaternion(A.w / other, A.x / other, A.y / other, A.z / other);
}
Quaternion VMath::operator*(const Quaternion& A, float other) {
  return Quaternion(A.w * other, A.x * other, A.y * other, A.z * other);
}
Quaternion VMath::operator*(const Quaternion& A, const Quaternion& B) {
  return Quaternion{
      A.w * B.w - A.x * B.x - A.y * B.y - A.z * B.z,
      A.w * B.x + A.x * B.w + A.y * B.z - A.z * B.y,
      A.w * B.y - A.x * B.z + A.y * B.w + A.z * B.x,
      A.w * B.z + A.x * B.y - A.y * B.x + A.z * B.w,
  };
}
Quaternion VMath::normalize(const Quaternion& Q) { return Q.normalized(); }

//------------------------------------------------------------------------------

SO3 SO3::operator*=(const SO3& more_recent) {
  Q = more_recent.Q * Q;
  T = (more_recent.Q * Quaternion(T) * ~more_recent.Q).xyz() + more_recent.T;
  return *this;
}

SO3 SO3::operator*(const SO3& Rhs) const { return SO3(Q * Rhs.Q, (Q * Quaternion(Rhs.T) * ~Q).xyz() + T); }

Vector3 SO3::operator*(const Vector3& V) const { return (Q * Quaternion(V) * ~Q).vec(); }
Point3 SO3::operator*(const Point3& V) const {
  return (Q * Quaternion(V - Point3::ZERO) * ~Q).vec() + Point3::ZERO + T;
}

void SO3::inv() {
  // (Q1 - T1) * (Q2 - T2) = (Q1*Q2 - Q1*T2+T1)
  // (~Q - ~T1) * (Q - T) = (~Q*Q - ~Q*T+~T)
  T = (~Q * Quaternion(T) * Q).xyz();
  Q.inv();
}
SO3 SO3::operator~() const { return SO3(~Q, (~Q * Quaternion(T) * Q).xyz()); }
