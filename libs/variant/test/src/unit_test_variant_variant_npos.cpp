/**
 *	@file	unit_test_variant_variant_npos.cpp
 *
 *	@brief	variant_npos のテスト
 */

#include <hamon/variant/variant_npos.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>

static_assert(hamon::is_same<decltype(hamon::variant_npos), const hamon::size_t>::value, "");
static_assert(hamon::variant_npos == static_cast<hamon::size_t>(-1), "");
