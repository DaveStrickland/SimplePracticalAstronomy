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

#ifndef SPA_JULIANDATE_H_
#define SPA_JULIANDATE_H_

namespace SPA
{

/**
 * @file JulianDate.h
 * @brief Declaration of the JulianDate class.
 * @ingroup group_time
 *
 * @author Dave Strickland <dave.strickland@gmail.com>
 *
 * @version Aug 25, 2018 dks : Initial coding
 */

/**
 * @defgroup group_time Time
 *
 * @brief  Time-related sections from Practical Astronomy With Your Calculator
 */

// Forward declarations
class DateAndTime;
class TimeDifference;

/**
 * @brief Astronomical Julian Date class JulianDate
 * @ingroup group_time
 *
 * The Julian Date is a continuous count of the number Solar days since
 * noon on Monday, January 1, 4713 BC, proleptic Julian calendar
 * (November 24, 4714 BC, proleptic Gregorian calendar). It is the Julian
 * Day Number plus the fraction of the day since the preceding noon
 * in Universal Time (UT).
 */
class JulianDate
{
    public:
        /// Default constructor
        JulianDate();

        /// Copy constructor
        JulianDate(const JulianDate& aJulianDate) = default;

        /**
         * Construct from explicit year, month, day, hours, minutes and seconds and
         * UTC hour offset.
         *
         * @note Input parameters must follow the constraints for inputs
         *  to the equivalent DateAndTime class constructor.
         *
         * @param[in] aYear Year, Gregorian calendar
         * @param[in] aMonth Month of Year
         * @param[in] aDay Day of Month
         * @param[in] anHours Hours after midnight
         * @param[in] aMinutes Minutes into the hour
         * @param[in] aSeconds Seconds in the minute
         * @param[in] aUTC_OffsetHours Offset from UTC in decimal hours, e.g. -4.00
         */
        JulianDate(int aYear,
                   int aMonth,
                   int aDay,
                   int anHours,
                   int aMinutes,
                   double aSeconds,
                   double aUTC_OffsetHours = 0);

        /**
         * @brief Construct a Juliandate from a DateAndTime
         *
         * @param[in] aDateAndTime Input DateAndTime object
         */
        JulianDate(const SPA::DateAndTime& aDateAndTime);

        /**
         * Construct from decimal days since start of Julian Date epoch.
         *
         * @param[in] aDecimalDays A floating point representation of a Julian Date.
         *   For example to represent 1985-02-17 06:00:00 UTC you would input the
         *   actual JulianDate 2446113.75
         */
        JulianDate(double aDecimalDays);

        /**
         *  Copy assignment operator
         *
         *  @param[in] aJulianDate Input JulianDate to be copied.
         */
        JulianDate& operator=(const JulianDate& aJulianDate) = default;

        /**
         * @brief Compound subtraction operator for a JulianDate and a TimeDifference
         *
         * @param[in] aTimeDifference Time difference to be subtracted from the current JulianDate
         * @return A reference to a JulianDate
         */
        JulianDate& operator-=(const TimeDifference& aTimeDifference);

        /**
         * @brief Subtraction operator for a JulianDate and a TimeDifference
         *
         * @param[in] aTimeDifference Time difference to be subtracted from the current JulianDate
         * @return Output JulianDate
         */
        JulianDate operator-(const TimeDifference& aTimeDifference);

        /**
         * @brief Compound addition operator for a JulianDate and a TimeDifference
         *
         * @param[in] aTimeDifference Time difference to be added to the current JulianDate
         * @return A reference to a JulianDate
         */
        JulianDate& operator+=(const TimeDifference& aTimeDifference);

        /**
         * @brief Addition operator for a JulianDate and a TimeDifference
         *
         * @param[in] aTimeDifference Time difference to be added to the current JulianDate
         * @return Output JulianDate
         */
        JulianDate operator+(const TimeDifference& aTimeDifference);

        /// Destructor
        virtual ~JulianDate() = default;

        /**
         * Returns Julian date as 64-bit floating point decimal days since the
         *   start of the Julian Period
         *
         * @return Julian date as 64-bit floating point decimal days since the
         *   start of the Julian Period
         */
        double getDecimalDays() const
        {
            return theJulianDays;
        }

        /**
         * @brief Returns the Modified Julian Date, i.e. the
         *  Julian Date minus 2400000.5.
         *
         * @return The Modified Julian Date
         */
        double getModifiedJulianDate() const;

        /**
         * @brief Returns the DataAndTime associated with this JulianDate.
         *
         * Implements Section 5 of PAWYC. A slight difference from
         * that section is that this routine returns a full DateAndTime
         * object with hours, minutes and seconds, rather than
         * a decimal day fraction.
         *
         * @todo It is not clear if this
         *   returns a Julian calendar DateAndTime for JulianDate
         *   earlier than SPA_LAST_DAY_OF_JULIAN_CALENDAR, although
         *   this seems likely.
         *
         * @return A DateAndTime object corresponding to this
         *   JulianDate, with a zero UTC offset.
         */
        DateAndTime getDateAndTime() const;

    private:
        /**
         * @brief Converts a Date and Time into a Julian Date using the algorithm
         *  given in Section 4 of PAWYC.
         *
         * @todo Check continuity around change in Julian to Gregorian calendars.
         *
         * @param[in] aDateAndTime Input DateAndTime. If the input date is less than
         *  1582-10-15 this function assumes that the date must be in the Julian
         *  Calendar.
         * @return The julian date as a double
         */
        double convertDateAndTimeToJulianDate(const SPA::DateAndTime& aDateAndTime);

        /// Decimal days since start of Julian Date Period;
        double theJulianDays;
};


/**
 * @brief Difference operator for two JulianDates
 * @ingroup group_time
 *
 * @note Subtraction is the only arithmetic operator that makes physical
 *   sense for JulianDates.
 *
 * @param[in] aLHS_JulianDate First JulianDate that aRHS_JulianDate will be subtracted from.
 * @param[in] aRHS_JulianDate JulianDate to subtract from aLHS_JulianDate.
 * @return TimeDifference between aLHS_JulianDate and aLHS_JulianDate
 */
TimeDifference operator-(const JulianDate& aLHS_JulianDate, const JulianDate& aRHS_JulianDate);

} /* namespace SPA */

#endif /* INC_JULIANDATE_H_ */
