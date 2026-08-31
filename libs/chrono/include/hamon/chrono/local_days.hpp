/**
 *	@file	local_days.hpp
 *
 *	@brief	local_days の定義
 */

#ifndef HAMON_CHRONO_LOCAL_DAYS_HPP
#define HAMON_CHRONO_LOCAL_DAYS_HPP

#include <hamon/chrono/local_time.hpp>
#include <hamon/chrono/duration.hpp>

namespace hamon {
namespace chrono {

// [time.clock.local], local time
using local_days = local_time<days>;

}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_LOCAL_DAYS_HPP
