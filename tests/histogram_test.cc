#include "components/histogram.h"

#include <catch2/catch.hpp>

TEST_CASE("Histogram updates with particles properly") {
  std::vector<idealgas::Particle*> particles({});
  glm::vec2 top_left_corner(0, 0);
  glm::vec2 bottom_right_corner(100, 100);
  ci::Color color("white");
  size_t num = 4;
  float bin_width = 1;
  idealgas::Histogram histogram(particles, top_left_corner, bottom_right_corner,
                                bin_width, color, num);

  SECTION("Histogram with no particles") {
    std::vector<size_t> histogram_vector =
        histogram.UpdateParticleBins(particles);

    std::vector<size_t> expected_histogram({0});

    REQUIRE(histogram_vector.size() == 1);
    REQUIRE(expected_histogram == histogram_vector);
  }

  SECTION("Histogram with 1 bin for 1 slow particle") {
    std::vector<idealgas::Particle*> updated_particles;
    glm::vec2 position(10, 10);
    glm::vec2 velocity(.1, 0);
    float radius = 10.0f;
    float mass = 1.0f;

    idealgas::Particle* particle =
        new idealgas::Particle(position, velocity, color, radius, mass);

    updated_particles.push_back(particle);

    std::vector<size_t> histogram_vector =
        histogram.UpdateParticleBins(updated_particles);

    std::vector<size_t> expected_histogram({1});

    REQUIRE(histogram_vector.size() == 1);
    REQUIRE(expected_histogram == histogram_vector);
  }

  SECTION("Histogram with multiple bins for 1 fast particle") {
    std::vector<idealgas::Particle*> updated_particles;
    glm::vec2 position(10, 10);
    glm::vec2 velocity(1, 0);
    float radius = 10.0f;
    float mass = 1.0f;

    idealgas::Particle* particle =
        new idealgas::Particle(position, velocity, color, radius, mass);

    updated_particles.push_back(particle);

    std::vector<size_t> histogram_vector =
        histogram.UpdateParticleBins(updated_particles);

    std::vector<size_t> expected_histogram({0, 1});

    REQUIRE(histogram_vector.size() == 2);
    REQUIRE(expected_histogram == histogram_vector);
  }

  SECTION("Histogram dynamically changes size") {
    std::vector<idealgas::Particle*> updated_particles;
    glm::vec2 position(10, 10);
    glm::vec2 velocity(.1, 0);
    float radius = 10.0f;
    float mass = 1.0f;

    idealgas::Particle* particle =
        new idealgas::Particle(position, velocity, color, radius, mass);

    updated_particles.push_back(particle);

    std::vector<size_t> histogram_vector1 =
        histogram.UpdateParticleBins(updated_particles);

    std::vector<size_t> expected_histogram1({1});

    REQUIRE(histogram_vector1.size() == 1);
    REQUIRE(expected_histogram1 == histogram_vector1);

    glm::vec2 velocity2(10, 5);
    idealgas::Particle* particle2 =
        new idealgas::Particle(position, velocity2, color, radius, mass);

    updated_particles.push_back(particle2);

    std::vector<size_t> histogram_vector2 =
        histogram.UpdateParticleBins(updated_particles);

    std::vector<size_t> expected_histogram2(
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1});

    REQUIRE(histogram_vector2.size() == 12);
    REQUIRE(expected_histogram2 == histogram_vector2);
  }

  SECTION("Histogram with multiple particles spread over velocities") {
    std::vector<idealgas::Particle*> updated_particles;
    glm::vec2 position(10, 10);
    float radius = 10.0f;
    float mass = 1.0f;

    glm::vec2 velocity1(.1, 0);
    idealgas::Particle* particle1 =
        new idealgas::Particle(position, velocity1, color, radius, mass);

    updated_particles.push_back(particle1);

    glm::vec2 velocity2(2, 0);
    idealgas::Particle* particle2 =
        new idealgas::Particle(position, velocity2, color, radius, mass);

    updated_particles.push_back(particle2);

    glm::vec2 velocity3(5, 0);
    idealgas::Particle* particle3 =
        new idealgas::Particle(position, velocity3, color, radius, mass);

    updated_particles.push_back(particle3);

    glm::vec2 velocity4(5, 0);
    idealgas::Particle* particle4 =
        new idealgas::Particle(position, velocity4, color, radius, mass);

    updated_particles.push_back(particle4);

    std::vector<size_t> histogram_vector =
        histogram.UpdateParticleBins(updated_particles);

    std::vector<size_t> expected_histogram1({1, 0, 1, 0, 0, 2});

    REQUIRE(histogram_vector.size() == 6);
    REQUIRE(expected_histogram1 == histogram_vector);
  }
}