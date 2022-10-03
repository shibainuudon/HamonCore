/**
 *	@file	max_size_type.hpp
 *
 *	@brief	max_size_type の定義
 */

#ifndef HAMON_RANGES_DETAIL_MAX_SIZE_TYPE_HPP
#define HAMON_RANGES_DETAIL_MAX_SIZE_TYPE_HPP

namespace hamon
{

namespace ranges
{

namespace detail
{

#if __SIZEOF_INT128__

using max_size_type = unsigned __int128;

#else

using max_size_type = unsigned long long;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_MAX_SIZE_TYPE_HPP
