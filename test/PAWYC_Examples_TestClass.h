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
 * @file PAWYC_Examples_TestClass.h
 * @brief Declares the PAWYC_Examples_TestClass used to demo each Section of PAWYC using SPA
 * @ingroup group_test
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Sep 2, 2018 dks : Initial coding 
 */

/**
 * @defgroup group_examples Examples
 * @brief Examples calculations from PAWYC implemented using SPA
 */

#ifndef TEST_PAWYC_EXAMPLES_TESTCLASS_H_
#define TEST_PAWYC_EXAMPLES_TESTCLASS_H_

#include <cute/cute.h>

namespace SPA
{
namespace TEST
{

/**
 * @brief CUTE test class used to demostrate each Section of PAWYC using SPA
 *
 * Each algorithm presented in PAWYC \cite pawyc_1988 has an example
 * associated with it, which the tests in this class demonstrate
 * as examples of how to use SPA. More rigorous tests of each algorithm
 * are provided in other Test Classes,
 *
 * @ingroup group_examples
 */
class PAWYC_Examples_TestClass
{

    public:
        /// Default constructor
        PAWYC_Examples_TestClass();

        /// Default destructor.
        virtual ~PAWYC_Examples_TestClass();

        /**
         * @brief Example of Section 2, calculating the month and day of Easter
         *   for a given year (in the Gregorian calendar)
         *
         * For the year 2000 C.E. Easter Sunday is 23rd April.
         */
        void example2_DateOfEaster();

        /**
         * @brief Example of Section 3, calculating the day number
         *
         * On 1985 February 17th the day number is 48, and the number
         * of days from 1990 January 0.0 is -1778.
         */
        void example3_DayNumber();

        /**
         * @brief Example of Section 4, calculating the Julian Date
         *
         * On 1985 February 17 at 06:00:00 UT the Julina Date
         * is 2446113.75,  and the number
         * of days from 1990 January 0.0 is -1778.
         */
        void example4_JulianDate();

        /**
         * @brief Example of Section 5, converting Julian day number
         *   to the calendar date.
         *
         * The Gregorian date corresponding to JD=2446113.75 is
         * 1985 February 17.25, i.e. 1985 02 17 06:00:00 UTC.
         *
         */
        void example5_JulianDateToCalendarDate();

        /**
         * @brief Example of Section 6, finding the day of the week.
         *
         * The day of the week corresponding to 1985 February 17 is
         * 0 (Sunday).
         */
        void example6_DayOfWeek();

        /**
         * Adds all methods that run this class's unit tests to the given cute suite.
         *
         * @param[in,out] aSuite The cute suite that the tests will be added to.
         */
        static void makeTestSuite(cute::suite& aSuite)
        {
            aSuite += CUTE_SMEMFUN(PAWYC_Examples_TestClass, example2_DateOfEaster);
            aSuite += CUTE_SMEMFUN(PAWYC_Examples_TestClass, example3_DayNumber);
            aSuite += CUTE_SMEMFUN(PAWYC_Examples_TestClass, example4_JulianDate);
            aSuite += CUTE_SMEMFUN(PAWYC_Examples_TestClass, example5_JulianDateToCalendarDate);
            aSuite += CUTE_SMEMFUN(PAWYC_Examples_TestClass, example6_DayOfWeek);
        }
    private:
};

} /* namespace TEST */
} /* namespace SPA */

#endif /* TEST_PAWYC_EXAMPLES_TESTCLASS_H_ */
