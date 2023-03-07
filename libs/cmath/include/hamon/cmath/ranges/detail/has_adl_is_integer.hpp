/**
 *	@file	has_adl_is_integer.hpp
 *
 *	@brief	has_adl_is_integer の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_HAS_ADL_IS_INTEGER_HPP
#define HAMON_CMATH_RANGES_DETAIL_HAS_ADL_IS_INTEGER_HPP

#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/concepts/detail/can_reference.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

namespace ranges
{

namespace is_integer_detail
{

#if 0
void is_integer(const auto&) = delete;
#else
template <typename T> void is_integer(const T&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_is_integer =
	hamon::detail::class_or_enum<T> &&
	requires(T const& t)
	{
		{ is_integer(t) } -> hamon::detail::can_reference;
	};

#else

template <typename T>
struct has_adl_is_integer_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<U>::value>,
		typename S = decltype(is_integer(hamon::declval<U const&>()))
	>
	static auto test(int) -> hamon::detail::can_reference<S>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_is_integer = typename has_adl_is_integer_impl<T>::type;

#endif

}	// namespace is_integer_detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_HAS_ADL_IS_INTEGER_HPP
