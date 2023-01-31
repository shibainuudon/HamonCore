/**
 *	@file	fill.hpp
 *
 *	@brief	ranges::fill の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_FILL_HPP
#define HAMON_ALGORITHM_RANGES_FILL_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::fill;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/fill_n.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/ranges/concepts/output_range.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace ranges
{

struct fill_fn
{
private:
	template <
		typename T,
		typename Out,
		HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, Out, Sent)
	>
	static HAMON_CXX14_CONSTEXPR Out
	impl(Out first, Sent last, T const& value,
		hamon::detail::overload_priority<2>)
	{
		auto const len = last - first;
		return ranges::fill_n(first, len, value);
	}

	template <typename T, typename Out, typename Sent,
		typename = hamon::enable_if_t<std::is_scalar<T>::value>>
	static HAMON_CXX14_CONSTEXPR Out
	impl(Out first, Sent last, T const& value,
		hamon::detail::overload_priority<1>)
	{
		const auto tmp = value;
		for (; first != last; ++first)
		{
			*first = tmp;
		}

		return first;
	}

	template <typename T, typename Out, typename Sent>
	static HAMON_CXX14_CONSTEXPR Out
	impl(Out first, Sent last, T const& value,
		hamon::detail::overload_priority<0>)
	{
		for (; first != last; ++first)
		{
			*first = value;
		}

		return first;
	}

public:
	template <
		typename T,
		HAMON_CONSTRAINED_PARAM(hamon::output_iterator, T const&, Out),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Out, Sent)
	>
	HAMON_CXX14_CONSTEXPR Out operator()(
		Out first, Sent last, T const& value) const
	{
		return impl(
			std::move(first),
			std::move(last),
			value,
			hamon::detail::overload_priority<2>{});
	}

	template <
		typename T,
		HAMON_CONSTRAINED_PARAM(ranges::output_range, T const&, Range)
	>
	HAMON_CXX14_CONSTEXPR ranges::borrowed_iterator_t<Range>
	operator()(Range&& r, T const& value) const
	{
		return (*this)(ranges::begin(r), ranges::end(r), value);
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR fill_fn fill{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_FILL_HPP
