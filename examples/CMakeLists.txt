add_executable(blocks_example
    blocks_example.cpp
        ${CMAKE_SOURCE_DIR}/src/core/EntityComponentSystem.cpp
        ${CMAKE_SOURCE_DIR}/src/core/Vector2D.cpp
)
target_include_directories(blocks_example PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(blocks_example PRIVATE sts_engine spdlog::spdlog)
