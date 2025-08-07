/**
 *	@file	enable_nonlocking_formatter_optimization.hpp
 *
 *	@brief	enable_nonlocking_formatter_optimization の定義
 */

#ifndef HAMON_FORMAT_ENABLE_NONLOCKING_FORMATTER_OPTIMIZATION_HPP
#define HAMON_FORMAT_ENABLE_NONLOCKING_FORMATTER_OPTIMIZATION_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::enable_nonlocking_formatter_optimization;

}	// namespace hamon

#else

namespace hamon
{

// [format.formatter.locking], formatter locking
template <typename T>
constexpr bool enable_nonlocking_formatter_optimization = false;

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_ENABLE_NONLOCKING_FORMATTER_OPTIMIZATION_HPP
