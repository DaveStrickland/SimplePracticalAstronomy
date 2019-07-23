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
 * @file SpaTestUtilities.h
 * @brief Declarations of test utility functions used for SPA testing
 * @ingroup group_test
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Sep 2, 2018 dks : Initial coding 
 */

#ifndef TEST_SPATESTUTILITIES_H_
#define TEST_SPATESTUTILITIES_H_

#include <string>
#include <cmath>
#include "SpaTimeConstants.h"

namespace SPA
{
namespace TEST
{

/**
 * @brief A utility replacement for CUTE's ASSERT_EQUAL_DELTAM that reports
 *   results using std::fixed with a user-supplied number of digits
 *   of precision.
 * @ingroup group_test
 *
 * Checks whether std::fabs(anActualValue - anExpectedValue) > aTolerance,
 * and if so, prints out the input message and data values using CUTE's
 * FAILM() method.
 *
 * @param[in] aMessage Descriptive string to be used in the error message
 *   if anExpectedValue is not equal to anActualValue to within the
 *   test tolerance aTolerance.
 * @param[in] anExpectedValue Expected data value.
 * @param[in] anActualValue Actual measured value.
 * @param[in] aTolerance Test tolerance for floating point equality test.
 * @param[in] aNumberOfDigitsOfPrecision Number of digits of precision to
 *   which anExpectedValue, anActualValue and aTolerance will be printed
 *   in any error message.
 */
void spaTestFloatingPointEqual(const std::string& aMessage,
                               double anExpectedValue,
                               double anActualValue,
                               double aTolerance,
                               int aNumberOfDigitsOfPrecision = 6);

} /* namespace TEST */
} /* namespace SPA */

#endif /* TEST_SPATESTUTILITIES_H_ */
