#include <cmath>
#include <iostream>

#include "vec2.h"

using p_sim::vec2;
double p_sim::norm(const vec2 &vec, int p) {
  return std::pow(std::pow(vec.x, p) + std::pow(vec.y, p), 1.0 / p);
}
double p_sim::norm(const vec2 &vec) { return norm(vec, 2); }
vec2 p_sim::normalize(const vec2 &vec) {
  double magnitude = norm(vec);
  return vec2(vec.x / magnitude, vec.y / magnitude);
}
std::ostream &operator<<(std::ostream &out, const p_sim::vec2 &vec) {
  out << "<" << vec.x << ", " << vec.y << ">";
  return out;
}