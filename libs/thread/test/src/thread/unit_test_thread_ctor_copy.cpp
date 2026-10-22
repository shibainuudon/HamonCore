/**
 *	@file	unit_test_thread_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	thread(thread const&) = delete;
 */

#include <hamon/thread/thread.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace ctor_copy_test
{

static_assert(!hamon::is_copy_constructible_v<hamon::thread>, "");
static_assert(!hamon::is_nothrow_copy_constructible_v<hamon::thread>, "");
static_assert(!hamon::is_trivially_copy_constructible_v<hamon::thread>, "");
static_assert(!hamon::is_implicitly_copy_constructible_v<hamon::thread>, "");

}	// namespace ctor_copy_test

}	// namespace hamon_thread_test
