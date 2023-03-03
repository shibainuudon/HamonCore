/**
 *	@file	save_value.hpp
 *
 *	@brief	save_valueの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_SAVE_VALUE_HPP
#define HAMON_SERIALIZATION_DETAIL_SAVE_VALUE_HPP

#include <hamon/serialization/detail/has_adl_save_value.hpp>
#include <hamon/serialization/detail/save_array.hpp>
#include <hamon/serialization/detail/save_arithmetic.hpp>
#include <hamon/serialization/detail/save_class.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/underlying_type.hpp>
#include <hamon/type_traits/is_arithmetic.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace save_value_detail
{

struct save_value_fn
{
private:
	// save_value(ar, t);
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_save_value<Archive&, T const&>::value>>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<4>)
	{
		save_value(ar, t);
	}

	// save array
	template <typename Archive, typename T, typename = hamon::enable_if_t<hamon::is_array<T>::value>>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<3>)
	{
		hamon::serialization::detail::save_array(ar, t);
	}
	
	// save arithmetic
	template <typename Archive, typename T, typename = hamon::enable_if_t<hamon::is_arithmetic<T>::value>>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<2>)
	{
		hamon::serialization::detail::save_arithmetic(ar, t);
	}

	// save enum
	template <typename Archive, typename T, typename = hamon::enable_if_t<std::is_enum<T>::value>>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<1>)
	{
		hamon::serialization::detail::save_arithmetic(ar, static_cast<hamon::underlying_type_t<T>>(t));
	}

	// save class
	template <typename Archive, typename T, typename = hamon::enable_if_t<std::is_class<T>::value>>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<0>)
	{
		hamon::serialization::detail::save_class(ar, t);
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T const& t) const
	{
		impl(ar, t, hamon::detail::overload_priority<4>{});
	}
};

}	// namespace save_value_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
save_value_detail::save_value_fn save_value{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_SAVE_VALUE_HPP
