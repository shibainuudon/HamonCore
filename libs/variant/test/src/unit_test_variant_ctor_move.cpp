﻿/**
 *	@file	unit_test_variant_ctor_move.cpp
 *
 *	@brief	variant(variant &&) のテスト
 */

#include <hamon/variant.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_variant_test
{

namespace ctor_move_test
{

struct CopyOnlyTrivial
{
	HAMON_CXX11_CONSTEXPR CopyOnlyTrivial(CopyOnlyTrivial const&) = default;
	HAMON_CXX11_CONSTEXPR CopyOnlyTrivial(CopyOnlyTrivial &&) = delete;
};

struct CopyOnlyNonTrivial
{
	HAMON_CXX11_CONSTEXPR CopyOnlyNonTrivial(CopyOnlyNonTrivial const&) {}
	HAMON_CXX11_CONSTEXPR CopyOnlyNonTrivial(CopyOnlyNonTrivial &&) = delete;
};

struct MoveOnlyTrivial
{
	HAMON_CXX11_CONSTEXPR MoveOnlyTrivial(MoveOnlyTrivial const&) = delete;
	HAMON_CXX11_CONSTEXPR MoveOnlyTrivial(MoveOnlyTrivial &&) = default;
};

struct MoveOnlyNonTrivial
{
	int value;
	HAMON_CXX11_CONSTEXPR MoveOnlyNonTrivial(int v) : value(v) {}
	HAMON_CXX11_CONSTEXPR MoveOnlyNonTrivial(MoveOnlyNonTrivial const&) = delete;
	HAMON_CXX11_CONSTEXPR MoveOnlyNonTrivial(MoveOnlyNonTrivial && rhs) : value(rhs.value) {}
};

struct Noexcept
{
	HAMON_CXX11_CONSTEXPR Noexcept(Noexcept &&) noexcept(true) {}
};
static_assert( hamon::is_nothrow_move_constructible<Noexcept>::value, "");

struct NotNoexcept
{
	HAMON_CXX11_CONSTEXPR NotNoexcept(NotNoexcept &&) noexcept(false) {}
};
static_assert(!hamon::is_nothrow_move_constructible<NotNoexcept>::value, "");

// Tiが全てムーブ構築可能であれば、ムーブ構築可能
static_assert( hamon::is_move_constructible<hamon::variant<int>>::value, "");
static_assert( hamon::is_move_constructible<hamon::variant<float>>::value, "");
static_assert( hamon::is_move_constructible<hamon::variant<CopyOnlyTrivial>>::value, "");
static_assert( hamon::is_move_constructible<hamon::variant<CopyOnlyNonTrivial>>::value, "");
static_assert( hamon::is_move_constructible<hamon::variant<MoveOnlyTrivial>>::value, "");
static_assert( hamon::is_move_constructible<hamon::variant<MoveOnlyNonTrivial>>::value, "");
static_assert( hamon::is_move_constructible<hamon::variant<Noexcept>>::value, "");
static_assert( hamon::is_move_constructible<hamon::variant<NotNoexcept>>::value, "");
static_assert( hamon::is_move_constructible<hamon::variant<int, float>>::value, "");
static_assert( hamon::is_move_constructible<hamon::variant<int, CopyOnlyTrivial>>::value, "");
static_assert( hamon::is_move_constructible<hamon::variant<int, CopyOnlyNonTrivial>>::value, "");
static_assert( hamon::is_move_constructible<hamon::variant<int, MoveOnlyTrivial>>::value, "");
static_assert( hamon::is_move_constructible<hamon::variant<int, MoveOnlyNonTrivial>>::value, "");
static_assert( hamon::is_move_constructible<hamon::variant<int, Noexcept>>::value, "");
static_assert( hamon::is_move_constructible<hamon::variant<int, NotNoexcept>>::value, "");

// Tiが全てトリビアルにムーブ構築可能であれば、トリビアルにムーブ構築可能
static_assert( hamon::is_trivially_move_constructible<hamon::variant<int>>::value, "");
static_assert( hamon::is_trivially_move_constructible<hamon::variant<float>>::value, "");
static_assert( hamon::is_trivially_move_constructible<hamon::variant<CopyOnlyTrivial>>::value, "");
static_assert(!hamon::is_trivially_move_constructible<hamon::variant<CopyOnlyNonTrivial>>::value, "");
static_assert( hamon::is_trivially_move_constructible<hamon::variant<int, float>>::value, "");
static_assert( hamon::is_trivially_move_constructible<hamon::variant<int, CopyOnlyTrivial>>::value, "");
static_assert(!hamon::is_trivially_move_constructible<hamon::variant<int, CopyOnlyNonTrivial>>::value, "");

// Tiが全て例外を投げずにムーブ構築可能であれば、例外を投げずにムーブ構築可能
static_assert( hamon::is_nothrow_move_constructible<hamon::variant<int>>::value, "");
static_assert( hamon::is_nothrow_move_constructible<hamon::variant<Noexcept>>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<hamon::variant<NotNoexcept>>::value, "");
static_assert( hamon::is_nothrow_move_constructible<hamon::variant<int, int>>::value, "");
static_assert( hamon::is_nothrow_move_constructible<hamon::variant<int, Noexcept>>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<hamon::variant<int, NotNoexcept>>::value, "");

#if !defined(HAMON_NO_EXCEPTIONS)

struct ThrowOnMove
{
	int value;
	ThrowOnMove(int v) : value(v) {}
	ThrowOnMove(ThrowOnMove const&) = default;
	ThrowOnMove(ThrowOnMove &&) : value() { throw 42; }
	ThrowOnMove& operator=(ThrowOnMove const&) = default;
	ThrowOnMove& operator=(ThrowOnMove &&) { throw 42; }
};

template <typename Variant>
void MakeEmpty(Variant& v)
{
	Variant v2(hamon::in_place_type_t<ThrowOnMove>{}, 0);
	try
	{
		v = hamon::move(v2);
	}
	catch (...)
	{
	}
}

#endif

GTEST_TEST(VariantTest, CtorMoveTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int> v1(42);
		HAMON_CXX11_CONSTEXPR hamon::variant<int> v2 = hamon::move(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v2.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<0>(v2), 42);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, float> v1(41);
		HAMON_CXX11_CONSTEXPR hamon::variant<int, float> v2 = hamon::move(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v2.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<0>(v2), 41);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, float> v1(4.5f);
		HAMON_CXX11_CONSTEXPR hamon::variant<int, float> v2 = hamon::move(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v2.index(), 1u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::adl_get<1>(v2), 4.5f);
	}
	{
		hamon::variant<int, hamon::string, float> v1 = 13;
		hamon::variant<int, hamon::string, float> v2 = hamon::move(v1);
		EXPECT_EQ(v2.index(), 0u);
		EXPECT_EQ(hamon::adl_get<0>(v2), 13);
	}
	{
		hamon::variant<int, hamon::string, float> v1 = "hello";
		hamon::variant<int, hamon::string, float> v2 = hamon::move(v1);
		EXPECT_EQ(v2.index(), 1u);
		EXPECT_EQ(hamon::adl_get<1>(v2), "hello");
	}
	{
		hamon::variant<int, hamon::string, float> v1 = 1.5f;
		hamon::variant<int, hamon::string, float> v2 = hamon::move(v1);
		EXPECT_EQ(v2.index(), 2u);
		EXPECT_EQ(hamon::adl_get<2>(v2), 1.5f);
	}
	{
		hamon::variant<int, MoveOnlyNonTrivial, float> v1(
			hamon::in_place_index_t<1>{}, 42);
		hamon::variant<int, MoveOnlyNonTrivial, float> v2 = hamon::move(v1);
		EXPECT_EQ(v2.index(), 1u);
		EXPECT_EQ(hamon::adl_get<1>(v2).value, 42);
	}

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::variant<int, ThrowOnMove> v1(hamon::in_place_index_t<0>{}, 42);
		MakeEmpty(v1);
		EXPECT_TRUE(v1.valueless_by_exception());

		hamon::variant<int, ThrowOnMove> v2(hamon::move(v1));
		EXPECT_TRUE(v2.valueless_by_exception());
	}
#endif
}

}	// namespace ctor_move_test

}	// namespace hamon_variant_test
