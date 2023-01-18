/**
 *	@file	lexicographical_compare_three_way.hpp
 *
 *	@brief	lexicographical_compare_three_way の定義
 */

#ifndef HAMON_ALGORITHM_LEXICOGRAPHICAL_COMPARE_THREE_WAY_HPP
#define HAMON_ALGORITHM_LEXICOGRAPHICAL_COMPARE_THREE_WAY_HPP

#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

#include <hamon/algorithm/config.hpp>
#include <hamon/compare/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM) && defined(HAMON_USE_STD_COMPARE)

#include <algorithm>

namespace hamon
{

using std::lexicographical_compare_three_way;

}	// namespace hamon

#else

#include <hamon/compare/compare_three_way.hpp>
#include <hamon/compare/strong_ordering.hpp>

namespace hamon
{

template <typename InputIter1, typename InputIter2, typename Comp>
inline HAMON_CXX14_CONSTEXPR auto
lexicographical_compare_three_way(
	InputIter1 first1, InputIter1 last1,
	InputIter2 first2, InputIter2 last2,
	Comp comp)
-> decltype(comp(*first1, *first2))
{
	while (first1 != last1)
	{
		if (first2 == last2)
		{
			return hamon::strong_ordering::greater;
		}

		if (auto cmp = comp(*first1, *first2); cmp != 0)
		{
			return cmp;
		}

		++first1;
		++first2;
	}

	return (first2 == last2) <=> true;
}

template <typename InputIter1, typename InputIter2>
inline HAMON_CXX14_CONSTEXPR auto
lexicographical_compare_three_way(
	InputIter1 first1, InputIter1 last1,
	InputIter2 first2, InputIter2 last2)
{
	return hamon::lexicographical_compare_three_way(
		first1, last1, first2, last2, hamon::compare_three_way{});
}

}	// namespace hamon

#endif

#endif

#endif // HAMON_ALGORITHM_LEXICOGRAPHICAL_COMPARE_THREE_WAY_HPP
