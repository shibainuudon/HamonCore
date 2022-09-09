/**
 *	@file	save_value.hpp
 *
 *	@brief	save_valueの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_SAVE_VALUE_HPP
#define HAMON_SERIALIZATION_DETAIL_SAVE_VALUE_HPP

#include <hamon/serialization/detail/save_array.hpp>
#include <hamon/serialization/detail/save_arithmetic.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

namespace serialization
{

namespace detail
{

struct save_value_fn
{
private:
	template <typename Archive, typename T, typename = hamon::enable_if_t<std::is_array<T>::value>>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<2>)
	{
		hamon::serialization::save_array(ar, t);
	}
	template <typename Archive, typename T, typename = hamon::enable_if_t<std::is_arithmetic<T>::value>>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<1>)
	{
		hamon::serialization::save_arithmetic(ar, t);
	}
	template <typename Archive, typename T, typename = hamon::enable_if_t<std::is_enum<T>::value>>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<0>)
	{
		hamon::serialization::save_arithmetic(ar, static_cast<std::underlying_type_t<T>>(t));
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T const& t) const
	{
		impl(ar, t, hamon::detail::overload_priority<2>{});
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR detail::save_value_fn save_value{};

}	// inline namespace cpo

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_SAVE_VALUE_HPP
