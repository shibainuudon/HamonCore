/**
 *	@file	bit_scan_reverse.hpp
 *
 *	@brief	bit_scan_reverse 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_BIT_SCAN_REVERSE_HPP
#define HAMON_BIGINT_BIGINT_ALGO_BIT_SCAN_REVERSE_HPP

#include <hamon/bigint/bigint_algo/detail/actual_size.hpp>
#include <hamon/bigint/bigint_algo/detail/bit_scan_reverse.hpp>
#include <hamon/bigint/bigint_algo/is_zero.hpp>
#include <hamon/array.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/inplace_vector.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace bit_scan_reverse_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
bit_scan_reverse_impl(hamon::size_t* index, T* p, hamon::size_t n)
{
	bool ret = detail::bit_scan_reverse(index, p[n - 1]);
	*index += hamon::bitsof<T>() * (n - 1);
	return ret;
}

}	// namespace bit_scan_reverse_detail

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
bit_scan_reverse(hamon::size_t* index, hamon::vector<T> const& vec)
{
	return bit_scan_reverse_detail::bit_scan_reverse_impl(index, vec.data(), vec.size());
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR bool
bit_scan_reverse(hamon::size_t* index, hamon::inplace_vector<T, N> const& vec)
{
	return bit_scan_reverse_detail::bit_scan_reverse_impl(index, vec.data(), vec.size());
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR bool
bit_scan_reverse(hamon::size_t* index, hamon::array<T, N> const& vec)
{
	auto const n = detail::actual_size(vec);
	if (n == 0)
	{
		return false;
	}
	return bit_scan_reverse_detail::bit_scan_reverse_impl(index, vec.data(), n);
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_BIT_SCAN_REVERSE_HPP
