﻿/**
 *	@file	serialize_value.hpp
 *
 *	@brief	serialize_valueの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_SERIALIZE_VALUE_HPP
#define HAMON_SERIALIZATION_DETAIL_SERIALIZE_VALUE_HPP

#include <hamon/serialization/detail/has_adl_serialize.hpp>
#include <hamon/serialization/detail/always_false.hpp>
#include <hamon/serialization/access.hpp>
#include <hamon/serialization/version.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_empty.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace serialize_value_detail
{

struct serialize_value_fn
{
private:
	// t.serialize(ar, version);
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<access::has_member_serialize<Archive&, T&, version_t>::value>>
	static void impl(Archive& ar, T const& t, version_t version, hamon::detail::overload_priority<5>)
	{
		access::serialize(ar, const_cast<T&>(t), version);
	}

	// t.serialize(ar);
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<access::has_member_serialize<Archive&, T&>::value>>
	static void impl(Archive& ar, T const& t, version_t, hamon::detail::overload_priority<4>)
	{
		access::serialize(ar, const_cast<T&>(t));
	}

	// serialize(ar, t, version);
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_serialize<Archive&, T&, version_t>::value>>
	static void impl(Archive& ar, T const& t, version_t version, hamon::detail::overload_priority<3>)
	{
		serialize(ar, const_cast<T&>(t), version);
	}

	// serialize(ar, t);
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_serialize<Archive&, T&>::value>>
	static void impl(Archive& ar, T const& t, version_t, hamon::detail::overload_priority<2>)
	{
		serialize(ar, const_cast<T&>(t));
	}

	// 空のクラス
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<hamon::is_empty<T>::value>>
	static void impl(Archive&, T const&, version_t, hamon::detail::overload_priority<1>)
	{
		// save,load,serialize等が定義されておらず、
		// 空のクラスのときは何もしない
	}

	// fallback
	template <typename Archive, typename T>
	static void impl(Archive&, T const&, version_t, hamon::detail::overload_priority<0>)
	{
		static_assert(always_false<T>::value, "This type is not serializable.");
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T const& t, version_t version) const
	{
		impl(ar, t, version, hamon::detail::overload_priority<5>{});
	}
};

}	// namespace serialize_value_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
serialize_value_detail::serialize_value_fn serialize_value{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_SERIALIZE_VALUE_HPP
