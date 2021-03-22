#include "physics/collision_physics.h"

#include <catch2/catch.hpp>

TEST_CASE("Check particle collision detector") {
  glm::vec2 top_left_corner(0, 0);
  glm::vec2 bottom_right_corner(100, 100);
  float radius = 10.0f;
  float mass = 1.0f;
  ci::Color color("orange");
  idealgas::CollisionPhysics physics(top_left_corner, bottom_right_corner);

  SECTION("Particles touching horizontally and collide") {
    glm::vec2 left_particle_position(20, 20);
    glm::vec2 left_particle_velocity(1, 0);
    idealgas::Particle left_particle(
        left_particle_position, left_particle_velocity, color, radius, mass);

    glm::vec2 right_particle_position(30, 20);
    glm::vec2 right_particle_velocity(-1, 0);
    idealgas::Particle right_particle(
        right_particle_position, right_particle_velocity, color, radius, mass);

    REQUIRE(physics.DidParticlesCollide(left_particle, right_particle));
  }

  SECTION("Particles touching horizontally and don't collide") {
    glm::vec2 left_particle_position(20, 20);
    glm::vec2 left_particle_velocity(-1, 0);
    idealgas::Particle left_particle(
        left_particle_position, left_particle_velocity, color, radius, mass);

    glm::vec2 right_particle_position(30, 20);
    glm::vec2 right_particle_velocity(1, 0);
    idealgas::Particle right_particle(
        right_particle_position, right_particle_velocity, color, radius, mass);

    REQUIRE(!physics.DidParticlesCollide(left_particle, right_particle));
  }

  SECTION("Particles touching vertically and collide") {
    glm::vec2 top_particle_position(20, 20);
    glm::vec2 top_particle_velocity(0, 1);
    idealgas::Particle top_particle(top_particle_position,
                                    top_particle_velocity, color, radius, mass);

    glm::vec2 bottom_particle_position(20, 30);
    glm::vec2 bottom_particle_velocity(0, -1);
    idealgas::Particle bottom_particle(bottom_particle_position,
                                       bottom_particle_velocity, color, radius,
                                       mass);

    REQUIRE(physics.DidParticlesCollide(top_particle, bottom_particle));
  }

  SECTION("Particles touching vertically and don't collide") {
    glm::vec2 top_particle_position(20, 20);
    glm::vec2 top_particle_velocity(0, -1);
    idealgas::Particle top_particle(top_particle_position,
                                    top_particle_velocity, color, radius, mass);

    glm::vec2 bottom_particle_position(20, 30);
    glm::vec2 bottom_particle_velocity(0, 1);
    idealgas::Particle bottom_particle(bottom_particle_position,
                                       bottom_particle_velocity, color, radius,
                                       mass);

    REQUIRE(!physics.DidParticlesCollide(top_particle, bottom_particle));
  }

  SECTION("Particles touching diagonally and collide") {
    glm::vec2 top_particle_position(20, 20);
    glm::vec2 top_particle_velocity(1, 1);
    idealgas::Particle top_particle(top_particle_position,
                                    top_particle_velocity, color, radius, mass);

    glm::vec2 bottom_particle_position(30, 30);
    glm::vec2 bottom_particle_velocity(-1, -1);
    idealgas::Particle bottom_particle(bottom_particle_position,
                                       bottom_particle_velocity, color, radius,
                                       mass);

    REQUIRE(physics.DidParticlesCollide(top_particle, bottom_particle));
  }

  SECTION("Particles touching diagonally and don't collide") {
    glm::vec2 top_particle_position(20, 20);
    glm::vec2 top_particle_velocity(-1, -1);
    idealgas::Particle top_particle(top_particle_position,
                                    top_particle_velocity, color, radius, mass);

    glm::vec2 bottom_particle_position(30, 30);
    glm::vec2 bottom_particle_velocity(1, 1);
    idealgas::Particle bottom_particle(bottom_particle_position,
                                       bottom_particle_velocity, color, radius,
                                       mass);

    REQUIRE(!physics.DidParticlesCollide(top_particle, bottom_particle));
  }

  SECTION("Particles are not touching") {
    glm::vec2 top_particle_position(10, 10);
    glm::vec2 top_particle_velocity(1, 1);
    idealgas::Particle top_particle(top_particle_position,
                                    top_particle_velocity, color, radius, mass);

    glm::vec2 bottom_particle_position(30, 30);
    glm::vec2 bottom_particle_velocity(-1, -1);
    idealgas::Particle bottom_particle(bottom_particle_position,
                                       bottom_particle_velocity, color, radius,
                                       mass);

    REQUIRE(!physics.DidParticlesCollide(top_particle, bottom_particle));
  }
}

