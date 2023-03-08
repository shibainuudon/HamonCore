/**
 *	@file	slerp.hpp
 *
 *	@brief	slerp の定義
 */

#ifndef HAMON_QVM_QUATERNION_SLERP_HPP
#define HAMON_QVM_QUATERNION_SLERP_HPP

#include <hamon/qvm/quaternion/quaternion.hpp>
#include <hamon/qvm/quaternion/dot.hpp>
#include <hamon/cmath/acos.hpp>
#include <hamon/cmath/sin.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	球面線形補間
 *
 *	@param	from	開始クォータニオン
 *	@param	to		終了クォータニオン
 *	@param	t		補間係数
 *
 *	@return	from と to を 係数t で球面線形補間したクォータニオン
 */
template <typename T, HAMON_CONSTRAINED_PARAM(hamon::arithmetic, U)>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR quaternion<T>
slerp(quaternion<T> const& from, quaternion<T> const& to, U t) HAMON_NOEXCEPT
{
	if (t <= U(0.0))
	{
		return from;
	}

	if (t >= U(1.0))
	{
		return to;
	}

	auto const cos_half_theta = dot(from, to);

	if (cos_half_theta >= T(1.0))
	{
		return lerp(from, to, t);
	}

	auto const half_theta = hamon::acos(cos_half_theta);
	auto const inv_sin_half_theta = T(1.0) / hamon::sin(half_theta);
	auto const ratio_a = hamon::sin(half_theta * (U(1.0) - t)) * inv_sin_half_theta;
	auto const ratio_b = hamon::sin(half_theta * t) * inv_sin_half_theta;

	return (from * ratio_a) + (to * ratio_b);
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_QUATERNION_SLERP_HPP
