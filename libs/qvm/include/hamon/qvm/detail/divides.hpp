/**
 *	@file	divides.hpp
 *
 *	@brief	divides の定義
 */

#ifndef HAMON_QVM_DETAIL_DIVIDES_HPP
#define HAMON_QVM_DETAIL_DIVIDES_HPP

#include <hamon/qvm/detail/transform.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/functional/divides.hpp>
#include <hamon/type_traits/arithmetic_promote.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

namespace detail
{

/**
 *	@brief	divides
 */
template <
	template <typename, hamon::size_t...> class GenType,
	typename T, hamon::size_t... Ns
>
HAMON_NODISCARD inline HAMON_CONSTEXPR GenType<T, Ns...>
divides(GenType<T, Ns...> const& lhs, GenType<T, Ns...> const& rhs) HAMON_NOEXCEPT
{
	return hamon::qvm::detail::transform(lhs, rhs, hamon::divides<>{});
}

/**
 *	@brief	divides
 *
 *	要素の型が違うときのオーバーロード
 */
template <
	template <typename, hamon::size_t...> class GenType,
	typename T1, typename T2, hamon::size_t... Ns,
	typename T3 = hamon::arithmetic_promote_t<T1, T2>
>
HAMON_NODISCARD inline HAMON_CONSTEXPR GenType<T3, Ns...>
divides(GenType<T1, Ns...> const& lhs, GenType<T2, Ns...> const& rhs) HAMON_NOEXCEPT
{
	using Promoted = GenType<T3, Ns...>;
	return divides(Promoted{lhs}, Promoted{rhs});
}

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_DETAIL_DIVIDES_HPP
