/**
 *	@file	load_class.hpp
 *
 *	@brief	load_classの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_LOAD_CLASS_HPP
#define HAMON_SERIALIZATION_DETAIL_LOAD_CLASS_HPP

#include <hamon/serialization/detail/has_adl_load.hpp>
#include <hamon/serialization/detail/serialize_value.hpp>
#include <hamon/serialization/detail/load_class_version.hpp>
#include <hamon/serialization/access.hpp>
#include <hamon/serialization/version.hpp>
#include <hamon/serialization/nvp.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace serialization
{

namespace detail
{

template <typename Archive>
void start_load_class(Archive&)
{
}

template <typename Archive>
void end_load_class(Archive&)
{
}

namespace load_class_detail
{

struct load_class_fn
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
		hamon::serialization::detail::serialize_value(ar, t, version);
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T& t) const
	{
		start_load_class(ar);
		auto const version = hamon::serialization::detail::load_class_version(ar, t);
		impl(ar, t, version, hamon::detail::overload_priority<4>{});
		end_load_class(ar);
	}
};

}	// namespace load_class_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR load_class_detail::load_class_fn load_class{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_LOAD_CLASS_HPP
