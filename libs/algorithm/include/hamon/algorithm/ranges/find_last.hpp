/**
 *	@file	find_last.hpp
 *
 *	@brief	ranges::find_last の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_FIND_LAST_HPP
#define HAMON_ALGORITHM_RANGES_FIND_LAST_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) &&	\
	defined(__cpp_lib_ranges_find_last) && (__cpp_lib_ranges_find_last >= 202207L)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::find_last;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/find.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirect_binary_predicate.hpp>
#include <hamon/iterator/ranges/prev.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/borrowed_subrange_t.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

struct find_last_fn
{
private:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::same_as, Iter, Sent),
		typename T,
		typename Proj
	>
	HAMON_CXX14_CONSTEXPR ranges::subrange<Iter> impl(
		Iter first, Sent last, T const& value, Proj proj,
		hamon::detail::overload_priority<1>) const
	{
		Iter found = ranges::find(
			hamon::reverse_iterator<Iter>{last},
			hamon::reverse_iterator<Iter>{first},
			value, hamon::move(proj)).base();

		if (found == first)
		{
			return { last, last };
		}
		else
		{
			return { ranges::prev(found), last };
		}
	}

	template <typename Iter, typename Sent, typename T, typename Proj>
	HAMON_CXX14_CONSTEXPR ranges::subrange<Iter> impl(
		Iter first, Sent last, T const& value, Proj proj,
		hamon::detail::overload_priority<0>) const
	{
		Iter found = ranges::find(first, last, value, proj);
		if (found == last)
		{
			return { found, found };
		}

		first = found;
			
		for (;;)
		{
			first = ranges::find(ranges::next(first), last, value, proj);
			if (first == last)
			{
				return { found, first };
			}

			found = first;
		}
	}

public:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::forward_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename T,
		typename Proj = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Iter first, Sent last, T const& value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::subrange<Iter>,
		hamon::indirect_binary_predicate<
			ranges::equal_to,
			hamon::projected<Iter, Proj>,
			T const*>)
	{
		return impl(
			hamon::move(first),
			hamon::move(last),
			hamon::move(value),
			hamon::move(proj),
			hamon::detail::overload_priority<1>{});
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::forward_range, Range),
		typename T,
		typename Proj = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, T const& value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::borrowed_subrange_t<Range>,
		hamon::indirect_binary_predicate<
			ranges::equal_to,
			hamon::projected<ranges::iterator_t<Range>, Proj>,
			T const*>)
	{
		return (*this)(ranges::begin(r), ranges::end(r), value, hamon::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR find_last_fn find_last{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_FIND_LAST_HPP
