/**
 *	@file	fill_n.hpp
 *
 *	@brief	ranges::fill_n の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_FILL_N_HPP
#define HAMON_ALGORITHM_RANGES_FILL_N_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::fill_n;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_scalar.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

struct fill_n_fn
{
private:
	//// TODO: Generalize this optimization to contiguous iterators.
	//if constexpr (is_pointer_v<Out>
	//	// Note that __is_byte already implies !is_volatile.
	//	&& __is_byte<remove_pointer_t<Out>>::value
	//	&& integral<T>)
	//{
	//	__builtin_memset(first, static_cast<unsigned char>(value), n);
	//	return first + n;
	//}

	template <typename T, typename Out, typename Difference,
		typename = hamon::enable_if_t<hamon::is_scalar<T>::value>>
	static HAMON_CXX14_CONSTEXPR Out
	impl(Out first, Difference n, T const& value,
		hamon::detail::overload_priority<1>)
	{
		auto const tmp = value;
		for (; n > 0; --n, (void)++first)
		{
			*first = tmp;
		}

		return first;
	}

	template <typename T, typename Out, typename Difference>
	static HAMON_CXX14_CONSTEXPR Out
	impl(Out first, Difference n, T const& value,
		hamon::detail::overload_priority<0>)
	{
		for (; n > 0; --n, (void)++first)
		{
			*first = value;
		}

		return first;
	}

public:
	template <
		typename T,
		HAMON_CONSTRAINED_PARAM(hamon::output_iterator, T const&, Out)
	>
	HAMON_CXX14_CONSTEXPR Out operator()(
		Out first, hamon::iter_difference_t<Out> n, T const& value) const
	{
		if (n <= 0)
		{
			return first;
		}

		return impl(
			std::move(first),
			std::move(n),
			value,
			hamon::detail::overload_priority<1>{});
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR fill_n_fn fill_n{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_FILL_N_HPP
