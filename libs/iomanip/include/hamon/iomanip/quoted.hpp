/**
 *	@file	quoted.hpp
 *
 *	@brief	quoted の定義
 */

#ifndef HAMON_IOMANIP_QUOTED_HPP
#define HAMON_IOMANIP_QUOTED_HPP

#include <hamon/iomanip/detail/quoted_impl.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <iomanip>
#include <string>
#if (HAMON_CXX_STANDARD >= 17) && HAMON_HAS_INCLUDE(<string_view>)
#include <string_view>
#endif

namespace hamon
{

#if defined(__cpp_lib_quoted_string_io) && (__cpp_lib_quoted_string_io >= 201304L)

using std::quoted;

#else

template <typename CharT>
auto quoted(CharT const* s, CharT delim = CharT('"'), CharT escape = CharT('\\'))
-> hamon::detail::quoted_output<CharT, void>
{
	return hamon::detail::quoted_output<CharT, void>
	{
		s, hamon::char_traits<CharT>::length(s), delim, escape
	};
}

template <typename CharT, typename Traits, typename Allocator>
auto quoted(std::basic_string<CharT, Traits, Allocator> const& s, CharT delim = CharT('"'), CharT escape = CharT('\\'))
-> hamon::detail::quoted_output<CharT, Traits>
{
	return hamon::detail::quoted_output<CharT, Traits>
	{
		s.data(), s.size(), delim, escape
	};
}

template <typename CharT, typename Traits, typename Allocator>
auto quoted(std::basic_string<CharT, Traits, Allocator>& s, CharT delim = CharT('"'), CharT escape = CharT('\\'))
-> hamon::detail::quoted_input<std::basic_string<CharT, Traits, Allocator>>
{
	using String = std::basic_string<CharT, Traits, Allocator>;
	return hamon::detail::quoted_input<String>{s, delim, escape};
}

#if defined(HAMON_HAS_STD_STRING_VIEW)
template <typename CharT, typename Traits>
auto quoted(std::basic_string_view<CharT, Traits> s, CharT delim = CharT('"'), CharT escape = CharT('\\'))
-> hamon::detail::quoted_output<CharT, Traits>
{
	return hamon::detail::quoted_output<CharT, Traits>
	{
		s.data(), s.size(), delim, escape
	};
}
#endif

#endif

#if !defined(HAMON_USE_STD_STRING)
template <typename CharT, typename Traits, typename Allocator>
auto quoted(hamon::basic_string<CharT, Traits, Allocator> const& s, CharT delim = CharT('"'), CharT escape = CharT('\\'))
-> hamon::detail::quoted_output<CharT, Traits>
{
	return hamon::detail::quoted_output<CharT, Traits>
	{
		s.data(), s.size(), delim, escape
	};
}

template <typename CharT, typename Traits, typename Allocator>
auto quoted(hamon::basic_string<CharT, Traits, Allocator>& s, CharT delim = CharT('"'), CharT escape = CharT('\\'))
-> hamon::detail::quoted_input<hamon::basic_string<CharT, Traits, Allocator>>
{
	using String = hamon::basic_string<CharT, Traits, Allocator>;
	return hamon::detail::quoted_input<String>{s, delim, escape};
}
#endif

#if !defined(HAMON_USE_STD_STRING_VIEW)
template <typename CharT, typename Traits>
auto quoted(hamon::basic_string_view<CharT, Traits> s, CharT delim = CharT('"'), CharT escape = CharT('\\'))
-> hamon::detail::quoted_output<CharT, Traits>
{
	return hamon::detail::quoted_output<CharT, Traits>
	{
		s.data(), s.size(), delim, escape
	};
}
#endif

}	// namespace hamon

#endif // HAMON_IOMANIP_QUOTED_HPP
