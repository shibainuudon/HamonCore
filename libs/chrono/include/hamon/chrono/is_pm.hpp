/**
 *	@file	is_pm.hpp
 *
 *	@brief	is_pm の定義
 */

#ifndef HAMON_CHRONO_IS_PM_HPP
#define HAMON_CHRONO_IS_PM_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::is_pm;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

// 30.10 12/24 hours functions[time.12]

HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
is_pm(hours const& h) HAMON_NOEXCEPT
{
	// [time.12]/3
	return 12_h <= h && h <= 23_h;
}

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_IS_PM_HPP
