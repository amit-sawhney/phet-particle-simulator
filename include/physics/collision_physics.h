#pragma once

#include "cinder/gl/gl.h"
#include "components/particle.h"

namespace idealgas {

/**
 * This class represents the physical nature of how particles behave within our
 * environment
 */
class CollisionPhysics {
 public:
  /**
   * Contextualizes the physics within a bounded region of space
   * @param top_left_corner the top_left_corner_ of the contained system
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
   * @param particle1 the particle1 in the container
   * @param particle2 the particle2 in the container
   * @return true if particles are touching, else false
   */
  bool DidParticlesCollide(const Particle& particle1,
                           const Particle& particle2) const;

  /**
   * Calculates and updates the velocities for two collided particles
   * @param particle1 the first particle that collided in the container
   * @param particle2 the second particle that collided in the container
   */
  void UpdateCollidedParticleVelocities(Particle& particle1,
                                        Particle& particle2);
  /**
   * Determines if a particle is colliding the top wall of the container
   * @param particle the particle in the container
   * @return true if the particle is touching the top wall, else false
   */
  bool IsParticleCollidingWithTopWall(const Particle& particle) const;

  /**
   * Determines if a particle is colliding the left wall of the container
   * @param particle the particle in the container
   * @return true if the particle is touching the left wall, else false
   */
  bool IsParticleCollidingWithLeftWall(const Particle& particle) const;

  /**
   * Determines if a particle is colliding the right wall of the container
   * @param particle the particle in the container
   * @return true if the particle is touching the right wall, else false
   */
  bool IsParticleCollidingWithRightWall(const Particle& particle) const;

  /**
   * Determines if a particle is colliding the bottom wall of the container
   * @param particle the particle in the container
   * @return true if the particle is touching the right wall, else false
   */
  bool IsParticleCollidingWithBottomWall(const Particle& particle) const;

 private:
  float left_wall_;
  float right_wall_;
  float top_wall_;
  float bottom_wall_;
};
}  // namespace idealgas