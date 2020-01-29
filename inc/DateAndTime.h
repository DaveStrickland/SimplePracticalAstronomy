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
 * @file DateAndTime.h
 * @brief Declaration of the DateAndTime class.
 * @ingroup group_time
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Sep 1, 2018 dks : Initial coding 
 */

#ifndef INC_DATEANDTIME_H_
#define INC_DATEANDTIME_H_

#include <iostream>
#include <iomanip>

namespace SPA
{

/**
 * @brief A simple date and time class
 * @ingroup group_time
 *
 * @note This is a deliberately simple class that is not intended
 *  to have all the functionality of the python datetime or
 *  boost datetime classes. In particular it is not calendar
 *  aware and makes no distinction between Gregorian and
 *  Julian calendars.
 * @note It is difficult to create a useful date class without
 *  tying it to a time class, and vice versa, when time zones
 *  are considered.
 * @note I have not decided on what to do when construction with
 *   invalid inputs is attempted. Options would be to throw, to
 *   not throw but construct a magic value ("not a valid date"), clip
 *   to an allowed range (but without alerting the user to the fact
 *   that they have a problem), or have a flag that
 *   denotes whether the DataAndTime is valid (but that the user has
 *   to check).
 *
 */
class DateAndTime
{
    public:
        /// Default constructor
        DateAndTime();

        /**
         * Construct from explicit year, month, day, hours, minutes and seconds and
         * UTC hour offset.
         *
         * @param[in] aYear Year.
         *   No constraints on input values.
         * @param[in] aMonth Month of Year.
         *   Allowed input value in range 1..12 inclusive.
         * @param[in] aDay Day of Month.
         *   Allowed input value in range 0..31 inclusive.
         *   Zero is allowed as some calculations use January zero.
         * @param[in] anHours Hours after midnight in a 24-hour clock.
         *   Allowed input value in range 0..23 inclusive.
         * @param[in] aMinutes Minutes into the hour.
         *   Allowed input value in range 0..59 inclusive.
         * @param[in] aSeconds Seconds in the minute.
         *   Allowed input value in range 0..60 inclusive.
         *   Sixty is allowed as technically a minute with a leap second has
         *   sixty one seconds in it.
         * @param[in] aUTC_OffsetHours Offset from UTC in decimal hours, e.g. -4.00.
         *   Allowed input value in range -12.0..12.0 inclusive.
         */
        DateAndTime(int aYear,
                    int aMonth,
                    int aDay,
                    int anHours = 0,
                    int aMinutes = 0,
                    double aSeconds = 0,
                    double aUTC_OffsetHours = 0);

        /// Default destructor
        virtual ~DateAndTime() = default;

        /// Friend equality operator
        friend bool operator==(const DateAndTime& aLHS, const DateAndTime& aRHS);

        /// Friend less than operator
        friend bool operator<(const DateAndTime& aLHS, const DateAndTime& aRHS);

        /**
         * Returns the day of the month
         * @return Returns the day of the month
         */
        int getDay() const
        {
            return theDay;
        }

        /**
         * Returns the hour within the day
         * @return Returns the hour within the day based on
         *  a 24-hour clock.
         */
        int getHours() const
        {
            return theHours;
        }

        /**
         * Returns the minutes within the hour
         * @return Returns the minutes within the hour
         */
        int getMinutes() const
        {
            return theMinutes;
        }

        /**
         * Returns the month within the year
         * @return Returns the month within the year
         */
        int getMonth() const
        {
            return theMonth;
        }

        /**
         * Returns the decimal seconds within the minutes
         * @return Returns the decimal seconds within the minutes
         */
        double getSeconds() const
        {
            return theSeconds;
        }

        /**
         * Returns the time zone offset from UTC in decimal hours
         * @return Returns the time zone offset from UTC in decimal hours
         */
        double getUtcOffsetHours() const
        {
            return theUTC_OffsetHours;
        }

        /**
         * Returns the year
         * @return Returns the year
         */
        int getYear() const
        {
            return theYear;
        }

        /**
         * Sets the day
         * @param[in] aDay Input day value to use
         */
        void setDay(int aDay);

        /**
         * Sets the hours in the day
         * @param[in] anHours Input hours (24 hour clock)
         */
        void setHours(int anHours);

        /**
         * Sets the minutes in the hour
         * @param aMinutes Minutes in the hour
         */
        void setMinutes(int aMinutes);

        /**
         * Sets the month in the year.
         * @param[in] aMonth Input month
         */
        void setMonth(int aMonth);

        /**
         * Sets the seconds in the minute.
         * @param[in] aSeconds Input seconds in the minute
         */
        void setSeconds(double aSeconds);

