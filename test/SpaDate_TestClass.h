/*
 * Copyright (C) 2020 David Strickland, <dave.strickland@gmail.com>
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
 * @file SpaDate_TestClass.h
 * @brief Declaration of SpaDate_TestClass
 *
 * @ingroup group_test
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Feb 01, 2020 dks : Initial coding 
 */

#ifndef TEST_SPADATE_TESTCLASS_H_
#define TEST_SPADATE_TESTCLASS_H_

#include <string>
#include <cute/cute.h>

namespace SPA
{

// Forward declaration
class SpaDate;

namespace TEST
{

/**
 * @brief CUTE test class of SpaDate class
 *
 * @ingroup group_test
 *
 */
class SpaDate_TestClass
{
    public:
        /// Default constructor
        SpaDate_TestClass() = default;

        /// Default destructor
        virtual ~SpaDate_TestClass() = default;

        /**
         * Tests constructors.
         */
        void testConstructors();

        /**
         * Tests  comparison operators
         */
        void testComparisonOperators();

        /**
         * Adds all methods that run this class's unit tests to the given cute suite.
         *
         * @param[in,out] aSuite The cute suite that the tests will be added to.
         */
        static void makeTestSuite(cute::suite& aSuite)
        {
            aSuite += CUTE_SMEMFUN(SpaDate_TestClass, testConstructors);
            aSuite += CUTE_SMEMFUN(SpaDate_TestClass, testComparisonOperators);
        }
    private:
        /**
         * @brief Compares the contents of a SpaDate object with a set
         *  of expected values, and fill a string with diagnostic information
         *  only if they differ,
         *
         * @limitations This technically has two outputs, a bool and a string
         *  containing the error message only if the bool is  false. If we used
         *  C++17 we could use std::optional (and make the bool true if an error
         *  occurs).
         *
         * @param[in] aSpaDate Input SpaDate object to be analyzed.
         * @param[in] anExpectedYear Expected year value.
         * @param[in] anExpectedMonth Expected month value.
         * @param[in] anExpectedDay Expected day value.
         * @param[out] anErrorMessage String listing the differences only
         *   if the SpaDate object does not match the expected values.
         *   If no problems are found this string is cleared of any existing
         *   contents,
         * @return True if the input SpaDate matches the expected values.
         */
        bool checkSpaDateValues(const SPA::SpaDate& aSpaDate,
                                int anExpectedYear,
                                int anExpectedMonth,
                                int anExpectedDay,
                                std::string& anErrorMessage);
};

} /* namespace TEST */
} /* namespace SPA */

#endif /* TEST_SPADATE_TESTCLASS_H_ */
