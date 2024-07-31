/**
 *	@file	unit_test_functional_bind_back.cpp
 *
 *	@brief	bind_back のテスト
 */

#include <hamon/functional/bind_back.hpp>
#include <hamon/functional/ref.hpp>
#include <hamon/functional/cref.hpp>
#include <hamon/utility/as_const.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_functional_test
{

namespace bind_back_test
{

HAMON_CXX11_CONSTEXPR int f0()
{
	return 42;
}

HAMON_CXX11_CONSTEXPR int f1(int x)
{
	return x * 10;
}

HAMON_CXX11_CONSTEXPR int f2(int x, int y)
{
	return x * 100 + y * 10;
}

HAMON_CXX11_CONSTEXPR int f3(int x, int y, int z)
{
	return x * 1000 + y * 100 + z * 10;
}

HAMON_CXX11_CONSTEXPR int minus(int a, int  b)
{
	return a - b;
}

HAMON_CXX11_CONSTEXPR int minus_nothrow(int a, int  b) noexcept
{
	return a - b;
}

struct PMF
{
	int val;

	HAMON_CXX11_CONSTEXPR int minus(int arg) const
	{
		return val - arg;
	}

	HAMON_CXX11_CONSTEXPR int minus_nothrow(int arg) const noexcept
	{
		return val - arg;
	}
};

struct Minus
{
	HAMON_CXX11_CONSTEXPR int operator()(int a, int  b) const
	{
		return a - b;
	}

	HAMON_CXX11_CONSTEXPR float operator()(float a, float  b) const noexcept
	{
		return a - b;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool QualifiersTest()
{
	struct DetectQualifiers
	{
		HAMON_CXX14_CONSTEXPR int operator()() &
		{
			return 1;
		}

		HAMON_CXX11_CONSTEXPR int operator()() const&
		{
			return 2;
		}

		HAMON_CXX14_CONSTEXPR int operator()() &&
		{
			return 3;
		}

		HAMON_CXX11_CONSTEXPR int operator()() const&&
		{
			return 4;
		}
	};

	{
		auto b = hamon::bind_back(DetectQualifiers{});
		VERIFY(b() == 1);
		VERIFY(hamon::as_const(b)() == 2);
		VERIFY(hamon::move(b)() == 3);
		VERIFY(hamon::move(hamon::as_const(b))() == 4);
	}
#if defined(HAMON_HAS_CXX20_NONTYPE_TEMPLATE_PARAMETER_CLASS)
	{
		auto b = hamon::bind_back<DetectQualifiers{}>();
		VERIFY(b() == 1);
		VERIFY(hamon::as_const(b)() == 2);
		VERIFY(hamon::move(b)() == 3);
		VERIFY(hamon::move(hamon::as_const(b))() == 4);
	}
#endif

	return true;
}

HAMON_CXX17_CONSTEXPR bool StatefulLambdaTest()
{
    int value = 0;

    auto b0 = hamon::bind_back([&value] { ++value; });
    b0();
    VERIFY(value == 1);
    b0();
    VERIFY(value == 2);

    auto b1 = hamon::bind_back([&value](int x, int y) { value = value * x + y; }, 10);
    b1(3);
    VERIFY(value == 16);
    b1(4);
    VERIFY(value == 74);

	return true;
}

HAMON_CXX14_CONSTEXPR bool DecayTest()
{
	{
		struct F { void operator()() {} };

		static_assert(hamon::is_same<
			decltype(hamon::bind_back(hamon::declval<F>(), hamon::declval<int[]>())),
			decltype(hamon::bind_back(hamon::declval<F>(), hamon::declval<int*>()))
		>::value, "");
		static_assert(hamon::is_same<
			decltype(hamon::bind_back(hamon::declval<F>(), hamon::declval<decltype(f1)>())),
			decltype(hamon::bind_back(hamon::declval<F>(), hamon::declval<int(*)(int)>()))
		>::value, "");
		static_assert(hamon::is_same<
			decltype(hamon::bind_back(hamon::declval<F>(), hamon::declval<int>())),
			decltype(hamon::bind_back(hamon::declval<F&>(), hamon::declval<int&>()))
		>::value, "");
		static_assert(hamon::is_same<
			decltype(hamon::bind_back(hamon::declval<F>(), hamon::declval<int>())),
			decltype(hamon::bind_back(hamon::declval<const F&>(), hamon::declval<const int&>()))
		>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool ReferenceWrapperTest()
{
	struct F { void operator()() {} };

	static_assert(!hamon::is_same<
		decltype(hamon::bind_back(hamon::declval<F>(), hamon::declval<int&>())),
		decltype(hamon::bind_back(hamon::declval<F>(), hamon::ref(hamon::declval<int&>())))
	>::value, "");
	static_assert(!hamon::is_same<
		decltype(hamon::bind_back(hamon::declval<F>(), hamon::declval<const int&>())),
		decltype(hamon::bind_back(hamon::declval<F>(), hamon::cref(hamon::declval<int&>())))
	>::value, "");
	static_assert(!hamon::is_same<
		decltype(hamon::bind_back(hamon::declval<F>(), hamon::ref(hamon::declval<int&>()))),
		decltype(hamon::bind_back(hamon::declval<F>(), hamon::cref(hamon::declval<int&>())))
	>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool ForwardTest()
{
	struct S
	{
		HAMON_CXX11_CONSTEXPR int operator()(int&) const { return 1; }
		HAMON_CXX11_CONSTEXPR int operator()(int&&) const { return 2; }
		HAMON_CXX11_CONSTEXPR int operator()(int const&) const { return 3; }
		HAMON_CXX11_CONSTEXPR int operator()(int const&&) const { return 4; }
	};

	int i = 0;
	int const ci = 0;

	{
		auto b = hamon::bind_back(S{});
		VERIFY(b(i) == 1);
		VERIFY(b(hamon::move(i)) == 2);
		VERIFY(b(ci) == 3);
		VERIFY(b(hamon::move(ci)) == 4);

		VERIFY(b(hamon::ref(i)) == 1);
		VERIFY(b(hamon::cref(i)) == 3);
	}
#if defined(HAMON_HAS_CXX20_NONTYPE_TEMPLATE_PARAMETER_CLASS)
	{
		auto b = hamon::bind_back<S{}>();
		VERIFY(b(i) == 1);
		VERIFY(b(hamon::move(i)) == 2);
		VERIFY(b(ci) == 3);
		VERIFY(b(hamon::move(ci)) == 4);

		VERIFY(b(hamon::ref(i)) == 1);
		VERIFY(b(hamon::cref(i)) == 3);
	}
#endif

	return true;
}

HAMON_CXX14_CONSTEXPR bool ReturnTypeTest()
{
	struct S
	{
		int val;
		HAMON_CXX14_CONSTEXPR int& operator()() & { return val; }
		HAMON_CXX14_CONSTEXPR int&& operator()() && { return hamon::move(val); }
		HAMON_CXX11_CONSTEXPR int const& operator()() const& { return val; }
		HAMON_CXX11_CONSTEXPR int const&& operator()() const&& { return hamon::move(val); }
	};

	{
		auto b = hamon::bind_back(S{});
		static_assert(hamon::is_same<decltype(b()), int&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::move(b)()), int&&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::as_const(b)()), int const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::move(hamon::as_const(b))()), int const&&>::value, "");
	}
#if defined(HAMON_HAS_CXX20_NONTYPE_TEMPLATE_PARAMETER_CLASS)
	{
		auto b = hamon::bind_back<S{}>();
		static_assert(hamon::is_same<decltype(b()), int&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::move(b)()), int&&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::as_const(b)()), int const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::move(hamon::as_const(b))()), int const&&>::value, "");
	}
#endif

	return true;
}

struct NoThrow
{
	HAMON_CXX11_CONSTEXPR NoThrow() noexcept(true) {}
	HAMON_CXX11_CONSTEXPR NoThrow(NoThrow&&) noexcept(true) {}
	HAMON_CXX11_CONSTEXPR NoThrow(NoThrow const&) noexcept(true) {}
	NoThrow& operator=(NoThrow&&) noexcept(true) {return *this;}
	NoThrow& operator=(NoThrow const&) noexcept(true) {return *this;}

	template <typename... Args>
	void operator()(Args...) {}
};

struct ThrowOnCopy
{
	HAMON_CXX11_CONSTEXPR ThrowOnCopy() noexcept(true) {}
	HAMON_CXX11_CONSTEXPR ThrowOnCopy(ThrowOnCopy&&) noexcept(true) {}
	HAMON_CXX11_CONSTEXPR ThrowOnCopy(ThrowOnCopy const&) noexcept(false) {}
	ThrowOnCopy& operator=(ThrowOnCopy&&) noexcept(true) {return *this;}
	ThrowOnCopy& operator=(ThrowOnCopy const&) noexcept(true) {return *this;}

	template <typename... Args>
	void operator()(Args...) {}
};

struct ThrowOnMove
{
	HAMON_CXX11_CONSTEXPR ThrowOnMove() noexcept(true) {}
	HAMON_CXX11_CONSTEXPR ThrowOnMove(ThrowOnMove&&) noexcept(false) {}
	HAMON_CXX11_CONSTEXPR ThrowOnMove(ThrowOnMove const&) noexcept(true) {}
	ThrowOnMove& operator=(ThrowOnMove&&) noexcept(true) {return *this;}
	ThrowOnMove& operator=(ThrowOnMove const&) noexcept(true) {return *this;}

	template <typename... Args>
	void operator()(Args...) {}
};

#if !defined(HAMON_USE_STD_BIND_BACK)
static_assert( noexcept(hamon::bind_back(NoThrow{})), "");
static_assert( noexcept(hamon::bind_back(ThrowOnCopy{})), "");
static_assert(!noexcept(hamon::bind_back(ThrowOnMove{})), "");

static_assert( noexcept(hamon::bind_back(NoThrow{}, NoThrow{})), "");
static_assert( noexcept(hamon::bind_back(NoThrow{}, ThrowOnCopy{})), "");
static_assert(!noexcept(hamon::bind_back(NoThrow{}, ThrowOnMove{})), "");

static_assert( noexcept(hamon::bind_back(ThrowOnCopy{}, NoThrow{})), "");
static_assert( noexcept(hamon::bind_back(ThrowOnCopy{}, ThrowOnCopy{})), "");
static_assert(!noexcept(hamon::bind_back(ThrowOnCopy{}, ThrowOnMove{})), "");

static_assert(!noexcept(hamon::bind_back(ThrowOnMove{}, NoThrow{})), "");
static_assert(!noexcept(hamon::bind_back(ThrowOnMove{}, ThrowOnCopy{})), "");
static_assert(!noexcept(hamon::bind_back(ThrowOnMove{}, ThrowOnMove{})), "");

#if defined(HAMON_HAS_CXX20_NONTYPE_TEMPLATE_PARAMETER_CLASS)
static_assert( noexcept(hamon::bind_back<NoThrow{}>()), "");
static_assert(!noexcept(hamon::bind_back<ThrowOnCopy{}>()), "");
static_assert( noexcept(hamon::bind_back<ThrowOnMove{}>()), "");

static_assert( noexcept(hamon::bind_back<NoThrow{}>(NoThrow{})), "");
static_assert( noexcept(hamon::bind_back<NoThrow{}>(ThrowOnCopy{})), "");
static_assert(!noexcept(hamon::bind_back<NoThrow{}>(ThrowOnMove{})), "");

static_assert(!noexcept(hamon::bind_back<ThrowOnCopy{}>(NoThrow{})), "");
static_assert(!noexcept(hamon::bind_back<ThrowOnCopy{}>(ThrowOnCopy{})), "");
static_assert(!noexcept(hamon::bind_back<ThrowOnCopy{}>(ThrowOnMove{})), "");

static_assert( noexcept(hamon::bind_back<ThrowOnMove{}>(NoThrow{})), "");
static_assert( noexcept(hamon::bind_back<ThrowOnMove{}>(ThrowOnCopy{})), "");
static_assert(!noexcept(hamon::bind_back<ThrowOnMove{}>(ThrowOnMove{})), "");
#endif
#endif

#undef VERIFY

GTEST_TEST(FunctionalTest, BindBackTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(QualifiersTest());
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(StatefulLambdaTest());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DecayTest());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ReferenceWrapperTest());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ForwardTest());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ReturnTypeTest());

	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back(f0)(), 42);
	static_assert( hamon::is_invocable<decltype(hamon::bind_back(f0))>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f0)), int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f0)), int, int>::value, "");

	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back(f1)(2), 20);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back(f1, 3)(), 30);
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f1))>::value, "");
	static_assert( hamon::is_invocable<decltype(hamon::bind_back(f1)), int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f1)), void*>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f1)), int, int>::value, "");
	static_assert( hamon::is_invocable<decltype(hamon::bind_back(f1, hamon::declval<int>()))>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f1, hamon::declval<int>())), int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f1, hamon::declval<int>())), int, int>::value, "");

	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back(f2)(4, 5), 450);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back(f2, 6)(7), 760);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back(f2, 8, 9)(), 890);
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f2))>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f2)), int>::value, "");
	static_assert( hamon::is_invocable<decltype(hamon::bind_back(f2)), int, int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f2)), int, void*>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f2, hamon::declval<int>()))>::value, "");
	static_assert( hamon::is_invocable<decltype(hamon::bind_back(f2, hamon::declval<int>())), int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f2, hamon::declval<int>())), void*>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f2, hamon::declval<int>())), int, int>::value, "");
	static_assert( hamon::is_invocable<decltype(hamon::bind_back(f2, hamon::declval<int>(), hamon::declval<int>()))>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f2, hamon::declval<int>(), hamon::declval<int>())), int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f2, hamon::declval<int>(), hamon::declval<int>())), int, int>::value, "");

	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back(f3)(2, 3, 4), 2340);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back(f3, 3)(4, 5), 4530);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back(f3, 4, 5)(6), 6450);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back(f3, 5, 6, 7)(), 5670);
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f3))>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f3)), int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f3)), int, int>::value, "");
	static_assert( hamon::is_invocable<decltype(hamon::bind_back(f3)), int, int, int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f3, hamon::declval<int>()))>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f3, hamon::declval<int>())), int>::value, "");
	static_assert( hamon::is_invocable<decltype(hamon::bind_back(f3, hamon::declval<int>())), int, int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f3, hamon::declval<int>())), int, int, int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f3, hamon::declval<int>(), hamon::declval<int>()))>::value, "");
	static_assert( hamon::is_invocable<decltype(hamon::bind_back(f3, hamon::declval<int>(), hamon::declval<int>())), int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f3, hamon::declval<int>(), hamon::declval<int>())), int, int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f3, hamon::declval<int>(), hamon::declval<int>())), int, int, int>::value, "");
	static_assert( hamon::is_invocable<decltype(hamon::bind_back(f3, hamon::declval<int>(), hamon::declval<int>(), hamon::declval<int>()))>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f3, hamon::declval<int>(), hamon::declval<int>(), hamon::declval<int>())), int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f3, hamon::declval<int>(), hamon::declval<int>(), hamon::declval<int>())), int, int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back(f3, hamon::declval<int>(), hamon::declval<int>(), hamon::declval<int>())), int, int, int>::value, "");

