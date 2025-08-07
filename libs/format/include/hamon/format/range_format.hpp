/**
 *	@file	range_format.hpp
 *
 *	@brief	range_format の定義
 */

#ifndef HAMON_FORMAT_RANGE_FORMAT_HPP
#define HAMON_FORMAT_RANGE_FORMAT_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::range_format;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_GCC("-Wshadow")

// [format.range.fmtkind], variable template format_kind
enum class range_format
{
	disabled,
	map,
	set,
	sequence,
	string,
	debug_string
};

HAMON_WARNING_POP()

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_RANGE_FORMAT_HPP
