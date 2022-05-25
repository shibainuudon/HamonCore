/**
 *	@file	cref.hpp
 *
 *	@brief	cref の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_CREF_HPP
#define HAMON_CONCEPTS_DETAIL_CREF_HPP

#include <hamon/type_traits/remove_reference.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
using cref = const hamon::remove_reference_t<T>&;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_CREF_HPP
