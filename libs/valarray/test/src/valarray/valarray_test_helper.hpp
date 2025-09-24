/**
 *	@file	valarray_test_helper.hpp
 *
 *	@brief
 */

#ifndef HAMON_VALARRAY_TEST_HELPER_HPP
#define HAMON_VALARRAY_TEST_HELPER_HPP

#include <hamon/cmath/pow.hpp>
#include <hamon/cmath/abs.hpp>

namespace hamon_valarray_test
{

inline HAMON_CXX20_CONSTEXPR bool
is_about(double x, double y, int significant_digits)
{
	double epsilon = hamon::pow(1.0 / 10.0, significant_digits);
	return hamon::abs(x - y) < epsilon;
}

}	// namespace hamon_valarray_test

#endif // HAMON_VALARRAY_TEST_HELPER_HPP
