/**
 *	@file	vformat.hpp
 *
 *	@brief	vformat の定義
 */

#ifndef HAMON_FORMAT_VFORMAT_HPP
#define HAMON_FORMAT_VFORMAT_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::vformat;

}	// namespace hamon

#else

#include <hamon/format/format_args.hpp>
#include <hamon/format/wformat_args.hpp>
#include <hamon/format/vformat_to.hpp>
#include <hamon/iterator/back_inserter.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <locale>

//#include <hamon/format/__format/__try_constant_folding.hpp>
#include <hamon/format/__format/__allocating_buffer.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

// 28.5.5 Formatting functions[format.functions]

inline hamon::string
vformat(hamon::string_view fmt, hamon::format_args args)
{
	//auto __result = __format::__try_constant_folding(fmt, args);
	//if (__result.has_value())
	//{
	//	return *hamon::move(__result);
	//}
	__format::__allocating_buffer<char> __buffer;
	hamon::vformat_to(__buffer.__make_output_iterator(), fmt, args);
	return hamon::string{__buffer.__view()};
}

inline hamon::wstring
vformat(hamon::wstring_view fmt, hamon::wformat_args args)
{
	//auto __result = __format::__try_constant_folding(fmt, args);
	//if (__result.has_value())
	//{
	//	return *hamon::move(__result);
	//}
	__format::__allocating_buffer<wchar_t> __buffer;
	hamon::vformat_to(__buffer.__make_output_iterator(), fmt, args);
	return hamon::wstring{__buffer.__view()};
}

inline hamon::string
vformat(std::locale const& loc, hamon::string_view fmt, hamon::format_args args)
{
	__format::__allocating_buffer<char> __buffer;
	hamon::vformat_to(__buffer.__make_output_iterator(), loc, fmt, args);
	return hamon::string{__buffer.__view()};
}

inline hamon::wstring
vformat(std::locale const& loc, hamon::wstring_view fmt, hamon::wformat_args args)
{
	__format::__allocating_buffer<wchar_t> __buffer;
	hamon::vformat_to(__buffer.__make_output_iterator(), loc, fmt, args);
	return hamon::wstring{__buffer.__view()};
}

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_VFORMAT_HPP
