/**
 *	@file	formatter_fwd.hpp
 *
 *	@brief	formatter の前方宣言
 */

#ifndef HAMON_FORMAT_FORMATTER_FWD_HPP
#define HAMON_FORMAT_FORMATTER_FWD_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::formatter;

}	// namespace hamon

#else


namespace hamon
{

// [format.formatter], formatter
template <typename T, typename charT = char>
struct formatter;

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_FORMATTER_FWD_HPP
