/**
 *	@file	generate.hpp
 *
 *	@brief	generate の定義
 */

#ifndef HAMON_ALGORITHM_GENERATE_HPP
#define HAMON_ALGORITHM_GENERATE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::generate;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		出力の範囲へ関数の結果を書き込む
 *
 *	@tparam		ForwardIterator
 *	@tparam		Generator
 *
 *	@param		first
 *	@param		last
 *	@param		gen
 *
 *	@require	gen は引数を取らないこと。
 *
 *	@effect		[first,last) のそれぞれのイテレータについて
 *				関数オブジェクト gen を呼び出し、その戻り値を代入する。
 *
 *	@complexity	正確に last - first 回の gen の呼び出しと代入が行われる。
 */
template <typename ForwardIterator, typename Generator>
inline HAMON_CXX14_CONSTEXPR void
generate(ForwardIterator first, ForwardIterator last, Generator gen)
{
	while (first != last)
	{
		*first++ = gen();
	}
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_GENERATE_HPP
