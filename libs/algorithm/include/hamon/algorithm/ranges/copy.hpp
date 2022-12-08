/**
 *	@file	copy.hpp
 *
 *	@brief	ranges::copy の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_COPY_HPP
#define HAMON_ALGORITHM_RANGES_COPY_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::copy;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_out_result.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/iterator/concepts/indirectly_copyable.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/detail/is_memcpyable.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <utility>
#include <cstring>	// memmove

namespace hamon
{

namespace ranges
{

template <typename Iter, typename Out>
using copy_result = in_out_result<Iter, Out>;

struct copy_fn
{
private:
	template <
		typename Iter,
		HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, Iter, Sent),
		typename Out
	>
	static HAMON_CXX14_CONSTEXPR copy_result<Iter, Out>
	impl(Iter first, Sent last, Out result,
		hamon::detail::overload_priority<1>)
	{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
		if (!std::is_constant_evaluated())
		{
			if constexpr (hamon::detail::is_memcpyable<Out, Iter>::value)
			{
				using ValueTypeI = hamon::iter_value_t<Iter>;
				static_assert(std::is_copy_assignable<ValueTypeI>::value, "");
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
			*result = *first;
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
	static HAMON_CXX14_CONSTEXPR copy_result<Iter, Out>
	impl(Iter first, Sent last, Out result,
		hamon::detail::overload_priority<0>)
	{
		while (first != last)
		{
			*result = *first;
			++first;
			++result;
		}

		return { std::move(first), std::move(result) };
	}

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <
		hamon::input_iterator Iter,
		hamon::sentinel_for<Iter> Sent,
		hamon::weakly_incrementable Out
	>
	requires hamon::indirectly_copyable<Iter, Out>
#else
	template <
		typename Iter,
		typename Sent,
		typename Out,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::input_iterator<Iter>,
			hamon::sentinel_for<Sent, Iter>,
			hamon::weakly_incrementable<Out>,
			hamon::indirectly_copyable<Iter, Out>
		>::value>
	>
#endif
	HAMON_CXX14_CONSTEXPR copy_result<Iter, Out>
	operator()(Iter first, Sent last, Out result) const
	{
		return impl(
			std::move(first),
			std::move(last),
			std::move(result),
			hamon::detail::overload_priority<1>{});
	}

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <
		ranges::input_range Range,
		hamon::weakly_incrementable Out
	>
	requires hamon::indirectly_copyable<ranges::iterator_t<Range>, Out>
#else
	template <
		typename Range,
		typename Out,
		typename = hamon::enable_if_t<hamon::conjunction<
			ranges::input_range<Range>,
			hamon::weakly_incrementable<Out>,
			hamon::indirectly_copyable<ranges::iterator_t<Range>, Out>
		>::value>
	>
#endif
	HAMON_CXX14_CONSTEXPR copy_result<ranges::borrowed_iterator_t<Range>, Out>
	operator()(Range&& r, Out result) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(result));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR copy_fn copy{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_COPY_HPP
