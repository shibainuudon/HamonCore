/**
 *	@file	complex_test_utility.hpp
 *
 *	@brief
 */

#ifndef UNIT_TEST_COMPLEX_COMPLEX_TEST_UTILITY_HPP
#define UNIT_TEST_COMPLEX_COMPLEX_TEST_UTILITY_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/cmath/signbit.hpp>

namespace
{

template <typename T>
HAMON_CXX11_CONSTEXPR bool
complex_near_sub(T expected, T x, double error)
{
	return hamon::isnan(expected) ? hamon::isnan(x) :
		hamon::isinf(expected) ? (expected == x) :
		(hamon::fabs(expected - x) <= error);
}

template <typename T>
HAMON_CXX11_CONSTEXPR bool
complex_near(hamon::complex<T> const& expected, hamon::complex<T> const& x, double error)
{
	return
		complex_near_sub(expected.real(), x.real(), error) &&
		complex_near_sub(expected.imag(), x.imag(), error);
}

template <typename T>
HAMON_CXX11_CONSTEXPR bool
complex_eq_sub(T expected, T x)
{
	return hamon::isnan(expected) ? hamon::isnan(x) :
		hamon::iszero(expected) ? hamon::iszero(x) && (hamon::signbit(expected) == hamon::signbit(x)) :
		(expected == x);
}

template <typename T>
HAMON_CXX11_CONSTEXPR bool
complex_eq(hamon::complex<T> const& expected, hamon::complex<T> const& x)
{
	return
		complex_eq_sub(expected.real(), x.real()) &&
		complex_eq_sub(expected.imag(), x.imag());
}

}	// namespace

#endif // UNIT_TEST_COMPLEX_COMPLEX_TEST_UTILITY_HPP
