/**
 *	@file	unit_test_scoped_allocator_select_on_container_copy_construction.cpp
 *
 *	@brief	select_on_container_copy_construction のテスト
 */

#include <hamon/scoped_allocator/scoped_allocator_adaptor.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/string.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_scoped_allocator_test
{

namespace select_on_container_copy_construction_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <class T>
using alloc_t = hamon::allocator<T>;

// コンテナの要素(Inner)
using string = hamon::basic_string<
	char,
	hamon::char_traits<char>,
	alloc_t<char>
>;

// コンテナ(Outer)
template <class T>
using vector = hamon::vector<
	T,
	hamon::scoped_allocator_adaptor<alloc_t<T>, alloc_t<typename T::value_type>>
>;

inline HAMON_CXX20_CONSTEXPR bool test()
{
	vector<string>::allocator_type alloc
	{
		alloc_t<string>(), // vector自体のアロケータオブジェクト
		alloc_t<char>()    // vectorの全ての要素に使用するアロケータオブジェクト
	};

	vector<string>::allocator_type for_copy_alloc = alloc.select_on_container_copy_construction();
	(void)for_copy_alloc;

	return true;
}

#undef VERIFY

GTEST_TEST(ScopedAllocatorTest, SelectOnContainerCopyConstructionTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace select_on_container_copy_construction_test

}	// namespace hamon_scoped_allocator_test
