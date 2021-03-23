#include "components/histogram.h"

namespace idealgas {

Histogram::Histogram() = default;

Histogram::Histogram(const std::vector<Particle*>& particles,
                     const glm::vec2& top_left_corner,
                     const glm::vec2& bottom_right_corner, float bin_width,
                     const ci::Color& bin_color) {
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

  float histogram_height = bottom_right_corner_.y - top_left_corner_.y;

  size_t highest_bin_height = CalculateMostParticlesInSingleBin();
  float y_interval = histogram_height / num_y_axis_marks_;

  if (y_interval == 0) {
    y_interval = 10;
  }

  int count_looped = 0;
  for (float mark = 0; mark <= histogram_height; mark += y_interval) {
    int mark_value = 0;

    if (count_looped != 0) {
      mark_value =
          int(highest_bin_height -
              highest_bin_height / ((num_y_axis_marks_) * (count_looped)));
    }

    std::string markLabel = std::to_string(mark_value);
    ci::gl::drawStringRight(
        markLabel,
        glm::vec2(top_left_corner_.x - 20, bottom_right_corner_.y - mark),
        ci::Color("white"), ci::Font("Arial", 20));
    ++count_looped;
  }

  DrawHistogramTitle();

  DrawHistogramBins();
}

void Histogram::DrawHistogramTitle() {
  float margin_top = 20.0f;

  std::string xAxisLabel = "Speed of particles";
  ci::gl::drawStringCentered(
      xAxisLabel,
      glm::vec2(top_left_corner_.x +
                    (bottom_right_corner_.x - top_left_corner_.x) / 2,
                bottom_right_corner_.y + margin_top),
      ci::Color("white"), ci::Font("Arial", 25));
}

void Histogram::DrawHistogramBins() {
  size_t bin_display_width =
      size_t((bottom_right_corner_.x - top_left_corner_.x)) / num_bins_;

  size_t most_particles_in_bin = CalculateMostParticlesInSingleBin();
  float histogram_height = bottom_right_corner_.y - top_left_corner_.y;

  for (size_t bin = 0; bin < particle_bins_.size(); ++bin) {
    float bin_height =
        particle_bins_[bin] / float(most_particles_in_bin) * histogram_height;
    glm::vec2 top_left_bin_corner(
        top_left_corner_.x + bin + bin_display_width * bin,
        bottom_right_corner_.y - bin_height);

    glm::vec2 bottom_right_bin_corner(
        top_left_corner_.x + bin_display_width * (bin + 1),
        bottom_right_corner_.y);
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
  size_t max_num_of_particles = 0;

  for (const unsigned int& particle_bin : particle_bins_) {
    max_num_of_particles = std::max(particle_bin, max_num_of_particles);
  }

  return max_num_of_particles;
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
