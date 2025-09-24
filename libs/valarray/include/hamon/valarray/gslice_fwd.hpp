/**
 *	@file	gslice_fwd.hpp
 *
 *	@brief	gslice の前方宣言
 */

#ifndef HAMON_VALARRAY_GSLICE_FWD_HPP
#define HAMON_VALARRAY_GSLICE_FWD_HPP

#include <hamon/valarray/config.hpp>

#if defined(HAMON_USE_STD_VALARRAY)

#include <valarray>

namespace hamon
{

using std::gslice;

}	// namespace hamon

#else

namespace hamon
{

class gslice;

}	// namespace hamon

#endif

#endif // HAMON_VALARRAY_GSLICE_FWD_HPP
