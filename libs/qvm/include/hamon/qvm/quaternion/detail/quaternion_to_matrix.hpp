/**
 *	@file	quaternion_to_matrix.hpp
 *
 *	@brief	quaternion_to_matrix の定義
 */

#ifndef HAMON_QVM_QUATERNION_DETAIL_QUATERNION_TO_MATRIX_HPP
#define HAMON_QVM_QUATERNION_DETAIL_QUATERNION_TO_MATRIX_HPP

#include <hamon/qvm/quaternion/quaternion.hpp>
#include <hamon/qvm/matrix/matrix.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename T>
inline HAMON_CONSTEXPR matrix<T, 3, 3>
quaternion_to_matrix_impl(
	T xx, T xy, T xz, T xw, T yy, T yz, T yw, T zz, T zw) HAMON_NOEXCEPT
{
	return
	{
		1 - yy - zz, xy + zw,     xz - yw,
		xy - zw,     1 - xx - zz, yz + xw,
		xz + yw,     yz - xw,     1 - xx - yy,
	};
}

template <typename T>
inline HAMON_CONSTEXPR matrix<T, 3, 3>
quaternion_to_matrix(quaternion<T> const& q) HAMON_NOEXCEPT
{
	return quaternion_to_matrix_impl(
		2 * q.x() * q.x(),
		2 * q.x() * q.y(),
		2 * q.x() * q.z(),
		2 * q.x() * q.w(),
		2 * q.y() * q.y(),
		2 * q.y() * q.z(),
		2 * q.y() * q.w(),
		2 * q.z() * q.z(),
		2 * q.z() * q.w());
}

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_QUATERNION_DETAIL_QUATERNION_TO_MATRIX_HPP
