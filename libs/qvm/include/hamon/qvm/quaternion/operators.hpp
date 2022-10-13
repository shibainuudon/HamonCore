/**
 *	@file	operators.hpp
 *
 *	@brief	operators の定義
 */

#ifndef HAMON_QVM_QUATERNION_OPERATORS_HPP
#define HAMON_QVM_QUATERNION_OPERATORS_HPP

#include <hamon/qvm/quaternion/quaternion.hpp>
#include <hamon/qvm/detail/transform.hpp>
#include <hamon/qvm/detail/multiplies_scalar.hpp>
#include <hamon/qvm/detail/divides_scalar.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/negate.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/functional/minus.hpp>
#include <hamon/config.hpp>
#include <utility>

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
	return
		lhs[0] == rhs[0] &&
		lhs[1] == rhs[1] &&
		lhs[2] == rhs[2] &&
		lhs[3] == rhs[3];
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
->decltype(hamon::qvm::transform(v, hamon::negate<>{}))
{
	return hamon::qvm::transform(v, hamon::negate<>{});
}

/**
 *	@brief	Quaternion + Quaternion -> Quaternion
 */
template <typename T1, typename T2>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator+(quaternion<T1> const& lhs, quaternion<T2> const& rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::transform(lhs, rhs, hamon::plus<>{}))
{
	return hamon::qvm::transform(lhs, rhs, hamon::plus<>{});
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
->decltype(hamon::qvm::transform(lhs, rhs, hamon::minus<>{}))
{
	return hamon::qvm::transform(lhs, rhs, hamon::minus<>{});
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
->quaternion<decltype(std::declval<T1>() * std::declval<T2>())>
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
->decltype(hamon::qvm::transform(lhs, detail::multiplies_scalar<T2>{rhs}))
{
	return hamon::qvm::transform(lhs, detail::multiplies_scalar<T2>{rhs});
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
->decltype(hamon::qvm::transform(rhs, detail::multiplies_scalar<T2>{lhs}))
{
	return hamon::qvm::transform(rhs, detail::multiplies_scalar<T2>{lhs});
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
->decltype(hamon::qvm::transform(lhs, detail::divides_scalar<T2>{rhs}))
{
	return hamon::qvm::transform(lhs, detail::divides_scalar<T2>{rhs});
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

#endif // HAMON_QVM_QUATERNION_QUATERNION_HPP
