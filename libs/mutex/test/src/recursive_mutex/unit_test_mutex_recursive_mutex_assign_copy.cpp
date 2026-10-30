/**
 *	@file	unit_test_mutex_recursive_mutex_assign_copy.cpp
 *
 *	@brief	コピー代入演算子のテスト
 *
 *	recursive_mutex& operator=(const recursive_mutex&) = delete;
 */

#include <hamon/mutex/recursive_mutex.hpp>
#include <hamon/type_traits.hpp>

static_assert(!hamon::is_copy_assignable_v<hamon::recursive_mutex>, "");
