/**
 *	@file	unit_test_thread_jthread_assign_copy.cpp
 *
 *	@brief	コピー代入演算子のテスト
 *
 *	jthread& operator=(const jthread&) = delete;
 */

#include <hamon/thread/jthread.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_jthread_test
{

namespace assign_copy_test
{

static_assert(!hamon::is_copy_assignable_v<hamon::jthread>, "");
static_assert(!hamon::is_nothrow_copy_assignable_v<hamon::jthread>, "");
static_assert(!hamon::is_trivially_copy_assignable_v<hamon::jthread>, "");

}	// namespace assign_copy_test

}	// namespace hamon_jthread_test
