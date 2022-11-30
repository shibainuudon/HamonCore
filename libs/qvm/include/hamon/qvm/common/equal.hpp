/**
 *	@file	equal.hpp
 *
 *	@brief	equal の定義
 */

#ifndef HAMON_QVM_COMMON_EQUAL_HPP
#define HAMON_QVM_COMMON_EQUAL_HPP

#include <hamon/qvm/detail/transform.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	equal
 */
template <
	template <typename, std::size_t...> class GenType,
	typename T, std::size_t... Ns
>
HAMON_NODISCARD inline HAMON_CONSTEXPR GenType<bool, Ns...>
equal(GenType<T, Ns...> const& lhs, GenType<T, Ns...> const& rhs) HAMON_NOEXCEPT
{
	return hamon::qvm::detail::transform(lhs, rhs, hamon::equal_to<>{});
}

/**
 *	@brief	equal
 * 
 *	要素の型が違うときのオーバーロード
 */
template <
	template <typename, std::size_t...> class GenType,
	typename T1, typename T2, std::size_t... Ns
>
HAMON_NODISCARD inline HAMON_CONSTEXPR GenType<bool, Ns...>
equal(GenType<T1, Ns...> const& lhs, GenType<T2, Ns...> const& rhs) HAMON_NOEXCEPT
{
	using Common = GenType<hamon::common_type_t<T1, T2>, Ns...>;
	return equal(Common{lhs}, Common{rhs});
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_COMMON_EQUAL_HPP
