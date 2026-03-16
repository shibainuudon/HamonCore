/**
 *	@file	copy.hpp
 *
 *	@brief	copy 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_COPY_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_COPY_HPP

#include <hamon/bigint/bigint_algo/detail/actual_size.hpp>
#include <hamon/bigint/bigint_algo/detail/resize.hpp>
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

template <typename VectorType1, typename VectorType2>
inline HAMON_CXX14_CONSTEXPR void
copy(VectorType1& out, VectorType2 const& src)
{
	auto n = detail::actual_size(src);
	detail::resize(out, n);
	hamon::size_t i = 0;
	for (; i < n; ++i)
	{
		out[i] = src[i];
	}
	for (; i < out.size(); ++i)
	{
		out[i] = 0;
	}
}

}	// namespace detail
}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_COPY_HPP
