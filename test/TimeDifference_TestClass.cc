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
 * @file TimeDifference_TestClass.cc
 * @brief Definition for the CUTE test class for the TimeDifference class.
 * @ingroup group_test
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Sep 22, 2018 dks : Initial coding 
 */

#include "TimeDifference_TestClass.h"
#include "TimeDifference.h"

namespace SPA
{
namespace TEST
{

void TimeDifference_TestClass::testConstructors()
{
    // Default constructor, can do an exact binary comparison against zero.
    SPA::TimeDifference timeDiff1;
    double expectedDayDifference = 0;
    ASSERT_EQUALM("Default TimeDifference constructor failed",
                  expectedDayDifference,
                  timeDiff1.getDecimalDayDifference());

    // Construct with an input decimal day difference.
    expectedDayDifference = 4.5;
    double tolerance = 1.0e-14;
    SPA::TimeDifference timeDiff2(expectedDayDifference);
    ASSERT_EQUAL_DELTAM("Value TimeDifference constructor failed",
                        expectedDayDifference,
                        timeDiff2.getDecimalDayDifference(),
                        tolerance);
}

void TimeDifference_TestClass::testSetters()
{
    // Construct with an input decimal day difference.
    double initialDayDifference = 4.5;
    double expectedDayDifference = 7.5;
    double tolerance = 1.0e-14;
    SPA::TimeDifference timeDiff1(initialDayDifference);
    timeDiff1.setDecimalDayDifference(expectedDayDifference);
    ASSERT_EQUAL_DELTAM("setDecimalDayDifference did not work",
                        expectedDayDifference,
                        timeDiff1.getDecimalDayDifference(),
                        tolerance);
}

} /* namespace TEST */
} /* namespace SPA */
