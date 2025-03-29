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
 * @file SpaTime_TestClass.cc
 * @brief Definition of the SpaTime_TestClass
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

#include "SpaTime_TestClass.h"
#include "SpaTime.h"
#include "SpaTimeConstants.h"

namespace SPA
{
namespace TEST
{

void SpaTime_TestClass::testConstructors()
{
    // Expected values.
    int expectedHours = 0;
    int expectedMinutes = 0;
    double expectedSeconds = 0;
    double expectedUtcOffset = 0;
    double fpTolerance = 1.0e-9; // Floating point tolerance allowed.

    // 1. Default constructor, expect all values zeroed.
    SpaTime stime1;
    std::string stime1Info;
    if ( ! checkSpaTimeValues(stime1,
                              expectedHours, expectedMinutes, expectedSeconds,
                              expectedUtcOffset, fpTolerance,
                              stime1Info) )
    {
        FAILM(stime1Info.c_str());
    }

    // 2. Constructor setting all values.
    expectedHours = 4;
    expectedMinutes = 5;
    expectedSeconds = 6.7;
    expectedUtcOffset = 8.9;
    SpaTime stime2(expectedHours, expectedMinutes, expectedSeconds, expectedUtcOffset);
    std::string stime2Info;
    if ( ! checkSpaTimeValues(stime2,
                              expectedHours, expectedMinutes, expectedSeconds,
                              expectedUtcOffset, fpTolerance,
                              stime2Info) )
    {
        FAILM(stime2Info.c_str());
    }

    return;
}

void SpaTime_TestClass::testComparisonOperators()
{
    // 1. Compare against self
    SpaTime stime1(6, 7, 11, -2.0); // 04:07:11 UT
    ASSERT_EQUALM("Test 1a: stime1 < stime1", false, stime1 < stime1);
    ASSERT_EQUALM("Test 1b: stime1 > stime1", false, stime1 > stime1);
    ASSERT_EQUALM("Test 1c: stime1 <= stime1", true, stime1 <= stime1);
    ASSERT_EQUALM("Test 1d: stime1 >= stime1", true, stime1 >= stime1);
    ASSERT_EQUALM("Test 1e: stime1 == stime1", true, stime1 == stime1);
    ASSERT_EQUALM("Test 1f: stime1 != stime1", false, stime1 != stime1);

    // 2. Compare against different hours within same day.
    SpaTime stime1hr_lo(5, 7, 11, -2.0); // 03:07:11 UT
    SpaTime stime1hr_hi(7, 11, -2.0);    // 05:07:11 UT

    ASSERT_EQUALM("Test 2a: stime1hr_lo < stime1hr_hi", true,  stime1hr_lo < stime1hr_hi);
    ASSERT_EQUALM("Test 2b: stime1hr_lo > stime1hr_hi", false, stime1hr_lo > stime1hr_hi);
    ASSERT_EQUALM("Test 2c: stime1hr_hi < stime1hr_lo", false, stime1hr_hi < stime1hr_lo);
    ASSERT_EQUALM("Test 2d: stime1hr_hi > stime1hr_lo", true,  stime1hr_hi > stime1hr_lo);
    ASSERT_EQUALM("Test 2e: stime1hr_lo == stime1hr_hi", false, stime1hr_lo == stime1hr_hi);
    ASSERT_EQUALM("Test 2f: stime1hr_lo != stime1hr_hi", true,  stime1hr_lo != stime1hr_hi);

    // 3. Compare against different minutes within same day.
    SpaTime stime1mn_lo(6, 6, 11, -2.0); // 04:06:11 UT
    SpaTime stime1mn_hi(6, 8, 11, -2.0); // 04:08:11 UT

    ASSERT_EQUALM("Test 3a: stime1mn_lo < stime1mn_hi", true,  stime1mn_lo < stime1mn_hi);
    ASSERT_EQUALM("Test 3b: stime1mn_lo > stime1mn_hi", false, stime1mn_lo > stime1mn_hi);
    ASSERT_EQUALM("Test 3c: stime1mn_hi < stime1mn_lo", false, stime1mn_hi < stime1mn_lo);
    ASSERT_EQUALM("Test 3d: stime1mn_hi > stime1mn_lo", true,  stime1mn_hi > stime1mn_lo);
    ASSERT_EQUALM("Test 3e: stime1mn_lo == stime1mn_hi", false, stime1mn_lo == stime1mn_hi);
    ASSERT_EQUALM("Test 3f: stime1mn_lo != stime1mn_hi", true,  stime1mn_lo != stime1mn_hi);

    // 4. Compare against different  seconds within same day.
    SpaTime stime1sec_lo(6, 7, 10.5, -2.0); // 04:06:10.5 UT
    SpaTime stime1sec_hi(6, 7, 11.5, -2.0); // 04:08:11.5 UT

    ASSERT_EQUALM("Test 4a: stime1sec_lo < stime1sec_hi", true,  stime1sec_lo < stime1sec_hi);
    ASSERT_EQUALM("Test 4b: stime1sec_lo > stime1sec_hi", false, stime1sec_lo > stime1sec_hi);
    ASSERT_EQUALM("Test 4c: stime1sec_hi < stime1sec_lo", false, stime1sec_hi < stime1sec_lo);
    ASSERT_EQUALM("Test 4d: stime1sec_hi > stime1sec_lo", true,  stime1sec_hi > stime1sec_lo);
    ASSERT_EQUALM("Test 4e: stime1sec_lo == stime1sec_hi", false, stime1sec_lo == stime1sec_hi);
    ASSERT_EQUALM("Test 4f: stime1sec_lo != stime1sec_hi", true,  stime1sec_lo != stime1sec_hi);

    // 5. UTC time corrections.
    SpaTime stime1utc_lo(6, 7, 11, -2.1); // 04:01:11 UT
    SpaTime stime1utc_hi(6, 7, 11, -1.9); // 04:13:11 UT

    ASSERT_EQUALM("Test 5a: stime1utc_lo < stime1utc_hi", true,  stime1utc_lo < stime1utc_hi);
    ASSERT_EQUALM("Test 5b: stime1utc_lo > stime1utc_hi", false, stime1utc_lo > stime1utc_hi);
    ASSERT_EQUALM("Test 5c: stime1utc_hi < stime1utc_lo", false, stime1utc_hi < stime1utc_lo);
    ASSERT_EQUALM("Test 5d: stime1utc_hi > stime1utc_lo", true,  stime1utc_hi > stime1utc_lo);
    ASSERT_EQUALM("Test 5e: stime1utc_lo == stime1utc_hi", false, stime1utc_lo == stime1utc_hi);
    ASSERT_EQUALM("Test 5f: stime1utc_lo != stime1utc_hi", true,  stime1utc_lo != stime1utc_hi);
    return;
}

void SpaTime_TestClass::testGetDayFraction()
{
    // Lambda that calculates the day fraction as we expect it.
    auto edfLambda = [](SpaTime sTime)
    {
        double edf = double(sTime.getHours()) / double(SPA_HOURS_IN_DAY)
            + double(sTime.getMinutes()) / double(SPA_MINUTES_IN_DAY)
            + sTime.getSeconds() / double(SPA_SECONDS_IN_DAY);
        return edf;
    };
        
    SpaTime stime1(6, 0, 0, 0); // 1985-02-17 06:00:00 UT
    double expectedDayFraction = edfLambda(stime1);

    // Now offset by UTC correction
    expectedDayFraction += stime1.getUtcOffsetHours()/double(SPA_HOURS_IN_DAY);

    double dayFraction = stime1.getDayFraction();
    double tolerance = 1.0e-8;
    ASSERT_EQUAL_DELTAM("1. Expected day fraction mismatch for 06:00:00 UT",
                        expectedDayFraction,
                        dayFraction,
                        tolerance);

    // 2. Test UTC offset
    SpaTime stime2(16, 30, 24, -6.0);   // 16:30:24 TZ offset -6.0 hours
    expectedDayFraction = edfLambda(stime2);    // No utc offset
    expectedDayFraction += stime2.getUtcOffsetHours()/double(SPA_HOURS_IN_DAY);
    ASSERT_EQUAL_DELTAM("2. Expected day fraction mismatch for 16:30:24 TZ offset -6:00",
        expectedDayFraction,
        stime2.getDayFraction(),
        tolerance);
    return;
}

void SpaTime_TestClass::testGetDecimalHours()
{   
    // Test decimal hours into a day from local (not UT) midnight.
    const double tolerance = 1.0e-8;

    SpaTime stime1(6, 30, 0, 4.0);   // 06:30:00 TZ +4.0 hours
    double expected_dhours1 = 6.5;
    ASSERT_EQUAL_DELTAM("1. Expected decimal hours mismatch for 06:30:00 TZ +4.0 hours",
        expected_dhours1,
        stime1.getDecimalHours(),
        tolerance);

    SpaTime stime2(23, 21, 30, -5.0);   // 23:21:30 TZ -5.0 hours
        double expected_dhours2 = 23.35833333;
        ASSERT_EQUAL_DELTAM("2. Expected decimal hours mismatch for 23:21:30 TZ -5.0 hours",
            expected_dhours2,
            stime2.getDecimalHours(),
            tolerance);
    

    return;
}

void SpaTime_TestClass::testGetHMS()
{   
    // Test decimal hours into a day from UT midnight.
    const double tolerance = 1.0e-8;

    SpaTime stime1(6, 30, 0, 4.0);   // 06:30:00 TZ +4.0 hours = 02:30:00 UTC
    double expected_dhours1 = 6.5 - 4.0;

    SpaTime stime2(23, 21, 30, -5.0);   // 23:21:30 TZ -5.0 hours

    FAILM("not yet implemented");
    return;
}

void SpaTime_TestClass::testGetDecimalHoursUTC()
{   
    // Test decimal hours into  H:M:S 
    const double tolerance = 1.0e-8;

    SpaTime stime1(6, 30, 0, 4.0);   // 06:30:00 TZ +4.0 hours = 02:30:00 UTC
    double expected_dhours1 = 6.5 - 4.0;
    ASSERT_EQUAL_DELTAM("1. Expected decimal hours from UTC mismatch for 06:30:00 TZ +4.0 hours",
        expected_dhours1,
        stime1.getDecimalHoursUTC(),
        tolerance);

    SpaTime stime2(23, 21, 30, -5.0);   // 23:21:30 TZ -5.0 hours
        double expected_dhours2 = 23.35833333 + 5.0 -24.0;
        ASSERT_EQUAL_DELTAM("2. Expected decimal hours from UTC mismatch for 23:21:30 TZ -5.0 hours",
            expected_dhours2,
            stime2.getDecimalHoursUTC(),
            tolerance);
    return;
}

bool SpaTime_TestClass::checkSpaTimeValues(const SPA::SpaTime& aSpaTime,
                                           int anExpectedHours,
                                           int anExpectedMinutes,
                                           double anExpectedSeconds,
                                           double anExpectedUtcOffset,
                                           double aFloatingPointTolerance,
                                           std::string& anErrorMessage)
{
    bool passes = true;
    std::ostringstream ss;
    ss << "SpaTime does NOT match expectation:";
    if (aSpaTime.getHours() != anExpectedHours)
    {
        ss << " hours=" << aSpaTime.getHours() << " anExpectedHours=" << anExpectedHours;
        passes = false;
    }

    if (aSpaTime.getMinutes() != anExpectedMinutes)
    {
        ss << " minutes=" << aSpaTime.getMinutes() << " anExpectedMinutes=" << anExpectedMinutes;
        passes = false;
    }

    double secondsDiff = std::fabs(aSpaTime.getSeconds() - anExpectedSeconds);
    if (secondsDiff > aFloatingPointTolerance)
    {
        ss << " seconds=" << std::fixed << std::setprecision(6)
           << aSpaTime.getSeconds() << " anExpectedSeconds=" << anExpectedSeconds
           << " difference=" << secondsDiff;
        passes = false;
    }

    double utcOffsetDiff = std::fabs(aSpaTime.getUtcOffsetHours() - anExpectedUtcOffset);
    if (utcOffsetDiff > aFloatingPointTolerance)
    {
        ss << " utcOffsetHours=" << std::fixed << std::setprecision(6)
           << aSpaTime.getUtcOffsetHours() << " anExpectedUtcOffset=" << anExpectedUtcOffset
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

void SpaTime_TestClass::testGettersAndSetters()
{
    double tolerance = 1.0e-8;

    // Constructor setting all values.
    int expectedHours = 4;
    int expectedMinutes = 5;
    double expectedSeconds = 6.7;
    double expectedUtcOffset = 8.9;
    SpaTime spat(expectedHours, expectedMinutes, expectedSeconds, expectedUtcOffset);

    ASSERT_EQUALM("After ctor, hour does not match expectation", 
        expectedHours,
        spat.getHours());
    ASSERT_EQUALM("After ctor, minute does not match expectation", 
        expectedMinutes,
        spat.getMinutes());
    ASSERT_EQUAL_DELTAM("After ctor, second does not match expectation", 
        expectedSeconds,
        spat.getSeconds(),
        tolerance);
    ASSERT_EQUAL_DELTAM("After ctor, UTC offset does not match expectation", 
        expectedUtcOffset,
        spat.getUtcOffsetHours(),
        tolerance);

    // Now test the setters.
    expectedHours = 6;
    expectedMinutes = 30;
    expectedSeconds = 33.5;
    expectedUtcOffset = -5.0;
    spat.setHours(expectedHours);
    spat.setMinutes(expectedMinutes);
    spat.setSeconds(expectedSeconds);
    spat.setUtcOffsetHours(expectedUtcOffset);
    ASSERT_EQUALM("After setter, hour does not match expectation", 
        expectedHours,
        spat.getHours());
    ASSERT_EQUALM("After setter, minute does not match expectation", 
        expectedMinutes,
        spat.getMinutes());
    ASSERT_EQUAL_DELTAM("After setter, second does not match expectation", 
        expectedSeconds,
        spat.getSeconds(),
        tolerance);
    ASSERT_EQUAL_DELTAM("After setter, UTC offset does not match expectation", 
        expectedUtcOffset,
        spat.getUtcOffsetHours(),
        tolerance);
    return;
}

void SpaTime_TestClass::testOstreamOperator()
{
    std::ostringstream ss;
    SpaTime spat(6, 33, 21.52, -5.0); // 1985-02-17 06:33:21.52 UTC-5.0 hours
    ss << spat;
    std::string output_str = ss.str();   

    // Very mutch a cludge, this is what we expect the ostream operator to
    // produce.
    std::string expected_str("SpaTime{ theHours=6 theMinutes=33 theSeconds=21.520000 theUTC_OffsetHours=-5.0000 }");

    ASSERT_EQUALM("ostream string does not match expectation",
        expected_str, 
        output_str);
    return;
}

} /* namespace TEST */
} /* namespace SPA */
