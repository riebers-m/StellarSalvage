set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TestCatch TestCatch.cpp)
target_link_libraries(TestCatch Catch2::Catch2WithMain)
add_test(NAME TestCatchTest COMMAND TestCatch)

add_executable(testVector2D
        core/TestVector2D.cpp
        ${CMAKE_SOURCE_DIR}/src/core/Vector2D.cpp
)
target_include_directories(testVector2D PRIVATE ${CMAKE_SOURCE_DIR}/include/core)
target_link_libraries(testVector2D PRIVATE Catch2::Catch2WithMain)
add_test(NAME testVector2D COMMAND TestVector2D)