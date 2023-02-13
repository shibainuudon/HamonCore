/**
 *	@file	remove_copy.hpp
 *
 *	@brief	ranges::remove_copy の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_REMOVE_COPY_HPP
#define HAMON_ALGORITHM_RANGES_REMOVE_COPY_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

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
#include <hamon/preprocessor/punctuation/comma.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

template <typename Iter, typename Out>
using remove_copy_result = in_out_result<Iter, Out>;

struct remove_copy_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out),
		typename T,
		typename Proj = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Iter first, Sent last, Out result,
		T const& value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		remove_copy_result<Iter HAMON_PP_COMMA() Out>,
		HAMON_CONCEPTS_AND(
			hamon::indirectly_copyable<Iter HAMON_PP_COMMA() Out>,
			hamon::indirect_binary_predicate<
				ranges::equal_to HAMON_PP_COMMA()
				hamon::projected<Iter HAMON_PP_COMMA() Proj> HAMON_PP_COMMA()
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

		return { std::move(first), std::move(result) };
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, Range),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out),
		typename T,
		typename Proj = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Range&& r, Out result,
		T const& value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		remove_copy_result<
			ranges::borrowed_iterator_t<Range> HAMON_PP_COMMA() Out>,
		HAMON_CONCEPTS_AND(
			hamon::indirectly_copyable<ranges::iterator_t<Range> HAMON_PP_COMMA() Out>,
			hamon::indirect_binary_predicate<
				ranges::equal_to HAMON_PP_COMMA()
				hamon::projected<ranges::iterator_t<Range> HAMON_PP_COMMA() Proj> HAMON_PP_COMMA()
				T const*>))
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(result), value, std::move(proj));
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
