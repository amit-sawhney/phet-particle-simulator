#include "display/gas_simulation_app.h"

namespace idealgas {

IdealGasApp::IdealGasApp() {
  std::vector<Particle> initial_particles;
  glm::vec2 particle_location(200, 200);
  glm::vec2 particle_velocity(-1, 0);
  ci::Color particle1_color("red");
  float radius = 3.0;
  float mass = 10.0;
  Particle particle(particle_location, particle_velocity, particle1_color,
                    radius, mass);
  initial_particles.push_back(particle);

  glm::vec2 top_left_corner(100, 100);
  glm::vec2 bottom_right_corner(600, 600);

  float particle_radius = 3.0;
  float particle_mass = 1.0;

  ci::Color particle_color("orange");

  GasContainer container(initial_particles, 100, top_left_corner,
                         bottom_right_corner, particle_radius, particle_mass,
                         particle_color);
  container_ = container;
  ci::app::setWindowSize(kWindowWidth, kWindowHeight);
}

void IdealGasApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);

  container_.Display();
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_UP:
      container_.ModifyParticlesSpeed(kDeltaVelocity, true);
      break;
    case ci::app::KeyEvent::KEY_DOWN:
      container_.ModifyParticlesSpeed(kDeltaVelocity, false);
      break;
  }
}

}  // namespace idealgas
