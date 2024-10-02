/**
 *	@file	fill_n.hpp
 *
 *	@brief	ranges::fill_n の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_FILL_N_HPP
#define HAMON_ALGORITHM_RANGES_FILL_N_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::fill_n;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_scalar.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

// 27.7.6 Fill[alg.fill]

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
		typename O,
		typename T = hamon::iter_value_t<O>
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		O first, hamon::iter_difference_t<O> n, T const& value) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		O,
		hamon::output_iterator<O, T const&>)
	{
		if (n <= 0)
		{
			return first;
		}

		return impl(
			hamon::move(first),
			hamon::move(n),
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