#if defined(HAMON_HAS_CXX17_NONTYPE_TEMPLATE_PARAMETER_AUTO)
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back<f0>()(), 42);
	static_assert( hamon::is_invocable<decltype(hamon::bind_back<f0>())>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f0>()), int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f0>()), int, int>::value, "");

	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back<f1>()(2), 20);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back<f1>(3)(), 30);
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f1>())>::value, "");
	static_assert( hamon::is_invocable<decltype(hamon::bind_back<f1>()), int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f1>()), int, int>::value, "");
	static_assert( hamon::is_invocable<decltype(hamon::bind_back<f1>(hamon::declval<int>()))>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f1>(hamon::declval<int>())), int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f1>(hamon::declval<int>())), int, int>::value, "");

	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back<f2>()(4, 5), 450);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back<f2>(6)(7), 760);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back<f2>(8, 9)(), 890);
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f2>())>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f2>()), int>::value, "");
	static_assert( hamon::is_invocable<decltype(hamon::bind_back<f2>()), int, int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f2>(hamon::declval<int>()))>::value, "");
	static_assert( hamon::is_invocable<decltype(hamon::bind_back<f2>(hamon::declval<int>())), int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f2>(hamon::declval<int>())), int, int>::value, "");
	static_assert( hamon::is_invocable<decltype(hamon::bind_back<f2>(hamon::declval<int>(), hamon::declval<int>()))>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f2>(hamon::declval<int>(), hamon::declval<int>())), int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f2>(hamon::declval<int>(), hamon::declval<int>())), int, int>::value, "");

	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back<f3>()(2, 3, 4), 2340);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back<f3>(3)(4, 5), 4530);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back<f3>(4, 5)(6), 6450);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back<f3>(5, 6, 7)(), 5670);
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f3>())>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f3>()), int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f3>()), int, int>::value, "");
	static_assert( hamon::is_invocable<decltype(hamon::bind_back<f3>()), int, int, int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f3>(hamon::declval<int>()))>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f3>(hamon::declval<int>())), int>::value, "");
	static_assert( hamon::is_invocable<decltype(hamon::bind_back<f3>(hamon::declval<int>())), int, int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f3>(hamon::declval<int>())), int, int, int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f3>(hamon::declval<int>(), hamon::declval<int>()))>::value, "");
	static_assert( hamon::is_invocable<decltype(hamon::bind_back<f3>(hamon::declval<int>(), hamon::declval<int>())), int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f3>(hamon::declval<int>(), hamon::declval<int>())), int, int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f3>(hamon::declval<int>(), hamon::declval<int>())), int, int, int>::value, "");
	static_assert( hamon::is_invocable<decltype(hamon::bind_back<f3>(hamon::declval<int>(), hamon::declval<int>(), hamon::declval<int>()))>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f3>(hamon::declval<int>(), hamon::declval<int>(), hamon::declval<int>())), int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f3>(hamon::declval<int>(), hamon::declval<int>(), hamon::declval<int>())), int, int>::value, "");
	static_assert(!hamon::is_invocable<decltype(hamon::bind_back<f3>(hamon::declval<int>(), hamon::declval<int>(), hamon::declval<int>())), int, int, int>::value, "");
