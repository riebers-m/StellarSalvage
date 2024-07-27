//
// Created by max on 13.07.24.
//

#include "Engine.hpp"
#include "Details.hpp"

namespace sts {
Engine const &Engine::instance() {
  static auto engine = Engine{};
  return engine;
}
Engine::Engine() : m_details(std::make_unique<Details>()) {
  // SDL Setup code here
}
Engine::~Engine() {
  // SDL Cleanup code here
}
std::shared_ptr<Renderer> Engine::create_renderer(size_t x, size_t y,
                                                  std::string const &title,
                                                  Engine const &engine) {}
} // namespace sts