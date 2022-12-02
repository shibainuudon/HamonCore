/**
 *	@file	unit_test_functional_invoke_r.cpp
 *
 *	@brief	invoke_r のテスト
 */

#include <hamon/functional/invoke_r.hpp>
#include <hamon/functional/ref.hpp>
#include <hamon/functional/cref.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "constexpr_test.hpp"

namespace hamon_functional_test
{

namespace invoke_r_test
{

HAMON_CONSTEXPR int function1()
{
	return 0;
}

HAMON_CONSTEXPR short function2(float)
{
	return 1;
}

HAMON_CONSTEXPR char function3(int, float)
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

	short f2() const
	{
		return 10;
	}

	char f3() volatile
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

GTEST_TEST(FunctionalTest, InvokeRTest)
{
	static_assert(!noexcept(throw_func(0)), "");
	static_assert( noexcept(nothrow_func(0)), "");
	static_assert(!noexcept(hamon::invoke_r<int >(throw_func, 0)), "");
	static_assert(!noexcept(hamon::invoke_r<char>(throw_func, 0)), "");
	static_assert(!noexcept(hamon::invoke_r<void>(throw_func, 0)), "");
	static_assert(std::is_same<decltype(hamon::invoke_r<int >(throw_func, 0)), int>::value, "");
	static_assert(std::is_same<decltype(hamon::invoke_r<char>(throw_func, 0)), char>::value, "");
	static_assert(std::is_same<decltype(hamon::invoke_r<void>(throw_func, 0)), void>::value, "");
#if HAMON_CXX_STANDARD >= 17
	static_assert( noexcept(hamon::invoke_r<int  >(nothrow_func, 0)), "");
	static_assert( noexcept(hamon::invoke_r<short>(nothrow_func, 0)), "");
	static_assert( noexcept(hamon::invoke_r<void >(nothrow_func, 0)), "");
#endif
	static_assert(std::is_same<decltype(hamon::invoke_r<int  >(nothrow_func, 0)), int>::value, "");
	static_assert(std::is_same<decltype(hamon::invoke_r<short>(nothrow_func, 0)), short>::value, "");
	static_assert(std::is_same<decltype(hamon::invoke_r<void >(nothrow_func, 0)), void>::value, "");

	{
		Foo f{};
		static_assert(!noexcept(f.throw_member_func()), "");
		static_assert( noexcept(f.nothrow_member_func()), "");
		static_assert(!noexcept(hamon::invoke_r<int  >(&Foo::throw_member_func, &f)), "");
		static_assert(!noexcept(hamon::invoke_r<float>(&Foo::throw_member_func, &f)), "");
		static_assert(!noexcept(hamon::invoke_r<void >(&Foo::throw_member_func, &f)), "");
		static_assert(std::is_same<decltype(hamon::invoke_r<int  >(&Foo::throw_member_func, &f)), int>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<float>(&Foo::throw_member_func, &f)), float>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<void >(&Foo::throw_member_func, &f)), void>::value, "");
#if HAMON_CXX_STANDARD >= 17
		static_assert( noexcept(hamon::invoke_r<int >(&Foo::nothrow_member_func, &f)), "");
		static_assert( noexcept(hamon::invoke_r<long>(&Foo::nothrow_member_func, &f)), "");
		static_assert( noexcept(hamon::invoke_r<void>(&Foo::nothrow_member_func, &f)), "");
#endif
		static_assert(std::is_same<decltype(hamon::invoke_r<int  >(&Foo::nothrow_member_func, &f)), int>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<float>(&Foo::nothrow_member_func, &f)), float>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<void >(&Foo::nothrow_member_func, &f)), void>::value, "");
	}
	{
		Bar bar;
		static_assert( noexcept(hamon::invoke_r<int  >(&Bar::x, bar)), "");
		static_assert( noexcept(hamon::invoke_r<long >(&Bar::x, bar)), "");
		static_assert( noexcept(hamon::invoke_r<void >(&Bar::x, bar)), "");
		static_assert( noexcept(hamon::invoke_r<int  >(&Bar::x, &bar)), "");
		static_assert( noexcept(hamon::invoke_r<short>(&Bar::x, &bar)), "");
		static_assert( noexcept(hamon::invoke_r<void >(&Bar::x, &bar)), "");
		static_assert( noexcept(hamon::invoke_r<int  >(&Bar::x, hamon::ref(bar))), "");
		static_assert( noexcept(hamon::invoke_r<char >(&Bar::x, hamon::ref(bar))), "");
		static_assert( noexcept(hamon::invoke_r<void >(&Bar::x, hamon::ref(bar))), "");
		static_assert( noexcept(hamon::invoke_r<int  >(&Bar::x, hamon::cref(bar))), "");
		static_assert( noexcept(hamon::invoke_r<long >(&Bar::x, hamon::cref(bar))), "");
		static_assert( noexcept(hamon::invoke_r<void >(&Bar::x, hamon::cref(bar))), "");

		static_assert(std::is_same<decltype(hamon::invoke_r<int >(&Bar::x, bar)), int>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<long>(&Bar::x, bar)), long>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<void>(&Bar::x, bar)), void>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<int >(&Bar::x, &bar)), int>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<long>(&Bar::x, &bar)), long>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<void>(&Bar::x, &bar)), void>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<int >(&Bar::x, hamon::ref(bar))), int>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<long>(&Bar::x, hamon::ref(bar))), long>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<void>(&Bar::x, hamon::ref(bar))), void>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<int >(&Bar::x, hamon::cref(bar))), int>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<long>(&Bar::x, hamon::cref(bar))), long>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<void>(&Bar::x, hamon::cref(bar))), void>::value, "");
	}
	{
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(0, hamon::invoke_r<int  >(function1));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(0, hamon::invoke_r<long >(function1));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(1, hamon::invoke_r<int  >(function2, 0.0f));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(1, hamon::invoke_r<short>(function2, 0.0f));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(2, hamon::invoke_r<int  >(function3, 0, 0.0f));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(2, hamon::invoke_r<char >(function3, 0, 0.0f));

		static_assert(std::is_same<decltype(hamon::invoke_r<int  >(function1)), int>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<long >(function1)), long>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<void >(function1)), void>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<int  >(function2, 0.0f)), int>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<short>(function2, 0.0f)), short>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<void >(function2, 0.0f)), void>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<int  >(function3, 0, 0.0f)), int>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<char >(function3, 0, 0.0f)), char>::value, "");
		static_assert(std::is_same<decltype(hamon::invoke_r<void >(function3, 0, 0.0f)), void>::value, "");
	}
	{
		HAMON_CONSTEXPR Foo f{};
		HAMON_CONSTEXPR Base b{};
		HAMON_CONSTEXPR Derived d{};

		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(3, hamon::invoke_r<int>(f));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(4, hamon::invoke_r<int>(&Foo::member_func, f));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(4, hamon::invoke_r<int>(&Foo::member_func, &f));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(4, hamon::invoke_r<int>(&Foo::member_func, hamon::ref(f)));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(4, hamon::invoke_r<int>(&Foo::member_func, hamon::cref(f)));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(5, hamon::invoke_r<int>(&Base::nonvirtual_func, b, 0));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(5, hamon::invoke_r<int>(&Base::nonvirtual_func, &b, 0));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(5, hamon::invoke_r<int>(&Base::nonvirtual_func, hamon::ref(b), 0));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(5, hamon::invoke_r<int>(&Base::nonvirtual_func, hamon::cref(b), 0));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(5, hamon::invoke_r<int>(&Base::nonvirtual_func, d, 0));
		                      EXPECT_EQ(5, hamon::invoke_r<int>(&Base::nonvirtual_func, &d, 0));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(5, hamon::invoke_r<int>(&Base::nonvirtual_func, hamon::ref(d), 0));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(5, hamon::invoke_r<int>(&Base::nonvirtual_func, hamon::cref(d), 0));
		                      EXPECT_EQ(6, hamon::invoke_r<int>(&Base::virtual_func, b));
		                      EXPECT_EQ(6, hamon::invoke_r<int>(&Base::virtual_func, &b));
		                      EXPECT_EQ(6, hamon::invoke_r<int>(&Base::virtual_func, hamon::ref(b)));
		                      EXPECT_EQ(6, hamon::invoke_r<int>(&Base::virtual_func, hamon::cref(b)));
		                      EXPECT_EQ(8, hamon::invoke_r<int>(&Base::virtual_func, d));
		                      EXPECT_EQ(8, hamon::invoke_r<int>(&Base::virtual_func, &d));
		                      EXPECT_EQ(8, hamon::invoke_r<int>(&Base::virtual_func, hamon::ref(d)));
		                      EXPECT_EQ(8, hamon::invoke_r<int>(&Base::virtual_func, hamon::cref(d)));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(7, hamon::invoke_r<int>(&Derived::nonvirtual_func, d, 0, 0));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(7, hamon::invoke_r<int>(&Derived::nonvirtual_func, &d, 0, 0));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(7, hamon::invoke_r<int>(&Derived::nonvirtual_func, hamon::ref(d), 0, 0));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(7, hamon::invoke_r<int>(&Derived::nonvirtual_func, hamon::cref(d), 0, 0));
		                      EXPECT_EQ(8, hamon::invoke_r<int>(&Derived::virtual_func, d));
		                      EXPECT_EQ(8, hamon::invoke_r<int>(&Derived::virtual_func, &d));
		                      EXPECT_EQ(8, hamon::invoke_r<int>(&Derived::virtual_func, hamon::ref(d)));
		                      EXPECT_EQ(8, hamon::invoke_r<int>(&Derived::virtual_func, hamon::cref(d)));
	}
	{
		Bar bar;
		EXPECT_EQ( 9, hamon::invoke_r<int>(&Bar::f1, bar));
		EXPECT_EQ( 9, hamon::invoke_r<int>(&Bar::f1, &bar));
		EXPECT_EQ( 9, hamon::invoke_r<int>(&Bar::f1, hamon::ref(bar)));
//		EXPECT_EQ( 9, hamon::invoke_r<int>(&Bar::f1, hamon::cref(bar)));
		EXPECT_EQ(10, hamon::invoke_r<int>(&Bar::f2, bar));
		EXPECT_EQ(10, hamon::invoke_r<int>(&Bar::f2, &bar));
		EXPECT_EQ(10, hamon::invoke_r<int>(&Bar::f2, hamon::ref(bar)));
		EXPECT_EQ(10, hamon::invoke_r<int>(&Bar::f2, hamon::cref(bar)));
		EXPECT_EQ(11, hamon::invoke_r<int>(&Bar::f3, bar));
		EXPECT_EQ(11, hamon::invoke_r<int>(&Bar::f3, &bar));
		EXPECT_EQ(11, hamon::invoke_r<int>(&Bar::f3, hamon::ref(bar)));
//		EXPECT_EQ(11, hamon::invoke_r<int>(&Bar::f3, hamon::cref(bar)));
		EXPECT_EQ(12, hamon::invoke_r<int>(&Bar::f4, bar));
		EXPECT_EQ(12, hamon::invoke_r<int>(&Bar::f4, &bar));
		EXPECT_EQ(12, hamon::invoke_r<int>(&Bar::f4, hamon::ref(bar)));
		EXPECT_EQ(12, hamon::invoke_r<int>(&Bar::f4, hamon::cref(bar)));

		EXPECT_EQ(17, hamon::invoke_r<int>(&Bar::x, bar));
		EXPECT_EQ(17, hamon::invoke_r<int>(&Bar::x, &bar));
		EXPECT_EQ(17, hamon::invoke_r<int>(&Bar::x, hamon::ref(bar)));
		EXPECT_EQ(17, hamon::invoke_r<int>(&Bar::x, hamon::cref(bar)));
		EXPECT_EQ(18, hamon::invoke_r<int>(&Bar::y, bar));
		EXPECT_EQ(18, hamon::invoke_r<int>(&Bar::y, &bar));
		EXPECT_EQ(18, hamon::invoke_r<int>(&Bar::y, hamon::ref(bar)));
		EXPECT_EQ(18, hamon::invoke_r<int>(&Bar::y, hamon::cref(bar)));
		EXPECT_EQ(19, hamon::invoke_r<int>(&Bar::z, bar));
		EXPECT_EQ(19, hamon::invoke_r<int>(&Bar::z, &bar));
		EXPECT_EQ(19, hamon::invoke_r<int>(&Bar::z, hamon::ref(bar)));
		EXPECT_EQ(19, hamon::invoke_r<int>(&Bar::z, hamon::cref(bar)));
		EXPECT_EQ(20, hamon::invoke_r<int>(&Bar::w, bar));
		EXPECT_EQ(20, hamon::invoke_r<int>(&Bar::w, &bar));
		EXPECT_EQ(20, hamon::invoke_r<int>(&Bar::w, hamon::ref(bar)));
		EXPECT_EQ(20, hamon::invoke_r<int>(&Bar::w, hamon::cref(bar)));
	}
	{
		const Bar bar;
//		EXPECT_EQ( 9, hamon::invoke_r<int>(&Bar::f1, bar));
//		EXPECT_EQ( 9, hamon::invoke_r<int>(&Bar::f1, &bar));
//		EXPECT_EQ( 9, hamon::invoke_r<int>(&Bar::f1, hamon::ref(bar)));
//		EXPECT_EQ( 9, hamon::invoke_r<int>(&Bar::f1, hamon::cref(bar)));
		EXPECT_EQ(10, hamon::invoke_r<int>(&Bar::f2, bar));
		EXPECT_EQ(10, hamon::invoke_r<int>(&Bar::f2, &bar));
		EXPECT_EQ(10, hamon::invoke_r<int>(&Bar::f2, hamon::ref(bar)));
		EXPECT_EQ(10, hamon::invoke_r<int>(&Bar::f2, hamon::cref(bar)));
//		EXPECT_EQ(11, hamon::invoke_r<int>(&Bar::f3, bar));
//		EXPECT_EQ(11, hamon::invoke_r<int>(&Bar::f3, &bar));
//		EXPECT_EQ(11, hamon::invoke_r<int>(&Bar::f3, hamon::ref(bar)));
//		EXPECT_EQ(11, hamon::invoke_r<int>(&Bar::f3, hamon::cref(bar)));
		EXPECT_EQ(12, hamon::invoke_r<int>(&Bar::f4, bar));
		EXPECT_EQ(12, hamon::invoke_r<int>(&Bar::f4, &bar));
		EXPECT_EQ(12, hamon::invoke_r<int>(&Bar::f4, hamon::ref(bar)));
		EXPECT_EQ(12, hamon::invoke_r<int>(&Bar::f4, hamon::cref(bar)));

		EXPECT_EQ(17, hamon::invoke_r<int>(&Bar::x, bar));
		EXPECT_EQ(17, hamon::invoke_r<int>(&Bar::x, &bar));
		EXPECT_EQ(17, hamon::invoke_r<int>(&Bar::x, hamon::ref(bar)));
		EXPECT_EQ(17, hamon::invoke_r<int>(&Bar::x, hamon::cref(bar)));
		EXPECT_EQ(18, hamon::invoke_r<int>(&Bar::y, bar));
		EXPECT_EQ(18, hamon::invoke_r<int>(&Bar::y, &bar));
		EXPECT_EQ(18, hamon::invoke_r<int>(&Bar::y, hamon::ref(bar)));
		EXPECT_EQ(18, hamon::invoke_r<int>(&Bar::y, hamon::cref(bar)));
		EXPECT_EQ(19, hamon::invoke_r<int>(&Bar::z, bar));
		EXPECT_EQ(19, hamon::invoke_r<int>(&Bar::z, &bar));
		EXPECT_EQ(19, hamon::invoke_r<int>(&Bar::z, hamon::ref(bar)));
		EXPECT_EQ(19, hamon::invoke_r<int>(&Bar::z, hamon::cref(bar)));
		EXPECT_EQ(20, hamon::invoke_r<int>(&Bar::w, bar));
		EXPECT_EQ(20, hamon::invoke_r<int>(&Bar::w, &bar));
		EXPECT_EQ(20, hamon::invoke_r<int>(&Bar::w, hamon::ref(bar)));
		EXPECT_EQ(20, hamon::invoke_r<int>(&Bar::w, hamon::cref(bar)));
	}
