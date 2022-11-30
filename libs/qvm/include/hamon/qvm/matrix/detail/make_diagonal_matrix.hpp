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

template <typename Matrix>
struct make_diagonal_matrix;

template <
	template <typename, std::size_t, std::size_t> class Matrix,
	typename T, std::size_t N
>
struct make_diagonal_matrix<Matrix<T, N, N>>
{
private:
	template <template <typename, std::size_t> class Vector, std::size_t... Js>
	HAMON_NODISCARD static HAMON_CONSTEXPR Vector<T, N>
	impl_2(Vector<T, N> const& v, std::size_t I, hamon::index_sequence<Js...>) HAMON_NOEXCEPT
	{
		return Vector<T, N>{ (I == Js ? v[I] : 0)... };
	}

	template <template <typename, std::size_t> class Vector, std::size_t... Is>
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, N, N>
	impl(Vector<T, N> const& arg, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
	{
		return Matrix<T, N, N>{ impl_2(arg, Is, hamon::make_index_sequence<N>{})... };
	}

public:
	template <template <typename, std::size_t> class Vector>
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, N, N>
	invoke(Vector<T, N> const& arg) HAMON_NOEXCEPT
	{
		return impl(arg, hamon::make_index_sequence<N>{});
	}
};

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_DETAIL_MAKE_DIAGONAL_MATRIX_HPP
