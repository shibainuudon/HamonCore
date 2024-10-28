/**
 *	@file	erase_if.hpp
 *
 *	@brief	erase_if の定義
 */

#ifndef HAMON_INPLACE_VECTOR_ERASE_IF_HPP
#define HAMON_INPLACE_VECTOR_ERASE_IF_HPP

#include <hamon/inplace_vector/config.hpp>

#if defined(HAMON_USE_STD_INPLACE_VECTOR)

#include <inplace_vector>

namespace hamon
{

using std::erase_if;

}	// namespace hamon

#else

#include <hamon/inplace_vector/inplace_vector.hpp>
#include <hamon/algorithm/remove_if.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 23.3.14.6 Erasure[inplace.vector.erasure]

template <typename T, hamon::size_t N, typename Predicate>
HAMON_CXX14_CONSTEXPR
typename hamon::inplace_vector<T, N>::size_type
erase_if(hamon::inplace_vector<T, N>& c, Predicate pred)
{
	using size_type = typename hamon::inplace_vector<T, N>::size_type;

	// [inplace.vector.erasure]/2
	auto it = hamon::remove_if(c.begin(), c.end(), pred);
	auto r = hamon::distance(it, c.end());
	c.erase(it, c.end());
	return static_cast<size_type>(r);
}

}	// namespace hamon

#endif

#endif // HAMON_INPLACE_VECTOR_ERASE_IF_HPP
