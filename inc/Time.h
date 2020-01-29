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
 * @file Time.h
 * @brief Declaration of the Time class.
 * @ingroup group_time
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Jan 28, 2020 dks : Initial coding 
 */

#ifndef INC_TIME_H_
#define INC_TIME_H_

#include <iostream>
#include <iomanip>

namespace SPA
{

/**
 * @brief A simple time class
 * @ingroup group_time
 *
 * @note This is a deliberately simple class that is not intended
 *  to have all the functionality of the python datetime or
 *  boost datetime classes. It has only a very simplistic treatment of
 *  time zones.
 */
class Time
{
    public:
        /// Default constructor
        Time();

        /**
         * Construct from explicit hours, minutes and seconds and
         * UTC hour offset.
         *
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
        Time(int anHours = 0,
             int aMinutes = 0,
             double aSeconds = 0,
             double aUTC_OffsetHours = 0);

        /// Default destructor
        virtual ~Time() = default;

        /// Friend equality operator
        friend bool operator==(const Time& aLHS, const Time& aRHS);

        /// Friend less than operator
        friend bool operator<(const Time& aLHS, const Time& aRHS);

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
 * @brief Equality operator for Time class.
 * @ingroup group_time
 *
 * @limitations Even floating point members must be binary
 *   identical.
 *
 * @param[in] aLHS First input Time instance.
 * @param[in] aRHS Second input Time instance.
 * @return True if all data elements of aLHS and aRHS are binary equal.
 */
bool operator==(const Time& aLHS,
                const Time& aRHS);

/**
 * @brief Less than operator for Time class.
 * @ingroup group_time
 *
 * The fractional decimal days since 00:00:00 UTC are compared.
 *
 * @limitations There is the possibility of edge cases where UTC
 *   corrections and/or the floating point conversions to decimal
 *   days cause issues. These have not been tested for or corrected yet.
 *
 * @param[in] aLHS First input Time instance.
 * @param[in] aRHS Second input Time instance.
 * @return True if aLHS is less than aRHS
 */
bool operator<(const Time& aLHS,
               const Time& aRHS);

/**
 * @brief Inequality operator for Time.
 * @ingroup group_time
 *
 * @param[in] aLHS First input Time instance.
 * @param[in] aRHS Second input Time instance.
 * @return True if aLHS is not equal to aRHS
 */
inline bool operator!=(const Time& aLHS,
                       const Time& aRHS)
{
    return !operator==(aLHS, aRHS);
}

/**
 * @brief Greater than operator for Time.
 * @ingroup group_time
 *
 * @param[in] aLHS First input Time instance.
 * @param[in] aRHS Second input Time instance.
 * @return True if aLHS is greater than aRHS
 */
inline bool operator>(const Time& aLHS,
                      const Time& aRHS)
{
    return operator<(aRHS, aLHS);
}

/**
 * @brief Less than or equal to operator for Time.
 * @ingroup group_time
 *
 * @param[in] aLHS First input Time instance.
 * @param[in] aRHS Second input Time instance.
 * @return True if aLHS is less than or equal to aRHS
 */
inline bool operator<=(const Time& aLHS,
                       const Time& aRHS)
{
    return !operator>(aLHS, aRHS);
}

/**
 * @brief Greater than or equal to operator for Time.
 * @ingroup group_time
 *
 * @param[in] aLHS First input Time instance.
 * @param[in] aRHS Second input Time instance.
 * @return True if aLHS is greater than or equal to aRHS
 */
inline bool operator>=(const Time& aLHS,
                       const Time& aRHS)
{
    return !operator<(aLHS, aRHS);
}

} /* namespace SPA */

/**
 * @brief Ostream operator for Time class.
 * @ingroup group_time
 *
 * @param[in,out] os Output stream to modify
 * @param aTime Time object to serialize to stream
 * @return Stream representation of the DataAndTime object
 */
std::ostream& operator<<(std::ostream& os,
                         const SPA::Time& aTime);

#endif /* INC_TIME_H_ */