TEST_CASE("Particle velocities update according to the laws of physics") {
  glm::vec2 top_left_corner(0, 0);
  glm::vec2 bottom_right_corner(100, 100);
  float radius = 10.0f;
  float mass = 1.0f;
  ci::Color color("orange");
  idealgas::CollisionPhysics physics(top_left_corner, bottom_right_corner);

  SECTION("Particles horizontally moving at each other with same speed") {
    glm::vec2 left_particle_position(20, 20);
    glm::vec2 left_particle_velocity(1, 0);
    idealgas::Particle left_particle(
        left_particle_position, left_particle_velocity, color, radius, mass);

    glm::vec2 right_particle_position(30, 20);
    glm::vec2 right_particle_velocity(-1, 0);
    idealgas::Particle right_particle(
        right_particle_position, right_particle_velocity, color, radius, mass);

    physics.UpdateCollidedParticleVelocities(&left_particle, &right_particle);

    glm::vec2 expected_left_particle_velocity(-1, 0);
    glm::vec2 expected_right_particle_velocity(1, 0);

    REQUIRE(left_particle.GetVelocity() == expected_left_particle_velocity);
    REQUIRE(right_particle.GetVelocity() == expected_right_particle_velocity);
  }

  SECTION("Particles horizontally moving at each other with different speeds") {
    glm::vec2 left_particle_position(20, 20);
    glm::vec2 left_particle_velocity(3, 0);
    idealgas::Particle left_particle(
        left_particle_position, left_particle_velocity, color, radius, mass);

    glm::vec2 right_particle_position(30, 20);
    glm::vec2 right_particle_velocity(-1, 0);
    idealgas::Particle right_particle(
        right_particle_position, right_particle_velocity, color, radius, mass);

    physics.UpdateCollidedParticleVelocities(&left_particle, &right_particle);

    glm::vec2 expected_left_particle_velocity(-1, 0);
    glm::vec2 expected_right_particle_velocity(3, 0);

    REQUIRE(left_particle.GetVelocity() == expected_left_particle_velocity);
    REQUIRE(right_particle.GetVelocity() == expected_right_particle_velocity);
  }

  SECTION("Particles vertically moving at each other with same speed") {
    glm::vec2 top_particle_position(20, 20);
    glm::vec2 top_particle_velocity(0, 1);
    idealgas::Particle top_particle(top_particle_position,
                                    top_particle_velocity, color, radius, mass);

    glm::vec2 bottom_particle_position(20, 30);
    glm::vec2 bottom_particle_velocity(0, -1);
    idealgas::Particle bottom_particle(bottom_particle_position,
                                       bottom_particle_velocity, color, radius,
                                       mass);

    physics.UpdateCollidedParticleVelocities(&top_particle, &bottom_particle);

    glm::vec2 expected_top_particle_velocity(0, -1);
    glm::vec2 expected_bottom_particle_velocity(0, 1);

    REQUIRE(top_particle.GetVelocity() == expected_top_particle_velocity);
    REQUIRE(bottom_particle.GetVelocity() == expected_bottom_particle_velocity);
  }

  SECTION("Particles vertically moving at each other with different speeds") {
    glm::vec2 top_particle_position(20, 20);
    glm::vec2 top_particle_velocity(0, 3);
    idealgas::Particle top_particle(top_particle_position,
                                    top_particle_velocity, color, radius, mass);

    glm::vec2 bottom_particle_position(20, 30);
    glm::vec2 bottom_particle_velocity(0, -1);
    idealgas::Particle bottom_particle(bottom_particle_position,
                                       bottom_particle_velocity, color, radius,
                                       mass);

    physics.UpdateCollidedParticleVelocities(&top_particle, &bottom_particle);

    glm::vec2 expected_top_particle_velocity(0, -1);
    glm::vec2 expected_bottom_particle_velocity(0, 3);

    REQUIRE(top_particle.GetVelocity() == expected_top_particle_velocity);
    REQUIRE(bottom_particle.GetVelocity() == expected_bottom_particle_velocity);
  }

  SECTION("Particles moving at each other at angle with same speed") {
    glm::vec2 top_particle_position(20, 20);
    glm::vec2 top_particle_velocity(1, 1);
    idealgas::Particle top_particle(top_particle_position,
                                    top_particle_velocity, color, radius, mass);

    glm::vec2 bottom_particle_position(30, 30);
    glm::vec2 bottom_particle_velocity(-1, -1);
    idealgas::Particle bottom_particle(bottom_particle_position,
                                       bottom_particle_velocity, color, radius,
                                       mass);

    physics.UpdateCollidedParticleVelocities(&top_particle, &bottom_particle);

    glm::vec2 expected_top_particle_velocity(-1, -1);
    glm::vec2 expected_bottom_particle_velocity(1, 1);

    REQUIRE(top_particle.GetVelocity() == expected_top_particle_velocity);
    REQUIRE(bottom_particle.GetVelocity() == expected_bottom_particle_velocity);
  }

  SECTION("Particles moving at each other at angle with different speeds") {
    glm::vec2 top_particle_position(20, 20);
    glm::vec2 top_particle_velocity(3, 2);
    idealgas::Particle top_particle(top_particle_position,
                                    top_particle_velocity, color, radius, mass);

    glm::vec2 bottom_particle_position(40, 20);
    glm::vec2 bottom_particle_velocity(-2, 5);
    idealgas::Particle bottom_particle(bottom_particle_position,
                                       bottom_particle_velocity, color, radius,
                                       mass);

    physics.UpdateCollidedParticleVelocities(&top_particle, &bottom_particle);

    glm::vec2 expected_top_particle_velocity(-2, 2);
    glm::vec2 expected_bottom_particle_velocity(3, 5);

    REQUIRE(top_particle.GetVelocity() == expected_top_particle_velocity);
    REQUIRE(bottom_particle.GetVelocity() == expected_bottom_particle_velocity);
  }

  SECTION("Particle horizontally moving at a resting particle") {
    glm::vec2 left_particle_position(20, 20);
    glm::vec2 left_particle_velocity(1, 0);
    idealgas::Particle left_particle(
        left_particle_position, left_particle_velocity, color, radius, mass);

    glm::vec2 right_particle_position(30, 20);
    glm::vec2 right_particle_velocity(0, 0);
    idealgas::Particle right_particle(
        right_particle_position, right_particle_velocity, color, radius, mass);

    physics.UpdateCollidedParticleVelocities(&left_particle, &right_particle);

    glm::vec2 expected_left_particle_velocity(0, 0);
    glm::vec2 expected_right_particle_velocity(1, 0);

    REQUIRE(left_particle.GetVelocity() == expected_left_particle_velocity);
    REQUIRE(right_particle.GetVelocity() == expected_right_particle_velocity);
  }

  SECTION("Particle vertically moving at a resting particle") {
    glm::vec2 top_particle_position(20, 20);
    glm::vec2 top_particle_velocity(0, 1);
    idealgas::Particle top_particle(top_particle_position,
                                    top_particle_velocity, color, radius, mass);

    glm::vec2 bottom_particle_position(20, 30);
    glm::vec2 bottom_particle_velocity(0, 0);
    idealgas::Particle bottom_particle(bottom_particle_position,
                                       bottom_particle_velocity, color, radius,
                                       mass);

    physics.UpdateCollidedParticleVelocities(&top_particle, &bottom_particle);

    glm::vec2 expected_top_particle_velocity(0, 0);
    glm::vec2 expected_bottom_particle_velocity(0, 1);

    REQUIRE(top_particle.GetVelocity() == expected_top_particle_velocity);
    REQUIRE(bottom_particle.GetVelocity() == expected_bottom_particle_velocity);
  }

  SECTION("Particle diagonally moving at a resting particle") {
    glm::vec2 top_particle_position(20, 20);
    glm::vec2 top_particle_velocity(1, 1);
    idealgas::Particle top_particle(top_particle_position,
                                    top_particle_velocity, color, radius, mass);

    glm::vec2 bottom_particle_position(30, 30);
    glm::vec2 bottom_particle_velocity(0, 0);
    idealgas::Particle bottom_particle(bottom_particle_position,
                                       bottom_particle_velocity, color, radius,
                                       mass);

    physics.UpdateCollidedParticleVelocities(&top_particle, &bottom_particle);

    glm::vec2 expected_top_particle_velocity(0, 0);
    glm::vec2 expected_bottom_particle_velocity(1, 1);

    REQUIRE(top_particle.GetVelocity() == expected_top_particle_velocity);
    REQUIRE(bottom_particle.GetVelocity() == expected_bottom_particle_velocity);
  }

  SECTION("Three particles collide at the same time") {
    glm::vec2 top_particle_position(20, 20);
    glm::vec2 top_particle_velocity(1, 1);
    idealgas::Particle top_particle(top_particle_position,
                                    top_particle_velocity, color, radius, mass);

    glm::vec2 middle_particle_position(20, 30);
    glm::vec2 middle_particle_velocity(1, 0);
    idealgas::Particle middle_particle(
        top_particle_position, top_particle_velocity, color, radius, mass);

    glm::vec2 bottom_particle_position(20, 40);
    glm::vec2 bottom_particle_velocity(-1, -1);
    idealgas::Particle bottom_particle(bottom_particle_position,
                                       bottom_particle_velocity, color, radius,
                                       mass);

    physics.UpdateCollidedParticleVelocities(&top_particle, &bottom_particle);

    glm::vec2 expected_top_particle_velocity(1, -1);
    glm::vec2 expected_middle_particle_velocity(1, 1);
    glm::vec2 expected_bottom_particle_velocity(-1, 1);

    REQUIRE(top_particle.GetVelocity() == expected_top_particle_velocity);
    REQUIRE(middle_particle.GetVelocity() == expected_middle_particle_velocity);
    REQUIRE(bottom_particle.GetVelocity() == expected_bottom_particle_velocity);
  }
}

