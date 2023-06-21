/**
 *	@file	unit_test_optional_assign_value.cpp
 *
 *	@brief	Perfect-forwarded 代入演算子のテスト
 *
 *	template<class U = T> constexpr optional<T>& operator=(U&& v);
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace assign_value_test
{

struct AssignableInt
{
	explicit AssignableInt(int) = delete;
	AssignableInt& operator=(int);
};
static_assert(!hamon::is_constructible<AssignableInt, int>::value, "");
static_assert( hamon::is_assignable<AssignableInt&, int>::value, "");

struct ConstructibleInt
{
	explicit ConstructibleInt(int);
	ConstructibleInt& operator=(int) = delete;
};
static_assert( hamon::is_constructible<ConstructibleInt, int>::value, "");
static_assert(!hamon::is_assignable<ConstructibleInt&, int>::value, "");

struct AssignableConstructibleInt
{
	explicit AssignableConstructibleInt(int);
	AssignableConstructibleInt& operator=(int);
};
static_assert( hamon::is_constructible<AssignableConstructibleInt, int>::value, "");
static_assert( hamon::is_assignable<AssignableConstructibleInt&, int>::value, "");

static_assert(!hamon::is_assignable<hamon::optional<AssignableInt>&, int>::value, "");
static_assert(!hamon::is_assignable<hamon::optional<ConstructibleInt>&, int>::value, "");
static_assert( hamon::is_assignable<hamon::optional<AssignableConstructibleInt>&, int>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test1()
{
	// *this contains a value
	{
		hamon::optional<int> o {3};
		short const s = 4;
		VERIFY(o.has_value());
		auto& r = (o = s);
		VERIFY(o.has_value());
		VERIFY(o.value() == 4);
		VERIFY(*o == 4);
		static_assert(hamon::is_same<decltype(r), hamon::optional<int>&>::value, "");
		VERIFY(&r == &o);
	}
	{
		hamon::optional<long> o {4};
		short s = 5;
		VERIFY(o.has_value());
		auto& r = (o = hamon::move(s));
		VERIFY(o.has_value());
		VERIFY(o.value() == 5);
		VERIFY(*o == 5);
		static_assert(hamon::is_same<decltype(r), hamon::optional<long>&>::value, "");
		VERIFY(&r == &o);
	}

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test2()
{
	// *this dos not contain a value
	{
		hamon::optional<short> o;
		char const s = 4;
		VERIFY(!o.has_value());
		auto& r = (o = s);
		VERIFY(o.has_value());
		VERIFY(o.value() == 4);
		VERIFY(*o == 4);
		static_assert(hamon::is_same<decltype(r), hamon::optional<short>&>::value, "");
		VERIFY(&r == &o);
	}
	{
		hamon::optional<int> o;
		short s = 5;
		VERIFY(!o.has_value());
		auto& r = (o = hamon::move(s));
		VERIFY(o.has_value());
		VERIFY(o.value() == 5);
		VERIFY(*o == 5);
		static_assert(hamon::is_same<decltype(r), hamon::optional<int>&>::value, "");
		VERIFY(&r == &o);
	}

	return true;
}

#undef VERIFY

static int s_copy_assign_count = 0;
static int s_copy_ctor_count = 0;
static int s_move_assign_count = 0;
static int s_move_ctor_count = 0;

struct S
{
	S()
	{
	}

	S(int const&)
	{
		++s_copy_ctor_count;
	}

	S(int&&)
	{
		++s_move_ctor_count;
	}

	S& operator=(int const&)
	{
		++s_copy_assign_count;
		return *this;
	}

	S& operator=(int&&)
	{
		++s_move_assign_count;
		return *this;
	}
};

void InvokeCountTest()
{
	s_copy_assign_count = 0;
	s_copy_ctor_count = 0;
	s_move_assign_count = 0;
	s_move_ctor_count = 0;

	// *this contains a value
	{
		hamon::optional<S> o {hamon::in_place};
		int const i = 10;
		o = i;
		EXPECT_EQ(1, s_copy_assign_count);
		EXPECT_EQ(0, s_copy_ctor_count);
		EXPECT_EQ(0, s_move_assign_count);
		EXPECT_EQ(0, s_move_ctor_count);
	}

	s_copy_assign_count = 0;
	s_copy_ctor_count = 0;
	s_move_assign_count = 0;
	s_move_ctor_count = 0;

	{
		hamon::optional<S> o {hamon::in_place};
		int i = 10;
		o = hamon::move(i);
		EXPECT_EQ(0, s_copy_assign_count);
		EXPECT_EQ(0, s_copy_ctor_count);
		EXPECT_EQ(1, s_move_assign_count);
		EXPECT_EQ(0, s_move_ctor_count);
	}

	s_copy_assign_count = 0;
	s_copy_ctor_count = 0;
	s_move_assign_count = 0;
	s_move_ctor_count = 0;

	// *this dos not contain a value
	{
		hamon::optional<S> o;
		int const i = 10;
		o = i;
		EXPECT_EQ(0, s_copy_assign_count);
		EXPECT_EQ(1, s_copy_ctor_count);
		EXPECT_EQ(0, s_move_assign_count);
		EXPECT_EQ(0, s_move_ctor_count);
	}

	s_copy_assign_count = 0;
	s_copy_ctor_count = 0;
	s_move_assign_count = 0;
	s_move_ctor_count = 0;

	{
		hamon::optional<S> o;
		int i = 10;
		o = hamon::move(i);
		EXPECT_EQ(0, s_copy_assign_count);
		EXPECT_EQ(0, s_copy_ctor_count);
		EXPECT_EQ(0, s_move_assign_count);
		EXPECT_EQ(1, s_move_ctor_count);
	}
}

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnAssign1
{
	int value;

	ThrowOnAssign1()
		: value(-1)
	{}

	ThrowOnAssign1(int const& rhs)
		: value(rhs)
	{
		throw 42;
	}

	ThrowOnAssign1(int && rhs)
		: value(rhs)
	{
		throw 42;
	}

	ThrowOnAssign1& operator=(int const& rhs)
	{
		value = rhs;
		throw 42;
	}

	ThrowOnAssign1& operator=(int&& rhs)
	{
		value = rhs;
		throw 42;
	}
};

struct ThrowOnAssign2
{
	int value;

	ThrowOnAssign2()
		: value(-1)
	{}

	ThrowOnAssign2(int const& rhs)
		: value(rhs)
	{
		throw 42;
	}

	ThrowOnAssign2(int && rhs)
		: value(rhs)
	{
		throw 42;
	}

	ThrowOnAssign2& operator=(int const&)
	{
		throw 42;
	}

	ThrowOnAssign2& operator=(int&&)
	{
		throw 42;
	}
};

void ThrowOnAssignTest()
{
	// *this contains a value
	{
		hamon::optional<ThrowOnAssign1> o {hamon::in_place};
		int const i = 10;
		EXPECT_ANY_THROW(o = i);
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(10, o.value().value);
		EXPECT_EQ(10, o->value);
	}
	{
		hamon::optional<ThrowOnAssign2> o {hamon::in_place};
		int const i = 10;
		EXPECT_ANY_THROW(o = i);
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(-1, o.value().value);
		EXPECT_EQ(-1, o->value);
	}
	{
		hamon::optional<ThrowOnAssign1> o {hamon::in_place};
		int i = 10;
		EXPECT_ANY_THROW(o = hamon::move(i));
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(10, o.value().value);
		EXPECT_EQ(10, o->value);
	}
	{
		hamon::optional<ThrowOnAssign2> o {hamon::in_place};
		int i = 10;
		EXPECT_ANY_THROW(o = hamon::move(i));
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(-1, o.value().value);
		EXPECT_EQ(-1, o->value);
	}

	// *this dos not contain a value
	{
		hamon::optional<ThrowOnAssign1> o;
		int const i = 10;
		EXPECT_ANY_THROW(o = i);
		EXPECT_TRUE(!o.has_value());
	}
	{
		hamon::optional<ThrowOnAssign2> o;
		int const i = 10;
		EXPECT_ANY_THROW(o = i);
		EXPECT_TRUE(!o.has_value());
	}
	{
		hamon::optional<ThrowOnAssign1> o;
		int i = 10;
		EXPECT_ANY_THROW(o = hamon::move(i));
		EXPECT_TRUE(!o.has_value());
	}
	{
		hamon::optional<ThrowOnAssign2> o;
		int i = 10;
		EXPECT_ANY_THROW(o = hamon::move(i));
		EXPECT_TRUE(!o.has_value());
	}
}
#endif

GTEST_TEST(OptionalTest, AssignValueTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2()));
	InvokeCountTest();
#if !defined(HAMON_NO_EXCEPTIONS)
	ThrowOnAssignTest();
#endif
}

}	// namespace assign_value_test

}	// namespace hamon_optional_test
