add_executable(TestCatch TestCatch.cpp)
target_link_libraries(TestCatch Catch2::Catch2WithMain)
add_test(NAME TestCatchTest COMMAND TestCatch)