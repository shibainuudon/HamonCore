/**
 *	@file	from_chars_result.hpp
 *
 *	@brief	from_chars_result の定義
 */

#ifndef HAMON_CHARCONV_FROM_CHARS_RESULT_HPP
#define HAMON_CHARCONV_FROM_CHARS_RESULT_HPP

#include <hamon/charconv/config.hpp>

#if defined(HAMON_USE_STD_CHARCONV)

#include <charconv>

namespace hamon
{

using std::from_chars_result;

}	// namespace hamon

#else

#include <hamon/system_error/errc.hpp>
#include <hamon/config.hpp>

namespace hamon
{

struct from_chars_result
{
	const char* ptr;
	hamon::errc ec;
#if defined(HAMON_HAS_CXX20_CONSISTENT_DEFAULTED_COMPARISONS)
	friend bool operator==(from_chars_result const&, from_chars_result const&) = default;
#else
	friend HAMON_CXX11_CONSTEXPR bool
	operator==(from_chars_result const& lhs, from_chars_result const& rhs)
	{
		return
			lhs.ptr == rhs.ptr &&
			lhs.ec  == rhs.ec;
	}
#endif
#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	friend HAMON_CXX11_CONSTEXPR bool
	operator!=(from_chars_result const& lhs, from_chars_result const& rhs)
	{
		return !(lhs == rhs);
	}
#endif
};

}	// namespace hamon

#endif

#endif // HAMON_CHARCONV_FROM_CHARS_RESULT_HPP
