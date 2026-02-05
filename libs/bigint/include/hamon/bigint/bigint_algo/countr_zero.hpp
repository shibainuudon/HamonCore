/**
 *	@file	countr_zero.hpp
 *
 *	@brief	countr_zero 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_COUNTR_ZERO_HPP
#define HAMON_BIGINT_BIGINT_ALGO_COUNTR_ZERO_HPP

#include <hamon/array.hpp>
#include <hamon/bit/countr_zero.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/inplace_vector.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace countr_zero_detail
{

template <hamon::size_t N, typename T>
inline HAMON_CXX14_CONSTEXPR int
countr_zero_impl(T const* vec, hamon::size_t n) HAMON_NOEXCEPT
{
	for (hamon::size_t i = 0; i < n; ++i)
	{
		auto const v = vec[i];
		if (v != 0)
		{
			return static_cast<int>(i * hamon::bitsof<T>()) + hamon::countr_zero(v);
		}
	}
	return static_cast<int>(N * hamon::bitsof<T>());
}

}	// namespace countr_zero_detail

template <typename T, hamon::size_t N>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR int
countr_zero(hamon::inplace_vector<T, N> const& vec) HAMON_NOEXCEPT
{
	return countr_zero_detail::countr_zero_impl<N>(vec.data(), vec.size());
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR int
countr_zero(hamon::array<T, N> const& vec) HAMON_NOEXCEPT
{
	return countr_zero_detail::countr_zero_impl<N>(vec.data(), N);
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_COUNTR_ZERO_HPP
