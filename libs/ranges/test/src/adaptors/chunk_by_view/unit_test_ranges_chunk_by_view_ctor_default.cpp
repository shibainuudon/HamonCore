/**
 *	@file	unit_test_ranges_chunk_by_view_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	chunk_by_view() requires default_initializable<V> && default_initializable<Pred> = default;
 */

#include <hamon/ranges/adaptors/chunk_by_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace chunk_by_view_test
{
namespace ctor_default_test
{

struct F1
{
	bool operator()(int, int) const { return true; }
};

struct F2
{
	F2() = delete;
	bool operator()(int, int) const;
};

struct F3
{
	F3() noexcept(false) {}
	bool operator()(int, int) const;
};

template <typename T>
struct NoDefaultCtor : hamon::ranges::view_base
{
	NoDefaultCtor() = delete;

	HAMON_CXX11_CONSTEXPR T* begin() const noexcept { return nullptr; }
	HAMON_CXX11_CONSTEXPR T* end()   const noexcept { return nullptr; }
};

template <typename T>
struct NoThrowOnDefaultCtor : hamon::ranges::view_base
{
	NoThrowOnDefaultCtor() noexcept {}

	HAMON_CXX11_CONSTEXPR T* begin() const noexcept { return nullptr; }
	HAMON_CXX11_CONSTEXPR T* end()   const noexcept { return nullptr; }
};

static_assert( hamon::is_default_constructible<hamon::ranges::chunk_by_view<test_forward_view<int>, F1>>::value == true, "");
static_assert(!hamon::is_default_constructible<hamon::ranges::chunk_by_view<test_forward_view<int>, F2>>::value == true, "");
static_assert( hamon::is_default_constructible<hamon::ranges::chunk_by_view<test_forward_view<int>, F3>>::value == true, "");

static_assert(!hamon::is_default_constructible<hamon::ranges::chunk_by_view<NoDefaultCtor<int>, F1>>::value == true, "");
static_assert(!hamon::is_default_constructible<hamon::ranges::chunk_by_view<NoDefaultCtor<int>, F2>>::value == true, "");
static_assert(!hamon::is_default_constructible<hamon::ranges::chunk_by_view<NoDefaultCtor<int>, F3>>::value == true, "");

static_assert( hamon::is_default_constructible<hamon::ranges::chunk_by_view<NoThrowOnDefaultCtor<int>, F1>>::value == true, "");
static_assert(!hamon::is_default_constructible<hamon::ranges::chunk_by_view<NoThrowOnDefaultCtor<int>, F2>>::value == true, "");
static_assert( hamon::is_default_constructible<hamon::ranges::chunk_by_view<NoThrowOnDefaultCtor<int>, F3>>::value == true, "");

static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::chunk_by_view<test_forward_view<int>, F1>>::value == true, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::chunk_by_view<test_forward_view<int>, F2>>::value == true, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::chunk_by_view<test_forward_view<int>, F3>>::value == true, "");

static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::chunk_by_view<NoDefaultCtor<int>, F1>>::value == true, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::chunk_by_view<NoDefaultCtor<int>, F2>>::value == true, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::chunk_by_view<NoDefaultCtor<int>, F3>>::value == true, "");

static_assert( hamon::is_nothrow_default_constructible<hamon::ranges::chunk_by_view<NoThrowOnDefaultCtor<int>, F1>>::value == true, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::chunk_by_view<NoThrowOnDefaultCtor<int>, F2>>::value == true, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::chunk_by_view<NoThrowOnDefaultCtor<int>, F3>>::value == true, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using CV = hamon::ranges::chunk_by_view<test_forward_view<int>, F1>;
	CV cv{};
	VERIFY(cv.begin() == cv.end());
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ChunkByViewCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace ctor_default_test
}	// namespace chunk_by_view_test
}	// namespace hamon_ranges_test
