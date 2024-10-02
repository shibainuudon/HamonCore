/**
 *	@file	find.hpp
 *
 *	@brief	ranges::find の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_FIND_HPP
#define HAMON_ALGORITHM_RANGES_FIND_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::find;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirect_binary_predicate.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/iterator/projected_value_t.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
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

// 27.6.6 Find[alg.find]

struct find_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, I),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, I, S),
		typename Proj = hamon::identity,
		typename T = hamon::projected_value_t<I, Proj>
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		I first, S last, T const& value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		I,
		hamon::indirect_binary_predicate<
			ranges::equal_to,
			hamon::projected<I, Proj>,
			T const*>)
	{
		while (first != last && !(hamon::invoke(proj, *first) == value))
		{
			++first;
		}

		return first;
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
		typename Proj = hamon::identity,
		typename T = hamon::projected_value_t<ranges::iterator_t<R>, Proj>
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		R&& r, T const& value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::borrowed_iterator_t<R>,
		hamon::indirect_binary_predicate<
			ranges::equal_to,
			hamon::projected<ranges::iterator_t<R>, Proj>,
			T const*>)
	{
		return (*this)(
			ranges::begin(r), ranges::end(r), value, hamon::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR find_fn find{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_FIND_HPP
