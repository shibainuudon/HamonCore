﻿/**
 *	@file	typedefs.hpp
 *
 *	@brief	別名の定義
 */

#ifndef HAMON_CHRONO_DURATION_TYPEDEFS_HPP
#define HAMON_CHRONO_DURATION_TYPEDEFS_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using nanoseconds  = std::chrono::nanoseconds;
using microseconds = std::chrono::microseconds;
using milliseconds = std::chrono::milliseconds;
using seconds      = std::chrono::seconds;
using minutes      = std::chrono::minutes;
using hours        = std::chrono::hours;
using days         = std::chrono::days;
using weeks        = std::chrono::weeks;
using years        = std::chrono::years;
using months       = std::chrono::months;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration/duration.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/ratio.hpp>

namespace hamon {
namespace chrono {

// convenience typedefs
using nanoseconds  = duration<hamon::int64_t, hamon::nano>;
using microseconds = duration<hamon::int64_t, hamon::micro>;
using milliseconds = duration<hamon::int64_t, hamon::milli>;
using seconds      = duration<hamon::int64_t>;
using minutes      = duration<hamon::int32_t, hamon::ratio<  60>>;
using hours        = duration<hamon::int32_t, hamon::ratio<3600>>;
using days         = duration<hamon::int32_t, hamon::ratio_multiply<hamon::ratio<24>, hours::period>>;
using weeks        = duration<hamon::int32_t, hamon::ratio_multiply<hamon::ratio<7>, days::period>>;
using years        = duration<hamon::int32_t, hamon::ratio_multiply<hamon::ratio<146097, 400>, days::period>>;
using months       = duration<hamon::int32_t, hamon::ratio_divide<years::period, hamon::ratio<12>>>;

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_DURATION_TYPEDEFS_HPP
