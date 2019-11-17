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
 * @file SpaTimeConstants.h
 * @brief Time-related constants for use in SPA
 * @ingroup group_time
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Sep 2, 2018 dks : Initial coding 
 */

#ifndef INC_SPA_TIME_CONSTANTS_H_
#define INC_SPA_TIME_CONSTANTS_H_

#include <array>

namespace SPA
{

/**
 * @brief Number of years in a century
 * @ingroup group_time
 * @source Common expectation
 * @units Years
 */
constexpr int SPA_YEARS_IN_CENTURY = 100;

/**
 * @brief Number of whole days in a non-leap year
 * @ingroup group_time
 * @source Common expectation
 * @units Days
 */
constexpr int SPA_DAYS_IN_NONLEAP_YEAR = 365;

/**
 * @brief Hours in a day.
 * @ingroup group_time
 * @source Common expectation
 * @units Hours
 */
constexpr int SPA_HOURS_IN_DAY = 24;

/**
 * @brief Minutes in an hour.
 * @ingroup group_time
 * @source Common expectation
 * @units Minutes
 */
constexpr int SPA_MINUTES_IN_HOUR = 60;

/**
 * @brief Seconds in a (non-leap) minute.
 * @ingroup group_time
 * @source Common expectation
 * @units Seconds
 */
constexpr int SPA_SECONDS_IN_MINUTE = 60;

/**
 * @brief Seconds in an hour.
 * @ingroup group_time
 * @source Common expectation
 * @units Seconds
 */
constexpr int SPA_SECONDS_IN_HOUR = SPA_SECONDS_IN_MINUTE * SPA_MINUTES_IN_HOUR;

/**
 * @brief Seconds in a day
 * @ingroup group_time
 * @source Common expectation
 * @units Seconds
 */
constexpr int SPA_SECONDS_IN_DAY = SPA_SECONDS_IN_HOUR * SPA_HOURS_IN_DAY;

/**
 * @brief Minutes in a day
 * @ingroup group_time
 * @source Common expectation
 * @units Minutes
 */
constexpr int SPA_MINUTES_IN_DAY = SPA_MINUTES_IN_HOUR * SPA_HOURS_IN_DAY;

/**
 * @brief Number of Solar Days in a Julian Year.
 * @ingroup group_time
 * @source PAWYC Section 4
 * @units Decimal Solar Says
 */
constexpr double SPA_DAYS_IN_JULIAN_YEAR = 365.25;

/**
 * @brief Average number of Solar Days in Gregorian Year.
 * @ingroup group_time
 * @source PAWYC Section 1
 * @units Decimal Solar Says
 */
constexpr double SPA_DAYS_IN_GREGORIAN_YEAR = 365.2425;

/**
 * @brief Number of Solar Days in a Julian Century.
 * @ingroup group_time
 * @source PAWYC Section 4
 * @units Decimal Solar Says
 */
constexpr double SPA_DAYS_IN_JULIAN_CENTURY = SPA_DAYS_IN_JULIAN_YEAR * SPA_YEARS_IN_CENTURY;

/**
 * @brief Average number of Solar Days in Gregorian Century.
 * @ingroup group_time
 * @source PAWYC Section 1
 * @units Decimal Solar Says
 */
constexpr double SPA_DAYS_IN_GREGORIAN_CENTURY = SPA_DAYS_IN_GREGORIAN_YEAR * SPA_YEARS_IN_CENTURY;

/**
 * @brief Zero epoch for Modified Julian Date (MJD), 1858-11-17 00:00:00 UT.
 * @ingroup group_time
 * @source PAWYC Section 4
 * @units Decimal Julian Days since the start of the Julian Period
 */
constexpr double SPA_MJD_EPOCH = 2400000.5;

/**
 * @brief Last day of Julian calendar in most of Western Europe, 1582-10-14 12:00:00 UTC
 * @ingroup group_time
 * @source PAWYC Section 5
 * @units Decimal Julian Days since the start of the Julian Period
 *
 * @note Although not explained in PAWYC Section 5, this constant is
 *  clearly related to the change over from the Julian Calendar
 *  to the Gregorian Calnedar.
 */
constexpr double SPA_LAST_DAY_OF_JULIAN_CALENDAR = 2299160;

/**
 * @brief A conversion constant used in converting Julian Date to
 *  a calendar date, corresponds to 0400 Feb 29, 18:00:00 UTC.
 * @ingroup group_time
 * @source PAWYC Section 5
 * @units Decimal Julian Days since the start of the Julian Period
 *
 * @note Origin not explained in PAWYC.
 */
constexpr double SPA_JULIAN_CONVERSION_CONVERSION_CONST = 1867216.25;

/**
 * @brief Average number of days per month for months
 *   March through December
 * @ingroup group_time
 * @source PAWYC Section 2
 * @units Decimal days
 *
 * @note Although not explained in PAWYC, 30.6 is exactly the average
 *  number of days per month for months March through December
 * (306 days, 10 months).
 * @note This constant can also be used in PAWYC algorithms that
 *  use 30.60001. This value was a necessary historically because
 *  <a href="http://www.hpmuseum.org/cgi-sys/cgiwrap/hpmuseum/archv011.cgi?read=31650">older
 *  calculators lacked the accuracy of ieee754 floating point math.</a>
 *
 */
constexpr double SPA_AVG_DAYS_PER_MONTH = 30.6;

/**
 * @brief Days to the beginning of the month for leap years.
 * @ingroup group_time
 * @source PAWYC Table 2b
 * @units Days
 */
constexpr std::array<int, 12> SPA_DAYSTART_LEAPYEAR = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};

/**
 * @brief Number of days in a week
 * @ingroup group_time
 * @source Common usage.
 * @units Days.
 *
 */
constexpr int SPA_DAYS_PER_WEEK = 7;

/**
 * @brief  Month enumeration, month in year starting from 1.
 * @ingroup group_time
 */
enum Months
{
    JAN = 1,//!< January. Note January is one.
    FEB,    //!< February
    MAR,    //!< March
    APR,    //!< April
    MAY,    //!< May
    JUN,    //!< June
    JUL,    //!< July
    AUG,    //!< August
    SEP,    //!< September
    OCT,    //!< October
    NOV,    //!< November
    DEC     //!< December
};

/**
 * @brief Named days of the week enumeration, starting at 0 with Sunday
 * @ingroup group_time
 */
enum WeekDays
{
    SUN,    //!< Sunday. Note that Sunday is zero.
    MON,    //!< Monday
    TUE,    //!< Tuesday
    WED,    //!< Wednesday
    THU,    //!< Thursday
    FRI,    //!< Friday
    SAT     //!< Saturday
};

} // end namespace SPA

#endif /* INC_SPA_TIME_CONSTANTS_H_ */
