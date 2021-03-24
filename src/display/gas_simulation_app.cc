#include "display/gas_simulation_app.h"

#include <components/histogram.h>

namespace idealgas {

IdealGasApp::IdealGasApp() {
  std::vector<Particle*> initial_particles;
  initial_particles.push_back(&orange_particle_);
  initial_particles.push_back(&white_particle_);
  initial_particles.push_back(&blue_particle_);

  GasContainer container(initial_particles, 0, kTopLeftCorner,
                         kBottomRightCorner, kDefaultParticleRadius,
                         kDefaultParticleMass, kDefaultParticleColor);

  blue_histogram_ =
      Histogram(initial_particles, glm::vec2(650, 100), glm::vec2(850, 300), 1,
                blue_particle_.GetColor(), 4);
  orange_histogram_ =
      Histogram(initial_particles, glm::vec2(650, 400), glm::vec2(850, 600), 1,
                orange_particle_.GetColor(), 4);
  white_histogram_ =
      Histogram(initial_particles, glm::vec2(900, 100), glm::vec2(1100, 300), 1,
                white_particle_.GetColor(), 4);

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
  Particle* blue_particle = new Particle(glm::vec2(550, 550), glm::vec2(-3, -1),
                                         ci::Color("blue"), 3, 5);
  Particle* orange_particle = new Particle(
      glm::vec2(550, 550), glm::vec2(-2, -2), ci::Color("orange"), 6, 8);
  Particle* white_particle = new Particle(
      glm::vec2(550, 550), glm::vec2(-1, -1.5), ci::Color("white"), 9, 11);

  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_UP:
      container_.ModifyParticlesSpeed(kDeltaVelocity, true);
      break;
    case ci::app::KeyEvent::KEY_DOWN:
      container_.ModifyParticlesSpeed(kDeltaVelocity, false);
      break;
    case ci::app::KeyEvent::KEY_b:
      container_.AddParticleToContainer(blue_particle);
      break;
    case ci::app::KeyEvent::KEY_o:
      container_.AddParticleToContainer(orange_particle);
      break;
    case ci::app::KeyEvent::KEY_w:
      container_.AddParticleToContainer(white_particle);
      break;
  }
}

}  // namespace idealgas
