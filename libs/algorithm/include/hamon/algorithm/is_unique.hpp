/**
 *	@file	is_unique.hpp
 *
 *	@brief	is_unique 関数の定義
 */

#ifndef HAMON_ALGORITHM_IS_UNIQUE_HPP
#define HAMON_ALGORITHM_IS_UNIQUE_HPP

#include <hamon/algorithm/adjacent_find.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		与えられた範囲に重複した要素がないかどうか取得する
 *
 *	@tparam		ForwardIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@return		与えられた範囲に重複した要素がなければtrue
 *
 *	@complexity
 */
template <typename ForwardIterator>
inline HAMON_CONSTEXPR bool
is_unique(ForwardIterator first, ForwardIterator last)
{
	return hamon::adjacent_find(first, last) == last;
}

/**
 *	@brief		与えられた範囲に重複した要素がないかどうか取得する
 *
 *	@tparam		ForwardIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@return		与えられた範囲に重複した要素がなければtrue
 *
 *	@complexity
 */
template <typename ForwardIterator, typename Compare>
inline HAMON_CONSTEXPR bool
is_unique(ForwardIterator first, ForwardIterator last, Compare comp)
{
	return hamon::adjacent_find(first, last, comp) == last;
}

}	// namespace hamon

#endif // HAMON_ALGORITHM_IS_UNIQUE_HPP
