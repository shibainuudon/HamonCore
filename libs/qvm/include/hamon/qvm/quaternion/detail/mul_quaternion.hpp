/**
 *	@file	mul_quaternion.hpp
 *
 *	@brief	mul_quaternion の定義
 */

#ifndef HAMON_QVM_QUATERNION_DETAIL_MUL_QUATERNION_HPP
#define HAMON_QVM_QUATERNION_DETAIL_MUL_QUATERNION_HPP

#include <hamon/qvm/quaternion/quaternion.hpp>
#include <hamon/type_traits/arithmetic_promote.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

namespace detail
{

/**
 *	@brief	mul_quaternion
 */
template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR quaternion<T>
mul_quaternion(quaternion<T> const& lhs, quaternion<T> const& rhs) HAMON_NOEXCEPT
{
	return
	{
		(lhs.w() * rhs.x()) + (lhs.x() * rhs.w()) + (lhs.y() * rhs.z()) - (lhs.z() * rhs.y()),
		(lhs.w() * rhs.y()) - (lhs.x() * rhs.z()) + (lhs.y() * rhs.w()) + (lhs.z() * rhs.x()),
		(lhs.w() * rhs.z()) + (lhs.x() * rhs.y()) - (lhs.y() * rhs.x()) + (lhs.z() * rhs.w()),
		(lhs.w() * rhs.w()) - (lhs.x() * rhs.x()) - (lhs.y() * rhs.y()) - (lhs.z() * rhs.z()),
	};
}

/**
 *	@brief	mul_quaternion
 *
 *	要素の型が違うときのオーバーロード
 */
template <typename T1, typename T2,	typename T3 = hamon::arithmetic_promote_t<T1, T2>>
HAMON_NODISCARD inline HAMON_CONSTEXPR quaternion<T3>
mul_quaternion(quaternion<T1> const& lhs, quaternion<T2> const& rhs) HAMON_NOEXCEPT
{
	return mul_quaternion(quaternion<T3>{lhs}, quaternion<T3>{rhs});
}

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_QUATERNION_DETAIL_MUL_QUATERNION_HPP
