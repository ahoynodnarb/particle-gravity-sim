#pragma once

#include <vector>

#include "particle.h"

namespace p_sim {
#define G 6.674e-5
class physics_solver {
protected:
  std::vector<particle> particles_;

public:
  double time_delta;
  static void apply_gravity(particle &, particle &);

  physics_solver(double time_delta = 1.0 / 60.0) : time_delta(time_delta) {}
  void add_particle(const particle &);
  const std::vector<particle> &get_particles() const;
  virtual void step();
};
} // namespace p_sim