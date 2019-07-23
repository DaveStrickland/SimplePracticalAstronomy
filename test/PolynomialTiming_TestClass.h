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
 * @file PolynomialTiming_TestClass.h
 * @brief Declaration of PolynomialTiming_TestClass
 *
 * @ingroup group_test
 *
 * @author Dave Strickland, <dave.strickland@gmail.com>
 *
 * @version Aug 27, 2018 dks : Initial coding
 */

#ifndef TEST_POLYNOMIALTIMING_TESTCLASS_H_
#define TEST_POLYNOMIALTIMING_TESTCLASS_H_

#include <cute/cute.h>
#include <string>
#include <functional>


namespace SPA { namespace TEST
{

/**
 * @brief A timing test for various possible forms of polynomial evaluation
 *
 * @ingroup group_test
 *
 * Results: On a VirtualBox Fedora 28 Intel i5, the following results were
 * obtained for the first run of each function. Similar results were obtained
 * when run a second time in a different order.
 *
 * method: SimpleThreeCoeff       1.000e+07 tests, 0.089736 s, 0.008974 us/test, final value=3.3843e+10
 * method: ZeroThreeCoeff         1.000e+07 tests, 0.100192 s, 0.010019 us/test, final value=3.3843e+10
 * method: PowThreeCoeff          1.000e+07 tests, 0.083776 s, 0.008378 us/test, final value=3.3843e+10
 * method: SimpleSixCoeff         1.000e+07 tests, 0.115722 s, 0.011572 us/test, final value=1.6869e+16
 * method: PowSixCoeff            1.000e+07 tests, 5.213849 s, 0.521385 us/test, final value=1.6869e+16
 * method: LoopPowSixCoeff        1.000e+07 tests, 5.325249 s, 0.532525 us/test, final value=1.6869e+16
 * method: ZeroLoopSimpleSixCoeff 1.000e+07 tests, 0.221260 s, 0.022126 us/test, final value=1.6869e+16
 * method: LoopSimpleSixCoeff     1.000e+07 tests, 0.191932 s, 0.019193 us/test, final value=1.6869e+16
 * method: NumRecSixCoeff         1.000e+07 tests, 0.116697 s, 0.011670 us/test, final value=1.6869e+16
 * method: NumRecLoopSixCoeff     1.000e+07 tests, 0.165862 s, 0.016586 us/test, final value=1.6869e+16
 *
 * For known, hard-wired, polynomial size:
 * SimpleSixCoeff OR NumRecSixCoeff are the fastest, and equally good.
 *
 * For an arbitrary length polynomial a loop is needed:
 * In this case NumRecLoopSixCoeff is 25% faster than LoopSimpleSizeCoeff, but both are
 * noticeably slower than a hand-optimized solution for a fixed size polynomial.
 *
 * For polynomials with some coefficients equal to zero:
 * The cost of finding and ignoring the zero coefficients is slightly larger than the
 * cost of performing any unneeded multiplications if we dont ignore them. In other
 * words, the cost of an 'if' is greater than the cost of a multiplication.
 *
 * The use of pow(), even with simple integral type powers, is discouraged given
 * its extreme cost.
 */
class PolynomialTiming_TestClass
{
    public:
        /// Default constructor.
        PolynomialTiming_TestClass(){};

        /// Default destructor.
        virtual ~PolynomialTiming_TestClass(){};

        /**
         * Runs a series of test function that evaluate 3-or-6 coefficient
         * polynomials in a number of different ways.
         *
         * Reports results to standard output.
         */
        void testTiming();

        /**
          * Adds all methods that run this class's unit tests to the given cute suite.
          *
          * @param[in,out] aSuite The cute suite that the tests will be added to.
          */
         static void makeTestSuite(cute::suite& aSuite)
         {
            aSuite += CUTE_SMEMFUN(PolynomialTiming_TestClass, testTiming);
         }

    private:
         /**
          * This function runs an input polynomial test function aNumTests times,
          * using aCoeff to calulate a unique input value for each test.
          *
          * In an earlier version where aCoeff was not a variable, rerunning
          * some of these functions a second time would result in zero time
          * spent. I believe the compiler was detecting that nothing had changed
          * and optimized the call away.
          *
          * @param[in] aNumTests
          * @param[in] aCoeff Input value to be passed for polynomial evaluation.
          *   Can be any value for the purposes of timing testing.
          * @param[in] aFuncPtr Function pointer to the polynomial evaluation
          *   function under test.
          * @return Accumulated value from summing the polynomial aNumTests times.
          *   Used to trick compiler into believer value is used.
          */
         double runTestLoop(const int aNumTests,
                            const double aCoeff,
                            std::function<double(const double)> aFuncPtr);

         /**
          * Helper function to format and print the timing results.
          *
          * @param[in] aTestName Name of the test.
          * @param[in] aTimeSeconds Total time spent running the function aNumTests times.
          * @param[in] aNumTests Number of times the test was run.
          * @param[in] aTestValue Final value of returned by the test,
          *   primarily useful for a by-eye check that tests of the same
          *   type of polynomial give the same answer.
          */
         void printResult(const std::string& aTestName,
                          double aTimeSeconds,
                          const int aNumTests,
                          double aTestValue);
};

} // end namespace TEST
} // end namespace SPA

#endif /* TEST_POLYNOMIALTIMING_TESTCLASS_H_ */
