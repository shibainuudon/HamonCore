/**
 *	@file	bit_width.hpp
 *
 *	@brief	bit_width 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_BIT_WIDTH_HPP
#define HAMON_BIGINT_BIGINT_ALGO_BIT_WIDTH_HPP

#include <hamon/bigint/bigint_algo/detail/actual_size.hpp>
#include <hamon/array.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/bit/bit_width.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/inplace_vector.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace bit_width_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR int
bit_width_impl(T* p, hamon::size_t n) HAMON_NOEXCEPT
{
	hamon::size_t const i = n - 1;
	return static_cast<int>(hamon::bitsof<T>() * i) + hamon::bit_width(p[i]);
}

}	// namespace bit_width_detail

template <typename T>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR int
bit_width(hamon::vector<T> const& vec) HAMON_NOEXCEPT
{
	return bit_width_detail::bit_width_impl(vec.data(), vec.size());
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR int
bit_width(hamon::inplace_vector<T, N> const& vec) HAMON_NOEXCEPT
{
	return bit_width_detail::bit_width_impl(vec.data(), vec.size());
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR int
bit_width(hamon::array<T, N> const& vec) HAMON_NOEXCEPT
{
	auto const n = detail::actual_size(vec);
	if (n == 0)
	{
		return 0;
	}
	return bit_width_detail::bit_width_impl(vec.data(), n);
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_bit_width_HPP
