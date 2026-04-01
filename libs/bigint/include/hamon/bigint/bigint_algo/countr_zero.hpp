/**
 *	@file	countr_zero.hpp
 *
 *	@brief	countr_zero 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_COUNTR_ZERO_HPP
#define HAMON_BIGINT_BIGINT_ALGO_COUNTR_ZERO_HPP

#include <hamon/bit/countr_zero.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace countr_zero_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR int
countr_zero_impl(T const* vec, hamon::size_t n, hamon::size_t max_size) HAMON_NOEXCEPT
{
	for (hamon::size_t i = 0; i < n; ++i)
	{
		auto const v = vec[i];
		if (v != 0)
		{
			return static_cast<int>(i * hamon::bitsof<T>()) + hamon::countr_zero(v);
		}
	}
	return static_cast<int>(max_size * hamon::bitsof<T>());
}

}	// namespace countr_zero_detail

template <typename VectorType>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR int
countr_zero(VectorType const& vec) HAMON_NOEXCEPT
{
	return countr_zero_detail::countr_zero_impl(vec.data(), vec.size(), vec.max_size());
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_COUNTR_ZERO_HPP
