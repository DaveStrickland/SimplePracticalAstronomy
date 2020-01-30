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
 * @file SpaDate.h
 * @brief Declaration of the SpaDate class.
 * @ingroup group_time
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Jan 28, 2020 dks : Initial coding 
 */

#ifndef INC_SPADATE_H_
#define INC_SPADATE_H_

#include <iostream>
#include <iomanip>

namespace SPA
{

/**
 * @brief A simple date class
 * @ingroup group_time
 * 
 * This is an explicity European calendar.
 *
 * @note This is a deliberately simple class that is not intended
 *  to have all the functionality of the python datetime or
 *  boost datetime classes. In particular it is not calendar
 *  aware and makes no distinction between Gregorian and
 *  Julian calendars.
 * @note It is difficult to create a useful date class without
 *  tying it to a time class, and vice versa, when time zones
 *  are considered.
 */
class SpaDate
{
    public:
        /// Default constructor
        SpaDate();

        /**
         * Construct from explicit year, month, day.
         *
         * @param[in] aYear Year.
         *   No constraints on input values.
         * @param[in] aMonth Month of Year.
         *   Allowed input value in range 1..12 inclusive.
         * @param[in] aDay Day of Month.
         *   Allowed input value in range 0..31 inclusive.
         *   Zero is allowed as some calculations use January zero.
         */
        SpaDate(int aYear,
             int aMonth,
             int aDay);

        /// Default destructor
        virtual ~SpaDate() = default;

        /// Friend equality operator
        friend bool operator==(const SpaDate& aLHS, const SpaDate& aRHS);

        /// Friend less than operator
        friend bool operator<(const SpaDate& aLHS, const SpaDate& aRHS);

        /**
         * Returns the day of the month
         * @return Returns the day of the month
         */
        int getDay() const
        {
            return theDay;
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
         * Sets the month in the year.
         * @param[in] aMonth Input month
         */
        void setMonth(int aMonth);

        /**
         * Sets the year.
         * @note Currently B.C. ("Before Christ') and the less offensive
         *   B.C.E ("Before Common Era") years should be handled carefully
         *   because there is no year zero. Given a BC or BCE date use
         *   convertBCE_Year() before passing a year into
         *   SpaDate.
         * @param[in] aYear Input year
         */
        void setYear(int aYear);

    private:
        /// The year
        int theYear;

        /// The month
        int theMonth;

        /// Day within the month
        int theDay;
};

/**
 * @brief Equality operator for SpaDate class.
 * @ingroup group_time
 *
 * @limitations Even floating point members must be binary
 *   identical.
 *
 * @param[in] aLHS First input SpaDate instance.
 * @param[in] aRHS Second input SpaDate instance.
 * @return True if all data elements of aLHS and aRHS are binary equal.
 */
bool operator==(const SpaDate& aLHS,
                const SpaDate& aRHS);

/**
 * @brief Less than operator for SpaDate class.
 * @ingroup group_time
 *
 * @param[in] aLHS First input SpaDate instance.
 * @param[in] aRHS Second input SpaDate instance.
 * @return True if aLHS is less than aRHS
 */
bool operator<(const SpaDate& aLHS,
               const SpaDate& aRHS);

/**
 * @brief Inequality operator for SpaDate.
 * @ingroup group_time
 *
 * @param[in] aLHS First input SpaDate instance.
 * @param[in] aRHS Second input SpaDate instance.
 * @return True if aLHS is not equal to aRHS
 */
inline bool operator!=(const SpaDate& aLHS,
                const SpaDate& aRHS)
{
    return !operator==(aLHS, aRHS);
}

/**
 * @brief Greater than operator for SpaDate.
 * @ingroup group_time
 *
 * @param[in] aLHS First input SpaDate instance.
 * @param[in] aRHS Second input SpaDate instance.
 * @return True if aLHS is greater than aRHS
 */
inline bool operator>(const SpaDate& aLHS,
                      const SpaDate& aRHS)
{
    return operator<(aRHS, aLHS);
}

/**
 * @brief Less than or equal to operator for SpaDate.
 * @ingroup group_time
 *
 * @param[in] aLHS First input SpaDate instance.
 * @param[in] aRHS Second input SpaDate instance.
 * @return True if aLHS is less than or equal to aRHS
 */
inline bool operator<=(const SpaDate& aLHS,
                       const SpaDate& aRHS)
{
    return !operator>(aLHS, aRHS);
}

/**
 * @brief Greater than or equal to operator for SpaDate.
 * @ingroup group_time
 *
 * @param[in] aLHS First input SpaDate instance.
 * @param[in] aRHS Second input SpaDate instance.
 * @return True if aLHS is greater than or equal to aRHS
 */
inline bool operator>=(const SpaDate& aLHS,
                       const SpaDate& aRHS)
{
    return !operator<(aLHS, aRHS);
}

} /* namespace SPA */

/**
 * @brief Ostream operator for SpaDate class.
 * @ingroup group_time
 *
 * @param[in,out] os Output stream to modify
 * @param aSpaDate Data object to serialize to stream
 * @return Stream representation of the DataAndTime object
 */
std::ostream& operator<<(std::ostream& os,
                         const SPA::SpaDate& aSpaDate);

#endif /* INC_SPADATE_H_ */
