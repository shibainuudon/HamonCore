/**
 *	@file	civil.hpp
 *
 *	@brief	days_from_civil, civil_from_days の定義
 */

#ifndef HAMON_CHRONO_DETAIL_CIVIL_HPP
#define HAMON_CHRONO_DETAIL_CIVIL_HPP

#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {
namespace detail {

struct civil
{
	int year;
	unsigned month;
	unsigned day;
};

#if defined(HAMON_HAS_CXX14_CONSTEXPR)

// https://howardhinnant.github.io/date_algorithms.html#days_from_civil
inline HAMON_CXX14_CONSTEXPR int
days_from_civil(civil c) HAMON_NOEXCEPT
{
	static_assert(hamon::numeric_limits<unsigned>::digits >= 18,
		"This algorithm has not been ported to a 16 bit unsigned integer");
	static_assert(hamon::numeric_limits<int>::digits >= 20,
		"This algorithm has not been ported to a 16 bit signed integer");

	const int y      = c.year - (c.month <= 2);
	const unsigned m = c.month;
	const unsigned d = c.day;

	const int era = (y >= 0 ? y : y-399) / 400;
	const unsigned yoe = static_cast<unsigned>(y - era * 400);       // [0, 399]
	const unsigned doy = (153 * (m > 2 ? m-3 : m+9) + 2) / 5 + d-1;  // [0, 365]
	const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;      // [0, 146096]
	return era * 146097 + static_cast<int>(doe) - 719468;
}

// https://howardhinnant.github.io/date_algorithms.html#civil_from_days
inline HAMON_CXX14_CONSTEXPR civil
civil_from_days(int z) HAMON_NOEXCEPT
{
	static_assert(hamon::numeric_limits<unsigned>::digits >= 18,
		"This algorithm has not been ported to a 16 bit unsigned integer");
	static_assert(hamon::numeric_limits<int>::digits >= 20,
		"This algorithm has not been ported to a 16 bit signed integer");
	z += 719468;
	const int era = (z >= 0 ? z : z - 146096) / 146097;
	const unsigned doe = static_cast<unsigned>(z - era * 146097);          // [0, 146096]
	const unsigned yoe = (doe - doe/1460 + doe/36524 - doe/146096) / 365;  // [0, 399]
	const int y = static_cast<int>(yoe) + era * 400;
	const unsigned doy = doe - (365*yoe + yoe/4 - yoe/100);                // [0, 365]
	const unsigned mp = (5*doy + 2)/153;                                   // [0, 11]
	const unsigned d = doy - (153*mp+2)/5 + 1;                             // [1, 31]
	const unsigned m = mp < 10 ? mp+3 : mp-9;                              // [1, 12]
	return {y + (m <= 2), m, d};
}

#else

inline HAMON_CXX11_CONSTEXPR int
days_from_civil_impl_5(int era, unsigned doe) HAMON_NOEXCEPT
{
	return era * 146097 + static_cast<int>(doe) - 719468;
}

inline HAMON_CXX11_CONSTEXPR int
days_from_civil_impl_4(int era, unsigned yoe, unsigned doy) HAMON_NOEXCEPT
{
	return days_from_civil_impl_5(era, yoe * 365 + yoe / 4 - yoe / 100 + doy);
}

inline HAMON_CXX11_CONSTEXPR int
days_from_civil_impl_3(unsigned m, unsigned d, int era, unsigned yoe) HAMON_NOEXCEPT
{
	return days_from_civil_impl_4(era, yoe, (153 * (m > 2 ? m-3 : m+9) + 2) / 5 + d-1);
}

inline HAMON_CXX11_CONSTEXPR int
days_from_civil_impl_2(int y, unsigned m, unsigned d, int era) HAMON_NOEXCEPT
{
	return days_from_civil_impl_3(m, d, era, static_cast<unsigned>(y - era * 400));
}

inline HAMON_CXX11_CONSTEXPR int
days_from_civil_impl_1(int y, unsigned m, unsigned d) HAMON_NOEXCEPT
{
	return days_from_civil_impl_2(y, m, d, (y >= 0 ? y : y-399) / 400);
}

inline HAMON_CXX11_CONSTEXPR int
days_from_civil(civil c) HAMON_NOEXCEPT
{
	static_assert(hamon::numeric_limits<unsigned>::digits >= 18,
		"This algorithm has not been ported to a 16 bit unsigned integer");
	static_assert(hamon::numeric_limits<int>::digits >= 20,
		"This algorithm has not been ported to a 16 bit signed integer");

	return days_from_civil_impl_1(c.year - (c.month <= 2), c.month, c.day);
}

inline HAMON_CXX11_CONSTEXPR civil
civil_from_days_impl_8(int y, unsigned d, unsigned m) HAMON_NOEXCEPT
{
	return {y + (m <= 2), m, d};
}

inline HAMON_CXX11_CONSTEXPR civil
civil_from_days_impl_7(int y, unsigned doy, unsigned mp) HAMON_NOEXCEPT
{
	return civil_from_days_impl_8(
		y,
		doy - (153*mp+2)/5 + 1,
		mp < 10 ? mp+3 : mp-9);
}

inline HAMON_CXX11_CONSTEXPR civil
civil_from_days_impl_6(int y, unsigned doy) HAMON_NOEXCEPT
{
	return civil_from_days_impl_7(y, doy, (5*doy + 2)/153);
}

inline HAMON_CXX11_CONSTEXPR civil
civil_from_days_impl_5(unsigned doe, unsigned yoe, int y) HAMON_NOEXCEPT
{
	return civil_from_days_impl_6(y, doe - (365*yoe + yoe/4 - yoe/100));
}

inline HAMON_CXX11_CONSTEXPR civil
civil_from_days_impl_4(int era, unsigned doe, unsigned yoe) HAMON_NOEXCEPT
{
	return civil_from_days_impl_5(doe, yoe, static_cast<int>(yoe) + era * 400);
}

inline HAMON_CXX11_CONSTEXPR civil
civil_from_days_impl_3(int era, unsigned doe) HAMON_NOEXCEPT
{
	return civil_from_days_impl_4(era, doe, (doe - doe/1460 + doe/36524 - doe/146096) / 365);
}

inline HAMON_CXX11_CONSTEXPR civil
civil_from_days_impl_2(int z, int era) HAMON_NOEXCEPT
{
	return civil_from_days_impl_3(era, static_cast<unsigned>(z - era * 146097));
}

inline HAMON_CXX11_CONSTEXPR civil
civil_from_days_impl_1(int z) HAMON_NOEXCEPT
{
	return civil_from_days_impl_2(z, (z >= 0 ? z : z - 146096) / 146097);
}

inline HAMON_CXX11_CONSTEXPR civil
civil_from_days(int z) HAMON_NOEXCEPT
{
	static_assert(hamon::numeric_limits<unsigned>::digits >= 18,
		"This algorithm has not been ported to a 16 bit unsigned integer");
	static_assert(hamon::numeric_limits<int>::digits >= 20,
		"This algorithm has not been ported to a 16 bit signed integer");

	return civil_from_days_impl_1(z + 719468);
}

#endif

}	// namespace detail
}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_DETAIL_CIVIL_HPP
