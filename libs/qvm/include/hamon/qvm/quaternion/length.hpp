/**
 *	@file	length.hpp
 *
 *	@brief	length の定義
 */

#ifndef HAMON_QVM_QUATERNION_LENGTH_HPP
#define HAMON_QVM_QUATERNION_LENGTH_HPP

#include <hamon/qvm/quaternion/quaternion.hpp>
#include <hamon/qvm/quaternion/length_sq.hpp>
#include <hamon/cmath/sqrt.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	クォータニオンの長さを取得します
 */
template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
length(quaternion<T> const& q) HAMON_NOEXCEPT
->decltype(hamon::sqrt(length_sq(q)))
{
	return hamon::sqrt(length_sq(q));
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_QUATERNION_LENGTH_HPP
