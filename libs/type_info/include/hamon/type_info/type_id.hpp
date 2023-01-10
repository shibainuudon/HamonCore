/**
 *	@file	type_id.hpp
 *
 *	@brief
 */

#ifndef HAMON_TYPE_INFO_TYPE_ID_HPP
#define HAMON_TYPE_INFO_TYPE_ID_HPP

#include <hamon/type_info/type_info.hpp>
#include <hamon/type_info/nameof.hpp>
#include <hamon/type_info/detail/type_info_access.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

template <typename T>
HAMON_NODISCARD HAMON_CONSTEXPR hamon::type_info
type_id() HAMON_NOEXCEPT
{
	return detail::type_info_access::make_type_info(hamon::nameof<T>());
}

template <typename T>
HAMON_NODISCARD HAMON_CONSTEXPR hamon::type_info
type_id(T&&) HAMON_NOEXCEPT
{
	return type_id<typename std::decay<T>::type>();
}

}	// namespace hamon

#endif // HAMON_TYPE_INFO_TYPE_ID_HPP