#if 0
	{
		volatile Bar bar;
//		EXPECT_EQ( 9, hamon::invoke_r<int>(&Bar::f1, bar));
//		EXPECT_EQ( 9, hamon::invoke_r<int>(&Bar::f1, &bar));
//		EXPECT_EQ( 9, hamon::invoke_r<int>(&Bar::f1, hamon::ref(bar)));
//		EXPECT_EQ( 9, hamon::invoke_r<int>(&Bar::f1, hamon::cref(bar)));
//		EXPECT_EQ(10, hamon::invoke_r<int>(&Bar::f2, bar));
//		EXPECT_EQ(10, hamon::invoke_r<int>(&Bar::f2, &bar));
//		EXPECT_EQ(10, hamon::invoke_r<int>(&Bar::f2, hamon::ref(bar)));
//		EXPECT_EQ(10, hamon::invoke_r<int>(&Bar::f2, hamon::cref(bar)));
		EXPECT_EQ(11, hamon::invoke_r<int>(&Bar::f3, bar));
		EXPECT_EQ(11, hamon::invoke_r<int>(&Bar::f3, &bar));
		EXPECT_EQ(11, hamon::invoke_r<int>(&Bar::f3, hamon::ref(bar)));
//		EXPECT_EQ(11, hamon::invoke_r<int>(&Bar::f3, hamon::cref(bar)));
		EXPECT_EQ(12, hamon::invoke_r<int>(&Bar::f4, bar));
		EXPECT_EQ(12, hamon::invoke_r<int>(&Bar::f4, &bar));
		EXPECT_EQ(12, hamon::invoke_r<int>(&Bar::f4, hamon::ref(bar)));
		EXPECT_EQ(12, hamon::invoke_r<int>(&Bar::f4, hamon::cref(bar)));

		EXPECT_EQ(17, hamon::invoke_r<int>(&Bar::x, bar));
		EXPECT_EQ(17, hamon::invoke_r<int>(&Bar::x, &bar));
		EXPECT_EQ(17, hamon::invoke_r<int>(&Bar::x, hamon::ref(bar)));
		EXPECT_EQ(17, hamon::invoke_r<int>(&Bar::x, hamon::cref(bar)));
		EXPECT_EQ(18, hamon::invoke_r<int>(&Bar::y, bar));
		EXPECT_EQ(18, hamon::invoke_r<int>(&Bar::y, &bar));
		EXPECT_EQ(18, hamon::invoke_r<int>(&Bar::y, hamon::ref(bar)));
		EXPECT_EQ(18, hamon::invoke_r<int>(&Bar::y, hamon::cref(bar)));
		EXPECT_EQ(19, hamon::invoke_r<int>(&Bar::z, bar));
		EXPECT_EQ(19, hamon::invoke_r<int>(&Bar::z, &bar));
		EXPECT_EQ(19, hamon::invoke_r<int>(&Bar::z, hamon::ref(bar)));
		EXPECT_EQ(19, hamon::invoke_r<int>(&Bar::z, hamon::cref(bar)));
		EXPECT_EQ(20, hamon::invoke_r<int>(&Bar::w, bar));
		EXPECT_EQ(20, hamon::invoke_r<int>(&Bar::w, &bar));
		EXPECT_EQ(20, hamon::invoke_r<int>(&Bar::w, hamon::ref(bar)));
		EXPECT_EQ(20, hamon::invoke_r<int>(&Bar::w, hamon::cref(bar)));
	}
	{
		const volatile Bar bar;
//		EXPECT_EQ( 9, hamon::invoke_r<int>(&Bar::f1, bar));
//		EXPECT_EQ( 9, hamon::invoke_r<int>(&Bar::f1, &bar));
//		EXPECT_EQ( 9, hamon::invoke_r<int>(&Bar::f1, hamon::ref(bar)));
//		EXPECT_EQ( 9, hamon::invoke_r<int>(&Bar::f1, hamon::cref(bar)));
//		EXPECT_EQ(10, hamon::invoke_r<int>(&Bar::f2, bar));
//		EXPECT_EQ(10, hamon::invoke_r<int>(&Bar::f2, &bar));
//		EXPECT_EQ(10, hamon::invoke_r<int>(&Bar::f2, hamon::ref(bar)));
//		EXPECT_EQ(10, hamon::invoke_r<int>(&Bar::f2, hamon::cref(bar)));
//		EXPECT_EQ(11, hamon::invoke_r<int>(&Bar::f3, bar));
//		EXPECT_EQ(11, hamon::invoke_r<int>(&Bar::f3, &bar));
//		EXPECT_EQ(11, hamon::invoke_r<int>(&Bar::f3, hamon::ref(bar)));
//		EXPECT_EQ(11, hamon::invoke_r<int>(&Bar::f3, hamon::cref(bar)));
		EXPECT_EQ(12, hamon::invoke_r<int>(&Bar::f4, bar));
		EXPECT_EQ(12, hamon::invoke_r<int>(&Bar::f4, &bar));
		EXPECT_EQ(12, hamon::invoke_r<int>(&Bar::f4, hamon::ref(bar)));
		EXPECT_EQ(12, hamon::invoke_r<int>(&Bar::f4, hamon::cref(bar)));

		EXPECT_EQ(17, hamon::invoke_r<int>(&Bar::x, bar));
		EXPECT_EQ(17, hamon::invoke_r<int>(&Bar::x, &bar));
		EXPECT_EQ(17, hamon::invoke_r<int>(&Bar::x, hamon::ref(bar)));
		EXPECT_EQ(17, hamon::invoke_r<int>(&Bar::x, hamon::cref(bar)));
		EXPECT_EQ(18, hamon::invoke_r<int>(&Bar::y, bar));
		EXPECT_EQ(18, hamon::invoke_r<int>(&Bar::y, &bar));
		EXPECT_EQ(18, hamon::invoke_r<int>(&Bar::y, hamon::ref(bar)));
		EXPECT_EQ(18, hamon::invoke_r<int>(&Bar::y, hamon::cref(bar)));
		EXPECT_EQ(19, hamon::invoke_r<int>(&Bar::z, bar));
		EXPECT_EQ(19, hamon::invoke_r<int>(&Bar::z, &bar));
		EXPECT_EQ(19, hamon::invoke_r<int>(&Bar::z, hamon::ref(bar)));
		EXPECT_EQ(19, hamon::invoke_r<int>(&Bar::z, hamon::cref(bar)));
		EXPECT_EQ(20, hamon::invoke_r<int>(&Bar::w, bar));
		EXPECT_EQ(20, hamon::invoke_r<int>(&Bar::w, &bar));
		EXPECT_EQ(20, hamon::invoke_r<int>(&Bar::w, hamon::ref(bar)));
		EXPECT_EQ(20, hamon::invoke_r<int>(&Bar::w, hamon::cref(bar)));
	}
#endif
}

}	// namespace invoke_r_test

}	// namespace hamon_functional_test
