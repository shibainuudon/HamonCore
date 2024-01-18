﻿/**
 *	@file	unit_test_optional_assign_optional_copy.cpp
 *
 *	@brief	const optional<U>& からの代入演算子のテスト
 *
 *	template<class U> constexpr optional<T>& operator=(const optional<U>& rhs);
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace assign_optional_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test1()
{
	// *this contains a value, rhs contains a value
	{
		hamon::optional<int> o1 {42};
		hamon::optional<short> const o2 {(short)13};
		VERIFY(o1.has_value());
		VERIFY(o2.has_value());
		auto& r = (o1 = o2);
		VERIFY(o1.has_value());
		VERIFY(o2.has_value());
		VERIFY(o1.value() == 13);
		VERIFY(*o1 == 13);
		static_assert(hamon::is_same<decltype(r), hamon::optional<int>&>::value, "");
		VERIFY(&r == &o1);
	}

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test2()
{
	// *this contains a value, rhs does not contain a value
	{
		hamon::optional<long> o1 {42};
		hamon::optional<int> const o2;
		VERIFY(o1.has_value());
		VERIFY(!o2.has_value());
		auto& r = (o1 = o2);
		VERIFY(!o1.has_value());
		VERIFY(!o2.has_value());
		static_assert(hamon::is_same<decltype(r), hamon::optional<long>&>::value, "");
		VERIFY(&r == &o1);
	}

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test3()
{
	// *this dos not contain a value, rhs contains a value
	{
		hamon::optional<int> o1;
		hamon::optional<char> const o2 {(char)13};
		VERIFY(!o1.has_value());
		VERIFY(o2.has_value());
		auto& r = (o1 = o2);
		VERIFY(o1.has_value());
		VERIFY(o2.has_value());
		VERIFY(o1.value() == 13);
		VERIFY(*o1 == 13);
		static_assert(hamon::is_same<decltype(r), hamon::optional<int>&>::value, "");
		VERIFY(&r == &o1);
	}

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test4()
{
	// *this dos not contain a value, rhs does not contain a value
	{
		hamon::optional<short> o1;
		hamon::optional<char> const o2;
		VERIFY(!o1.has_value());
		VERIFY(!o2.has_value());
		auto& r = (o1 = o2);
		VERIFY(!o1.has_value());
		VERIFY(!o2.has_value());
		static_assert(hamon::is_same<decltype(r), hamon::optional<short>&>::value, "");
		VERIFY(&r == &o1);
	}

	return true;
}

#undef VERIFY

static int s_copy_assign_count = 0;
static int s_copy_ctor_count = 0;
static int s_dtor_count = 0;

struct S
{
	S()
	{
	}

	S(int const&)
	{
		++s_copy_ctor_count;
	}

	S& operator=(int const&)
	{
		++s_copy_assign_count;
		return *this;
	}

	~S()
	{
		++s_dtor_count;
	}
};

void InvokeCountTest()
{
	s_copy_assign_count = 0;
	s_copy_ctor_count = 0;
	s_dtor_count = 0;

	// *this contains a value, rhs contains a value
	{
		hamon::optional<S> o {hamon::in_place};
		hamon::optional<int> const i = 10;
		o = i;
		EXPECT_EQ(1, s_copy_assign_count);
		EXPECT_EQ(0, s_copy_ctor_count);
		EXPECT_EQ(0, s_dtor_count);
	}

	s_copy_assign_count = 0;
	s_copy_ctor_count = 0;
	s_dtor_count = 0;

	// *this contains a value, rhs does not contain a value
	{
		hamon::optional<S> o {hamon::in_place};
		hamon::optional<int> const i;
		o = i;
		EXPECT_EQ(0, s_copy_assign_count);
		EXPECT_EQ(0, s_copy_ctor_count);
		EXPECT_EQ(1, s_dtor_count);
	}

	s_copy_assign_count = 0;
	s_copy_ctor_count = 0;
	s_dtor_count = 0;

	// *this dos not contain a value, rhs contains a value
	{
		hamon::optional<S> o;
		hamon::optional<int> const i = 10;
		o = i;
		EXPECT_EQ(0, s_copy_assign_count);
		EXPECT_EQ(1, s_copy_ctor_count);
		EXPECT_EQ(0, s_dtor_count);
	}

	s_copy_assign_count = 0;
	s_copy_ctor_count = 0;
	s_dtor_count = 0;

	// *this dos not contain a value, rhs does not contain a value
	{
		hamon::optional<S> o;
		hamon::optional<int> const i;
		o = i;
		EXPECT_EQ(0, s_copy_assign_count);
		EXPECT_EQ(0, s_copy_ctor_count);
		EXPECT_EQ(0, s_dtor_count);
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

	ThrowOnAssign1& operator=(int const& rhs)
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

	ThrowOnAssign2& operator=(int const&)
	{
		throw 42;
	}
};

void ThrowOnAssignTest()
{
	// *this contains a value, rhs contains a value
	{
		hamon::optional<ThrowOnAssign1> o {hamon::in_place};
		hamon::optional<int> const i = 10;
		EXPECT_ANY_THROW(o = i);
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(10, o.value().value);
		EXPECT_EQ(10, o->value);
	}
	{
		hamon::optional<ThrowOnAssign2> o {hamon::in_place};
		hamon::optional<int> const i = 10;
		EXPECT_ANY_THROW(o = i);
		EXPECT_TRUE(o.has_value());
		EXPECT_EQ(-1, o.value().value);
		EXPECT_EQ(-1, o->value);
	}

	// *this contains a value, rhs does not contain a value
	{
		hamon::optional<ThrowOnAssign1> o {hamon::in_place};
		hamon::optional<int> const i;
		EXPECT_NO_THROW(o = i);
		EXPECT_TRUE(!o.has_value());
	}
	{
		hamon::optional<ThrowOnAssign2> o {hamon::in_place};
		hamon::optional<int> const i;
		EXPECT_NO_THROW(o = i);
		EXPECT_TRUE(!o.has_value());
	}

	// *this dos not contain a value, rhs contains a value
	{
		hamon::optional<ThrowOnAssign1> o;
		hamon::optional<int> const i = 10;
		EXPECT_ANY_THROW(o = i);
		EXPECT_TRUE(!o.has_value());
	}
	{
		hamon::optional<ThrowOnAssign2> o;
		hamon::optional<int> const i = 10;
		EXPECT_ANY_THROW(o = i);
		EXPECT_TRUE(!o.has_value());
	}

	// *this dos not contain a value, rhs does not contain a value
	{
		hamon::optional<ThrowOnAssign1> o;
		hamon::optional<int> const i;
		EXPECT_NO_THROW(o = i);
		EXPECT_TRUE(!o.has_value());
	}
	{
		hamon::optional<ThrowOnAssign2> o;
		hamon::optional<int> const i;
		EXPECT_NO_THROW(o = i);
		EXPECT_TRUE(!o.has_value());
	}
}
#endif

GTEST_TEST(OptionalTest, AssignOptionalCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test3()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test4()));
	InvokeCountTest();
#if !defined(HAMON_NO_EXCEPTIONS)
	ThrowOnAssignTest();
#endif
}

}	// namespace assign_optional_copy_test

}	// namespace hamon_optional_test
