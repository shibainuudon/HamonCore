/**
 *	@file	fp_weak_ordering.hpp
 *
 *	@brief	fp_weak_ordering の定義
 */

#ifndef HAMON_COMPARE_DETAIL_FP_WEAK_ORDERING_HPP
#define HAMON_COMPARE_DETAIL_FP_WEAK_ORDERING_HPP

#include <hamon/compare/weak_ordering.hpp>
#include <hamon/compare/partial_ordering.hpp>
#include <hamon/compare/is_lt.hpp>
#include <hamon/compare/is_gt.hpp>
#include <hamon/compare/is_eq.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
HAMON_CXX14_CONSTEXPR hamon::weak_ordering
fp_weak_ordering(T e, T f)
{
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON) && \
	!defined(_MSC_VER)
	// Returns an integer with the same sign as the argument, and magnitude
	// indicating the classification: zero=1 subnorm=2 norm=3 inf=4 nan=5
	/*auto __cat = [](T fp) -> int {
		const int __sign = __builtin_signbit(fp) ? -1 : 1;
		if (__builtin_isnormal(fp))
			return (fp == 0 ? 1 : 3) * __sign;
		if (__builtin_isnan(fp))
			return 5 * __sign;
		if (int __inf = __builtin_isinf_sign(fp))
			return 4 * __inf;
		return 2 * __sign;
	};*/

	auto po = e <=> f;

	if (hamon::is_lt(po))
	{
		return hamon::weak_ordering::less;
	}
	else if (hamon::is_gt(po))
	{
		return hamon::weak_ordering::greater;
	}
	else if (po == hamon::partial_ordering::equivalent)
	{
		return hamon::weak_ordering::equivalent;
	}
	else  // unordered, at least one argument is NaN
	{
		// return -1 for negative nan, +1 for positive nan, 0 otherwise.
		auto isnan_sign = [](T fp) -> int
		{
			return std::isnan(fp) ?
				std::signbit(fp) ? -1 : 1
				: 0;
		};

		auto ord = isnan_sign(e) <=> isnan_sign(f);

		if (hamon::is_eq(ord))
		{
			return hamon::weak_ordering::equivalent;
		}
		else if (hamon::is_lt(ord))
		{
			return hamon::weak_ordering::less;
		}
		else
		{
			return hamon::weak_ordering::greater;
		}
	}

#else

	if (e < f)
	{
		return hamon::weak_ordering::less;
	}
	else if (e > f)
	{
		return hamon::weak_ordering::greater;
	}
	else if (e == f)
	{
		return hamon::weak_ordering::equivalent;
	}
	else  // unordered, at least one argument is NaN
	{
		auto isnan_sign = [](T fp) -> int
		{
			return std::isnan(fp) ?
				std::signbit(fp) ? -1 : 1
				: 0;
		};

		auto e2 = isnan_sign(e);
		auto f2 = isnan_sign(f);
		if (e2 == f2)
		{
			return hamon::weak_ordering::equivalent;
		}
		else if (e2 < f2)
		{
			return hamon::weak_ordering::less;
		}
		else
		{
			return hamon::weak_ordering::greater;
		}
	}

#endif
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_COMPARE_DETAIL_FP_WEAK_ORDERING_HPP
