/**
 *	@file	static_typeid.hpp
 *
 *	@brief
 */

#ifndef HAMON_STATIC_TYPEINFO_STATIC_TYPEID_HPP
#define HAMON_STATIC_TYPEINFO_STATIC_TYPEID_HPP

#include <hamon/static_typeinfo/static_type_info.hpp>
#include <hamon/static_typeinfo/nameof.hpp>
#include <hamon/static_typeinfo/detail/type_info_access.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename T>
HAMON_NODISCARD HAMON_CONSTEXPR hamon::static_type_info
static_typeid() HAMON_NOEXCEPT
{
	return detail::type_info_access::make_type_info(hamon::nameof<T>());
}

template <typename T>
HAMON_NODISCARD HAMON_CONSTEXPR hamon::static_type_info
static_typeid(T&&) HAMON_NOEXCEPT
{
	return static_typeid<hamon::decay_t<T>>();
}

}	// namespace hamon

#endif // HAMON_STATIC_TYPEINFO_STATIC_TYPEID_HPP
