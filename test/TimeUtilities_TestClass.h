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
 * @file TimeUtilities_TestClass.h
 * @brief Declaration of the CUTE test class for TimeUtilies
 * @ingroup group_test
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Sep 2, 2018 dks : Initial coding 
 */

#ifndef TEST_TIMEUTILITIES_TESTCLASS_H_
#define TEST_TIMEUTILITIES_TESTCLASS_H_

#include <cute/cute.h>

namespace SPA
{
namespace TEST
{

/**
 * @brief CUTE test class for TimeUtilities
 * @ingroup group_test
 */
class TimeUtilities_TestClass
{
    public:
        /// Default constructor
        TimeUtilities_TestClass() = default;

        /// Default destructor
        virtual ~TimeUtilities_TestClass()= default;

        /**
         * Tests handling of BC/BCE years
         */
        void testCalculateBCE_Year();

        /**
         * Tests the calculateDayInTheWeek() functions.
         */

        void testCalculateDayInTheWeek();
        /**
         * Tests day number calculation following Section 3 of PAWYC.
         */
        void testCalculateDayNumber();

        /**
         * Tests the conversion of hours, minutes and seconds
         * into decimal hours.
         */ 
        void testCalculateDecimalHours();

        /**
         * Tests calculating the date of Easter for several several different
         * input dates..
         */
        void testCalculateEaster();

        /**
         * Tests splitting a real number into an integer and fractional
         *  parts.
         */
        void testIntegerAndFraction();

        /**
         * Tests the conversion of decimal hours to hours, minutes
         * and seconds.
         */
        void testCalculateHoursMinutesAndSeconds();

        /**
         * Tests leap year calculation
         */
        void testIsLeapYear();

        /**
         * Tests the quotientAndRemainder function.
         */
        void testQuotientAndRemainder();

        /**
         * Tests ostream operators for time-related enumerations
         * produce the expected string output.
         */
        void testTimeEnumerationOstream();

        /**
         * @brief Utility function that returns true if two
         *   times, A and B, have matching hours, minutes and seconds.
         * 
         * The hours and minutes must match exactly, the seconds
         * must match within the input floating point tolerance.
         * 
         * @param[in] anHoursA Input hours from time A.
         * @param[in] aMinutesA Input minutes from time A.
         * @param[in] aSecondsA Input seconds from time A.
         * @param[in] anHoursB Input hours from time B.
         * @param[in] aMinutesB Input minutes from time B.
         * @param[in] aSecondsB Input seconds from time B.
         * @param[in] aSecondsTolerance Tolerance within which the
         *   seconds from A and B are considered to match.
         * @return True if times A and B match, false otherwise.
         */
        static bool hoursMinutesSecondsMatch(int anHoursA,
                                             int aMinutesA,
                                             double aSecondsA,
                                             int anHoursB,
                                             int aMinutesB,
                                             double aSecondsB,
                                             double aSecondsTolerance = 1.0e-9);

        /**
         * Adds all methods that run this class's unit tests to the given cute suite.
         *
         * @param[in,out] aSuite The cute suite that the tests will be added to.
         */
        static void makeTestSuite(cute::suite& aSuite)
        {
            aSuite += CUTE_SMEMFUN(TimeUtilities_TestClass, testIntegerAndFraction);
            aSuite += CUTE_SMEMFUN(TimeUtilities_TestClass, testQuotientAndRemainder);
            aSuite += CUTE_SMEMFUN(TimeUtilities_TestClass, testCalculateEaster);
            aSuite += CUTE_SMEMFUN(TimeUtilities_TestClass, testIsLeapYear);
            aSuite += CUTE_SMEMFUN(TimeUtilities_TestClass, testCalculateDayNumber);
            aSuite += CUTE_SMEMFUN(TimeUtilities_TestClass, testCalculateBCE_Year);
            aSuite += CUTE_SMEMFUN(TimeUtilities_TestClass, testCalculateDayInTheWeek);
            aSuite += CUTE_SMEMFUN(TimeUtilities_TestClass, testCalculateDecimalHours);
            aSuite += CUTE_SMEMFUN(TimeUtilities_TestClass, testCalculateHoursMinutesAndSeconds);
            aSuite += CUTE_SMEMFUN(TimeUtilities_TestClass, testTimeEnumerationOstream);
        }
    private:
};

} /* namespace TEST */
} /* namespace SPA */

#endif /* TEST_TIMEUTILITIES_TESTCLASS_H_ */
