#include "physics/collision_physics.h"

namespace idealgas {

CollisionPhysics::CollisionPhysics(const glm::vec2& top_left_corner,
                                   const glm::vec2& bottom_right_corner) {
  leftWall_ = top_left_corner.x;
  topWall_ = top_left_corner.y;
  rightWall_ = bottom_right_corner.x;
  bottomWall_ = bottom_right_corner.y;
}

CollisionPhysics::CollisionPhysics() = default;

bool CollisionPhysics::DidParticlesCollide(Particle first_particle,
                                           Particle second_particle) const {
  bool areTouching = glm::distance(first_particle.GetPosition(),
                                   second_particle.GetPosition()) <=
                     first_particle.GetRadius() + second_particle.GetRadius();

  bool areMovingTowardsEachOther =
      glm::dot(first_particle.GetVelocity() - second_particle.GetVelocity(),
               first_particle.GetPosition() - second_particle.GetPosition()) <
      0;

  return areTouching && areMovingTowardsEachOther;
}

void CollisionPhysics::UpdateCollidedParticleVelocities(
    Particle& first_particle, Particle& second_particle) {
  glm::vec2 delta_positions =
      first_particle.GetPosition() - second_particle.GetPosition();
  glm::vec2 delta_velocities =
      first_particle.GetVelocity() - second_particle.GetVelocity();

  glm::vec2 first_new_velocity =
      first_particle.GetVelocity() -
      (glm::dot(delta_velocities, (delta_positions)) /
       glm::pow(glm::length(delta_positions), 2)) *
          delta_positions;

  glm::vec2 second_new_velocity =
      second_particle.GetVelocity() -
      glm::dot(-delta_velocities, -delta_positions) /
          glm::pow(glm::length(-delta_positions), 2) * -delta_positions;

  first_particle.SetVelocity(first_new_velocity);
  second_particle.SetVelocity(second_new_velocity);
}

bool CollisionPhysics::IsParticleCollidingWithTopWall(Particle particle) const {
  float y_pos = particle.GetPosition().y;
  float y_velocity = particle.GetVelocity().y;
  float radius = particle.GetRadius();

  return y_pos - radius <= topWall_ && y_velocity < 0;
}

bool CollisionPhysics::IsParticleCollidingWithBottomWall(
    Particle particle) const {
  float y_pos = particle.GetPosition().y;
  float y_velocity = particle.GetVelocity().y;
  float radius = particle.GetRadius();

  return y_pos + radius >= bottomWall_ && y_velocity > 0;
}

bool CollisionPhysics::IsParticleCollidingWithLeftWall(
    Particle particle) const {
  float x_pos = particle.GetPosition().x;
  float x_velocity = particle.GetVelocity().x;
  float radius = particle.GetRadius();

  return x_pos - radius <= leftWall_ && x_velocity < 0;
}

bool CollisionPhysics::IsParticleCollidingWithRightWall(
    Particle particle) const {
  float x_pos = particle.GetPosition().x;
  float x_velocity = particle.GetVelocity().x;
  float radius = particle.GetRadius();

  return x_pos + radius >= rightWall_ && x_velocity > 0;
}

}  // namespace idealgas