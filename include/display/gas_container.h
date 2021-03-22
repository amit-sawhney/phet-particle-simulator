#pragma once

#include "cinder/gl/gl.h"
#include "components/particle.h"
#include "physics/collision_physics.h"

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  /**
   * Initializes a container for particles to exist within and generates the
   * starting conditions for the container given a specific set of parameters
   * @param initial_particles the locations of all of the initial particles to
   * specifically render in the container
   * @param num_rand_particles the number of random particles to generate within
   * the container
   * @param top_left_corner the coordinate for the top left corner of the
   * container
   * @param bottom_right_corner the coordinate for the bottom right corner of
   * the container
   * @param default_particle_radius the default default particle_radius to
   * assign to the generated particles
   * @param default_particle_mass the default particle mass to assign to the
   * generated particles
   * @param default_particle_color the default particle color to assign to the
   * generated particles
   */
  GasContainer(std::vector<Particle> initial_particles, int num_rand_particles,
               const glm::vec2& top_left_corner,
               const glm::vec2& bottom_right_corner,
               float default_particle_radius, float default_particle_mass,
               const ci::Color& default_particle_color);

  /**
   * A default constructor as required by the Ideal Gas class
   */
  GasContainer();

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  /**
   * Updates the velocity of all of the particles according to a global
   * velocity change
   * @param delta_velocity the amount to change all of the velocities by
   * @param should_increase_speed whether or not the velocities should increase
   * or decrease in magnitude
   */
  void ModifyParticlesSpeed(const glm::vec2& delta_velocity,
                            bool should_increase_speed);

  /**
   * Adds a specific particle configuration to the container
   * @param particle the particle configuration to add to the container
   */
  void AddParticleToContainer(const Particle& particle);

  std::vector<Particle> GetParticles();

  std::vector<Particle> GetParticlesByColor(ci::Color color);

 private:
  /**
   * Generates a specific amount of particles randomly positioned in the
   * container
   * @param particle_count the number of random particles to add
   */
  void AddRandomParticles(int particle_count);

  /**
   * Calculates a random initial position for a particle within the container
   * bounds
   * @return a random position within the container
   */
  glm::vec2 CalculateRandomInitialPosition() const;

  /**
   * Calculates a random initial velocity for a particle based on its radius
   * size
   * @param particle_radius the radius of the particle to base the velocity off
   * of
   * @return a random velocity in component form
   */
  glm::vec2 CalculateRandomInitialVelocity(const float particle_radius) const;

  /**
   * Adds a singular particle to the container at a certain position
   * @param new_position the position on the board to place the particle at
   */
  void AddParticleToContainer(const glm::vec2& new_position);

  /**
   * Generates a random number in between a min and max value
   * @param min the minimum value the number can be
   * @param max the maximum value the number can be
   * @return the randomly generates number
   */
  float GenerateRandomNumber(float min, float max) const;

  /**
   * Determines what particles during a frame have collided with the wall and
   * updates their velocities correspondingly
   * @param particles the current state of all of the particles within the
   * container
   */
  void DetermineWallCollisions();

  /**
   * Determines what particles during a frame have collided with each other
   * @param particles the current state of all of the particles within the
   * container
   */
  void DetermineParticleCollisions();

  std::vector<Particle> particles_;
  glm::vec2 top_left_corner_;
  glm::vec2 bottom_right_corner_;
  float default_particle_radius_;
  float default_particle_mass_;
  ci::Color default_particle_color_;
  CollisionPhysics physics_;
};

}  // namespace idealgas
