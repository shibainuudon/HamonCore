/**
 *	@file	copy.hpp
 *
 *	@brief	copy 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_COPY_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_COPY_HPP

#include <hamon/inplace_vector.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{
namespace detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR void
copy(T& out, T const& src)
{
	out = src;
}

/**
 *	inplace_vector をコピー代入すると、clangでC++20のときにconstexprにできない。
 *	inplace_vector の m_value が初期化されていないという理由でconstexprにできないのだが、
 *	デフォルトコンストラクタで初期化されるはずなのでclangのバグではないかという気がする。
 *	(実際にgccやMSVCではconstexprにできている)
 *
 *	仕方がないので、inplace_vector のときは手動でsize()ぶんだけコピーするようにしたら
 *	constexprにできるようになった。
 */
template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR void
copy(hamon::inplace_vector<T, N>& out, hamon::inplace_vector<T, N> const& src)
{
	out.resize(src.size());
	for (hamon::size_t i = 0; i < src.size(); ++i)
	{
		out[i] = src[i];
	}
}

}	// namespace detail
}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_COPY_HPP