TEST_CASE("Particle collides with the walls of the container") {
  glm::vec2 top_left_corner(0, 0);
  glm::vec2 bottom_right_corner(100, 100);
  float radius = 10.0f;
  float mass = 1.0f;
  ci::Color color("orange");
  idealgas::CollisionPhysics physics(top_left_corner, bottom_right_corner);

  SECTION("Particle is touching the top wall and collides") {
    glm::vec2 particle_position(10, 10);
    glm::vec2 particle_velocity(0, -1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    REQUIRE(physics.IsParticleCollidingWithTopWall(particle));
  }

  SECTION("Particle is touching the top wall and doesn't collide") {
    glm::vec2 particle_position(10, 10);
    glm::vec2 particle_velocity(1, 0);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    REQUIRE(!physics.IsParticleCollidingWithTopWall(particle));
  }

  SECTION("Particle is not touching the top wall and doesn't collide") {
    glm::vec2 particle_position(10, 20);
    glm::vec2 particle_velocity(0, -1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    REQUIRE(!physics.IsParticleCollidingWithTopWall(particle));
  }

  SECTION("Particle is touching the left wall and collides") {
    glm::vec2 particle_position(10, 10);
    glm::vec2 particle_velocity(-1, 0);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    REQUIRE(physics.IsParticleCollidingWithLeftWall(particle));
  }

  SECTION("Particle is touching the left wall and doesn't collide") {
    glm::vec2 particle_position(10, 10);
    glm::vec2 particle_velocity(0, 1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    REQUIRE(!physics.IsParticleCollidingWithLeftWall(particle));
  }

  SECTION("Particle is not touching the left wall and doesn't collide") {
    glm::vec2 particle_position(20, 10);
    glm::vec2 particle_velocity(-1, 0);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    REQUIRE(!physics.IsParticleCollidingWithLeftWall(particle));
  }

  SECTION("Particle is touching the right wall and collides") {
    glm::vec2 particle_position(90, 10);
    glm::vec2 particle_velocity(1, 0);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    REQUIRE(physics.IsParticleCollidingWithRightWall(particle));
  }

  SECTION("Particle is touching the right wall and doesn't collide") {
    glm::vec2 particle_position(90, 10);
    glm::vec2 particle_velocity(0, 1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    REQUIRE(!physics.IsParticleCollidingWithRightWall(particle));
  }

  SECTION("Particle is not touching the right wall and doesn't collide") {
    glm::vec2 particle_position(80, 10);
    glm::vec2 particle_velocity(1, 0);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    REQUIRE(!physics.IsParticleCollidingWithRightWall(particle));
  }

  SECTION("Particle is touching the top bottom and collides") {
    glm::vec2 particle_position(10, 90);
    glm::vec2 particle_velocity(0, 1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    REQUIRE(physics.IsParticleCollidingWithBottomWall(particle));
  }

  SECTION("Particle is touching the bottom wall and doesn't collide") {
    glm::vec2 particle_position(10, 90);
    glm::vec2 particle_velocity(1, 0);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    REQUIRE(!physics.IsParticleCollidingWithBottomWall(particle));
  }

  SECTION("Particle is not touching the bottom wall and doesn't collide") {
    glm::vec2 particle_position(10, 80);
    glm::vec2 particle_velocity(0, 1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    REQUIRE(!physics.IsParticleCollidingWithBottomWall(particle));
  }

  SECTION("Particle is touching top and left wall and collides") {
    glm::vec2 particle_position(10, 10);
    glm::vec2 particle_velocity(-1, -1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    REQUIRE(physics.IsParticleCollidingWithLeftWall(particle));
    REQUIRE(physics.IsParticleCollidingWithTopWall(particle));
  }

  SECTION("Particle is touching top and left wall and doesn't collide") {
    glm::vec2 particle_position(10, 10);
    glm::vec2 particle_velocity(1, 1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    REQUIRE(!physics.IsParticleCollidingWithLeftWall(particle));
    REQUIRE(!physics.IsParticleCollidingWithTopWall(particle));
  }

  SECTION("Particle is touching top and right wall and collides") {
    glm::vec2 particle_position(90, 10);
    glm::vec2 particle_velocity(1, -1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    REQUIRE(physics.IsParticleCollidingWithRightWall(particle));
    REQUIRE(physics.IsParticleCollidingWithTopWall(particle));
  }

  SECTION("Particle is touching top and right wall and doesn't collide") {
    glm::vec2 particle_position(90, 10);
    glm::vec2 particle_velocity(-1, 1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    REQUIRE(!physics.IsParticleCollidingWithRightWall(particle));
    REQUIRE(!physics.IsParticleCollidingWithTopWall(particle));
  }

  SECTION("Particle is touching bottom and left wall and collides") {
    glm::vec2 particle_position(10, 90);
    glm::vec2 particle_velocity(-1, 1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    REQUIRE(physics.IsParticleCollidingWithLeftWall(particle));
    REQUIRE(physics.IsParticleCollidingWithBottomWall(particle));
  }

  SECTION("Particle is touching bottom and left wall and doesn't collide") {
    glm::vec2 particle_position(10, 90);
    glm::vec2 particle_velocity(1, -1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    REQUIRE(!physics.IsParticleCollidingWithLeftWall(particle));
    REQUIRE(!physics.IsParticleCollidingWithBottomWall(particle));
  }

  SECTION("Particle is touching bottom and right wall and collides") {
    glm::vec2 particle_position(90, 90);
    glm::vec2 particle_velocity(1, 1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    REQUIRE(physics.IsParticleCollidingWithRightWall(particle));
    REQUIRE(physics.IsParticleCollidingWithBottomWall(particle));
  }

  SECTION("Particle is touching bottom and right wall and doesn't collide") {
    glm::vec2 particle_position(90, 90);
    glm::vec2 particle_velocity(-1, -1);
    idealgas::Particle particle(particle_position, particle_velocity, color,
                                radius, mass);

    REQUIRE(!physics.IsParticleCollidingWithRightWall(particle));
    REQUIRE(!physics.IsParticleCollidingWithTopWall(particle));
  }
}
