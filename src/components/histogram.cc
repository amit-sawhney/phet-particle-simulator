#include "components/histogram.h"

#include <utility>

namespace idealgas {

Histogram::Histogram() = default;

Histogram::Histogram(const std::vector<Particle*>& particles,
                     const glm::vec2& top_left_corner,
                     const glm::vec2& bottom_right_corner, float bin_width,
                     const ci::Color& bin_color, size_t num_y_axis_marks) {
  top_left_corner_ = top_left_corner;
  bottom_right_corner_ = bottom_right_corner;
  histogram_height_ = bottom_right_corner_.y - top_left_corner_.y;
  histogram_width_ = bottom_right_corner_.x - top_left_corner_.x;
  bin_width_ = bin_width;
  bin_color_ = bin_color;
  num_y_axis_marks_ = num_y_axis_marks;
  num_bins_ = CalculateNumOfBins(particles);
}

void Histogram::Draw() {
  ci::Color border_color("white");
  ci::gl::color(border_color);
  ci::gl::drawStrokedRect(ci::Rectf(top_left_corner_, bottom_right_corner_));
  ci::gl::color(bin_color_);

  ci::Color text_color("white");
  float text_size = 25.0f;
  ci::Font text_font("Arial", text_size);

  DrawHistogramYAxisValues(text_color, text_size, text_font);

  DrawHistogramXAxisLabel(text_color, text_size, text_font);

  DrawHistogramBins();
}

void Histogram::DrawHistogramXAxisLabel(const ci::Color& text_color,
                                        float text_size, ci::Font text_font) {
  std::string text_label = "Speed of particles";

  float x_position = top_left_corner_.x + (histogram_width_) / 2;
  float y_position = bottom_right_corner_.y + text_size;

  ci::gl::drawStringCentered(text_label, glm::vec2(x_position, y_position),
                             text_color, std::move(text_font));
}

void Histogram::DrawHistogramYAxisValues(const ci::Color& text_color,
                                         float text_size,
                                         const ci::Font& text_font) {
  size_t highest_bin_height = CalculateMostParticlesInSingleBin();
  float y_interval = histogram_height_ / num_y_axis_marks_;

  // Calculates the common difference to be displayed on the y axis
  float mark_value_difference = float(highest_bin_height) / num_y_axis_marks_;

  size_t count_looped = 0;
  for (float mark = 0; mark <= histogram_height_; mark += y_interval) {
    // Calculates the sequence index the mark value is at
    size_t mark_value = int(mark_value_difference * count_looped);

    std::string mark_label = std::to_string(mark_value);
    float x_position = top_left_corner_.x - text_size;
    float y_position = bottom_right_corner_.y - mark;

    ci::gl::drawStringRight(mark_label, glm::vec2(x_position, y_position),
                            text_color, text_font);
    ++count_looped;
  }
}

void Histogram::DrawHistogramBins() {
  size_t display_width = size_t(histogram_width_) / num_bins_;

  size_t max_particles = CalculateMostParticlesInSingleBin();

  for (size_t bin = 0; bin < particle_bins_.size(); ++bin) {
    size_t num_particles = particle_bins_[bin];
    float bin_height = num_particles / float(max_particles) * histogram_height_;

    float top_left_x = top_left_corner_.x + float(bin + display_width * bin);
    float top_left_y = bottom_right_corner_.y - bin_height;
    glm::vec2 top_left_bin_corner(top_left_x, top_left_y);

    float bottom_right_x = top_left_corner_.x + display_width * (bin + 1);
    glm::vec2 bottom_right_bin_corner(bottom_right_x, bottom_right_corner_.y);
    ci::gl::drawSolidRect(
        ci::Rectf(top_left_bin_corner, bottom_right_bin_corner));
  }
}

std::vector<size_t> Histogram::UpdateParticleBins(
    const std::vector<Particle*>& particles) {
  num_bins_ = CalculateNumOfBins(particles);
  particle_bins_ = std::vector<size_t>(num_bins_, 0);

  for (Particle* particle : particles) {
    size_t bin = int(particle->GetSpeed() / bin_width_);
    ++particle_bins_[bin];
  }

  return particle_bins_;
}

size_t Histogram::CalculateNumOfBins(const std::vector<Particle*>& particles) {
  float max_speed = CalculateFastestParticle(particles);

  return size_t(max_speed / bin_width_) + 1;
}

size_t Histogram::CalculateMostParticlesInSingleBin() {
  size_t max_particles = 0;

  for (const size_t& particle_bin : particle_bins_) {
    max_particles = std::max(particle_bin, max_particles);
  }

  return max_particles;
}

float Histogram::CalculateFastestParticle(
    const std::vector<Particle*>& particles) {
  float max_speed = -1;

  for (Particle* particle : particles) {
    max_speed = std::max(particle->GetSpeed(), max_speed);
  }

  return max_speed;
}

}  // namespace idealgas
