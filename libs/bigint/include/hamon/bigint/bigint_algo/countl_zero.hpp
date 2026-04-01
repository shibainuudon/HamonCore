/**
 *	@file	countl_zero.hpp
 *
 *	@brief	countl_zero 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_COUNTL_ZERO_HPP
#define HAMON_BIGINT_BIGINT_ALGO_COUNTL_ZERO_HPP

#include <hamon/bigint/bigint_algo/detail/vector_value_t.hpp>
#include <hamon/bigint/bigint_algo/bit_width.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

template <typename VectorType>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR int
countl_zero(VectorType const& vec) HAMON_NOEXCEPT
{
	using T = detail::vector_value_t<VectorType>;
	return static_cast<int>((hamon::bitsof<T>() * vec.max_size()) -
		static_cast<hamon::size_t>(bigint_algo::bit_width(vec)));
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_COUNTL_ZERO_HPP
