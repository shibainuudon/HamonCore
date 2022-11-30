/**
 *	@file	minus.hpp
 *
 *	@brief	minus の定義
 */

#ifndef HAMON_QVM_DETAIL_MINUS_HPP
#define HAMON_QVM_DETAIL_MINUS_HPP

#include <hamon/qvm/detail/transform.hpp>
#include <hamon/functional/minus.hpp>
#include <hamon/type_traits/arithmetic_promote.hpp>
#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

namespace detail
{

/**
 *	@brief	minus
 */
template <
	template <typename, std::size_t...> class GenType,
	typename T, std::size_t... Ns
>
HAMON_NODISCARD inline HAMON_CONSTEXPR GenType<T, Ns...>
minus(GenType<T, Ns...> const& lhs, GenType<T, Ns...> const& rhs) HAMON_NOEXCEPT
{
	return hamon::qvm::detail::transform(lhs, rhs, hamon::minus<>{});
}

/**
 *	@brief	minus
 *
 *	要素の型が違うときのオーバーロード
 */
template <
	template <typename, std::size_t...> class GenType,
	typename T1, typename T2, std::size_t... Ns,
	typename T3 = hamon::arithmetic_promote_t<T1, T2>
>
HAMON_NODISCARD inline HAMON_CONSTEXPR GenType<T3, Ns...>
minus(GenType<T1, Ns...> const& lhs, GenType<T2, Ns...> const& rhs) HAMON_NOEXCEPT
{
	using Promoted = GenType<T3, Ns...>;
	return minus(Promoted{lhs}, Promoted{rhs});
}

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_DETAIL_MINUS_HPP
