#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"

namespace idealgas {
class Histogram {
 public:
  Histogram();

  Histogram(std::vector<Particle> particles, glm::vec2 top_left_corner,
            glm::vec2 bottom_right_corner, size_t bin_width);

  void Draw();

 private:

  std::vector<size_t> BuildParticleBins(const std::vector<Particle>& particles);

  float CalculateFastestParticle(const std::vector<Particle>& particles);

  glm::vec2 top_left_corner_;
  glm::vec2 bottom_right_corner_;
  std::vector<size_t> particle_bins_;
  size_t bin_width_;
};
}  // namespace idealgas
