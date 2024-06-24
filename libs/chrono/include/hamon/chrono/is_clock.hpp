/**
 *	@file	is_clock.hpp
 *
 *	@brief	is_clock の定義
 */

#ifndef HAMON_CHRONO_IS_CLOCK_HPP
#define HAMON_CHRONO_IS_CLOCK_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::is_clock;
using std::chrono::is_clock_v;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

namespace detail
{

template <typename T>
struct is_clock_impl
{
private:
	template <typename U,
		typename = typename U::rep,			// [time.traits.is.clock]/1.1
		typename = typename U::period,		// [time.traits.is.clock]/1.1
		typename = typename U::duration,	// [time.traits.is.clock]/1.1
		typename = typename U::time_point,	// [time.traits.is.clock]/1.1
		typename = decltype(U::is_steady),	// [time.traits.is.clock]/1.2
		typename = decltype(U::now())		// [time.traits.is.clock]/1.3
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

}

// 29.4.4 Class template is_clock[time.traits.is.clock]

template <typename T>
struct is_clock
	: public hamon::chrono::detail::is_clock_impl<T>::type
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
constexpr bool is_clock_v = is_clock<T>::value;

#endif

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_IS_CLOCK_HPP
