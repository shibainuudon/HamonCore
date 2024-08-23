/**
 *	@file	unit_test_memory_pointer_traits.cpp
 *
 *	@brief	pointer_traits のテスト
 */

#include <hamon/memory/pointer_traits.hpp>
#include <hamon/memory/default_delete.hpp>
#include <hamon/memory/unique_ptr.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/cstddef.hpp>
#include <gtest/gtest.h>
#include <memory>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace pointer_traits_test
{

template <typename, typename...>
struct MyPtr
{
};

template <typename T>
struct ConstPtr
{
	using element_type = T const;
	using difference_type = unsigned int;

	template <typename U>
	using rebind = ConstPtr<hamon::remove_cv_t<U>>;

	template <typename E>
	static ConstPtr<T> pointer_to(E& r)
	{
		return {&r};
	}

	element_type* m_p;
};

struct S
{};

template <typename T, typename = void>
struct has_pointer
	: public hamon::false_type
{};

template <typename T>
struct has_pointer<T, hamon::void_t<typename T::pointer>>
	: public hamon::true_type
{};

static_assert(!has_pointer<hamon::pointer_traits<int>>::value, "");
static_assert( has_pointer<hamon::pointer_traits<int*>>::value, "");
static_assert( has_pointer<hamon::pointer_traits<MyPtr<int>>>::value, "");
static_assert( has_pointer<hamon::pointer_traits<ConstPtr<int>>>::value, "");
static_assert(!has_pointer<hamon::pointer_traits<S>>::value, "");

template <typename T, typename = void>
struct has_element_type
	: public hamon::false_type
{};

template <typename T>
struct has_element_type<T, hamon::void_t<typename T::element_type>>
	: public hamon::true_type
{};

static_assert(!has_element_type<hamon::pointer_traits<int>>::value, "");
static_assert( has_element_type<hamon::pointer_traits<int*>>::value, "");
static_assert( has_element_type<hamon::pointer_traits<MyPtr<int>>>::value, "");
static_assert( has_element_type<hamon::pointer_traits<ConstPtr<int>>>::value, "");
static_assert(!has_element_type<hamon::pointer_traits<S>>::value, "");

template <typename T, typename = void>
struct has_difference_type
	: public hamon::false_type
{};

template <typename T>
struct has_difference_type<T, hamon::void_t<typename T::difference_type>>
	: public hamon::true_type
{};

static_assert(!has_difference_type<hamon::pointer_traits<int>>::value, "");
static_assert( has_difference_type<hamon::pointer_traits<int*>>::value, "");
static_assert( has_difference_type<hamon::pointer_traits<MyPtr<int>>>::value, "");
static_assert( has_difference_type<hamon::pointer_traits<ConstPtr<int>>>::value, "");
static_assert(!has_difference_type<hamon::pointer_traits<S>>::value, "");

template <typename T, typename = void>
struct has_rebind
	: public hamon::false_type
{};

template <typename T>
struct has_rebind<T, hamon::void_t<typename T::template rebind<char>>>
	: public hamon::true_type
{};

static_assert(!has_rebind<hamon::pointer_traits<int>>::value, "");
static_assert( has_rebind<hamon::pointer_traits<int*>>::value, "");
static_assert( has_rebind<hamon::pointer_traits<MyPtr<int>>>::value, "");
static_assert( has_rebind<hamon::pointer_traits<ConstPtr<int>>>::value, "");
static_assert(!has_rebind<hamon::pointer_traits<S>>::value, "");

template <typename T, typename Arg, typename = void>
struct has_pointer_to
	: public hamon::false_type
{};

template <typename T, typename Arg>
struct has_pointer_to<T, Arg, hamon::void_t<decltype(T::pointer_to(hamon::declval<Arg>()))>>
	: public hamon::true_type
{};

static_assert(!has_pointer_to<hamon::pointer_traits<int>, int&>::value, "");
static_assert( has_pointer_to<hamon::pointer_traits<int*>, int&>::value, "");
static_assert(!has_pointer_to<hamon::pointer_traits<int*>, char&>::value, "");
static_assert(!has_pointer_to<hamon::pointer_traits<void*>, int&>::value, "");
static_assert(!has_pointer_to<hamon::pointer_traits<MyPtr<int>>, int&>::value, "");
static_assert( has_pointer_to<hamon::pointer_traits<ConstPtr<int>>, int&>::value, "");
static_assert( has_pointer_to<hamon::pointer_traits<ConstPtr<int>>, char&>::value, "");
static_assert(!has_pointer_to<hamon::pointer_traits<ConstPtr<void>>, int&>::value, "");
static_assert(!has_pointer_to<hamon::pointer_traits<S>, int&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool pointer_to_test()
{
	{
		int value = 3;
		int* p = hamon::pointer_traits<int*>::pointer_to(value);
		VERIFY(*p == 3);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, PointerTraitsTest)
{
	// pointer
	static_assert(hamon::is_same<hamon::pointer_traits<int*>::pointer, int*>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<const float*>::pointer, const float*>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<void*>::pointer, void*>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<std::shared_ptr<int>>::pointer, std::shared_ptr<int>>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<std::shared_ptr<void>>::pointer, std::shared_ptr<void>>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<hamon::unique_ptr<char>>::pointer, hamon::unique_ptr<char>>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<hamon::unique_ptr<void>>::pointer, hamon::unique_ptr<void>>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<ConstPtr<char>>::pointer, ConstPtr<char>>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<ConstPtr<void>>::pointer, ConstPtr<void>>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<MyPtr<char>>::pointer, MyPtr<char>>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<MyPtr<void>>::pointer, MyPtr<void>>::value, "");

	// element_type
	static_assert(hamon::is_same<hamon::pointer_traits<int*>::element_type, int>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<const float*>::element_type, const float>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<void*>::element_type, void>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<std::shared_ptr<int>>::element_type, int>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<std::shared_ptr<void>>::element_type, void>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<hamon::unique_ptr<char>>::element_type, char>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<hamon::unique_ptr<void>>::element_type, void>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<ConstPtr<char>>::element_type, char const>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<ConstPtr<void>>::element_type, void const>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<MyPtr<char>>::element_type, char>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<MyPtr<void>>::element_type, void>::value, "");

	// difference_type
	static_assert(hamon::is_same<hamon::pointer_traits<int*>::difference_type, hamon::ptrdiff_t>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<const float*>::difference_type, hamon::ptrdiff_t>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<void*>::difference_type, hamon::ptrdiff_t>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<std::shared_ptr<int>>::difference_type, hamon::ptrdiff_t>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<std::shared_ptr<void>>::difference_type, hamon::ptrdiff_t>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<hamon::unique_ptr<char>>::difference_type, hamon::ptrdiff_t>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<hamon::unique_ptr<void>>::difference_type, hamon::ptrdiff_t>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<ConstPtr<char>>::difference_type, unsigned int>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<ConstPtr<void>>::difference_type, unsigned int>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<MyPtr<char>>::difference_type, hamon::ptrdiff_t>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<MyPtr<void>>::difference_type, hamon::ptrdiff_t>::value, "");

	// rebind
	static_assert(hamon::is_same<hamon::pointer_traits<int*>::template rebind<const char>, const char*>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<const float*>::template rebind<void>, void*>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<void*>::template rebind<int>, int*>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<std::shared_ptr<int>>::template rebind<float>, std::shared_ptr<float>>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<std::shared_ptr<void>>::template rebind<int>, std::shared_ptr<int>>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<hamon::unique_ptr<int>>::template rebind<float>, hamon::unique_ptr<float, hamon::default_delete<int>>>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<hamon::unique_ptr<void>>::template rebind<float>, hamon::unique_ptr<float, hamon::default_delete<void>>>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<ConstPtr<int>>::template rebind<const char>, ConstPtr<char>>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<ConstPtr<void>>::template rebind<int>, ConstPtr<int>>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<MyPtr<int>>::template rebind<const char>, MyPtr<const char>>::value, "");
	static_assert(hamon::is_same<hamon::pointer_traits<MyPtr<void>>::template rebind<int>, MyPtr<int>>::value, "");

	// pointer_to
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(pointer_to_test());
	{
		int value = 4;
		auto p = hamon::pointer_traits<ConstPtr<int>>::pointer_to(value);
		EXPECT_TRUE(*p.m_p == 4);
	}
}

}	// namespace pointer_traits_test

}	// namespace hamon_memory_test
