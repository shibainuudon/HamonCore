/**
 *	@file	unit_test_variant_assign_t.cpp
 *
 *	@brief	variant& operator=(T&&) のテスト
 */

#include <hamon/variant.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/in_place_index.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"

namespace hamon_variant_test
{

namespace assign_t_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

static_assert( hamon::is_assignable<hamon::variant<int>, int>::value, "");
static_assert( hamon::is_assignable<hamon::variant<int, float>, int>::value, "");
static_assert( hamon::is_assignable<hamon::variant<float, int>, int>::value, "");
static_assert(!hamon::is_assignable<hamon::variant<int, int>, int>::value, "ambiguous");
static_assert(!hamon::is_assignable<hamon::variant<int, float, int>, int>::value, "ambiguous");
static_assert( hamon::is_assignable<hamon::variant<int, float, int>, float>::value, "");
static_assert( hamon::is_assignable<hamon::variant<std::string>, const char*>::value, "");
static_assert(!hamon::is_assignable<hamon::variant<std::string, std::string>, const char*>::value, "ambiguous");
static_assert(!hamon::is_assignable<hamon::variant<std::string, void*>, int>::value, "no matching operator=");
static_assert(!hamon::is_assignable<hamon::variant<int>, float>::value, "narrowing conversion");
static_assert( hamon::is_assignable<hamon::variant<std::unique_ptr<int>>, std::unique_ptr<int>>::value, "");
static_assert(!hamon::is_assignable<hamon::variant<std::unique_ptr<char>>, std::unique_ptr<int>>::value, "no matching operator=");
static_assert(!hamon::is_assignable<hamon::variant<bool>, std::unique_ptr<int>>::value, "no explicit bool in operator=");
static_assert(!hamon::is_assignable<hamon::variant<std::unique_ptr<char>, bool>, std::unique_ptr<int>>::value, "no explicit bool in operator=");

//struct X
//{
//	operator void*();
//};
//static_assert(!hamon::is_assignable<hamon::variant<std::unique_ptr<char>, bool>, X>::value, "no boolean conversion in operator=");

//#if defined(HAMON_HAS_CXX20_POINTER_TO_BOOL_CONVERTING)
//static_assert(!hamon::is_assignable<hamon::variant<std::unique_ptr<char>, bool>, void*>::value, "no boolean conversion in operator=");
//#else
//static_assert( hamon::is_assignable<hamon::variant<std::unique_ptr<char>, bool>, void*>::value, "");
//#endif

static_assert(!hamon::is_assignable<hamon::variant<std::unique_ptr<char>, hamon::false_type>, void*>::value, "no converted to bool in operator=");

struct X {};
struct Y { operator X(); };
static_assert( hamon::is_assignable<hamon::variant<X>, Y>::value, "regression on user-defined conversions in operator=");

struct S1_1
{
	S1_1(int);
	S1_1& operator=(int const&);
};

struct S1_2
{
	S1_2(int);
	S1_2& operator=(int const&) = delete;
};

struct S1_3
{
	S1_3(int)                   = delete;
	S1_3& operator=(int const&);
};

struct S1_4
{
	S1_4(int)                   = delete;
	S1_4& operator=(int const&) = delete;
};

static_assert( hamon::is_constructible<S1_1, int>::value, "");
static_assert( hamon::is_constructible<S1_2, int>::value, "");
static_assert(!hamon::is_constructible<S1_3, int>::value, "");
static_assert(!hamon::is_constructible<S1_4, int>::value, "");
static_assert( hamon::is_assignable<S1_1&, int>::value, "");
static_assert(!hamon::is_assignable<S1_2&, int>::value, "");
static_assert( hamon::is_assignable<S1_3&, int>::value, "");
static_assert(!hamon::is_assignable<S1_4&, int>::value, "");

// *thisが保持している型をTjとしたとき、
// is_constructible<Tj, T> &&
// is_assignable<Tj&, T>がtrueであるとき、
// is_assignable<variant<...>, T> がtrueになる
static_assert( hamon::is_assignable<hamon::variant<S1_1>&, int>::value, "");
static_assert( hamon::is_assignable<hamon::variant<S1_2>&, int>::value, "");	// これは一時オブジェクトが作成されてムーブ代入される
static_assert(!hamon::is_assignable<hamon::variant<S1_3>&, int>::value, "");
static_assert(!hamon::is_assignable<hamon::variant<S1_4>&, int>::value, "");

struct S2_1
{
	S2_1(int)                   noexcept(true);
	S2_1& operator=(int const&) noexcept(true);
};

struct S2_2
{
	S2_2(int)                   noexcept(false);
	S2_2& operator=(int const&) noexcept(true);
};

struct S2_3
{
	S2_3(int)                   noexcept(true);
	S2_3& operator=(int const&) noexcept(false);
};

struct S2_4
{
	S2_4(int)                   noexcept(false);
	S2_4& operator=(int const&) noexcept(false);
};

static_assert( hamon::is_nothrow_constructible<S2_1, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<S2_2, int>::value, "");
static_assert( hamon::is_nothrow_constructible<S2_3, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<S2_4, int>::value, "");
static_assert( hamon::is_nothrow_assignable<S2_1, int>::value, "");
static_assert( hamon::is_nothrow_assignable<S2_2, int>::value, "");
static_assert(!hamon::is_nothrow_assignable<S2_3, int>::value, "");
static_assert(!hamon::is_nothrow_assignable<S2_4, int>::value, "");

// *thisが保持している型をTjとしたとき、
// is_nothrow_constructible<Tj, T> &&
// is_nothrow_assignable<Tj&, T>がtrueであるとき、
// is_nothrow_assignable<variant<Types...>, T> がtrueになる
static_assert( hamon::is_nothrow_assignable<hamon::variant<S2_1>, int>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::variant<S2_2>, int>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::variant<S2_3>, int>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::variant<S2_4>, int>::value, "");

#if !defined(HAMON_NO_EXCEPTIONS)

struct ThrowOnCtor
{
	int value;
	ThrowOnCtor() : value(0) {}
	ThrowOnCtor(int) noexcept(false) { throw 42; }
	ThrowOnCtor& operator=(int v) noexcept
	{
		value = v;
		return *this;
	}
};

struct ThrowOnAssign
{
	int value;
	ThrowOnAssign() : value(0) {}
	ThrowOnAssign(int v) noexcept : value(v) {}
	ThrowOnAssign& operator=(int) noexcept(false) { throw 42; }
};

#endif

inline HAMON_CXX20_CONSTEXPR bool AssignTTest()
{
	using std::get;
	{
		hamon::variant<int> v(43);
		v = 42;
		VERIFY(v.index() == 0u);
		VERIFY(get<0>(v) == 42);
	}
	{
		hamon::variant<int, long> v(43L);
		v = 42;
		VERIFY(v.index() == 0u);
		VERIFY(get<0>(v) == 42);
		v = 43L;
		VERIFY(v.index() == 1u);
		VERIFY(get<1>(v) == 43);
	}
	return true;
}

GTEST_TEST(VariantTest, AssignTTest)
{
#if defined(HAMON_HAS_CXX20_CONSTEXPR_UNION) && !defined(HAMON_APPLE_CLANG)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(AssignTTest());
#else
	EXPECT_TRUE(AssignTTest());
#endif

	using std::get;
	{
		hamon::variant<float, std::string> v = 0.5f;
		v = "foo";
		EXPECT_EQ(v.index(), 1u);
		EXPECT_EQ(get<1>(v), "foo");
		v = 2.5f;
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(get<0>(v), 2.5f);
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::variant<std::string, ThrowOnCtor> v(
			hamon::in_place_index_t<0>{}, "hoge");

		// ThrowOnCtor::ThrowOnCtor(int) を呼び出すので例外を投げる
		EXPECT_THROW(v = 42, int);
		
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(get<0>(v), "hoge");
	}
	{
		hamon::variant<std::string, ThrowOnAssign> v(
			hamon::in_place_index_t<0>{}, "hoge");
		
		// ThrowOnAssign::ThrowOnAssign(int) を呼び出すので例外を投げない
		v = 42;

		EXPECT_EQ(v.index(), 1u);
		EXPECT_EQ(get<1>(v).value, 42);
	}
	{
		hamon::variant<ThrowOnCtor, std::string> v;

		// ThrowOnCtor::operator=(int) を呼び出すので例外を投げない
		v = 42;

		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(get<0>(v).value, 42);
	}
	{
		hamon::variant<ThrowOnAssign, std::string> v;

		// ThrowOnAssign::operator=(int) を呼び出すので例外を投げる
		EXPECT_THROW(v = 42, int);

		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(get<0>(v).value, 0);
	}
#endif
}

#undef VERIFY

}	// namespace assign_t_test

}	// namespace hamon_variant_test
