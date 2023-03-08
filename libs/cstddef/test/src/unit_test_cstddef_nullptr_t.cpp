/**
 *	@file	unit_test_cstddef_nullptr_t.cpp
 *
 *	@brief	nullptr_t のテスト
 */

#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/type_traits/is_same.hpp>

// nullptr_t は nullptr リテラルの型
static_assert(hamon::is_same<hamon::nullptr_t, decltype(nullptr)>::value, "");

// nullptr_t は sizeof(void*)と同じサイズ
static_assert(sizeof(hamon::nullptr_t) == sizeof(void*), "");
