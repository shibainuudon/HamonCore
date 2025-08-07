/**
 *	@file	__create_format_arg.hpp
 *
 *	@brief	__create_format_arg の定義
 */

#ifndef HAMON_FORMAT___FORMAT___CREATE_FORMAT_ARG_HPP
#define HAMON_FORMAT___FORMAT___CREATE_FORMAT_ARG_HPP

#include <hamon/format/__format/__determine_arg_t.hpp>
#include <hamon/format/__format/__arg_t.hpp>
#include <hamon/format/detail/formattable_with.hpp>
#include <hamon/format/detail/__is_bounded_array_of.hpp>
#include <hamon/format/detail/__basic_format_arg_value.hpp>
#include <hamon/format/basic_format_arg.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/string/char_traits.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits/remove_const.hpp>
#include <hamon/type_traits/extent.hpp>

namespace hamon
{

namespace __format
{

// Pseudo constuctor for basic_format_arg
//
// Modeled after template<class T> explicit basic_format_arg(T& v) noexcept;
// [format.arg]/4-6
template <class _Context, class _Tp>
hamon::basic_format_arg<_Context> __create_format_arg(_Tp& __value) noexcept
{
	using _Dp               = hamon::remove_const_t<_Tp>;
	constexpr __format::__arg_t __arg = __format::__determine_arg_t<_Context, _Dp>();
	static_assert(__arg != __format::__arg_t::__none, "the supplied type is not formattable");
	static_assert(hamon::detail::formattable_with<_Tp, _Context>);

	using __context_char_type = typename _Context::char_type;
	// Not all types can be used to directly initialize the
	// __basic_format_arg_value.  First handle all types needing adjustment, the
	// final else requires no adjustment.
	if constexpr (__arg == __format::__arg_t::__char_type)
	{
		if constexpr (hamon::same_as<__context_char_type, wchar_t> && hamon::same_as<_Dp, char>)
		{
			return hamon::basic_format_arg<_Context>{__arg, static_cast<wchar_t>(static_cast<unsigned char>(__value))};
		}
		else
		{
			return hamon::basic_format_arg<_Context>{__arg, __value};
		}
	}
	else if constexpr (__arg == __format::__arg_t::__int)
	{
		return hamon::basic_format_arg<_Context>{__arg, static_cast<int>(__value)};
	}
	else if constexpr (__arg == __format::__arg_t::__long_long)
	{
		return hamon::basic_format_arg<_Context>{__arg, static_cast<long long>(__value)};
	}
	else if constexpr (__arg == __format::__arg_t::__unsigned)
	{
		return hamon::basic_format_arg<_Context>{__arg, static_cast<unsigned>(__value)};
	}
	else if constexpr (__arg == __format::__arg_t::__unsigned_long_long)
	{
		return hamon::basic_format_arg<_Context>{__arg, static_cast<unsigned long long>(__value)};
	}
	else if constexpr (__arg == __format::__arg_t::__string_view)
	{
		// Using std::size on a character array will add the NUL-terminator to the size.
		if constexpr (hamon::detail::__is_bounded_array_of<_Dp, __context_char_type>)
		{
			const __context_char_type* const __pbegin = hamon::begin(__value);
			const __context_char_type* const __pzero =
				hamon::char_traits<__context_char_type>::find(__pbegin, hamon::extent_v<_Dp>, __context_char_type {});
			//_LIBCPP_ASSERT_VALID_INPUT_RANGE(__pzero != nullptr, "formatting a non-null-terminated array");
			return hamon::basic_format_arg<_Context>{
				__arg, hamon::basic_string_view<__context_char_type>{__pbegin, static_cast<size_t>(__pzero - __pbegin)}};
		}
		else
		{
			// When the _Traits or _Allocator are different an implicit conversion will fail.
			return hamon::basic_format_arg<_Context>{__arg, hamon::basic_string_view<__context_char_type>{__value.data(), __value.size()}};
		}
	}
	else if constexpr (__arg == __format::__arg_t::__ptr)
	{
		return hamon::basic_format_arg<_Context>{__arg, static_cast<const void*>(__value)};
	}
	else if constexpr (__arg == __format::__arg_t::__handle)
	{
		return hamon::basic_format_arg<_Context>{__arg, typename hamon::detail::__basic_format_arg_value<_Context>::__handle {__value}};
	}
	else
	{
		return hamon::basic_format_arg<_Context>{__arg, __value};
	}
}

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___CREATE_FORMAT_ARG_HPP
