/**
 *	@file	has_adl_round_half_even.hpp
 *
 *	@brief	has_adl_round_half_even の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_HAS_ADL_ROUND_HALF_EVEN_HPP
#define HAMON_CMATH_RANGES_DETAIL_HAS_ADL_ROUND_HALF_EVEN_HPP

#include <hamon/cmath/ranges/detail/is_not_void.hpp>
#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

namespace ranges
{

namespace round_half_even_detail
{

#if 0
void round_half_even(const auto&) = delete;
#else
template <typename T> void round_half_even(const T&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_round_half_even =
	hamon::detail::class_or_enum<T> &&
	requires(T const& t)
	{
		{ round_half_even(t) } -> hamon::detail::is_not_void;
	};

#else

template <typename T>
struct has_adl_round_half_even_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<U>::value>,
		typename S = decltype(round_half_even(hamon::declval<U const&>()))
	>
	static auto test(int) -> hamon::detail::is_not_void<S>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_round_half_even = typename has_adl_round_half_even_impl<T>::type;

#endif

}	// namespace round_half_even_detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_HAS_ADL_ROUND_HALF_EVEN_HPP
