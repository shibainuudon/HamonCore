﻿/**
 *	@file	lerp.hpp
 *
 *	@brief	lerp の定義
 */

#ifndef HAMON_QVM_COMMON_LERP_HPP
#define HAMON_QVM_COMMON_LERP_HPP

#include <hamon/qvm/detail/transform.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cmath/lerp.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename T>
struct lerp_fn
{
	T	m_t;

	template <typename U1, typename U2>
	HAMON_CONSTEXPR auto operator()(U1&& lhs, U2&& rhs) const
	->decltype(hamon::lerp(hamon::forward<U1>(lhs), hamon::forward<U2>(rhs), m_t))
	{
		return hamon::lerp(hamon::forward<U1>(lhs), hamon::forward<U2>(rhs), m_t);
	}
};

}	// namespace detail

/**
 *	@brief	lerp
 */
template <
	template <typename, hamon::size_t...> class GenType,
	typename T1, hamon::size_t... Ns,
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, T2)
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
lerp(GenType<T1, Ns...> const& from, GenType<T1, Ns...> const& to, T2 const& t) HAMON_NOEXCEPT
->decltype(hamon::qvm::detail::transform(from, to, hamon::qvm::detail::lerp_fn<T2>{t}))
{
	return hamon::qvm::detail::transform(from, to, hamon::qvm::detail::lerp_fn<T2>{t});
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_COMMON_LERP_HPP
