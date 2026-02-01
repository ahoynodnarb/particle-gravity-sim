#pragma once

#include <vector>

#include "particle2d.h"

namespace p_sim {
extern void check_collision(particle2d &, particle2d &);
extern void apply_gravity(particle2d &, particle2d &);
class physics_solver2d {

protected:
  std::vector<std::unique_ptr<particle2d>> particles_;

public:
  double time_delta;

  physics_solver2d(double time_delta = 1.0 / 60.0) : time_delta(time_delta) {}
  void add_particle(std::unique_ptr<particle2d>);
  const std::vector<std::unique_ptr<particle2d>> &get_particles() const;
  virtual void step();
};
} // namespace p_sim