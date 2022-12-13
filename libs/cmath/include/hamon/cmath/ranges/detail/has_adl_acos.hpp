/**
 *	@file	has_adl_acos.hpp
 *
 *	@brief	has_adl_acos の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_HAS_ADL_ACOS_HPP
#define HAMON_CMATH_RANGES_DETAIL_HAS_ADL_ACOS_HPP

#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/concepts/detail/can_reference.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace acos_detail
{

#if 0
void acos(const auto&) = delete;
#else
template <typename T> void acos(const T&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_acos =
	hamon::detail::class_or_enum<T> &&
	requires(T const& t)
	{
		{ acos(t) } -> hamon::detail::can_reference;
	};

#else

template <typename T>
struct has_adl_acos_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<U>::value>,
		typename S = decltype(acos(std::declval<U const&>()))
	>
	static auto test(int) -> hamon::detail::can_reference<S>;

	template <typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_acos = typename has_adl_acos_impl<T>::type;

#endif

}	// namespace acos_detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_HAS_ADL_ACOS_HPP
