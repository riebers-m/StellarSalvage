cmake_minimum_required(VERSION 3.24)

project(Stellar-Salvage
        LANGUAGES CXX
        VERSION 0.1.0
)

# add dependencies
include(cmake/CPM.cmake)

option(BUILD_TESTS "Build all tests" ON)
# Option for selecting the backend
option(USE_SDL2 "Use SDL2 as the rendering backend" OFF)
option(USE_SFML "Use SFML as the rendering backend" ON)


if (UNIX)
    if(USE_SDL2)
        find_package(PkgConfig REQUIRED)
        find_package(SDL2 REQUIRED)
        # find_package does not find sdl2 ttf under ubuntu
    #    PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
    #    PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
    elseif (USE_SFML)
        find_package(SFML COMPONENTS graphics window system REQUIRED)
    else ()
        message(FATAL_ERROR "invalid backend")
    endif ()
else ()
    if(USE_SDL2)
        find_package(SDL2 REQUIRED)
        #find_package(SDL2_ttf REQUIRED)
        #find_package(SDL2_image REQUIRED)
    elseif (USE_SFML)
        find_package(SFML COMPONENTS graphics window system REQUIRED)
    else ()
        message(FATAL_ERROR "invalid backend")
    endif ()
endif ()


CPMAddPackage("gh:gabime/spdlog@1.14.1")


add_subdirectory(src)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog sts_engine)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

if (BUILD_TESTS)
    message(STATUS "Building tests")
    CPMAddPackage("gh:catchorg/Catch2@3.6.0")
    enable_testing()
    add_subdirectory(test)
endif ()