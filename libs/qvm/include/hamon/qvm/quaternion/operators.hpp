/**
 *	@file	operators.hpp
 *
 *	@brief	operators の定義
 */

#ifndef HAMON_QVM_QUATERNION_OPERATORS_HPP
#define HAMON_QVM_QUATERNION_OPERATORS_HPP

#include <hamon/qvm/quaternion/quaternion.hpp>
#include <hamon/qvm/quaternion/detail/mul_quaternion.hpp>
#include <hamon/qvm/detail/plus.hpp>
#include <hamon/qvm/detail/minus.hpp>
#include <hamon/qvm/detail/transform.hpp>
#include <hamon/qvm/detail/multiplies_scalar.hpp>
#include <hamon/qvm/detail/divides_scalar.hpp>
#include <hamon/qvm/common/all.hpp>
#include <hamon/qvm/common/equal.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/negate.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/functional/minus.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	operator==
 */
template <typename T1, typename T2>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator==(quaternion<T1> const& lhs, quaternion<T2> const& rhs) HAMON_NOEXCEPT
{
	return hamon::qvm::all(hamon::qvm::equal(lhs, rhs));
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

/**
 *	@brief	operator!=
 */
template <typename T1, typename T2>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator!=(quaternion<T1> const& lhs, quaternion<T2> const& rhs) HAMON_NOEXCEPT
{
	return !(lhs == rhs);
}

#endif

/**
 *	@brief	unary operator+
 */
template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR quaternion<T>
operator+(quaternion<T> const& v) HAMON_NOEXCEPT
{
	return v;
}

/**
 *	@brief	unary operator-
 */
template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator-(quaternion<T> const& v) HAMON_NOEXCEPT
->decltype(hamon::qvm::detail::transform(v, hamon::negate<>{}))
{
	return hamon::qvm::detail::transform(v, hamon::negate<>{});
}

/**
 *	@brief	Quaternion + Quaternion -> Quaternion
 */
template <typename T1, typename T2>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator+(quaternion<T1> const& lhs, quaternion<T2> const& rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::detail::plus(lhs, rhs))
{
	return hamon::qvm::detail::plus(lhs, rhs);
}

/**
 *	@brief	Quaternion += Quaternion
 */
template <typename T1, typename T2>
inline HAMON_CXX14_CONSTEXPR quaternion<T1>&
operator+=(quaternion<T1>& lhs, quaternion<T2> const& rhs) HAMON_NOEXCEPT
{
	return lhs = lhs + rhs;
}

/**
 *	@brief	Quaternion - Quaternion -> Quaternion
 */
template <typename T1, typename T2>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator-(quaternion<T1> const& lhs, quaternion<T2> const& rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::detail::minus(lhs, rhs))
{
	return hamon::qvm::detail::minus(lhs, rhs);
}

/**
 *	@brief	Quaternion -= Quaternion
 */
template <typename T1, typename T2>
inline HAMON_CXX14_CONSTEXPR quaternion<T1>&
operator-=(quaternion<T1>& lhs, quaternion<T2> const& rhs) HAMON_NOEXCEPT
{
	return lhs = lhs - rhs;
}

/**
 *	@brief	Quaternion * Quaternion -> Quaternion
 */
template <typename T1, typename T2>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator*(quaternion<T1> const& lhs, quaternion<T2> const& rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::detail::mul_quaternion(lhs, rhs))
{
	return hamon::qvm::detail::mul_quaternion(lhs, rhs);
}

/**
 *	@brief	Quaternion *= Quaternion
 */
template <typename T1, typename T2>
inline HAMON_CXX14_CONSTEXPR quaternion<T1>&
operator*=(quaternion<T1>& lhs, quaternion<T2> const& rhs) HAMON_NOEXCEPT
{
	return lhs = lhs * rhs;
}

/**
 *	@brief	Quaternion * スカラー -> Quaternion
 */
template <
	typename T1,
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, T2)
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator*(quaternion<T1> const& lhs, T2 rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::detail::multiplies_scalar(lhs, rhs))
{
	return hamon::qvm::detail::multiplies_scalar(lhs, rhs);
}

/**
 *	@brief	スカラー * Quaternion -> Quaternion
 */
template <
	typename T1,
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, T2)
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator*(T2 lhs, quaternion<T1> const& rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::detail::multiplies_scalar(rhs, lhs))
{
	return hamon::qvm::detail::multiplies_scalar(rhs, lhs);
}

/**
 *	@brief	Quaternion *= スカラー
 */
template <
	typename T1,
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, T2)
>
inline HAMON_CXX14_CONSTEXPR quaternion<T1>&
operator*=(quaternion<T1>& lhs, T2 rhs) HAMON_NOEXCEPT
{
	return lhs = lhs * rhs;
}

/**
 *	@brief	Quaternion / スカラー -> Quaternion
 */
template <
	typename T1,
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, T2)
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator/(quaternion<T1> const& lhs, T2 rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::detail::divides_scalar(lhs, rhs))
{
	return hamon::qvm::detail::divides_scalar(lhs, rhs);
}

/**
 *	@brief	Quaternion /= スカラー
 */
template <
	typename T1,
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, T2)
>
inline HAMON_CXX14_CONSTEXPR quaternion<T1>&
operator/=(quaternion<T1>& lhs, T2 rhs) HAMON_NOEXCEPT
{
	return lhs = lhs / rhs;
}

/**
 *	@brief	Vector3 * Quaternion -> Vector3
 */
template <typename T1, typename T2>
HAMON_NODISCARD inline HAMON_CONSTEXPR vector<T1, 3>
operator*(vector<T1, 3> const& lhs, quaternion<T2> const& rhs) HAMON_NOEXCEPT
{
	return (rhs * quaternion<T1>(lhs, 0) * conjugate(rhs)).imag();
}

/**
 *	@brief	Vector3 *= Quaternion
 */
template <typename T1, typename T2>
HAMON_NODISCARD inline HAMON_CONSTEXPR vector<T1, 3>&
operator*=(vector<T1, 3>& lhs, quaternion<T2> const& rhs) HAMON_NOEXCEPT
{
	return lhs = lhs * rhs;
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_QUATERNION_OPERATORS_HPP
