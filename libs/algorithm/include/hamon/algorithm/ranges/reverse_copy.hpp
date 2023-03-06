/**
 *	@file	reverse_copy.hpp
 *
 *	@brief	ranges::reverse_copy の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_REVERSE_COPY_HPP
#define HAMON_ALGORITHM_RANGES_REVERSE_COPY_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::reverse_copy;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_out_result.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/iterator/concepts/indirectly_copyable.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/preprocessor/punctuation/comma.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
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

template <typename Iter, typename Out>
using reverse_copy_result = in_out_result<Iter, Out>;

struct reverse_copy_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Iter first, Sent last, Out result) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		reverse_copy_result<Iter HAMON_PP_COMMA() Out>,
		hamon::indirectly_copyable<Iter HAMON_PP_COMMA() Out>)
	{
		auto i = ranges::next(first, last);
		auto tail = i;
		while (first != tail)
		{
			--tail;
			*result = *tail;
			++result;
		}

		return { i, result };
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::bidirectional_range, Range),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, Out result) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		reverse_copy_result<ranges::borrowed_iterator_t<Range> HAMON_PP_COMMA() Out>,
		hamon::indirectly_copyable<ranges::iterator_t<Range> HAMON_PP_COMMA() Out>)
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			hamon::move(result));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR reverse_copy_fn reverse_copy{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_REVERSE_COPY_HPP
