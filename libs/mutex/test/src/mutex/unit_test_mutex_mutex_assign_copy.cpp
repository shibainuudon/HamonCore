/**
 *	@file	unit_test_mutex_mutex_assign_copy.cpp
 *
 *	@brief	コピー代入演算子のテスト
 *
 *	mutex& operator=(const mutex&) = delete;
 */

#include <hamon/mutex/mutex.hpp>
#include <hamon/type_traits.hpp>

static_assert(!hamon::is_copy_assignable_v<hamon::mutex>, "");
