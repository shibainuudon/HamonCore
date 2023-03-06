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
#include <hamon/concepts/assignable_from.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/conjunction.hpp>
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

template <HAMON_CONSTRAINED_PARAM(hamon::random_access_iterator, It)>
inline HAMON_CXX14_CONSTEXPR void
advance_impl_1(hamon::detail::overload_priority<2>, It& it, hamon::iter_difference_t<It> n)
{
	it += n;
}

template <HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, It)>
inline HAMON_CXX14_CONSTEXPR void
advance_impl_1(hamon::detail::overload_priority<1>, It& it, hamon::iter_difference_t<It> n)
{
	if (n > 0)
	{
		do
		{
			++it;
		} while (--n);
	}
	else if (n < 0)
	{
		do
		{
			--it;
		} while (++n);
	}
}

template <typename It>
inline HAMON_CXX14_CONSTEXPR void
advance_impl_1(hamon::detail::overload_priority<0>, It& it, hamon::iter_difference_t<It> n)
{
	HAMON_ASSERT(n >= 0);
	while (n-- > 0)
	{
		++it;
	}
}

}	// namespace detail

template <HAMON_CONSTRAINED_PARAM(hamon::input_or_output_iterator, It)>
inline HAMON_CXX14_CONSTEXPR void
advance(It& it, hamon::iter_difference_t<It> n)
{
	ranges::detail::advance_impl_1(hamon::detail::overload_priority<2>{}, it, n);
}

namespace detail
{

template <
	typename It, typename Sent
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	, typename = hamon::enable_if_t<hamon::assignable_from<It&, Sent>::value>
#endif
>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
requires hamon::assignable_from<It&, Sent>
#endif
inline HAMON_CXX14_CONSTEXPR void
advance_impl_2(hamon::detail::overload_priority<2>, It& it, Sent bound)
{
	it = hamon::move(bound);
}

template <
	typename It,
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::sized_sentinel_for<It> Sent
#else
	typename Sent,
	typename = hamon::enable_if_t<hamon::sized_sentinel_for<Sent, It>::value>
#endif
>
inline HAMON_CXX14_CONSTEXPR void
advance_impl_2(hamon::detail::overload_priority<1>, It& it, Sent bound)
{
	ranges::advance(it, bound - it);
}

template <typename It, typename Sent>
inline HAMON_CXX14_CONSTEXPR void
advance_impl_2(hamon::detail::overload_priority<0>, It& it, Sent bound)
{
	while (it != bound)
	{
		++it;
	}
}

}	// namespace detail

template <
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::input_or_output_iterator It, hamon::sentinel_for<It> Sent
#else
	typename It, typename Sent,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::input_or_output_iterator<It>,
		hamon::sentinel_for<Sent, It>
	>::value>
#endif
>
inline HAMON_CXX14_CONSTEXPR void
advance(It& it, Sent bound)
{
	ranges::detail::advance_impl_2(hamon::detail::overload_priority<2>{}, it, bound);
}

namespace detail
{

template <
	typename It, typename Difference,
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::sized_sentinel_for<It> Sent
#else
	typename Sent,
	typename = hamon::enable_if_t<hamon::sized_sentinel_for<Sent, It>::value>
#endif
>
inline HAMON_CXX14_CONSTEXPR Difference
advance_impl_3(hamon::detail::overload_priority<1>, It& it, Difference n, Sent bound)
{
	const auto diff = bound - it;
	// n and bound must not lead in opposite directions:
	HAMON_ASSERT(n == 0 || diff == 0 || ((n < 0) == (diff < 0)));
	const auto absdiff = diff < 0 ? -diff : diff;
	const auto absn = n < 0 ? -n : n;;
	if (absn >= absdiff)
	{
		ranges::advance(it, bound);
		return n - diff;
	}
	else
	{
		ranges::advance(it, n);
		return 0;
	}
}

template <
	typename It, typename Difference, typename Sent
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	, typename = hamon::enable_if_t<
		hamon::bidirectional_iterator<It>::value &&
		hamon::same_as<It, Sent>::value
	>
#endif
>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
requires hamon::bidirectional_iterator<It> && hamon::same_as<It, Sent>
#endif
inline HAMON_CXX14_CONSTEXPR Difference
advance_impl_4(hamon::detail::overload_priority<1>, It& it, Difference n, Sent bound)
{
	hamon::iter_difference_t<It> m = 0;
	do
	{
		--it;
		--m;
	} while (m != n && it != bound);

	return n - m;
}

template <typename It, typename Difference, typename Sent>
inline HAMON_CXX14_CONSTEXPR Difference
advance_impl_4(hamon::detail::overload_priority<0>, It& /*it*/, Difference n, Sent /*bound*/)
{
	HAMON_ASSERT(n >= 0);
	return n;
}

template <typename It, typename Difference, typename Sent>
inline HAMON_CXX14_CONSTEXPR Difference
advance_impl_3(hamon::detail::overload_priority<0>, It& it, Difference n, Sent bound)
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
		} while (m != n && it != bound);

		return n - m;
	}
	else
	{
		return advance_impl_4(
			hamon::detail::overload_priority<1>{}, it, n, bound);
	}
}

}	// namespace detail

template <
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::input_or_output_iterator It, hamon::sentinel_for<It> Sent
#else
	typename It, typename Sent,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::input_or_output_iterator<It>,
		hamon::sentinel_for<Sent, It>
	>::value>
#endif
>
inline HAMON_CXX14_CONSTEXPR hamon::iter_difference_t<It>
advance(It& it, hamon::iter_difference_t<It> n, Sent bound)
{
	return ranges::detail::advance_impl_3(
		hamon::detail::overload_priority<1>{}, it, n, bound);
}

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_RANGES_ADVANCE_HPP
