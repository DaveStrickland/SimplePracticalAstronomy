cmake_minimum_required(VERSION 3.0)
project(spa)

# Optimized with debug features. Could also do
#  cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo <path and other arguments>
#  cmake -DCMAKE_BUILD_TYPE=Debug <path and other arguments>
#  cmake -DCMAKE_BUILD_TYPE=Release <path and other arguments>
set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_RULE_MESSAGES OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

# Stops .cc.gcno
###set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

# Global compile options
#  Old method: set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
add_compile_options(-Wall)

# Library module
set(SOURCES src/DateAndTime.cc
    src/TimeUtilities.cc
    src/JulianDate.cc
    src/TimeDifference.cc)
###set(MY_DEBUG_OPTIONS -O0 -fprofile-arcs
##    -ftest-coverage)
add_library(spa SHARED ${SOURCES})
target_compile_features(spa PUBLIC cxx_std_11)
target_compile_options(spa PUBLIC "$<$<CONFIG:DEBUG>:${MY_DEBUG_OPTIONS}>")
target_include_directories(spa PUBLIC inc)
target_include_directories(spa PRIVATE src)

# really only needed for debug coverage
###target_link_libraries(spa "--coverage")

install(TARGETS spa DESTINATION lib)

# unit test
set(TEST_SOURCES test/spa_unit_test.cc
    test/SpaTestUtilities.cc
    test/DateAndTime_TestClass.cc
    test/TimeUtilities_TestClass.cc
    test/JulianDate_TestClass.cc
    test/TimeDifference_TestClass.cc
    test/PolynomialTiming_TestClass.cc
    test/GetTimeTest.cc
    test/PAWYC_Examples_TestClass.cc)
add_executable(spa_unit_test ${TEST_SOURCES})
target_compile_features(spa_unit_test PUBLIC cxx_std_11)
target_include_directories(spa_unit_test PUBLIC inc)
target_include_directories(spa_unit_test PRIVATE test)

# really only needed for debug coverage
###target_link_libraries(spa_unit_test spa "--coverage")
target_link_libraries(spa_unit_test spa)

# For interest sake, print includes
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "Configured include dir='${dir}'")
endforeach()

#set(CMAKE_INSTALL_RPATH "${ORIGIN}")
#set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
