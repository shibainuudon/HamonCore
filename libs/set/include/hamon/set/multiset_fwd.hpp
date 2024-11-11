/**
 *	@file	multiset_fwd.hpp
 *
 *	@brief	multiset の前方宣言
 */

#ifndef HAMON_SET_MULTISET_FWD_HPP
#define HAMON_SET_MULTISET_FWD_HPP

#include <hamon/set/config.hpp>

#if defined(HAMON_USE_STD_MULTISET)

#include <set>

namespace hamon
{

using std::multiset;

}	// namespace hamon

#else

#include <hamon/functional/less.hpp>
#include <hamon/memory/allocator.hpp>

namespace hamon
{

// [multiset], class template multiset
template <
	typename Key,
	typename Compare = hamon::less<Key>,
	typename Allocator = hamon::allocator<Key>>
class multiset;

}	// namespace hamon

#endif

#endif // HAMON_SET_MULTISET_FWD_HPP
