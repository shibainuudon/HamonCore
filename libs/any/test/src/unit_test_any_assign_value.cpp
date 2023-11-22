/**
 *	@file	unit_test_any_assign_value.cpp
 *
 *	@brief	任意の型の代入演算子のテスト
 *
 *	template<class T>
 *	any& operator=(T&& rhs);
 */

#include <hamon/any.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/array.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>

namespace hamon_any_test
{

namespace assign_value_test
{

struct S1
{
	S1(S1 const&) = default;
	S1(S1 &&)     = default;
};

struct S2
{
	S2(S2 const&) = delete;
	S2(S2 &&)     = default;
};

struct S3
{
	S3(S3 const&) = default;
	S3(S3 &&)     = delete;
};

struct S4
{
	S4(S4 const&) = delete;
	S4(S4 &&)     = delete;
};

static_assert( hamon::is_assignable<hamon::any, int>::value, "");
static_assert( hamon::is_assignable<hamon::any, float>::value, "");
static_assert( hamon::is_assignable<hamon::any, void*>::value, "");
static_assert( hamon::is_assignable<hamon::any, hamon::string>::value, "");
static_assert( hamon::is_assignable<hamon::any, S1>::value, "");
static_assert(!hamon::is_assignable<hamon::any, S2>::value, "");
static_assert( hamon::is_assignable<hamon::any, S3>::value, "");
static_assert(!hamon::is_assignable<hamon::any, S4>::value, "");

template <typename T, hamon::size_t N>
void AssignArrayTest2(hamon::any& a)
{
	a = hamon::array<T, N>{};
	EXPECT_TRUE(a.has_value());
}

template <typename T>
void AssignArrayTest(hamon::any& a)
{
	AssignArrayTest2<T, 1>(a);
	AssignArrayTest2<T, 2>(a);
	AssignArrayTest2<T, 3>(a);
	AssignArrayTest2<T, 4>(a);
	AssignArrayTest2<T, 5>(a);
	AssignArrayTest2<T, 6>(a);
	AssignArrayTest2<T, 7>(a);
	AssignArrayTest2<T, 8>(a);
	AssignArrayTest2<T, 9>(a);
	AssignArrayTest2<T, 10>(a);
	AssignArrayTest2<T, 11>(a);
	AssignArrayTest2<T, 12>(a);
	AssignArrayTest2<T, 13>(a);
	AssignArrayTest2<T, 14>(a);
	AssignArrayTest2<T, 15>(a);
	AssignArrayTest2<T, 16>(a);
	AssignArrayTest2<T, 17>(a);
	AssignArrayTest2<T, 18>(a);
	AssignArrayTest2<T, 19>(a);
}

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnCopy
{
	ThrowOnCopy()
	{
	}

	ThrowOnCopy(ThrowOnCopy const&)
	{
		throw 42;
	}

	ThrowOnCopy(ThrowOnCopy&&)
	{
	}
};

struct ThrowOnMove
{
	ThrowOnMove()
	{
	}

	ThrowOnMove(ThrowOnMove const&)
	{
	}

	ThrowOnMove(ThrowOnMove&&)
	{
		throw 42;
	}
};
#endif

GTEST_TEST(AnyTest, AssignValueTest)
{
	{
		hamon::any a;
		EXPECT_FALSE(a.has_value());

		a = 42;
		EXPECT_TRUE(a.has_value());
		EXPECT_EQ(42, hamon::any_cast<int>(a));

		a = hamon::string("World");
		EXPECT_TRUE(a.has_value());
		EXPECT_EQ("World", hamon::any_cast<hamon::string>(a));

		AssignArrayTest<char>(a);
		AssignArrayTest<short>(a);
		AssignArrayTest<int>(a);
		AssignArrayTest<long>(a);
		AssignArrayTest<long long>(a);

		a = 13;
		EXPECT_TRUE(a.has_value());
		EXPECT_EQ(13, hamon::any_cast<int>(a));

#if !defined(HAMON_NO_EXCEPTIONS)
		// [any.assign]/10
		// No effects if an exception is thrown.
		{
			ThrowOnCopy t;
			EXPECT_THROW(a = t, int);
			EXPECT_TRUE(a.has_value());
			EXPECT_EQ(13, hamon::any_cast<int>(a));
		}

		EXPECT_THROW(a = ThrowOnMove(), int);
		EXPECT_TRUE(a.has_value());
		EXPECT_EQ(13, hamon::any_cast<int>(a));
#endif
	}
}

}	// namespace assign_value_test

}	// namespace hamon_any_test
