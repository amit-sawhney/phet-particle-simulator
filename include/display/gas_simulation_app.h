#pragma once

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
  GasContainer container_;
  const size_t kWindowWidth = 1500;
  const size_t kWindowHeight = 800;
  const glm::vec2 kDeltaVelocity{.05, .05};
};

}  // namespace idealgas