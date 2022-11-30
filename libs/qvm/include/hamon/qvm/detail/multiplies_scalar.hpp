/**
 *	@file	multiplies_scalar.hpp
 *
 *	@brief	multiplies_scalar の定義
 */

#ifndef HAMON_QVM_DETAIL_MULTIPLIES_SCALAR_HPP
#define HAMON_QVM_DETAIL_MULTIPLIES_SCALAR_HPP

#include <hamon/qvm/detail/transform.hpp>
#include <hamon/type_traits/arithmetic_promote.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <cstddef>
#include <type_traits>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename T>
struct multiplies_scalar_fn
{
	T	m_value;

	HAMON_CONSTEXPR T operator()(T const& lhs) const HAMON_NOEXCEPT
	{
		return lhs * m_value;
	}
};

/**
 *	@brief	multiplies_scalar
 */
template <
	template <typename, std::size_t...> class GenType,
	typename T1, typename T2, std::size_t... Ns,
	typename = hamon::enable_if_t<std::is_arithmetic<T2>::value>,
	typename T3 = hamon::arithmetic_promote_t<T1, T2>
>
HAMON_NODISCARD inline HAMON_CONSTEXPR GenType<T3, Ns...>
multiplies_scalar(GenType<T1, Ns...> const& lhs, T2 const& rhs) HAMON_NOEXCEPT
{
	using Promoted = GenType<T3, Ns...>;
	return hamon::qvm::detail::transform(Promoted{lhs}, multiplies_scalar_fn<T3>{static_cast<T3>(rhs)});
}

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_DETAIL_MULTIPLIES_SCALAR_HPP
