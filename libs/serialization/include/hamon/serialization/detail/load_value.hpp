/**
 *	@file	load_value.hpp
 *
 *	@brief	load_valueの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_LOAD_VALUE_HPP
#define HAMON_SERIALIZATION_DETAIL_LOAD_VALUE_HPP

#include <hamon/serialization/detail/load_array.hpp>
#include <hamon/serialization/detail/load_arithmetic.hpp>
#include <hamon/serialization/detail/load_class.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/underlying_type.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace load_value_detail
{

struct load_value_fn
{
private:
	// load array
	template <typename Archive, typename T, typename = hamon::enable_if_t<std::is_array<T>::value>>
	static void impl(Archive& ar, T& t, hamon::detail::overload_priority<3>)
	{
		hamon::serialization::detail::load_array(ar, t, std::extent<T>::value);
	}

	// load arithmetic
	template <typename Archive, typename T, typename = hamon::enable_if_t<std::is_arithmetic<T>::value>>
	static void impl(Archive& ar, T& t, hamon::detail::overload_priority<2>)
	{
		hamon::serialization::detail::load_arithmetic(ar, t);
	}
	
	// load enum
	template <typename Archive, typename T, typename = hamon::enable_if_t<std::is_enum<T>::value>>
	static void impl(Archive& ar, T& t, hamon::detail::overload_priority<1>)
	{
		hamon::underlying_type_t<T> tmp;
		hamon::serialization::detail::load_arithmetic(ar, tmp);
		t = static_cast<T>(tmp);
	}

	// load class
	template <typename Archive, typename T, typename = hamon::enable_if_t<std::is_class<T>::value>>
	static void impl(Archive& ar, T& t, hamon::detail::overload_priority<0>)
	{
		hamon::serialization::detail::load_class(ar, t);
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T& t) const
	{
		impl(ar, t, hamon::detail::overload_priority<3>{});
	}
};

}	// namespace load_value_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
load_value_detail::load_value_fn load_value{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_LOAD_VALUE_HPP
