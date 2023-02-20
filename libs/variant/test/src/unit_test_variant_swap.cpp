/**
 *	@file	unit_test_variant_swap.cpp
 *
 *	@brief	constexpr void swap(variant& rhs) noexcept(see below); のテスト
 */

#include <hamon/variant.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"

namespace hamon_variant_test
{

namespace swap_test
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

struct S1_5
{
	S1_5(S1_5 const&)            = delete;
	S1_5& operator=(S1_5 const&) = delete;
	S1_5(S1_5 &&)                = default;
	S1_5& operator=(S1_5 &&)     = default;
};
void swap(S1_5&, S1_5&) = delete;

struct S1_6
{
	S1_6(S1_6 const&)            = delete;
	S1_6& operator=(S1_6 const&) = delete;
	S1_6(S1_6 &&)                = delete;
	S1_6& operator=(S1_6 &&)     = delete;
};
void swap(S1_6&, S1_6&);

static_assert( hamon::is_move_constructible<S1_1>::value, "");
static_assert(!hamon::is_move_constructible<S1_2>::value, "");
static_assert( hamon::is_move_constructible<S1_3>::value, "");
static_assert(!hamon::is_move_constructible<S1_4>::value, "");
static_assert( hamon::is_move_constructible<S1_5>::value, "");
static_assert(!hamon::is_move_constructible<S1_6>::value, "");
static_assert( hamon::is_move_assignable<S1_1>::value, "");
static_assert( hamon::is_move_assignable<S1_2>::value, "");
static_assert(!hamon::is_move_assignable<S1_3>::value, "");
static_assert(!hamon::is_move_assignable<S1_4>::value, "");
static_assert( hamon::is_move_assignable<S1_5>::value, "");
static_assert(!hamon::is_move_assignable<S1_6>::value, "");
static_assert( hamon::is_swappable<S1_1>::value, "");
#if HAMON_CXX_STANDARD >= 17
static_assert(!hamon::is_swappable<S1_2>::value, "");
static_assert(!hamon::is_swappable<S1_3>::value, "");
static_assert(!hamon::is_swappable<S1_4>::value, "");
#endif
static_assert(!hamon::is_swappable<S1_5>::value, "");
static_assert( hamon::is_swappable<S1_6>::value, "");

static_assert( hamon::is_swappable<hamon::variant<S1_1>>::value, "");
#if HAMON_CXX_STANDARD >= 17
static_assert(!hamon::is_swappable<hamon::variant<S1_2>>::value, "");
static_assert(!hamon::is_swappable<hamon::variant<S1_3>>::value, "");
static_assert(!hamon::is_swappable<hamon::variant<S1_4>>::value, "");
#endif
// TODO
//static_assert( hamon::is_swappable<hamon::variant<S1_5>>::value, "");
//static_assert(!hamon::is_swappable<hamon::variant<S1_6>>::value, "");

struct S2_1
{
	S2_1(S2_1 const&)            = delete;
	S2_1& operator=(S2_1 const&) = delete;
	S2_1(S2_1 &&)                noexcept(true);
	S2_1& operator=(S2_1 &&)     noexcept(true);
};

struct S2_2
{
	S2_2(S2_2 const&)            = delete;
	S2_2& operator=(S2_2 const&) = delete;
	S2_2(S2_2 &&)                noexcept(false);
	S2_2& operator=(S2_2 &&)     noexcept(true);
};

struct S2_3
{
	S2_3(S2_3 const&)            = delete;
	S2_3& operator=(S2_3 const&) = delete;
	S2_3(S2_3 &&)                noexcept(true);
	S2_3& operator=(S2_3 &&)     noexcept(false);
};

struct S2_4
{
	S2_4(S2_4 const&)            = delete;
	S2_4& operator=(S2_4 const&) = delete;
	S2_4(S2_4 &&)                noexcept(false);
	S2_4& operator=(S2_4 &&)     noexcept(false);
};

struct S2_5
{
	S2_5(S2_5 const&)            = delete;
	S2_5& operator=(S2_5 const&) = delete;
	S2_5(S2_5 &&)                noexcept(true);
	S2_5& operator=(S2_5 &&)     noexcept(true);
};
void swap(S2_5&, S2_5&) noexcept(false);

struct S2_6
{
	S2_6(S2_6 const&)            = delete;
	S2_6& operator=(S2_6 const&) = delete;
	S2_6(S2_6 &&)                noexcept(false);
	S2_6& operator=(S2_6 &&)     noexcept(false);
};
void swap(S2_6&, S2_6&) noexcept(true);

static_assert( hamon::is_nothrow_move_constructible<S2_1>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<S2_2>::value, "");
static_assert( hamon::is_nothrow_move_constructible<S2_3>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<S2_4>::value, "");
static_assert( hamon::is_nothrow_move_constructible<S2_5>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<S2_6>::value, "");
static_assert( hamon::is_nothrow_swappable<S2_1>::value, "");
static_assert(!hamon::is_nothrow_swappable<S2_2>::value, "");
static_assert(!hamon::is_nothrow_swappable<S2_3>::value, "");
static_assert(!hamon::is_nothrow_swappable<S2_4>::value, "");
static_assert(!hamon::is_nothrow_swappable<S2_5>::value, "");
static_assert( hamon::is_nothrow_swappable<S2_6>::value, "");

static_assert( hamon::is_swappable<hamon::variant<int, float, char>>::value, "");
static_assert( hamon::is_swappable<hamon::variant<S2_1>>::value, "");
static_assert( hamon::is_swappable<hamon::variant<S2_2>>::value, "");
static_assert( hamon::is_swappable<hamon::variant<S2_3>>::value, "");
static_assert( hamon::is_swappable<hamon::variant<S2_4>>::value, "");
static_assert( hamon::is_swappable<hamon::variant<S2_5>>::value, "");
static_assert( hamon::is_swappable<hamon::variant<S2_6>>::value, "");

static_assert( hamon::is_nothrow_swappable<hamon::variant<int, float, char>>::value, "");
static_assert( hamon::is_nothrow_swappable<hamon::variant<S2_1>>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::variant<S2_2>>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::variant<S2_3>>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::variant<S2_4>>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::variant<S2_5>>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::variant<S2_6>>::value, "");

#if !defined(HAMON_NO_EXCEPTIONS)

struct ThrowOnMoveCtor
{
	int value;
	ThrowOnMoveCtor(int v) : value(v) {}
	ThrowOnMoveCtor(ThrowOnMoveCtor const&) = default;
	ThrowOnMoveCtor(ThrowOnMoveCtor &&) : value() { throw 42; }
	ThrowOnMoveCtor& operator=(ThrowOnMoveCtor const&) = default;
	ThrowOnMoveCtor& operator=(ThrowOnMoveCtor &&) = default;
};

void swap(ThrowOnMoveCtor& lhs, ThrowOnMoveCtor& rhs)
{
	using std::swap;
	swap(lhs.value, rhs.value);
}

struct ThrowOnMoveAssign
{
	int value;
	ThrowOnMoveAssign(int v) : value(v) {}
	ThrowOnMoveAssign(ThrowOnMoveAssign const&) = default;
	ThrowOnMoveAssign(ThrowOnMoveAssign &&) = default;
	ThrowOnMoveAssign& operator=(ThrowOnMoveAssign const&) = default;
	ThrowOnMoveAssign& operator=(ThrowOnMoveAssign &&) { throw 42; }
};

void swap(ThrowOnMoveAssign& lhs, ThrowOnMoveAssign& rhs)
{
	using std::swap;
	swap(lhs.value, rhs.value);
}

struct ThrowOnSwap
{
	int value;
	ThrowOnSwap(int v) : value(v) {}
	ThrowOnSwap(ThrowOnSwap const&) = default;
	ThrowOnSwap(ThrowOnSwap &&) = default;
	ThrowOnSwap& operator=(ThrowOnSwap const&) = default;
	ThrowOnSwap& operator=(ThrowOnSwap &&) = default;
};

void swap(ThrowOnSwap&, ThrowOnSwap&)
{
	throw 42;
}

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

inline HAMON_CXX14_CONSTEXPR bool SwapTest()
{
	using std::get;
	using std::swap;

	// same index
	{
		hamon::variant<int> v1(42);
		hamon::variant<int> v2(43);
		v1.swap(v2);
		VERIFY(get<0>(v1) == 43);
		VERIFY(get<0>(v2) == 42);
		swap(v1, v2);
		VERIFY(get<0>(v1) == 42);
		VERIFY(get<0>(v2) == 43);
	}
	{
		hamon::variant<int, float> v1(0.5f);
		hamon::variant<int, float> v2(1.5f);
		v1.swap(v2);
		VERIFY(get<1>(v1) == 1.5f);
		VERIFY(get<1>(v2) == 0.5f);
		swap(v1, v2);
		VERIFY(get<1>(v1) == 0.5f);
		VERIFY(get<1>(v2) == 1.5f);
	}

	// different index
	{
		hamon::variant<int, float> v1(42);
		hamon::variant<int, float> v2(1.5f);
		v1.swap(v2);
		VERIFY(get<1>(v1) == 1.5f);
		VERIFY(get<0>(v2) == 42);
		swap(v1, v2);
		VERIFY(get<0>(v1) == 42);
		VERIFY(get<1>(v2) == 1.5f);
	}

	return true;
}

GTEST_TEST(VariantTest, SwapTest)
{
#if defined(HAMON_HAS_CXX20_CONSTEXPR_UNION)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(SwapTest());
#else
	EXPECT_TRUE(SwapTest());
#endif

#if !defined(HAMON_NO_EXCEPTIONS)
	using std::get;
	using std::swap;

	// same index
	{
		hamon::variant<ThrowOnMoveCtor, int> v1(hamon::in_place_index_t<0>{}, 42);
		hamon::variant<ThrowOnMoveCtor, int> v2(hamon::in_place_index_t<0>{}, 43);
		v1.swap(v2);
		EXPECT_EQ(43, get<0>(v1).value);
		EXPECT_EQ(42, get<0>(v2).value);
	}
	{
		hamon::variant<ThrowOnMoveAssign, int> v1(hamon::in_place_index_t<0>{}, 42);
		hamon::variant<ThrowOnMoveAssign, int> v2(hamon::in_place_index_t<0>{}, 43);
		v1.swap(v2);
		EXPECT_EQ(43, get<0>(v1).value);
		EXPECT_EQ(42, get<0>(v2).value);
	}
	{
		hamon::variant<ThrowOnSwap, int> v1(hamon::in_place_index_t<0>{}, 42);
		hamon::variant<ThrowOnSwap, int> v2(hamon::in_place_index_t<0>{}, 43);
		EXPECT_THROW(v1.swap(v2), int);
		EXPECT_EQ(42, get<0>(v1).value);
		EXPECT_EQ(43, get<0>(v2).value);
	}

	// different index
	{
		hamon::variant<ThrowOnMoveCtor, int> v1(hamon::in_place_index_t<0>{}, 42);
		hamon::variant<ThrowOnMoveCtor, int> v2(hamon::in_place_index_t<1>{}, 43);
		
		EXPECT_THROW(v1.swap(v2), int);
		
		if (!v1.valueless_by_exception())
		{
			EXPECT_EQ(42, get<0>(v1).value);
		}
		if (!v2.valueless_by_exception())
		{
			EXPECT_EQ(43, get<1>(v2));
		}
		
		EXPECT_THROW(v2.swap(v1), int);

		if (!v1.valueless_by_exception())
		{
			EXPECT_EQ(42, get<0>(v1).value);
		}
		if (!v2.valueless_by_exception())
		{
			EXPECT_EQ(43, get<1>(v2));
		}
	}
	{
		hamon::variant<ThrowOnMoveAssign, int> v1(hamon::in_place_index_t<0>{}, 42);
		hamon::variant<ThrowOnMoveAssign, int> v2(hamon::in_place_index_t<1>{}, 43);
		v1.swap(v2);
		EXPECT_EQ(43, get<1>(v1));
		EXPECT_EQ(42, get<0>(v2).value);
		v1.swap(v2);
		EXPECT_EQ(42, get<0>(v1).value);
		EXPECT_EQ(43, get<1>(v2));
	}
	{
		hamon::variant<ThrowOnSwap, int> v1(hamon::in_place_index_t<0>{}, 42);
		hamon::variant<ThrowOnSwap, int> v2(hamon::in_place_index_t<1>{}, 43);
		v1.swap(v2);
		EXPECT_EQ(43, get<1>(v1));
		EXPECT_EQ(42, get<0>(v2).value);
		v1.swap(v2);
		EXPECT_EQ(42, get<0>(v1).value);
		EXPECT_EQ(43, get<1>(v2));
	}

	// both empty
	{
		hamon::variant<int, MakeEmptyT> v1(hamon::in_place_index_t<0>{}, 42);
		hamon::variant<int, MakeEmptyT> v2(hamon::in_place_index_t<0>{}, 43);
		MakeEmpty(v1);
		MakeEmpty(v2);
		EXPECT_TRUE( v1.valueless_by_exception());
		EXPECT_TRUE( v2.valueless_by_exception());

		v1.swap(v2);
		EXPECT_TRUE( v1.valueless_by_exception());
		EXPECT_TRUE( v2.valueless_by_exception());

		swap(v1, v2);
		EXPECT_TRUE( v1.valueless_by_exception());
		EXPECT_TRUE( v2.valueless_by_exception());
	}

	// only one empty
	{
#if !defined(HAMON_USE_STD_VARIANT)
		hamon::variant<int, MakeEmptyT> v1(hamon::in_place_index_t<0>{}, 42);
		hamon::variant<int, MakeEmptyT> v2(hamon::in_place_index_t<0>{}, 43);
		MakeEmpty(v1);
		EXPECT_TRUE( v1.valueless_by_exception());
		EXPECT_TRUE(!v2.valueless_by_exception());

		v1.swap(v2);
		EXPECT_TRUE(!v1.valueless_by_exception());
		EXPECT_TRUE( v2.valueless_by_exception());

		v1.swap(v2);
		EXPECT_TRUE( v1.valueless_by_exception());
		EXPECT_TRUE(!v2.valueless_by_exception());

		swap(v1, v2);
		EXPECT_TRUE(!v1.valueless_by_exception());
		EXPECT_TRUE( v2.valueless_by_exception());

		swap(v1, v2);
		EXPECT_TRUE( v1.valueless_by_exception());
		EXPECT_TRUE(!v2.valueless_by_exception());
#endif
	}
#endif
}

#undef VERIFY

}	// namespace swap_test

}	// namespace hamon_variant_test
