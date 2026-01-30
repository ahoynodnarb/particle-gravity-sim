#pragma once

#include <vector>

#include "particle.h"

namespace p_sim {
constexpr double G = 6.674e-11;
extern void check_collision(particle &, particle &);
extern void apply_gravity(particle &, particle &);
class physics_solver {

protected:
  std::vector<std::unique_ptr<particle>> particles_;

public:
  double time_delta;

  physics_solver(double time_delta = 1.0 / 60.0) : time_delta(time_delta) {}
  void add_particle(std::unique_ptr<particle>);
  const std::vector<std::unique_ptr<particle>> &get_particles() const;
  virtual void step();
};
} // namespace p_sim