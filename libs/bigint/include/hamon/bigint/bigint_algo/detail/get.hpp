/**
 *	@file	get.hpp
 *
 *	@brief	get 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_GET_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_GET_HPP

#include <hamon/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <vector>

namespace hamon
{
namespace bigint_algo
{
namespace detail
{

template <typename T>
inline T get(std::vector<T> const& vec, hamon::size_t i)
{
	return i < vec.size() ? vec[i] : T{};
}

template <typename T, hamon::size_t N>
inline HAMON_CXX11_CONSTEXPR T
get(hamon::array<T, N> const& arr, hamon::size_t i)
{
	return i < arr.size() ? arr[i] : T{};
}

}	// namespace detail
}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_GET_HPP
