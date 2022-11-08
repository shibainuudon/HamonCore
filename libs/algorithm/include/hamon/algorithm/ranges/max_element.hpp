/**
 *	@file	max_element.hpp
 *
 *	@brief	ranges::max_element の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_MAX_ELEMENT_HPP
#define HAMON_ALGORITHM_RANGES_MAX_ELEMENT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::max_element;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/functional/ranges/less.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirect_strict_weak_order.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

struct max_element_fn
{
	template <
#if defined(HAMON_HAS_CXX20_CONCEPTS)
		hamon::forward_iterator Iter,
		hamon::sentinel_for<Iter> Sent,
		typename Proj = hamon::identity,
		hamon::indirect_strict_weak_order<
			hamon::projected<Iter, Proj>
		> Comp = ranges::less
#else
		typename Iter,
		typename Sent,
		typename Proj = hamon::identity,
		typename Comp = ranges::less,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::forward_iterator<Iter>,
			hamon::sentinel_for<Sent, Iter>,
			hamon::indirect_strict_weak_order<Comp,
				hamon::projected<Iter, Proj>>
		>::value>
#endif
	>
	HAMON_CXX14_CONSTEXPR Iter
	operator()(
		Iter first, Sent last,
		Comp comp = {}, Proj proj = {}) const
	{
		if (first == last)
		{
			return first;
		}

		auto i = first;
		while (++i != last)
		{
			if (hamon::invoke(comp,
				hamon::invoke(proj, *first),
				hamon::invoke(proj, *i)))
			{
				first = i;
			}
		}

		return first;
	}

	template <
#if defined(HAMON_HAS_CXX20_CONCEPTS)
		ranges::forward_range Range,
		typename Proj = hamon::identity,
		hamon::indirect_strict_weak_order<
			hamon::projected<ranges::iterator_t<Range>, Proj>
		> Comp = ranges::less
#else
		typename Range,
		typename Proj = hamon::identity,
		typename Comp = ranges::less,
		typename = hamon::enable_if_t<hamon::conjunction<
			ranges::forward_range<Range>,
			hamon::indirect_strict_weak_order<Comp,
				hamon::projected<ranges::iterator_t<Range>, Proj>>
		>::value>
#endif
	>
	HAMON_CXX14_CONSTEXPR ranges::borrowed_iterator_t<Range>
	operator()(Range&& r, Comp comp = {}, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(comp), std::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR max_element_fn max_element{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_MAX_ELEMENT_HPP
