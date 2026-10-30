/**
 *	@file	unit_test_mutex_recursive_timed_mutex_assign_copy.cpp
 *
 *	@brief	コピー代入演算子のテスト
 *
 *	recursive_timed_mutex& operator=(const recursive_timed_mutex&) = delete;
 */

#include <hamon/mutex/recursive_timed_mutex.hpp>
#include <hamon/type_traits.hpp>

static_assert(!hamon::is_copy_assignable_v<hamon::recursive_timed_mutex>, "");
