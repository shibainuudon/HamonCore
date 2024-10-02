/**
 *	@file	fill.hpp
 *
 *	@brief	ranges::fill の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_FILL_HPP
#define HAMON_ALGORITHM_RANGES_FILL_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

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
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/ranges/concepts/output_range.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_scalar.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

namespace ranges
{

// 27.7.6 Fill[alg.fill]

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
		typename = hamon::enable_if_t<hamon::is_scalar<T>::value>>
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
		typename O,
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, O, S),
		typename T = hamon::iter_value_t<O>
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		O first, S last, T const& value) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		O,
		hamon::output_iterator<O, T const&>)
	{
		return impl(
			hamon::move(first),
			hamon::move(last),
			value,
			hamon::detail::overload_priority<2>{});
	}

	template <
		typename R,
		typename T = ranges::range_value_t<R>
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(R&& r, T const& value) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::borrowed_iterator_t<R>,
		ranges::output_range<R, T const&>)
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
