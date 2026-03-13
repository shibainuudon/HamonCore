/**
 *	@file	multiply_add.hpp
 *
 *	@brief	multiply_add 関数の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_MULTIPLY_ADD_HPP
#define HAMON_BIGINT_BIGINT_ALGO_MULTIPLY_ADD_HPP

#include <hamon/bigint/bigint_algo/detail/mulc.hpp>
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
	detail::resize(x, x.size() + 1);
	auto p = x.data();
	auto n = x.size();
	while (n != 0)
	{
		*p = detail::mulc(*p, y, &z);
		++p;
		--n;
	}
	bigint_algo::normalize(x);
	return z != 0;
}

}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_MULTIPLY_HPP
