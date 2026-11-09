cmake_minimum_required(VERSION 3.20)
project(MiniGitPractice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

# One small program per exercise. Each one is also a CTest test.
foreach(exercise ex5_index_file ex6_write_tests ex7_class ex8_exceptions)
    add_executable(${exercise} ${exercise}.cpp)
    add_test(NAME ${exercise} COMMAND ${exercise})
endforeach()
