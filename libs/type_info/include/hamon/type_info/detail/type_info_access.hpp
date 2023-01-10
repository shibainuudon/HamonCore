/**
 *	@file	type_info_access.hpp
 *
 *	@brief
 */

#ifndef HAMON_TYPE_INFO_DETAIL_TYPE_INFO_ACCESS_HPP
#define HAMON_TYPE_INFO_DETAIL_TYPE_INFO_ACCESS_HPP

#include <hamon/type_info/detail/type_info_access_fwd.hpp>
#include <hamon/type_info/type_info.hpp>
#include <hamon/string_view/string_view.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

class type_info_access
{
public:
	static HAMON_CONSTEXPR hamon::type_info
	make_type_info(hamon::string_view name) HAMON_NOEXCEPT
	{
		return {name};
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_TYPE_INFO_DETAIL_TYPE_INFO_ACCESS_HPP
