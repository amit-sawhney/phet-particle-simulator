#include "display/gas_simulation_app.h"

#include <components/histogram.h>

namespace idealgas {

IdealGasApp::IdealGasApp() {
  std::vector<Particle*> initial_particles;
  initial_particles.push_back(&orange_particle_);
  initial_particles.push_back(&white_particle_);
  initial_particles.push_back(&blue_particle_);

  glm::vec2 top_left_corner(100, 100);
  glm::vec2 bottom_right_corner(600, 600);

  GasContainer container(initial_particles, 0, top_left_corner,
                         bottom_right_corner, kDefaultParticleRadius,
                         kDefaultParticleMass, kDefaultParticleColor);

  blue_histogram_ =
      Histogram(initial_particles, glm::vec2(650, 100), glm::vec2(850, 300), 1,
                blue_particle_.GetColor());
  orange_histogram_ =
      Histogram(initial_particles, glm::vec2(650, 400), glm::vec2(850, 600), 1,
                orange_particle_.GetColor());
  white_histogram_ =
      Histogram(initial_particles, glm::vec2(900, 100), glm::vec2(1100, 300), 1,
                white_particle_.GetColor());

  container_ = container;
  ci::app::setWindowSize(kWindowWidth, kWindowHeight);
}

void IdealGasApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);

  blue_histogram_.Draw();
  orange_histogram_.Draw();
  white_histogram_.Draw();

  container_.Display();
}

void IdealGasApp::update() {
  std::vector<Particle*> blue_particles =
      container_.GetParticlesByColor(blue_particle_.GetColor());

  std::vector<Particle*> orange_particles =
      container_.GetParticlesByColor(orange_particle_.GetColor());

  std::vector<Particle*> white_particles =
      container_.GetParticlesByColor(white_particle_.GetColor());

  blue_histogram_.UpdateParticleBins(blue_particles);
  orange_histogram_.UpdateParticleBins(orange_particles);
  white_histogram_.UpdateParticleBins(white_particles);

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
    case ci::app::KeyEvent::KEY_b:
      container_.AddParticleToContainer(&blue_particle_);
      break;
    case ci::app::KeyEvent::KEY_o:
      container_.AddParticleToContainer(&orange_particle_);
      break;
    case ci::app::KeyEvent::KEY_w:
      container_.AddParticleToContainer(&white_particle_);
      break;
  }
}

}  // namespace idealgas
