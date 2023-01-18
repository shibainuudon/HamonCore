/**
 *	@file	generate_n.hpp
 *
 *	@brief	generate_n の定義
 */

#ifndef HAMON_ALGORITHM_GENERATE_N_HPP
#define HAMON_ALGORITHM_GENERATE_N_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::generate_n;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		出力の範囲へ関数の結果を n 個書き込む
 *
 *	@tparam		OutputIterator
 *	@tparam		Size
 *	@tparam		Generator
 *
 *	@param		first
 *	@param		n
 *	@param		gen
 *
 *	@require	gen は引数を取らないこと。
 *				Size は integral type に変換可能であること。
 *
 *	@return		n が 1 以上の場合、first + n が返される。
 *				そうでない場合、first が返される。
 *
 *	@effect		n が 1 以上の場合、[first,first+n) のそれぞれのイテレータについて
 *				関数オブジェクト gen を呼び出し、その戻り値を代入する。
 *				そうでない場合、何もしない。
 *
 *	@complexity	n が 1 以上の場合、n 回の gen の呼び出しと代入が行われる。
 *				そうでない場合、何もしない。
 */
template <
	typename OutputIterator,
	typename Size,
	typename Generator
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
generate_n(OutputIterator first, Size n, Generator gen)
{
	while (n-- > 0)
	{
		*first++ = gen();
	}

	return first;
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_GENERATE_N_HPP
