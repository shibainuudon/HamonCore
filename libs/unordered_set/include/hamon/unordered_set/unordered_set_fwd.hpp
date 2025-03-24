/**
 *	@file	unordered_set_fwd.hpp
 *
 *	@brief	unordered_set の前方宣言
 */

#ifndef HAMON_UNORDERED_SET_UNORDERED_SET_FWD_HPP
#define HAMON_UNORDERED_SET_UNORDERED_SET_FWD_HPP

#include <hamon/unordered_set/config.hpp>

#if defined(HAMON_USE_STD_UNORDERED_SET)

#include <unordered_set>

namespace hamon
{

using std::unordered_set;

}	// namespace hamon

#else

#include <hamon/functional/hash.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/memory/allocator.hpp>

namespace hamon
{

// [unord.set], class template unordered_set
template <
	typename Key,
	typename Hash = hamon::hash<Key>,
	typename Pred = hamon::equal_to<Key>,
	typename Alloc = hamon::allocator<Key>
>
class unordered_set;

}	// namespace hamon

#endif

#endif // HAMON_UNORDERED_SET_UNORDERED_SET_FWD_HPP
