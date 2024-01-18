/**
 *	@file	unit_test_optional_emplace.cpp
 *
 *	@brief	emplace関数のテスト
 *
 *	template<class... Args> constexpr T& emplace(Args&&... args);
 *	template<class U, class... Args> constexpr T& emplace(initializer_list<U> il, Args&&... args);
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/string.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace emplace_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test1()
{
	// *this contains a value
	{
		hamon::optional<int> o {3};
		VERIFY(o.has_value());
		auto& r = o.emplace(11);
		VERIFY(o.has_value());
		VERIFY(o.value() == 11);
		VERIFY(*o == 11);
		static_assert(hamon::is_same<decltype(r), int&>::value, "");
		VERIFY(r == 11);
	}

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test2()
{
	// *this dos not contain a value
	{
		hamon::optional<long> o;
		VERIFY(!o.has_value());
		auto& r = o.emplace(12);
		VERIFY(o.has_value());
		VERIFY(o.value() == 12);
		VERIFY(*o == 12);
		static_assert(hamon::is_same<decltype(r), long&>::value, "");
		VERIFY(r == 12);
	}

	return true;
}

#undef VERIFY

struct S1
{
	int value;
	S1() : value(0) {}
	S1(int&) : value(1) {}
	S1(int&&) : value(2) {}
	S1(int const&) : value(3) {}
	S1(int const&&) : value(4) {}
};

struct S2
{
	int value;
	S2() : value(0) {}
	S2(std::initializer_list<int>, int&) : value(1) {}
	S2(std::initializer_list<int>, int&&) : value(2) {}
	S2(std::initializer_list<int>, int const&) : value(3) {}
	S2(std::initializer_list<int>, int const&&) : value(4) {}
};

void PerfectForwardTest()
{
	// *this contains a value
	{
		hamon::optional<S1> o {hamon::in_place};
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(o->value, 0);
		int i = 0;
		o.emplace(i);
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(o->value, 1);
	}
	{
		hamon::optional<S1> o {hamon::in_place};
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(o->value, 0);
		int const i = 0;
		o.emplace(i);
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(o->value, 3);
	}
	{
		hamon::optional<S1> o {hamon::in_place};
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(o->value, 0);
		int i = 0;
		o.emplace(hamon::move(i));
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(o->value, 2);
	}
	{
		hamon::optional<S1> o {hamon::in_place};
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(o->value, 0);
		int const i = 0;
		o.emplace(hamon::move(i));
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(o->value, 4);
	}

	{
		hamon::optional<S2> o {hamon::in_place};
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(o->value, 0);
		int i = 0;
		o.emplace({0}, i);
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(o->value, 1);
	}
	{
		hamon::optional<S2> o {hamon::in_place};
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(o->value, 0);
		int const i = 0;
		o.emplace({0}, i);
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(o->value, 3);
	}
	{
		hamon::optional<S2> o {hamon::in_place};
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(o->value, 0);
		int i = 0;
		o.emplace({0}, hamon::move(i));
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(o->value, 2);
	}
	{
		hamon::optional<S2> o {hamon::in_place};
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(o->value, 0);
		int const i = 0;
		o.emplace({0}, hamon::move(i));
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(o->value, 4);
	}
}

#if !defined(HAMON_NO_EXCEPTIONS)
static bool s_dtor_invoked = false;

struct ThrowOnCtor
{
	ThrowOnCtor()
	{
	}

	~ThrowOnCtor()
	{
		s_dtor_invoked = true;
	}

	ThrowOnCtor(int)
	{
		throw 42;
	}
};

void ThrowOnCtorTest()
{
	s_dtor_invoked = false;

	// *this contains a value
	{
		hamon::optional<ThrowOnCtor> o {hamon::in_place};
		EXPECT_ANY_THROW(o.emplace(10));
		EXPECT_TRUE(!o.has_value());
		EXPECT_TRUE(s_dtor_invoked);
	}

	s_dtor_invoked = false;

	// *this dos not contain a value
	{
		hamon::optional<ThrowOnCtor> o;
		EXPECT_ANY_THROW(o.emplace(10));
		EXPECT_TRUE(!o.has_value());
		EXPECT_TRUE(!s_dtor_invoked);
	}
}
#endif

GTEST_TEST(OptionalTest, EmplaceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2()));

	// *this contains a value
	{
		hamon::optional<hamon::string> o {"hello"};
		EXPECT_TRUE(o.has_value());
		auto& r = o.emplace(3u, 'X');
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(o.value(), "XXX");
		EXPECT_EQ(*o, "XXX");
		static_assert(hamon::is_same<decltype(r), hamon::string&>::value, "");
		EXPECT_EQ(r, "XXX");
	}
	{
		std::allocator<char> alloc;
		hamon::optional<hamon::string> o {"hello"};
		EXPECT_TRUE(o.has_value());
		auto& r = o.emplace({'A', 'B', 'C'}, alloc);
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(o.value(), "ABC");
		EXPECT_EQ(*o, "ABC");
		static_assert(hamon::is_same<decltype(r), hamon::string&>::value, "");
		EXPECT_EQ(r, "ABC");
	}

	// *this dos not contain a value
	{
		hamon::optional<hamon::string> o;
		EXPECT_TRUE(!o.has_value());
		auto& r = o.emplace(4u, 'Y');
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(o.value(), "YYYY");
		EXPECT_EQ(*o, "YYYY");
		static_assert(hamon::is_same<decltype(r), hamon::string&>::value, "");
		EXPECT_EQ(r, "YYYY");
	}
	{
		std::allocator<char> alloc;
		hamon::optional<hamon::string> o;
		EXPECT_TRUE(!o.has_value());
		auto& r = o.emplace({'X', 'Y', 'Z'}, alloc);
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(o.value(), "XYZ");
		EXPECT_EQ(*o, "XYZ");
		static_assert(hamon::is_same<decltype(r), hamon::string&>::value, "");
		EXPECT_EQ(r, "XYZ");
	}

	PerfectForwardTest();
#if !defined(HAMON_NO_EXCEPTIONS)
	ThrowOnCtorTest();
#endif
}

}	// namespace emplace_test

}	// namespace hamon_optional_test
