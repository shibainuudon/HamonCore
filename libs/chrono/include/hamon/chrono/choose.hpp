/**
 *	@file	choose.hpp
 *
 *	@brief	choose の定義
 */

#ifndef HAMON_CHRONO_CHOOSE_HPP
#define HAMON_CHRONO_CHOOSE_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::choose;

}	// namespace chrono
}	// namespace hamon

#else


namespace hamon {
namespace chrono {

// [time.zone.timezone], class time_zone
enum class choose
{
	earliest,
	latest
};

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_CHOOSE_HPP
