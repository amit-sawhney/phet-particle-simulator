#include "display/gas_container.h"

namespace idealgas {

using glm::vec2;

GasContainer::GasContainer(std::vector<Particle> initial_particles,
                           int num_rand_particles,
                           const glm::vec2& top_left_corner,
                           const glm::vec2& bottom_right_corner,
                           float default_particle_radius,
                           float default_particle_mass,
                           const ci::Color& default_particle_color) {
  firstCornerPoint_ = top_left_corner;
  secondCornerPoint_ = bottom_right_corner;
  particleRadius_ = default_particle_radius;
  particleMass_ = default_particle_mass;
  particleColor_ = default_particle_color;
  physics_ = CollisionPhysics(top_left_corner, bottom_right_corner);
  GasContainer::AddRandomParticles(num_rand_particles);

  particles_.insert(particles_.end(), initial_particles.begin(),
                    initial_particles.end());
}

GasContainer::GasContainer() = default;

void GasContainer::Display() const {
  for (Particle current_particle : particles_) {
    ci::gl::color(current_particle.GetColor());
    ci::gl::drawSolidCircle(current_particle.GetPosition(),
                            current_particle.GetRadius());
  }
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(firstCornerPoint_, secondCornerPoint_));
}

void GasContainer::AdvanceOneFrame() {
  // Check if there are any collisions on this frame
  GasContainer::DetermineWallCollisions();
  GasContainer::DetermineParticleCollisions();

  // Update the position of all of the particles
  for (Particle& current_particle : particles_) {
    current_particle.UpdatePosition();
  }
}

std::vector<Particle> GasContainer::GetParticles() {
  return particles_;
}

void GasContainer::ModifyParticlesSpeed(const glm::vec2& delta_velocity,
                                        bool shouldIncreaseSpeed) {
  for (Particle& current_particle : particles_) {
    current_particle.UpdateVelocity(delta_velocity, shouldIncreaseSpeed);
  }
}

void GasContainer::DetermineParticleCollisions() {
  for (size_t particle_1_idx = 0; particle_1_idx < particles_.size() - 1;
       ++particle_1_idx) {
    for (size_t particle_2_idx = particle_1_idx + 1;
         particle_2_idx < particles_.size(); ++particle_2_idx) {
      Particle& first_particle = particles_[particle_1_idx];
      Particle& second_particle = particles_[particle_2_idx];

      if (physics_.DidParticlesCollide(first_particle, second_particle)) {
        physics_.UpdateCollidedParticleVelocities(first_particle,
                                                  second_particle);
      }
    }
  }
}

void GasContainer::DetermineWallCollisions() {
  for (Particle& current_particle : particles_) {
    float x_velocity = current_particle.GetVelocity().x;
    float y_velocity = current_particle.GetVelocity().y;

    if (physics_.IsParticleCollidingWithTopWall(current_particle) ||
        physics_.IsParticleCollidingWithBottomWall(current_particle)) {
      current_particle.SetVelocity(glm::vec2(x_velocity, -y_velocity));
      y_velocity = -y_velocity;
    }

    if (physics_.IsParticleCollidingWithRightWall(current_particle) ||
        physics_.IsParticleCollidingWithLeftWall(current_particle)) {
      current_particle.SetVelocity(glm::vec2(-x_velocity, y_velocity));
    }
  }
}

void GasContainer::AddRandomParticles(int particle_count) {
  for (int particle = 0; particle < particle_count; ++particle) {
    glm::vec2 rand_position = GasContainer::CalculateRandomInitialPosition();
    GasContainer::AddParticleToContainer(rand_position);
  }
}

void GasContainer::AddParticleToContainer(const glm::vec2& new_position) {
  glm::vec2 new_velocity =
      GasContainer::CalculateRandomInitialVelocity(particleRadius_);
  ci::Color color(particleColor_);
  Particle new_particle(new_position, new_velocity, color, particleRadius_,
                        particleMass_);
  particles_.push_back(new_particle);
}

float GasContainer::GenerateRandomNumber(float min, float max) const {
  // code below derived from:
  // https://stackoverflow.com/questions/13408990/how-to-generate-random-float-number-in-c
  return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}

glm::vec2 GasContainer::CalculateRandomInitialPosition() const {
  int x_position = int(GasContainer::GenerateRandomNumber(
      float(firstCornerPoint_.x), float(secondCornerPoint_.y)));
  int y_position = int(GasContainer::GenerateRandomNumber(
      float(firstCornerPoint_.x), float(secondCornerPoint_.y)));
  return glm::vec2(x_position, y_position);
}

glm::vec2 GasContainer::CalculateRandomInitialVelocity(
    const float particle_radius) const {
  float velocity_range = 0.7f * particle_radius;
  float x_velocity =
      GasContainer::GenerateRandomNumber(-velocity_range, velocity_range);
  float y_velocity =
      GasContainer::GenerateRandomNumber(-velocity_range, velocity_range);

  return glm::vec2(x_velocity, y_velocity);
}

}  // namespace idealgas