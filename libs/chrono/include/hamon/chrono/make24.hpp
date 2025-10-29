/**
 *	@file	make24.hpp
 *
 *	@brief	make24 の定義
 */

#ifndef HAMON_CHRONO_MAKE24_HPP
#define HAMON_CHRONO_MAKE24_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::make24;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

// 30.10 12/24 hours functions[time.12]

HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hours
make24(hours const& h, bool is_pm) HAMON_NOEXCEPT
{
	// [time.12]/5
	return is_pm ?
		(h == 12_h ? h : h + 12_h) :
		(h == 12_h ? 0_h : h);
}

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_MAKE24_HPP
