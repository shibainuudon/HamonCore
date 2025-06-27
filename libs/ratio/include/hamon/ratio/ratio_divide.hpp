/**
 *	@file	ratio_divide.hpp
 *
 *	@brief	ratio_divide の定義
 */

#ifndef HAMON_RATIO_RATIO_DIVIDE_HPP
#define HAMON_RATIO_RATIO_DIVIDE_HPP

#include <hamon/ratio/config.hpp>

#if defined(HAMON_USE_STD_RATIO)

#include <ratio>

namespace hamon
{

using std::ratio_divide;

}	// namespace hamon

#else

namespace hamon
{

// TODO

}	// namespace hamon

#endif

#endif // HAMON_RATIO_RATIO_DIVIDE_HPP
