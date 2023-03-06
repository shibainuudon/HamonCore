/**
 *	@file	has_adl_floor.hpp
 *
 *	@brief	has_adl_floor の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_HAS_ADL_FLOOR_HPP
#define HAMON_CMATH_RANGES_DETAIL_HAS_ADL_FLOOR_HPP

#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/concepts/detail/can_reference.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace floor_detail
{

#if 0
void floor(const auto&) = delete;
#else
template <typename T> void floor(const T&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_floor =
	hamon::detail::class_or_enum<T> &&
	requires(T const& t)
	{
		{ floor(t) } -> hamon::detail::can_reference;
	};

#else

template <typename T>
struct has_adl_floor_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<U>::value>,
		typename S = decltype(floor(std::declval<U const&>()))
	>
	static auto test(int) -> hamon::detail::can_reference<S>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_floor = typename has_adl_floor_impl<T>::type;

#endif

}	// namespace floor_detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_HAS_ADL_FLOOR_HPP
