/**
 *	@file	unit_test_chrono_duration_ctor_rep.cpp
 *
 *	@brief	値からのコンストラクタのテスト
 *
 *	template<class Rep2>
 *	constexpr explicit duration(const Rep2& r);
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_ctor_rep_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Rep, typename Period>
HAMON_CXX14_CONSTEXPR bool test_integer()
{
	using Duration = hamon::chrono::duration<Rep, Period>;

	static_assert( hamon::is_constructible<Duration, Rep>::value, "");
	static_assert( hamon::is_constructible<Duration, int>::value, "");
	static_assert( hamon::is_constructible<Duration, short>::value, "");
	static_assert( hamon::is_constructible<Duration, char>::value, "");
	static_assert( hamon::is_constructible<Duration, long long>::value, "");
	static_assert(!hamon::is_constructible<Duration, float>::value, "");
	static_assert(!hamon::is_constructible<Duration, double>::value, "");

#if !defined(HAMON_USE_STD_CHRONO)
	static_assert( hamon::is_nothrow_constructible<Duration, Rep>::value, "");
#endif
	static_assert(!hamon::is_trivially_constructible<Duration, Rep>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Duration, Rep>::value, "");

	{
		Rep const r{42};
		Duration d{r};
		VERIFY(d.count() == 42);
	}
	{
		Duration d{13};
		VERIFY(d.count() == 13);
	}

	return true;
}

template <typename Rep, typename Period>
HAMON_CXX14_CONSTEXPR bool test_float()
{
	using Duration = hamon::chrono::duration<Rep, Period>;

	static_assert( hamon::is_constructible<Duration, Rep>::value, "");
	static_assert( hamon::is_constructible<Duration, int>::value, "");
	static_assert( hamon::is_constructible<Duration, short>::value, "");
	static_assert( hamon::is_constructible<Duration, char>::value, "");
	static_assert( hamon::is_constructible<Duration, long long>::value, "");
	static_assert( hamon::is_constructible<Duration, float>::value, "");
	static_assert( hamon::is_constructible<Duration, double>::value, "");

#if !defined(HAMON_USE_STD_CHRONO)
	static_assert( hamon::is_nothrow_constructible<Duration, Rep>::value, "");
#endif
	static_assert(!hamon::is_trivially_constructible<Duration, Rep>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Duration, Rep>::value, "");

	{
		Rep const r{42};
		Duration d{r};
		VERIFY(d.count() == 42);
	}
	{
		Duration d{13};
		VERIFY(d.count() == 13);
	}
	{
		Duration d{3.5};
		VERIFY(d.count() == 3.5);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(DurationTest, CtorRepTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_integer<int,   hamon::ratio<60>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_integer<short, hamon::milli>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_integer<long,  hamon::ratio<1, 30>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_float<float,  hamon::ratio<60>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_float<double, hamon::milli>()));
}

}	// namespace duration_ctor_rep_test

}	// namespace hamon_chrono_test
