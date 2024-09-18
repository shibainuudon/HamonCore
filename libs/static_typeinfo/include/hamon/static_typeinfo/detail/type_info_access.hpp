/**
 *	@file	type_info_access.hpp
 *
 *	@brief
 */

#ifndef HAMON_STATIC_TYPEINFO_DETAIL_TYPE_INFO_ACCESS_HPP
#define HAMON_STATIC_TYPEINFO_DETAIL_TYPE_INFO_ACCESS_HPP

#include <hamon/static_typeinfo/detail/type_info_access_fwd.hpp>
#include <hamon/static_typeinfo/static_type_info.hpp>
#include <hamon/string_view/string_view.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

class type_info_access
{
public:
	static HAMON_CONSTEXPR hamon::static_type_info
	make_type_info(hamon::string_view name) HAMON_NOEXCEPT
	{
		return {name};
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_STATIC_TYPEINFO_DETAIL_TYPE_INFO_ACCESS_HPP
