/**
 *	@file	inverse.hpp
 *
 *	@brief	inverse の定義
 */

#ifndef HAMON_QVM_MATRIX_INVERSE_HPP
#define HAMON_QVM_MATRIX_INVERSE_HPP

#include <hamon/qvm/matrix/matrix.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename Matrix, typename T>
inline HAMON_CONSTEXPR Matrix
inverse_impl_1(Matrix const& tmp, T det) HAMON_NOEXCEPT
{
	return det == 0 ?
		Matrix::identity() :
		tmp / det;
}

template <typename T>
inline HAMON_CONSTEXPR matrix<T, 3, 3>
inverse_impl(matrix<T, 3, 3> const& m, matrix<T, 3, 3> const& tmp) HAMON_NOEXCEPT
{
	return inverse_impl_1(
		tmp,
		m[0][0] * tmp[0][0] +
		m[0][1] * tmp[1][0] +
		m[0][2] * tmp[2][0]);
}

template <typename T>
inline HAMON_CONSTEXPR matrix<T, 4, 4>
inverse_impl(matrix<T, 4, 4> const& m, matrix<T, 4, 4> const& tmp) HAMON_NOEXCEPT
{
	return inverse_impl_1(
		tmp,
		m[0][0] * tmp[0][0] +
		m[0][1] * tmp[1][0] +
		m[0][2] * tmp[2][0] +
		m[0][3] * tmp[3][0]);
}

}	// namespace detail

/**
 *	@brief	2x2行列の逆行列を求めます
 */
template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR matrix<T, 2, 2>
inverse(matrix<T, 2, 2> const& m) HAMON_NOEXCEPT
{
	return detail::inverse_impl_1(
		matrix<T, 2, 2>
		{
			 m[1][1], -m[0][1],
			-m[1][0],  m[0][0],
		},
		m[0][0]*m[1][1] - m[0][1]*m[1][0]);
}

/**
 *	@brief	3x3行列の逆行列を求めます
 */
template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR matrix<T, 3, 3>
inverse(matrix<T, 3, 3> const& m) HAMON_NOEXCEPT
{
	return detail::inverse_impl(
		m,
		matrix<T, 3, 3>
		{
			m[1][1] * m[2][2] - m[1][2] * m[2][1],
			m[2][1] * m[0][2] - m[2][2] * m[0][1],
			m[0][1] * m[1][2] - m[0][2] * m[1][1],
			m[1][2] * m[2][0] - m[1][0] * m[2][2],
			m[2][2] * m[0][0] - m[2][0] * m[0][2],
			m[0][2] * m[1][0] - m[0][0] * m[1][2],
			m[1][0] * m[2][1] - m[1][1] * m[2][0],
			m[2][0] * m[0][1] - m[2][1] * m[0][0],
			m[0][0] * m[1][1] - m[0][1] * m[1][0],
		});
}

/**
 *	@brief	4x4行列の逆行列を求めます
 */
