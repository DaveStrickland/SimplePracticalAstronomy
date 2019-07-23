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
 * @file JulianDate_TestClass.h
 * @brief Declaration of the JulianDate_TestClass
 *
 * @ingroup group_test
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Aug 29, 2018 dks : Initial coding
 */

#ifndef TEST_JULIANDATE_TESTCLASS_H_
#define TEST_JULIANDATE_TESTCLASS_H_

#include <cute/cute.h>

namespace SPA
{
namespace TEST
{

/**
 * @brief Tests of the JulianDate class
 *
 * @ingroup group_test
 *
 */
class JulianDate_TestClass
{
    public:
        /// Constructor
        JulianDate_TestClass();

        /// Destructor
        virtual ~JulianDate_TestClass();

        /**
         * Tests that int() truncates towards zero and also that
         * floor() rounds down.
         */
        void testIntTruncates();

        /**
         * Tests JulianDate constructors.
         *
         * The primary numerical test is the example given in Section 4 of PAWYC,
         * e.g. 1985-02-17 06:00:00 UTC gives JulianDate 2446113.75
         */
        void testConstructors();

        /**
         * Test the JulianDate TimeDifference operators.
         */
        void testOperators();

        /**
         * Tests JulianDate::getModifiedJulianDate().
         */
        void testGetModifiedJulianDate();

        /**
         * Tests JulianDate::getDateAndTime().
         */
        void testGetDateAndTime();

        /**
          * Adds all methods that run this class's unit tests to the given cute suite.
          *
          * @param[in,out] aSuite The cute suite that the tests will be added to.
          */
         static void makeTestSuite(cute::suite& aSuite)
         {
            aSuite += CUTE_SMEMFUN(JulianDate_TestClass, testIntTruncates);
            aSuite += CUTE_SMEMFUN(JulianDate_TestClass, testConstructors);
            aSuite += CUTE_SMEMFUN(JulianDate_TestClass, testOperators);
            aSuite += CUTE_SMEMFUN(JulianDate_TestClass, testGetModifiedJulianDate);
            aSuite += CUTE_SMEMFUN(JulianDate_TestClass, testGetDateAndTime);
         }
    private:
         /**
          * The test tolerance for decimal days in JulianDate tests is
          * about 1.0e-9 days.
          */
         double theTolerance;

         /**
          * Number of digits to print numbers to.
          */
         int theDigitsOfPrecision;

};

} // end namespace TEST
} // end namespace SPA

#endif /* TEST_JULIANDATE_TESTCLASS_H_ */
