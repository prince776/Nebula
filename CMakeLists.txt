cmake_minimum_required(VERSION 3.2.0)
project(Nebula VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER "gcc-11")
set(CMAKE_CXX_COMPILER "g++-11")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB test_src CONFIGURE_DEPENDS src/tests/*.cpp)

add_executable(Nebula src/main.cpp)
add_executable(tester ${test_src})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_test(NebulaTester tester)
