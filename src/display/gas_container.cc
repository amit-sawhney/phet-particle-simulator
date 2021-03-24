#include "display/gas_container.h"

namespace idealgas {

GasContainer::GasContainer(const std::vector<Particle*>& initial_particles,
                           size_t num_rand_particles,
                           const glm::vec2& top_left_corner,
                           const glm::vec2& bottom_right_corner,
                           float default_particle_radius,
                           float default_particle_mass,
                           const ci::Color& default_particle_color) {
  top_left_corner_ = top_left_corner;
  bottom_right_corner_ = bottom_right_corner;
  default_particle_radius_ = default_particle_radius;
  default_particle_mass_ = default_particle_mass;
  default_particle_color_ = default_particle_color;
  physics_ = CollisionPhysics(top_left_corner, bottom_right_corner);
  GasContainer::AddRandomParticles(num_rand_particles);

  particles_.insert(particles_.end(), initial_particles.begin(),
                    initial_particles.end());
}

GasContainer::GasContainer() = default;

GasContainer::~GasContainer() {
  particles_.clear();
}

void GasContainer::Display() const {
  for (Particle* current_particle : particles_) {
    ci::gl::color(current_particle->GetColor());
    ci::gl::drawSolidCircle(current_particle->GetPosition(),
                            current_particle->GetRadius());
  }
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(top_left_corner_, bottom_right_corner_));
}

void GasContainer::AdvanceOneFrame() {
  // Check if there are any collisions on this frame
  GasContainer::DetermineWallCollisions();
  GasContainer::DetermineParticleCollisions();

  // Update the position of all of the particles
  for (Particle* current_particle : particles_) {
    current_particle->UpdatePosition();
  }
}

std::vector<Particle*> GasContainer::GetParticles() {
  return particles_;
}

std::vector<Particle*> GasContainer::GetParticlesByColor(
    const ci::Color& color) {
  std::vector<Particle*> colored_particles;

  for (Particle* particle : particles_) {
    if (particle->GetColor() == color) {
      colored_particles.push_back(particle);
    }
  }

  return colored_particles;
}

void GasContainer::ModifyParticlesSpeed(const glm::vec2& delta_velocity,
                                        bool should_increase_speed) {
  for (Particle* current_particle : particles_) {
    current_particle->UpdateVelocity(delta_velocity, should_increase_speed);
  }
}

void GasContainer::DetermineParticleCollisions() {
  for (size_t particle_1_idx = 0; particle_1_idx < particles_.size() - 1;
       ++particle_1_idx) {
    // Compare all of the particles with each the first particle past this point
    for (size_t particle_2_idx = particle_1_idx + 1;
         particle_2_idx < particles_.size(); ++particle_2_idx) {
      Particle* particle1 = particles_[particle_1_idx];
      Particle* particle2 = particles_[particle_2_idx];

      if (physics_.DidParticlesCollide(*particle1, *particle2)) {
        physics_.UpdateCollidedParticleVelocities(particle1, particle2);
      }
    }
  }
}

void GasContainer::DetermineWallCollisions() {
  for (Particle* current_particle : particles_) {
    float x_velocity = current_particle->GetVelocity().x;
    float y_velocity = current_particle->GetVelocity().y;

    if (physics_.IsParticleCollidingWithTopWall(*current_particle) ||
        physics_.IsParticleCollidingWithBottomWall(*current_particle)) {
      current_particle->SetVelocity(glm::vec2(x_velocity, -y_velocity));

      // Update y_velocity properly if particle is also colliding with sides
      y_velocity = -y_velocity;
    }

    if (physics_.IsParticleCollidingWithRightWall(*current_particle) ||
        physics_.IsParticleCollidingWithLeftWall(*current_particle)) {
      current_particle->SetVelocity(glm::vec2(-x_velocity, y_velocity));
    }
  }
}

void GasContainer::AddRandomParticles(size_t particle_count) {
  for (size_t particle = 0; particle < particle_count; ++particle) {
    glm::vec2 rand_position = GasContainer::CalculateRandomInitialPosition();
    GasContainer::AddParticleToContainer(rand_position);
  }
}

void GasContainer::AddParticleToContainer(const glm::vec2& new_position) {
  glm::vec2 new_velocity =
      GasContainer::CalculateRandomInitialVelocity(default_particle_radius_);
  ci::Color color(default_particle_color_);
  Particle* new_particle =
      new Particle(new_position, new_velocity, color, default_particle_radius_,
                   default_particle_mass_);
  particles_.push_back(new_particle);
}

void GasContainer::AddParticleToContainer(Particle* particle) {
  particles_.push_back(particle);
}

float GasContainer::GenerateRandomNumber(float min, float max) const {
  // code below derived from:
  // https://stackoverflow.com/questions/13408990/how-to-generate-random-float-number-in-c
  return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}

glm::vec2 GasContainer::CalculateRandomInitialPosition() const {
  size_t x_position = int(GasContainer::GenerateRandomNumber(
      float(top_left_corner_.x), float(bottom_right_corner_.y)));
  size_t y_position = int(GasContainer::GenerateRandomNumber(
      float(top_left_corner_.x), float(bottom_right_corner_.y)));
  return glm::vec2(x_position, y_position);
}

glm::vec2 GasContainer::CalculateRandomInitialVelocity(
    const float particle_radius) const {
  float velocity_reduction_factor = 0.7f;
  float velocity_range = velocity_reduction_factor * particle_radius;
  float x_velocity =
      GasContainer::GenerateRandomNumber(-velocity_range, velocity_range);
  float y_velocity =
      GasContainer::GenerateRandomNumber(-velocity_range, velocity_range);

  return glm::vec2(x_velocity, y_velocity);
}

}  // namespace idealgas
