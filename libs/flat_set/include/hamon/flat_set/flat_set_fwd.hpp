/**
 *	@file	flat_set_fwd.hpp
 *
 *	@brief	flat_set の前方宣言
 */

#ifndef HAMON_FLAT_SET_FLAT_SET_FWD_HPP
#define HAMON_FLAT_SET_FLAT_SET_FWD_HPP

#include <hamon/flat_set/config.hpp>

#if !defined(HAMON_USE_STD_FLAT_SET)

#include <hamon/functional/less.hpp>
#include <hamon/vector.hpp>

namespace hamon
{

// [flat.set], class template flat_set

template <typename Key, typename Compare = hamon::less<Key>, typename KeyContainer = hamon::vector<Key>>
class flat_set;

}	// namespace hamon

#endif

#endif // HAMON_FLAT_SET_FLAT_SET_FWD_HPP
