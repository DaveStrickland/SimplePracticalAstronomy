# CMake configuration for SimplePracticalAstronomy
#
# 2021-11-16 dks : Updated CMakeLists.txt for CMake 3.5
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(spa LANGUAGES CXX)

# Optimized with debug features. Could also do
#  cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo <path and other arguments>
#  cmake -DCMAKE_BUILD_TYPE=Debug <path and other arguments>
#  cmake -DCMAKE_BUILD_TYPE=Release <path and other arguments>

# we default to Release build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Compile options.
# Print any specified in the user's shell
message(STATUS "Using CMAKE_CXX_COMPILER = ${CMAKE_CXX_COMPILER} version ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Environment specified C++ compiler flags: ${CMAKE_CXX_FLAGS}")

list(APPEND flags "-Wall")
if(NOT WIN32)
  list(APPEND flags "-Wextra" "-Wpedantic")
endif()

# Profiling
if(MY_PROFILING)
    list(APPEND flags -fprofile-arcs -ftest-coverage)
endif()

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_RULE_MESSAGES OFF)


# Stops .cc.gcno
###set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

# Library module
set(SOURCES src/SpaDate.cc
    src/SpaTime.cc
    src/DateAndTime.cc
    src/TimeUtilities.cc
    src/JulianDate.cc
    src/TimeDifference.cc)
    
# unit test sources
set(TEST_SOURCES test/spa_unit_test.cc
    test/SpaTestUtilities.cc
    test/DateAndTime_TestClass.cc
    test/SpaDate_TestClass.cc
    test/SpaTime_TestClass.cc
    test/TimeUtilities_TestClass.cc
    test/JulianDate_TestClass.cc
    test/TimeDifference_TestClass.cc
    test/PolynomialTiming_TestClass.cc
    test/GetTimeTest.cc
    test/PAWYC_Examples_TestClass.cc)
    
add_library(spa SHARED ${SOURCES})
set_target_properties(spa
  PROPERTIES
    CXX_STANDARD 14
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE 1
  )

target_include_directories(spa PUBLIC inc)
target_include_directories(spa PRIVATE src)
target_compile_options(spa
  PRIVATE
    ${flags}
  )

# really only needed for debug coverage
if(MY_PROFILING)
    target_link_libraries(spa "--coverage")
    target_link_libraries(spa_unit_test spa "--coverage")
endif()

install(TARGETS spa DESTINATION lib)


add_executable(spa_unit_test ${TEST_SOURCES})
set_target_properties(spa_unit_test
  PROPERTIES
    CXX_STANDARD 14
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
  )
  
target_include_directories(spa_unit_test PUBLIC inc)
target_include_directories(spa_unit_test PRIVATE test)
target_compile_options(spa_unit_test
  PRIVATE
    ${flags}
  )
  
# really only needed for debug coverage

target_link_libraries(spa_unit_test spa)

# For interest sake, print includes
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "Configured include dir='${dir}'")
endforeach()

#set(CMAKE_INSTALL_RPATH "${ORIGIN}")
#set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
