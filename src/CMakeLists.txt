set(SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/include/Renderer.hpp
        ../include/Engine.hpp
        ../include/Exception.hpp
        ../include/KeyCode.hpp
)

if (USE_SDL2)
    message(STATUS "Building with SDL2 backend")
    list(APPEND SOURCE_FILES
            ${CMAKE_SOURCE_DIR}/backends/sdl2/Details.hpp
            ${CMAKE_SOURCE_DIR}/backends/sdl2/SDLRenderer.cpp
            ${CMAKE_SOURCE_DIR}/backends/sdl2/SDLRenderer.hpp
            ${CMAKE_SOURCE_DIR}/backends/sdl2/Engine.cpp
            ${CMAKE_SOURCE_DIR}/backends/sdl2/SDLDetails.cpp
    )
elseif (USE_SFML)
    message(STATUS "Building with SFML backend")
    list(APPEND SOURCE_FILES
            ${CMAKE_SOURCE_DIR}/backends/sfml/SFMLKeyCode.hpp
            ${CMAKE_SOURCE_DIR}/backends/sfml/SFMLKeyCode.cpp
            ${CMAKE_SOURCE_DIR}/backends/sfml/Details.hpp
            ${CMAKE_SOURCE_DIR}/backends/sfml/SFMLDetails.cpp
            ${CMAKE_SOURCE_DIR}/backends/sfml/SFMLRenderer.cpp
            ${CMAKE_SOURCE_DIR}/backends/sfml/SFMLRenderer.hpp
            ${CMAKE_SOURCE_DIR}/backends/sfml/Engine.cpp
    )
endif ()


add_library(sts_engine STATIC ${SOURCE_FILES})

#link necessary libs
if (USE_SDL2)
    message(STATUS "Linking SDL2 libs")
    target_link_libraries(sts_engine PRIVATE SDL2::SDL2 spdlog::spdlog)
elseif (USE_SFML)
    message(STATUS "Linking SFML libs")
    target_link_libraries(sts_engine PRIVATE sfml-graphics sfml-audio sfml-window spdlog::spdlog)
endif ()
target_include_directories(sts_engine PRIVATE ${CMAKE_SOURCE_DIR}/include)
set_target_properties(sts_engine PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)