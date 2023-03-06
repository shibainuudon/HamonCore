/**
 *	@file	move_backward.hpp
 *
 *	@brief	ranges::move_backward の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_MOVE_BACKWARD_HPP
#define HAMON_ALGORITHM_RANGES_MOVE_BACKWARD_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::move_backward;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_out_result.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/concepts/indirectly_movable.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/preprocessor/punctuation/comma.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/detail/is_memcpyable.hpp>
#include <hamon/config.hpp>
#include <type_traits>	// is_constant_evaluated
#include <utility>
#include <cstring>	// memmove

namespace hamon
{

namespace ranges
{

template <typename Iter, typename Out>
using move_backward_result = in_out_result<Iter, Out>;

struct move_backward_fn
{
private:
	template <
		typename Iter,
		HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, Iter, Sent),
		typename Out
	>
	static HAMON_CXX14_CONSTEXPR move_backward_result<Iter, Out>
	impl(Iter first, Sent last, Out result,
		hamon::detail::overload_priority<1>)
	{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
		if (!std::is_constant_evaluated())
		{
			if constexpr (hamon::detail::is_memcpyable<Out, Iter>::value)
			{
				using ValueTypeI = hamon::iter_value_t<Iter>;
				static_assert(hamon::is_move_assignable<ValueTypeI>::value, "");
				auto num = last - first;
				if (num)
				{
					std::memmove(result - num, first, sizeof(ValueTypeI) * static_cast<std::size_t>(num));
				}
				return { first + num, result - num };
			}
		}
#endif

		auto lasti = ranges::next(first, last);
		auto tail = lasti;

		for (auto n = last - first; n > 0; --n)
		{
			--tail;
			--result;
			*result = std::move(*tail);
		}

		return { std::move(lasti), std::move(result) };
	}

	template <typename Iter, typename Sent, typename Out>
	static HAMON_CXX14_CONSTEXPR move_backward_result<Iter, Out>
	impl(Iter first, Sent last, Out result,
		hamon::detail::overload_priority<0>)
	{
		auto lasti = ranges::next(first, last);
		auto tail = lasti;

		while (first != tail)
		{
			--tail;
			--result;
			*result = std::move(*tail);
		}

		return { std::move(lasti), std::move(result) };
	}

public:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, Out)
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Iter first, Sent last, Out result) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		move_backward_result<Iter HAMON_PP_COMMA() Out>,
		hamon::indirectly_movable<Iter, Out>)
	{
		return impl(
			std::move(first),
			std::move(last),
			std::move(result),
			hamon::detail::overload_priority<1>{});
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::bidirectional_range, Range),
		HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, Out)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, Out result) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		move_backward_result<ranges::borrowed_iterator_t<Range> HAMON_PP_COMMA() Out>,
		hamon::indirectly_movable<ranges::iterator_t<Range>, Out>)
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(result));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR move_backward_fn move_backward{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_MOVE_BACKWARD_HPP
