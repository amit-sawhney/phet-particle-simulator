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

bool CollisionPhysics::DidParticlesCollide(const Particle& particle1,
                                           const Particle& particle2) const {
  float particle_distances =
      glm::distance(particle1.GetPosition(), particle2.GetPosition());

  bool areTouching =
      particle_distances <= particle1.GetRadius() + particle2.GetRadius();

  glm::vec2 delta_velocity = particle1.GetVelocity() - particle2.GetVelocity();
  glm::vec2 delta_position = particle1.GetPosition() - particle2.GetVelocity();

  bool areMovingTowardsEachOther = glm::dot(delta_velocity, delta_position) < 0;

  return areTouching && areMovingTowardsEachOther;
}

void CollisionPhysics::UpdateCollidedParticleVelocities(Particle& particle1,
                                                        Particle& particle2) {
  glm::vec2 delta_position = particle1.GetPosition() - particle2.GetPosition();
  glm::vec2 delta_velocity = particle1.GetVelocity() - particle2.GetVelocity();

  // Calculates the new velocity of particle 1 based on the collision
  glm::vec2 new_velocity1 =
      particle1.GetVelocity() - (glm::dot(delta_velocity, (delta_position)) /
                                 glm::pow(glm::length(delta_position), 2)) *
                                    delta_position;

  // Calculates the new velocity of particle 2 based on the collision
  glm::vec2 new_velocity2 =
      particle2.GetVelocity() - glm::dot(-delta_velocity, -delta_position) /
                                    glm::pow(glm::length(-delta_position), 2) *
                                    -delta_position;

  particle1.SetVelocity(new_velocity1);
  particle2.SetVelocity(new_velocity2);
}

bool CollisionPhysics::IsParticleCollidingWithTopWall(
    const Particle& particle) const {
  float y_pos = particle.GetPosition().y;
  float y_velocity = particle.GetVelocity().y;
  float radius = particle.GetRadius();

  return y_pos - radius <= topWall_ && y_velocity < 0;
}

bool CollisionPhysics::IsParticleCollidingWithBottomWall(
    const Particle& particle) const {
  float y_pos = particle.GetPosition().y;
  float y_velocity = particle.GetVelocity().y;
  float radius = particle.GetRadius();

  return y_pos + radius >= bottomWall_ && y_velocity > 0;
}

bool CollisionPhysics::IsParticleCollidingWithLeftWall(
    const Particle& particle) const {
  float x_pos = particle.GetPosition().x;
  float x_velocity = particle.GetVelocity().x;
  float radius = particle.GetRadius();

  return x_pos - radius <= leftWall_ && x_velocity < 0;
}

bool CollisionPhysics::IsParticleCollidingWithRightWall(
    const Particle& particle) const {
  float x_pos = particle.GetPosition().x;
  float x_velocity = particle.GetVelocity().x;
  float radius = particle.GetRadius();

  return x_pos + radius >= rightWall_ && x_velocity > 0;
}

}  // namespace idealgas