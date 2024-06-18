/**
 *	@file	duration_cast.hpp
 *
 *	@brief	duration_cast の定義
 */

#ifndef HAMON_CHRONO_DURATION_DURATION_CAST_HPP
#define HAMON_CHRONO_DURATION_DURATION_CAST_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::duration_cast;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration/duration_fwd.hpp>
#include <hamon/chrono/detail/is_specialization_of_duration.hpp>
#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/ratio/ratio_divide.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_arithmetic.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

namespace detail {

template <typename ToDuration, typename CR, hamon::intmax_t N, hamon::intmax_t D>
struct duration_cast_impl
{
	// [time.duration.cast]/2.4
	template <typename Duration>
	static HAMON_CXX11_CONSTEXPR ToDuration invoke(Duration const& d)
	{
		return ToDuration(static_cast<typename ToDuration::rep>(static_cast<CR>(d.count()) * static_cast<CR>(N) / static_cast<CR>(D)));
	}
};

template <typename ToDuration, typename CR>
struct duration_cast_impl<ToDuration, CR, 1, 1>
{
	// [time.duration.cast]/2.1
	template <typename Duration>
	static HAMON_CXX11_CONSTEXPR ToDuration invoke(Duration const& d)
	{
		return ToDuration(static_cast<typename ToDuration::rep>(d.count()));
	}
};

template <typename ToDuration, typename CR, hamon::intmax_t N>
struct duration_cast_impl<ToDuration, CR, N, 1>
{
	// [time.duration.cast]/2.2
	template <typename Duration>
	static HAMON_CXX11_CONSTEXPR ToDuration invoke(Duration const& d)
	{
		return ToDuration(static_cast<typename ToDuration::rep>(static_cast<CR>(d.count()) * static_cast<CR>(N)));
	}
};

template <typename ToDuration, typename CR, hamon::intmax_t D>
struct duration_cast_impl<ToDuration, CR, 1, D>
{
	// [time.duration.cast]/2.3
	template <typename Duration>
	static HAMON_CXX11_CONSTEXPR ToDuration invoke(Duration const& d)
	{
		return ToDuration(static_cast<typename ToDuration::rep>(static_cast<CR>(d.count()) / static_cast<CR>(D)));
	}
};

}	// namespace detail

// 29.5.8 Conversions[time.duration.cast]

template <typename ToDuration, typename Rep, typename Period,
	typename = hamon::enable_if_t<
		// [time.duration.cast]/1
		hamon::chrono::detail::is_specialization_of_duration<ToDuration>::value>>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR ToDuration	// nodiscard as an extension
duration_cast(duration<Rep, Period> const& d) HAMON_NOEXCEPT_IF(	// noexcept as an extension
	hamon::is_arithmetic<Rep>::value &&
	hamon::is_arithmetic<typename ToDuration::rep>::value)
{
	// [time.duration.cast]/2
	using CF = hamon::ratio_divide<Period, typename ToDuration::period>;
	using CR = hamon::common_type_t<typename ToDuration::rep, Rep, hamon::intmax_t>;

	return hamon::chrono::detail::duration_cast_impl<ToDuration, CR, CF::num, CF::den>::invoke(d);
}

}	// namespace chrono
}	// namespace hamon

#include <hamon/chrono/duration/duration.hpp>

#endif

#endif // HAMON_CHRONO_DURATION_DURATION_CAST_HPP
