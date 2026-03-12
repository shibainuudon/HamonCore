/**
 *	@file	multiply_add.hpp
 *
 *	@brief	multiply_add 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_MULTIPLY_ADD_HPP
#define HAMON_BIGINT_BIGINT_ALGO_MULTIPLY_ADD_HPP

#include <hamon/bigint/bigint_algo/detail/actual_size.hpp>
#include <hamon/bigint/bigint_algo/detail/hi.hpp>
#include <hamon/bigint/bigint_algo/detail/lo.hpp>
#include <hamon/bigint/bigint_algo/detail/mul_addc.hpp>
#include <hamon/bigint/bigint_algo/detail/resize.hpp>
#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{

namespace multiply_add_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
multiply_add_impl(T* p1, hamon::size_t n1, T y, T z)
{
	T carry = z;
	hamon::size_t i = 0;
	for (; i < n1; ++i)
	{
		auto const r = detail::mul_addc(p1[i], y, T{0}, carry);
		p1[i] = detail::lo(r);
		carry = detail::hi(r);
	}

	return carry != 0;
}

}	// namespace multiply_add_detail

// x = x * y + z
template <typename VectorType, typename T2,
	typename T1 = hamon::ranges::range_value_t<VectorType>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::is_integral<T2>,
		hamon::is_same<T1, T2>
	>::value>
>
inline HAMON_CXX14_CONSTEXPR bool
multiply_add(VectorType& x, T2 y, T2 z)
{
	auto n1 = detail::actual_size(x);
	detail::resize(x, n1 + 1);
	auto overflow = multiply_add_detail::multiply_add_impl(x.data(), x.size(), y, z);
	bigint_algo::normalize(x);
	return overflow;
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_MULTIPLY_HPP
