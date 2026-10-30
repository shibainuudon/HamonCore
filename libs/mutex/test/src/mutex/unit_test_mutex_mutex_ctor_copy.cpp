/**
 *	@file	unit_test_mutex_mutex_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	mutex(const mutex&) = delete;
 */

#include <hamon/mutex/mutex.hpp>
#include <hamon/type_traits.hpp>

static_assert(!hamon::is_copy_constructible_v<hamon::mutex>, "");
