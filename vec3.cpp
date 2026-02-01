#include <cmath>
#include <iostream>

#include "vec3.h"

using p_sim::vec3;
double p_sim::dot(const vec3 &lhs, const vec3 &rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
double p_sim::norm(const vec3 &vec, int p) {
  return std::pow(std::pow(vec.x, p) + std::pow(vec.y, p) + std::pow(vec.z, p),
                  1.0 / p);
}
double p_sim::norm(const vec3 &vec) { return norm(vec, 2); }
vec3 p_sim::unit(const vec3 &vec) {
  double magnitude = norm(vec);
  return vec3(vec.x / magnitude, vec.y / magnitude, vec.z / magnitude);
}
vec3 p_sim::normal(const vec3 &vec) {
  return norm(vec) * unit(vec3(1.0 / vec.x, -1.0 / vec.y, 0));
}
vec3 p_sim::cross(const vec3 &lhs, const vec3 &rhs) {
  return vec3(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z,
              lhs.x * rhs.y - lhs.y * rhs.x);
}
std::ostream &operator<<(std::ostream &out, const p_sim::vec3 &vec) {
  out << "<" << vec.x << ", " << vec.y << ", " << vec.z << ">";
  return out;
}