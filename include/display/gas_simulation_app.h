#pragma once

#include <components/histogram.h>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"

namespace idealgas {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class IdealGasApp : public ci::app::App {
 public:
  /**
   * Starts the Ideal Gas Application and determines the initial conditions for
   * the containers and particles
   */
  IdealGasApp();

  /**
   * Draws the current state of the Ideal Gas App
   */
  void draw() override;

  /**
   * Updates the Ideal Gas App after 1 unit of time
   */
  void update() override;

  /**
   * Listens for user input and passes on events to the container
   * @param event the keyboard event triggered by the user
   */
  void keyDown(ci::app::KeyEvent event) override;

 private:
  const size_t kWindowWidth = 1500;
  const size_t kWindowHeight = 800;
  const glm::vec2 kDeltaVelocity{.05, .05};
  const glm::vec2 kTopLeftCorner{100, 100};
  const glm::vec2 kBottomRightCorner{600, 600};
  const float kDefaultParticleRadius = 3.0;
  const float kDefaultParticleMass = 1.0;
  const ci::Color kDefaultParticleColor = ci::Color("orange");

  Particle* GenerateParticle(const glm::vec2& position,
                             const glm::vec2& velocity, const ci::Color& color,
                             float radius, float mass);

  GasContainer container_;
  Histogram blue_histogram_;
  Histogram orange_histogram_;
  Histogram white_histogram_;
  Particle blue_particle_ =
      Particle(glm::vec2(550, 550), glm::vec2(-3, -1), ci::Color("blue"), 3, 5);
  Particle orange_particle_ = Particle(glm::vec2(550, 550), glm::vec2(-2, -2),
                                       ci::Color("orange"), 6, 8);
  Particle white_particle_ = Particle(glm::vec2(550, 550), glm::vec2(-1, -1.5),
                                      ci::Color("white"), 9, 11);
};

}  // namespace idealgas