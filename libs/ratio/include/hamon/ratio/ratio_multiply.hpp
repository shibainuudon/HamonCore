/**
 *	@file	ratio_multiply.hpp
 *
 *	@brief	ratio_multiply の定義
 */

#ifndef HAMON_RATIO_RATIO_MULTIPLY_HPP
#define HAMON_RATIO_RATIO_MULTIPLY_HPP

#include <hamon/ratio/config.hpp>

#if defined(HAMON_USE_STD_RATIO)

#include <ratio>

namespace hamon
{

using std::ratio_multiply;

}	// namespace hamon

#else

namespace hamon
{

// TODO

}	// namespace hamon

#endif

#endif // HAMON_RATIO_RATIO_MULTIPLY_HPP