template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR matrix<T, 4, 4>
inverse(matrix<T, 4, 4> const& m) HAMON_NOEXCEPT
{
	return detail::inverse_impl(
		m,
		matrix<T, 4, 4>
		{
			m[1][1]*m[2][2]*m[3][3] +
			m[1][2]*m[2][3]*m[3][1] +
			m[1][3]*m[2][1]*m[3][2] -
			m[1][1]*m[2][3]*m[3][2] -
			m[1][2]*m[2][1]*m[3][3] -
			m[1][3]*m[2][2]*m[3][1],
			m[0][1]*m[2][3]*m[3][2] +
			m[0][2]*m[2][1]*m[3][3] +
			m[0][3]*m[2][2]*m[3][1] -
			m[0][1]*m[2][2]*m[3][3] -
			m[0][2]*m[2][3]*m[3][1] -
			m[0][3]*m[2][1]*m[3][2],
			m[0][1]*m[1][2]*m[3][3] +
			m[0][2]*m[1][3]*m[3][1] +
			m[0][3]*m[1][1]*m[3][2] -
			m[0][1]*m[1][3]*m[3][2] -
			m[0][2]*m[1][1]*m[3][3] -
			m[0][3]*m[1][2]*m[3][1],
			m[0][1]*m[1][3]*m[2][2] +
			m[0][2]*m[1][1]*m[2][3] +
			m[0][3]*m[1][2]*m[2][1] -
			m[0][1]*m[1][2]*m[2][3] -
			m[0][2]*m[1][3]*m[2][1] -
			m[0][3]*m[1][1]*m[2][2],

			m[1][0]*m[2][3]*m[3][2] +
			m[1][2]*m[2][0]*m[3][3] +
			m[1][3]*m[2][2]*m[3][0] -
			m[1][0]*m[2][2]*m[3][3] -
			m[1][2]*m[2][3]*m[3][0] -
			m[1][3]*m[2][0]*m[3][2],
			m[0][0]*m[2][2]*m[3][3] +
			m[0][2]*m[2][3]*m[3][0] +
			m[0][3]*m[2][0]*m[3][2] -
			m[0][0]*m[2][3]*m[3][2] -
			m[0][2]*m[2][0]*m[3][3] -
			m[0][3]*m[2][2]*m[3][0],
			m[0][0]*m[1][3]*m[3][2] +
			m[0][2]*m[1][0]*m[3][3] +
			m[0][3]*m[1][2]*m[3][0] -
			m[0][0]*m[1][2]*m[3][3] -
			m[0][2]*m[1][3]*m[3][0] -
			m[0][3]*m[1][0]*m[3][2],
			m[0][0]*m[1][2]*m[2][3] +
			m[0][2]*m[1][3]*m[2][0] +
			m[0][3]*m[1][0]*m[2][2] -
			m[0][0]*m[1][3]*m[2][2] -
			m[0][2]*m[1][0]*m[2][3] -
			m[0][3]*m[1][2]*m[2][0],

			m[1][0]*m[2][1]*m[3][3] +
			m[1][1]*m[2][3]*m[3][0] +
			m[1][3]*m[2][0]*m[3][1] -
			m[1][0]*m[2][3]*m[3][1] -
			m[1][1]*m[2][0]*m[3][3] -
			m[1][3]*m[2][1]*m[3][0],
			m[0][0]*m[2][3]*m[3][1] +
			m[0][1]*m[2][0]*m[3][3] +
			m[0][3]*m[2][1]*m[3][0] -
			m[0][0]*m[2][1]*m[3][3] -
			m[0][1]*m[2][3]*m[3][0] -
			m[0][3]*m[2][0]*m[3][1],
			m[0][0]*m[1][1]*m[3][3] +
			m[0][1]*m[1][3]*m[3][0] +
			m[0][3]*m[1][0]*m[3][1] -
			m[0][0]*m[1][3]*m[3][1] -
			m[0][1]*m[1][0]*m[3][3] -
			m[0][3]*m[1][1]*m[3][0],
			m[0][0]*m[1][3]*m[2][1] +
			m[0][1]*m[1][0]*m[2][3] +
			m[0][3]*m[1][1]*m[2][0] -
			m[0][0]*m[1][1]*m[2][3] -
			m[0][1]*m[1][3]*m[2][0] -
			m[0][3]*m[1][0]*m[2][1],

			m[1][0]*m[2][2]*m[3][1] +
			m[1][1]*m[2][0]*m[3][2] +
			m[1][2]*m[2][1]*m[3][0] -
			m[1][0]*m[2][1]*m[3][2] -
			m[1][1]*m[2][2]*m[3][0] -
			m[1][2]*m[2][0]*m[3][1],
			m[0][0]*m[2][1]*m[3][2] +
			m[0][1]*m[2][2]*m[3][0] +
			m[0][2]*m[2][0]*m[3][1] -
			m[0][0]*m[2][2]*m[3][1] -
			m[0][1]*m[2][0]*m[3][2] -
			m[0][2]*m[2][1]*m[3][0],
			m[0][0]*m[1][2]*m[3][1] +
			m[0][1]*m[1][0]*m[3][2] +
			m[0][2]*m[1][1]*m[3][0] -
			m[0][0]*m[1][1]*m[3][2] -
			m[0][1]*m[1][2]*m[3][0] -
			m[0][2]*m[1][0]*m[3][1],
			m[0][0]*m[1][1]*m[2][2] +
			m[0][1]*m[1][2]*m[2][0] +
			m[0][2]*m[1][0]*m[2][1] -
			m[0][0]*m[1][2]*m[2][1] -
			m[0][1]*m[1][0]*m[2][2] -
			m[0][2]*m[1][1]*m[2][0],
		});
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_INVERSE_HPP
