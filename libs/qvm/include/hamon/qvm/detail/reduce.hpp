/**
 *	@file	reduce.hpp
 *
 *	@brief	reduce の定義
 */

#ifndef HAMON_QVM_DETAIL_REDUCE_HPP
#define HAMON_QVM_DETAIL_REDUCE_HPP

#include <hamon/functional/plus.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>
#include <cstddef>	// size_t

namespace hamon
{

namespace qvm
{

namespace detail
{

// vとinitが同じ型のときのオーバーロード
template <typename T, typename F>
HAMON_NODISCARD inline HAMON_CONSTEXPR T
reduce_impl(T v, T init, F binary_op, std::size_t) HAMON_NOEXCEPT
{
	return binary_op(init, v);
}

// reduce_implのループ
template <
	template <typename, std::size_t...> class GenType,
	typename T, std::size_t N0, std::size_t... Ns,
	typename U, typename F,
	typename = hamon::enable_if_t<N0 != 0>
>
HAMON_NODISCARD inline HAMON_CONSTEXPR U
reduce_impl(GenType<T, N0, Ns...> const& v, U init, F binary_op, std::size_t i) HAMON_NOEXCEPT
{
	return i == N0 ?
		init :
		reduce_impl(
			v,
			reduce_impl(v[i], init, binary_op, 0),
			binary_op,
			i+1);
}

// 要素数が0のときのオーバーロード
template <
	template <typename, std::size_t...> class GenType,
	typename T, std::size_t... Ns,
	typename U, typename F
>
HAMON_NODISCARD inline HAMON_CONSTEXPR U
reduce_impl(GenType<T, 0, Ns...> const&, U init, F, std::size_t) HAMON_NOEXCEPT
{
	return init;
}

template <
	template <typename, std::size_t...> class GenType,
	typename T,
	std::size_t... Ns,
	typename F = hamon::plus<>,
	typename U = decltype(hamon::declval<F>()(hamon::declval<T>(), hamon::declval<T>()))
>
HAMON_NODISCARD inline HAMON_CONSTEXPR U
reduce(GenType<T, Ns...> const& v, U init = {}, F binary_op = {}) HAMON_NOEXCEPT
{
	return detail::reduce_impl(v, init, binary_op, 0);
}

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_DETAIL_REDUCE_HPP
