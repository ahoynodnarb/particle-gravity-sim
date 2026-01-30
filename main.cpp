#include <iostream>

#include "particle.h"
#include "physics_solver.h"
#include "simulator.h"
#include "vec2.h"

#define FPS 30
#define DELTA_T 1.0 / 20.0
#define FRAME_STEPS 400
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 700
#define ZOOM_FACTOR 1.0
#define N_MAX_TRAILS 400 * 3

using namespace p_sim;
int main() {
  double mass_1 = 5e10;
  double mass_2 = 1e8;
  double mass_3 = 5e8;
  double mass_4 = 5e6;

  vec2 x_0_1 = vec2(0, 0);
  vec2 x_0_2 = vec2(120, 80);
  vec2 x_0_3 = vec2(180, -200);
  vec2 x_0_4 = vec2(70, -70);

  vec2 v_0_1 = vec2(0.01, -0.01);

  vec2 r2 = x_0_2 - x_0_1;
  vec2 tangent_vec2 = unit(vec2(r2.y, -r2.x));
  double orbit_velocity_2 = sqrt(G * mass_1 / norm(r2));
  vec2 v_0_2 = 0.75 * tangent_vec2 * orbit_velocity_2;

  vec2 r3 = x_0_3 - x_0_1;
  vec2 tangent_vec3 = unit(vec2(r3.y, -r3.x));
  double orbit_velocity_3 = sqrt(G * mass_1 / norm(r3));
  vec2 v_0_3 = 0.75 * tangent_vec3 * orbit_velocity_3;

  vec2 r4 = x_0_4 - x_0_1;
  vec2 tangent_vec4 = unit(vec2(r4.y, -r4.x));
  double orbit_velocity_4 = sqrt(G * mass_1 / norm(r4));
  vec2 v_0_4 = 0.75 * tangent_vec4 * orbit_velocity_4;

  vec2 a_0_1;
  vec2 a_0_2;
  vec2 a_0_3;
  vec2 a_0_4;

  auto p_1 =
      std::make_unique<particle>(x_0_1, v_0_1, a_0_1, 12.0, mass_1, false);
  auto p_2 =
      std::make_unique<particle>(x_0_2, v_0_2, a_0_2, 5.0, mass_2, false);
  auto p_3 =
      std::make_unique<particle>(x_0_3, v_0_3, a_0_3, 4.0, mass_3, false);
  auto p_4 =
      std::make_unique<particle>(x_0_4, v_0_4, a_0_4, 3.0, mass_4, false);

  auto solver = std::make_shared<physics_solver>(DELTA_T);
  solver->add_particle(std::move(p_1));
  solver->add_particle(std::move(p_2));
  solver->add_particle(std::move(p_3));
  solver->add_particle(std::move(p_4));
  simulator graphics_simulator(solver, FPS, FRAME_STEPS,
                               vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
                               ZOOM_FACTOR, N_MAX_TRAILS, WINDOW_WIDTH,
                               WINDOW_HEIGHT, "3 particle gravity");
  graphics_simulator.render();

  return 0;
}