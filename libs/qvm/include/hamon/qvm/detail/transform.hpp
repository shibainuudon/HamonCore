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

HAMON_WARNING_PUSH();
HAMON_WARNING_DISABLE_GCC("-Wunused-but-set-parameter");

namespace hamon
{

namespace qvm
{

namespace detail
{

template <
	template <typename, std::size_t...> class GenType,
	typename T1, std::size_t N0,
	typename F,
	typename T2 = decltype(std::declval<F>()(std::declval<T1>())),
	typename Result = GenType<T2, N0>,
	std::size_t... Is
>
HAMON_NODISCARD inline HAMON_CONSTEXPR Result
transform_impl(GenType<T1, N0> const& v, F unary_op, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
{
	return Result { unary_op(v[Is])... };
}

template <
	template <typename, std::size_t...> class GenType,
	typename T1, std::size_t N0, std::size_t N1, std::size_t... Ns,
	typename F,
	typename T2 = decltype(std::declval<F>()(std::declval<T1>())),
	typename Result = GenType<T2, N0, N1, Ns...>,
	std::size_t... Is
>
HAMON_NODISCARD inline HAMON_CONSTEXPR Result
transform_impl(GenType<T1, N0, N1, Ns...> const& m, F unary_op, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
{
	return Result { transform_impl(m[Is], unary_op, hamon::make_index_sequence<N1>{})... };
}

template <
	template <typename, std::size_t...> class GenType,
	typename T1, typename T2, std::size_t N0,
	typename F,
	typename T3 = decltype(std::declval<F>()(std::declval<T1>(), std::declval<T2>())),
	typename Result = GenType<T3, N0>,
	std::size_t... Is
>
HAMON_NODISCARD inline HAMON_CONSTEXPR Result
transform_impl(GenType<T1, N0> const& lhs, GenType<T2, N0> const& rhs, F binary_op, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
{
	return Result { binary_op(lhs[Is], rhs[Is])... };
}

template <
	template <typename, std::size_t...> class GenType,
	typename T1, typename T2, std::size_t N0, std::size_t N1, std::size_t... Ns,
	typename F,
	typename T3 = decltype(std::declval<F>()(std::declval<T1>(), std::declval<T2>())),
	typename Result = GenType<T3, N0, N1, Ns...>,
	std::size_t... Is
>
HAMON_NODISCARD inline HAMON_CONSTEXPR Result
transform_impl(GenType<T1, N0, N1, Ns...> const& lhs, GenType<T2, N0, N1, Ns...> const& rhs, F binary_op, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
{
	return Result{ transform_impl(lhs[Is], rhs[Is], binary_op, hamon::make_index_sequence<N1>{})... };
}

/**
 *	@brief	transform (Unary operation)
 */
template <
	template <typename, std::size_t...> class GenType,
	typename T, std::size_t N0, std::size_t... Ns,
	typename F
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
transform(GenType<T, N0, Ns...> const& v, F unary_op) HAMON_NOEXCEPT
->decltype(detail::transform_impl(v, unary_op, hamon::make_index_sequence<N0>{}))
{
	return detail::transform_impl(v, unary_op, hamon::make_index_sequence<N0>{});
}

/**
 *	@brief	transform (Binary operation)
 */
template <
	template <typename, std::size_t...> class GenType,
	typename T1, typename T2, std::size_t N0, std::size_t... Ns,
	typename F
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
transform(GenType<T1, N0, Ns...> const& lhs, GenType<T2, N0, Ns...> const& rhs, F binary_op) HAMON_NOEXCEPT
->decltype(detail::transform_impl(lhs, rhs, binary_op, hamon::make_index_sequence<N0>{}))
{
	return detail::transform_impl(lhs, rhs, binary_op, hamon::make_index_sequence<N0>{});
}

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

HAMON_WARNING_POP();

#endif // HAMON_QVM_DETAIL_TRANSFORM_HPP
