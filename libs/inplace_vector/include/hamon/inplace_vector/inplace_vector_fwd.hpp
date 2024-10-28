/**
 *	@file	inplace_vector_fwd.hpp
 *
 *	@brief	inplace_vector の前方宣言
 */

#ifndef HAMON_INPLACE_VECTOR_INPLACE_VECTOR_FWD_HPP
#define HAMON_INPLACE_VECTOR_INPLACE_VECTOR_FWD_HPP

#if defined(HAMON_USE_STD_INPLACE_VECTOR)

#include <inplace_vector>

namespace hamon
{

using std::inplace_vector;

}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>

namespace hamon
{

// [inplace.vector], class template inplace_vector
template <typename T, hamon::size_t N>
class inplace_vector;

}	// namespace hamon

#endif

#endif // HAMON_INPLACE_VECTOR_INPLACE_VECTOR_FWD_HPP
