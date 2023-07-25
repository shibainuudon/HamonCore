/**
 *	@file	normalize.hpp
 *
 *	@brief	normalize 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_NORMALIZE_HPP
#define HAMON_BIGINT_BIGINT_ALGO_NORMALIZE_HPP

#include <hamon/config.hpp>
#include <vector>

namespace hamon
{
namespace bigint_algo
{

/**
 *	正規化
 *  ・末尾の0を取り除く
 *  ・空の場合は {0} を返す
 */
template <typename T>
inline void
normalize(std::vector<T>& vec)
{
	auto n = vec.size();
	if (n == 0)
	{
		vec.resize(1);
		vec[0] = 0;
		return;
	}

	auto p = &vec[0];
	for (; n > 1; --n)
	{
		if (p[n - 1] != 0)
		{
			break;
		}
	}
	
	vec.resize(n);
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_NORMALIZE_HPP
