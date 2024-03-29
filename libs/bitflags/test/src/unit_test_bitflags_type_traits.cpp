﻿/**
 *	@file	unit_test_bitflags_type_traits.cpp
 *
 *	@brief
 */

#include <hamon/bitflags.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_trivially_default_constructible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_copy_constructible.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_trivially_move_constructible.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_nothrow_copy_assignable.hpp>
#include <hamon/type_traits/is_trivially_copy_assignable.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_trivially_move_assignable.hpp>
#include <hamon/type_traits/is_destructible.hpp>
#include <hamon/type_traits/is_nothrow_destructible.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <hamon/cstdint/uint8_t.hpp>
#include <hamon/cstdint/uint16_t.hpp>
#include <gtest/gtest.h>
#include "bitflags_test.hpp"

namespace hamon_bitflags_test
{

// デフォルトコンストラクト可能
static_assert( hamon::is_default_constructible<Bitflag1>::value, "");
static_assert( hamon::is_default_constructible<Bitflag2>::value, "");
static_assert( hamon::is_default_constructible<Bitflag3>::value, "");
static_assert(!hamon::is_trivially_default_constructible<Bitflag1>::value, "");
static_assert(!hamon::is_trivially_default_constructible<Bitflag2>::value, "");
static_assert(!hamon::is_trivially_default_constructible<Bitflag3>::value, "");
static_assert( hamon::is_nothrow_default_constructible<Bitflag1>::value, "");
static_assert( hamon::is_nothrow_default_constructible<Bitflag2>::value, "");
static_assert( hamon::is_nothrow_default_constructible<Bitflag3>::value, "");
static_assert( hamon::is_implicitly_default_constructible<Bitflag1>::value, "");
static_assert( hamon::is_implicitly_default_constructible<Bitflag2>::value, "");
static_assert( hamon::is_implicitly_default_constructible<Bitflag3>::value, "");

// テンプレートパラメータで指定したenum型からはコンストラクト可能
static_assert( hamon::is_constructible<Bitflag1, Enum1>::value, "");
static_assert(!hamon::is_constructible<Bitflag1, Enum2>::value, "");
static_assert(!hamon::is_constructible<Bitflag1, Enum3>::value, "");
static_assert(!hamon::is_constructible<Bitflag2, Enum1>::value, "");
static_assert( hamon::is_constructible<Bitflag2, Enum2>::value, "");
static_assert(!hamon::is_constructible<Bitflag2, Enum3>::value, "");
static_assert(!hamon::is_constructible<Bitflag3, Enum1>::value, "");
static_assert(!hamon::is_constructible<Bitflag3, Enum2>::value, "");
static_assert( hamon::is_constructible<Bitflag3, Enum3>::value, "");

// 整数型からはコンストラクト不可
static_assert(!hamon::is_constructible<Bitflag1, int>::value, "");
static_assert(!hamon::is_constructible<Bitflag2, int>::value, "");
static_assert(!hamon::is_constructible<Bitflag3, int>::value, "");
static_assert(!hamon::is_constructible<Bitflag1, hamon::uint8_t>::value, "");
static_assert(!hamon::is_constructible<Bitflag2, hamon::uint8_t>::value, "");
static_assert(!hamon::is_constructible<Bitflag3, hamon::uint8_t>::value, "");
static_assert(!hamon::is_constructible<Bitflag1, hamon::uint16_t>::value, "");
static_assert(!hamon::is_constructible<Bitflag2, hamon::uint16_t>::value, "");
static_assert(!hamon::is_constructible<Bitflag3, hamon::uint16_t>::value, "");

// コンストラクト可能なenumでもimplicitコンストラクト不可
static_assert(!hamon::is_implicitly_constructible<Bitflag1, Enum1>::value, "");
static_assert(!hamon::is_implicitly_constructible<Bitflag2, Enum2>::value, "");
static_assert(!hamon::is_implicitly_constructible<Bitflag3, Enum3>::value, "");

// コンストラクト可能なenumでもnothrowコンストラクト不可
static_assert(!hamon::is_nothrow_constructible<Bitflag1, Enum1>::value, "");
static_assert(!hamon::is_nothrow_constructible<Bitflag2, Enum2>::value, "");
static_assert(!hamon::is_nothrow_constructible<Bitflag3, Enum3>::value, "");

// テンプレートパラメータが違うbitflag型からはコンストラクト不可
static_assert( hamon::is_constructible<Bitflag1, Bitflag1>::value, "");
static_assert(!hamon::is_constructible<Bitflag1, Bitflag2>::value, "");
static_assert(!hamon::is_constructible<Bitflag1, Bitflag3>::value, "");
static_assert(!hamon::is_constructible<Bitflag2, Bitflag1>::value, "");
static_assert( hamon::is_constructible<Bitflag2, Bitflag2>::value, "");
static_assert(!hamon::is_constructible<Bitflag2, Bitflag3>::value, "");
static_assert(!hamon::is_constructible<Bitflag3, Bitflag1>::value, "");
static_assert(!hamon::is_constructible<Bitflag3, Bitflag2>::value, "");
static_assert( hamon::is_constructible<Bitflag3, Bitflag3>::value, "");

// Copy Constructible
static_assert( hamon::is_copy_constructible<Bitflag1>::value, "");
static_assert( hamon::is_copy_constructible<Bitflag2>::value, "");
static_assert( hamon::is_copy_constructible<Bitflag3>::value, "");
static_assert( hamon::is_trivially_copy_constructible<Bitflag1>::value, "");
static_assert( hamon::is_trivially_copy_constructible<Bitflag2>::value, "");
static_assert( hamon::is_trivially_copy_constructible<Bitflag3>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<Bitflag1>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<Bitflag2>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<Bitflag3>::value, "");

// Move Constructible
static_assert( hamon::is_move_constructible<Bitflag1>::value, "");
static_assert( hamon::is_move_constructible<Bitflag2>::value, "");
static_assert( hamon::is_move_constructible<Bitflag3>::value, "");
static_assert( hamon::is_trivially_move_constructible<Bitflag1>::value, "");
static_assert( hamon::is_trivially_move_constructible<Bitflag2>::value, "");
static_assert( hamon::is_trivially_move_constructible<Bitflag3>::value, "");
static_assert( hamon::is_nothrow_move_constructible<Bitflag1>::value, "");
static_assert( hamon::is_nothrow_move_constructible<Bitflag2>::value, "");
static_assert( hamon::is_nothrow_move_constructible<Bitflag3>::value, "");

// Assignable
static_assert(!hamon::is_assignable<Bitflag1, Enum1>::value, "");
static_assert(!hamon::is_assignable<Bitflag1, Enum2>::value, "");
static_assert(!hamon::is_assignable<Bitflag1, Enum3>::value, "");
static_assert(!hamon::is_assignable<Bitflag1, int>::value, "");
static_assert(!hamon::is_assignable<Bitflag1, Bitflag2>::value, "");
static_assert(!hamon::is_assignable<Bitflag1, Bitflag3>::value, "");

// Copy Assignable
static_assert( hamon::is_copy_assignable<Bitflag1>::value, "");
static_assert( hamon::is_copy_assignable<Bitflag2>::value, "");
static_assert( hamon::is_copy_assignable<Bitflag3>::value, "");
static_assert( hamon::is_trivially_copy_assignable<Bitflag1>::value, "");
static_assert( hamon::is_trivially_copy_assignable<Bitflag2>::value, "");
static_assert( hamon::is_trivially_copy_assignable<Bitflag3>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<Bitflag1>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<Bitflag2>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<Bitflag3>::value, "");

// Move Assignable
static_assert( hamon::is_move_assignable<Bitflag1>::value, "");
static_assert( hamon::is_move_assignable<Bitflag2>::value, "");
static_assert( hamon::is_move_assignable<Bitflag3>::value, "");
static_assert( hamon::is_trivially_move_assignable<Bitflag1>::value, "");
static_assert( hamon::is_trivially_move_assignable<Bitflag2>::value, "");
static_assert( hamon::is_trivially_move_assignable<Bitflag3>::value, "");
static_assert( hamon::is_nothrow_move_assignable<Bitflag1>::value, "");
static_assert( hamon::is_nothrow_move_assignable<Bitflag2>::value, "");
static_assert( hamon::is_nothrow_move_assignable<Bitflag3>::value, "");

// Destructible
static_assert( hamon::is_destructible<Bitflag1>::value, "");
static_assert( hamon::is_destructible<Bitflag2>::value, "");
static_assert( hamon::is_destructible<Bitflag3>::value, "");
static_assert( hamon::is_trivially_destructible<Bitflag1>::value, "");
static_assert( hamon::is_trivially_destructible<Bitflag2>::value, "");
static_assert( hamon::is_trivially_destructible<Bitflag3>::value, "");
static_assert( hamon::is_nothrow_destructible<Bitflag1>::value, "");
static_assert( hamon::is_nothrow_destructible<Bitflag2>::value, "");
static_assert( hamon::is_nothrow_destructible<Bitflag3>::value, "");

}	// namespace hamon_bitflags_test
