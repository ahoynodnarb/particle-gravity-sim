#include <vector>

#include "particle.h"
#include "physics_solver.h"
#include "vec2.h"

using namespace p_sim;
void physics_solver::apply_gravity(particle &p, particle &q) {
  vec2 r = p.x - q.x;
  double distance = norm(r);
  double g_force = G * p.mass * q.mass / (distance * distance);
  if (!p.fixed) {
    p.a += (g_force / p.mass) * (-r / distance);
  }
  if (!q.fixed) {
    q.a += (g_force / q.mass) * (r / distance);
  }
}

void physics_solver::add_particle(particle &p) { particles_.push_back(p); }
const std::vector<particle> &physics_solver::get_particles() const {
  return particles_;
}
// TODO: Maybe an epsilon to check against the distance?
void physics_solver::step() {
  for (auto it_0 = particles_.begin(); it_0 != particles_.end(); ++it_0) {
    particle &p = *it_0;
    // precompute parts of the leapfrog verlet for this timestep
    // this is actually fine because the inner loop already accounts
    // for both the action and reaction gravitational forces so the acceleration
    // of the particle following the inner loop will be the final acceleration
    // for the next timestep
    vec2 x_step = p.v * time_delta + 0.5 * p.a * (time_delta * time_delta);
    vec2 v_step = 0.5 * p.a * time_delta;
    for (auto it_1 = std::next(it_0); it_1 != particles_.end(); ++it_1) {
      particle &q = *it_1;
      if (p.fixed && q.fixed) {
        continue;
      }
      apply_gravity(p, q);
    }
    // apply leapfrog
    if (!p.fixed) {
      v_step += 0.5 * p.a * time_delta;
      p.x += x_step;
      p.v += v_step;
      p.a = vec2(0, 0);
    }
  }
}