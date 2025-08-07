/**
 *	@file	wformat_string.hpp
 *
 *	@brief	wformat_string の定義
 */

#ifndef HAMON_FORMAT_WFORMAT_STRING_HPP
#define HAMON_FORMAT_WFORMAT_STRING_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::wformat_string;

}	// namespace hamon

#else

#include <hamon/format/basic_format_string.hpp>
#include <hamon/type_traits/type_identity.hpp>

namespace hamon
{

// [format.fmt.string], class template basic_format_string

template <typename... Args>
using wformat_string = hamon::basic_format_string<wchar_t, hamon::type_identity_t<Args>...>;

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_WFORMAT_STRING_HPP
