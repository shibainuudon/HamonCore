/**
 *	@file	load.hpp
 *
 *	@brief	loadの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_LOAD_HPP
#define HAMON_SERIALIZATION_DETAIL_LOAD_HPP

#include <hamon/serialization/detail/has_adl_load.hpp>
#include <hamon/serialization/detail/serialize_value.hpp>
#include <hamon/serialization/access.hpp>
#include <hamon/serialization/version.hpp>
#include <hamon/serialization/nvp.hpp>
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

struct load_fn
{
private:
	// t.load(ar, version);
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<access::has_member_load<Archive&, T&, version_t>::value>>
	static void impl(Archive& ar, T& t, version_t version, hamon::detail::overload_priority<4>)
	{
		access::load(ar, t, version);
	}

	// t.load(ar);
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<access::has_member_load<Archive&, T&>::value>>
	static void impl(Archive& ar, T& t, version_t, hamon::detail::overload_priority<3>)
	{
		access::load(ar, t);
	}

	// load(ar, t, version);
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_load<Archive&, T&, version_t>::value>>
	static void impl(Archive& ar, T& t, version_t version, hamon::detail::overload_priority<2>)
	{
		load(ar, t, version);
	}

	// load(ar, t);
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_load<Archive&, T&>::value>>
	static void impl(Archive& ar, T& t, version_t, hamon::detail::overload_priority<1>)
	{
		load(ar, t);
	}

	// serialize_value
	template <typename Archive, typename T>
	static void impl(Archive& ar, T& t, version_t version, hamon::detail::overload_priority<0>)
	{
		hamon::serialization::serialize_value(ar, t, version);
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T& t, version_t version) const
	{
		impl(ar, t, version, hamon::detail::overload_priority<4>{});
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR detail::load_fn load{};

}	// inline namespace cpo

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_LOAD_HPP
