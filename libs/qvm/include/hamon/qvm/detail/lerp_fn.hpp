/**
 *	@file	lerp_fn.hpp
 *
 *	@brief	lerp_fn の定義
 */

#ifndef HAMON_QVM_DETAIL_LERP_FN_HPP
#define HAMON_QVM_DETAIL_LERP_FN_HPP

#include <hamon/cmath/lerp.hpp>
#include <hamon/config.hpp>
#include <utility>

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
	->decltype(hamon::lerp(std::forward<U1>(lhs), std::forward<U2>(rhs), m_t))
	{
		return hamon::lerp(std::forward<U1>(lhs), std::forward<U2>(rhs), m_t);
	}
};

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_DETAIL_LERP_FN_HPP
