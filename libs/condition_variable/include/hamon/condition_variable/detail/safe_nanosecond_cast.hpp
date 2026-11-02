/**
 *	@file	safe_nanosecond_cast.hpp
 *
 *	@brief	safe_nanosecond_cast の定義
 */

#ifndef HAMON_CONDITION_VARIABLE_DETAIL_SAFE_NANOSECOND_CAST_HPP
#define HAMON_CONDITION_VARIABLE_DETAIL_SAFE_NANOSECOND_CAST_HPP

#include <hamon/chrono.hpp>
#include <hamon/limits.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_floating_point.hpp>

namespace hamon
{

namespace detail
{

template <typename Rep, typename Period, hamon::enable_if_t<hamon::is_floating_point<Rep>::value>* = nullptr>
inline chrono::nanoseconds safe_nanosecond_cast(chrono::duration<Rep, Period> d)
{
	using R = hamon::ratio_divide<Period, nano>;
	using ns_rep = chrono::nanoseconds::rep;
	Rep result_float = d.count() * R::num / R::den;

	Rep result_max = hamon::numeric_limits<ns_rep>::max();
	if (result_float >= result_max)
	{
		return chrono::nanoseconds::max();
	}

	Rep result_min = hamon::numeric_limits<ns_rep>::min();
	if (result_float <= result_min)
	{
		return chrono::nanoseconds::min();
	}

	return chrono::nanoseconds(static_cast<ns_rep>(result_float));
}

template <typename Rep, typename Period, hamon::enable_if_t<!hamon::is_floating_point<Rep>::value>* = nullptr>
inline chrono::nanoseconds safe_nanosecond_cast(chrono::duration<Rep, Period> d)
{
	if (d.count() == 0)
	{
		return chrono::nanoseconds(0);
	}

	using R = hamon::ratio_divide<Period, nano>;
	using ns_rep = chrono::nanoseconds::rep;
	ns_rep result_max = hamon::numeric_limits<ns_rep>::max();
	if (d.count() > 0 && d.count() > result_max / R::num)
	{
		return chrono::nanoseconds::max();
	}

	ns_rep result_min = hamon::numeric_limits<ns_rep>::min();
	if (d.count() < 0 && d.count() < result_min / R::num)
	{
		return chrono::nanoseconds::min();
	}

	ns_rep result = d.count() * R::num / R::den;
	if (result == 0)
	{
		return chrono::nanoseconds(1);
	}

	return chrono::nanoseconds(result);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONDITION_VARIABLE_DETAIL_SAFE_NANOSECOND_CAST_HPP
