#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"

namespace idealgas {
/**
 * This class represents a singular Histogram on the simulation that will
 * properly model and render the particle speeds of a set of particles
 */
class Histogram {
 public:
  /**
   * Default constructor for Histogram to run IdealGasApp
   */
  Histogram();

  /**
   * Initialize histogram configuration by specifying the dimensions and
   * attributes of a singular histogram
   * @param particles the particles to place within the histogram
   * @param top_left_corner the top left corner of the histogram box
   * @param bottom_right_corner the bottom right corner of the histogram box
   * @param bin_width the width of each of the bins of particles
   * @param bin_color the color of each of the bins of particles
   */
  Histogram(const std::vector<Particle*>& particles,
            const glm::vec2& top_left_corner,
            const glm::vec2& bottom_right_corner, float bin_width,
            const ci::Color& bin_color);

  /**
   * Draws the Histogram on the screen of cinder according to configuration
   */
  void Draw();

  /**
   * Updates each of the bins after a frame rate to represent the new bins after
   * collisions
   * @param particles the particles to be placed into this histogram
   * @return a vector representing the number of particles in each bin
   */
  std::vector<size_t> UpdateParticleBins(
      const std::vector<Particle*>& particles);

  /**
   * Calculates the number of bins that will be displayed based on bin width
   * @param particles the particles to be placed into the histogram
   * @return the number of bins in the histogram
   */
  size_t CalculateNumOfBins(const std::vector<Particle*>& particles);

 private:
  /**
   * Determines the fastest particle in the incoming set of particles
   * @param particles the incoming set of particles
   * @return the fastest particle speed
   */
  float CalculateFastestParticle(const std::vector<Particle*>& particles);

  /**
   * Determines which bin of particles has the most particles
   * @return the number of particles in that bin
   */
  size_t CalculateMostParticlesInSingleBin();

  /**
   * Draws the x axis label on the histogram
   */
  void DrawHistogramXAxisLabel(const ci::Color& text_color, float text_size,
                               ci::Font text_font);

  /**
   * Determines the values and location of each mark up the y axis
   */
  void DrawHistogramYAxisValues(const ci::Color& text_color, float text_size,
                                const ci::Font& text_font);

  /**
   * Draws the histogram
   */
  void DrawHistogramBins();

  glm::vec2 top_left_corner_;
  glm::vec2 bottom_right_corner_;
  float histogram_height_;
  float histogram_width_;
  std::vector<size_t> particle_bins_;
  float bin_width_;
  ci::Color bin_color_;
  size_t num_bins_;
  size_t num_y_axis_marks_ = 4;
};
}  // namespace idealgas
