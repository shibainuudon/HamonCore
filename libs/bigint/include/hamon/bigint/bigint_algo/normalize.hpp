/**
 *	@file	normalize.hpp
 *
 *	@brief	normalize 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_NORMALIZE_HPP
#define HAMON_BIGINT_BIGINT_ALGO_NORMALIZE_HPP

#include <hamon/bigint/bigint_algo/detail/zero.hpp>
#include <hamon/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

/**
 *	正規化
 *  ・末尾の0を取り除く
 *  ・空の場合は {0} を返す
 */
template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR void
normalize(VectorType& vec)
{
	auto n = vec.size();
	if (n == 0)
	{
		detail::zero(vec);
		return;
	}

	auto p = vec.data();
	for (; n > 1; --n)
	{
		if (p[n - 1] != 0)
		{
			break;
		}
	}

	vec.resize(n);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR void
normalize(hamon::array<T, N>&)
{
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_NORMALIZE_HPP
