/**
 *	@file	operators.hpp
 *
 *	@brief	operators の定義
 */

#ifndef HAMON_QVM_VECTOR_OPERATORS_HPP
#define HAMON_QVM_VECTOR_OPERATORS_HPP

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/qvm/common/all.hpp>
#include <hamon/qvm/common/equal.hpp>
#include <hamon/qvm/detail/plus.hpp>
#include <hamon/qvm/detail/minus.hpp>
#include <hamon/qvm/detail/multiplies.hpp>
#include <hamon/qvm/detail/divides.hpp>
#include <hamon/qvm/detail/transform.hpp>
#include <hamon/qvm/detail/multiplies_scalar.hpp>
#include <hamon/qvm/detail/divides_scalar.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/functional/negate.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/functional/minus.hpp>
#include <hamon/functional/multiplies.hpp>
#include <hamon/functional/divides.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	operator==
 */
template <typename T1, typename T2, hamon::size_t N>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator==(vector<T1, N> const& lhs, vector<T2, N> const& rhs) HAMON_NOEXCEPT
{
	return hamon::qvm::all(hamon::qvm::equal(lhs, rhs));
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

/**
 *	@brief	operator!=
 */
template <typename T1, typename T2, hamon::size_t N>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator!=(vector<T1, N> const& lhs, vector<T2, N> const& rhs) HAMON_NOEXCEPT
{
	return !(lhs == rhs);
}

#endif

/**
 *	@brief	unary operator+
 */
template <typename T, hamon::size_t N>
HAMON_NODISCARD inline HAMON_CONSTEXPR vector<T, N>
operator+(vector<T, N> const& v) HAMON_NOEXCEPT
{
	return v;
}

/**
 *	@brief	unary operator-
 */
template <typename T, hamon::size_t N>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator-(vector<T, N> const& v) HAMON_NOEXCEPT
->decltype(hamon::qvm::detail::transform(v, hamon::negate<>{}))
{
	return hamon::qvm::detail::transform(v, hamon::negate<>{});
}

/**
 *	@brief	Vector + Vector -> Vector
 */
template <typename T1, typename T2, hamon::size_t N>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator+(vector<T1, N> const& lhs, vector<T2, N> const& rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::detail::plus(lhs, rhs))
{
	return hamon::qvm::detail::plus(lhs, rhs);
}

/**
 *	@brief	Vector += Vector
 */
template <typename T1, typename T2, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR vector<T1, N>&
operator+=(vector<T1, N>& lhs, vector<T2, N> const& rhs) HAMON_NOEXCEPT
{
	return lhs = lhs + rhs;
}

/**
 *	@brief	Vector - Vector -> Vector
 */
template <typename T1, typename T2, hamon::size_t N>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator-(vector<T1, N> const& lhs, vector<T2, N> const& rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::detail::minus(lhs, rhs))
{
	return hamon::qvm::detail::minus(lhs, rhs);
}

/**
 *	@brief	Vector -= Vector
 */
template <typename T1, typename T2, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR vector<T1, N>&
operator-=(vector<T1, N>& lhs, vector<T2, N> const& rhs) HAMON_NOEXCEPT
{
	return lhs = lhs - rhs;
}

/**
 *	@brief	Vector * Vector -> Vector
 */
template <typename T1, typename T2, hamon::size_t N>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator*(vector<T1, N> const& lhs, vector<T2, N> const& rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::detail::multiplies(lhs, rhs))
{
	return hamon::qvm::detail::multiplies(lhs, rhs);
}

/**
 *	@brief	Vector *= Vector
 */
template <typename T1, typename T2, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR vector<T1, N>&
operator*=(vector<T1, N>& lhs, vector<T2, N> const& rhs) HAMON_NOEXCEPT
{
	return lhs = lhs * rhs;
}

/**
 *	@brief	Vector / Vector -> Vector
 */
template <typename T1, typename T2, hamon::size_t N>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator/(vector<T1, N> const& lhs, vector<T2, N> const& rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::detail::divides(lhs, rhs))
{
	return hamon::qvm::detail::divides(lhs, rhs);
}

/**
 *	@brief	Vector /= Vector
 */
template <typename T1, typename T2, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR vector<T1, N>&
operator/=(vector<T1, N>& lhs, vector<T2, N> const& rhs) HAMON_NOEXCEPT
{
	return lhs = lhs / rhs;
}

/**
 *	@brief	Vector * スカラー -> Vector
 */
template <
	typename T1, hamon::size_t N,
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, T2)
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator*(vector<T1, N> const& lhs, T2 rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::detail::multiplies_scalar(lhs, rhs))
{
	return hamon::qvm::detail::multiplies_scalar(lhs, rhs);
}

/**
 *	@brief	スカラー * Vector -> Vector
 */
template <
	typename T1, hamon::size_t N,
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, T2)
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator*(T2 lhs, vector<T1, N> const& rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::detail::multiplies_scalar(rhs, lhs))
{
	return hamon::qvm::detail::multiplies_scalar(rhs, lhs);
}

/**
 *	@brief	Vector *= スカラー
 */
template <
	typename T1, hamon::size_t N,
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, T2)
>
inline HAMON_CXX14_CONSTEXPR vector<T1, N>&
operator*=(vector<T1, N>& lhs, T2 rhs) HAMON_NOEXCEPT
{
	return lhs = lhs * rhs;
}

/**
 *	@brief	Vector / スカラー -> Vector
 */
template <
	typename T1, hamon::size_t N,
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, T2)
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator/(vector<T1, N> const& lhs, T2 rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::detail::divides_scalar(lhs, rhs))
{
	return hamon::qvm::detail::divides_scalar(lhs, rhs);
}

/**
 *	@brief	Vector /= スカラー
 */
template <
	typename T1, hamon::size_t N,
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, T2)
>
inline HAMON_CXX14_CONSTEXPR vector<T1, N>&
operator/=(vector<T1, N>& lhs, T2 rhs) HAMON_NOEXCEPT
{
	return lhs = lhs / rhs;
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_VECTOR_OPERATORS_HPP
