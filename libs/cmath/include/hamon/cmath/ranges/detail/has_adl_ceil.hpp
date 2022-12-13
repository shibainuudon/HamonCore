/**
 *	@file	has_adl_ceil.hpp
 *
 *	@brief	has_adl_ceil の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_HAS_ADL_CEIL_HPP
#define HAMON_CMATH_RANGES_DETAIL_HAS_ADL_CEIL_HPP

#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/concepts/detail/can_reference.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace ceil_detail
{

#if 0
void ceil(const auto&) = delete;
#else
template <typename T> void ceil(const T&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_ceil =
	hamon::detail::class_or_enum<T> &&
	requires(T const& t)
	{
		{ ceil(t) } -> hamon::detail::can_reference;
	};

#else

template <typename T>
struct has_adl_ceil_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<U>::value>,
		typename S = decltype(ceil(std::declval<U const&>()))
	>
	static auto test(int) -> hamon::detail::can_reference<S>;

	template <typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_ceil = typename has_adl_ceil_impl<T>::type;

#endif

}	// namespace ceil_detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_HAS_ADL_CEIL_HPP
