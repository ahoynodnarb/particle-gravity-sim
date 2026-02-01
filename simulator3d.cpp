#include <raylib.h>
#include <raymath.h>

#include "particle3d.h"
#include "simulator3d.h"

using namespace p_sim;
void simulator3d::_draw_particles() {
  for (const auto &p : solver_->get_particles()) {
    // raylib draws from the top left, but each particle's position is its
    // center. hence, shift both coordinates and flip y to get cartesian
    vec3 pos = p->x - p->radius;
    float x = zoom_factor_ * pos.x;
    float y = zoom_factor_ * pos.y;
    float z = zoom_factor_ * pos.z;
    DrawSphere(Vector3({x, y, z}), zoom_factor_ * p->radius, WHITE);
  }
}
void simulator3d::_draw_trails() {
  for (const auto &pos : previous_positions_) {
    float x = zoom_factor_ * pos.x;
    float y = zoom_factor_ * pos.y;
    float z = zoom_factor_ * pos.z;
    DrawSphere(Vector3({x, y, z}), zoom_factor_ * 1, RED);
  }
}
void simulator3d::_update_camera_position() {
  float mouse_scroll = GetMouseWheelMove();
  if (fabs(mouse_scroll) > 1e-1) {
    target_distance_ = std::max(0.0f, target_distance_ - mouse_scroll);
  }
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    Vector2 mouse_delta = GetMouseDelta();
    Vector3 r = camera_.target - camera_.position;
    float radius = Vector3Length(r);
    Vector3 coord = (Vector3){mouse_delta.x, mouse_delta.y, 0.0f};
    Matrix camera_transform = GetCameraMatrix(camera_);
    Matrix space_transform = MatrixInvert(camera_transform);
    Quaternion rotation = QuaternionFromMatrix(space_transform);

    Vector3 lateral_translation =
        Vector3Negate(Vector3RotateByQuaternion(coord, rotation)) *
        rotation_speed_;
    float lateral_dist = Vector3Length(lateral_translation);
    float dist_to_radius =
        radius - sqrt(radius * radius - lateral_dist * lateral_dist);
    Vector3 forward_translation = (r / radius) * dist_to_radius;
    camera_.position += lateral_translation + forward_translation;
  }
  camera_.position =
      camera_.target +
      Vector3Normalize(camera_.position - camera_.target) * target_distance_;
}
void simulator3d::_update_camera_target() {
  if (IsKeyPressed(KEY_LEFT)) {
    target_index--;
  } else if (IsKeyPressed(KEY_RIGHT)) {
    target_index++;
  }
  auto &particles = solver_->get_particles();
  target_index = target_index % particles.size();
  auto &particle = particles[target_index];
  vec3 target = zoom_factor_ * (particle->x - particle->radius);
  Vector3 new_target =
      (Vector3){(float)target.x, (float)target.y, (float)target.z};
  camera_.target = new_target;
}
void simulator3d::_perform_physics_steps() {
  for (size_t i = 0; i < steps_per_frame_; ++i) {
    solver_->step();
  }
  for (const auto &p : solver_->get_particles()) {
    vec3 pos = p->x;
    if (previous_positions_.size() == max_n_trails_) {
      previous_positions_.pop_front();
    }
    previous_positions_.push_back(pos - p->radius);
  }
}
void simulator3d::render() {
  InitWindow(window_width_, window_height_, window_title_.c_str());
  SetTargetFPS(target_fps_);
  camera_ = {0};
  camera_.position = (Vector3){0.0f, 0.0f, 0.0f};
  camera_.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera_.fovy = 45.0f;
  camera_.projection = CAMERA_PERSPECTIVE;
  while (!WindowShouldClose()) {
    _update_camera_target();
    _update_camera_position();

    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode3D(camera_);
    _draw_trails();
    _draw_particles();
    EndMode3D();
    EndDrawing();
    _perform_physics_steps();
  }
  CloseWindow();
}