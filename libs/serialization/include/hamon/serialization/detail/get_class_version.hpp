/**
 *	@file	get_class_version.hpp
 *
 *	@brief	get_class_versionの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_GET_CLASS_VERSION_HPP
#define HAMON_SERIALIZATION_DETAIL_GET_CLASS_VERSION_HPP

#include <hamon/serialization/detail/has_adl_get_class_version.hpp>
#include <hamon/serialization/access.hpp>
#include <hamon/serialization/version.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace get_class_version_detail
{

struct get_class_version_fn
{
private:
	// t.get_class_version();
	template <typename T,
		typename = hamon::enable_if_t<access::has_member_get_class_version<T const&>::value>>
	static version_t impl(T const& t, hamon::detail::overload_priority<2>)
	{
		return access::get_class_version(t);
	}

	// get_class_version(t);
	template <typename T,
		typename = hamon::enable_if_t<has_adl_get_class_version<T const&>::value>>
	static version_t impl(T const& t, hamon::detail::overload_priority<1>)
	{
		return static_cast<version_t>(get_class_version(t));
	}

	// fallback
	template <typename T>
	static version_t impl(T const&, hamon::detail::overload_priority<0>)
	{
		return 0;
	}

public:
	template <typename T>
	version_t operator()(T const& t) const
	{
		return impl(t, hamon::detail::overload_priority<2>{});
	}
};

}	// namespace get_class_version_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
get_class_version_detail::get_class_version_fn get_class_version{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_GET_CLASS_VERSION_HPP
