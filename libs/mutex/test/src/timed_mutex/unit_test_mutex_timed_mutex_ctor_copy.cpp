/**
 *	@file	unit_test_mutex_timed_mutex_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	timed_mutex(const timed_mutex&) = delete;
 */

#include <hamon/mutex/timed_mutex.hpp>
#include <hamon/type_traits.hpp>

static_assert(!hamon::is_copy_constructible_v<hamon::timed_mutex>, "");