        /**
         * Sets the offset from UTC.
         * @param[in] aUTC_OffsetHours Offset from UTC in decimal hours
         */
        void setUtcOffsetHours(double aUTC_OffsetHours);

        /**
         * Sets the year.
         * @note Currently B.C. ("Before Christ') and the less offensive
         *   B.C.E ("Before Common Era") years should be handled carefully
         *   because there is no year zero. Given a BC or BCE date use
         *   convertBCE_Year() before passing a year into
         *   DateAndTime.
         * @param[in] aYear Input year
         */
        void setYear(int aYear);

        /**
         * Returns the time within the current day as a fraction of a day from UT 00:00:00
         * on that day.
         *
         * Examples:
         * \li For a UTC correction of 0.00 hours at 08:00:00 local the day fraction is 0.333333
         * \li For a UTC correction of -12.00 hours at 06:00:00 local the day fraction is -0.25,
         *   i.e. its technically the previous day.
         *
         * @return The decimal day fraction with respect to UTC.
         */
        double getDayFraction() const;

    private:
        /// The year
        int theYear;

        /// The month
        int theMonth;

        /// Day within the month
        int theDay;

        /// Hour within the day
        int theHours;

        /// Minutes in the hour
        int theMinutes;

        /// Seconds in the minute
        double theSeconds;

        /// Offset from UTC in decimal hours
        double theUTC_OffsetHours;
};

/**
 * @brief Equality operator for DateAndTime class.
 * @ingroup group_time
 *
 * @limitations Even floating point members must be binary
 *   identical.
 *
 * @param[in] aLHS First input DateAndTime instance.
 * @param[in] aRHS Second input DateAndTime instance.
 * @return True if all data elements of aLHS and aRHS are binary equal.
 */
bool operator==(const DateAndTime& aLHS,
                const DateAndTime& aRHS);

/**
 * @brief Less than operator for DateAndTime class.
 * @ingroup group_time
 *
 * Years are directly compared, and within a year the
 * date and time is converted to decimal days since the start
 * of the year in UTC.
 *
 * @limitations There is the possibility of edge cases where UTC
 *   time zone corrections push the true date into the preceding
 *   or following year. This are not caught as yet.
 *
 * @param[in] aLHS First input DateAndTime instance.
 * @param[in] aRHS Second input DateAndTime instance.
 * @return True if aLHS is less than aRHS
 */
bool operator<(const DateAndTime& aLHS,
               const DateAndTime& aRHS);

/**
 * @brief Inequality operator for DateAndTime.
 * @ingroup group_time
 *
 * @param[in] aLHS First input DateAndTime instance.
 * @param[in] aRHS Second input DateAndTime instance.
 * @return True if aLHS is not equal to aRHS
 */
inline bool operator!=(const DateAndTime& aLHS,
                const DateAndTime& aRHS)
{
    return !operator==(aLHS, aRHS);
}

/**
 * @brief Greater than operator for DateAndTime.
 * @ingroup group_time
 *
 * @param[in] aLHS First input DateAndTime instance.
 * @param[in] aRHS Second input DateAndTime instance.
 * @return True if aLHS is greater than aRHS
 */
inline bool operator>(const DateAndTime& aLHS,
                      const DateAndTime& aRHS)
{
    return operator<(aRHS, aLHS);
}

/**
 * @brief Less than or equal to operator for DateAndTime.
 * @ingroup group_time
 *
 * @param[in] aLHS First input DateAndTime instance.
 * @param[in] aRHS Second input DateAndTime instance.
 * @return True if aLHS is less than or equal to aRHS
 */
inline bool operator<=(const DateAndTime& aLHS,
                       const DateAndTime& aRHS)
{
    return !operator>(aLHS, aRHS);
}

/**
 * @brief Greater than or equal to operator for DateAndTime.
 * @ingroup group_time
 *
 * @param[in] aLHS First input DateAndTime instance.
 * @param[in] aRHS Second input DateAndTime instance.
 * @return True if aLHS is greater than or equal to aRHS
 */
inline bool operator>=(const DateAndTime& aLHS,
                       const DateAndTime& aRHS)
{
    return !operator<(aLHS, aRHS);
}

} /* namespace SPA */

/**
 * @brief Ostream operator for DateAndTime class.
 * @ingroup group_time
 *
 * @param[in,out] os Output stream to modify
 * @param aDateAndTime DataAndTime object to serialize to stream
 * @return Stream representation of the DataAndTime object
 */
std::ostream& operator<<(std::ostream& os,
                         const SPA::DateAndTime& aDateAndTime);

#endif /* INC_DATEANDTIME_H_ */
