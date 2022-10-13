/**
 *	@file	make_diagonal_matrix.hpp
 *
 *	@brief	make_diagonal_matrix の定義
 */

#ifndef HAMON_QVM_MATRIX_DETAIL_MAKE_DIAGONAL_MATRIX_HPP
#define HAMON_QVM_MATRIX_DETAIL_MAKE_DIAGONAL_MATRIX_HPP

#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename Vector, typename Arg, std::size_t... Js>
HAMON_NODISCARD inline HAMON_CONSTEXPR Vector
make_diagonal_matrix_impl(Arg const& v, std::size_t I, hamon::index_sequence<Js...>) HAMON_NOEXCEPT
{
	return Vector{ (I == Js ? v[I] : 0)... };
}

template <
	typename Matrix,
	typename Arg,
	typename Vector = typename Matrix::value_type,
	std::size_t... Is>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix
make_diagonal_matrix_impl(Arg const& arg, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
{
	return { make_diagonal_matrix_impl<Vector>(arg, Is, hamon::make_index_sequence<vector_size<Vector>::value>{})... };
}

template <typename Matrix, typename Arg>
HAMON_NODISCARD inline HAMON_CONSTEXPR Matrix
make_diagonal_matrix(Arg const& arg) HAMON_NOEXCEPT
{
	return make_diagonal_matrix_impl<Matrix>(arg, hamon::make_index_sequence<vector_size<Matrix>::value>{});
}

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_DETAIL_MAKE_DIAGONAL_MATRIX_HPP
