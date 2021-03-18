#pragma once

#include "cinder/gl/gl.h"
#include "components/particle.h"

namespace idealgas {

/**
 * This class represents the physical natural of how particles behave within our
 * environment
 */
class CollisionPhysics {
 public:
  /**
   * Contextualizes the physics within a bounded region of space
   * @param top_left_corner the top_left_corner of the contained system
   * @param bottom_right_corner the bottom_right_corner of the contained system
   */
  CollisionPhysics(const glm::vec2& top_left_corner,
                   const glm::vec2& bottom_right_corner);

  /**
   * A default constructor for collision physics
   */
  CollisionPhysics();

  /**
   * Calculates whether two passed particles are touching or not
   * @param first_particle the first_particle in the container
   * @param second_particle the second_particle in the container
   * @return true if particles are touching, else false
   */
  bool DidParticlesCollide(Particle first_particle,
                           Particle second_particle) const;

  /**
   * Calculates and updates the velocities for two collided particles
   * @param first_particle the first particle that collided in the container
   * @param second_particle the second particle that collided in the container
   */
  void UpdateCollidedParticleVelocities(Particle& first_particle,
                                        Particle& second_particle);
  /**
   * Determines if a particle is colliding the top wall of the container
   * @param particle the particle in the container
   * @return true if the particle is touching the top wall, else false
   */
  bool IsParticleCollidingWithTopWall(Particle particle) const;

  /**
   * Determines if a particle is colliding the left wall of the container
   * @param particle the particle in the container
   * @return true if the particle is touching the left wall, else false
   */
  bool IsParticleCollidingWithLeftWall(Particle particle) const;

  /**
   * Determines if a particle is colliding the right wall of the container
   * @param particle the particle in the container
   * @return true if the particle is touching the right wall, else false
   */
  bool IsParticleCollidingWithRightWall(Particle particle) const;

  /**
   * Determines if a particle is colliding the bottom wall of the container
   * @param particle the particle in the container
   * @return true if the particle is touching the right wall, else false
   */
  bool IsParticleCollidingWithBottomWall(Particle particle) const;

 private:
  float leftWall_;
  float rightWall_;
  float topWall_;
  float bottomWall_;
};
}  // namespace idealgas