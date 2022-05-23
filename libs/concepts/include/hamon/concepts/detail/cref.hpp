/**
 *	@file	cref.hpp
 *
 *	@brief	cref の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_CREF_HPP
#define HAMON_CONCEPTS_DETAIL_CREF_HPP

#include <type_traits>

namespace hamon
{

namespace detail
{

template <typename T>
using cref = const typename std::remove_reference<T>::type&;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_CREF_HPP
