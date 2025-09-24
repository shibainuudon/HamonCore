/**
 *	@file	mask_array_fwd.hpp
 *
 *	@brief	mask_array の前方宣言
 */

#ifndef HAMON_VALARRAY_MASK_ARRAY_FWD_HPP
#define HAMON_VALARRAY_MASK_ARRAY_FWD_HPP

#include <hamon/valarray/config.hpp>

#if defined(HAMON_USE_STD_VALARRAY)

#include <valarray>

namespace hamon
{

using std::mask_array;

}	// namespace hamon

#else

namespace hamon
{

template <typename T>
class mask_array;

}	// namespace hamon

#endif

#endif // HAMON_VALARRAY_MASK_ARRAY_FWD_HPP
