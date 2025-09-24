/**
 *	@file	slice_fwd.hpp
 *
 *	@brief	slice の前方宣言
 */

#ifndef HAMON_VALARRAY_SLICE_FWD_HPP
#define HAMON_VALARRAY_SLICE_FWD_HPP

#include <hamon/valarray/config.hpp>

#if defined(HAMON_USE_STD_VALARRAY)

#include <valarray>

namespace hamon
{

using std::slice;

}	// namespace hamon

#else

namespace hamon
{

class slice;

}	// namespace hamon

#endif

#endif // HAMON_VALARRAY_SLICE_FWD_HPP
