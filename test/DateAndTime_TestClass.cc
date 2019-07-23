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
 * @file DateAndTime_TestClass.cc
 * @brief Definition of the DateAndTime_TestClass
 *
 * @ingroup group_test
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Sep 1, 2018 dks : Initial coding 
 */

#include <sstream>
#include <iomanip>
#include <cmath>

#include "DateAndTime_TestClass.h"
#include "DateAndTime.h"
#include "SpaTimeConstants.h"

namespace SPA
{
namespace TEST
{

void DateAndTime_TestClass::testConstructors()
{
    // Expected values.
    int expectedYear = 0;
    int expectedMonth = 0;
    int expectedDay = 0;
    int expectedHours = 0;
    int expectedMinutes = 0;
    double expectedSeconds = 0;
    double expectedUtcOffset = 0;
    double fpTolerance = 1.0e-9; // Floating point tolerance allowed.

    // 1. Default constructor, expect all values zeroed.
    DateAndTime dat1;
    // FYI, std::cout << "example 1: " << dat1 << std::endl;
    std::string dat1Info;
    if ( ! checkDateAndTimeValues(dat1,
                                  expectedYear, expectedMonth, expectedDay,
                                  expectedHours, expectedMinutes, expectedSeconds,
                                  expectedUtcOffset, fpTolerance,
                                  dat1Info) )
    {
        FAILM(dat1Info.c_str());
    }

    // 2. Constructor setting all values.
    expectedYear = 1;
    expectedMonth = 2;
    expectedDay = 3;
    expectedHours = 4;
    expectedMinutes = 5;
    expectedSeconds = 6.7;
    expectedUtcOffset = 8.9;
    DateAndTime dat2(expectedYear, expectedMonth, expectedDay,
                     expectedHours, expectedMinutes, expectedSeconds, expectedUtcOffset);
    // FYI, std::cout << "example 2: " << dat2 << std::endl;
    std::string dat2Info;
    if ( ! checkDateAndTimeValues(dat2,
                                  expectedYear, expectedMonth, expectedDay,
                                  expectedHours, expectedMinutes, expectedSeconds,
                                  expectedUtcOffset, fpTolerance,
                                  dat2Info) )
    {
        FAILM(dat2Info.c_str());
    }

    // Example 3, just use year, month and day.
    expectedYear = 1809;
    expectedMonth = 2;
    expectedDay = 12;
    expectedHours = 0;
    expectedMinutes = 0;
    expectedSeconds = 0;
    expectedUtcOffset = 0;
    DateAndTime dat3(expectedYear, expectedMonth, expectedDay);
    // FYI, std::cout << "example 3: " << dat3 << std::endl;
    std::string dat3Info;
    if ( ! checkDateAndTimeValues(dat3,
                                  expectedYear, expectedMonth, expectedDay,
                                  expectedHours, expectedMinutes, expectedSeconds,
                                  expectedUtcOffset, fpTolerance,
                                  dat3Info) )
    {
        FAILM(dat3Info.c_str());
    }
    return;
}

void DateAndTime_TestClass::testComparisonOperators()
{
    // 1. Compare against self
    DateAndTime dat1(1985, 2, 17, 6, 7, 11, -2.0); // 1985-02-17 04:07:11 UT
    ASSERT_EQUALM("Test 1a: dat1 < dat1", false, dat1 < dat1);
    ASSERT_EQUALM("Test 1b: dat1 > dat1", false, dat1 > dat1);
    ASSERT_EQUALM("Test 1c: dat1 <= dat1", true, dat1 <= dat1);
    ASSERT_EQUALM("Test 1d: dat1 >= dat1", true, dat1 >= dat1);
    ASSERT_EQUALM("Test 1e: dat1 == dat1", true, dat1 == dat1);
    ASSERT_EQUALM("Test 1f: dat1 != dat1", false, dat1 != dat1);


    // 2. Compare against years.
    DateAndTime dat1y_lo(1984, 2, 17, 6, 7, 11, -2.0);
    DateAndTime dat1y_hi(1988, 2, 17, 6, 7, 11, -2.0);

    ASSERT_EQUALM("Test 2a: dat1y_lo < dat1", true, dat1y_lo < dat1);
    ASSERT_EQUALM("Test 2b: dat1y_lo > dat1", false, dat1y_lo > dat1);
    ASSERT_EQUALM("Test 2c: dat1y_lo <= dat1", true, dat1y_lo <= dat1);
    ASSERT_EQUALM("Test 2d: dat1y_lo >= dat1", false, dat1y_lo >= dat1);
    ASSERT_EQUALM("Test 2e: dat1y_lo == dat1", false, dat1y_lo == dat1);
    ASSERT_EQUALM("Test 2f: dat1y_lo != dat1", true, dat1y_lo != dat1);

    ASSERT_EQUALM("Test 2g: dat1y_hi < dat1", false, dat1y_hi < dat1);
    ASSERT_EQUALM("Test 2h: dat1y_hi > dat1", true, dat1y_hi > dat1);
    ASSERT_EQUALM("Test 2i: dat1y_hi <= dat1", false, dat1y_hi <= dat1);
    ASSERT_EQUALM("Test 2j: dat1y_hi >= dat1", true, dat1y_hi >= dat1);
    ASSERT_EQUALM("Test 2k: dat1y_hi == dat1", false, dat1y_hi == dat1);
    ASSERT_EQUALM("Test 2l: dat1y_hi != dat1", true, dat1y_hi != dat1);

    // 3. Compare against months in same year.
    DateAndTime dat1m_lo(1985, 1, 17, 6, 7, 11, -2.0);
    DateAndTime dat1m_hi(1985, 3, 17, 6, 7, 11, -2.0);

    ASSERT_EQUALM("Test 3a: dat1y_lo < dat1", true, dat1m_lo < dat1);
    ASSERT_EQUALM("Test 3b: dat1m_lo > dat1", false, dat1m_lo > dat1);
    ASSERT_EQUALM("Test 3c: dat1m_lo <= dat1", true, dat1m_lo <= dat1);
    ASSERT_EQUALM("Test 3d: dat1m_lo >= dat1", false, dat1m_lo >= dat1);
    ASSERT_EQUALM("Test 3e: dat1m_lo == dat1", false, dat1m_lo == dat1);
    ASSERT_EQUALM("Test 3f: dat1m_lo != dat1", true, dat1m_lo != dat1);

    ASSERT_EQUALM("Test 3g: dat1m_hi < dat1", false, dat1m_hi < dat1);
    ASSERT_EQUALM("Test 3h: dat1m_hi > dat1", true, dat1m_hi > dat1);
    ASSERT_EQUALM("Test 3i: dat1m_hi <= dat1", false, dat1m_hi <= dat1);
    ASSERT_EQUALM("Test 3j: dat1m_hi >= dat1", true, dat1m_hi >= dat1);
    ASSERT_EQUALM("Test 3k: dat1m_hi == dat1", false, dat1m_hi == dat1);
    ASSERT_EQUALM("Test 3l: dat1m_hi != dat1", true, dat1m_hi != dat1);

    // 4. Compare against days in same month.
    DateAndTime dat1d_lo(1985, 2, 16, 6, 7, 11, -2.0);
    DateAndTime dat1d_hi(1985, 2, 18, 6, 7, 11, -2.0);

    ASSERT_EQUALM("Test 4a: dat1y_lo < dat1", true, dat1d_lo < dat1);
    ASSERT_EQUALM("Test 4b: dat1d_lo > dat1", false, dat1d_lo > dat1);
    ASSERT_EQUALM("Test 4c: dat1d_lo <= dat1", true, dat1d_lo <= dat1);
    ASSERT_EQUALM("Test 4d: dat1d_lo >= dat1", false, dat1d_lo >= dat1);
    ASSERT_EQUALM("Test 4e: dat1d_lo == dat1", false, dat1d_lo == dat1);
    ASSERT_EQUALM("Test 4f: dat1d_lo != dat1", true, dat1d_lo != dat1);

    ASSERT_EQUALM("Test 4g: dat1d_hi < dat1", false, dat1d_hi < dat1);
    ASSERT_EQUALM("Test 4h: dat1d_hi > dat1", true, dat1d_hi > dat1);
    ASSERT_EQUALM("Test 4i: dat1d_hi <= dat1", false, dat1d_hi <= dat1);
    ASSERT_EQUALM("Test 4j: dat1d_hi >= dat1", true, dat1d_hi >= dat1);
    ASSERT_EQUALM("Test 4k: dat1d_hi == dat1", false, dat1d_hi == dat1);
    ASSERT_EQUALM("Test 4l: dat1d_hi != dat1", true, dat1d_hi != dat1);

    // 5. Compare against different times within same day.
    DateAndTime dat1hr_lo(1985, 2, 17, 5, 7, 11, -2.0); // 1985-02-17 03:07:11 UT
    DateAndTime dat1hr_hi(1985, 2, 17, 7, 7, 11, -2.0); // 1985-02-17 05:07:11 UT

    ASSERT_EQUALM("Test 5a: dat1hr_lo < dat1", true,  dat1hr_lo < dat1);
    ASSERT_EQUALM("Test 5b: dat1hr_lo > dat1", false, dat1hr_lo > dat1);
    ASSERT_EQUALM("Test 5c: dat1hr_hi < dat1", false, dat1hr_hi < dat1);
    ASSERT_EQUALM("Test 5d: dat1hr_hi > dat1", true,  dat1hr_hi > dat1);

    DateAndTime dat1mn_lo(1985, 2, 17, 6, 6, 11, -2.0); // 1985-02-17 04:06:11 UT
    DateAndTime dat1mn_hi(1985, 2, 17, 6, 8, 11, -2.0); // 1985-02-17 04:08:11 UT

    ASSERT_EQUALM("Test 5e: dat1mn_lo < dat1", true,  dat1mn_lo < dat1);
    ASSERT_EQUALM("Test 5f: dat1mn_lo > dat1", false, dat1mn_lo > dat1);
    ASSERT_EQUALM("Test 5g: dat1mn_hi < dat1", false, dat1mn_hi < dat1);
    ASSERT_EQUALM("Test 5h: dat1mn_hi > dat1", true,  dat1mn_hi > dat1);

    DateAndTime dat1sec_lo(1985, 2, 17, 6, 7, 10.5, -2.0); // 1985-02-17 04:06:10.5 UT
    DateAndTime dat1sec_hi(1985, 2, 17, 6, 7, 11.5, -2.0); // 1985-02-17 04:08:11.5 UT

    ASSERT_EQUALM("Test 5e: dat1sec_lo < dat1", true,  dat1sec_lo < dat1);
    ASSERT_EQUALM("Test 5f: dat1sec_lo > dat1", false, dat1sec_lo > dat1);
    ASSERT_EQUALM("Test 5g: dat1sec_hi < dat1", false, dat1sec_hi < dat1);
    ASSERT_EQUALM("Test 5h: dat1sec_hi > dat1", true,  dat1sec_hi > dat1);

    // 6. UTC time corrections.
    DateAndTime dat1utc_lo(1985, 2, 17, 6, 7, 11, -2.1); // 1985-02-17 04:01:11 UT
    DateAndTime dat1utc_hi(1985, 2, 17, 6, 7, 11, -1.9); // 1985-02-17 04:13:11 UT

    ASSERT_EQUALM("Test 6a: dat1utc_lo < dat1", true,  dat1utc_lo < dat1);
    ASSERT_EQUALM("Test 6b: dat1utc_lo > dat1", false, dat1utc_lo > dat1);
    ASSERT_EQUALM("Test 6c: dat1utc_lo == dat1", false, dat1utc_lo == dat1);
    ASSERT_EQUALM("Test 6d: dat1utc_lo != dat1", true,  dat1utc_lo != dat1);

    ASSERT_EQUALM("Test 6e: dat1utc_hi < dat1", false, dat1utc_hi < dat1);
    ASSERT_EQUALM("Test 6f: dat1utc_hi > dat1", true,  dat1utc_hi > dat1);
    ASSERT_EQUALM("Test 6g: dat1utc_hi == dat1", false, dat1utc_hi == dat1);
    ASSERT_EQUALM("Test 6h: dat1utc_hi != dat1", true,  dat1utc_hi != dat1);
    return;
}

void DateAndTime_TestClass::testGetDayFraction()
{
    DateAndTime dat(1985, 2, 17, 6, 0, 0, 0); // 1985-02-17 06:00:00 UT
    double expectedDayFraction = double(dat.getHours()) / double(SPA_HOURS_IN_DAY)
                    + double(dat.getMinutes()) / double(SPA_MINUTES_IN_DAY)
                    + dat.getSeconds() / double(SPA_SECONDS_IN_DAY);
    // Now offset by UTC correction
    expectedDayFraction += dat.getUtcOffsetHours()/double(SPA_HOURS_IN_DAY);

    double dayFraction = dat.getDayFraction();
    double tolerance = 1.0e-8;
    ASSERT_EQUAL_DELTAM("Expected day fraction mismatch for 1985-02-17 06:00:00 UT",
                        expectedDayFraction,
                        dayFraction,
                        tolerance);
    return;
}

bool DateAndTime_TestClass::checkDateAndTimeValues(const SPA::DateAndTime& aDateAndTime,
                                                   int anExpectedYear,
                                                   int anExpectedMonth,
                                                   int anExpectedDay,
                                                   int anExpectedHours,
                                                   int anExpectedMinutes,
                                                   double anExpectedSeconds,
                                                   double anExpectedUtcOffset,
                                                   double aFloatingPointTolerance,
                                                   std::string& anErrorMessage)
{
    bool passes = true;
    std::ostringstream ss;
    ss << "DateAndTime does NOT match expectation:";
    if (aDateAndTime.getYear() != anExpectedYear)
    {
        ss << " year=" << aDateAndTime.getYear() << " anExpectedYear=" << anExpectedYear;
        passes = false;
    }

    if (aDateAndTime.getMonth() != anExpectedMonth)
    {
        ss << " month=" << aDateAndTime.getMonth() << " anExpectedMonth=" << anExpectedMonth;
        passes = false;
    }

    if (aDateAndTime.getDay() != anExpectedDay)
    {
        ss << " day" << aDateAndTime.getDay() << " anExpectedDay=" << anExpectedDay;
        passes = false;
    }

    if (aDateAndTime.getHours() != anExpectedHours)
    {
        ss << " hours=" << aDateAndTime.getHours() << " anExpectedHours=" << anExpectedHours;
        passes = false;
    }

    if (aDateAndTime.getMinutes() != anExpectedMinutes)
    {
        ss << " minutes=" << aDateAndTime.getMinutes() << " anExpectedMinutes=" << anExpectedMinutes;
        passes = false;
    }

    double secondsDiff = std::fabs(aDateAndTime.getSeconds() - anExpectedSeconds);
    if (secondsDiff > aFloatingPointTolerance)
    {
        ss << " seconds=" << std::fixed << std::setprecision(6)
           << aDateAndTime.getSeconds() << " anExpectedSeconds=" << anExpectedSeconds
           << " difference=" << secondsDiff;
        passes = false;
    }

    double utcOffsetDiff = std::fabs(aDateAndTime.getUtcOffsetHours() - anExpectedUtcOffset);
    if (utcOffsetDiff > aFloatingPointTolerance)
    {
        ss << " utcOffsetHours=" << std::fixed << std::setprecision(6)
           << aDateAndTime.getUtcOffsetHours() << " anExpectedUtcOffset=" << anExpectedUtcOffset
           << " difference=" << utcOffsetDiff;
        passes = false;
    }

    // Only set output string if there is a problem
    if (!passes)
    {
        anErrorMessage = ss.str();
    }
    else
    {
        anErrorMessage.clear();
    }
    return passes;
}

} /* namespace TEST */
} /* namespace SPA */
