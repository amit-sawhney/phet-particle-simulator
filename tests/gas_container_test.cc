#include <display/gas_container.h>

#include <catch2/catch.hpp>

TEST_CASE("Test constructor initializes particle container") {
  const glm::vec2 top_left_corner(0, 0);
  const glm::vec2 bottom_right_corner(100, 100);
  float radius = 10.0f;
  float mass = 1.0f;
  const ci::Color color("orange");

  const glm::vec2 particle1_position(10, 0);
  const glm::vec2 velocity1_position(0, 0);
  idealgas::Particle particle1(particle1_position, velocity1_position, color,
                               radius, mass);

  const glm::vec2 particle2_position(10, 10);
  const glm::vec2 velocity2_position(0, 0);
  idealgas::Particle particle2(particle2_position, velocity2_position, color,
                               radius, mass);

  SECTION("Container tracks initial particles passed to constructor") {
    std::vector<idealgas::Particle*> initial_particles(
        {&particle1, &particle2});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    REQUIRE(container.GetParticles().size() == 2);
    REQUIRE(particle1.GetPosition() ==
            container.GetParticles().at(0)->GetPosition());
    REQUIRE(particle1.GetVelocity() ==
            container.GetParticles().at(0)->GetVelocity());
    REQUIRE(particle2.GetPosition() ==
            container.GetParticles().at(1)->GetPosition());
    REQUIRE(particle2.GetVelocity() ==
            container.GetParticles().at(1)->GetVelocity());
  }

  SECTION("Container contains random initialized particles within container") {
    std::vector<idealgas::Particle*> initial_particles({});

    idealgas::GasContainer container(initial_particles, 10, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    REQUIRE(container.GetParticles().size() == 10);
    for (idealgas::Particle* particle : container.GetParticles()) {
      REQUIRE(particle->GetPosition().x >= top_left_corner.x);
      REQUIRE(particle->GetPosition().x <= bottom_right_corner.x);
      REQUIRE(particle->GetPosition().y >= top_left_corner.y);
      REQUIRE(particle->GetPosition().y <= bottom_right_corner.y);
      REQUIRE(particle->GetSpeed() <= particle->GetRadius());
    }
  }
}

TEST_CASE("Particles collide with the container walls") {
  const glm::vec2 top_left_corner(0, 0);
  const glm::vec2 bottom_right_corner(100, 100);
  float radius = 10.0f;
  float mass = 1.0f;
  const ci::Color color("orange");

  SECTION("Particle collides with left wall") {
    const glm::vec2 particle_position(10, 10);
    const glm::vec2 particle_velocity(-1, 0);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    std::vector<idealgas::Particle*> initial_particles({&particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();
    const glm::vec2 expected_position(11, 10);

    REQUIRE(container.GetParticles().at(0)->GetPosition() == expected_position);
  }

  SECTION("Particle collides with right wall") {
    const glm::vec2 particle_position(90, 10);
    const glm::vec2 particle_velocity(1, 0);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    std::vector<idealgas::Particle*> initial_particles({&particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();
    const glm::vec2 expected_position(89, 10);

    REQUIRE(container.GetParticles().at(0)->GetPosition() == expected_position);
  }

  SECTION("Particle collides with top wall") {
    const glm::vec2 particle_position(10, 10);
    const glm::vec2 particle_velocity(0, -1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    std::vector<idealgas::Particle*> initial_particles({&particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();
    const glm::vec2 expected_position(10, 11);

    REQUIRE(container.GetParticles().at(0)->GetPosition() == expected_position);
  }

  SECTION("Particle collides with bottom wall") {
    const glm::vec2 particle_position(10, 90);
    const glm::vec2 particle_velocity(0, 1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    std::vector<idealgas::Particle*> initial_particles({&particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();
    const glm::vec2 expected_position(10, 89);

    REQUIRE(container.GetParticles().at(0)->GetPosition() == expected_position);
  }

  SECTION("Particle collides with top left corner") {
    const glm::vec2 particle_position(10, 10);
    const glm::vec2 particle_velocity(-1, -1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    std::vector<idealgas::Particle*> initial_particles({&particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();
    const glm::vec2 expected_position(11, 11);

    REQUIRE(container.GetParticles().at(0)->GetPosition() == expected_position);
  }

  SECTION("Particle collides with bottom right corner") {
    const glm::vec2 particle_position(90, 90);
    const glm::vec2 particle_velocity(1, 1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    std::vector<idealgas::Particle*> initial_particles({&particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();
    const glm::vec2 expected_position(89, 89);

    REQUIRE(container.GetParticles().at(0)->GetPosition() == expected_position);
  }

  SECTION("Particle collides with bottom left corner") {
    const glm::vec2 particle_position(10, 90);
    const glm::vec2 particle_velocity(-1, 1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    std::vector<idealgas::Particle*> initial_particles({&particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();
    const glm::vec2 expected_position(11, 89);

    REQUIRE(container.GetParticles().at(0)->GetPosition() == expected_position);
  }

  SECTION("Particle collides with top right corner") {
    const glm::vec2 particle_position(90, 10);
    const glm::vec2 particle_velocity(1, -1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    std::vector<idealgas::Particle*> initial_particles({&particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();
    const glm::vec2 expected_position(89, 11);

    REQUIRE(container.GetParticles().at(0)->GetPosition() == expected_position);
  }
}

TEST_CASE("Particles collide with other particles") {
  const glm::vec2 top_left_corner(0, 0);
  const glm::vec2 bottom_right_corner(100, 100);
  float radius = 10.0f;
  float mass = 1.0f;
  const ci::Color color("orange");

  SECTION("Particles collide vertically") {
    const glm::vec2 top_particle_position(20, 20);
    const glm::vec2 top_particle_velocity(0, 1);
    idealgas::Particle top_particle(top_particle_position,
                                    top_particle_velocity, color, radius, mass);

    const glm::vec2 bottom_particle_position(20, 30);
    const glm::vec2 bottom_particle_velocity(0, -1);
    idealgas::Particle bottom_particle(bottom_particle_position,
                                       bottom_particle_velocity, color, radius,
                                       mass);

    std::vector<idealgas::Particle*> initial_particles(
        {&top_particle, &bottom_particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();

    const glm::vec2 expected_top_position(20, 19);
    const glm::vec2 expected_bottom_position(20, 31);
    REQUIRE(container.GetParticles().at(0)->GetPosition() ==
            expected_top_position);
    REQUIRE(container.GetParticles().at(1)->GetPosition() ==
            expected_bottom_position);
  }

  SECTION("Particles collide horizontally") {
    const glm::vec2 left_particle_position(20, 20);
    const glm::vec2 top_particle_velocity(1, 0);
    idealgas::Particle left_particle(
        left_particle_position, top_particle_velocity, color, radius, mass);

    const glm::vec2 right_particle_position(30, 20);
    const glm::vec2 right_particle_velocity(-1, 0);
    idealgas::Particle right_particle(
        right_particle_position, right_particle_velocity, color, radius, mass);

    std::vector<idealgas::Particle*> initial_particles(
        {&left_particle, &right_particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();

    const glm::vec2 expected_left_position(19, 20);
    const glm::vec2 expected_right_position(31, 20);
    REQUIRE(container.GetParticles().at(0)->GetPosition() ==
            expected_left_position);
    REQUIRE(container.GetParticles().at(1)->GetPosition() ==
            expected_right_position);
  }

  SECTION("Particles collide diagonally to top right and bottom left corner") {
    const glm::vec2 top_particle_position(30, 30);
    const glm::vec2 top_particle_velocity(1, -1);
    idealgas::Particle top_particle(top_particle_position,
                                    top_particle_velocity, color, radius, mass);

    const glm::vec2 bottom_particle_position(40, 20);
    const glm::vec2 bottom_particle_velocity(-1, 1);
    idealgas::Particle bottom_particle(bottom_particle_position,
                                       bottom_particle_velocity, color, radius,
                                       mass);

    std::vector<idealgas::Particle*> initial_particles(
        {&top_particle, &bottom_particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();

    const glm::vec2 expected_top_position(29, 31);
    const glm::vec2 expected_bottom_position(41, 19);
    REQUIRE(container.GetParticles().at(0)->GetPosition() ==
            expected_top_position);
    REQUIRE(container.GetParticles().at(1)->GetPosition() ==
            expected_bottom_position);
  }

  SECTION("Particles collide diagonally to top left and bottom right corner") {
    const glm::vec2 top_particle_position(20, 20);
    const glm::vec2 top_particle_velocity(1, 1);
    idealgas::Particle top_particle(top_particle_position,
                                    top_particle_velocity, color, radius, mass);

    const glm::vec2 bottom_particle_position(30, 30);
    const glm::vec2 bottom_particle_velocity(-1, -1);
    idealgas::Particle bottom_particle(bottom_particle_position,
                                       bottom_particle_velocity, color, radius,
                                       mass);

    std::vector<idealgas::Particle*> initial_particles(
        {&top_particle, &bottom_particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();

    const glm::vec2 expected_top_position(19, 19);
    const glm::vec2 expected_bottom_position(31, 31);
    REQUIRE(container.GetParticles().at(0)->GetPosition() ==
            expected_top_position);
    REQUIRE(container.GetParticles().at(1)->GetPosition() ==
            expected_bottom_position);
  }
}

TEST_CASE("Particles don't collide with any environmental factors") {
  const glm::vec2 top_left_corner(0, 0);
  const glm::vec2 bottom_right_corner(100, 100);
  float radius = 10.0f;
  float mass = 1.0f;
  const ci::Color color("orange");

  SECTION("Particles don't collide with top wall when traveling down") {
    const glm::vec2 particle_position(10, 10);
    const glm::vec2 particle_velocity(0, 1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    std::vector<idealgas::Particle*> initial_particles({&particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();

    REQUIRE(container.GetParticles().at(0)->GetVelocity() == particle_velocity);
  }

  SECTION("Particles don't collide with right wall when moving left") {
    const glm::vec2 particle_position(90, 10);
    const glm::vec2 particle_velocity(-1, 0);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    std::vector<idealgas::Particle*> initial_particles({&particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();

    REQUIRE(container.GetParticles().at(0)->GetVelocity() == particle_velocity);
  }

  SECTION("Particles don't collide with left wall when moving right") {
    const glm::vec2 particle_position(10, 10);
    const glm::vec2 particle_velocity(1, 0);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    std::vector<idealgas::Particle*> initial_particles({&particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();

    REQUIRE(container.GetParticles().at(0)->GetVelocity() == particle_velocity);
  }

  SECTION("Particles don't collide with bottom wall when traveling up") {
    const glm::vec2 particle_position(10, 90);
    const glm::vec2 particle_velocity(0, -1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    std::vector<idealgas::Particle*> initial_particles({&particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();

    REQUIRE(container.GetParticles().at(0)->GetVelocity() == particle_velocity);
  }

  SECTION("Particles don't collide with bottom wall if 0 vertical velocity") {
    const glm::vec2 particle_position(10, 90);
    const glm::vec2 particle_velocity(1, 0);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    std::vector<idealgas::Particle*> initial_particles({&particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();

    REQUIRE(container.GetParticles().at(0)->GetPosition().y == 90);
  }

  SECTION("Particles don't collide with top wall if 0 vertical velocity") {
    const glm::vec2 particle_position(10, 10);
    const glm::vec2 particle_velocity(1, 0);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    std::vector<idealgas::Particle*> initial_particles({&particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();

    REQUIRE(container.GetParticles().at(0)->GetPosition().y == 10);
  }

  SECTION("Particles don't collide with left wall if 0 horizontal velocity") {
    const glm::vec2 particle_position(10, 10);
    const glm::vec2 particle_velocity(0, 1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    std::vector<idealgas::Particle*> initial_particles({&particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();

    REQUIRE(container.GetParticles().at(0)->GetPosition().x == 10);
  }

  SECTION("Particles don't collide with right wall if 0 horizontal velocity") {
    const glm::vec2 particle_position(90, 10);
    const glm::vec2 particle_velocity(0, 1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    std::vector<idealgas::Particle*> initial_particles({&particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();

    REQUIRE(container.GetParticles().at(0)->GetPosition().x == 90);
  }

  SECTION("Particles don't collide if not going in same direction") {
    const glm::vec2 top_particle_position(20, 20);
    const glm::vec2 top_particle_velocity(1, -1);
    idealgas::Particle top_particle(top_particle_position,
                                    top_particle_velocity, color, radius, mass);

    const glm::vec2 bottom_particle_position(20, 30);
    const glm::vec2 bottom_particle_velocity(-1, 1);
    idealgas::Particle bottom_particle(bottom_particle_position,
                                       bottom_particle_velocity, color, radius,
                                       mass);

    std::vector<idealgas::Particle*> initial_particles(
        {&top_particle, &bottom_particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();

    const glm::vec2 expected_top_position(21, 19);
    const glm::vec2 expected_bottom_position(19, 31);
    REQUIRE(container.GetParticles().at(0)->GetPosition() ==
            expected_top_position);
    REQUIRE(container.GetParticles().at(0)->GetVelocity() ==
            top_particle_velocity);
    REQUIRE(container.GetParticles().at(1)->GetPosition() ==
            expected_bottom_position);
    REQUIRE(container.GetParticles().at(1)->GetVelocity() ==
            bottom_particle_velocity);
  }

  SECTION("Particles don't collide with each other if not moving") {
    const glm::vec2 top_particle_position(30, 30);
    const glm::vec2 top_particle_velocity(0, 0);
    idealgas::Particle top_particle(top_particle_position,
                                    top_particle_velocity, color, radius, mass);

    const glm::vec2 bottom_particle_position(30, 40);
    const glm::vec2 bottom_particle_velocity(0, 0);
    idealgas::Particle bottom_particle(bottom_particle_position,
                                       bottom_particle_velocity, color, radius,
                                       mass);

    std::vector<idealgas::Particle*> initial_particles(
        {&top_particle, &bottom_particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();

    REQUIRE(container.GetParticles().at(0)->GetPosition() ==
            top_particle_position);
    REQUIRE(container.GetParticles().at(1)->GetPosition() ==
            bottom_particle_position);
  }

  SECTION("Particles don't collide when not by each other") {
    const glm::vec2 top_particle_position(30, 30);
    const glm::vec2 top_particle_velocity(1, 1);
    idealgas::Particle top_particle(top_particle_position,
                                    top_particle_velocity, color, radius, mass);

    const glm::vec2 bottom_particle_position(60, 60);
    const glm::vec2 bottom_particle_velocity(1, 1);
    idealgas::Particle bottom_particle(bottom_particle_position,
                                       bottom_particle_velocity, color, radius,
                                       mass);

    std::vector<idealgas::Particle*> initial_particles(
        {&top_particle, &bottom_particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    container.AdvanceOneFrame();

    const glm::vec2 expected_top_position(31, 31);
    const glm::vec2 expected_bottom_position(61, 61);
    REQUIRE(container.GetParticles().at(0)->GetPosition() ==
            expected_top_position);
    REQUIRE(container.GetParticles().at(1)->GetPosition() ==
            expected_bottom_position);
  }
}

TEST_CASE("Particles change speed on global modification") {
  const glm::vec2 top_left_corner(0, 0);
  const glm::vec2 bottom_right_corner(100, 100);
  float radius = 10.0f;
  float mass = 1.0f;
  const ci::Color color("orange");

  SECTION("Particle velocity decreases in magnitude on slow down") {
    const glm::vec2 top_particle_position(20, -20);
    const glm::vec2 top_particle_velocity(2, -2);
    idealgas::Particle top_particle(top_particle_position,
                                    top_particle_velocity, color, radius, mass);

    const glm::vec2 bottom_particle_position(30, 30);
    const glm::vec2 bottom_particle_velocity(3, -3);
    idealgas::Particle bottom_particle(bottom_particle_position,
                                       bottom_particle_velocity, color, radius,
                                       mass);

    std::vector<idealgas::Particle*> initial_particles(
        {&top_particle, &bottom_particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    glm::vec2 delta_velocity(1, 1);
    container.ModifyParticlesSpeed(delta_velocity, false);

    const glm::vec2 expected_top_velocity(1, -1);
    const glm::vec2 expected_bottom_velocity(2, -2);
    REQUIRE(container.GetParticles().at(0)->GetVelocity() ==
            expected_top_velocity);
    REQUIRE(container.GetParticles().at(1)->GetVelocity() ==
            expected_bottom_velocity);
  }

  SECTION("Particle velocity increases in magnitude on speed up") {
    const glm::vec2 top_particle_position(20, -20);
    const glm::vec2 top_particle_velocity(2, -2);
    idealgas::Particle top_particle(top_particle_position,
                                    top_particle_velocity, color, radius, mass);

    const glm::vec2 bottom_particle_position(30, 30);
    const glm::vec2 bottom_particle_velocity(3, -3);
    idealgas::Particle bottom_particle(bottom_particle_position,
                                       bottom_particle_velocity, color, radius,
                                       mass);

    std::vector<idealgas::Particle*> initial_particles(
        {&top_particle, &bottom_particle});

    idealgas::GasContainer container(initial_particles, 0, top_left_corner,
                                     bottom_right_corner, radius, mass, color);

    glm::vec2 delta_velocity(1, 1);
    container.ModifyParticlesSpeed(delta_velocity, true);

    const glm::vec2 expected_top_velocity(3, -3);
    const glm::vec2 expected_bottom_velocity(4, -4);
    REQUIRE(container.GetParticles().at(0)->GetVelocity() ==
            expected_top_velocity);
    REQUIRE(container.GetParticles().at(1)->GetVelocity() ==
            expected_bottom_velocity);
  }
}
