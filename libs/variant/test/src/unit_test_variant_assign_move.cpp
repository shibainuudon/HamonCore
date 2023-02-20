/**
 *	@file	unit_test_variant_assign_move.cpp
 *
 *	@brief	variant& operator=(variant&&) のテスト
 */

#include <hamon/variant.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_variant_test
{

namespace assign_move_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct S1_1
{
	S1_1(S1_1 const&)            = delete;
	S1_1& operator=(S1_1 const&) = delete;
	S1_1(S1_1 &&)                = default;
	S1_1& operator=(S1_1 &&)     = default;
};

struct S1_2
{
	S1_2(S1_2 const&)            = delete;
	S1_2& operator=(S1_2 const&) = delete;
	S1_2(S1_2 &&)                = delete;
	S1_2& operator=(S1_2 &&)     = default;
};

struct S1_3
{
	S1_3(S1_3 const&)            = delete;
	S1_3& operator=(S1_3 const&) = delete;
	S1_3(S1_3 &&)                = default;
	S1_3& operator=(S1_3 &&)     = delete;
};

struct S1_4
{
	S1_4(S1_4 const&)            = delete;
	S1_4& operator=(S1_4 const&) = delete;
	S1_4(S1_4 &&)                = delete;
	S1_4& operator=(S1_4 &&)     = delete;
};

static_assert( hamon::is_move_constructible<S1_1>::value, "");
static_assert(!hamon::is_move_constructible<S1_2>::value, "");
static_assert( hamon::is_move_constructible<S1_3>::value, "");
static_assert(!hamon::is_move_constructible<S1_4>::value, "");
static_assert( hamon::is_move_assignable<S1_1>::value, "");
static_assert( hamon::is_move_assignable<S1_2>::value, "");
static_assert(!hamon::is_move_assignable<S1_3>::value, "");
static_assert(!hamon::is_move_assignable<S1_4>::value, "");

// Types...のすべての型Tiについて、
// is_move_constructible_v<Ti> &&
// is_move_assignable_v<Ti>がtrueであるとき、
// is_move_assignable_v<variant<Types...>> がtrueになる
static_assert( hamon::is_move_assignable<hamon::variant<S1_1>>::value, "");
static_assert(!hamon::is_move_assignable<hamon::variant<S1_2>>::value, "");
static_assert(!hamon::is_move_assignable<hamon::variant<S1_3>>::value, "");
static_assert(!hamon::is_move_assignable<hamon::variant<S1_4>>::value, "");

struct S2_1
{
	S2_1(S2_1 const&)            = delete;
	S2_1& operator=(S2_1 const&) = delete;
	S2_1(S2_1 &&)                = default;
	S2_1& operator=(S2_1 &&)     = default;
	~S2_1()                      = default;
};

struct S2_2
{
	S2_2(S2_2 const&)            = delete;
	S2_2& operator=(S2_2 const&) = delete;
	S2_2(S2_2 &&)                {}
	S2_2& operator=(S2_2 &&)     = default;
	~S2_2()                      = default;
};

struct S2_3
{
	S2_3(S2_3 const&)            = delete;
	S2_3& operator=(S2_3 const&) = delete;
	S2_3(S2_3 &&)                = default;
	S2_3& operator=(S2_3 &&)     {return *this;}
	~S2_3()                      = default;
};

struct S2_4
{
	S2_4(S2_4 const&)            = delete;
	S2_4& operator=(S2_4 const&) = delete;
	S2_4(S2_4 &&)                {}
	S2_4& operator=(S2_4 &&)     {return *this;}
	~S2_4()                      = default;
};

struct S2_5
{
	S2_5(S2_5 const&)            = delete;
	S2_5& operator=(S2_5 const&) = delete;
	S2_5(S2_5 &&)                = default;
	S2_5& operator=(S2_5 &&)     = default;
	~S2_5()                      {}
};

struct S2_6
{
	S2_6(S2_6 const&)            = delete;
	S2_6& operator=(S2_6 const&) = delete;
	S2_6(S2_6 &&)                {}
	S2_6& operator=(S2_6 &&)     = default;
	~S2_6()                      {}
};

struct S2_7
{
	S2_7(S2_7 const&)            = delete;
	S2_7& operator=(S2_7 const&) = delete;
	S2_7(S2_7 &&)                = default;
	S2_7& operator=(S2_7 &&)     {return *this;}
	~S2_7()                      {}
};

struct S2_8
{
	S2_8(S2_8 const&)            = delete;
	S2_8& operator=(S2_8 const&) = delete;
	S2_8(S2_8 &&)                {}
	S2_8& operator=(S2_8 &&)     {return *this;}
	~S2_8()                      {}
};

static_assert( hamon::is_trivially_move_constructible<S2_1>::value, "");
static_assert(!hamon::is_trivially_move_constructible<S2_2>::value, "");
static_assert( hamon::is_trivially_move_constructible<S2_3>::value, "");
static_assert(!hamon::is_trivially_move_constructible<S2_4>::value, "");
static_assert(!hamon::is_trivially_move_constructible<S2_5>::value, "");
static_assert(!hamon::is_trivially_move_constructible<S2_6>::value, "");
static_assert(!hamon::is_trivially_move_constructible<S2_7>::value, "");
static_assert(!hamon::is_trivially_move_constructible<S2_8>::value, "");
static_assert( hamon::is_trivially_move_assignable<S2_1>::value, "");
static_assert( hamon::is_trivially_move_assignable<S2_2>::value, "");
static_assert(!hamon::is_trivially_move_assignable<S2_3>::value, "");
static_assert(!hamon::is_trivially_move_assignable<S2_4>::value, "");
static_assert( hamon::is_trivially_move_assignable<S2_5>::value, "");
static_assert( hamon::is_trivially_move_assignable<S2_6>::value, "");
static_assert(!hamon::is_trivially_move_assignable<S2_7>::value, "");
static_assert(!hamon::is_trivially_move_assignable<S2_8>::value, "");
static_assert( hamon::is_trivially_destructible<S2_1>::value, "");
static_assert( hamon::is_trivially_destructible<S2_2>::value, "");
static_assert( hamon::is_trivially_destructible<S2_3>::value, "");
static_assert( hamon::is_trivially_destructible<S2_4>::value, "");
static_assert(!hamon::is_trivially_destructible<S2_5>::value, "");
static_assert(!hamon::is_trivially_destructible<S2_6>::value, "");
static_assert(!hamon::is_trivially_destructible<S2_7>::value, "");
static_assert(!hamon::is_trivially_destructible<S2_8>::value, "");

// Types...のすべての型Tiについて、
// is_trivially_move_constructible_v<Ti> &&
// is_trivially_move_assignable_v<Ti> &&
// is_trivially_destructible_v<Ti>がtrueであるとき、
// is_trivially_move_assignable_v<variant<Types...>> がtrueになる
static_assert( hamon::is_trivially_move_assignable<hamon::variant<S2_1>>::value, "");
static_assert(!hamon::is_trivially_move_assignable<hamon::variant<S2_2>>::value, "");
static_assert(!hamon::is_trivially_move_assignable<hamon::variant<S2_3>>::value, "");
static_assert(!hamon::is_trivially_move_assignable<hamon::variant<S2_4>>::value, "");
static_assert(!hamon::is_trivially_move_assignable<hamon::variant<S2_5>>::value, "");
static_assert(!hamon::is_trivially_move_assignable<hamon::variant<S2_6>>::value, "");
static_assert(!hamon::is_trivially_move_assignable<hamon::variant<S2_7>>::value, "");
static_assert(!hamon::is_trivially_move_assignable<hamon::variant<S2_8>>::value, "");


struct S3_1
{
	S3_1(S3_1 const&)            = delete;
	S3_1& operator=(S3_1 const&) = delete;
	S3_1(S3_1 &&)                noexcept(true);
	S3_1& operator=(S3_1 &&)     noexcept(true);
};

struct S3_2
{
	S3_2(S3_2 const&)            = delete;
	S3_2& operator=(S3_2 const&) = delete;
	S3_2(S3_2 &&)                noexcept(false);
	S3_2& operator=(S3_2 &&)     noexcept(true);
};

struct S3_3
{
	S3_3(S3_3 const&)            = delete;
	S3_3& operator=(S3_3 const&) = delete;
	S3_3(S3_3 &&)                noexcept(true);
	S3_3& operator=(S3_3 &&)     noexcept(false);
};

struct S3_4
{
	S3_4(S3_4 const&)            = delete;
	S3_4& operator=(S3_4 const&) = delete;
	S3_4(S3_4 &&)                noexcept(false);
	S3_4& operator=(S3_4 &&)     noexcept(false);
};

static_assert( hamon::is_nothrow_move_constructible<S3_1>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<S3_2>::value, "");
static_assert( hamon::is_nothrow_move_constructible<S3_3>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<S3_4>::value, "");
static_assert( hamon::is_nothrow_move_assignable<S3_1>::value, "");
static_assert( hamon::is_nothrow_move_assignable<S3_2>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<S3_3>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<S3_4>::value, "");

// Types...のすべての型Tiについて、
// is_nothrow_move_constructible<Ti> &&
// is_nothrow_move_assignable<Ti>がtrueであるとき、
// is_nothrow_move_assignable<variant<Types...>> がtrueになる
static_assert( hamon::is_nothrow_move_assignable<hamon::variant<S3_1>>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::variant<S3_2>>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::variant<S3_3>>::value, "");
static_assert(!hamon::is_nothrow_move_assignable<hamon::variant<S3_4>>::value, "");

struct MoveOnlyTrivial
{
	int value;
	HAMON_CXX11_CONSTEXPR MoveOnlyTrivial(int v) : value(v) {}
	HAMON_CXX11_CONSTEXPR MoveOnlyTrivial(MoveOnlyTrivial const&) = delete;
	HAMON_CXX11_CONSTEXPR MoveOnlyTrivial(MoveOnlyTrivial &&) = default;
	HAMON_CXX14_CONSTEXPR MoveOnlyTrivial& operator=(MoveOnlyTrivial const&) = delete;
	HAMON_CXX14_CONSTEXPR MoveOnlyTrivial& operator=(MoveOnlyTrivial &&) = default;
};
static_assert( hamon::is_move_assignable<MoveOnlyTrivial>::value, "");
static_assert( hamon::is_trivially_move_assignable<MoveOnlyTrivial>::value, "");
static_assert(!hamon::is_copy_assignable<MoveOnlyTrivial>::value, "");

struct MoveOnlyNonTrivial
{
	int value;
	HAMON_CXX11_CONSTEXPR MoveOnlyNonTrivial(int v) : value(v) {}
	HAMON_CXX11_CONSTEXPR MoveOnlyNonTrivial(MoveOnlyNonTrivial const&) = delete;
	HAMON_CXX11_CONSTEXPR MoveOnlyNonTrivial(MoveOnlyNonTrivial && rhs) : value(rhs.value) {}
	HAMON_CXX14_CONSTEXPR MoveOnlyNonTrivial& operator=(MoveOnlyNonTrivial const&) = delete;
	HAMON_CXX14_CONSTEXPR MoveOnlyNonTrivial& operator=(MoveOnlyNonTrivial && rhs) { value = rhs.value; return *this; }
};
static_assert( hamon::is_move_assignable<MoveOnlyNonTrivial>::value, "");
static_assert(!hamon::is_trivially_move_assignable<MoveOnlyNonTrivial>::value, "");
static_assert(!hamon::is_copy_assignable<MoveOnlyNonTrivial>::value, "");

#if !defined(HAMON_NO_EXCEPTIONS)

struct ThrowOnCopy
{
	int value;
	ThrowOnCopy(int v) : value(v) {}
	ThrowOnCopy(ThrowOnCopy const&) : value() { throw 42; }
	ThrowOnCopy(ThrowOnCopy &&) = default;
	ThrowOnCopy& operator=(ThrowOnCopy const&) { throw 42; }
	ThrowOnCopy& operator=(ThrowOnCopy &&) = default;
};

struct ThrowOnMove
{
	int value;
	ThrowOnMove(int v) : value(v) {}
	ThrowOnMove(ThrowOnMove const&) = default;
	ThrowOnMove(ThrowOnMove &&) : value() { throw 42; }
	ThrowOnMove& operator=(ThrowOnMove const&) = default;
	ThrowOnMove& operator=(ThrowOnMove &&) { throw 42; }
};

struct MakeEmptyT
{
	int value;
	MakeEmptyT(int v) : value(v) {}
	MakeEmptyT(MakeEmptyT const&) = default;
	MakeEmptyT(MakeEmptyT &&) : value() { throw 42; }
	MakeEmptyT& operator=(MakeEmptyT const&) { throw 42; }
	MakeEmptyT& operator=(MakeEmptyT &&) { throw 42; }
};

template <typename Variant>
void MakeEmpty(Variant& v)
{
	Variant v2(hamon::in_place_type_t<MakeEmptyT>{}, 0);
	try
	{
		v = hamon::move(v2);
	}
	catch (...)
	{
	}
}

#endif

inline HAMON_CXX14_CONSTEXPR bool SameIndexConstexprTest()
{
	using std::get;

	{
		hamon::variant<int> v1(42);
		hamon::variant<int> v2(43);
		hamon::variant<int>& ref = (v1 = hamon::move(v2));
		VERIFY(&ref == &v1);
		VERIFY(v1.index() == 0u);
		VERIFY(get<0>(v1) == 43);
	}
	{
		hamon::variant<int, long, float> v1(13L);
		hamon::variant<int, long, float> v2(77L);
		hamon::variant<int, long, float>& ref = (v1 = hamon::move(v2));
		VERIFY(&ref == &v1);
		VERIFY(v1.index() == 1u);
		VERIFY(get<1>(v1) == 77);
	}
	{
		hamon::variant<MoveOnlyTrivial> v1(42);
		hamon::variant<MoveOnlyTrivial> v2(43);
		hamon::variant<MoveOnlyTrivial>& ref = (v1 = hamon::move(v2));
		VERIFY(&ref == &v1);
		VERIFY(v1.index() == 0u);
		VERIFY(get<0>(v1).value == 43);
	}
	{
		hamon::variant<int, float, MoveOnlyTrivial> v1(
			hamon::in_place_index_t<2>{}, 42);
		hamon::variant<int, float, MoveOnlyTrivial> v2(
			hamon::in_place_index_t<2>{}, 43);
		hamon::variant<int, float, MoveOnlyTrivial>& ref = (v1 = hamon::move(v2));
		VERIFY(&ref == &v1);
		VERIFY(v1.index() == 2u);
		VERIFY(get<2>(v1).value == 43);
	}

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool DifferentIndexConstexprTest()
{
	using std::get;

	{
		hamon::variant<int, long, float> v1(42);
		VERIFY(v1.index() == 0u);
		VERIFY(get<0>(v1) == 42);
		hamon::variant<int, long, float> v2(77L);
		hamon::variant<int, long, float>& ref = (v1 = hamon::move(v2));
		VERIFY(&ref == &v1);
		VERIFY(v1.index() == 1u);
		VERIFY(get<1>(v1) == 77);
	}
	{
		hamon::variant<int, float, MoveOnlyTrivial> v1(0.5f);
		VERIFY(v1.index() == 1u);
		VERIFY(get<1>(v1) == 0.5f);
		hamon::variant<int, float, MoveOnlyTrivial> v2(
			hamon::in_place_index_t<2>{}, 43);
		hamon::variant<int, float, MoveOnlyTrivial>& ref = (v1 = hamon::move(v2));
		VERIFY(&ref == &v1);
		VERIFY(v1.index() == 2u);
		VERIFY(get<2>(v1).value == 43);
	}

	return true;
}

GTEST_TEST(VariantTest, AssignMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SameIndexConstexprTest());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DifferentIndexConstexprTest());

	using std::get;

	// Same index
	{
		hamon::variant<MoveOnlyNonTrivial> v1(42);
		hamon::variant<MoveOnlyNonTrivial> v2(43);
		hamon::variant<MoveOnlyNonTrivial>& ref = (v1 = hamon::move(v2));
		EXPECT_TRUE(&ref == &v1);
		EXPECT_TRUE(v1.index() == 0u);
		EXPECT_TRUE(get<0>(v1).value == 43);
	}
	{
		hamon::variant<int, float, MoveOnlyNonTrivial> v1(
			hamon::in_place_index_t<2>{}, 42);
		hamon::variant<int, float, MoveOnlyNonTrivial> v2(
			hamon::in_place_index_t<2>{}, 43);
		hamon::variant<int, float, MoveOnlyNonTrivial>& ref = (v1 = hamon::move(v2));
		EXPECT_TRUE(&ref == &v1);
		EXPECT_TRUE(v1.index() == 2u);
		EXPECT_TRUE(get<2>(v1).value == 43);
	}

	// Different index
	{
		hamon::variant<int, float, MoveOnlyNonTrivial> v1(0.5f);
		EXPECT_TRUE(v1.index() == 1u);
		EXPECT_TRUE(get<1>(v1) == 0.5f);
		hamon::variant<int, float, MoveOnlyNonTrivial> v2(
			hamon::in_place_index_t<2>{}, 43);
		hamon::variant<int, float, MoveOnlyNonTrivial>& ref = (v1 = hamon::move(v2));
		EXPECT_TRUE(&ref == &v1);
		EXPECT_TRUE(v1.index() == 2u);
		EXPECT_TRUE(get<2>(v1).value == 43);
	}

#if !defined(HAMON_NO_EXCEPTIONS)
	// Same index
	{
		hamon::variant<int, ThrowOnMove> v1(hamon::in_place_index_t<1>{}, 42);
		hamon::variant<int, ThrowOnMove> v2(hamon::in_place_index_t<1>{}, 43);
		EXPECT_THROW(v1 = hamon::move(v2), int);
		EXPECT_EQ(v1.index(), 1u);
		EXPECT_EQ(get<1>(v1).value, 42);
	}
	{
		hamon::variant<int, ThrowOnCopy> v1(hamon::in_place_index_t<1>{}, 42);
		hamon::variant<int, ThrowOnCopy> v2(hamon::in_place_index_t<1>{}, 43);
		EXPECT_NO_THROW(v1 = hamon::move(v2));
		EXPECT_EQ(v1.index(), 1u);
		EXPECT_EQ(get<1>(v1).value, 43);
	}

	// Different index
	{
		hamon::variant<int, ThrowOnMove> v1(hamon::in_place_index_t<0>{}, 42);
		hamon::variant<int, ThrowOnMove> v2(hamon::in_place_index_t<1>{}, 43);
		EXPECT_THROW(v1 = hamon::move(v2), int);
		EXPECT_TRUE(v1.valueless_by_exception());
		EXPECT_EQ(v1.index(), hamon::variant_npos);
	}
	{
		hamon::variant<int, ThrowOnMove> v1(hamon::in_place_index_t<1>{}, 42);
		hamon::variant<int, ThrowOnMove> v2(hamon::in_place_index_t<0>{}, 43);
		EXPECT_NO_THROW(v1 = hamon::move(v2));
		EXPECT_EQ(v1.index(), 0u);
		EXPECT_EQ(get<0>(v1), 43);
	}

	// Empty = Empty
	{
		hamon::variant<int, MakeEmptyT> v1(hamon::in_place_index_t<0>{}, 42);
		hamon::variant<int, MakeEmptyT> v2(hamon::in_place_index_t<0>{}, 43);
		MakeEmpty(v1);
		MakeEmpty(v2);
		EXPECT_TRUE( v1.valueless_by_exception());
		EXPECT_TRUE( v2.valueless_by_exception());

		hamon::variant<int, MakeEmptyT>& ref = (v1 = hamon::move(v2));
		EXPECT_TRUE(&ref == &v1);
		EXPECT_TRUE( v1.valueless_by_exception());
		EXPECT_EQ(v1.index(), hamon::variant_npos);
	}

	// Non-Empty = Empty
	{
		hamon::variant<int, MakeEmptyT> v1(hamon::in_place_index_t<0>{}, 42);
		hamon::variant<int, MakeEmptyT> v2(hamon::in_place_index_t<0>{}, 43);
		MakeEmpty(v2);
		EXPECT_TRUE(!v1.valueless_by_exception());
		EXPECT_TRUE( v2.valueless_by_exception());

		hamon::variant<int, MakeEmptyT>& ref = (v1 = hamon::move(v2));
		EXPECT_TRUE(&ref == &v1);
		EXPECT_TRUE( v1.valueless_by_exception());
		EXPECT_EQ(v1.index(), hamon::variant_npos);
	}

	// Empty = Non-Empty
	{
		hamon::variant<int, MakeEmptyT> v1(hamon::in_place_index_t<0>{}, 42);
		hamon::variant<int, MakeEmptyT> v2(hamon::in_place_index_t<0>{}, 43);
		MakeEmpty(v1);
		EXPECT_TRUE( v1.valueless_by_exception());
		EXPECT_TRUE(!v2.valueless_by_exception());

		hamon::variant<int, MakeEmptyT>& ref = (v1 = hamon::move(v2));
		EXPECT_TRUE(&ref == &v1);
		EXPECT_TRUE(!v1.valueless_by_exception());
		EXPECT_EQ(v1.index(), 0u);
		EXPECT_EQ(get<0>(v1), 43);
	}
#endif
}

#undef VERIFY

}	// namespace assign_move_test

}	// namespace hamon_variant_test
