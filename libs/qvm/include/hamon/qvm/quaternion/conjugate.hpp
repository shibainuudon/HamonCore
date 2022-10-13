/**
 *	@file	conjugate.hpp
 *
 *	@brief	conjugate の定義
 */

#ifndef HAMON_QVM_QUATERNION_CONJUGATE_HPP
#define HAMON_QVM_QUATERNION_CONJUGATE_HPP

#include <hamon/qvm/quaternion/quaternion.hpp>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	クォータニオンの共役を取得します
 */
template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR quaternion<T>
conjugate(quaternion<T> const& q) HAMON_NOEXCEPT
{
	return {-q.imag(), q.real()};
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_QUATERNION_CONJUGATE_HPP
