/**
 *	@file	lexicographical_compare.hpp
 *
 *	@brief	lexicographical_compare の定義
 */

#ifndef HAMON_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP
#define HAMON_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::lexicographical_compare;

}	// namespace hamon

#else

#include <hamon/functional/less.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	2つの範囲を辞書式順序で比較する
 *
 *	@tparam	InputIterator1
 *	@tparam	InputIterator2
 *	@tparam	Compare
 *
 *	@param	first1
 *	@param	last1
 *	@param	first2
 *	@param	last2
 *	@param	comp
 *
 *	@return		範囲[first1, last1)が辞書式比較で範囲[first2, last2)より小さい場合trueを返す。
 *				そうでなければfalseを返す
 *
 *	@complexity	高々2*min((last1 - first1), (last2 - first2))回の比較が行われる。
 *
 *	@note		空のシーケンスは、空じゃないシーケンスより小さいと判断されるが、
 *				空のシーケンスに対しては小さくないと判断される。
 *				どちらかのシーケンスの横断が先に終わる場合(つまり、範囲の長さが合わない場合)、
 *				先に終わった方が小さいと判断される。
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename Compare
>
inline HAMON_CXX11_CONSTEXPR bool
lexicographical_compare(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	Compare comp)
{
#if defined(HAMON_HAS_CXX14_CONSTEXPR)
	for (; first2 != last2; ++first1, (void) ++first2)
	{
		if (first1 == last1 || comp(*first1, *first2))
		{
			return true;
		}

		if (comp(*first2, *first1))
		{
			return false;
		}
	}

	return false;
#else
	return
		first2 == last2 ?
			false :
		(first1 == last1 || comp(*first1, *first2)) ?
			true :
		(comp(*first2, *first1)) ?
			false :
		hamon::lexicographical_compare(
			hamon::next(first1), last1,
			hamon::next(first2), last2,
			comp);
#endif
}

/**
 *	@brief	2つの範囲を辞書式順序で比較する
 *
 *	@tparam	InputIterator1
 *	@tparam	InputIterator2
 *
 *	@param	first1
 *	@param	last1
 *	@param	first2
 *	@param	last2
 *
 *	@return		範囲[first1, last1)が辞書式比較で範囲[first2, last2)より小さい場合trueを返す。
 *				そうでなければfalseを返す
 *
 *	@complexity	高々2*min((last1 - first1), (last2 - first2))回の比較が行われる。
 *
 *	@note		空のシーケンスは、空じゃないシーケンスより小さいと判断されるが、
 *				空のシーケンスに対しては小さくないと判断される。
 *				どちらかのシーケンスの横断が先に終わる場合(つまり、範囲の長さが合わない場合)、
 *				先に終わった方が小さいと判断される。
 */
template <
	typename InputIterator1,
	typename InputIterator2
>
inline HAMON_CXX11_CONSTEXPR bool
lexicographical_compare(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2)
{
	return hamon::lexicographical_compare(
		first1, last1, first2, last2, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP
