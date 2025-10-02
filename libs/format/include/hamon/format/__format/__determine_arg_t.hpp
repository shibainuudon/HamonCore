/**
 *	@file	__determine_arg_t.hpp
 *
 *	@brief	__determine_arg_t の定義
 */

#ifndef HAMON_FORMAT___FORMAT___DETERMINE_ARG_T_HPP
#define HAMON_FORMAT___FORMAT___DETERMINE_ARG_T_HPP

#include <hamon/format/__format/__arg_t.hpp>
#include <hamon/format/__format/__signed_integer.hpp>
#include <hamon/format/__format/__unsigned_integer.hpp>
#include <hamon/format/detail/formattable_with.hpp>
#include <hamon/format/detail/__is_bounded_array_of.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/string_view.hpp>
#include <hamon/string.hpp>

namespace hamon
{

namespace __format
{

/// \returns The @c __arg_t based on the type of the formatting argument.
///
/// \pre \c __formattable<_Tp, typename _Context::char_type>
template <class _Context, class _Tp>
consteval __arg_t __determine_arg_t();

// Boolean
template <class, same_as<bool> _Tp>
consteval __arg_t __determine_arg_t()
{
	return __arg_t::__boolean;
}

// Char
template <class _Context, same_as<typename _Context::char_type> _Tp>
consteval __arg_t __determine_arg_t()
{
	return __arg_t::__char_type;
}
template <class _Context, class _CharT>
	requires(same_as<typename _Context::char_type, wchar_t>&& same_as<_CharT, char>)
consteval __arg_t __determine_arg_t()
{
	return __arg_t::__char_type;
}

// Signed integers
template <class, __signed_integer _Tp>
consteval __arg_t __determine_arg_t()
{
	if constexpr (sizeof(_Tp) <= sizeof(int))
		return __arg_t::__int;
	else if constexpr (sizeof(_Tp) <= sizeof(long long))
		return __arg_t::__long_long;
	else
		static_assert(sizeof(_Tp) == 0, "an unsupported signed integer was used");
}

// Unsigned integers
template <class, __unsigned_integer _Tp>
consteval __arg_t __determine_arg_t()
{
	if constexpr (sizeof(_Tp) <= sizeof(unsigned))
		return __arg_t::__unsigned;
	else if constexpr (sizeof(_Tp) <= sizeof(unsigned long long))
		return __arg_t::__unsigned_long_long;
	else
		static_assert(sizeof(_Tp) == 0, "an unsupported unsigned integer was used");
}

// Floating-point
template <class, same_as<float> _Tp>
consteval __arg_t __determine_arg_t()
{
	return __arg_t::__float;
}
template <class, same_as<double> _Tp>
consteval __arg_t __determine_arg_t()
{
	return __arg_t::__double;
}
template <class, same_as<long double> _Tp>
consteval __arg_t __determine_arg_t()
{
	return __arg_t::__long_double;
}

// Char pointer
template <class _Context, class _Tp>
	requires(same_as<typename _Context::char_type*, _Tp> || same_as<const typename _Context::char_type*, _Tp>)
consteval __arg_t __determine_arg_t()
{
	return __arg_t::__const_char_type_ptr;
}

// Char array
template <class _Context, class _Tp>
	requires hamon::detail::__is_bounded_array_of<_Tp, typename _Context::char_type>
consteval __arg_t __determine_arg_t()
{
	return __arg_t::__string_view;
}

// String view
template <class _Context, class _Tp>
	requires(same_as<typename _Context::char_type, typename _Tp::value_type>&&
same_as<_Tp, basic_string_view<typename _Tp::value_type, typename _Tp::traits_type>>)
consteval __arg_t __determine_arg_t()
{
	return __arg_t::__string_view;
}

// String
template <class _Context, class _Tp>
	requires(
same_as<typename _Context::char_type, typename _Tp::value_type>&&
same_as<_Tp, basic_string<typename _Tp::value_type, typename _Tp::traits_type, typename _Tp::allocator_type>>)
consteval __arg_t __determine_arg_t()
{
	return __arg_t::__string_view;
}

// Pointers
template <class, class _Ptr>
	requires(same_as<_Ptr, void*> || same_as<_Ptr, const void*> || same_as<_Ptr, nullptr_t>)
consteval __arg_t __determine_arg_t()
{
	return __arg_t::__ptr;
}

// Handle
//
// Note this version can't be constrained avoiding ambiguous overloads.
// That means it can be instantiated by disabled formatters. To solve this, a
// constrained version for not formattable formatters is added.
template <class _Context, class _Tp>
consteval __arg_t __determine_arg_t()
{
	return __arg_t::__handle;
}

// The overload for not formattable types allows triggering the static
// assertion below.
template <class _Context, class _Tp>
	requires(!hamon::detail::formattable_with<_Tp, _Context>)
consteval __arg_t __determine_arg_t()
{
	return __arg_t::__none;
}

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___DETERMINE_ARG_T_HPP
