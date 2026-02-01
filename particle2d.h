#pragma once

#include "vec2.h"

namespace p_sim {
struct particle2d {
  vec2 x;
  vec2 v;
  vec2 a;
  double radius;
  double mass;
  bool fixed;
  particle2d(vec2 x = {}, vec2 v = {}, vec2 a = {}, double radius = 0.0,
             double mass = 0.0, bool fixed = false)
      : x(x), v(v), a(a), radius(radius), mass(mass), fixed(fixed) {}
};
} // namespace p_sim