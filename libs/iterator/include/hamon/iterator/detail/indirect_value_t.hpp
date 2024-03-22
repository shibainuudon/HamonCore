/**
 *	@file	indirect_value_t.hpp
 *
 *	@brief	indirect_value_t の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_INDIRECT_VALUE_T_HPP
#define HAMON_ITERATOR_DETAIL_INDIRECT_VALUE_T_HPP

#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>

namespace hamon
{

namespace detail
{

// 25.3.6.2 Indirect callable traits[indirectcallable.traits]

template <typename T>
struct indirect_value_impl
{
	// [indirectcallable.traits]/1.2
	using type = hamon::iter_value_t<T>&;
};

template <HAMON_CONSTRAINED_PARAM(hamon::indirectly_readable, T)>
using indirect_value_t = typename indirect_value_impl<T>::type;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_INDIRECT_VALUE_T_HPP
