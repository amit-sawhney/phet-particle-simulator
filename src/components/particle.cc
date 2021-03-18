#include "components/particle.h"

namespace idealgas {

Particle::Particle(const glm::vec2 &position, const glm::vec2 &velocity,
                   const ci::Color &color, float radius, float mass)
    : position_(position),
      velocity_(velocity),
      color_(color),
      radius_(radius),
      mass_(mass) {
}

glm::vec2 Particle::GetPosition() const {
  return position_;
}

glm::vec2 Particle::GetVelocity() const {
  return velocity_;
}

ci::Color Particle::GetColor() const {
  return color_;
}

float Particle::GetRadius() const {
  return radius_;
}

void Particle::UpdatePosition() {
  position_ += velocity_;
}

void Particle::SetVelocity(const glm::vec2 &new_velocity) {
  velocity_ = new_velocity;
}

void Particle::UpdateVelocity(const glm::vec2 &delta_velocity,
                              bool shouldIncreaseSpeed) {
  if (shouldIncreaseSpeed) {
    if (velocity_.x > 0) {
      velocity_.x += delta_velocity.x;
    } else if (velocity_.x < 0) {
      velocity_.x -= delta_velocity.x;
    }

    if (velocity_.y > 0) {
      velocity_.y += delta_velocity.y;
    } else if (velocity_.y < 0) {
      velocity_.y -= delta_velocity.y;
    }
  } else {
    if (velocity_.x > 0) {
      velocity_.x -= delta_velocity.x;
    } else if (velocity_.x < 0) {
      velocity_.x += delta_velocity.x;
    }

    if (velocity_.y > 0) {
      velocity_.y -= delta_velocity.y;
    } else if (velocity_.y < 0) {
      velocity_.y += delta_velocity.y;
    }
  }
}

}  // namespace idealgas