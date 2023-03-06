/**
 *	@file	reverse.hpp
 *
 *	@brief	ranges::reverse の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_REVERSE_HPP
#define HAMON_ALGORITHM_RANGES_REVERSE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::reverse;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/permutable.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

struct reverse_fn
{
private:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::random_access_iterator, Iter),
		typename Sent
	>
	static HAMON_CXX14_CONSTEXPR Iter
	impl(Iter first, Sent last,
		hamon::detail::overload_priority<1>)
	{
		auto i = ranges::next(first, last);
		auto tail = i;

		if (first != last)
		{
			--tail;
			while (first < tail)
			{
				ranges::iter_swap(first, tail);
				++first;
				--tail;
			}
		}

		return i;
	}

	template <typename Iter, typename Sent>
	static HAMON_CXX14_CONSTEXPR Iter
	impl(Iter first, Sent last,
		hamon::detail::overload_priority<0>)
	{
		auto i = ranges::next(first, last);
		auto tail = i;

		for (;;)
		{
			if (first == tail || first == --tail)
			{
				break;
			}
			else
			{
				ranges::iter_swap(first, tail);
				++first;
			}
		}

		return i;
	}

public:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Iter first, Sent last) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		Iter, hamon::permutable<Iter>)
	{
		return impl(
			hamon::move(first),
			hamon::move(last),
			hamon::detail::overload_priority<1>{});
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::bidirectional_range, Range)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		hamon::ranges::borrowed_iterator_t<Range>,
		hamon::permutable<ranges::iterator_t<Range>>)
	{
		return (*this)(ranges::begin(r), ranges::end(r));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR reverse_fn reverse{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_REVERSE_HPP
