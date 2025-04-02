/*
 * Copyright (C) 2020-2025 David Strickland, <dave.strickland@gmail.com>
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
 * @file SpaDate_TestClass.cc
 * @brief Definition of the SpaDate_TestClass
 *
 * @ingroup group_test
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Feb 01, 2020 dks : Initial coding 
 */

#include <sstream>
#include <iomanip>
#include <cmath>

#include "SpaDate_TestClass.h"
#include "SpaDate.h"
#include "SpaTimeConstants.h"

namespace SPA
{
namespace TEST
{

void SpaDate_TestClass::testConstructors()
{
    // Expected values.
    int expectedYear = 0;
    int expectedMonth = 0;
    int expectedDay = 0;

    // 1. Default constructor, expect all values zeroed.
    SpaDate dat1;
    std::string dat1Info;
    if ( ! checkSpaDateValues(dat1,
                              expectedYear, expectedMonth, expectedDay,
                              dat1Info) )
    {
        FAILM(dat1Info.c_str());
    }

    // 2. Constructor setting all values.
    expectedYear = 1;
    expectedMonth = 2;
    expectedDay = 3;
    SpaDate dat2(expectedYear, expectedMonth, expectedDay);
    std::string dat2Info;
    if ( ! checkSpaDateValues(dat2,
                              expectedYear, expectedMonth, expectedDay,
                              dat2Info) )
    {
        FAILM(dat2Info.c_str());
    }

    return;
}

void SpaDate_TestClass::testComparisonOperators()
{
    // 1. Compare against self
    SpaDate dat1(1985, 2, 17); // 1985-02-17
    ASSERT_EQUALM("Test 1a: dat1 < dat1", false, dat1 < dat1);
    ASSERT_EQUALM("Test 1b: dat1 > dat1", false, dat1 > dat1);
    ASSERT_EQUALM("Test 1c: dat1 <= dat1", true, dat1 <= dat1);
    ASSERT_EQUALM("Test 1d: dat1 >= dat1", true, dat1 >= dat1);
    ASSERT_EQUALM("Test 1e: dat1 == dat1", true, dat1 == dat1);
    ASSERT_EQUALM("Test 1f: dat1 != dat1", false, dat1 != dat1);


    // 2. Compare against years.
    SpaDate dat1y_lo(1984, 2, 17);
    SpaDate dat1y_hi(1988, 2, 17);

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
    SpaDate dat1m_lo(1985, 1, 17);
    SpaDate dat1m_hi(1985, 3, 17);

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
    SpaDate dat1d_lo(1985, 2, 16);
    SpaDate dat1d_hi(1985, 2, 18);

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
    return;
}

bool SpaDate_TestClass::checkSpaDateValues(const SPA::SpaDate& aSpaDate,
                                                   int anExpectedYear,
                                                   int anExpectedMonth,
                                                   int anExpectedDay,
                                                   std::string& anErrorMessage)
{
    bool passes = true;
    std::ostringstream ss;
    ss << "SpaDate does NOT match expectation:";
    if (aSpaDate.getYear() != anExpectedYear)
    {
        ss << " year=" << aSpaDate.getYear() << " anExpectedYear=" << anExpectedYear;
        passes = false;
    }

    if (aSpaDate.getMonth() != anExpectedMonth)
    {
        ss << " month=" << aSpaDate.getMonth() << " anExpectedMonth=" << anExpectedMonth;
        passes = false;
    }

    if (aSpaDate.getDay() != anExpectedDay)
    {
        ss << " day" << aSpaDate.getDay() << " anExpectedDay=" << anExpectedDay;
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

void SpaDate_TestClass::testGettersAndSetters()
{
    double tolerance = 1.0e-8;

    // Constructor setting all values.
    int expectedYear = 1;
    int expectedMonth = 2;
    int expectedDay = 3;
    SpaDate dat(expectedYear, expectedMonth, expectedDay);

    ASSERT_EQUALM("After ctor, year does not match expectation", 
        expectedYear,
        dat.getYear());
    ASSERT_EQUALM("After ctor, month does not match expectation", 
        expectedMonth,
        dat.getMonth());
    ASSERT_EQUALM("After ctor, day does not match expectation", 
        expectedDay,
        dat.getDay());

    // Now test the setters.
    expectedYear = 2024;
    expectedMonth = 12;
    expectedDay = 25;
    dat.setYear(expectedYear);
    dat.setMonth(expectedMonth);
    dat.setDay(expectedDay);
    ASSERT_EQUALM("After setter, year does not match expectation", 
        expectedYear,
        dat.getYear());
    ASSERT_EQUALM("After setter, month does not match expectation", 
        expectedMonth,
        dat.getMonth());
    ASSERT_EQUALM("After setter, day does not match expectation", 
        expectedDay,
        dat.getDay());
    return;
}

void SpaDate_TestClass::testOstreamOperator()
{
    std::ostringstream ss;
    SpaDate dat(1985, 2, 17); // 1985-02-17 
    ss << dat;
    std::string output_str = ss.str();   

    // Very mutch a cludge, this is what we expect the ostream operator to
    // produce.
    std::string expected_str("SpaDate{ theYear=1985 theMonth=2 theDay=17 }");

    ASSERT_EQUALM("ostream string does not match expectation",
        expected_str, 
        output_str);
    return;
}

void SpaDate_TestClass::testGetDayNumber()
{
    std::ostringstream ss;

    // Additional test cases can be constructed using the unix cal command, e.g.
    // `cal 02 2024` shows the calendar for February 2024, and the ordinal day
    // numbers can be shown using `cal -j 02 2024`

    const int NUM_TESTS = 4;
    std::array<int, NUM_TESTS> iYears = {{1985, 2018, 2024, 2024}};
    std::array<int, NUM_TESTS> iMonth = {{2,    9,    2,    3}};
    std::array<int, NUM_TESTS> iDay   = {{17,   2,    29,   3}};
    std::array<int, NUM_TESTS> expectedDayNumber = {{48, 245, 60, 63}};
    for (int iTest = 0; iTest < NUM_TESTS; iTest++)
    {
        int year  = iYears[iTest];
        int month = iMonth[iTest];
        int day   = iDay[iTest];
        SpaDate sdate(year, month, day);
        int expected = expectedDayNumber[iTest];

        int oDayNum = sdate.getDayNumber();
        ss << "  Test " << iTest << " year=" << year
           << " month=" << month
           << " day=" << day
           << " expectedDayNumber=" << expected
           << ", got dayNumber=" << oDayNum;
        if (oDayNum !=  expected)
        {
            FAILM(ss.str());
        }
        ss.str(std::string()); // clear ss
    }
    return;
}

void SpaDate_TestClass::testDifferenceOperator()
{
    const double tolerance = 1.0e-8;
    const int NUM_TESTS = 4;
    std::ostringstream ss;

    // Julian date for a given date can be obtained from https://aa.usno.navy.mil/data/JulianDate
    SpaDate sdate1(2024, 6, 18);
    double trueJD1 = 2460479.5;
 
    std::array<int, NUM_TESTS> iYears = {{2023, 2024, 2024, 2027}};
    std::array<int, NUM_TESTS> iMonth = {{6,    5,    6,    6}};
    std::array<int, NUM_TESTS> iDay   = {{18,   18,   18,   25}};
    std::array<double, NUM_TESTS> iJD = {{2460113.5, 
                                          2460448.5, 
                                          2460479.5, 
                                          2461581.5}};
    for (int iTest = 0; iTest < NUM_TESTS; iTest++)
    {
        int year  = iYears[iTest];
        int month = iMonth[iTest];
        int day   = iDay[iTest];
        SpaDate sdate2(year, month, day);
        int expected = trueJD1 - iJD[iTest];

        TimeDifference tdiff = sdate1 - sdate2;

        ss << "  Test " << iTest << " sdate1=" << sdate1
           << " minus sdate2=" << sdate2
           << " should be " << expected
           << " days, but got " << expected
           << ", got dayNumber=" << tdiff.getDecimalDayDifference();
        std::string eMessage(ss.str());
        ss.str(std::string()); // clear ss
        ASSERT_EQUAL_DELTAM(eMessage,
            expected,
            tdiff.getDecimalDayDifference(),
            tolerance);
    }
    return;
}

} /* namespace TEST */
} /* namespace SPA */
