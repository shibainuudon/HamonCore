/**
 *	@file	reduce.hpp
 *
 *	@brief	reduce の定義
 */

#ifndef HAMON_QVM_DETAIL_REDUCE_HPP
#define HAMON_QVM_DETAIL_REDUCE_HPP

#include <hamon/qvm/detail/vector_rank.hpp>
#include <hamon/qvm/detail/vector_element.hpp>
#include <hamon/qvm/detail/vector_size.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <cstddef>
#include <utility>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <
	typename Vector,
	typename U,
	typename F,
	std::size_t N = hamon::qvm::detail::vector_size<Vector>::value,
	hamon::enable_if_t<detail::vector_rank<Vector>::value == 1>* = nullptr
>
HAMON_NODISCARD inline HAMON_CONSTEXPR U
reduce_impl_2(Vector const& v, U init, F binary_op, std::size_t I) HAMON_NOEXCEPT
{
	return I == N ?
		init :
		reduce_impl_2(
			v,
			binary_op(init, v[I]),
			binary_op,
			I+1);
}

template <
	typename Matrix,
	typename U,
	typename F,
	std::size_t N = hamon::qvm::detail::vector_size<Matrix>::value,
	hamon::enable_if_t<(detail::vector_rank<Matrix>::value > 1)>* = nullptr
>
HAMON_NODISCARD inline HAMON_CONSTEXPR U
reduce_impl_2(Matrix const& m, U init, F binary_op, std::size_t I) HAMON_NOEXCEPT
{
	return I == N ?
		init :
		reduce_impl_2(
			m,
			reduce_impl_2(m[I], init, binary_op, 0),
			binary_op,
			I+1);
}

template <
	typename Vector,
	std::size_t N = hamon::qvm::detail::vector_size<Vector>::value
>
struct reduce_impl_t
{
	template <typename U, typename F>
	HAMON_CONSTEXPR U
	operator()(Vector const& v, U init, F binary_op) const HAMON_NOEXCEPT
	{
		return reduce_impl_2(v, init, binary_op, 0);
	}
};

template <typename Vector>
struct reduce_impl_t<Vector, 0>
{
	template <typename U, typename F>
	HAMON_CONSTEXPR U
	operator()(Vector const&, U init, F) const HAMON_NOEXCEPT
	{
		return init;
	}
};

}	// namespace detail

template <
	typename Vector,
	typename T = hamon::qvm::detail::vector_element_t<Vector>,
	typename F = hamon::plus<>,
	typename U = decltype(std::declval<F>()(std::declval<T>(), std::declval<T>()))
>
HAMON_NODISCARD inline HAMON_CONSTEXPR U
reduce(Vector const& v, U init = {}, F binary_op = {}) HAMON_NOEXCEPT
{
	return detail::reduce_impl_t<Vector>{}(v, init, binary_op);
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_DETAIL_reduce_HPP
