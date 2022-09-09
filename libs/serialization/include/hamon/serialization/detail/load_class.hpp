/**
 *	@file	load_class.hpp
 *
 *	@brief	load_classの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_LOAD_CLASS_HPP
#define HAMON_SERIALIZATION_DETAIL_LOAD_CLASS_HPP

#include <hamon/serialization/detail/has_adl_load_class.hpp>
#include <hamon/serialization/detail/has_adl_load.hpp>
#include <hamon/serialization/detail/serialize_value.hpp>
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

struct load_class_fn
{
private:
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_load_class<Archive, T>::value>>
	static void impl(Archive& ar, T& t, hamon::detail::overload_priority<3>)
	{
		load_class(ar, t);
	}

	template <typename Archive, typename T,
		typename = hamon::enable_if_t<access::has_member_load<Archive&, T&>::value>>
	static void impl(Archive& ar, T& t, hamon::detail::overload_priority<2>)
	{
		access::load(ar, t);
	}

	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_load<Archive&, T&>::value>>
	static void impl(Archive& ar, T& t, hamon::detail::overload_priority<1>)
	{
		load(ar, t);
	}

	template <typename Archive, typename T>
	static void impl(Archive& ar, T& t, hamon::detail::overload_priority<0>)
	{
		hamon::serialization::serialize_value(ar, t);
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T& t) const
	{
		impl(ar, t, hamon::detail::overload_priority<3>{});
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR detail::load_class_fn load_class{};

}	// inline namespace cpo

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_LOAD_CLASS_HPP
