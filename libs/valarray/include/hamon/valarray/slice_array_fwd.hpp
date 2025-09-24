/**
 *	@file	slice_array_fwd.hpp
 *
 *	@brief	slice_array の前方宣言
 */

#ifndef HAMON_VALARRAY_SLICE_ARRAY_FWD_HPP
#define HAMON_VALARRAY_SLICE_ARRAY_FWD_HPP

#include <hamon/valarray/config.hpp>

#if defined(HAMON_USE_STD_VALARRAY)

#include <valarray>

namespace hamon
{

using std::slice_array;

}	// namespace hamon

#else

namespace hamon
{

template <typename T>
class slice_array;

}	// namespace hamon

#endif

#endif // HAMON_VALARRAY_SLICE_ARRAY_FWD_HPP
