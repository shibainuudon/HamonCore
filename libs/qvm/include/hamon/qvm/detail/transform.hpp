/**
 *	@file	transform.hpp
 *
 *	@brief	transform の定義
 */

#ifndef HAMON_QVM_DETAIL_TRANSFORM_HPP
#define HAMON_QVM_DETAIL_TRANSFORM_HPP

#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>
#include <cstddef>
#include <utility>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_GCC("-Wunused-but-set-parameter")

namespace hamon
{

namespace qvm
{

namespace detail
{

template <
	template <typename, std::size_t> class Vector,
	typename T1, std::size_t N0,
	typename F,
	typename T2 = decltype(std::declval<F>()(std::declval<T1>())),
	typename Result = Vector<T2, N0>,
	std::size_t... Is
>
HAMON_NODISCARD inline HAMON_CONSTEXPR Result
transform_impl(Vector<T1, N0> const& v, F unary_op, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
{
	return Result { unary_op(v[Is])... };
}

template <
	template <typename, std::size_t, std::size_t> class Matrix,
	typename T1, std::size_t N0, std::size_t N1,
	typename F,
	typename T2 = decltype(std::declval<F>()(std::declval<T1>())),
	typename Result = Matrix<T2, N0, N1>,
	std::size_t... Is
>
HAMON_NODISCARD inline HAMON_CONSTEXPR Result
transform_impl(Matrix<T1, N0, N1> const& m, F unary_op, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
{
	return Result { transform_impl(m[Is], unary_op, hamon::make_index_sequence<N1>{})... };
}

template <
	template <typename, std::size_t> class Vector,
	typename T1, typename T2, std::size_t N0,
	typename F,
	typename T3 = decltype(std::declval<F>()(std::declval<T1>(), std::declval<T2>())),
	typename Result = Vector<T3, N0>,
	std::size_t... Is
>
HAMON_NODISCARD inline HAMON_CONSTEXPR Result
transform_impl(Vector<T1, N0> const& lhs, Vector<T2, N0> const& rhs, F binary_op, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
{
	return Result { binary_op(lhs[Is], rhs[Is])... };
}

template <
	template <typename, std::size_t, std::size_t> class Matrix,
	typename T1, typename T2, std::size_t N0, std::size_t N1,
	typename F,
	typename T3 = decltype(std::declval<F>()(std::declval<T1>(), std::declval<T2>())),
	typename Result = Matrix<T3, N0, N1>,
	std::size_t... Is
>
HAMON_NODISCARD inline HAMON_CONSTEXPR Result
transform_impl(Matrix<T1, N0, N1> const& lhs, Matrix<T2, N0, N1> const& rhs, F binary_op, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
{
	return Result{ transform_impl(lhs[Is], rhs[Is], binary_op, hamon::make_index_sequence<N1>{})... };
}

/**
 *	@brief	transform (Unary operation)
 */
template <
	template <typename, std::size_t> class Vector,
	typename T, std::size_t N0,
	typename F
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
transform(Vector<T, N0> const& v, F unary_op) HAMON_NOEXCEPT
->decltype(detail::transform_impl(v, unary_op, hamon::make_index_sequence<N0>{}))
{
	return detail::transform_impl(v, unary_op, hamon::make_index_sequence<N0>{});
}

template <
	template <typename, std::size_t, std::size_t> class Matrix,
	typename T, std::size_t N0, std::size_t N1,
	typename F
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
transform(Matrix<T, N0, N1> const& v, F unary_op) HAMON_NOEXCEPT
->decltype(detail::transform_impl(v, unary_op, hamon::make_index_sequence<N0>{}))
{
	return detail::transform_impl(v, unary_op, hamon::make_index_sequence<N0>{});
}

/**
 *	@brief	transform (Binary operation)
 */
template <
	template <typename, std::size_t> class Vector,
	typename T1, typename T2, std::size_t N0,
	typename F
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
transform(Vector<T1, N0> const& lhs, Vector<T2, N0> const& rhs, F binary_op) HAMON_NOEXCEPT
->decltype(detail::transform_impl(lhs, rhs, binary_op, hamon::make_index_sequence<N0>{}))
{
	return detail::transform_impl(lhs, rhs, binary_op, hamon::make_index_sequence<N0>{});
}

template <
	template <typename, std::size_t, std::size_t> class Matrix,
	typename T1, typename T2, std::size_t N0, std::size_t N1,
	typename F
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
transform(Matrix<T1, N0, N1> const& lhs, Matrix<T2, N0, N1> const& rhs, F binary_op) HAMON_NOEXCEPT
->decltype(detail::transform_impl(lhs, rhs, binary_op, hamon::make_index_sequence<N0>{}))
{
	return detail::transform_impl(lhs, rhs, binary_op, hamon::make_index_sequence<N0>{});
}

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

HAMON_WARNING_POP()

#endif // HAMON_QVM_DETAIL_TRANSFORM_HPP
