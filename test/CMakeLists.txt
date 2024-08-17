add_executable(TestCatch TestCatch.cpp)
target_link_libraries(TestCatch Catch2::Catch2WithMain)
add_test(NAME TestCatchTest COMMAND TestCatch)

add_executable(TestVector2D
        core/TestVector2D.cpp
        ${CMAKE_SOURCE_DIR}/src/core/Vector2D.cpp
)
target_include_directories(TestVector2D PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestVector2D PRIVATE Catch2::Catch2WithMain)
add_test(NAME TestVector2DTest COMMAND TestVector2D)

add_executable(TestCollision
        core/TestCollision.cpp
        ${CMAKE_SOURCE_DIR}/src/core/Vector2D.cpp
        ${CMAKE_SOURCE_DIR}/src/core/Collision.cpp
)
target_include_directories(TestCollision PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TestCollision PRIVATE Catch2::Catch2WithMain)
add_test(NAME TestCollisionTest COMMAND TestCollision)