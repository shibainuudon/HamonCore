/**
 *	@file	inverse.hpp
 *
 *	@brief	inverse の定義
 */

#ifndef HAMON_QVM_QUATERNION_INVERSE_HPP
#define HAMON_QVM_QUATERNION_INVERSE_HPP

#include <hamon/qvm/quaternion/quaternion.hpp>
#include <hamon/qvm/quaternion/length_sq.hpp>
#include <hamon/qvm/quaternion/conjugate.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	クォータニオンの逆数を取得します
 */
template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR quaternion<T>
inverse(quaternion<T> const& q) HAMON_NOEXCEPT
{
	return
		length_sq(q) == 0 ?
		quaternion<T>::identity() :
		conjugate(q) / length_sq(q);
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_QUATERNION_INVERSE_HPP
