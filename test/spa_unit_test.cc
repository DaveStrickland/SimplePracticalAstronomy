/*
 * Copyright (C) 2018 David Strickland, <dave.strickland@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file spa_unit_test.cc
 * @brief Main unit test driver for SPA.
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Aug 27, 2018 dks : Initial coding
 */

/**
 * @defgroup group_test Test Code
 * @brief Test code and utilities
 */

#include <iostream>
#include <cute/cute.h>
#include <cute/cute_counting_listener.h>
#include <cute/ide_listener.h>
#include <cute/cute_runner.h>

#include "TimeUtilities_TestClass.h"
#include "DateAndTime_TestClass.h"
#include "JulianDate_TestClass.h"
#include "TimeDifference_TestClass.h"
#include "PolynomialTiming_TestClass.h"
#include "GetTimeTest.h"
#include "PAWYC_Examples_TestClass.h"

/**
 * @brief Main test driver
 *
 * @param[in] argc Number of arguments
 * @param[in] argv Array of arguments
 * @return Integer status code
 */
int main(int argc, char *argv[])
{
    std::string unitTestSuiteName("SPA Unit Test Suite");
    cute::suite unitTestSuite;

    std::string exampleSuiteName("PAWYC Examples Suite");
    cute::suite exampleSuite;

    // General prototypes or benchmarking
    SPA::TEST::PolynomialTiming_TestClass::makeTestSuite(unitTestSuite);
    SPA::TEST::MakeTimeTestSuite(unitTestSuite);

    // White box units tests of SPA itself
    SPA::TEST::TimeUtilities_TestClass::makeTestSuite(unitTestSuite);
    SPA::TEST::DateAndTime_TestClass::makeTestSuite(unitTestSuite);
    SPA::TEST::JulianDate_TestClass::makeTestSuite(unitTestSuite);
    SPA::TEST::TimeDifference_TestClass::makeTestSuite(unitTestSuite);
    
    // Examples of PAWYC sections using SPA
    SPA::TEST::PAWYC_Examples_TestClass::makeTestSuite(exampleSuite);

    cute::counting_listener<cute::ide_listener<>> listener;
    auto runner = cute::makeRunner(listener);
    bool pass = runner(unitTestSuite, unitTestSuiteName.c_str());
    pass = runner(exampleSuite, exampleSuiteName.c_str()) && pass; // keep previous pass result

    std::cout << "#summary:"
              << " numberOfSuites=" << listener.numberOfSuites
              << " numberOfTestsInSuites=" << listener.numberOfTestsInSuites
              << " numberOfTests=" << listener.numberOfTests
              << " successfulTests=" << listener.successfulTests
              << " errors=" << listener.errors
              << " failedTests=" << listener.failedTests;
    if (pass)
    {
        std::cout << " PASS";
    }
    else
    {
        std::cout << " FAIL";
    }
    std::cout << std::endl;
    return !pass;
}

