#include "components/histogram.h"

#include <components/particle.h>

namespace idealgas {

Histogram::Histogram() = default;

Histogram::Histogram(std::vector<Particle> particles, glm::vec2 top_left_corner,
                     glm::vec2 bottom_right_corner, size_t bin_width,
                     ci::Color bin_color) {
  top_left_corner_ = top_left_corner;
  bottom_right_corner_ = bottom_right_corner;
  bin_width_ = bin_width;
  bin_color_ = bin_color;

  num_bins_ = CalculateNumOfBins(particles);

  UpdateParticleBins(particles);
}

void Histogram::Draw() {
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(top_left_corner_, bottom_right_corner_));
  ci::gl::color(bin_color_);
  size_t bin_display_width =
      size_t((bottom_right_corner_.x - top_left_corner_.x)) / num_bins_;

  for (size_t bin = 0; bin < particle_bins_.size(); ++bin) {
    glm::vec2 top_left_bin_corner(
        top_left_corner_.x + bin + bin_display_width * bin,
        bottom_right_corner_.y - particle_bins_[bin]);

    glm::vec2 bottom_right_bin_corner(
        top_left_corner_.x + bin_display_width * (bin + 1),
        bottom_right_corner_.y);
    ci::gl::drawSolidRect(
        ci::Rectf(top_left_bin_corner, bottom_right_bin_corner));
  }
}

std::vector<size_t> Histogram::UpdateParticleBins(
    const std::vector<Particle>& particles) {
  num_bins_ = CalculateNumOfBins(particles);
  particle_bins_ = std::vector<size_t>(num_bins_, 0);

  for (const Particle& particle : particles) {
    size_t bin = size_t(particle.GetSpeed() / bin_width_);
    ++particle_bins_[bin];
  }

  return particle_bins_;
}

size_t Histogram::CalculateNumOfBins(const std::vector<Particle>& particles) {
  float max_speed = CalculateFastestParticle(particles);

  return size_t(max_speed) / bin_width_ + 1;
}

float Histogram::CalculateFastestParticle(
    const std::vector<Particle>& particles) {
  float max_speed = -1;

  for (const Particle& particle : particles) {
    max_speed = std::max(particle.GetSpeed(), max_speed);
  }

  return max_speed;
}

}  // namespace idealgas
