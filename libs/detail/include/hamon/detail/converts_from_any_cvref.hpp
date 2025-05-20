/**
 *	@file	converts_from_any_cvref.hpp
 *
 *	@brief	converts_from_any_cvref の定義
 */

#ifndef HAMON_DETAIL_CONVERTS_FROM_ANY_CVREF_HPP
#define HAMON_DETAIL_CONVERTS_FROM_ANY_CVREF_HPP

#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_convertible.hpp>

namespace hamon
{

namespace detail
{

// [optional.ctor]/1
template <typename T, typename W>
using converts_from_any_cvref = hamon::disjunction<
	hamon::is_constructible<T, W&>,       hamon::is_convertible<W&,       T>,
	hamon::is_constructible<T, W>,        hamon::is_convertible<W,        T>,
	hamon::is_constructible<T, W const&>, hamon::is_convertible<W const&, T>,
	hamon::is_constructible<T, W const>,  hamon::is_convertible<W const,  T>
>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_DETAIL_CONVERTS_FROM_ANY_CVREF_HPP
