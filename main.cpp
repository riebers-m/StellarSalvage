//
// Created by max on 12.07.24.
//

#include <spdlog/spdlog.h>
#include <format>

int main(int argc, char* argv[]) {
    spdlog::info(std::format("{},{}", "Hello", "There"));

    return 0;
}