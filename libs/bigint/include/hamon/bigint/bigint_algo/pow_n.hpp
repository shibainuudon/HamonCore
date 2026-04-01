/**
 *	@file	pow_n.hpp
 *
 *	@brief	pow_n 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_POW_N_HPP
#define HAMON_BIGINT_BIGINT_ALGO_POW_N_HPP

#include <hamon/bigint/bigint_algo/multiply.hpp>
#include <hamon/bigint/bigint_algo/detail/move.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace pow_n_detail
{

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
pow_n_impl(VectorType& out, VectorType const& x, hamon::uintmax_t y)
{
	if (y == 0)
	{
		out = VectorType{1};
		return false;
	}

	if (y == 1)
	{
		out = x;
		return false;
	}

	if (y == 2)
	{
		return bigint_algo::multiply(out, x, x);
	}

	VectorType tmp{0};

	if (y % 2 == 0)
	{
		auto f1 = pow_n_impl(out, x, y / 2);
		auto f2 = bigint_algo::multiply(tmp, out, out);
		detail::move(out, tmp);
		return f1 || f2;
	}
	else
	{
		auto f1 = pow_n_impl(out, x, y / 2);
		auto f2 = bigint_algo::multiply(tmp, out, out);
		auto f3 = bigint_algo::multiply(out, tmp, x);
		return f1 || f2 || f3;
	}
}

}	// namespace pow_n_detail

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
pow_n(VectorType& out, VectorType const& x, hamon::uintmax_t y)
{
	return pow_n_detail::pow_n_impl(out, x, y);
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_POW_N_HPP
