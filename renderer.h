#pragma once

#include "physics_solver.h"
#include "vec2.h"

#include <string>
#include <vector>

namespace p_sim {
class renderer {
private:
  physics_solver solver_;
  double target_fps_;
  int steps_per_frame_;

  int window_width_;
  int window_height_;
  std::string window_title_;

  vec2 draw_offset_;

  std::vector<vec2> previous_positions_;
  void _draw_particles();
  void _draw_trails();

public:
  renderer(const physics_solver &solver, double target_fps = 1.0 / 60.0,
           int steps_per_frame = 1, int window_width = 800,
           int window_height = 500, std::string window_title = {},
           const vec2 &draw_offset = {})
      : solver_(solver), target_fps_(target_fps),
        steps_per_frame_(steps_per_frame), window_width_(window_width),
        window_height_(window_height), window_title_(std::move(window_title)),
        draw_offset_(draw_offset) {}
  void render();
};
} // namespace p_sim