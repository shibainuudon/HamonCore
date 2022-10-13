/**
 *	@file	transpose.hpp
 *
 *	@brief	transpose の定義
 */

#ifndef HAMON_QVM_MATRIX_TRANSPOSE_HPP
#define HAMON_QVM_MATRIX_TRANSPOSE_HPP

#include <hamon/qvm/matrix/matrix.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename T, std::size_t R, std::size_t C, std::size_t... Js>
HAMON_NODISCARD inline HAMON_CONSTEXPR typename matrix<T, C, R>::value_type
transpose_impl(matrix<T, R, C> const& m, std::size_t I, hamon::index_sequence<Js...>) HAMON_NOEXCEPT
{
	return { m[Js][I]... };
}

template <typename T, std::size_t R, std::size_t C, std::size_t... Is>
HAMON_NODISCARD inline HAMON_CONSTEXPR matrix<T, C, R>
transpose_impl(matrix<T, R, C> const& m, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
{
	return { transpose_impl(m, Is, hamon::make_index_sequence<R>{})... };
}

template <typename T, std::size_t R, std::size_t C>
HAMON_NODISCARD inline HAMON_CONSTEXPR matrix<T, C, R>
transpose_impl(matrix<T, R, C> const& m) HAMON_NOEXCEPT
{
	return transpose_impl(m, hamon::make_index_sequence<C>{});
}

}	// namespace detail

/**
 *	@brief	転置行列を求めます
 */
template <typename T, std::size_t R, std::size_t C>
HAMON_NODISCARD inline HAMON_CONSTEXPR matrix<T, C, R>
transpose(matrix<T, R, C> const& m) HAMON_NOEXCEPT
{
	return detail::transpose_impl(m);
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_TRANSPOSE_HPP
