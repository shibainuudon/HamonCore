/**
 *	@file	set_fwd.hpp
 *
 *	@brief	set の前方宣言
 */

#ifndef HAMON_SET_SET_FWD_HPP
#define HAMON_SET_SET_FWD_HPP

#include <hamon/set/config.hpp>

#if defined(HAMON_USE_STD_SET)

#include <set>

namespace hamon
{

using std::set;

}	// namespace hamon

#else

#include <hamon/functional/less.hpp>
#include <hamon/memory/allocator.hpp>

namespace hamon
{

// [set], class template set
template <
	typename Key,
	typename Compare = hamon::less<Key>,
	typename Allocator = hamon::allocator<Key>>
class set;

}	// namespace hamon

#endif

#endif // HAMON_SET_SET_FWD_HPP
