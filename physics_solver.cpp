#include <vector>

#include "particle.h"
#include "physics_solver.h"
#include "vec2.h"

using namespace p_sim;
// this just computes the gravitational force between each particle, finds the
// distance vector, and applies the force in that direction
void p_sim::apply_gravity(particle &p, particle &q) {
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

void physics_solver::add_particle(const particle &p) {
  particles_.push_back(p);
}
const std::vector<particle> &physics_solver::get_particles() const {
  return particles_;
}
// TODO: Maybe an epsilon to check against the distance?
void physics_solver::step() {
  std::vector<vec2> initial_accelerations;
  initial_accelerations.reserve(particles_.size());
  for (const auto &p : particles_) {
    initial_accelerations.push_back(p.a);
  }
  for (unsigned i = 0; i < particles_.size(); ++i) {
    particle &p = particles_[i];
    // since apply_gravity applies to both particles, each particle p has
    // already accumulated all the gravitational forces for previous particles,
    // and the inner loop accumulates the gravitational forces for the next
    // particles stored
    for (unsigned j = i + 1; j < particles_.size(); ++j) {
      particle &q = particles_[j];
      if (p.fixed && q.fixed) {
        continue;
      }
      apply_gravity(p, q);
    }
    // apply leapfrog
    // since no more particles rely on any properties of particle p, we are
    // completely safe to do the verlet step
    if (!p.fixed) {
      vec2 &old_a = initial_accelerations[i];
      vec2 x_step = p.v * time_delta + 0.5 * old_a * (time_delta * time_delta);
      vec2 v_step = 0.5 * (old_a + p.a) * time_delta;
      p.x += x_step;
      p.v += v_step;
      p.a = old_a;
    }
  }
}