/**
 *	@file	local_seconds.hpp
 *
 *	@brief	local_seconds の定義
 */

#ifndef HAMON_CHRONO_LOCAL_SECONDS_HPP
#define HAMON_CHRONO_LOCAL_SECONDS_HPP

#include <hamon/chrono/local_time.hpp>
#include <hamon/chrono/duration.hpp>

namespace hamon {
namespace chrono {

// [time.clock.local], local time
using local_seconds = local_time<seconds>;

}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_LOCAL_SECONDS_HPP
