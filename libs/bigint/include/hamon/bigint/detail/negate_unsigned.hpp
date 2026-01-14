/**
 *	@file	negate_unsigned.hpp
 *
 *	@brief	negate_unsigned 関数の定義
 */

#ifndef HAMON_BIGINT_DETAIL_NEGATE_UNSIGNED_HPP
#define HAMON_BIGINT_DETAIL_NEGATE_UNSIGNED_HPP

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename T, typename = hamon::enable_if_t<hamon::is_unsigned<T>::value>>
inline HAMON_CXX11_CONSTEXPR T
negate_unsigned(T x) HAMON_NOEXCEPT
{
	return static_cast<T>(~x + 1);
}

}	// namespace hamon

#endif // HAMON_BIGINT_DETAIL_NEGATE_UNSIGNED_HPP
