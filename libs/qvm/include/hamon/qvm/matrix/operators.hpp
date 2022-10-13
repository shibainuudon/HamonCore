/**
 *	@file	operators.hpp
 *
 *	@brief	operators の定義
 */

#ifndef HAMON_QVM_MATRIX_OPERATORS_HPP
#define HAMON_QVM_MATRIX_OPERATORS_HPP

#include <hamon/qvm/matrix/matrix.hpp>
#include <hamon/qvm/matrix/all.hpp>
#include <hamon/qvm/matrix/equal.hpp>
#include <hamon/qvm/matrix/detail/mul_matrix.hpp>
#include <hamon/qvm/detail/transform.hpp>
#include <hamon/qvm/detail/multiplies_scalar.hpp>
#include <hamon/qvm/detail/divides_scalar.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/negate.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/functional/minus.hpp>
#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	operator==
 */
template <typename T1, typename T2, std::size_t R, std::size_t C>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator==(matrix<T1, R, C> const& lhs, matrix<T2, R, C> const& rhs) HAMON_NOEXCEPT
{
	return hamon::qvm::all(hamon::qvm::equal(lhs, rhs));
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

/**
 *	@brief	operator!=
 */
template <typename T1, typename T2, std::size_t R, std::size_t C>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator!=(matrix<T1, R, C> const& lhs, matrix<T2, R, C> const& rhs) HAMON_NOEXCEPT
{
	return !(lhs == rhs);
}

#endif

/**
 *	@brief	unary operator+
 */
template <typename T, std::size_t R, std::size_t C>
HAMON_NODISCARD inline HAMON_CONSTEXPR matrix<T, R, C>
operator+(matrix<T, R, C> const& v) HAMON_NOEXCEPT
{
	return v;
}

/**
 *	@brief	unary operator-
 */
template <typename T, std::size_t R, std::size_t C>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator-(matrix<T, R, C> const& v) HAMON_NOEXCEPT
->decltype(hamon::qvm::transform(v, hamon::negate<>{}))
{
	return hamon::qvm::transform(v, hamon::negate<>{});
}

/**
 *	@brief	Matrix + Matrix -> Matrix
 */
template <typename T1, typename T2, std::size_t R, std::size_t C>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator+(matrix<T1, R, C> const& lhs, matrix<T2, R, C> const& rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::transform(lhs, rhs, hamon::plus<>{}))
{
	return hamon::qvm::transform(lhs, rhs, hamon::plus<>{});
}

/**
 *	@brief	Matrix += Matrix
 */
template <typename T1, typename T2, std::size_t R, std::size_t C>
inline HAMON_CXX14_CONSTEXPR matrix<T1, R, C>&
operator+=(matrix<T1, R, C>& lhs, matrix<T2, R, C> const& rhs) HAMON_NOEXCEPT
{
	return lhs = lhs + rhs;
}

/**
 *	@brief	Matrix - Matrix -> Matrix
 */
template <typename T1, typename T2, std::size_t R, std::size_t C>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator-(matrix<T1, R, C> const& lhs, matrix<T2, R, C> const& rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::transform(lhs, rhs, hamon::minus<>{}))
{
	return hamon::qvm::transform(lhs, rhs, hamon::minus<>{});
}

/**
 *	@brief	Matrix -= Matrix
 */
template <typename T1, typename T2, std::size_t R, std::size_t C>
inline HAMON_CXX14_CONSTEXPR matrix<T1, R, C>&
operator-=(matrix<T1, R, C>& lhs, matrix<T2, R, C> const& rhs) HAMON_NOEXCEPT
{
	return lhs = lhs - rhs;
}

/**
 *	@brief	Matrix * Matrix -> Matrix
 */
template <
	typename T1, typename T2,
	std::size_t N, std::size_t M, std::size_t L
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator*(matrix<T1, N, L> const& lhs, matrix<T2, L, M> const& rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::detail::mul_matrix(lhs, rhs))
{
	return hamon::qvm::detail::mul_matrix(lhs, rhs);
}

/**
 *	@brief	Matrix *= Matrix
 */
template <
	typename T1, typename T2,
	std::size_t N, std::size_t M
>
inline HAMON_CXX14_CONSTEXPR matrix<T1, N, M>&
operator*=(matrix<T1, N, M>& lhs, matrix<T2, M, M> const& rhs) HAMON_NOEXCEPT
{
	return lhs = lhs * rhs;
}

/**
 *	@brief	Matrix * スカラー -> Matrix
 */
template <
	typename T1, std::size_t R, std::size_t C,
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, T2)
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator*(matrix<T1, R, C> const& lhs, T2 rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::transform(lhs, detail::multiplies_scalar<T2>{rhs}))
{
	return hamon::qvm::transform(lhs, detail::multiplies_scalar<T2>{rhs});
}

/**
 *	@brief	スカラー * Matrix -> Matrix
 */
template <
	typename T1, std::size_t R, std::size_t C,
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, T2)
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator*(T2 lhs, matrix<T1, R, C> const& rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::transform(rhs, detail::multiplies_scalar<T2>{lhs}))
{
	return hamon::qvm::transform(rhs, detail::multiplies_scalar<T2>{lhs});
}

/**
 *	@brief	Matrix *= スカラー
 */
template <
	typename T1, std::size_t R, std::size_t C,
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, T2)
>
inline HAMON_CXX14_CONSTEXPR matrix<T1, R, C>&
operator*=(matrix<T1, R, C>& lhs, T2 rhs) HAMON_NOEXCEPT
{
	return lhs = lhs * rhs;
}

/**
 *	@brief	Matrix / スカラー -> Matrix
 */
template <
	typename T1, std::size_t R, std::size_t C,
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, T2)
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator/(matrix<T1, R, C> const& lhs, T2 rhs) HAMON_NOEXCEPT
->decltype(hamon::qvm::transform(lhs, detail::divides_scalar<T2>{rhs}))
{
	return hamon::qvm::transform(lhs, detail::divides_scalar<T2>{rhs});
}

/**
 *	@brief	Matrix /= スカラー
 */
template <
	typename T1, std::size_t R, std::size_t C,
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, T2)
>
inline HAMON_CXX14_CONSTEXPR matrix<T1, R, C>&
operator/=(matrix<T1, R, C>& lhs, T2 rhs) HAMON_NOEXCEPT
{
	return lhs = lhs / rhs;
}

/**
 *	@brief	Vector * Matrix
 */
template <
	typename T1, typename T2,
	std::size_t N, std::size_t M,
	typename T3 = decltype(std::declval<T1>() * std::declval<T2>())
>
HAMON_NODISCARD inline HAMON_CONSTEXPR vector<T3, M>
operator*(vector<T1, N> const& lhs, matrix<T2, N, M> const& rhs) HAMON_NOEXCEPT
{
	return *((matrix<T1, 1, N>{ lhs } * rhs).cbegin());	// C++11でもconstexprにするため、const版のメンバ関数を呼び出す必要がある
}

/**
 *	@brief	Vector *= Matrix
 */
template <typename T1, typename T2, std::size_t N>
inline HAMON_CXX14_CONSTEXPR vector<T1, N>&
operator*=(vector<T1, N>& lhs, matrix<T2, N, N> const& rhs) HAMON_NOEXCEPT
{
	return lhs = lhs * rhs;
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_OPERATORS_HPP
