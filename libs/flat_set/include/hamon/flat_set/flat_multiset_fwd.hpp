/**
 *	@file	flat_multiset_fwd.hpp
 *
 *	@brief	flat_multiset の前方宣言
 */

#ifndef HAMON_FLAT_SET_FLAT_MULTISET_FWD_HPP
#define HAMON_FLAT_SET_FLAT_MULTISET_FWD_HPP

#include <hamon/flat_set/config.hpp>

#if !defined(HAMON_USE_STD_FLAT_SET)

#include <hamon/functional/less.hpp>
#include <hamon/vector.hpp>

namespace hamon
{

// [flat.multiset], class template flat_multiset

template <typename Key, typename Compare = hamon::less<Key>, typename KeyContainer = hamon::vector<Key>>
class flat_multiset;

}	// namespace hamon

#endif

#endif // HAMON_FLAT_SET_FLAT_MULTISET_FWD_HPP
