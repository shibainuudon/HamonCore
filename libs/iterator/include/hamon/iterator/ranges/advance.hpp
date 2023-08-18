/**
 *	@file	advance.hpp
 *
 *	@brief	ranges::advance 関数の実装
 */

#ifndef HAMON_ITERATOR_RANGES_ADVANCE_HPP
#define HAMON_ITERATOR_RANGES_ADVANCE_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{
namespace ranges
{

using std::ranges::advance;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/cmath/abs.hpp>
#include <hamon/concepts/assignable_from.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace detail
{

// advance(it, n) の実装

template <HAMON_CONSTRAINED_PARAM(hamon::random_access_iterator, It)>
inline HAMON_CXX14_CONSTEXPR void
advance_impl(It& it, hamon::iter_difference_t<It> n, hamon::detail::overload_priority<2>)
{
	it += n;
}

template <HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, It)>
inline HAMON_CXX14_CONSTEXPR void
advance_impl(It& it, hamon::iter_difference_t<It> n, hamon::detail::overload_priority<1>)
{
	if (n > 0)
	{
		do
		{
			++it;
		}
		while (--n);
	}
	else if (n < 0)
	{
		do
		{
			--it;
		}
		while (++n);
	}
}

template <typename It>
inline HAMON_CXX14_CONSTEXPR void
advance_impl(It& it, hamon::iter_difference_t<It> n, hamon::detail::overload_priority<0>)
{
	HAMON_ASSERT(n >= 0);
	while (n-- > 0)
	{
		++it;
	}
}

template <typename It>
inline HAMON_CXX14_CONSTEXPR void
advance_impl(It& it, hamon::iter_difference_t<It> n)
{
	advance_impl(it, n, hamon::detail::overload_priority<2>{});
}

// advance(it, bound) の実装

template <
	typename It, typename Sent,
	typename = hamon::enable_if_t<hamon::assignable_from_t<It&, Sent>::value>
>
inline HAMON_CXX14_CONSTEXPR void
advance_impl(It& it, Sent bound, hamon::detail::overload_priority<2>)
{
	it = hamon::move(bound);
}

template <typename It, HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, It, Sent)>
inline HAMON_CXX14_CONSTEXPR void
advance_impl(It& it, Sent bound, hamon::detail::overload_priority<1>)
{
	advance_impl(it, bound - it);
}

template <typename It, HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, It, Sent)>
inline HAMON_CXX14_CONSTEXPR void
advance_impl(It& it, Sent bound, hamon::detail::overload_priority<0>)
{
	while (it != bound)
	{
		++it;
	}
}

template <typename It, HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, It, Sent)>
inline HAMON_CXX14_CONSTEXPR void
advance_impl(It& it, Sent bound)
{
	advance_impl(it, bound, hamon::detail::overload_priority<2>{});
}

// advance(it, n, bound) の実装

template <
	HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, It),
	typename Sent,
	typename = hamon::enable_if_t<
		hamon::same_as_t<It, Sent>::value
	>
>
inline HAMON_CXX14_CONSTEXPR hamon::iter_difference_t<It>
advance_impl_2(It& it, hamon::iter_difference_t<It> n, Sent bound, hamon::detail::overload_priority<1>)
{
	hamon::iter_difference_t<It> m = 0;
	do
	{
		--it;
		--m;
	}
	while (m != n && it != bound);

	return n - m;
}

template <typename It, typename Sent>
inline HAMON_CXX14_CONSTEXPR hamon::iter_difference_t<It>
advance_impl_2(It& /*it*/, hamon::iter_difference_t<It> n, Sent /*bound*/, hamon::detail::overload_priority<0>)
{
	HAMON_ASSERT(n >= 0);
	return n;
}

template <typename It, HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, It, Sent)>
inline HAMON_CXX14_CONSTEXPR hamon::iter_difference_t<It>
advance_impl(It& it, hamon::iter_difference_t<It> n, Sent bound, hamon::detail::overload_priority<1>)
{
	auto const diff = bound - it;
	// n and bound must not lead in opposite directions:
	HAMON_ASSERT(n == 0 || diff == 0 || ((n < 0) == (diff < 0)));
	if (hamon::abs(n) >= hamon::abs(diff))
	{
		advance_impl(it, bound);
		return n - diff;
	}
	else
	{
		advance_impl(it, n);
		return 0;
	}
}

template <typename It, typename Sent>
inline HAMON_CXX14_CONSTEXPR hamon::iter_difference_t<It>
advance_impl(It& it, hamon::iter_difference_t<It> n, Sent bound, hamon::detail::overload_priority<0>)
{
	if (it == bound || n == 0)
	{
		return hamon::iter_difference_t<It>(0);
	}
	else if (n > 0)
	{
		hamon::iter_difference_t<It> m = 0;
		do
		{
			++it;
			++m;
		}
		while (m != n && it != bound);

		return n - m;
	}
	else
	{
		return advance_impl_2(it, n, bound, hamon::detail::overload_priority<1>{});
	}
}

template <typename It, HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, It, Sent)>
inline HAMON_CXX14_CONSTEXPR hamon::iter_difference_t<It>
advance_impl(It& it, hamon::iter_difference_t<It> n, Sent bound)
{
	return advance_impl(it, n, bound, hamon::detail::overload_priority<1>{});
}

}	// namespace detail

template <HAMON_CONSTRAINED_PARAM(hamon::input_or_output_iterator, It)>
inline HAMON_CXX14_CONSTEXPR void
advance(It& it, hamon::iter_difference_t<It> n)
{
	hamon::ranges::detail::advance_impl(it, n);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::input_or_output_iterator, It),
	HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, It, Sent)
>
inline HAMON_CXX14_CONSTEXPR void
advance(It& it, Sent bound)
{
	hamon::ranges::detail::advance_impl(it, bound);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::input_or_output_iterator, It),
	HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, It, Sent)
>
inline HAMON_CXX14_CONSTEXPR hamon::iter_difference_t<It>
advance(It& it, hamon::iter_difference_t<It> n, Sent bound)
{
	return hamon::ranges::detail::advance_impl(it, n, bound);
}

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_RANGES_ADVANCE_HPP
