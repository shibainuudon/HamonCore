/**
 *	@file	contains.hpp
 *
 *	@brief	ranges::contains の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_CONTAINS_HPP
#define HAMON_ALGORITHM_RANGES_CONTAINS_HPP

#include <algorithm>

#if defined(__cpp_lib_ranges_contains) && (__cpp_lib_ranges_contains >= 202207L)

namespace hamon
{

namespace ranges
{

using std::ranges::contains;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/find.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirect_binary_predicate.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace detail
{

struct contains_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename T,
		typename Proj = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Iter first, Sent last, T const& value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		bool,
		hamon::indirect_binary_predicate<
			ranges::equal_to,
			hamon::projected<Iter, Proj>,
			T const*
		>)
	{
		return ranges::find(hamon::move(first), last, value, proj) != last;
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::input_range, Range),
		typename T,
		typename Proj = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, T const& value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		bool,
		hamon::indirect_binary_predicate<
			ranges::equal_to,
			hamon::projected<ranges::iterator_t<Range>, Proj>,
			T const*
		>)
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			hamon::move(value),
			proj);
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR detail::contains_fn contains{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_CONTAINS_HPP
