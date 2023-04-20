/**
 *	@file	unit_test_tuple_apply.cpp
 *
 *	@brief	apply のテスト
 *
 *	template<class F, tuple-like Tuple>
 *	constexpr decltype(auto)
 *	apply(F&& f, Tuple&& t) noexcept(see below);
 */

#include <hamon/tuple.hpp>
#include <hamon/array.hpp>
#include <hamon/pair.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace apply_test
{

inline HAMON_CXX11_CONSTEXPR int
add(int x, int y)
{
	return x + y;
}

inline HAMON_CXX11_CONSTEXPR int
mul(int x, int y)
{
	return x * y;
}

struct add_t
{
	template <typename T>
	inline HAMON_CXX11_CONSTEXPR T
	operator()(T x, T y) const
	{
		return x + y;
	}
};

struct get_arity_t
{
	template <typename... Args>
	inline HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(Args...) const
	{
		return sizeof...(Args);
	}
};

inline HAMON_CXX11_CONSTEXPR int
throwable(int x)
{
	return x;
}

inline HAMON_CXX11_CONSTEXPR int
nothrow(int x) HAMON_NOEXCEPT
{
	return x;
}

GTEST_TEST(TupleTest, ApplyTest)
{
	using std::get;
#if 0	// TODO hamon::invokeのnoexcept指定が正しくない
	{
		hamon::tuple<int> t {1};
		static_assert(!noexcept(throwable(get<0>(t))), "");
		static_assert(!noexcept(hamon::apply(throwable, t)), "");
	}
	{
		hamon::tuple<int> t {1};
		static_assert(noexcept(nothrow(get<0>(t))), "");
		static_assert(noexcept(hamon::invoke(nothrow, get<0>(t))), "");
		static_assert(noexcept(hamon::apply(nothrow, t)), "");
	}
#endif
	{
		hamon::tuple<int, int> t { 1, 2 };
		EXPECT_TRUE(hamon::apply(add, t) == 3);
	}
	{
		hamon::tuple<int, int> t { 1, 2 };
		EXPECT_TRUE(hamon::apply(mul, t) == 2);
	}
	{
		hamon::pair<int, int> p { 3, 4 };
		EXPECT_TRUE(hamon::apply(add, p) == 7);
	}
	{
		hamon::pair<int, int> p { 3, 4 };
		EXPECT_TRUE(hamon::apply(mul, p) == 12);
	}
	{
		hamon::array<int, 2> a { 5, 6 };
		EXPECT_TRUE(hamon::apply(add, a) == 11);
	}
	{
		hamon::array<int, 2> a { 5, 6 };
		EXPECT_TRUE(hamon::apply(mul, a) == 30);
	}
	{
		hamon::array<std::string, 2> a { "hello ", "world" };
		EXPECT_TRUE(hamon::apply(add_t{}, a) == "hello world");
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<int, int> t { 1, 2 };
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::apply(add, t) == 3);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int> p { 3, 4 };
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::apply(add, p) == 7);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<int, 2> a { 5, 6 };
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::apply(add, a) == 11);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<> t{};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::apply(get_arity_t{}, t) == 0);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<int> t{42};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::apply(get_arity_t{}, t) == 1);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<int, float> t{1, 2};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::apply(get_arity_t{}, t) == 2);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<char, 3> a {};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::apply(get_arity_t{}, a) == 3);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<char, 10> a {};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::apply(get_arity_t{}, a) == 10);
	}
}

}	// namespace apply_test

}	// namespace hamon_tuple_test
