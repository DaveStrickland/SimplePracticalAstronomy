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
 * @file GetTimeTest.h
 * @brief Declarations of test functions related to C-style and C++-style
 *   time string parsing.
 *
 * @ingroup group_test
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Aug 27, 2018 dks : Initial coding
 */

#ifndef TEST_GETTIMETEST_H_
#define TEST_GETTIMETEST_H_

#include <list>
#include <string>
#include <ctime>
#include <cute/cute.h>

namespace SPA
{
namespace TEST
{

/**
 * @brief Wraps GetTimeTest for use with CUTE
 * @ingroup group_test
 */
void GetTimeTestWrapper();

/**
 * @brief Wraps StrpTimeTest for use with CUTE
 * @ingroup group_test
 */
void StrpTimeTestWrapper();

/**
 * @brief Test parsing time strings using get_time
 * @ingroup group_test
 *
 * @param[in] tm1 Input std::tm struct
 * @param[in] fmt_list Input lists of string time formats to use
 * @return Number of errors encountered
 */
int GetTimeTest(const std::tm& tm1,
                const std::list<std::string>& fmt_list);

/**
 * @brief Test parsing time strings using strptime
 * @ingroup group_test
 *
 * @param[in] tm1 Input std::tm struct
 * @param[in] fmt_list Input lists of string time formats to use
 * @return Number of errors encountered
 */
int StrpTimeTest(const std::tm& tm1,
                 const std::list<std::string>& fmt_list);

/**
 * @brief Compares two std::tm structs and returns a string listing their
 *   differences
 * @ingroup group_test
 *
 * @param[in] tm1 First input std::tm struct
 * @param[in] tm2 Second input std::tm struct
 * @return String listing their differences, or string stating no
 *   differences were found.
 */
std::string TmDiff(const std::tm& tm1,
                   const std::tm& tm2);

/**
 * @brief Function used to run the test if this file was compiled as a stand-alone
 * program.
 * @ingroup group_test
 */
void runMainGetTimeTest();

/**
 * @brief Performs test initialization of the time struct and test strings
 * @ingroup group_test
 *
 * @param[in,out] aTmStruct Output std::tm struct to be used in later testing
 * @param[in,out] aFormatList Output list of string time formatters to be used
 *   in later testing.
 */
void initializeGetTimeTest(std::tm& aTmStruct,
                           std::list<std::string>& aFormatList);

/**
 * CUTE test suite initializer for the test function defined in
 *   GetTimeTest
 *
 * @param[in,out] aSuite CUTE suite to be appended to.
 */
void MakeTimeTestSuite(cute::suite& aSuite);

} // end namespace TEST
} // end namespace SPA

#endif /* TEST_GETTIMETEST_H_ */
