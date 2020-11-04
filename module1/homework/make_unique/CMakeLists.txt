cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

if (CMAKE_VERSION VERSION_LESS 3.10)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

project(make_unique)
add_executable(${PROJECT_NAME} main.cpp)
add_executable(${PROJECT_NAME}-ut test.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wconversion -pedantic -Wextra)
target_compile_options(${PROJECT_NAME}-ut PRIVATE -Wall -Werror -Wconversion -pedantic -Wextra)
target_link_libraries(${PROJECT_NAME}-ut PUBLIC gtest_main)

add_test(NAME ${PROJECT_NAME}-test COMMAND ${PROJECT_NAME}-ut)
enable_testing()