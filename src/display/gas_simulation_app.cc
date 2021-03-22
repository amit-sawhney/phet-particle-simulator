#include "display/gas_simulation_app.h"

#include <components/histogram.h>

namespace idealgas {

IdealGasApp::IdealGasApp()
    : kBlueParticle(glm::vec2(550, 550), glm::vec2(-3, -1), ci::Color("blue"),
                    3, 5),
      kWhiteParticle(glm::vec2(550, 550), glm::vec2(-2, -2), ci::Color("white"),
                     6, 8),
      kOrangeParticle(glm::vec2(550, 550), glm::vec2(-1, -1.5),
                      ci::Color("orange"), 9, 11) {
  std::vector<Particle> initial_particles;
  initial_particles.push_back(kOrangeParticle);
  initial_particles.push_back(kWhiteParticle);
  initial_particles.push_back(kBlueParticle);

  glm::vec2 top_left_corner(100, 100);
  glm::vec2 bottom_right_corner(600, 600);

  float default_particle_radius = 3.0;
  float default_particle_mass = 1.0;

  ci::Color particle_color("orange");

  GasContainer container(initial_particles, 0, top_left_corner,
                         bottom_right_corner, default_particle_radius,
                         default_particle_mass, particle_color);

  blue_histogram_ = Histogram(initial_particles, glm::vec2(650, 100),
                              glm::vec2(850, 300), 1, kBlueParticle.GetColor());
  orange_histogram_ =
      Histogram(initial_particles, glm::vec2(650, 400), glm::vec2(850, 600), 1,
                kOrangeParticle.GetColor());
  white_histogram_ =
      Histogram(initial_particles, glm::vec2(900, 100), glm::vec2(1100, 300), 1,
                kWhiteParticle.GetColor());

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
  std::vector<Particle> blue_particles =
      container_.GetParticlesByColor(kBlueParticle.GetColor());

  std::vector<Particle> orange_particles =
      container_.GetParticlesByColor(kOrangeParticle.GetColor());

  std::vector<Particle> white_particles =
      container_.GetParticlesByColor(kWhiteParticle.GetColor());

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
      container_.AddParticleToContainer(kBlueParticle);
      break;
    case ci::app::KeyEvent::KEY_o:
      container_.AddParticleToContainer(kOrangeParticle);
      break;
    case ci::app::KeyEvent::KEY_w:
      container_.AddParticleToContainer(kWhiteParticle);
      break;
  }
}

}  // namespace idealgas
