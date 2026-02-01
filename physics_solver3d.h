#pragma once

#include <vector>

#include "particle3d.h"

namespace p_sim {
extern void check_collision(particle3d &, particle3d &);
extern void apply_gravity(particle3d &, particle3d &);
class physics_solver3d {

protected:
  std::vector<std::unique_ptr<particle3d>> particles_;

public:
  double time_delta;

  physics_solver3d(double time_delta = 1.0 / 60.0) : time_delta(time_delta) {}
  void add_particle(std::unique_ptr<particle3d>);
  const std::vector<std::unique_ptr<particle3d>> &get_particles() const;
  virtual void step();
};
} // namespace p_sim