/**
 *	@file	erase.hpp
 *
 *	@brief	erase の定義
 */

#ifndef HAMON_INPLACE_VECTOR_ERASE_HPP
#define HAMON_INPLACE_VECTOR_ERASE_HPP

#include <hamon/inplace_vector/config.hpp>

#if defined(HAMON_USE_STD_INPLACE_VECTOR)

#include <inplace_vector>

namespace hamon
{

using std::erase;

}	// namespace hamon

#else

#include <hamon/inplace_vector/inplace_vector.hpp>
#include <hamon/algorithm/remove.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 23.3.14.6 Erasure[inplace.vector.erasure]

template <typename T, hamon::size_t N, typename U = T>
HAMON_CXX14_CONSTEXPR
typename hamon::inplace_vector<T, N>::size_type
erase(hamon::inplace_vector<T, N>& c, U const& value)
{
	using size_type = typename hamon::inplace_vector<T, N>::size_type;

	// [inplace.vector.erasure]/1
	auto it = hamon::remove(c.begin(), c.end(), value);
	auto r = hamon::distance(it, c.end());
	c.erase(it, c.end());
	return static_cast<size_type>(r);
}

}	// namespace hamon

#endif

#endif // HAMON_INPLACE_VECTOR_ERASE_HPP
