/**
 *	@file	unique.hpp
 *
 *	@brief	ranges::unique の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_UNIQUE_HPP
#define HAMON_ALGORITHM_RANGES_UNIQUE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::unique;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/adjacent_find.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/iterator/concepts/permutable.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirect_equivalence_relation.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_subrange_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#define HAMON_RETURN_TYPE_REQUIRES_CLAUSES(T, ...)	\
	-> T requires __VA_ARGS__
#else
#define HAMON_RETURN_TYPE_REQUIRES_CLAUSES(T, ...)	\
	-> hamon::enable_if_t<__VA_ARGS__::value, T>
#endif

struct unique_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::permutable, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<Iter, Proj>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_equivalence_relation,
			ProjectedIter,
			Comp,
			ranges::equal_to)
	>
	HAMON_CXX14_CONSTEXPR ranges::subrange<Iter>
	operator()(Iter first, Sent last,
		Comp comp = {}, Proj proj = {}) const
	{
		first = ranges::adjacent_find(first, last, comp, proj);
		if (first == last)
		{
			return { first, first };
		}

		auto dest = first;
		++first;
		while (++first != last)
		{
			if (!hamon::invoke(comp,
				hamon::invoke(proj, *dest),
				hamon::invoke(proj, *first)))
			{
				*++dest = std::move(*first);
			}
		}

		return { ++dest, first };
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::forward_range, Range),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<ranges::iterator_t<Range>, Proj>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_equivalence_relation,
			ProjectedIter,
			Comp,
			ranges::equal_to)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, Comp comp = {}, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::borrowed_subrange_t<Range>,
		hamon::permutable<ranges::iterator_t<Range>>)
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(comp), std::move(proj));
	}
};

#undef HAMON_RETURN_TYPE_REQUIRES_CLAUSES

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR unique_fn unique{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_UNIQUE_HPP
