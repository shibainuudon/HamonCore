/**
 *	@file	endian.hpp
 *
 *	@brief	endian の定義
 */

#ifndef HAMON_BIT_ENDIAN_HPP
#define HAMON_BIT_ENDIAN_HPP

#include <hamon/config.hpp>

namespace hamon
{

// 22.11.10 Endian[bit.endian]

enum class endian
{
#if defined(HAMON_MSVC)

	little = 0,
	big    = 1,
#if defined(HAMON_LITTLE_ENDIAN)
	native = little
#elif defined(HAMON_BIG_ENDIAN)
	native = big
#else
	native = 2
#endif

#else

	little = __ORDER_LITTLE_ENDIAN__,
	big    = __ORDER_BIG_ENDIAN__,
	native = __BYTE_ORDER__

#endif
};

}	// namespace hamon

#endif // HAMON_BIT_ENDIAN_HPP
