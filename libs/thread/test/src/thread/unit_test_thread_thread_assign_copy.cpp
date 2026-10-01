/**
 *	@file	unit_test_thread_thread_assign_copy.cpp
 *
 *	@brief	コピー代入演算子のテスト
 *
 *	thread& operator=(thread const&) = delete;
 */

#include <hamon/thread/thread.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace assign_copy_test
{

static_assert(!hamon::is_copy_assignable_v<hamon::thread>, "");
static_assert(!hamon::is_nothrow_copy_assignable_v<hamon::thread>, "");
static_assert(!hamon::is_trivially_copy_assignable_v<hamon::thread>, "");

}	// namespace assign_copy_test

}	// namespace hamon_thread_test
