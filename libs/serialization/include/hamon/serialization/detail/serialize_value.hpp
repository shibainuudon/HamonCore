/**
 *	@file	serialize_value.hpp
 *
 *	@brief	serialize_valueの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_SERIALIZE_VALUE_HPP
#define HAMON_SERIALIZATION_DETAIL_SERIALIZE_VALUE_HPP

#include <hamon/serialization/detail/has_adl_serialize.hpp>
#include <hamon/serialization/detail/always_false.hpp>
#include <hamon/serialization/access.hpp>
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

struct serialize_value_fn
{
private:
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<access::has_member_serialize<Archive&, T&>::value>>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<2>)
	{
		access::serialize(ar, const_cast<T&>(t));
	}

	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_serialize<Archive&, T&>::value>>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<1>)
	{
		serialize(ar, const_cast<T&>(t));
	}

	template <typename Archive, typename T>
	static void impl(Archive&, T const&, hamon::detail::overload_priority<0>)
	{
		static_assert(always_false<T>::value, "This type is not serializable.");
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

HAMON_INLINE_VAR HAMON_CONSTEXPR detail::serialize_value_fn serialize_value{};

}	// inline namespace cpo

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_SERIALIZE_VALUE_HPP
