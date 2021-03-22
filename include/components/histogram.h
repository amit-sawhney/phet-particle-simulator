#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"

namespace idealgas {
class Histogram {
 public:
  Histogram();

  Histogram(const std::vector<Particle*>& particles, const glm::vec2& top_left_corner,
            const glm::vec2& bottom_right_corner, float bin_width, const ci::Color& bin_color);

  void Draw();

  std::vector<size_t> UpdateParticleBins(
      const std::vector<Particle*>& particles);

  size_t CalculateNumOfBins(const std::vector<Particle*>& particles);

 private:
  float CalculateFastestParticle(const std::vector<Particle*>& particles);

  glm::vec2 top_left_corner_;
  glm::vec2 bottom_right_corner_;
  std::vector<size_t> particle_bins_;
  float bin_width_;
  ci::Color bin_color_;
  size_t num_bins_;
};
}  // namespace idealgas