#endif

	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back(&f0)(), 42);

	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back(&f1)(2), 20);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back(&f1, 3)(), 30);

	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back(&f2)(4, 5), 450);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back(&f2, 6)(7), 760);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back(&f2, 8, 9)(), 890);

	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back(&f3)(2, 3, 4), 2340);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back(&f3, 3)(4, 5), 4530);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back(&f3, 4, 5)(6), 6450);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::bind_back(&f3, 5, 6, 7)(), 5670);

	{
		HAMON_CXX11_CONSTEXPR auto b = hamon::bind_back(minus);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b(10, 3), 7);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b(15, 20), -5);
		static_assert(!noexcept(b(hamon::declval<int>(), hamon::declval<int>())), "");
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = hamon::bind_back(minus, 50);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b(3), -47);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b(15), -35);
		static_assert(!noexcept(b(hamon::declval<int>())), "");
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = hamon::bind_back(minus, 50, 10);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b(), 40);
		static_assert(!noexcept(b()), "");
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = hamon::bind_back(minus_nothrow);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b(10, 3), 7);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b(15, 20), -5);
#if HAMON_CXX_STANDARD >= 17
		static_assert(noexcept(b(hamon::declval<int>(), hamon::declval<int>())), "");
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = hamon::bind_back(minus_nothrow, 50);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b(3), -47);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b(15), -35);
#if HAMON_CXX_STANDARD >= 17
		static_assert(noexcept(b(hamon::declval<int>())), "");
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = hamon::bind_back(minus_nothrow, 50, 10);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b(), 40);
#if HAMON_CXX_STANDARD >= 17
		static_assert(noexcept(b()), "");
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = hamon::bind_back(&PMF::minus, 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b(PMF{42}), 39);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b(PMF{10}), 7);
		static_assert(!noexcept(b(hamon::declval<PMF>())), "");
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = hamon::bind_back(&PMF::minus_nothrow, 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b(PMF{42}), 39);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b(PMF{10}), 7);
#if HAMON_CXX_STANDARD >= 17
		static_assert(noexcept(b(hamon::declval<PMF>())), "");
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = hamon::bind_back(Minus{}, 50);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b(1), -49);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b(2), -48);
		static_assert(!noexcept(b(hamon::declval<int>())), "");
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = hamon::bind_back(Minus{});
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b(50, 3), 47);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b(42, 15), 27);
		static_assert(!noexcept(b(hamon::declval<int>(), hamon::declval<int>())), "");
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = hamon::bind_back(Minus{});
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b(50.0f, 3.0f), 47.0f);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b(42.0f, 15.0f), 27.0f);
		static_assert(noexcept(b(hamon::declval<float>(), hamon::declval<float>())), "");
	}
	{
		HAMON_CXX17_CONSTEXPR auto plus = [](int a, int b) noexcept { return a + b; };
		HAMON_CXX17_CONSTEXPR auto b = hamon::bind_back(plus, 30);
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ(b(1), 31);
		static_assert(noexcept(b(hamon::declval<int>())), "");
	}
	{
		HAMON_CXX17_CONSTEXPR auto madd = [](int a, int b, int c) { return a * b + c; };
		HAMON_CXX17_CONSTEXPR auto b = hamon::bind_back(madd, 7);
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ(b(4, 10), 47);
		static_assert(!noexcept(b(hamon::declval<int>(), hamon::declval<int>())), "");
	}
	{
		struct S
		{
			int i = 42;
		};
		S s;
		auto lambda               = [](S x) { return x.i; };
		auto returns_lambda       = [=] { return lambda; };
		auto returns_const_lambda = [=]() -> const decltype(lambda) { return lambda; };
		auto returns_const_S      = []() -> const S { return {}; };

		using T = decltype(hamon::bind_back(lambda, s));
		static_assert(hamon::is_same<decltype(hamon::bind_back(lambda, hamon::move(s))), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(lambda, S{})), T>::value, "");

		static_assert(hamon::is_same<decltype(hamon::bind_back(hamon::move(lambda), s)), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(hamon::move(lambda), hamon::move(s))), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(hamon::move(lambda), S{})), T>::value, "");

		static_assert(hamon::is_same<decltype(hamon::bind_back(returns_lambda(), s)), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(returns_lambda(), hamon::move(s))), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(returns_lambda(), S{})), T>::value, "");

		static_assert(hamon::is_same<decltype(hamon::bind_back(lambda, hamon::as_const(s))), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(lambda, hamon::move(hamon::as_const(s)))), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(lambda, returns_const_S())), T>::value, "");

		static_assert(hamon::is_same<decltype(hamon::bind_back(hamon::move(lambda), hamon::as_const(s))), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(hamon::move(lambda), hamon::move(hamon::as_const(s)))), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(hamon::move(lambda), returns_const_S())), T>::value, "");

		static_assert(hamon::is_same<decltype(hamon::bind_back(returns_lambda(), hamon::as_const(s))), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(returns_lambda(), hamon::move(hamon::as_const(s)))), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(returns_lambda(), returns_const_S())), T>::value, "");

		static_assert(hamon::is_same<decltype(hamon::bind_back(hamon::as_const(lambda), s)), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(hamon::as_const(lambda), hamon::move(s))), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(hamon::as_const(lambda), S{})), T>::value, "");

		static_assert(hamon::is_same<decltype(hamon::bind_back(hamon::move(hamon::as_const(lambda)), s)), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(hamon::move(hamon::as_const(lambda)), hamon::move(s))), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(hamon::move(hamon::as_const(lambda)), S{})), T>::value, "");

		static_assert(hamon::is_same<decltype(hamon::bind_back(returns_const_lambda(), s)), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(returns_const_lambda(), hamon::move(s))), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(returns_const_lambda(), S{})), T>::value, "");

		static_assert(hamon::is_same<decltype(hamon::bind_back(hamon::as_const(lambda), hamon::as_const(s))), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(hamon::as_const(lambda), hamon::move(hamon::as_const(s)))), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(hamon::as_const(lambda), returns_const_S())), T>::value, "");

		static_assert(hamon::is_same<decltype(hamon::bind_back(hamon::move(hamon::as_const(lambda)), hamon::as_const(s))), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(hamon::move(hamon::as_const(lambda)), hamon::move(hamon::as_const(s)))), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(hamon::move(hamon::as_const(lambda)), returns_const_S())), T>::value, "");

		static_assert(hamon::is_same<decltype(hamon::bind_back(returns_const_lambda(), hamon::as_const(s))), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(returns_const_lambda(), hamon::move(hamon::as_const(s)))), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::bind_back(returns_const_lambda(), returns_const_S())), T>::value, "");
	}
}

}	// namespace bind_back_test

}	// namespace hamon_functional_test
