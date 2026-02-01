#pragma once

#include <iostream>

namespace p_sim {
struct vec3 {
  double x;
  double y;
  double z;

  vec3() : x(0.0), y(0.0), z(0.0) {};
  vec3(double x, double y, double z) : x(x), y(y), z(z) {};
  vec3 operator*(const vec3 &rhs) const {
    return vec3(x * rhs.x, y * rhs.y, z * rhs.z);
  }
  vec3 operator*(double rhs) const { return vec3(x * rhs, y * rhs, z * rhs); }
  friend vec3 operator*(double lhs, const vec3 &rhs) {
    return vec3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
  }
  vec3 &operator*=(const vec3 &rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
  }
  vec3 &operator*=(double rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
  }
  vec3 operator/(const vec3 &rhs) const {
    return vec3(x / rhs.x, y / rhs.y, z / rhs.z);
  }
  vec3 operator/(double rhs) const { return vec3(x / rhs, y / rhs, z / rhs); }
  friend vec3 operator/(double lhs, const vec3 &rhs) {
    return vec3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
  }
  vec3 &operator/=(const vec3 &rhs) {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    return *this;
  }
  vec3 &operator/=(double rhs) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
  }
  vec3 operator+(const vec3 &rhs) const {
    return vec3(x + rhs.x, y + rhs.y, z + rhs.z);
  }
  vec3 operator+(double rhs) const { return vec3(x + rhs, y + rhs, z + rhs); }
  friend vec3 operator+(double lhs, const vec3 &rhs) {
    return vec3(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
  }
  vec3 &operator+=(const vec3 &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }
  vec3 &operator+=(double rhs) {
    x += rhs;
    y += rhs;
    z += rhs;
    return *this;
  }
  vec3 operator-(const vec3 &rhs) const {
    return vec3(x - rhs.x, y - rhs.y, z - rhs.z);
  }
  vec3 operator-(double rhs) const { return vec3(x - rhs, y - rhs, z - rhs); }
  friend vec3 operator-(double lhs, const vec3 &rhs) {
    return vec3(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
  }
  vec3 operator-() const { return vec3(-x, -y, -z); }
  vec3 &operator-=(const vec3 &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }
  vec3 &operator-=(double rhs) {
    x -= rhs;
    y -= rhs;
    z -= rhs;
    return *this;
  }
};
extern double dot(const vec3 &, const vec3 &);
extern double norm(const vec3 &, int);
extern double norm(const vec3 &);
extern vec3 unit(const vec3 &);
extern vec3 normal(const vec3 &);
extern vec3 cross(const vec3 &, const vec3 &);
} // namespace p_sim
extern std::ostream &operator<<(std::ostream &, const p_sim::vec3 &);