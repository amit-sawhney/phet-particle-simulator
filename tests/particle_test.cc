#include <display/gas_container.h>

#include <catch2/catch.hpp>

TEST_CASE("Particle moves properly according to the velocity") {
  const glm::vec2 position(10, 10);
  const ci::Color color("red");
  float radius = 10.0f;
  float mass = 1.0f;

  SECTION("Particle moves towards bottom wall with positive y velocity") {
    const glm::vec2 velocity(0, 10);

    idealgas::Particle particle(position, velocity, color, radius, mass);
    particle.UpdatePosition();

    REQUIRE(particle.GetPosition().y == 20.0f);
  }

  SECTION("Particle moves towards top wall with negative y velocity") {
    const glm::vec2 velocity(0, -10);

    idealgas::Particle particle(position, velocity, color, radius, mass);
    particle.UpdatePosition();

    REQUIRE(particle.GetPosition().y == 0.0f);
  }

  SECTION("Particle moves towards left wall with negative x velocity") {
    const glm::vec2 velocity(-10, 0);

    idealgas::Particle particle(position, velocity, color, radius, mass);
    particle.UpdatePosition();

    REQUIRE(particle.GetPosition().x == 0.0f);
  }

  SECTION("Particle moves towards right wall with positive x velocity") {
    const glm::vec2 velocity(10, 0);

    idealgas::Particle particle(position, velocity, color, radius, mass);
    particle.UpdatePosition();

    REQUIRE(particle.GetPosition().x == 20.0f);
  }

  SECTION("Particle moves towards top left corner with negative velocity") {
    const glm::vec2 velocity(-10, -10);

    idealgas::Particle particle(position, velocity, color, radius, mass);
    particle.UpdatePosition();

    REQUIRE(particle.GetPosition().x == 0.0f);
    REQUIRE(particle.GetPosition().y == 0.0f);
  }

  SECTION("Particle moves towards bottom right corner with positive velocity") {
    const glm::vec2 velocity(10, 10);

    idealgas::Particle particle(position, velocity, color, radius, mass);
    particle.UpdatePosition();

    REQUIRE(particle.GetPosition().x == 20.0f);
    REQUIRE(particle.GetPosition().y == 20.0f);
  }
}

TEST_CASE("Particle velocity is modified according to magnitude") {
  const glm::vec2 position(10, 10);
  const ci::Color color("red");
  float radius = 10.0f;
  float mass = 1.0f;

  SECTION("Negative particle y velocity increases on slow down") {
    const glm::vec2 velocity(0, -10);
    const glm::vec2 delta_velocity(0, 5);

    idealgas::Particle particle(position, velocity, color, radius, mass);
    particle.UpdateVelocity(delta_velocity, false);

    REQUIRE(particle.GetVelocity().y == -5.0f);
  }

  SECTION("Negative particle y velocity decreases on speed up") {
    const glm::vec2 velocity(0, -10);
    const glm::vec2 delta_velocity(0, 5);

    idealgas::Particle particle(position, velocity, color, radius, mass);
    particle.UpdateVelocity(delta_velocity, true);

    REQUIRE(particle.GetVelocity().y == -15.0f);
  }

  SECTION("Positive particle y velocity decreases on slow down") {
    const glm::vec2 velocity(0, 10);
    const glm::vec2 delta_velocity(0, 5);

    idealgas::Particle particle(position, velocity, color, radius, mass);
    particle.UpdateVelocity(delta_velocity, false);

    REQUIRE(particle.GetVelocity().y == 5.0f);
  }

  SECTION("Positive particle y velocity increases on speed up") {
    const glm::vec2 velocity(0, 10);
    const glm::vec2 delta_velocity(0, 5);

    idealgas::Particle particle(position, velocity, color, radius, mass);
    particle.UpdateVelocity(delta_velocity, true);

    REQUIRE(particle.GetVelocity().y == 15.0f);
  }

  SECTION("Negative particle x velocity increases on slow down") {
    const glm::vec2 velocity(-10, 0);
    const glm::vec2 delta_velocity(5, 0);

    idealgas::Particle particle(position, velocity, color, radius, mass);
    particle.UpdateVelocity(delta_velocity, false);

    REQUIRE(particle.GetVelocity().x == -5.0f);
  }

  SECTION("Negative particle x velocity decreases on speed up") {
    const glm::vec2 velocity(-10, 0);
    const glm::vec2 delta_velocity(5, 0);

    idealgas::Particle particle(position, velocity, color, radius, mass);
    particle.UpdateVelocity(delta_velocity, true);

    REQUIRE(particle.GetVelocity().x == -15.0f);
  }

  SECTION("Positive particle x velocity decreases on slow down") {
    const glm::vec2 velocity(10, 0);
    const glm::vec2 delta_velocity(5, 0);

    idealgas::Particle particle(position, velocity, color, radius, mass);
    particle.UpdateVelocity(delta_velocity, false);

    REQUIRE(particle.GetVelocity().x == 5.0f);
  }

  SECTION("Positive particle x velocity increases on speed up") {
    const glm::vec2 velocity(10, 0);
    const glm::vec2 delta_velocity(5, 0);

    idealgas::Particle particle(position, velocity, color, radius, mass);
    particle.UpdateVelocity(delta_velocity, true);

    REQUIRE(particle.GetVelocity().x == 15.0f);
  }

  SECTION("Particle with no velocity does not change on velocity update") {
    const glm::vec2 velocity(0, 0);
    const glm::vec2 delta_velocity(5, 5);

    idealgas::Particle particle(position, velocity, color, radius, mass);
    particle.UpdateVelocity(delta_velocity, true);

    REQUIRE(particle.GetVelocity().x == 0.0f);
    REQUIRE(particle.GetVelocity().y == 0.0f);
  }
}
