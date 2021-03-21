#include "components/histogram.h"

#include <components/particle.h>

namespace idealgas {

Histogram::Histogram() = default;

Histogram::Histogram(std::vector<Particle> particles, glm::vec2 top_left_corner,
                     glm::vec2 bottom_right_corner, size_t bin_width) {
  top_left_corner_ = top_left_corner;
  bottom_right_corner_ = bottom_right_corner;
  bin_width_ = bin_width;

  particle_bins_ = BuildParticleBins(particles);
}

void Histogram::Draw() {
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(top_left_corner_, bottom_right_corner_));

  for (size_t bin = 0; bin < particle_bins_.size(); ++bin) {
    glm::vec2 top_left_bin_corner(
        top_left_corner_.x + bin + 20 * bin,
        bottom_right_corner_.y - particle_bins_[bin]);
    glm::vec2 bottom_right_bin_corner(top_left_corner_.x + 20,
                                      bottom_right_corner_.y);
    ci::gl::drawSolidRect(
        ci::Rectf(top_left_bin_corner, bottom_right_bin_corner));
  }
}

std::vector<size_t> Histogram::BuildParticleBins(
    const std::vector<Particle>& particles) {
  float max_speed = CalculateFastestParticle(particles);

  size_t num_bins = size_t(max_speed) / bin_width_ + 1;

  std::vector<size_t> particle_bins(num_bins, 0);

  for (const Particle& particle : particles) {
    size_t bin = size_t(particle.GetSpeed() / bin_width_);
    ++particle_bins[bin];
  }

  return particle_bins;
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
