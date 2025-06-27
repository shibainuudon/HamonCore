/**
 *	@file	ratio_subtract.hpp
 *
 *	@brief	ratio_subtract の定義
 */

#ifndef HAMON_RATIO_RATIO_SUBTRACT_HPP
#define HAMON_RATIO_RATIO_SUBTRACT_HPP

#include <hamon/ratio/config.hpp>

#if defined(HAMON_USE_STD_RATIO)

#include <ratio>

namespace hamon
{

using std::ratio_subtract;

}	// namespace hamon

#else

namespace hamon
{

// TODO

}	// namespace hamon

#endif

#endif // HAMON_RATIO_RATIO_SUBTRACT_HPP
