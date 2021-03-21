#pragma once

#include "cinder/gl/gl.h"

namespace idealgas {

/**
 * This class represents a singular particle that will exist within a container
 * with a specific attributes the replicate an ideal gas particle
 */
class Particle {
 public:
  /**
   * Initializes the attributes of a new particle
   * @param position the starting position of the particle
   * @param velocity the starting velocity of the particle
   * @param color the color of the particle
   * @param radius the radius of the particle
   * @param mass the mass of the particle
   */
  Particle(const glm::vec2& position, const glm::vec2& velocity,
           const ci::Color& color, float radius, float mass);

  glm::vec2 GetPosition() const;

  glm::vec2 GetVelocity() const;

  ci::Color GetColor() const;

  float GetRadius() const;

  float GetMass() const;

  float GetSpeed() const;

  void SetVelocity(const glm::vec2& new_velocity);

  /**
   * Updates the position of a particle by changing the position of the particle
   * as if one unit of time had passed
   */
  void UpdatePosition();

  /**
   * Determines whether velocity should be getting large in magnitude or not and
   * adjusts the current velocity accordingly to the delta_velocity
   * @param delta_velocity the amount to adjust the current velocity by
   * @param should_increase_speed determines whether velocities should get bigger
   * or smaller with respect to magnitude
   */
  void UpdateVelocity(const glm::vec2& delta_velocity,
                      bool should_increase_speed);

 private:
  glm::vec2 position_;
  glm::vec2 velocity_;
  ci::Color color_;
  float radius_;
  float mass_;
};
}  // namespace idealgas