#include <cmath>
#include <vector>

#include "particle.h"
#include "physics_solver.h"
#include "vec2.h"

using namespace p_sim;
// https://mechanicsmap.psu.edu/websites/11_impulse_momentum_particle/11-5_2D_collisions/2D_collisions.html
void p_sim::check_collision(particle &p, particle &q) {
  // points to p
  vec2 r = p.x - q.x;
  double distance = norm(r);
  if (distance > p.radius + q.radius) {
    return;
  }
  vec2 n = unit(r);
  vec2 t = normal(n);
  vec2 diff = n * ((p.radius + q.radius) - distance);

  // corrects their positions if they intersect
  if (p.fixed) {
    q.x -= diff;
  } else if (q.fixed) {
    p.x += diff;
  } else {
    p.x += diff / 2.0;
    q.x -= diff / 2.0;
  }
  double p_proj_n, p_proj_t;
  double q_proj_n, q_proj_t;
  double m_q = 1e30, m_p = 1e30;

  if (!p.fixed) {
    p_proj_n = dot(p.v, n);
    p_proj_t = dot(p.v, t);
    m_p = p.mass;
  }
  if (!q.fixed) {
    q_proj_n = dot(q.v, n);
    q_proj_t = dot(q.v, t);
    m_q = q.mass;
  }
  double v_p_n = (2 * m_q * q_proj_n + (m_p - m_q) * p_proj_n) / (m_q + m_p);
  double v_q_n = (2 * m_p * p_proj_n + (m_q - m_p) * q_proj_n) / (m_q + m_p);

  vec2 v_p_final = v_p_n * n + p_proj_t * t;
  vec2 v_q_final = v_q_n * n + q_proj_t * t;

  if (!p.fixed) {
    p.v = v_p_final;
  }
  if (!q.fixed) {
    q.v = v_q_final;
  }
}
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
  for (size_t i = 0; i < particles_.size(); ++i) {
    particle &p = particles_[i];
    vec2 x_step = p.v * time_delta + 0.5 * p.a * (time_delta * time_delta);
    vec2 v_step = 0.5 * p.a * time_delta;
    // since apply_gravity applies to both particles, each particle p has
    // already accumulated all the gravitational forces for previous particles,
    // and the inner loop accumulates the gravitational forces for the next
    // particles stored
    for (size_t j = i + 1; j < particles_.size(); ++j) {
      particle &q = particles_[j];
      if (p.fixed && q.fixed) {
        continue;
      }
      check_collision(p, q);
      apply_gravity(p, q);
    }
    // apply leapfrog
    // since no more particles rely on any properties of particle p, we are
    // completely safe to do the verlet step
    if (!p.fixed) {
      v_step += 0.5 * p.a * time_delta;
      p.x += x_step;
      p.v += v_step;
      p.a = vec2(0, 0);
    }
  }
}