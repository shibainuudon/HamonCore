/**
 *	@file	max_diff_type.hpp
 *
 *	@brief	max_diff_type の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_MAX_DIFF_TYPE_HPP
#define HAMON_CONCEPTS_DETAIL_MAX_DIFF_TYPE_HPP

namespace hamon
{

namespace ranges
{

namespace detail
{

#if __SIZEOF_INT128__

using max_diff_type = __int128;

#else

using max_diff_type = long long;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_MAX_DIFF_TYPE_HPP
