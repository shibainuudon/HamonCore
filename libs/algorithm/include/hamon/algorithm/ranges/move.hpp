/**
 *	@file	move.hpp
 *
 *	@brief	ranges::move の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_MOVE_HPP
#define HAMON_ALGORITHM_RANGES_MOVE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::move;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_out_result.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/iterator/concepts/indirectly_movable.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/preprocessor/punctuation/comma.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
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
using move_result = in_out_result<Iter, Out>;

struct move_fn
{
private:
	template <
		typename Iter,
		HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, Iter, Sent),
		typename Out
	>
	static HAMON_CXX14_CONSTEXPR move_result<Iter, Out>
	impl(Iter first, Sent last, Out result,
		hamon::detail::overload_priority<1>)
	{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
		if (!std::is_constant_evaluated())
		{
			if constexpr (hamon::detail::is_memcpyable<Out, Iter>::value)
			{
				using ValueTypeI = hamon::iter_value_t<Iter>;
				static_assert(std::is_move_assignable<ValueTypeI>::value, "");
				auto num = last - first;
				if (num)
				{
					std::memmove(result, first, sizeof(ValueTypeI) * static_cast<std::size_t>(num));
				}
				return { first + num, result + num };
			}
		}
#endif

		for (auto n = last - first; n > 0; --n)
		{
			*result = std::move(*first);
			++first;
			++result;
		}

		return { std::move(first), std::move(result) };
	}

	template <
		typename Iter,
		typename Sent,
		typename Out
	>
	static HAMON_CXX14_CONSTEXPR move_result<Iter, Out>
	impl(Iter first, Sent last, Out result,
		hamon::detail::overload_priority<0>)
	{
		while (first != last)
		{
			*result = std::move(*first);
			++first;
			++result;
		}

		return { std::move(first), std::move(result) };
	}

public:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Iter first, Sent last, Out result) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		move_result<Iter HAMON_PP_COMMA() Out>,
		hamon::indirectly_movable<Iter, Out>)
	{
		return impl(
			std::move(first),
			std::move(last),
			std::move(result),
			hamon::detail::overload_priority<1>{});
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::input_range, Range),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, Out result) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		move_result<ranges::borrowed_iterator_t<Range> HAMON_PP_COMMA() Out>,
		hamon::indirectly_movable<ranges::iterator_t<Range>, Out>)
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(result));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR move_fn move{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_MOVE_HPP
