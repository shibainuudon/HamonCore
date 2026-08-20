/**
 *	@file	common_type.hpp
 *
 *	@brief	common_type の特殊化
 */

#ifndef HAMON_CHRONO_TIME_POINT_COMMON_TYPE_HPP
#define HAMON_CHRONO_TIME_POINT_COMMON_TYPE_HPP

#include <hamon/chrono/time_point/time_point_fwd.hpp>
#include <hamon/type_traits/common_type.hpp>

namespace hamon
{

// 29.4.3 Specializations of common_type[time.traits.specializations]

template <typename Clock, typename Duration1, typename Duration2>
struct common_type<
	hamon::chrono::time_point<Clock, Duration1>,
	hamon::chrono::time_point<Clock, Duration2>>
{
	using type = hamon::chrono::time_point<
		Clock, hamon::common_type_t<Duration1, Duration2>>;
};

}	// namespace hamon

#endif // HAMON_CHRONO_TIME_POINT_COMMON_TYPE_HPP
