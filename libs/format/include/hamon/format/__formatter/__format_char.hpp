/**
 *	@file	__format_char.hpp
 *
 *	@brief	__format_char の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FORMAT_CHAR_HPP
#define HAMON_FORMAT___FORMATTER___FORMAT_CHAR_HPP

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/format/__format_spec/__parsed_specifications.hpp>
#include <hamon/format/__formatter/__write.hpp>
#include <hamon/format/format_error.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/signed_integral.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/limits.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

namespace __formatter
{

template <__format::__fmt_char_type _CharT>
auto
__format_char(hamon::integral auto __value,
			  hamon::output_iterator<const _CharT&> auto __out_it,
			  __format_spec::__parsed_specifications<_CharT> __specs) -> decltype(__out_it)
{
	using _Tp = decltype(__value);
	if constexpr (!hamon::same_as<_CharT, _Tp>)
	{
		// cmp_less and cmp_greater can't be used for character types.
		if constexpr (hamon::signed_integral<_CharT> == hamon::signed_integral<_Tp>)
		{
			if (__value < hamon::numeric_limits<_CharT>::min() || __value > hamon::numeric_limits<_CharT>::max())
			{
				hamon::detail::throw_format_error("Integral value outside the range of the char type");
			}
		}
		else if constexpr (hamon::signed_integral<_CharT>)
		{
			// _CharT is signed _Tp is unsigned
			if (__value > static_cast<hamon::make_unsigned_t<_CharT>>(hamon::numeric_limits<_CharT>::max()))
			{
				hamon::detail::throw_format_error("Integral value outside the range of the char type");
			}
		}
		else
		{
			// _CharT is unsigned _Tp is signed
			if (__value < 0 || static_cast<hamon::make_unsigned_t<_Tp>>(__value) > hamon::numeric_limits<_CharT>::max())
			{
				hamon::detail::throw_format_error("Integral value outside the range of the char type");
			}
		}
	}

	const auto __c = static_cast<_CharT>(__value);
	return __formatter::__write(hamon::addressof(__c), hamon::addressof(__c) + 1, hamon::move(__out_it), __specs);
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___FORMAT_CHAR_HPP
