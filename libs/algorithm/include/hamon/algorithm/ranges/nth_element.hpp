﻿/**
 *	@file	nth_element.hpp
 *
 *	@brief	ranges::nth_element の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_NTH_ELEMENT_HPP
#define HAMON_ALGORITHM_RANGES_NTH_ELEMENT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::nth_element;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/nth_element.hpp>
#include <hamon/algorithm/ranges/detail/make_comp_proj.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sortable.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
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

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#define HAMON_RETURN_TYPE_REQUIRES_CLAUSES(T, ...)	\
	-> T requires __VA_ARGS__
#else
#define HAMON_RETURN_TYPE_REQUIRES_CLAUSES(T, ...)	\
	-> hamon::enable_if_t<__VA_ARGS__::value, T>
#endif

struct nth_element_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::random_access_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename Comp = ranges::less,
		typename Proj = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Iter first, Iter nth, Sent last,
		Comp comp = {}, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		Iter,
		hamon::sortable<Iter, Comp, Proj>)
	{
		auto lasti = ranges::next(first, last);
		hamon::nth_element(
			std::move(first),
			std::move(nth),
			lasti,
			detail::make_comp_proj(comp, proj));
		return lasti;
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::random_access_range, Range),
		typename Comp = ranges::less,
		typename Proj = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, ranges::iterator_t<Range> nth,
		Comp comp = {}, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::borrowed_iterator_t<Range>,
		hamon::sortable<ranges::iterator_t<Range>, Comp, Proj>)
	{
		return (*this)(
			ranges::begin(r),
			std::move(nth),
			ranges::end(r),
			std::move(comp),
			std::move(proj));
	}
};

#undef HAMON_RETURN_TYPE_REQUIRES_CLAUSES

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR nth_element_fn nth_element{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_NTH_ELEMENT_HPP
