/**
 *	@file	vformat_to.hpp
 *
 *	@brief	vformat_to の定義
 */

#ifndef HAMON_FORMAT_VFORMAT_TO_HPP
#define HAMON_FORMAT_VFORMAT_TO_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::vformat_to;

}	// namespace hamon

#else

#include <hamon/format/format_args.hpp>
#include <hamon/format/wformat_args.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/string_view.hpp>
#include <hamon/utility/move.hpp>
#include <locale>

#include <hamon/format/other/__vformat_to.hpp>

namespace hamon
{

// 28.5.5 Formatting functions[format.functions]

template <hamon::output_iterator<const char&> Out>	// [format.functions]/13
Out vformat_to(Out out, hamon::string_view fmt, hamon::format_args args)
{
	return hamon::__vformat_to(hamon::move(out), fmt, args);
}

template <hamon::output_iterator<const wchar_t&> Out>	// [format.functions]/13
Out vformat_to(Out out, hamon::wstring_view fmt, hamon::wformat_args args)
{
	return hamon::__vformat_to(hamon::move(out), fmt, args);
}

template <hamon::output_iterator<const char&> Out>	// [format.functions]/13
Out vformat_to(Out out, std::locale const& loc, hamon::string_view fmt, hamon::format_args args)
{
	return hamon::__vformat_to(hamon::move(out), loc, fmt, args);
}

template <hamon::output_iterator<const wchar_t&> Out>	// [format.functions]/13
Out vformat_to(Out out, std::locale const& loc, hamon::wstring_view fmt, hamon::wformat_args args)
{
	return hamon::__vformat_to(hamon::move(out), loc, fmt, args);
}

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_VFORMAT_TO_HPP
