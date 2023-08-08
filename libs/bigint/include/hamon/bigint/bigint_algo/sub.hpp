/**
 *	@file	sub.hpp
 *
 *	@brief	sub 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_SUB_HPP
#define HAMON_BIGINT_BIGINT_ALGO_SUB_HPP

#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/bigint/bigint_algo/detail/hi.hpp>
#include <hamon/bigint/bigint_algo/detail/lo.hpp>
#include <hamon/bigint/bigint_algo/detail/subc.hpp>
#include <hamon/bigint/bigint_algo/detail/actual_size.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <vector>

namespace hamon
{
namespace bigint_algo
{

namespace sub_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR void
sub_impl(T* p1, hamon::size_t n1, T const* p2, hamon::size_t n2)
{
	T carry = 0;
	hamon::size_t i = 0;
	for (; i < n2; ++i)
	{
		auto const x = detail::subc(p1[i], p2[i], carry);
		p1[i] = detail::lo(x);
		carry = detail::hi(x);
	}
	for (; carry != 0 && i < n1; ++i)
	{
		auto const x = detail::subc(p1[i], T{0}, carry);
		p1[i] = detail::lo(x);
		carry = detail::hi(x);
	}
}

}	// namespace sub_detail

template <typename T>
inline void
sub(std::vector<T>& lhs, std::vector<T> const& rhs)
{
	lhs.resize(hamon::max(lhs.size(), rhs.size()));
	sub_detail::sub_impl(
		lhs.data(), lhs.size(),
		rhs.data(), rhs.size());
	bigint_algo::normalize(lhs);
}

template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR void
sub(hamon::array<T, N>& lhs, hamon::array<T, N> const& rhs)
{
	sub_detail::sub_impl(
		lhs.data(), lhs.size(),
		rhs.data(), detail::actual_size(rhs));
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_SUB_HPP
