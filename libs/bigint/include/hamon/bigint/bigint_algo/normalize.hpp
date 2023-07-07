/**
 *	@file	normalize.hpp
 *
 *	@brief	normalize 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_NORMALIZE_HPP
#define HAMON_BIGINT_BIGINT_ALGO_NORMALIZE_HPP

#include <hamon/iterator/next.hpp>
#include <hamon/config.hpp>
#include <vector>

namespace hamon
{
namespace detail
{
namespace bigint_algo
{

/**
 *	正規化
 *  ・末尾の0を取り除く
 *  ・空の場合は {0} を返す
 */
template <typename T>
inline std::vector<T>
normalize(std::vector<T> const& vec)
{
	auto n = static_cast<typename std::vector<T>::difference_type>(vec.size());
	for (auto i = vec.rbegin(); i != vec.rend(); ++i)
	{
		if (*i != 0)
		{
			break;
		}
		--n;
	}
	
	if (n == 0)
	{
		return std::vector<T>{0};
	}

	return std::vector<T>(vec.begin(), hamon::next(vec.begin(), n));
}

}	// namespace bigint_algo
}	// namespace detail
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_NORMALIZE_HPP
