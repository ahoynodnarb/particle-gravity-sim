#pragma once

#include "physics_solver.h"
#include "vec2.h"

#include <deque>
#include <string>

namespace p_sim {
class renderer {
private:
  physics_solver &solver_;
  int target_fps_;
  int steps_per_frame_;

  int window_width_;
  int window_height_;
  std::string window_title_;

  vec2 draw_offset_;
  double zoom_factor_;

  int max_n_trails_;
  std::deque<vec2> previous_positions_;
  void _draw_particles();
  void _draw_trails();
  void _update_draw_offset();
  void _perform_physics_steps();

public:
  renderer(physics_solver &solver, int target_fps = 1.0 / 60.0,
           int steps_per_frame = 1, const vec2 &draw_offset = {},
           double zoom_factor = 10.0, int max_n_trails = 1000,
           int window_width = 800, int window_height = 500,
           std::string window_title = {})
      : solver_(solver), target_fps_(target_fps),
        steps_per_frame_(steps_per_frame), draw_offset_(draw_offset),
        zoom_factor_(zoom_factor), max_n_trails_(max_n_trails),
        window_width_(window_width), window_height_(window_height),
        window_title_(std::move(window_title)) {}
  void render();
};
} // namespace p_sim