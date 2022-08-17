/**
 *	@file	serialization_test_utility.hpp
 *
 *	@brief
 */

#ifndef SERIALIZATION_TEST_UTILITY_HPP
#define SERIALIZATION_TEST_UTILITY_HPP

#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <random>
#include <limits>

namespace
{

inline std::mt19937& get_random_engine()
{
	static std::mt19937 mt;
	return mt;
}

template <typename T, typename = hamon::enable_if_t<std::is_floating_point<T>::value>>
inline T get_random_value_impl(hamon::detail::overload_priority<2>)
{
	std::uniform_real_distribution<T> dist(
		std::numeric_limits<T>::lowest() / 2,
		std::numeric_limits<T>::max() / 2);
	return dist(get_random_engine());
}

template <typename T, typename = hamon::enable_if_t<std::is_unsigned<T>::value>>
inline T get_random_value_impl(hamon::detail::overload_priority<1>)
{
	std::uniform_int_distribution<std::uintmax_t> dist(
		std::numeric_limits<T>::min(),
		std::numeric_limits<T>::max());
	return static_cast<T>(dist(get_random_engine()));
}

template <typename T, typename = hamon::enable_if_t<std::is_signed<T>::value>>
inline T get_random_value_impl(hamon::detail::overload_priority<0>)
{
	std::uniform_int_distribution<std::intmax_t> dist(
		std::numeric_limits<T>::min(),
		std::numeric_limits<T>::max());
	return static_cast<T>(dist(get_random_engine()));
}

template <typename T>
inline T get_random_value()
{
	return get_random_value_impl<T>(hamon::detail::overload_priority<2>{});
}

}	// namespace

#endif // SERIALIZATION_TEST_UTILITY_HPP
