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
 * @file JulianDate_TestClass.cc
 * @brief Definition of the JulianDate_TestClass
 *
 * @ingroup group_test
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Aug 29, 2018 dks : Initial coding
 */

#include <cmath>
#include <iostream>
#include <iomanip>
#include "SpaTestUtilities.h"
#include "JulianDate_TestClass.h"
#include "JulianDate.h"
#include "TimeDifference.h"
#include "DateAndTime.h"

namespace SPA
{
namespace TEST
{

JulianDate_TestClass::JulianDate_TestClass() : theTolerance(1.0e-9),
                theDigitsOfPrecision(10)
{
}

JulianDate_TestClass::~JulianDate_TestClass()
{
}

void JulianDate_TestClass::testIntTruncates()
{
    double input1 = 3.5;
    double expectedFloor1 = 3.0;
    double expectedInt1 = 3.0;
    ASSERT_EQUAL_DELTAM("Int did not truncate toward zero as expected.",
                        expectedInt1,
                        int(input1),
                        theTolerance);
    ASSERT_EQUAL_DELTAM("Floor did not round down as expected.",
                        expectedFloor1,
                        std::floor(input1),
                        theTolerance);

    double input2 = -3.5;
    double expectedFloor2 = -4.0;
    double expectedInt2 = -3.0;
    ASSERT_EQUAL_DELTAM("Int did not truncate toward zero as expected.",
                        expectedInt2,
                        int(input2),
                        theTolerance);
    ASSERT_EQUAL_DELTAM("Floor did not round down as expected.",
                        expectedFloor2,
                        std::floor(input2),
                        theTolerance);
    return;
}

void JulianDate_TestClass::testConstructors()
{
    // 1. Default constructor should give zero.
    double expected1 = 0;
    SPA::JulianDate jd1;
    spaTestFloatingPointEqual("1. Default constructor",
                              expected1,
                              jd1.getDecimalDays(),
                              theTolerance,
                              theDigitsOfPrecision);

    // 2. Construct with a double julian date, Jan 01 2000 at 12:00:00 UT
    double j2000 = 2451545;
    SPA::JulianDate jd2(j2000);
    spaTestFloatingPointEqual("2. Double constructor",
                              j2000,
                              jd2.getDecimalDays(),
                              theTolerance,
                              theDigitsOfPrecision);

    // 3. 1985-02-17 06:00:00 UTC : JulianDate 2446113.75 checked with xtime
    double expected3 =  2446113.75;
    SPA::JulianDate jd3(1985, 2, 17, 6, 0, 0, 0);
    spaTestFloatingPointEqual("3. YMDHMS TZ constructor with 1985-02-17 06:00:00 UTC",
                              expected3,
                              jd3.getDecimalDays(),
                              theTolerance,
                              theDigitsOfPrecision);

    // 4. 2009-06-19 18:00:00 UTC : JulianDate 2455002.25
    // This example is in PAWY Spreadsheet book, checked with xtime
    double expected4 =  2455002.25;
    SPA::JulianDate jd4(2009, 6, 19, 18, 0, 0, 0);
    spaTestFloatingPointEqual("4. YMDHMS TZ constructor with 2009-06-19 18:00:00 UTC",
                              expected4,
                              jd4.getDecimalDays(),
                              theTolerance,
                              theDigitsOfPrecision);

    // 5. Example before Gregorian calendar: the date of Cesare Borgia's death
    // Input Gregorian 1507-03-12 12:00:00 UTC : JulianDate 2271550.00
    // Input Julian 1507-03-12 (equiv to 1507-03-22 Gregorian) 12:00:00 UTC : JulianDate 2271560.00
    double expected5 =  2271560.00;
    SPA::JulianDate jd5(1507, 3, 12, 12, 0, 0, 0);
    spaTestFloatingPointEqual("5. YMDHMS TZ constructor with 1507-03-12 12:00:00 UTC",
                              expected5,
                              jd5.getDecimalDays(),
                              theTolerance,
                              theDigitsOfPrecision);
    return;
}

void JulianDate_TestClass::testOperators()
{
    // 1. Assignment operator. 2009-06-19 18:00:00 UTC : JulianDate 2455002.25
    // This example is in PAWY Spreadsheet book, checked with xtime
    double expected1 =  2455002.25;
    SPA::JulianDate jd1(2009, 6, 19, 18, 0, 0, 0);
    SPA::JulianDate jd2 = jd1;
    spaTestFloatingPointEqual("1. Assignment operator failed",
                              expected1,
                              jd2.getDecimalDays(),
                              theTolerance,
                              theDigitsOfPrecision);

    // 2. operator-(), jd2 - jd1 should have zero difference.
    SPA::TimeDifference timeDiff2 = jd2 - jd1;
    double expectedDifference2 = 0;
    spaTestFloatingPointEqual("2. JulianDate operator-() failed",
                              expectedDifference2,
                              timeDiff2.getDecimalDayDifference(),
                              theTolerance,
                              theDigitsOfPrecision);

    // 3. operator-(), create a Julian date one month later than jd2
    SPA::JulianDate jd3(2009, 7, 19, 18, 0, 0, 0);
    SPA::TimeDifference timeDiff3a = jd3 - jd2; // +30
    SPA::TimeDifference timeDiff3b = jd2 - jd3; // -30
    double expectedDifference3 = 30;
    spaTestFloatingPointEqual("3a. JulianDate/JulianDate operator-() failed",
                              expectedDifference3,
                              timeDiff3a.getDecimalDayDifference(),
                              theTolerance,
                              theDigitsOfPrecision);
    spaTestFloatingPointEqual("3b. JulianDate/JulianDate operator-() failed",
                              -expectedDifference3,
                              timeDiff3b.getDecimalDayDifference(),
                              theTolerance,
                              theDigitsOfPrecision);

    // 4. Non-compound operator -() and operator +() using a JulianDate and a TimeDifference
    SPA::JulianDate jd4a = jd3 - timeDiff3a; // Should equal jd2 exactly
    SPA::JulianDate jd4b = jd3 + timeDiff3b; // Should equal jd2 exactly
    SPA::JulianDate jd4c = jd2 - timeDiff3b; // Should equal jd3 exactly
    SPA::JulianDate jd4d = jd2 + timeDiff3a; // Should equal jd3 exactly
    spaTestFloatingPointEqual("4a. JulianDate/TimeDifference operator-() failed",
                              jd2.getDecimalDays(),
                              jd4a.getDecimalDays(),
                              theTolerance,
                              theDigitsOfPrecision);
    spaTestFloatingPointEqual("4b. JulianDate/TimeDifference operator+() failed",
                              jd2.getDecimalDays(),
                              jd4b.getDecimalDays(),
                              theTolerance,
                              theDigitsOfPrecision);
    spaTestFloatingPointEqual("4c. JulianDate/TimeDifference operator-() failed",
                              jd3.getDecimalDays(),
                              jd4c.getDecimalDays(),
                              theTolerance,
                              theDigitsOfPrecision);
    spaTestFloatingPointEqual("4d. JulianDate/TimeDifference operator+() failed",
                              jd3.getDecimalDays(),
                              jd4d.getDecimalDays(),
                              theTolerance,
                              theDigitsOfPrecision);
    // 5. Compound operator-=() and operator+=().
    SPA::JulianDate jd5a = jd2;
    jd5a += timeDiff3a; // should equal jd3
    SPA::JulianDate jd5b = jd2;
    jd5b -= timeDiff3b; // should equal jd3
    spaTestFloatingPointEqual("5a. JulianDate/TimeDifference operator+=() failed",
                              jd3.getDecimalDays(),
                              jd5a.getDecimalDays(),
                              theTolerance,
                              theDigitsOfPrecision);
    spaTestFloatingPointEqual("5b. JulianDate/TimeDifference operator-=() failed",
                              jd3.getDecimalDays(),
                              jd5b.getDecimalDays(),
                              theTolerance,
                              theDigitsOfPrecision);

    return;
}

void JulianDate_TestClass::testGetModifiedJulianDate()
{
    const int NUM_TESTS = 4;

    std::array<double, NUM_TESTS> input_jd = {{SPA_MJD_EPOCH,
                                              2400000.5,
                                              2458386.10018519,
                                              2397000.5}};
    std::array<double, NUM_TESTS> expected_mjd = {{0,
                                                  0,
                                                  58385.60018519,
                                                  -3000}};
    for (int iTest = 0; iTest < NUM_TESTS; iTest++)
    {
        JulianDate jd(input_jd.at(iTest));
        double mjd = jd.getModifiedJulianDate();
        spaTestFloatingPointEqual("getModifiedJulianDate failed",
                                  expected_mjd.at(iTest),
                                  mjd,
                                  theTolerance,
                                  theDigitsOfPrecision);
    }
    return;
}

void JulianDate_TestClass::testGetDateAndTime()
{
    double jdTolerance = 1.0e-4; // tolerance in fractional days

    /*
     * From https://heasarc.gsfc.nasa.gov/cgi-bin/Tools/xTime/xTime.pl
     * we know that 2019-01-06 06:00:00 == 2458489.75000000
     */
    DateAndTime date(2019, 1, 6, 6, 0, 0, 0);
    JulianDate jd(date);
    double expectedJulianData = 2458489.75000000;
    ASSERT_EQUAL_DELTAM("1a. Initial conversion to JulianDate incorrect.",
                        expectedJulianData,
                        jd.getDecimalDays(),
                        jdTolerance);
    DateAndTime outputDate = jd.getDateAndTime();

    // To check for approximate equivalence, we use Julian Dates
    // and time differences. This is non-circular because the
    // conversion to JD is independent of the conversion from JD
    // to DateAndTime.
    TimeDifference td = jd - JulianDate(outputDate);
    if ( std::fabs(td.getDecimalDayDifference()) > jdTolerance)
    {
        std::ostringstream ss;
        ss << "1b. Conversion from JD to DateAndTime incorrect: ";
        ss << " Input date=" << date
           << ", Output date=" << outputDate
           << ", difference=" << td.getDecimalDayDifference()
           << " days, which exceeds test tolerance=" << jdTolerance;
        FAILM(ss.str());
    }
}


} // end namespace TEST
} // end namespace SPA
