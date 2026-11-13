/**
 *	@file	is_specialization_of_duration.hpp
 *
 *	@brief	is_specialization_of_duration の定義
 */

#ifndef HAMON_CHRONO_DETAIL_IS_SPECIALIZATION_OF_DURATION_HPP
#define HAMON_CHRONO_DETAIL_IS_SPECIALIZATION_OF_DURATION_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_NO_STD)
#include <chrono>	// duration
#endif

namespace hamon {
namespace chrono {
namespace detail {

template <typename T>
struct is_specialization_of_duration
	: public hamon::false_type {};

#if !defined(HAMON_NO_STD)
template <typename Rep, typename Period>
struct is_specialization_of_duration<std::chrono::duration<Rep, Period>>
	: public hamon::true_type {};
#endif

}	// namespace detail
}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_DETAIL_IS_SPECIALIZATION_OF_DURATION_HPP
