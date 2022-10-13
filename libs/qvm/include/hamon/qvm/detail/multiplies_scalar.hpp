/**
 *	@file	multiplies_scalar.hpp
 *
 *	@brief	multiplies_scalar の定義
 */

#ifndef HAMON_QVM_DETAIL_MULTIPLIES_SCALAR_HPP
#define HAMON_QVM_DETAIL_MULTIPLIES_SCALAR_HPP

#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename T>
struct multiplies_scalar
{
	T	m_value;

	template <typename U>
	HAMON_CONSTEXPR auto operator()(U&& lhs) const
	->decltype(std::forward<U>(lhs) * m_value)
	{
		return std::forward<U>(lhs) * m_value;
	}
};

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_DETAIL_MULTIPLIES_SCALAR_HPP
