/**
 *	@file	remove_copy.hpp
 *
 *	@brief	ranges::remove_copy の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_REMOVE_COPY_HPP
#define HAMON_ALGORITHM_RANGES_REMOVE_COPY_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::remove_copy;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_out_result.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/detail/and.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/iterator/concepts/indirectly_copyable.hpp>
#include <hamon/iterator/concepts/indirect_binary_predicate.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/iterator/projected_value_t.hpp>
#include <hamon/preprocessor/punctuation/comma.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

// 27.7.8 Remove[alg.remove]

template <typename I, typename O>
using remove_copy_result = in_out_result<I, O>;

struct remove_copy_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, I),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, I, S),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, O),
		typename Proj = hamon::identity,
		typename T = hamon::projected_value_t<I, Proj>
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		I first, S last, O result,
		T const& value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		remove_copy_result<I HAMON_PP_COMMA() O>,
		HAMON_CONCEPTS_AND(
			hamon::indirectly_copyable<I HAMON_PP_COMMA() O>,
			hamon::indirect_binary_predicate<
				ranges::equal_to HAMON_PP_COMMA()
				hamon::projected<I HAMON_PP_COMMA() Proj> HAMON_PP_COMMA()
				T const*>
		))
	{
		for (; first != last; ++first)
		{
			if (!(hamon::invoke(proj, *first) == value))
			{
				*result = *first;
				++result;
			}
		}

		return { hamon::move(first), hamon::move(result) };
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, O),
		typename Proj = hamon::identity,
		typename T = hamon::projected_value_t<ranges::iterator_t<R>, Proj>
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		R&& r, O result,
		T const& value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		remove_copy_result<
			ranges::borrowed_iterator_t<R> HAMON_PP_COMMA() O>,
		HAMON_CONCEPTS_AND(
			hamon::indirectly_copyable<ranges::iterator_t<R> HAMON_PP_COMMA() O>,
			hamon::indirect_binary_predicate<
				ranges::equal_to HAMON_PP_COMMA()
				hamon::projected<ranges::iterator_t<R> HAMON_PP_COMMA() Proj> HAMON_PP_COMMA()
				T const*>))
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			hamon::move(result), value, hamon::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR remove_copy_fn remove_copy{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_REMOVE_COPY_HPP
