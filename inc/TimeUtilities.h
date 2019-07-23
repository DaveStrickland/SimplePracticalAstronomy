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
 * @file TimeUtilities.h
 * @brief Declaration of Time-related utility functions in the TIME_UTIL namespace
 * @ingroup group_time
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Sep 2, 2018 dks : Initial coding 
 */

#ifndef INC_TIMEUTILITIES_H_
#define INC_TIMEUTILITIES_H_

#include "SpaTimeConstants.h"

namespace SPA
{

// Forward declarations
class DateAndTime;
class JulianDate;

namespace TIME_UTIL
{

/**
 * @brief Calculates the day of the week given an input Julian Date.
 *
 * Implements Section 6 of PAWYC.
 *
 * @param[in] aJulianDate Julian Date for which the day of the week
 *   is to be calculated.
 * @return A WeekDays enumeration of the day of the week corresponding
 *   to the input date. May be cast to an integer by the user.
 */
WeekDays calculateDayInTheWeek(const JulianDate& aJulianDate);

/**
 * @brief Calculates the day of the week given an input DateAndTime.
 *
 * Implements Section 6 of PAWYC.
 *
 * @param[in] aDateAndTime DateAndTime instance for which the
 *   day of the week is to be calculated.
 * @return A WeekDays enumeration of the day of the week corresponding
 *   to the input date. May be cast to an integer by the user.
 */
WeekDays calculateDayInTheWeek(const DateAndTime& aDateAndTime);

/**
 * @brief Calculates the day of the week given an input year, month
 *   and day.
 *
 *  Implements Section 6 of PAWYC.
 *
 * @param[in] aYear Input year
 * @param[in] aMonth Input month
 * @param[in] aDay Input day
 * @return A WeekDays enumeration of the day of the week corresponding
 *   to the input date. May be cast to an integer by the user.
 */
WeekDays calculateDayInTheWeek(int aYear,
                               int aMonth,
                               int aDay);

/**
 * @brief Given a month and day within a year, calculates the day number (i.e.
 *   day number within the year).
 * @ingroup group_time
 *
 * This corresponds to Routine R1 of Section 3 of PAWYC.
 *
 * @note January 1st of any year is day number 1. An artificial day number zero
 *   is often used as an epoch, e.g. 1990 January 0.0 is technically one
 *   day before 1990 January 1, in other words the last day of the previous
 *   year.
 *
 * @limitations Lacks error handling and input sanity checking.
 *
 * @param[in] aYear Input year
 * @param[in] aMonth Input month
 * @param[in] aDay Input day
 * @return Day number within the year.
 */
int calculateDayNumber(int aYear,
                       int aMonth,
                       int aDay);

/**
 * @brief Calculate decimal hours from hours, minutes
 *  and seconds.
 * @ingroup group_time
 * 
 * Implements Section 7 of PAWYC.
 * 
 * @note No attempt to clip the input or output values
 *  is made.
 * 
 * @param[in] Input hours.
 * @param[in] Input minutes.
 * @param[in] Input seconds.
 * @return Decimal hours. 
 */
double calculateDecimalHours(int anHour,
                             int aMinute,
                             double aSeconds);

/**
 * @brief Calculates the date of Easter for a given year
 * @ingroup group_time
 *
 * Corresponds to Section 2 of PAWYC, which uses the method
 * published in Butcher's Ecclesiastical Calendar of 1876.
 * Wikipedia has an extensive discussion of various algorithms for
 * <a href="https://en.wikipedia.org/wiki/Computus#Algorithms">calculating
 * the date of Easter</a>, including the origin of
 * this algorithm which it calls "Anonymous Gregorian algorithm"
 * or the "Meeus/Jones/Butcher algorithm".
 *
 * @limitations Valid for Gregorian dates, i.e. from 1583 onwards.
 *
 * @limitations Input and output are limited to primitive types.
 *
 * @param[in] aYear Input year in Gregorian calendar.
 * @param[out] aMonth Output month number in range 1..12.
 * @param[out] aDay Output day of month in range 1..31.
 */
void calculateEaster(int aYear,
                     int &aMonth,
                     int &aDay);

/**
 * @brief Converts decimal hours to hours, minutes and seconds.
 * @ingroup group_time
 * 
 * Implements Section 8 of PAWYC.
 * 
 * @note Input negative decimal hours result in negative hours,
 *   negative minutes, and negative seconds output.
 * 
 * @param[in] Input decimal hours. 
 * @param[out] Output integer hours.
 * @param[out] Output integer minutes in the range +/-[0,59].
 * @param[out] Output floating point seconds in the range +/-[0,60).
 */
void calculateHoursMinutesAndSeconds(double aDecimalHours,
                                     int& anHours,
                                     int& aMinutes,
                                     double& aSeconds);

/**
 * Converts a year BC or BCE into a form usable by DateAndTime and other SPA code.
 *
 * Because 1 BCE (aka BC) immediately preceded the year 1 CE (aka AD), BCE/BC data
 * need special handling. See PAWYC Section 4.
 *
 * @param[in] aBCE_Year Input positive date in years BC or BCE.
 * @return Negative year
 */
inline int convertBCE_Year(int aBCE_Year)
{
    if (aBCE_Year < 1)
    {
        // This should not happen. TODO throw?
        return 0;
    }
    return -(aBCE_Year - 1);
}

/**
 * @brief Returns the total number of days in a given year
 *  from the Gregorian calendar.
 * @ingroup group_time
 *
 * @param[in] aYear Input year in the Gregorian calendar.
 * @return Number of days in the year, either 365 or 366.
 */
int daysInYear(int aYear);

/**
 * @brief Splits an input real number into its integer and
 *  fractional parts.
 * @ingroup group_time
 *
 * For an input real number \f$x\f$, the integer part \f$I\f$ is
 * \f[
 * I = \lfloor x \rfloor
 * \f]
 * and the fractional part \f$f\f$ is
 * \f[
 * f = frac(x) = x - I.
 * \f]
 * The fractional part has the property \f$f \ge 0\f$.
 *
 * @note Remember that cmath floor truncates toward negative
 *  infinity, and this formula is applied irrespective of whether
 *  \f$x\f$ is positive or negative.
 *
 * @param[in] aRealNumber Input real number to be split into
 *  integer and fractional parts.
 * @param[out] anIntegerPart Output integer part.
 * @param[out] aFractionalPart Output fractional part.
 */
void integerAndFraction(double aRealNumber,
                        double& anIntegerPart,
                        double& aFractionalPart);

/**
 * @brief Returns true of the input year is a leap year according to the Gregorian Calendar.
 * @ingroup group_time
 *
 * According to the rules of the Gregorian Calendar, a year is a leap year if
 * \li It is exactly divisible by 4, AND
 * \li it is not exactly divisible by 100, except when
 * \li it is exactly divisible by 400 (in which case it is a leap year).
 *
 * @param[in] aYear Input year according to the Gregorian Calendar
 * @return True if the year is a leap year.
 */
bool isLeapYear(int aYear);

/**
 * Divides an integer dividend by a divisor and returns
 *  an integer quotient and remainder.
 *
 * Given a dividend D and divisor d, this function calculates
 * an integer quotient Q
 * \f[
 * Q = \left \lfloor{\frac{D}{d}}\right \rfloor
 * \f]
 * and remainder r
 * \f[
 * r = D - (Q \times d).
 * \f]
 *
 * This function is used repeatedly by calculateEaster().
 *
 * @param[in] aDividend Input number to be divided.
 * @param[in] aDivisor Number to divide aDividend by.
 * @param[out] aQuotient  Integer (i.e. truncated) result of
 *   dividing aDividend by aDivisor.
 * @param[out] aRemainder Remainder, i.e. D modulus d.
 */
void quotientAndRemainder(int aDividend,
                          int aDivisor,
                          int& aQuotient,
                          int& aRemainder);


} // end namespace TIME_UTIL
} // end namespace SPA

#endif /* INC_TIMEUTILITIES_H_ */
