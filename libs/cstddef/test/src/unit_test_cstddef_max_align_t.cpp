/**
 *	@file	unit_test_cstddef_max_align_t.cpp
 *
 *	@brief	max_align_t のテスト
 */

#include <hamon/cstddef/max_align_t.hpp>
#include <hamon/type_traits/is_trivially_default_constructible.hpp>
#include <hamon/type_traits/is_trivially_copyable.hpp>
#include <hamon/type_traits/is_standard_layout.hpp>

// max_align_t はトリビアル型
static_assert(hamon::is_trivially_default_constructible_v<hamon::max_align_t>, "");
static_assert(hamon::is_trivially_copyable_v<hamon::max_align_t>, "");

// max_align_t は標準レイアウト型
static_assert(hamon::is_standard_layout_v<hamon::max_align_t>, "");

// max_align_t はあらゆるスカラー型以上のアラインメントを必要とする型
static_assert(alignof(hamon::max_align_t) >= alignof(char), "");
static_assert(alignof(hamon::max_align_t) >= alignof(short), "");
static_assert(alignof(hamon::max_align_t) >= alignof(int), "");
static_assert(alignof(hamon::max_align_t) >= alignof(long), "");
static_assert(alignof(hamon::max_align_t) >= alignof(long long), "");
static_assert(alignof(hamon::max_align_t) >= alignof(float), "");
static_assert(alignof(hamon::max_align_t) >= alignof(double), "");
static_assert(alignof(hamon::max_align_t) >= alignof(long double), "");
static_assert(alignof(hamon::max_align_t) >= alignof(void*), "");
