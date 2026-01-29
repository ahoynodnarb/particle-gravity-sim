#pragma once

#include <cmath>
#include <iostream>
#include <string>

namespace p_sim {
struct vec2 {
  double x;
  double y;

  vec2(double x = 0.0, double y = 0.0) : x(x), y(y) {};
  double dot(const vec2 &rhs) const { return x * rhs.x + y * rhs.y; }
  vec2 operator*(const vec2 &rhs) const { return vec2(x * rhs.x, y * rhs.y); }
  vec2 operator*(double rhs) const { return vec2(x * rhs, y * rhs); }
  friend vec2 operator*(double lhs, const vec2 &rhs) {
    return vec2(lhs * rhs.x, lhs * rhs.y);
  }
  vec2 &operator*=(const vec2 &rhs) {
    x *= rhs.x;
    y *= rhs.y;
    return *this;
  }
  vec2 &operator*=(double rhs) {
    x *= rhs;
    y *= rhs;
    return *this;
  }
  vec2 operator/(const vec2 &rhs) const { return vec2(x / rhs.x, y / rhs.y); }
  vec2 operator/(double rhs) const { return vec2(x / rhs, y / rhs); }
  friend vec2 operator/(double lhs, const vec2 &rhs) {
    return vec2(lhs / rhs.x, lhs / rhs.y);
  }
  vec2 &operator/=(const vec2 &rhs) {
    x /= rhs.x;
    y /= rhs.y;
    return *this;
  }
  vec2 &operator/=(double rhs) {
    x /= rhs;
    y /= rhs;
    return *this;
  }
  vec2 operator+(const vec2 &rhs) const { return vec2(x + rhs.x, y + rhs.y); }
  vec2 operator+(double rhs) const { return vec2(x + rhs, y + rhs); }
  friend vec2 operator+(double lhs, const vec2 &rhs) {
    return vec2(lhs + rhs.x, lhs + rhs.y);
  }
  vec2 &operator+=(const vec2 &rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }
  vec2 &operator+=(double rhs) {
    x += rhs;
    y += rhs;
    return *this;
  }
  vec2 operator-(const vec2 &rhs) const { return vec2(x - rhs.x, y - rhs.y); }
  vec2 operator-(double rhs) const { return vec2(x - rhs, y - rhs); }
  friend vec2 operator-(double lhs, const vec2 &rhs) {
    return vec2(lhs - rhs.x, lhs - rhs.y);
  }
  vec2 operator-() const { return vec2(-x, -y); }
  vec2 &operator-=(const vec2 &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }
  vec2 &operator-=(double rhs) {
    x -= rhs;
    y -= rhs;
    return *this;
  }
};
extern double norm(const vec2 &, int);
extern double norm(const vec2 &);
extern vec2 normalize(const vec2 &vec);
} // namespace p_sim
extern std::ostream &operator<<(std::ostream &out, const p_sim::vec2 &vec);