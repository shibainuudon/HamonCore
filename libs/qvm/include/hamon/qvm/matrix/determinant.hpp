/**
 *	@file	determinant.hpp
 *
 *	@brief	determinant の定義
 */

#ifndef HAMON_QVM_MATRIX_DETERMINANT_HPP
#define HAMON_QVM_MATRIX_DETERMINANT_HPP

#include <hamon/qvm/matrix/matrix.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	2x2行列の行列式を求めます
 */
template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR T
determinant(matrix<T, 2, 2> const& m) HAMON_NOEXCEPT
{
	return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

/**
 *	@brief	3x3行列の行列式を求めます
 */
template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR T
determinant(matrix<T, 3, 3> const& m) HAMON_NOEXCEPT
{
	return
		m[0][0] * m[1][1] * m[2][2] +
		m[1][0] * m[2][1] * m[0][2] +
		m[2][0] * m[0][1] * m[1][2] -
		m[0][0] * m[2][1] * m[1][2] -
		m[2][0] * m[1][1] * m[0][2] -
		m[1][0] * m[0][1] * m[2][2];
}

/**
 *	@brief	4x4行列の行列式を求めます
 */
template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR T
determinant(matrix<T, 4, 4> const& m) HAMON_NOEXCEPT
{
	return
		m[0][0] * (m[1][1]*m[2][2]*m[3][3] +
		           m[1][2]*m[2][3]*m[3][1] +
		           m[1][3]*m[2][1]*m[3][2] -
		           m[1][1]*m[2][3]*m[3][2] -
		           m[1][2]*m[2][1]*m[3][3] -
		           m[1][3]*m[2][2]*m[3][1]) +
		m[0][1] * (m[1][0]*m[2][3]*m[3][2] +
		           m[1][2]*m[2][0]*m[3][3] +
		           m[1][3]*m[2][2]*m[3][0] -
		           m[1][0]*m[2][2]*m[3][3] -
		           m[1][2]*m[2][3]*m[3][0] -
		           m[1][3]*m[2][0]*m[3][2]) +
		m[0][2] * (m[1][0]*m[2][1]*m[3][3] +
		           m[1][1]*m[2][3]*m[3][0] +
		           m[1][3]*m[2][0]*m[3][1] -
		           m[1][0]*m[2][3]*m[3][1] -
		           m[1][1]*m[2][0]*m[3][3] -
		           m[1][3]*m[2][1]*m[3][0]) +
		m[0][3] * (m[1][0]*m[2][2]*m[3][1] +
		           m[1][1]*m[2][0]*m[3][2] +
		           m[1][2]*m[2][1]*m[3][0] -
		           m[1][0]*m[2][1]*m[3][2] -
		           m[1][1]*m[2][2]*m[3][0] -
		           m[1][2]*m[2][0]*m[3][1]);
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_DETERMINANT_HPP
