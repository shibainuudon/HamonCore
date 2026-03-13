/**
 *	@file	move.hpp
 *
 *	@brief	move 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_MOVE_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_MOVE_HPP

#include <hamon/inplace_vector.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{
namespace detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR void
move(T& out, T& src)
{
	out = hamon::move(src);
}

/**
 *	inplace_vector をムーブ代入すると、clangでC++20のときにconstexprにできない。
 *	inplace_vector の m_value が初期化されていないという理由でconstexprにできないのだが、
 *	デフォルトコンストラクタで初期化されるはずなのでclangのバグではないかという気がする。
 *	(実際にgccやMSVCではconstexprにできている)
 *
 *	仕方がないので、inplace_vector のときは手動でsize()ぶんだけムーブするようにしたら
 *	constexprにできるようになった。
 */
template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR void
move(hamon::inplace_vector<T, N>& out, hamon::inplace_vector<T, N>& src)
{
	auto n = src.size();
	out.resize(n);
	auto p1 = out.data();
	auto p2 = src.data();
	for (; n != 0; --n)
	{
		*p1++ = *p2++;
	}
}

}	// namespace detail
}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_MOVE_HPP
