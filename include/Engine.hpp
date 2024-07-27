//
// Created by max on 13.07.24.
//

#ifndef STELLAR_SALVAGE_ENGINE_HPP
#define STELLAR_SALVAGE_ENGINE_HPP

#include "Renderer.hpp"
#include <memory>

namespace sts {
class Details;

class Engine {
public:
  Engine(Engine const &) = delete;
  Engine(Engine &&) = delete;
  Engine &operator=(Engine const &) = delete;
  Engine &operator=(Engine &&) = delete;
  ~Engine();

  std::shared_ptr<Renderer>
  create_renderer(size_t x, size_t y, std::string const &title = "Hello There",
                  Engine const &engine = instance());

private:
  Engine();

  static Engine const &instance();

  std::unique_ptr<Details> m_details;
};
} // namespace sts
#endif // STELLAR_SALVAGE_ENGINE_HPP
