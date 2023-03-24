/**
 *	@file	unit_test_functional_invoke.cpp
 *
 *	@brief	invoke のテスト
 */

#include <hamon/functional/invoke.hpp>
#include <hamon/functional/ref.hpp>
#include <hamon/functional/cref.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_functional_test
{

namespace invoke_test
{

HAMON_CONSTEXPR int function1()
{
	return 0;
}

HAMON_CONSTEXPR int function2(float)
{
	return 1;
}

HAMON_CONSTEXPR int function3(int, float)
{
	return 2;
}

int throw_func(int);
int nothrow_func(int) HAMON_NOEXCEPT;

struct Foo
{
	HAMON_CONSTEXPR int operator()() const
	{
		return 3;
	}

	HAMON_CONSTEXPR int member_func() const
	{
		return 4;
	}

	int throw_member_func();
	int nothrow_member_func() HAMON_NOEXCEPT;
};

struct Base
{
	HAMON_CONSTEXPR int nonvirtual_func(int) const
	{
		return 5;
	}

	virtual int virtual_func() const
	{
		return 6;
	}
};

struct Derived : public Base
{
	HAMON_CONSTEXPR int nonvirtual_func(int, int) const
	{
		return 7;
	}

	virtual int virtual_func() const
	{
		return 8;
	}
};

struct Bar
{
	int f1()
	{
		return 9;
	}

	int f2() const
	{
		return 10;
	}

	int f3() volatile
	{
		return 11;
	}

	int f4() const volatile
	{
		return 12;
	}

	Bar()
		: x(17)
		, y(18)
		, z(19)
		, w(20)
	{}

	int x;
	const int y;
	volatile int z;
	const volatile int w;

private:
	Bar& operator=(const Bar&);
};

GTEST_TEST(FunctionalTest, InvokeTest)
{
	static_assert(!noexcept(throw_func(0)), "");
	static_assert( noexcept(nothrow_func(0)), "");
	static_assert(!noexcept(hamon::invoke(throw_func, 0)), "");
#if HAMON_CXX_STANDARD >= 17
	static_assert( noexcept(hamon::invoke(nothrow_func, 0)), "");
#endif

	{
		Foo f{};
		static_assert(!noexcept(f.throw_member_func()), "");
		static_assert( noexcept(f.nothrow_member_func()), "");
		static_assert(!noexcept(hamon::invoke(&Foo::throw_member_func, &f)), "");
#if HAMON_CXX_STANDARD >= 17
		static_assert( noexcept(hamon::invoke(&Foo::nothrow_member_func, &f)), "");
#endif
	}
	{
		Bar bar;
		static_assert( noexcept(hamon::invoke(&Bar::x, bar)), "");
		static_assert( noexcept(hamon::invoke(&Bar::x, &bar)), "");
		static_assert( noexcept(hamon::invoke(&Bar::x, hamon::ref(bar))), "");
		static_assert( noexcept(hamon::invoke(&Bar::x, hamon::cref(bar))), "");
	}
	{
		HAMON_CONSTEXPR Foo f{};
		HAMON_CONSTEXPR Base b{};
		HAMON_CONSTEXPR Derived d{};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::invoke(function1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::invoke(function2, 0.0f));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::invoke(function3, 0, 0.0f));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::invoke(f));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::invoke(&Foo::member_func, f));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::invoke(&Foo::member_func, &f));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::invoke(&Foo::member_func, hamon::ref(f)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::invoke(&Foo::member_func, hamon::cref(f)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::invoke(&Base::nonvirtual_func, b, 0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::invoke(&Base::nonvirtual_func, &b, 0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::invoke(&Base::nonvirtual_func, hamon::ref(b), 0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::invoke(&Base::nonvirtual_func, hamon::cref(b), 0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::invoke(&Base::nonvirtual_func, d, 0));
		                      EXPECT_EQ(5, hamon::invoke(&Base::nonvirtual_func, &d, 0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::invoke(&Base::nonvirtual_func, hamon::ref(d), 0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::invoke(&Base::nonvirtual_func, hamon::cref(d), 0));
		                      EXPECT_EQ(6, hamon::invoke(&Base::virtual_func, b));
		                      EXPECT_EQ(6, hamon::invoke(&Base::virtual_func, &b));
		                      EXPECT_EQ(6, hamon::invoke(&Base::virtual_func, hamon::ref(b)));
		                      EXPECT_EQ(6, hamon::invoke(&Base::virtual_func, hamon::cref(b)));
		                      EXPECT_EQ(8, hamon::invoke(&Base::virtual_func, d));
		                      EXPECT_EQ(8, hamon::invoke(&Base::virtual_func, &d));
		                      EXPECT_EQ(8, hamon::invoke(&Base::virtual_func, hamon::ref(d)));
		                      EXPECT_EQ(8, hamon::invoke(&Base::virtual_func, hamon::cref(d)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, hamon::invoke(&Derived::nonvirtual_func, d, 0, 0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, hamon::invoke(&Derived::nonvirtual_func, &d, 0, 0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, hamon::invoke(&Derived::nonvirtual_func, hamon::ref(d), 0, 0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, hamon::invoke(&Derived::nonvirtual_func, hamon::cref(d), 0, 0));
		                      EXPECT_EQ(8, hamon::invoke(&Derived::virtual_func, d));
		                      EXPECT_EQ(8, hamon::invoke(&Derived::virtual_func, &d));
		                      EXPECT_EQ(8, hamon::invoke(&Derived::virtual_func, hamon::ref(d)));
		                      EXPECT_EQ(8, hamon::invoke(&Derived::virtual_func, hamon::cref(d)));
	}
	{
		Bar bar;
		EXPECT_EQ( 9, hamon::invoke(&Bar::f1, bar));
		EXPECT_EQ( 9, hamon::invoke(&Bar::f1, &bar));
		EXPECT_EQ( 9, hamon::invoke(&Bar::f1, hamon::ref(bar)));
//		EXPECT_EQ( 9, hamon::invoke(&Bar::f1, hamon::cref(bar)));
		EXPECT_EQ(10, hamon::invoke(&Bar::f2, bar));
		EXPECT_EQ(10, hamon::invoke(&Bar::f2, &bar));
		EXPECT_EQ(10, hamon::invoke(&Bar::f2, hamon::ref(bar)));
		EXPECT_EQ(10, hamon::invoke(&Bar::f2, hamon::cref(bar)));
		EXPECT_EQ(11, hamon::invoke(&Bar::f3, bar));
		EXPECT_EQ(11, hamon::invoke(&Bar::f3, &bar));
		EXPECT_EQ(11, hamon::invoke(&Bar::f3, hamon::ref(bar)));
//		EXPECT_EQ(11, hamon::invoke(&Bar::f3, hamon::cref(bar)));
		EXPECT_EQ(12, hamon::invoke(&Bar::f4, bar));
		EXPECT_EQ(12, hamon::invoke(&Bar::f4, &bar));
		EXPECT_EQ(12, hamon::invoke(&Bar::f4, hamon::ref(bar)));
		EXPECT_EQ(12, hamon::invoke(&Bar::f4, hamon::cref(bar)));

		EXPECT_EQ(17, hamon::invoke(&Bar::x, bar));
		EXPECT_EQ(17, hamon::invoke(&Bar::x, &bar));
		EXPECT_EQ(17, hamon::invoke(&Bar::x, hamon::ref(bar)));
		EXPECT_EQ(17, hamon::invoke(&Bar::x, hamon::cref(bar)));
		EXPECT_EQ(18, hamon::invoke(&Bar::y, bar));
		EXPECT_EQ(18, hamon::invoke(&Bar::y, &bar));
		EXPECT_EQ(18, hamon::invoke(&Bar::y, hamon::ref(bar)));
		EXPECT_EQ(18, hamon::invoke(&Bar::y, hamon::cref(bar)));
		EXPECT_EQ(19, hamon::invoke(&Bar::z, bar));
		EXPECT_EQ(19, hamon::invoke(&Bar::z, &bar));
		EXPECT_EQ(19, hamon::invoke(&Bar::z, hamon::ref(bar)));
		EXPECT_EQ(19, hamon::invoke(&Bar::z, hamon::cref(bar)));
		EXPECT_EQ(20, hamon::invoke(&Bar::w, bar));
		EXPECT_EQ(20, hamon::invoke(&Bar::w, &bar));
		EXPECT_EQ(20, hamon::invoke(&Bar::w, hamon::ref(bar)));
		EXPECT_EQ(20, hamon::invoke(&Bar::w, hamon::cref(bar)));
	}
	{
		const Bar bar;
//		EXPECT_EQ( 9, hamon::invoke(&Bar::f1, bar));
//		EXPECT_EQ( 9, hamon::invoke(&Bar::f1, &bar));
//		EXPECT_EQ( 9, hamon::invoke(&Bar::f1, hamon::ref(bar)));
//		EXPECT_EQ( 9, hamon::invoke(&Bar::f1, hamon::cref(bar)));
		EXPECT_EQ(10, hamon::invoke(&Bar::f2, bar));
		EXPECT_EQ(10, hamon::invoke(&Bar::f2, &bar));
		EXPECT_EQ(10, hamon::invoke(&Bar::f2, hamon::ref(bar)));
		EXPECT_EQ(10, hamon::invoke(&Bar::f2, hamon::cref(bar)));
//		EXPECT_EQ(11, hamon::invoke(&Bar::f3, bar));
//		EXPECT_EQ(11, hamon::invoke(&Bar::f3, &bar));
//		EXPECT_EQ(11, hamon::invoke(&Bar::f3, hamon::ref(bar)));
//		EXPECT_EQ(11, hamon::invoke(&Bar::f3, hamon::cref(bar)));
		EXPECT_EQ(12, hamon::invoke(&Bar::f4, bar));
		EXPECT_EQ(12, hamon::invoke(&Bar::f4, &bar));
		EXPECT_EQ(12, hamon::invoke(&Bar::f4, hamon::ref(bar)));
		EXPECT_EQ(12, hamon::invoke(&Bar::f4, hamon::cref(bar)));

		EXPECT_EQ(17, hamon::invoke(&Bar::x, bar));
		EXPECT_EQ(17, hamon::invoke(&Bar::x, &bar));
		EXPECT_EQ(17, hamon::invoke(&Bar::x, hamon::ref(bar)));
		EXPECT_EQ(17, hamon::invoke(&Bar::x, hamon::cref(bar)));
		EXPECT_EQ(18, hamon::invoke(&Bar::y, bar));
		EXPECT_EQ(18, hamon::invoke(&Bar::y, &bar));
		EXPECT_EQ(18, hamon::invoke(&Bar::y, hamon::ref(bar)));
		EXPECT_EQ(18, hamon::invoke(&Bar::y, hamon::cref(bar)));
		EXPECT_EQ(19, hamon::invoke(&Bar::z, bar));
		EXPECT_EQ(19, hamon::invoke(&Bar::z, &bar));
		EXPECT_EQ(19, hamon::invoke(&Bar::z, hamon::ref(bar)));
		EXPECT_EQ(19, hamon::invoke(&Bar::z, hamon::cref(bar)));
		EXPECT_EQ(20, hamon::invoke(&Bar::w, bar));
		EXPECT_EQ(20, hamon::invoke(&Bar::w, &bar));
		EXPECT_EQ(20, hamon::invoke(&Bar::w, hamon::ref(bar)));
		EXPECT_EQ(20, hamon::invoke(&Bar::w, hamon::cref(bar)));
	}
#if 0
	{
		volatile Bar bar;
//		EXPECT_EQ( 9, hamon::invoke(&Bar::f1, bar));
//		EXPECT_EQ( 9, hamon::invoke(&Bar::f1, &bar));
//		EXPECT_EQ( 9, hamon::invoke(&Bar::f1, hamon::ref(bar)));
//		EXPECT_EQ( 9, hamon::invoke(&Bar::f1, hamon::cref(bar)));
//		EXPECT_EQ(10, hamon::invoke(&Bar::f2, bar));
//		EXPECT_EQ(10, hamon::invoke(&Bar::f2, &bar));
//		EXPECT_EQ(10, hamon::invoke(&Bar::f2, hamon::ref(bar)));
//		EXPECT_EQ(10, hamon::invoke(&Bar::f2, hamon::cref(bar)));
		EXPECT_EQ(11, hamon::invoke(&Bar::f3, bar));
		EXPECT_EQ(11, hamon::invoke(&Bar::f3, &bar));
		EXPECT_EQ(11, hamon::invoke(&Bar::f3, hamon::ref(bar)));
//		EXPECT_EQ(11, hamon::invoke(&Bar::f3, hamon::cref(bar)));
		EXPECT_EQ(12, hamon::invoke(&Bar::f4, bar));
		EXPECT_EQ(12, hamon::invoke(&Bar::f4, &bar));
		EXPECT_EQ(12, hamon::invoke(&Bar::f4, hamon::ref(bar)));
		EXPECT_EQ(12, hamon::invoke(&Bar::f4, hamon::cref(bar)));

		EXPECT_EQ(17, hamon::invoke(&Bar::x, bar));
		EXPECT_EQ(17, hamon::invoke(&Bar::x, &bar));
		EXPECT_EQ(17, hamon::invoke(&Bar::x, hamon::ref(bar)));
		EXPECT_EQ(17, hamon::invoke(&Bar::x, hamon::cref(bar)));
		EXPECT_EQ(18, hamon::invoke(&Bar::y, bar));
		EXPECT_EQ(18, hamon::invoke(&Bar::y, &bar));
		EXPECT_EQ(18, hamon::invoke(&Bar::y, hamon::ref(bar)));
		EXPECT_EQ(18, hamon::invoke(&Bar::y, hamon::cref(bar)));
		EXPECT_EQ(19, hamon::invoke(&Bar::z, bar));
		EXPECT_EQ(19, hamon::invoke(&Bar::z, &bar));
		EXPECT_EQ(19, hamon::invoke(&Bar::z, hamon::ref(bar)));
		EXPECT_EQ(19, hamon::invoke(&Bar::z, hamon::cref(bar)));
		EXPECT_EQ(20, hamon::invoke(&Bar::w, bar));
		EXPECT_EQ(20, hamon::invoke(&Bar::w, &bar));
		EXPECT_EQ(20, hamon::invoke(&Bar::w, hamon::ref(bar)));
		EXPECT_EQ(20, hamon::invoke(&Bar::w, hamon::cref(bar)));
	}
	{
		const volatile Bar bar;
//		EXPECT_EQ( 9, hamon::invoke(&Bar::f1, bar));
//		EXPECT_EQ( 9, hamon::invoke(&Bar::f1, &bar));
//		EXPECT_EQ( 9, hamon::invoke(&Bar::f1, hamon::ref(bar)));
//		EXPECT_EQ( 9, hamon::invoke(&Bar::f1, hamon::cref(bar)));
//		EXPECT_EQ(10, hamon::invoke(&Bar::f2, bar));
//		EXPECT_EQ(10, hamon::invoke(&Bar::f2, &bar));
//		EXPECT_EQ(10, hamon::invoke(&Bar::f2, hamon::ref(bar)));
//		EXPECT_EQ(10, hamon::invoke(&Bar::f2, hamon::cref(bar)));
//		EXPECT_EQ(11, hamon::invoke(&Bar::f3, bar));
//		EXPECT_EQ(11, hamon::invoke(&Bar::f3, &bar));
//		EXPECT_EQ(11, hamon::invoke(&Bar::f3, hamon::ref(bar)));
//		EXPECT_EQ(11, hamon::invoke(&Bar::f3, hamon::cref(bar)));
		EXPECT_EQ(12, hamon::invoke(&Bar::f4, bar));
		EXPECT_EQ(12, hamon::invoke(&Bar::f4, &bar));
		EXPECT_EQ(12, hamon::invoke(&Bar::f4, hamon::ref(bar)));
		EXPECT_EQ(12, hamon::invoke(&Bar::f4, hamon::cref(bar)));

		EXPECT_EQ(17, hamon::invoke(&Bar::x, bar));
		EXPECT_EQ(17, hamon::invoke(&Bar::x, &bar));
		EXPECT_EQ(17, hamon::invoke(&Bar::x, hamon::ref(bar)));
		EXPECT_EQ(17, hamon::invoke(&Bar::x, hamon::cref(bar)));
		EXPECT_EQ(18, hamon::invoke(&Bar::y, bar));
		EXPECT_EQ(18, hamon::invoke(&Bar::y, &bar));
		EXPECT_EQ(18, hamon::invoke(&Bar::y, hamon::ref(bar)));
		EXPECT_EQ(18, hamon::invoke(&Bar::y, hamon::cref(bar)));
		EXPECT_EQ(19, hamon::invoke(&Bar::z, bar));
		EXPECT_EQ(19, hamon::invoke(&Bar::z, &bar));
		EXPECT_EQ(19, hamon::invoke(&Bar::z, hamon::ref(bar)));
		EXPECT_EQ(19, hamon::invoke(&Bar::z, hamon::cref(bar)));
		EXPECT_EQ(20, hamon::invoke(&Bar::w, bar));
		EXPECT_EQ(20, hamon::invoke(&Bar::w, &bar));
		EXPECT_EQ(20, hamon::invoke(&Bar::w, hamon::ref(bar)));
		EXPECT_EQ(20, hamon::invoke(&Bar::w, hamon::cref(bar)));
	}
#endif
}

}	// namespace invoke_test

}	// namespace hamon_functional_test
