/**
 *	@file	unit_test_thread_jthread_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	jthread(jthread const&) = delete;
 */

#include <hamon/thread/jthread.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_jthread_test
{

namespace ctor_copy_test
{

static_assert(!hamon::is_copy_constructible_v<hamon::jthread>, "");
static_assert(!hamon::is_nothrow_copy_constructible_v<hamon::jthread>, "");
static_assert(!hamon::is_trivially_copy_constructible_v<hamon::jthread>, "");
static_assert(!hamon::is_implicitly_copy_constructible_v<hamon::jthread>, "");

}	// namespace ctor_copy_test

}	// namespace hamon_jthread_test
