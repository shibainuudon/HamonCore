/**
 *	@file	unit_test_type_traits_is_detected.cpp
 *
 *	@brief	is_detected のテスト
 */

#include <hamon/type_traits/is_detected.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <memory>

namespace hamon_type_traits_test
{

namespace is_detected_test
{

template <typename T>
using copy_assignable =
	decltype(hamon::declval<T&>() = hamon::declval<T const&>());

template <typename T>
using has_func =
	decltype(hamon::declval<T>().func());

template <typename T, typename U>
using has_func2 =
	decltype(hamon::declval<T>().template func2<U>(hamon::declval<U>()));

template <typename T>
using has_value_type = typename T::value_type;

struct Copyable
{
	using value_type = int;

	void func(int);

	template <typename T>
	float func2(T);
};

struct NonCopyable
{
	void operator=(NonCopyable const&) = delete;

	void func();
};

static_assert( hamon::is_detected<copy_assignable, int>::value, "");
static_assert(!hamon::is_detected<copy_assignable, std::unique_ptr<int>>::value, "");
static_assert( hamon::is_detected<copy_assignable, std::shared_ptr<int>>::value, "");
static_assert( hamon::is_detected<copy_assignable, hamon::vector<int>>::value, "");
static_assert( hamon::is_detected<copy_assignable, Copyable>::value, "");
static_assert(!hamon::is_detected<copy_assignable, NonCopyable>::value, "");

static_assert(!hamon::is_detected<has_func, int>::value, "");
static_assert(!hamon::is_detected<has_func, hamon::vector<int>>::value, "");
static_assert(!hamon::is_detected<has_func, Copyable>::value, "");
static_assert( hamon::is_detected<has_func, NonCopyable>::value, "");

static_assert(!hamon::is_detected<has_func2, int, int>::value, "");
static_assert(!hamon::is_detected<has_func2, int, float>::value, "");
static_assert( hamon::is_detected<has_func2, Copyable, int>::value, "");
static_assert( hamon::is_detected<has_func2, Copyable, float>::value, "");
static_assert(!hamon::is_detected<has_func2, NonCopyable, int>::value, "");
static_assert(!hamon::is_detected<has_func2, NonCopyable, float>::value, "");

static_assert(!hamon::is_detected<has_value_type, int>::value, "");
static_assert(!hamon::is_detected<has_value_type, std::unique_ptr<int>>::value, "");
static_assert(!hamon::is_detected<has_value_type, std::shared_ptr<int>>::value, "");
static_assert( hamon::is_detected<has_value_type, hamon::vector<int>>::value, "");
static_assert( hamon::is_detected<has_value_type, Copyable>::value, "");
static_assert(!hamon::is_detected<has_value_type, NonCopyable>::value, "");

}	// namespace is_detected_test

}	// namespace hamon_type_traits_test
