#pragma once

#include "vec3.h"

namespace p_sim {
struct particle3d {
  vec3 x;
  vec3 v;
  vec3 a;
  double radius;
  double mass;
  bool fixed;
  particle3d(vec3 x = {}, vec3 v = {}, vec3 a = {}, double radius = 0.0,
             double mass = 0.0, bool fixed = false)
      : x(x), v(v), a(a), radius(radius), mass(mass), fixed(fixed) {}
};
} // namespace p_sim