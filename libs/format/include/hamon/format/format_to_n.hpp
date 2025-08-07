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

using std::format_to_n_result;
using std::format_to_n;

}	// namespace hamon

#else

#include <hamon/format/format_string.hpp>
#include <hamon/format/wformat_string.hpp>
#include <hamon/iterator/iter_difference_t.hpp>

namespace hamon
{

// 28.5.5 Formatting functions[format.functions]

template <typename Out>
struct format_to_n_result
{
	Out out;
	hamon::iter_difference_t<Out> size;
};

template <typename Out, typename... Args>
format_to_n_result<Out>
format_to_n(
	Out out,
	hamon::iter_difference_t<Out> n,
	hamon::format_string<Args...> fmt,
	Args&&... args);

template <typename Out, typename... Args>
format_to_n_result<Out>
format_to_n(
	Out out,
	hamon::iter_difference_t<Out> n,
	hamon::wformat_string<Args...> fmt,
	Args&&... args);

template <typename Out, typename... Args>
format_to_n_result<Out>
format_to_n(
	Out out,
	hamon::iter_difference_t<Out> n,
	std::locale const loc,
	hamon::format_string<Args...> fmt,
	Args&&... args);

template <typename Out, typename... Args>
format_to_n_result<Out>
format_to_n(
	Out out,
	hamon::iter_difference_t<Out> n,
	std::locale const loc,
	hamon::wformat_string<Args...> fmt,
	Args&&... args);

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_FORMAT_TO_N_HPP
