#include <raylib.h>
#include <vector>

#include "particle.h"
#include "renderer.h"

using namespace p_sim;
void renderer::_draw_particles() {
  for (const auto &p : solver_.get_particles()) {
    vec2 pos = p.x;
    int x = zoom_factor_ * pos.x + draw_offset_.x;
    int y = zoom_factor_ * pos.y + draw_offset_.y;
    DrawCircle(x, y, p.radius, WHITE);
  }
}
void renderer::_draw_trails() {
  for (const auto &pos : previous_positions_) {
    int x = zoom_factor_ * pos.x + draw_offset_.x;
    int y = zoom_factor_ * pos.y + draw_offset_.y;
    DrawCircle(x, y, 1, RED);
  }
}
void renderer::render() {
  InitWindow(window_width_, window_height_, window_title_.c_str());
  SetTargetFPS(target_fps_);
  double original_delta = solver_.time_delta;
  while (!WindowShouldClose()) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      Vector2 mouse_delta = GetMouseDelta();
      draw_offset_.x += mouse_delta.x;
      draw_offset_.y += mouse_delta.y;
    }
    BeginDrawing();
    ClearBackground(BLACK);
    _draw_trails();
    _draw_particles();
    EndDrawing();
    solver_.time_delta = original_delta * GetFrameTime();
    for (unsigned i = 0; i < steps_per_frame_; ++i) {
      solver_.step();
    }
    for (const auto &p : solver_.get_particles()) {
      vec2 pos = p.x;
      previous_positions_.push_back(pos);
    }
  }
  CloseWindow();
}