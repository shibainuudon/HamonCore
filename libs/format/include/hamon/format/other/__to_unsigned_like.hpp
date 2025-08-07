/**
 *	@file	__to_unsigned_like.hpp
 *
 *	@brief	__to_unsigned_like の定義
 */

#ifndef HAMON_FORMAT_OTHER___TO_UNSIGNED_LIKE_HPP
#define HAMON_FORMAT_OTHER___TO_UNSIGNED_LIKE_HPP

#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <class _Tp>
constexpr hamon::make_unsigned_t<_Tp>
__to_unsigned_like(_Tp __x) HAMON_NOEXCEPT
{
	return static_cast<hamon::make_unsigned_t<_Tp>>(__x);
}

}	// namespace hamon

#endif // HAMON_FORMAT_OTHER___TO_UNSIGNED_LIKE_HPP
