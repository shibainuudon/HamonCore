/**
 *	@file	transform.hpp
 *
 *	@brief	transform の定義
 */

#ifndef HAMON_QVM_DETAIL_TRANSFORM_HPP
#define HAMON_QVM_DETAIL_TRANSFORM_HPP

#include <hamon/qvm/detail/vector_rank.hpp>
#include <hamon/qvm/detail/vector_element.hpp>
#include <hamon/qvm/detail/vector_size.hpp>
#include <hamon/qvm/detail/rebind.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <cstddef>
#include <utility>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <
	typename Vector,
	typename F,
	typename T = hamon::qvm::detail::vector_element_t<Vector>,
	typename T2 = decltype(std::declval<F>()(std::declval<T>())),
	typename = hamon::enable_if_t<detail::vector_rank<Vector>::value == 1>,
	std::size_t... Is
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
transform_impl(Vector const& v, F unary_op, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
->detail::rebind_t<Vector, T2>
{
	return { unary_op(v[Is])... };
}

template <
	typename Matrix,
	typename F,
	typename T = hamon::qvm::detail::vector_element_t<Matrix>,
	typename T2 = decltype(std::declval<F>()(std::declval<T>())),
	typename = hamon::enable_if_t<(detail::vector_rank<Matrix>::value > 1)>,
	std::size_t M = hamon::qvm::detail::vector_size<typename Matrix::value_type>::value,
	std::size_t... Is
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
transform_impl(Matrix const& m, F unary_op, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
->detail::rebind_t<Matrix, T2>
{
	return { transform_impl(m[Is], unary_op, hamon::make_index_sequence<M>{})... };
}

template <
	typename Vector1,
	typename Vector2,
	typename F,
	typename T1 = hamon::qvm::detail::vector_element_t<Vector1>,
	typename T2 = hamon::qvm::detail::vector_element_t<Vector2>,
	typename T3 = decltype(std::declval<F>()(std::declval<T1>(), std::declval<T2>())),
	typename = hamon::enable_if_t<detail::vector_rank<Vector1>::value == 1>,
	std::size_t... Is
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
transform_impl(Vector1 const& lhs, Vector2 const& rhs, F binary_op, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
->detail::rebind_t<Vector1, T3>
{
	return { binary_op(lhs[Is], rhs[Is])... };
}

template <
	typename Matrix1,
	typename Matrix2,
	typename F,
	typename T1 = hamon::qvm::detail::vector_element_t<Matrix1>,
	typename T2 = hamon::qvm::detail::vector_element_t<Matrix2>,
	typename T3 = decltype(std::declval<F>()(std::declval<T1>(), std::declval<T2>())),
	typename = hamon::enable_if_t<(detail::vector_rank<Matrix1>::value > 1)>,
	std::size_t M1 = hamon::qvm::detail::vector_size<typename Matrix1::value_type>::value,
	std::size_t M2 = hamon::qvm::detail::vector_size<typename Matrix2::value_type>::value,
	std::size_t... Is
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
transform_impl(Matrix1 const& lhs, Matrix2 const& rhs, F binary_op, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
->detail::rebind_t<Matrix1, T3>
{
	return { transform_impl(lhs[Is], rhs[Is], binary_op, hamon::make_index_sequence<M1>{})... };
}

}	// namespace detail

template <
	typename Vector,
	typename F,
	typename T = hamon::qvm::detail::vector_element_t<Vector>,
	std::size_t N = hamon::qvm::detail::vector_size<Vector>::value
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
transform(Vector const& v, F unary_op) HAMON_NOEXCEPT
->decltype(detail::transform_impl(v, unary_op, hamon::make_index_sequence<N>{}))
{
	return detail::transform_impl(v, unary_op, hamon::make_index_sequence<N>{});
}

template <
	typename Vector1,
	typename Vector2,
	typename F,
	typename T1 = hamon::qvm::detail::vector_element_t<Vector1>,
	typename T2 = hamon::qvm::detail::vector_element_t<Vector2>,
	std::size_t N1 = hamon::qvm::detail::vector_size<Vector1>::value,
	std::size_t N2 = hamon::qvm::detail::vector_size<Vector2>::value,
	typename = hamon::enable_if_t<N1 == N2>,
	typename = hamon::enable_if_t<
		detail::vector_rank<Vector1>::value ==
		detail::vector_rank<Vector2>::value
	>
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
transform(Vector1 const& lhs, Vector2 const& rhs, F binary_op) HAMON_NOEXCEPT
->decltype(detail::transform_impl(lhs, rhs, binary_op, hamon::make_index_sequence<N1>{}))
{
	return detail::transform_impl(lhs, rhs, binary_op, hamon::make_index_sequence<N1>{});
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_DETAIL_TRANSFORM_HPP
