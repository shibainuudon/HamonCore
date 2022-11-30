/**
 *	@file	mul_matrix.hpp
 *
 *	@brief	mul_matrix の定義
 */

#ifndef HAMON_QVM_MATRIX_DETAIL_MUL_MATRIX_HPP
#define HAMON_QVM_MATRIX_DETAIL_MUL_MATRIX_HPP

#include <hamon/qvm/detail/reduce.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/type_traits/arithmetic_promote.hpp>
#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <
	template <typename, std::size_t, std::size_t> class Matrix,
	typename T, std::size_t N, std::size_t M, std::size_t L,
	typename Vector = typename Matrix<T, 1, L>::value_type,
	std::size_t... Ks
>
HAMON_NODISCARD inline HAMON_CONSTEXPR T
mul_matrix_impl_3(Matrix<T, N, L> const& lhs, Matrix<T, L, M> const& rhs, std::size_t I, std::size_t J, hamon::index_sequence<Ks...>) HAMON_NOEXCEPT
{
	return hamon::qvm::detail::reduce(Vector{(lhs[I][Ks] * rhs[Ks][J])...});
}

template <
	template <typename, std::size_t, std::size_t> class Matrix,
	typename T, std::size_t N, std::size_t M, std::size_t L,
	typename Vector = typename Matrix<T, N, M>::value_type,
	std::size_t... Js
>
HAMON_NODISCARD inline HAMON_CONSTEXPR Vector
mul_matrix_impl_2(Matrix<T, N, L> const& lhs, Matrix<T, L, M> const& rhs, std::size_t I, hamon::index_sequence<Js...>) HAMON_NOEXCEPT
{
	return { mul_matrix_impl_3(lhs, rhs, I, Js, hamon::make_index_sequence<L>{})... };
}

template <
	template <typename, std::size_t, std::size_t> class Matrix,
	typename T, std::size_t N, std::size_t M, std::size_t L,
	std::size_t... Is
>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix<T, N, M>
mul_matrix_impl(Matrix<T, N, L> const& lhs, Matrix<T, L, M> const& rhs, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
{
	return { mul_matrix_impl_2(lhs, rhs, Is, hamon::make_index_sequence<M>{})... };
}

/**
 *	@brief	mul_matrix
 */
template <
	template <typename, std::size_t, std::size_t> class Matrix,
	typename T, std::size_t N, std::size_t M, std::size_t L
>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix<T, N, M>
mul_matrix(Matrix<T, N, L> const& lhs, Matrix<T, L, M> const& rhs) HAMON_NOEXCEPT
{
	return mul_matrix_impl(lhs, rhs, hamon::make_index_sequence<N>{});
}

/**
 *	@brief	mul_matrix
 *
 *	要素の型が違うときのオーバーロード
 */
template <
	template <typename, std::size_t, std::size_t> class Matrix,
	typename T1, typename T2, std::size_t N, std::size_t M, std::size_t L,
	typename T3 = hamon::arithmetic_promote_t<T1, T2>
>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix<T3, N, M>
mul_matrix(Matrix<T1, N, L> const& lhs, Matrix<T2, L, M> const& rhs) HAMON_NOEXCEPT
{
	using Promoted1 = Matrix<T3, N, L>;
	using Promoted2 = Matrix<T3, L, M>;
	return mul_matrix(Promoted1{lhs}, Promoted2{rhs});
}

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_DETAIL_MUL_MATRIX_HPP
