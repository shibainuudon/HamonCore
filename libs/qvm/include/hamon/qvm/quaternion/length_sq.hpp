/**
 *	@file	length_sq.hpp
 *
 *	@brief	length_sq の定義
 */

#ifndef HAMON_QVM_QUATERNION_LENGTH_SQ_HPP
#define HAMON_QVM_QUATERNION_LENGTH_SQ_HPP

#include <hamon/qvm/quaternion/quaternion.hpp>
#include <hamon/qvm/quaternion/dot.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	クォータニオンの長さの２乗を取得します
 */
template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR T
length_sq(quaternion<T> const& q) HAMON_NOEXCEPT
{
	return dot(q, q);
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_QUATERNION_LENGTH_SQ_HPP
