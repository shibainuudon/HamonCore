/**
 *	@file	unit_test_memory_resource_memory_resource.cpp
 *
 *	@brief	memory_resource のテスト
 */

#include <hamon/memory_resource/memory_resource.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_abstract.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

GTEST_TEST(MemoryResourceTest, MemoryResourceTest)
{
	using MR = hamon::pmr::memory_resource;

	static_assert(hamon::is_abstract<MR>::value, "");

	static_assert(hamon::is_same<
		decltype(hamon::declval<MR&>().allocate(hamon::declval<hamon::size_t>())),
		void*
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<MR&>().allocate(hamon::declval<hamon::size_t>(), hamon::declval<hamon::size_t>())),
		void*
	>::value, "");

	static_assert(hamon::is_same<
		decltype(hamon::declval<MR&>().deallocate(hamon::declval<void*>(), hamon::declval<hamon::size_t>())),
		void
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<MR&>().deallocate(hamon::declval<void*>(), hamon::declval<hamon::size_t>(), hamon::declval<hamon::size_t>())),
		void
	>::value, "");

	static_assert(hamon::is_same<
		decltype(hamon::declval<MR const&>().is_equal(hamon::declval<MR const&>())),
		bool
	>::value, "");

	static_assert(hamon::is_same<
		decltype(hamon::declval<MR const&>() == hamon::declval<MR const&>()),
		bool
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<MR const&>() != hamon::declval<MR const&>()),
		bool
	>::value, "");
}
