/**
 *	@file	endian.hpp
 *
 *	@brief	endian の定義
 */

#ifndef HAMON_BIT_ENDIAN_HPP
#define HAMON_BIT_ENDIAN_HPP

#include <hamon/bit/config.hpp>

#if defined(HAMON_HAS_CXX_LIB_ENDIAN)

#include <bit>

namespace hamon
{

using std::endian;

}	// namespace hamon

#else

namespace hamon
{

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

#endif

#endif // HAMON_BIT_ENDIAN_HPP
