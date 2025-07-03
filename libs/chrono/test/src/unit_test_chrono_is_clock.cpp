/**
 *	@file	unit_test_chrono_is_clock.cpp
 *
 *	@brief	is_clock のテスト
 */

#include <hamon/chrono/is_clock.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/ratio.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_CLOCK_TEST(b, T)	\
	static_assert(hamon::chrono::is_clock_v<T>      == b, #T);	\
	static_assert(hamon::chrono::is_clock<T>::value == b, #T);	\
	static_assert(hamon::chrono::is_clock<T>{}()    == b, #T);	\
	static_assert(hamon::chrono::is_clock<T>{}      == b, #T)

#else

#define HAMON_IS_CLOCK_TEST(b, T)	\
	static_assert(hamon::chrono::is_clock<T>::value == b, #T);	\
	static_assert(hamon::chrono::is_clock<T>{}()    == b, #T);	\
	static_assert(hamon::chrono::is_clock<T>{}      == b, #T)

#endif

namespace hamon_chrono_test
{

struct Clock1
{
	using rep = int;
	using period = hamon::ratio<1>;
	using duration = hamon::chrono::duration<rep, period>;
	using time_point = hamon::chrono::time_point<Clock1, duration>;
	static constexpr bool is_steady = false;
	static constexpr int now() { return 0; }
};

struct Clock2
{
	using rep = void;
	using period = void;
	using duration = void;
	using time_point = void;
	static constexpr int is_steady = 0;
	static constexpr int now() { return 0; }
};

struct Clock3
{
//	using rep = void;
	using period = void;
	using duration = void;
	using time_point = void;
	static constexpr int is_steady = 0;
	static constexpr int now() { return 0; }
};

struct Clock4
{
	using rep = void;
//	using period = void;
	using duration = void;
	using time_point = void;
	static constexpr int is_steady = 0;
	static constexpr int now() { return 0; }
};

struct Clock5
{
	using rep = void;
	using period = void;
//	using duration = void;
	using time_point = void;
	static constexpr int is_steady = 0;
	static constexpr int now() { return 0; }
};

struct Clock6
{
	using rep = void;
	using period = void;
	using duration = void;
//	using time_point = void;
	static constexpr int is_steady = 0;
	static constexpr int now() { return 0; }
};

struct Clock7
{
	using rep = void;
	using period = void;
	using duration = void;
	using time_point = void;
//	static constexpr int is_steady = 0;
	static constexpr int now() { return 0; }
};

struct Clock8
{
	using rep = void;
	using period = void;
	using duration = void;
	using time_point = void;
	static constexpr int is_steady = 0;
//	static constexpr int now() { return 0; }
};

HAMON_IS_CLOCK_TEST(true,  Clock1);
HAMON_IS_CLOCK_TEST(true,  Clock2);
HAMON_IS_CLOCK_TEST(false, Clock3);
HAMON_IS_CLOCK_TEST(false, Clock4);
HAMON_IS_CLOCK_TEST(false, Clock5);
HAMON_IS_CLOCK_TEST(false, Clock6);
HAMON_IS_CLOCK_TEST(false, Clock7);
HAMON_IS_CLOCK_TEST(false, Clock8);

}	// namespace hamon_chrono_test

#undef HAMON_IS_CLOCK_TEST
