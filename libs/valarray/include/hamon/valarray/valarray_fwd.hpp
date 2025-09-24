/**
 *	@file	valarray_fwd.hpp
 *
 *	@brief	valarray の前方宣言
 */

#ifndef HAMON_VALARRAY_VALARRAY_FWD_HPP
#define HAMON_VALARRAY_VALARRAY_FWD_HPP

#include <hamon/valarray/config.hpp>

#if defined(HAMON_USE_STD_VALARRAY)

#include <valarray>

namespace hamon
{

using std::valarray;

}	// namespace hamon

#else

namespace hamon
{

template <typename T>
class valarray;

}	// namespace hamon

#endif

#endif // HAMON_VALARRAY_VALARRAY_FWD_HPP
