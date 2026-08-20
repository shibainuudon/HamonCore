/**
 *	@file	common_type.hpp
 *
 *	@brief	common_type の特殊化
 */

#ifndef HAMON_CHRONO_DURATION_COMMON_TYPE_HPP
#define HAMON_CHRONO_DURATION_COMMON_TYPE_HPP

#include <hamon/chrono/duration/duration_fwd.hpp>
#include <hamon/ratio/ratio_gcd.hpp>
#include <hamon/type_traits/common_type.hpp>

namespace hamon
{

// 29.4.3 Specializations of common_type[time.traits.specializations]

template <typename Rep1, typename Period1, typename Rep2, typename Period2>
struct common_type<
	hamon::chrono::duration<Rep1, Period1>,
	hamon::chrono::duration<Rep2, Period2>>
{
	using type = hamon::chrono::duration<
		hamon::common_type_t<Rep1, Rep2>,
		hamon::ratio_gcd<Period1, Period2>>;
};

}	// namespace hamon

#endif // HAMON_CHRONO_DURATION_COMMON_TYPE_HPP
