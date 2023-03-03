/**
 *	@file	get_random_value.hpp
 *
 *	@brief
 */

#ifndef UNIT_TEST_COMMON_GET_RANDOM_VALUE_HPP
#define UNIT_TEST_COMMON_GET_RANDOM_VALUE_HPP

#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <random>
#include <limits>
#include <type_traits>

namespace
{

inline std::mt19937& get_random_engine()
{
	static std::mt19937 mt;
	return mt;
}

template <typename T, typename = hamon::enable_if_t<std::is_floating_point<T>::value>>
inline T get_random_value_impl(T min, T max, hamon::detail::overload_priority<2>)
{
	std::uniform_real_distribution<T> dist(min, max);
	return dist(get_random_engine());
}

template <typename T, typename = hamon::enable_if_t<std::is_unsigned<T>::value>>
inline T get_random_value_impl(T min, T max, hamon::detail::overload_priority<1>)
{
	std::uniform_int_distribution<std::uintmax_t> dist(min, max);
	return static_cast<T>(dist(get_random_engine()));
}

template <typename T, typename = hamon::enable_if_t<std::is_signed<T>::value>>
inline T get_random_value_impl(T min, T max, hamon::detail::overload_priority<0>)
{
	std::uniform_int_distribution<std::intmax_t> dist(min, max);
	return static_cast<T>(dist(get_random_engine()));
}

template <typename T>
inline T get_random_value(T min, T max)
{
	return get_random_value_impl<T>(min, max, hamon::detail::overload_priority<2>{});
}

template <typename T, typename = hamon::enable_if_t<std::is_floating_point<T>::value>>
inline T get_random_value_impl(hamon::detail::overload_priority<1>)
{
	return get_random_value(
		std::numeric_limits<T>::lowest() / 2,
		std::numeric_limits<T>::max() / 2);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, T)>
inline T get_random_value_impl(hamon::detail::overload_priority<0>)
{
	return get_random_value(
		std::numeric_limits<T>::min(),
		std::numeric_limits<T>::max());
}

template <typename T>
inline T get_random_value()
{
	return get_random_value_impl<T>(hamon::detail::overload_priority<1>{});
}

}	// namespace

#endif // UNIT_TEST_COMMON_GET_RANDOM_VALUE_HPP
