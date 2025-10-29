/**
 *	@file	make12.hpp
 *
 *	@brief	make12 の定義
 */

#ifndef HAMON_CHRONO_MAKE12_HPP
#define HAMON_CHRONO_MAKE12_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::make12;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

// 30.10 12/24 hours functions[time.12]

HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hours
make12(hours const& h) HAMON_NOEXCEPT
{
	// [time.12]/4
	return (h == 0_h) ? 12_h :
		(h <= 12_h) ? h : h - 12_h;
}

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_MAKE12_HPP
