CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

PROJECT(
    interpreter
    VERSION 1.0
    DESCRIPTION "a simple interpreter for Python"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

set(src_directory "src")

# Probe all header files
# file(GLOB_RECURSE src_files "${src_directory}/*")
# Specify source files
set(src_files
  src/object.hpp
  src/object.cpp
  src/tokenize.hpp)

foreach(f ${src_files})
  message("Added source file ${f}")
endforeach()

# Set up main executable
add_executable(int standalone/main.cpp ${src_files})
target_include_directories(int PRIVATE ${src_directory})

# Enable compiler warnings
if(NOT TEST_INSTALLED_VERSION)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(int PUBLIC -Wall -Wpedantic -Wextra -Werror)
  elseif(MSVC)
    target_compile_options(int PUBLIC /W4 /WX)
    target_compile_definitions(int PUBLIC DOCTEST_CONFIG_USE_STD_HEADERS)
  endif()
endif()

# Set export compile command database on
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Fetch gtest
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)

# Set up tests
add_executable(test test/test.cpp ${src_files})
target_include_directories(test PRIVATE ${src_directory})
target_link_libraries(test gtest)
add_test(NAME test_all COMMAND test)