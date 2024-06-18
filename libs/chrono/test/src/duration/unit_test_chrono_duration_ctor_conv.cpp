/**
 *	@file	unit_test_chrono_duration_ctor_conv.cpp
 *
 *	@brief	変換コンストラクタのテスト
 *
 *	template<class Rep2, class Period2>
 *	constexpr duration(const duration<Rep2, Period2>& d);
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <ratio>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_ctor_conv_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Rep>
HAMON_CXX14_CONSTEXPR bool test_integer()
{
	using hamon::chrono::duration;
	using Duration = duration<Rep, std::micro>;

	static_assert(!hamon::is_constructible<Duration, duration<int, std::nano>>::value, "");
	static_assert( hamon::is_constructible<Duration, duration<int, std::micro>>::value, "");
	static_assert( hamon::is_constructible<Duration, duration<int, std::milli>>::value, "");
	static_assert(!hamon::is_constructible<Duration, duration<float, std::nano>>::value, "");
	static_assert(!hamon::is_constructible<Duration, duration<float, std::micro>>::value, "");
	static_assert(!hamon::is_constructible<Duration, duration<float, std::milli>>::value, "");

	static_assert( hamon::is_nothrow_constructible<Duration, duration<int, std::milli>>::value, "");
	static_assert(!hamon::is_trivially_constructible<Duration, duration<int, std::milli>>::value, "");
	static_assert( hamon::is_implicitly_constructible<Duration, duration<int, std::milli>>::value, "");

	{
		duration<int, std::milli> ms(3);
		duration<Rep, std::micro> us(ms);
		VERIFY(ms.count() == 3);
		VERIFY(us.count() == 3000);

//		duration<int, std::milli> ms2(us);	// error
	}

	return true;
}

template <typename Rep>
HAMON_CXX14_CONSTEXPR bool test_float()
{
	using hamon::chrono::duration;
	using Duration = duration<Rep, std::micro>;

	static_assert( hamon::is_constructible<Duration, duration<int, std::nano>>::value, "");
	static_assert( hamon::is_constructible<Duration, duration<int, std::micro>>::value, "");
	static_assert( hamon::is_constructible<Duration, duration<int, std::milli>>::value, "");
	static_assert( hamon::is_constructible<Duration, duration<float, std::nano>>::value, "");
	static_assert( hamon::is_constructible<Duration, duration<float, std::micro>>::value, "");
	static_assert( hamon::is_constructible<Duration, duration<float, std::milli>>::value, "");

	static_assert( hamon::is_nothrow_constructible<Duration, duration<int, std::nano>>::value, "");
	static_assert( hamon::is_nothrow_constructible<Duration, duration<int, std::micro>>::value, "");
	static_assert( hamon::is_nothrow_constructible<Duration, duration<int, std::milli>>::value, "");
	static_assert( hamon::is_nothrow_constructible<Duration, duration<float, std::nano>>::value, "");
//	static_assert( hamon::is_nothrow_constructible<Duration, duration<float, std::micro>>::value, "");
	static_assert( hamon::is_nothrow_constructible<Duration, duration<float, std::milli>>::value, "");

	static_assert(!hamon::is_trivially_constructible<Duration, duration<int, std::nano>>::value, "");
	static_assert(!hamon::is_trivially_constructible<Duration, duration<int, std::micro>>::value, "");
	static_assert(!hamon::is_trivially_constructible<Duration, duration<int, std::milli>>::value, "");
	static_assert(!hamon::is_trivially_constructible<Duration, duration<float, std::nano>>::value, "");
//	static_assert(!hamon::is_trivially_constructible<Duration, duration<float, std::micro>>::value, "");
	static_assert(!hamon::is_trivially_constructible<Duration, duration<float, std::milli>>::value, "");

	static_assert( hamon::is_implicitly_constructible<Duration, duration<int, std::nano>>::value, "");
	static_assert( hamon::is_implicitly_constructible<Duration, duration<int, std::micro>>::value, "");
	static_assert( hamon::is_implicitly_constructible<Duration, duration<int, std::milli>>::value, "");
	static_assert( hamon::is_implicitly_constructible<Duration, duration<float, std::nano>>::value, "");
//	static_assert( hamon::is_implicitly_constructible<Duration, duration<float, std::micro>>::value, "");
	static_assert( hamon::is_implicitly_constructible<Duration, duration<float, std::milli>>::value, "");

	{
		duration<int, std::milli> ms(3);
		duration<Rep, std::micro> us(ms);
		VERIFY(ms.count() == 3);
		VERIFY(us.count() == 3000);
	}
	{
		duration<float, std::micro> ms(4000);
		duration<Rep, std::milli> us(ms);
		VERIFY(ms.count() == 4000);
		VERIFY(us.count() == 4);
	}
	{
		duration<int, std::ratio<1, 2>> d1(1);
		duration<Rep> d2(d1);
		VERIFY(d1.count() == 1);
		VERIFY(d2.count() == 0.5);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(DurationTest, CtorConvTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_integer<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_integer<short>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_integer<long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_float<float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_float<double>()));
}

}	// namespace duration_ctor_conv_test

}	// namespace hamon_chrono_test
