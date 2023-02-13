/**
 *	@file	sample.hpp
 *
 *	@brief	ranges::sample の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_SAMPLE_HPP
#define HAMON_ALGORITHM_RANGES_SAMPLE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::sample;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/sample.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/detail/and.hpp>
#include <hamon/concepts/detail/or.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/concepts/indirectly_copyable.hpp>
#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/preprocessor/punctuation/comma.hpp>
#include <hamon/random/concepts/uniform_random_bit_generator.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

struct sample_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, OutIter),
		typename Gen
	>
	auto operator()(
		Iter first, Sent last,
		OutIter out_first,
		hamon::iter_difference_t<Iter> n, Gen&& g) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		OutIter,
		HAMON_CONCEPTS_AND(
			HAMON_CONCEPTS_OR(
				hamon::forward_iterator<Iter>,
				hamon::random_access_iterator<OutIter>),
		HAMON_CONCEPTS_AND(
			hamon::indirectly_copyable<
				Iter HAMON_PP_COMMA() OutIter>,
			hamon::uniform_random_bit_generator<
				hamon::remove_reference_t<Gen>>)))
	{
		return hamon::sample(
			std::move(first), ranges::next(first, last),
			std::move(out_first), n, std::forward<Gen>(g));
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::input_range, Range),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, OutIter),
		typename Gen
	>
	auto operator()(
		Range&& r, OutIter out_first,
		ranges::range_difference_t<Range> n, Gen&& g) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		OutIter,
		HAMON_CONCEPTS_AND(
			HAMON_CONCEPTS_OR(
				ranges::forward_range<Range>,
				hamon::random_access_iterator<OutIter>),
		HAMON_CONCEPTS_AND(
			hamon::indirectly_copyable<
				ranges::iterator_t<Range> HAMON_PP_COMMA() OutIter>,
			hamon::uniform_random_bit_generator<
				hamon::remove_reference_t<Gen>>)))
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(out_first), n, std::forward<Gen>(g));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR sample_fn sample{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_sample_HPP
