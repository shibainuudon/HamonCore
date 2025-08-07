/**
 *	@file	runtime_format_string.hpp
 *
 *	@brief	runtime_format_string の定義
 */

#ifndef HAMON_FORMAT_DETAIL_RUNTIME_FORMAT_STRING_HPP
#define HAMON_FORMAT_DETAIL_RUNTIME_FORMAT_STRING_HPP

#include <hamon/string_view.hpp>

namespace hamon
{

namespace detail
{

// 28.5.1 Header <format> synopsis[format.syn]

// runtime-format-string
template <typename charT>
struct runtime_format_string
{
private:
public:	// TODO
	hamon::basic_string_view<charT> str;
public:
	runtime_format_string(hamon::basic_string_view<charT> s) noexcept : str(s) {}

	runtime_format_string(runtime_format_string const&) = delete;
	runtime_format_string& operator=(runtime_format_string const&) = delete;
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORMAT_DETAIL_RUNTIME_FORMAT_STRING_HPP
