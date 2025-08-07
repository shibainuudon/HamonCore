/**
 *	@file	format_to_n.hpp
 *
 *	@brief	format_to_n の定義
 */

#ifndef HAMON_FORMAT_FORMAT_TO_N_HPP
#define HAMON_FORMAT_FORMAT_TO_N_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::format_to_n;

}	// namespace hamon

#else

#include <hamon/format/format_to_n_result.hpp>
#include <hamon/format/format_string.hpp>
#include <hamon/format/format_context.hpp>
#include <hamon/format/make_format_args.hpp>
#include <hamon/format/make_wformat_args.hpp>
#include <hamon/format/wformat_string.hpp>
#include <hamon/format/wformat_context.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/utility/move.hpp>
#include <locale>

#include <hamon/format/other/__vformat_to_n.hpp>

namespace hamon
{

template <hamon::output_iterator<char const&> Out, typename... Args>
hamon::format_to_n_result<Out>
format_to_n(Out out, hamon::iter_difference_t<Out> n, hamon::format_string<Args...> fmt, Args&&... args)
{
	return hamon::__vformat_to_n<hamon::format_context>(
		hamon::move(out), n, fmt.get(), hamon::make_format_args(args...));
}

template <hamon::output_iterator<wchar_t const&> Out, typename... Args>
hamon::format_to_n_result<Out>
format_to_n(Out out, hamon::iter_difference_t<Out> n, hamon::wformat_string<Args...> fmt, Args&&... args)
{
	return hamon::__vformat_to_n<hamon::wformat_context>(
		hamon::move(out), n, fmt.get(), hamon::make_wformat_args(args...));
}

template <hamon::output_iterator<char const&> Out, typename... Args>
hamon::format_to_n_result<Out>
format_to_n(Out out, hamon::iter_difference_t<Out> n, std::locale const& loc, hamon::format_string<Args...> fmt, Args&&... args)
{
	return hamon::__vformat_to_n<hamon::format_context>(
		hamon::move(out), n, loc, fmt.get(), hamon::make_format_args(args...));
}

template <hamon::output_iterator<wchar_t const&> Out, typename... Args>
hamon::format_to_n_result<Out>
format_to_n(Out out, hamon::iter_difference_t<Out> n, std::locale const& loc, hamon::wformat_string<Args...> fmt, Args&&... args)
{
	return hamon::__vformat_to_n<hamon::wformat_context>(
		hamon::move(out), n, loc, fmt.get(), hamon::make_wformat_args(args...));
}

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_FORMAT_TO_N_HPP
