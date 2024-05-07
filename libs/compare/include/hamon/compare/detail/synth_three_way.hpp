/**
 *	@file	synth_three_way.hpp
 *
 *	@brief	synth_three_way の定義
 */

#ifndef HAMON_COMPARE_DETAIL_SYNTH_THREE_WAY_HPP
#define HAMON_COMPARE_DETAIL_SYNTH_THREE_WAY_HPP

#include <hamon/compare/concepts/three_way_comparable_with.hpp>
#include <hamon/compare/weak_ordering.hpp>
#include <hamon/concepts/detail/boolean_testable.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

// 16.4.2.1 Exposition-only functions[expos.only.func]

struct synth_three_way_fn
{
private:
	template <typename T, typename U>
	static HAMON_CONSTEXPR bool
	s_noexcept(T const* t = nullptr, U const* u = nullptr)
	{
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		if constexpr (hamon::three_way_comparable_with<T, U>)
		{
			return noexcept(*t <=> *u);
		}
#endif
		return noexcept(*t < *u) && noexcept(*u < *t);
	}

public:
	template <typename T, typename U>
	HAMON_CXX14_CONSTEXPR
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	auto
#else
	hamon::weak_ordering
#endif
	operator()(T const& t, U const& u) const
		HAMON_NOEXCEPT_IF((s_noexcept<T, U>()))
#if defined(HAMON_HAS_CXX20_CONCEPTS)
		requires requires
		{
			{ t < u } -> hamon::detail::boolean_testable;
			{ u < t } -> hamon::detail::boolean_testable;
		}
#endif
	{
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		if constexpr (hamon::three_way_comparable_with<T, U>)
		{
			return t <=> u;
		}
		else
#endif
		{
			if (t < u)
			{
				return hamon::weak_ordering::less;
			}
			else if (u < t)
			{
				return hamon::weak_ordering::greater;
			}
			else
			{
				return hamon::weak_ordering::equivalent;
			}
		}
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
synth_three_way_fn synth_three_way{};

}	// inline namespace cpo

template <typename T, typename U = T>
using synth_three_way_result =
	decltype(hamon::detail::synth_three_way(hamon::declval<T&>(), hamon::declval<U&>()));

}	// namespace detail

}	// namespace hamon

#endif // HAMON_COMPARE_DETAIL_SYNTH_THREE_WAY_HPP
