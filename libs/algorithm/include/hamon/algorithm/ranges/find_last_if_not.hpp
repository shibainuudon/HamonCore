/**
 *	@file	find_last_if_not.hpp
 *
 *	@brief	ranges::find_last_if_not の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_FIND_LAST_IF_NOT_HPP
#define HAMON_ALGORITHM_RANGES_FIND_LAST_IF_NOT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) &&	\
	defined(__cpp_lib_find_last) && (__cpp_lib_find_last >= 202207L)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::find_last_if_not;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/find_if_not.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirect_unary_predicate.hpp>
#include <hamon/iterator/ranges/prev.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/preprocessor/punctuation/comma.hpp>
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

struct find_last_if_not_fn
{
private:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::same_as, Iter, Sent),
		typename Proj,
		typename Pred
	>
	HAMON_CXX14_CONSTEXPR ranges::subrange<Iter> impl(
		Iter first, Sent last, Pred pred, Proj proj,
		hamon::detail::overload_priority<1>) const
	{
		Iter found = ranges::find_if_not(
			hamon::reverse_iterator<Iter>{last},
			hamon::reverse_iterator<Iter>{first},
			hamon::move(pred), hamon::move(proj)).base();

		if (found == first)
		{
			return { last, last };
		}
		else
		{
			return { ranges::prev(found), last };
		}
	}

	template <typename Iter, typename Sent, typename Proj, typename Pred>
	HAMON_CXX14_CONSTEXPR ranges::subrange<Iter> impl(
		Iter first, Sent last, Pred pred, Proj proj,
		hamon::detail::overload_priority<0>) const
	{
		Iter found = ranges::find_if_not(first, last, pred, proj);
		if (found == last)
		{
			return { found, found };
		}

		first = found;

		for (;;)
		{
			first = ranges::find_if_not(ranges::next(first), last, pred, proj);
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
		typename Proj = hamon::identity,
		HAMON_CONSTRAINED_PARAM(
			hamon::indirect_unary_predicate,
			hamon::projected<Iter HAMON_PP_COMMA() Proj>,
			Pred)
	>
	HAMON_CXX14_CONSTEXPR ranges::subrange<Iter>
	operator()(Iter first, Sent last, Pred pred, Proj proj = {}) const
	{
		return impl(
			hamon::move(first),
			hamon::move(last),
			hamon::move(pred),
			hamon::move(proj),
			hamon::detail::overload_priority<1>{});
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::forward_range, Range),
		typename Proj = hamon::identity,
		HAMON_CONSTRAINED_PARAM(
			hamon::indirect_unary_predicate,
			hamon::projected<ranges::iterator_t<Range> HAMON_PP_COMMA() Proj>,
			Pred)
	>
	HAMON_CXX14_CONSTEXPR ranges::borrowed_subrange_t<Range>
	operator()(Range&& r, Pred pred, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			hamon::move(pred), hamon::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR find_last_if_not_fn find_last_if_not{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_FIND_LAST_IF_NOT_HPP
