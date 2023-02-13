/**
 *	@file	shuffle.hpp
 *
 *	@brief	ranges::shuffle の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_SHUFFLE_HPP
#define HAMON_ALGORITHM_RANGES_SHUFFLE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::shuffle;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/shuffle.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/detail/and.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/permutable.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/random/concepts/uniform_random_bit_generator.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

struct shuffle_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::random_access_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename Gen
	>
	auto operator()(Iter first, Sent last, Gen&& g) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		Iter,
		HAMON_CONCEPTS_AND(
			hamon::permutable<Iter>,
			hamon::uniform_random_bit_generator<
				hamon::remove_reference_t<Gen>>))
	{
		auto lasti = ranges::next(first, last);
		hamon::shuffle(std::move(first), lasti, std::forward<Gen>(g));
		return lasti;
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::random_access_range, Range),
		typename Gen
	>
	auto operator()(Range&& r, Gen&& g) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::borrowed_iterator_t<Range>,
		HAMON_CONCEPTS_AND(
			hamon::permutable<ranges::iterator_t<Range>>,
			hamon::uniform_random_bit_generator<
				hamon::remove_reference_t<Gen>>))
	{
		return (*this)(
			ranges::begin(r), ranges::end(r), std::forward<Gen>(g));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR shuffle_fn shuffle{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_SHUFFLE_HPP
