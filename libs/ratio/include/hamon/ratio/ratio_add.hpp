/**
 *	@file	ratio_add.hpp
 *
 *	@brief	ratio_add の定義
 */

#ifndef HAMON_RATIO_RATIO_ADD_HPP
#define HAMON_RATIO_RATIO_ADD_HPP

#include <hamon/ratio/config.hpp>

#if defined(HAMON_USE_STD_RATIO)

#include <ratio>

namespace hamon
{

using std::ratio_add;

}	// namespace hamon

#else

namespace hamon
{

// TODO

}	// namespace hamon

#endif

#endif // HAMON_RATIO_RATIO_ADD_HPP
