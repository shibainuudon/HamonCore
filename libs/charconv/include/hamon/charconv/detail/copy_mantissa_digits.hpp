/**
 *	@file	copy_mantissa_digits.hpp
 *
 *	@brief	copy_mantissa_digits の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_COPY_MANTISSA_DIGITS_HPP
#define HAMON_CHARCONV_DETAIL_COPY_MANTISSA_DIGITS_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/string_view.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

inline HAMON_CXX14_CONSTEXPR char*
copy_mantissa_digits(char* dst_first, char* dst_last, hamon::string_view src_str, bool* has_zero_tail)
{
	const char* src_first = src_str.data();
	auto src_length = src_str.length();
	auto dst_length = static_cast<hamon::size_t>(dst_last - dst_first);
	if (src_length > dst_length)
	{
		src_length = dst_length;
		*has_zero_tail = false;
	}
	const char* src_last = src_first + src_length;
	while (src_first != src_last)
	{
		*dst_first++ = *src_first++;
	}
	return dst_first;
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_COPY_MANTISSA_DIGITS_HPP
