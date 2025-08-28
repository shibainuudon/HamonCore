/**
 *	@file	__complement.hpp
 *
 *	@brief	__complement の定義
 */

#ifndef HAMON_FORMAT_OTHER___COMPLEMENT_HPP
#define HAMON_FORMAT_OTHER___COMPLEMENT_HPP

#include <hamon/type_traits/is_unsigned.hpp>

namespace hamon
{

template <typename _Tp>
inline constexpr _Tp
__complement(_Tp __x)
{
	static_assert(hamon::is_unsigned<_Tp>::value, "cast to unsigned first");
	return _Tp(~__x + 1);
}

}	// namespace hamon

#endif // HAMON_FORMAT_OTHER___COMPLEMENT_HPP
