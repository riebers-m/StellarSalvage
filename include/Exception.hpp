//
// Created by max on 13.07.24.
//

#ifndef STELLAR_SALVAGE_EXCEPTION_HPP
#define STELLAR_SALVAGE_EXCEPTION_HPP
#include <filesystem>
#include <format>
#include <stdexcept>
#include <string_view>

namespace sts {

class EngineError : protected std::exception {
public:
  explicit EngineError(std::string_view const message,
                       std::filesystem::path const &file, auto line)
      : m_message{std::format("{}:{}: {}", file.filename().string(), line,
                              message)} {}

  [[nodiscard]] const char *what() const noexcept override {
    return m_message.c_str();
  }

protected:
  std::string m_message;
};

#define EngineError(message)                                                   \
  EngineError { message, __FILE__, __LINE__ }

} // namespace sts
#endif // STELLAR_SALVAGE_EXCEPTION_HPP
