#include <iostream>

#include "particle.h"
#include "physics_solver.h"
#include "renderer.h"
#include "vec2.h"

#define FPS 30.0
#define DELTA_T 1.0 / 20.0
#define FRAME_STEPS 100
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 700

using namespace p_sim;
int main() {
  double mass_1 = 10000.0;
  double mass_2 = 1000.0;
  double mass_3 = 500.0;

  vec2 x_0_1 = vec2(0, 0);
  vec2 x_0_2 = vec2(9, 9);
  vec2 x_0_3 = vec2(4, 4);

  vec2 v_0_1 = vec2(0.01, -0.01);

  vec2 r2 = x_0_2 - x_0_1;
  vec2 tangent_vec2 = normalize(vec2(r2.y, -r2.x));
  double orbit_velocity_2 = sqrt(G * mass_1 / norm(r2));
  vec2 v_0_2 = tangent_vec2 * orbit_velocity_2;

  vec2 r3 = x_0_3 - x_0_1;
  vec2 tangent_vec3 = normalize(vec2(r3.y, -r3.x));
  double orbit_velocity_3 = sqrt(G * mass_1 / norm(r3));
  vec2 v_0_3 = -tangent_vec3 * orbit_velocity_3;

  vec2 a_0_1;
  vec2 a_0_2;
  vec2 a_0_3;

  particle p_1(x_0_1, v_0_1, a_0_1, 5.0, mass_1, false);
  particle p_2(x_0_2, v_0_2, a_0_2, 3.0, mass_2, false);
  particle p_3(x_0_3, v_0_3, a_0_3, 2.0, mass_3, false);

  physics_solver solver(DELTA_T);
  solver.add_particle(p_1);
  solver.add_particle(p_2);
  solver.add_particle(p_3);
  renderer graphics_renderer(solver, FPS, FRAME_STEPS, WINDOW_WIDTH,
                             WINDOW_HEIGHT, "3 particle gravity",
                             vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
  graphics_renderer.render();

  return 0;
}