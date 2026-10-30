/**
 *	@file	unit_test_mutex_recursive_mutex_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	recursive_mutex(const recursive_mutex&) = delete;
 */

#include <hamon/mutex/recursive_mutex.hpp>
#include <hamon/type_traits.hpp>

static_assert(!hamon::is_copy_constructible_v<hamon::recursive_mutex>, "");
