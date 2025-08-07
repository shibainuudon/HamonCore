/**
 *	@file	__is_bounded_array_of.hpp
 *
 *	@brief	__is_bounded_array_of の定義
 */

#ifndef HAMON_FORMAT_DETAIL___IS_BOUNDED_ARRAY_OF_HPP
#define HAMON_FORMAT_DETAIL___IS_BOUNDED_ARRAY_OF_HPP


namespace hamon
{

namespace detail
{

template <class _Arr, class _Elem>
inline constexpr bool __is_bounded_array_of = false;

template <class _Elem, size_t _Len>
inline constexpr bool __is_bounded_array_of<_Elem[_Len], _Elem> = true;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORMAT_DETAIL___IS_BOUNDED_ARRAY_OF_HPP
