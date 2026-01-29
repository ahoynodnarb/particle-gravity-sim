#include <raylib.h>

#include "particle.h"
#include "renderer.h"

using namespace p_sim;
void renderer::_draw_particles() {
  for (const auto &p : solver_.get_particles()) {
    // raylib draws from the top left, but each particle's position is its
    // center. hence, shift both coordinates and flip y to get cartesian
    vec2 pos = p->x - p->radius;
    int x = zoom_factor_ * pos.x + draw_offset_.x;
    int y = -zoom_factor_ * pos.y + draw_offset_.y;
    DrawCircle(x, y, zoom_factor_ * p->radius, WHITE);
  }
}
void renderer::_draw_trails() {
  for (const auto &pos : previous_positions_) {
    int x = zoom_factor_ * pos.x + draw_offset_.x;
    int y = -zoom_factor_ * pos.y + draw_offset_.y;
    DrawCircle(x, y, zoom_factor_ * 1, RED);
  }
}
void renderer::_update_draw_offset() {
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    Vector2 mouse_delta = GetMouseDelta();
    draw_offset_.x += mouse_delta.x;
    draw_offset_.y += mouse_delta.y;
  }
}
void renderer::_perform_physics_steps() {
  for (size_t i = 0; i < steps_per_frame_; ++i) {
    solver_.step();
  }
  for (const auto &p : solver_.get_particles()) {
    vec2 pos = p->x;
    if (previous_positions_.size() == max_n_trails_) {
      previous_positions_.pop_front();
    }
    previous_positions_.push_back(pos - p->radius);
  }
}
void renderer::render() {
  InitWindow(window_width_, window_height_, window_title_.c_str());
  SetTargetFPS(target_fps_);
  while (!WindowShouldClose()) {
    _update_draw_offset();

    BeginDrawing();
    ClearBackground(BLACK);
    _draw_trails();
    _draw_particles();
    EndDrawing();
    _perform_physics_steps();
  }
  CloseWindow();
}