/**
 *	@file	duration_values.hpp
 *
 *	@brief	duration_values の定義
 */

#ifndef HAMON_CHRONO_DURATION_DURATION_VALUES_HPP
#define HAMON_CHRONO_DURATION_DURATION_VALUES_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::duration_values;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

// 29.4.2 duration_values[time.traits.duration.values]

template <typename Rep>
struct duration_values
{
public:
	HAMON_NODISCARD static HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	Rep zero() HAMON_NOEXCEPT
	{
		// [time.traits.duration.values]/2
		return Rep(0);
	}

	HAMON_NODISCARD static HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	Rep min() HAMON_NOEXCEPT
	{
		// [time.traits.duration.values]/4
		return hamon::numeric_limits<Rep>::lowest();
	}

	HAMON_NODISCARD static HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	Rep max() HAMON_NOEXCEPT
	{
		// [time.traits.duration.values]/6
		return hamon::numeric_limits<Rep>::max();
	}
};

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_DURATION_DURATION_VALUES_HPP
