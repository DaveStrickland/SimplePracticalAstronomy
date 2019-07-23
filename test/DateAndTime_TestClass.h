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
 * @file DateAndTime_TestClass.h
 * @brief Declaration of DateAndTime_TestClass
 *
 * @ingroup group_test
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Sep 1, 2018 dks : Initial coding 
 */

#ifndef TEST_DATEANDTIME_TESTCLASS_H_
#define TEST_DATEANDTIME_TESTCLASS_H_

#include <string>
#include <cute/cute.h>

namespace SPA
{

// Forward declaration
class DateAndTime;

namespace TEST
{

/**
 * @brief CUTE test class of DateAndTime class
 *
 * @ingroup group_test
 *
 */
class DateAndTime_TestClass
{
    public:
        /// Default constructor
        DateAndTime_TestClass() = default;

        /// Default destructor
        virtual ~DateAndTime_TestClass() = default;

        /**
         * Tests constructors.
         */
        void testConstructors();

        /**
         * Tests  comparison operators
         */
        void testComparisonOperators();


        /**
         * Tests DateAndTime::getDayFraction()
         */
        void testGetDayFraction();

        /**
         * Adds all methods that run this class's unit tests to the given cute suite.
         *
         * @param[in,out] aSuite The cute suite that the tests will be added to.
         */
        static void makeTestSuite(cute::suite& aSuite)
        {
            aSuite += CUTE_SMEMFUN(DateAndTime_TestClass, testConstructors);
            aSuite += CUTE_SMEMFUN(DateAndTime_TestClass, testComparisonOperators);
            aSuite += CUTE_SMEMFUN(DateAndTime_TestClass, testGetDayFraction);
        }
    private:
        /**
         * @brief Compares the contents of a DateAndTime object with a set
         *  of expected values, and fill a string with diagnostic information
         *  only if they differ,
         *
         * @limitations This technically has two outputs, a bool and a string
         *  containing the error message only if the bool is  false. If we used
         *  C++17 we could use std::optional (and make the bool true if an error
         *  occurs).
         *
         *
         * @param[in] aDateAndTime Input DataAndTime object to be analyzed.
         * @param[in] anExpectedYear Expected year value.
         * @param[in] anExpectedMonth Expected month value.
         * @param[in] anExpectedDay Expected day value.
         * @param[in] anExpectedHours Expected hours value.
         * @param[in] anExpectedMinutes Expected minutes value.
         * @param[in] anExpectedSeconds Expected seconds value. See aFloatingPointTolerance.
         * @param[in] anExpectedUtcOffset Expected UTC Offset in hours value. See aFloatingPointTolerance.
         * @param[in] aFloatingPointTolerance Floating point values such as
         *   the DateAndTime seconds and UTC offset must match the
         *   expected values to within this tolerance to count as
         *   matching.
         * @param[out] anErrorMessage String listing the differences only
         *   if the DateAndTime object does not match the expected values.
         *   If no problems are found this string is cleared of any existing
         *   contents,
         * @return True if the input DateAndTime matches the expected values.
         */
        bool checkDateAndTimeValues(const SPA::DateAndTime& aDateAndTime,
                                   int anExpectedYear,
                                   int anExpectedMonth,
                                   int anExpectedDay,
                                   int anExpectedHours,
                                   int anExpectedMinutes,
                                   double anExpectedSeconds,
                                   double anExpectedUtcOffset,
                                   double aFloatingPointTolerance,
                                   std::string& anErrorMessage);
};

} /* namespace TEST */
} /* namespace SPA */

#endif /* TEST_DATEANDTIME_TESTCLASS_H_ */
