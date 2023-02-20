/**
 *	@file	unit_test_variant_ctor_copy.cpp
 *
 *	@brief	variant(variant const&) のテスト
 */

#include <hamon/variant.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"

namespace hamon_variant_test
{

namespace ctor_copy_test
{

struct CopyOnlyTrivial
{
	int value;
	HAMON_CXX11_CONSTEXPR CopyOnlyTrivial(int v) : value(v) {}
	HAMON_CXX11_CONSTEXPR CopyOnlyTrivial(CopyOnlyTrivial const&) = default;
	HAMON_CXX11_CONSTEXPR CopyOnlyTrivial(CopyOnlyTrivial &&) = delete;
};
static_assert( hamon::is_copy_constructible<CopyOnlyTrivial>::value, "");
static_assert( hamon::is_trivially_copy_constructible<CopyOnlyTrivial>::value, "");

struct CopyOnlyNonTrivial
{
	int value;
	HAMON_CXX11_CONSTEXPR CopyOnlyNonTrivial(int v) : value(v) {}
	HAMON_CXX11_CONSTEXPR CopyOnlyNonTrivial(CopyOnlyNonTrivial const& rhs) : value(rhs.value) {}
	HAMON_CXX11_CONSTEXPR CopyOnlyNonTrivial(CopyOnlyNonTrivial &&) = delete;
};
static_assert( hamon::is_copy_constructible<CopyOnlyNonTrivial>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<CopyOnlyNonTrivial>::value, "");

struct MoveOnlyTrivial
{
	HAMON_CXX11_CONSTEXPR MoveOnlyTrivial(MoveOnlyTrivial const&) = delete;
	HAMON_CXX11_CONSTEXPR MoveOnlyTrivial(MoveOnlyTrivial &&) = default;
};
static_assert(!hamon::is_copy_constructible<MoveOnlyTrivial>::value, "");

struct MoveOnlyNonTrivial
{
	HAMON_CXX11_CONSTEXPR MoveOnlyNonTrivial(MoveOnlyNonTrivial const&) = delete;
	HAMON_CXX11_CONSTEXPR MoveOnlyNonTrivial(MoveOnlyNonTrivial &&) {}
};
static_assert(!hamon::is_copy_constructible<MoveOnlyNonTrivial>::value, "");

struct Noexcept
{
	HAMON_CXX11_CONSTEXPR Noexcept(Noexcept const&) noexcept(true) {}
};
static_assert( hamon::is_nothrow_copy_constructible<Noexcept>::value, "");

struct NotNoexcept
{
	HAMON_CXX11_CONSTEXPR NotNoexcept(NotNoexcept const&) noexcept(false) {}
};
static_assert(!hamon::is_nothrow_copy_constructible<NotNoexcept>::value, "");

// Tiが全てコピー構築可能であれば、コピー構築可能
static_assert( hamon::is_copy_constructible<hamon::variant<int>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::variant<float>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::variant<CopyOnlyTrivial>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::variant<CopyOnlyNonTrivial>>::value, "");
static_assert(!hamon::is_copy_constructible<hamon::variant<MoveOnlyTrivial>>::value, "");
static_assert(!hamon::is_copy_constructible<hamon::variant<MoveOnlyNonTrivial>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::variant<Noexcept>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::variant<NotNoexcept>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::variant<int, float>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::variant<int, CopyOnlyTrivial>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::variant<int, CopyOnlyNonTrivial>>::value, "");
static_assert(!hamon::is_copy_constructible<hamon::variant<int, MoveOnlyTrivial>>::value, "");
static_assert(!hamon::is_copy_constructible<hamon::variant<int, MoveOnlyNonTrivial>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::variant<int, Noexcept>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::variant<int, NotNoexcept>>::value, "");

// Tiが全てトリビアルにコピー構築可能であれば、トリビアルにコピー構築可能
static_assert( hamon::is_trivially_copy_constructible<hamon::variant<int>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::variant<float>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::variant<CopyOnlyTrivial>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::variant<CopyOnlyNonTrivial>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::variant<int, float>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::variant<int, CopyOnlyTrivial>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::variant<int, CopyOnlyNonTrivial>>::value, "");

#if !defined(HAMON_USE_STD_VARIANT)
// Tiが全て例外を投げずにコピー構築可能であれば、例外を投げずにコピー構築可能
static_assert( hamon::is_nothrow_copy_constructible<hamon::variant<int>>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<hamon::variant<CopyOnlyTrivial>>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<hamon::variant<Noexcept>>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<hamon::variant<NotNoexcept>>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<hamon::variant<int, int>>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<hamon::variant<int, CopyOnlyTrivial>>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<hamon::variant<int, Noexcept>>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<hamon::variant<int, NotNoexcept>>::value, "");
#endif

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

GTEST_TEST(VariantTest, CtorCopyTest)
{
	using std::get;
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int> v1(42);
		HAMON_CXX11_CONSTEXPR hamon::variant<int> v2 = v1;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v2.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(get<0>(v2), 42);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, float> v1(41);
		HAMON_CXX11_CONSTEXPR hamon::variant<int, float> v2 = v1;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v2.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(get<0>(v2), 41);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, float> v1(4.5f);
		HAMON_CXX11_CONSTEXPR hamon::variant<int, float> v2 = v1;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v2.index(), 1u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(get<1>(v2), 4.5f);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<CopyOnlyTrivial> v1(
			hamon::in_place_index_t<0>{}, 42);
		HAMON_CXX11_CONSTEXPR hamon::variant<CopyOnlyTrivial> v2 = v1;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(v2.index(), 0u);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(get<0>(v2).value, 42);
	}
#if 1//defined(HAMON_USE_STD_VARIANT)
	{
		hamon::variant<CopyOnlyNonTrivial> v1(
			hamon::in_place_index_t<0>{}, 42);
		hamon::variant<CopyOnlyNonTrivial> v2 = v1;
		EXPECT_EQ(v2.index(), 0u);
		EXPECT_EQ(get<0>(v2).value, 42);
	}
#else
	{
		HAMON_CXX20_CONSTEXPR hamon::variant<CopyOnlyNonTrivial> v1(
			hamon::in_place_index_t<0>{}, 42);
		HAMON_CXX20_CONSTEXPR hamon::variant<CopyOnlyNonTrivial> v2 = v1;
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(v2.index(), 0u);
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(get<0>(v2).value, 42);
	}
#endif
	{
		hamon::variant<int, std::string, float> v1 = 13;
		hamon::variant<int, std::string, float> v2 = v1;
		EXPECT_EQ(v2.index(), 0u);
		EXPECT_EQ(get<0>(v2), 13);
	}
	{
		hamon::variant<int, std::string, float> v1 = "hello";
		hamon::variant<int, std::string, float> v2 = v1;
		EXPECT_EQ(v2.index(), 1u);
		EXPECT_EQ(get<1>(v2), "hello");
	}
	{
		hamon::variant<int, std::string, float> v1 = 1.5f;
		hamon::variant<int, std::string, float> v2 = v1;
		EXPECT_EQ(v2.index(), 2u);
		EXPECT_EQ(get<2>(v2), 1.5f);
	}

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::variant<int, ThrowOnMove> v1(hamon::in_place_index_t<0>{}, 42);
		MakeEmpty(v1);
		EXPECT_TRUE(v1.valueless_by_exception());

		auto const& cv1 = v1;
		hamon::variant<int, ThrowOnMove> v2(cv1);
		EXPECT_TRUE(v2.valueless_by_exception());
	}
#endif
}

}	// namespace ctor_copy_test

}	// namespace hamon_variant_test
