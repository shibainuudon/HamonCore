/**
 *	@file	__write_escaped_code_unit.hpp
 *
 *	@brief	__write_escaped_code_unit の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___WRITE_ESCAPED_CODE_UNIT_HPP
#define HAMON_FORMAT___FORMATTER___WRITE_ESCAPED_CODE_UNIT_HPP

#include <hamon/algorithm/ranges/copy.hpp>
#include <hamon/iterator/back_insert_iterator.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/string.hpp>
#include <charconv>

namespace hamon
{

namespace __formatter
{

struct __nul_terminator {};

template <class _CharT>
bool operator==(const _CharT* __cstr, __nul_terminator)
{
	return *__cstr == _CharT('\0');
}

template <class _CharT>
void
__write_escaped_code_unit(hamon::basic_string<_CharT>& __str, char32_t __value, const _CharT* __prefix)
{
	hamon::back_insert_iterator __out_it {__str};
	hamon::ranges::copy(__prefix, __nul_terminator{}, __out_it);

	char __buffer[8];
	std::to_chars_result __r = std::to_chars(hamon::begin(__buffer), hamon::end(__buffer), __value, 16);
//	_LIBCPP_ASSERT_INTERNAL(__r.ec == errc(0), "Internal buffer too small");
	hamon::ranges::copy(hamon::begin(__buffer), __r.ptr, __out_it);

	__str += _CharT('}');
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___WRITE_ESCAPED_CODE_UNIT_HPP
