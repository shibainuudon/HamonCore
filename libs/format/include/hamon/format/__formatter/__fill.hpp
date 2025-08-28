/**
 *	@file	__fill.hpp
 *
 *	@brief	__fill の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FILL_HPP
#define HAMON_FORMAT___FORMATTER___FILL_HPP

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/format/__format/__output_buffer.hpp>
#include <hamon/format/__format/__retarget_buffer.hpp>
#include <hamon/format/__format_spec/__code_point.hpp>
#include <hamon/algorithm/ranges/fill_n.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/iterator/back_insert_iterator.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

namespace __formatter
{

/// Fill wrapper.
///
/// This uses a "mass output function" of __format::__output_buffer when possible.
template <__format::__fmt_char_type _CharT, hamon::output_iterator<const _CharT&> _OutIt>
_OutIt __fill(_OutIt __out_it, size_t __n, _CharT __value)
{
	if constexpr (hamon::same_as<decltype(__out_it), hamon::back_insert_iterator<__format::__output_buffer<_CharT>>>)
	{
		__out_it.__get_container()->__fill(__n, __value);
		return __out_it;
	}
	else if constexpr (hamon::same_as<decltype(__out_it), typename __format::__retarget_buffer<_CharT>::__iterator>)
	{
		__out_it.__buffer_->__fill(__n, __value);
		return __out_it;
	}
	else
	{
		return hamon::ranges::fill_n(hamon::move(__out_it), __n, __value);
	}
}

#  if _LIBCPP_HAS_UNICODE
template <__format::__fmt_char_type _CharT, hamon::output_iterator<const _CharT&> _OutIt>
requires(hamon::same_as<_CharT, char>)
_OutIt __fill(_OutIt __out_it, size_t __n, __format_spec::__code_point<_CharT> __value)
{
	std::size_t __bytes = std::countl_one(static_cast<unsigned char>(__value.__data[0]));
	if (__bytes == 0)
	{
		return __formatter::__fill(hamon::move(__out_it), __n, __value.__data[0]);
	}

	for (size_t __i = 0; __i < __n; ++__i)
	{
		__out_it = __formatter::__copy(
			std::addressof(__value.__data[0]), std::addressof(__value.__data[0]) + __bytes, hamon::move(__out_it));
	}
	return __out_it;
}

template <__format::__fmt_char_type _CharT, hamon::output_iterator<const _CharT&> _OutIt>
requires(hamon::same_as<_CharT, wchar_t> && sizeof(wchar_t) == 2)
_OutIt __fill(_OutIt __out_it, size_t __n, __format_spec::__code_point<_CharT> __value)
{
	if (!__unicode::__is_high_surrogate(__value.__data[0]))
	{
		return __formatter::__fill(hamon::move(__out_it), __n, __value.__data[0]);
	}

	for (size_t __i = 0; __i < __n; ++__i)
	{
		__out_it = __formatter::__copy(
			std::addressof(__value.__data[0]), std::addressof(__value.__data[0]) + 2, hamon::move(__out_it));
	}
	return __out_it;
}

template <__format::__fmt_char_type _CharT, hamon::output_iterator<const _CharT&> _OutIt>
requires(hamon::same_as<_CharT, wchar_t> && sizeof(wchar_t) == 4)
_OutIt __fill(_OutIt __out_it, size_t __n, __format_spec::__code_point<_CharT> __value)
{
	return __formatter::__fill(hamon::move(__out_it), __n, __value.__data[0]);
}
#  else    // _LIBCPP_HAS_UNICODE
template <__format::__fmt_char_type _CharT, hamon::output_iterator<const _CharT&> _OutIt>
_OutIt __fill(_OutIt __out_it, size_t __n, __format_spec::__code_point<_CharT> __value)
{
	return __formatter::__fill(hamon::move(__out_it), __n, __value.__data[0]);
}
#  endif   // _LIBCPP_HAS_UNICODE


}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___FILL_HPP
