/**
 *	@file	is_am.hpp
 *
 *	@brief	is_am の定義
 */

#ifndef HAMON_CHRONO_IS_AM_HPP
#define HAMON_CHRONO_IS_AM_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::is_am;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

// 30.10 12/24 hours functions[time.12]

HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
is_am(hours const& h) HAMON_NOEXCEPT
{
	// [time.12]/2
	return 0_h <= h && h <= 11_h;
}

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_IS_AM_HPP
