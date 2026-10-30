/**
 *	@file	unit_test_mutex_scoped_lock_typedefs.cpp
 *
 *	@brief
 *
 *	using mutex_type = see below;     // Only if sizeof...(MutexTypes) == 1 is true
 */

#include <hamon/mutex/scoped_lock.hpp>
#include <hamon/mutex/mutex.hpp>
#include <hamon/mutex/recursive_mutex.hpp>
#include <hamon/mutex/timed_mutex.hpp>
#include <hamon/mutex/recursive_timed_mutex.hpp>
#include <hamon/type_traits.hpp>

namespace hamon_scoped_lock_test
{

template <typename T, typename = void>
struct has_mutex_type
	: public hamon::false_type {};

template <typename T>
struct has_mutex_type<T, hamon::void_t<typename T::mutex_type>>
	: public hamon::true_type {};

static_assert(!has_mutex_type<hamon::scoped_lock<>>::value, "");
static_assert( has_mutex_type<hamon::scoped_lock<hamon::mutex>>::value, "");
static_assert( has_mutex_type<hamon::scoped_lock<hamon::recursive_mutex>>::value, "");
static_assert( has_mutex_type<hamon::scoped_lock<hamon::timed_mutex>>::value, "");
static_assert( has_mutex_type<hamon::scoped_lock<hamon::recursive_timed_mutex>>::value, "");
static_assert(!has_mutex_type<hamon::scoped_lock<hamon::mutex, hamon::mutex>>::value, "");
static_assert(!has_mutex_type<hamon::scoped_lock<hamon::timed_mutex, hamon::recursive_timed_mutex>>::value, "");
static_assert(!has_mutex_type<hamon::scoped_lock<hamon::mutex, hamon::recursive_mutex, hamon::timed_mutex>>::value, "");

static_assert(hamon::is_same_v<hamon::scoped_lock<hamon::mutex                >::mutex_type, hamon::mutex>, "");
static_assert(hamon::is_same_v<hamon::scoped_lock<hamon::recursive_mutex      >::mutex_type, hamon::recursive_mutex>, "");
static_assert(hamon::is_same_v<hamon::scoped_lock<hamon::timed_mutex          >::mutex_type, hamon::timed_mutex>, "");
static_assert(hamon::is_same_v<hamon::scoped_lock<hamon::recursive_timed_mutex>::mutex_type, hamon::recursive_timed_mutex>, "");

}	// namespace hamon_scoped_lock_test
