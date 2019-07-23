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
 * @file TimeDifference_TestClass.h
 * @brief Contains the CUTE test class for the TimeDifference class.
 * @ingroup group_test
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Sep 22, 2018 dks : Initial coding 
 */

#ifndef TEST_TIMEDIFFERENCE_TESTCLASS_H_
#define TEST_TIMEDIFFERENCE_TESTCLASS_H_

#include <cute/cute.h>

namespace SPA
{
namespace TEST
{

/**
 * @brief Declares the CUTE test class for the TimeDifference class.
 * @ingroup group_test
 */
class TimeDifference_TestClass
{
    public:
        /// Constructor.
        TimeDifference_TestClass() = default;

        /// Destructor.
        virtual ~TimeDifference_TestClass() = default;

        /// Test constructors.
        void testConstructors();

        /// Test setters.
        void testSetters();

        /**
         * Adds all methods that run this class's unit tests to the given cute suite.
         *
         * @param[in,out] aSuite The cute suite that the tests will be added to.
         */
        static void makeTestSuite(cute::suite& aSuite)
        {
            aSuite += CUTE_SMEMFUN(TimeDifference_TestClass, testConstructors);
            aSuite += CUTE_SMEMFUN(TimeDifference_TestClass, testSetters);
        }
};

} /* namespace TEST */
} /* namespace SPA */

#endif /* TEST_TIMEDIFFERENCE_TESTCLASS_H_ */
