/**
 *	@file	is_sorted.hpp
 *
 *	@brief	is_sorted の定義
 */

#ifndef HAMON_ALGORITHM_IS_SORTED_HPP
#define HAMON_ALGORITHM_IS_SORTED_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::is_sorted;

}	// namespace hamon

#else

#include <hamon/algorithm/is_sorted_until.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		与えられた範囲がソート済みか判定する
 *
 *	@tparam		ForwardIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@return		is_sorted_until(first, last, comp) == last
 *
 *	@complexity	線形時間
 */
template <typename ForwardIterator, typename Compare>
inline HAMON_CXX14_CONSTEXPR bool
is_sorted(ForwardIterator first, ForwardIterator last, Compare comp)
{
	return hamon::is_sorted_until(first, last, comp) == last;
}

/**
 *	@brief		与えられた範囲がソート済みか判定する
 *
 *	@tparam		ForwardIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@return		is_sorted_until(first, last) == last
 *
 *	@complexity	線形時間
 */
template <typename ForwardIterator>
inline HAMON_CXX14_CONSTEXPR bool
is_sorted(ForwardIterator first, ForwardIterator last)
{
	return hamon::is_sorted(first, last, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_IS_SORTED_HPP
