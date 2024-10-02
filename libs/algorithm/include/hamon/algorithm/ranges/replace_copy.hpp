/**
 *	@file	replace_copy.hpp
 *
 *	@brief	ranges::replace_copy の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_REPLACE_COPY_HPP
#define HAMON_ALGORITHM_RANGES_REPLACE_COPY_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::replace_copy;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_out_result.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/detail/and.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/iterator/concepts/indirectly_copyable.hpp>
#include <hamon/iterator/concepts/indirect_binary_predicate.hpp>
#include <hamon/iterator/iter_value_t.hpp>
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

template <typename I, typename O>
using replace_copy_result = in_out_result<I, O>;

struct replace_copy_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, I),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, I, S),
		typename O,
		typename Proj = hamon::identity,
		typename T1 = hamon::projected_value_t<I, Proj>,
		typename T2 = hamon::iter_value_t<O>
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		I first, S last,
		O result,
		T1 const& old_value,
		T2 const& new_value,
		Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		replace_copy_result<I HAMON_PP_COMMA() O>,
		HAMON_CONCEPTS_AND(
			hamon::indirectly_copyable<I HAMON_PP_COMMA() O>,
		HAMON_CONCEPTS_AND(
			hamon::indirect_binary_predicate<
				ranges::equal_to HAMON_PP_COMMA()
				hamon::projected<I HAMON_PP_COMMA() Proj> HAMON_PP_COMMA()
				T1 const*>,
			hamon::output_iterator<O HAMON_PP_COMMA() T2 const&>)))
	{
		for (; first != last; ++first, (void)++result)
		{
			if (hamon::invoke(proj, *first) == old_value)
			{
				*result = new_value;
			}
			else
			{
				*result = *first;
			}
		}

		return { hamon::move(first), hamon::move(result) };
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
		typename O,
		typename Proj = hamon::identity,
		typename T1 = hamon::projected_value_t<ranges::iterator_t<R>, Proj>,
		typename T2 = hamon::iter_value_t<O>
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		R&& r,
		O result,
		T1 const& old_value,
		T2 const& new_value,
		Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		replace_copy_result<
			ranges::borrowed_iterator_t<R> HAMON_PP_COMMA() O>,
		HAMON_CONCEPTS_AND(
			hamon::indirectly_copyable<ranges::iterator_t<R> HAMON_PP_COMMA() O>,
		HAMON_CONCEPTS_AND(
			hamon::indirect_binary_predicate<
				ranges::equal_to HAMON_PP_COMMA()
				hamon::projected<ranges::iterator_t<R> HAMON_PP_COMMA() Proj> HAMON_PP_COMMA()
				T1 const*>,
			hamon::output_iterator<O HAMON_PP_COMMA() T2 const&>)))
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			hamon::move(result),
			old_value,
			new_value,
			hamon::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR replace_copy_fn replace_copy{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_REPLACE_COPY_HPP
