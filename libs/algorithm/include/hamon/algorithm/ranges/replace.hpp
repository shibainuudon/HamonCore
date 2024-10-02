/**
 *	@file	replace.hpp
 *
 *	@brief	ranges::replace の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_REPLACE_HPP
#define HAMON_ALGORITHM_RANGES_REPLACE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::replace;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/detail/and.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirectly_writable.hpp>
#include <hamon/iterator/concepts/indirect_binary_predicate.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/iterator/projected_value_t.hpp>
#include <hamon/preprocessor/punctuation/comma.hpp>
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

// 27.7.5 Replace[alg.replace]

struct replace_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, I),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, I, S),
		typename Proj = hamon::identity,
		typename T1 = hamon::projected_value_t<I, Proj>,
		typename T2 = T1
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		I first, S last,
		T1 const& old_value,
		T2 const& new_value,
		Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		I,
		HAMON_CONCEPTS_AND(
			hamon::indirectly_writable<I HAMON_PP_COMMA() T2 const&>,
			hamon::indirect_binary_predicate<
				ranges::equal_to HAMON_PP_COMMA()
				hamon::projected<I HAMON_PP_COMMA() Proj> HAMON_PP_COMMA()
				T1 const*>))
	{
		for (; first != last; ++first)
		{
			if (hamon::invoke(proj, *first) == old_value)
			{
				*first = new_value;
			}
		}

		return first;
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
		typename Proj = hamon::identity,
		typename T1 = hamon::projected_value_t<ranges::iterator_t<R>, Proj>,
		typename T2 = T1
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		R&& r,
		T1 const& old_value,
		T2 const& new_value,
		Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::borrowed_iterator_t<R>,
		HAMON_CONCEPTS_AND(
			hamon::indirectly_writable<ranges::iterator_t<R> HAMON_PP_COMMA() T2 const&>,
			hamon::indirect_binary_predicate<
				ranges::equal_to HAMON_PP_COMMA()
				hamon::projected<ranges::iterator_t<R> HAMON_PP_COMMA() Proj> HAMON_PP_COMMA()
				T1 const*>))
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			old_value, new_value, hamon::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR replace_fn replace{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_REPLACE_HPP
