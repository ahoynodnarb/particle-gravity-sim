#pragma once

#include <deque>
#include <string>

#include <raylib.h>

#include "physics_solver3d.h"
#include "vec2.h"
#include "vec3.h"

namespace p_sim {
class simulator3d {
private:
  std::shared_ptr<physics_solver3d> solver_;
  int target_fps_;
  int steps_per_frame_;

  int window_width_;
  int window_height_;
  std::string window_title_;

  Camera camera_;
  double zoom_factor_;
  float target_distance_ = 200.0f;
  float rotation_speed_ = 0.6f;

  int max_n_trails_;
  std::deque<vec3> previous_positions_;
  void _draw_particles();
  void _draw_trails();
  void _update_camera_position();
  void _update_camera_target();
  void _perform_physics_steps();

public:
  size_t target_index;
  simulator3d(const std::shared_ptr<physics_solver3d> solver,
              int target_fps = 1.0 / 60.0, int steps_per_frame = 1,
              double zoom_factor = 10.0, size_t target_index = 0,
              int max_n_trails = 1000, int window_width = 800,
              int window_height = 500, std::string window_title = {})
      : solver_(std::move(solver)), target_fps_(target_fps),
        steps_per_frame_(steps_per_frame), zoom_factor_(zoom_factor),
        target_index(target_index), max_n_trails_(max_n_trails),
        window_width_(window_width), window_height_(window_height),
        window_title_(std::move(window_title)) {}
  void render();
};
} // namespace p_sim