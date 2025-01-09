/**
 *	@file	unit_test_memory_resource_monotonic_buffer_resource.cpp
 *
 *	@brief	monotonic_buffer_resource のテスト
 */

#include <hamon/memory_resource/monotonic_buffer_resource.hpp>
#include <hamon/memory_resource/memory_resource.hpp>
#include <hamon/memory_resource/polymorphic_allocator.hpp>
#include <hamon/memory_resource/get_default_resource.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <vector>

GTEST_TEST(MemoryResourceTest, MonotonicBufferResourceTest)
{
	using MBR = hamon::pmr::monotonic_buffer_resource;

	static_assert( hamon::is_default_constructible<MBR>::value, "");
#if !defined(HAMON_USE_STD_MEMORY_RESOURCE)
	static_assert(!hamon::is_nothrow_default_constructible<MBR>::value, "");
#endif
	static_assert(!hamon::is_trivially_default_constructible<MBR>::value, "");
	static_assert( hamon::is_implicitly_default_constructible<MBR>::value, "");

	static_assert( hamon::is_constructible<MBR, hamon::pmr::memory_resource*>::value, "");
#if !defined(HAMON_USE_STD_MEMORY_RESOURCE)
	static_assert(!hamon::is_nothrow_constructible<MBR, hamon::pmr::memory_resource*>::value, "");
#endif
	static_assert(!hamon::is_implicitly_constructible<MBR, hamon::pmr::memory_resource*>::value, "");

	static_assert( hamon::is_constructible<MBR, hamon::size_t>::value, "");
#if !defined(HAMON_USE_STD_MEMORY_RESOURCE)
	static_assert(!hamon::is_nothrow_constructible<MBR, hamon::size_t>::value, "");
#endif
	static_assert(!hamon::is_implicitly_constructible<MBR, hamon::size_t>::value, "");

	static_assert( hamon::is_constructible<MBR, hamon::size_t, hamon::pmr::memory_resource*>::value, "");
#if !defined(HAMON_USE_STD_MEMORY_RESOURCE)
	static_assert(!hamon::is_nothrow_constructible<MBR, hamon::size_t, hamon::pmr::memory_resource*>::value, "");
#endif
	static_assert( hamon::is_implicitly_constructible<MBR, hamon::size_t, hamon::pmr::memory_resource*>::value, "");

	static_assert( hamon::is_constructible<MBR, void*, hamon::size_t>::value, "");
#if !defined(HAMON_USE_STD_MEMORY_RESOURCE)
	static_assert(!hamon::is_nothrow_constructible<MBR, void*, hamon::size_t>::value, "");
#endif
	static_assert( hamon::is_implicitly_constructible<MBR, void*, hamon::size_t>::value, "");

	static_assert( hamon::is_constructible<MBR, void*, hamon::size_t, hamon::pmr::memory_resource*>::value, "");
#if !defined(HAMON_USE_STD_MEMORY_RESOURCE)
	static_assert(!hamon::is_nothrow_constructible<MBR, void*, hamon::size_t, hamon::pmr::memory_resource*>::value, "");
#endif
	static_assert( hamon::is_implicitly_constructible<MBR, void*, hamon::size_t, hamon::pmr::memory_resource*>::value, "");

	static_assert(!hamon::is_copy_constructible<MBR>::value, "");
	static_assert(!hamon::is_move_constructible<MBR>::value, "");

	static_assert(!hamon::is_copy_assignable<MBR>::value, "");
	static_assert(!hamon::is_move_assignable<MBR>::value, "");

	{
		MBR mbr;
		EXPECT_TRUE(mbr.upstream_resource() == hamon::pmr::get_default_resource());

		hamon::pmr::polymorphic_allocator<int> pa{&mbr};
		std::vector<int, hamon::pmr::polymorphic_allocator<int>> v{pa};
		for (int i = 0; i < 2000; ++i)
		{
			v.push_back(i);
		}
		EXPECT_EQ( 0, v[ 0]);
		EXPECT_EQ(99, v[99]);
	}
	{
		MBR upstream;
		MBR mbr(&upstream);
		EXPECT_TRUE(mbr.upstream_resource() == &upstream);
		EXPECT_TRUE(mbr.upstream_resource() != hamon::pmr::get_default_resource());
		EXPECT_FALSE(mbr == upstream);
		EXPECT_TRUE (mbr != upstream);
		EXPECT_FALSE(upstream == mbr);
		EXPECT_TRUE (upstream != mbr);
		EXPECT_TRUE (*mbr.upstream_resource() == upstream);
		EXPECT_FALSE(*mbr.upstream_resource() != upstream);

		hamon::pmr::polymorphic_allocator<int> pa{&mbr};
		std::vector<int, hamon::pmr::polymorphic_allocator<int>> v{pa};
		for (int i = 0; i < 2000; ++i)
		{
			v.push_back(i);
		}
		EXPECT_EQ( 0, v[ 0]);
		EXPECT_EQ(99, v[99]);
	}
	{
		MBR mbr(4);
		EXPECT_TRUE(mbr.upstream_resource() == hamon::pmr::get_default_resource());

		hamon::pmr::polymorphic_allocator<int> pa{&mbr};
		std::vector<int, hamon::pmr::polymorphic_allocator<int>> v{pa};
		for (int i = 0; i < 2000; ++i)
		{
			v.push_back(i);
		}
		EXPECT_EQ( 0, v[ 0]);
		EXPECT_EQ(99, v[99]);
	}
	{
		MBR upstream;
		MBR mbr(8, &upstream);
		EXPECT_TRUE(mbr.upstream_resource() == &upstream);
		EXPECT_TRUE(mbr.upstream_resource() != hamon::pmr::get_default_resource());

		hamon::pmr::polymorphic_allocator<int> pa{&mbr};
		std::vector<int, hamon::pmr::polymorphic_allocator<int>> v{pa};
		for (int i = 0; i < 2000; ++i)
		{
			v.push_back(i);
		}
		EXPECT_EQ( 0, v[ 0]);
		EXPECT_EQ(99, v[99]);
	}
	{
		char buf[64];
		MBR mbr(buf, sizeof(buf));
		EXPECT_TRUE(mbr.upstream_resource() == hamon::pmr::get_default_resource());

		hamon::pmr::polymorphic_allocator<int> pa{&mbr};
		std::vector<int, hamon::pmr::polymorphic_allocator<int>> v{pa};
		for (int i = 0; i < 2000; ++i)
		{
			v.push_back(i);
		}
		EXPECT_EQ( 0, v[ 0]);
		EXPECT_EQ(99, v[99]);
	}
	{
		char buf[128];
		MBR upstream;
		MBR mbr(buf, sizeof(buf), &upstream);
		EXPECT_TRUE(mbr.upstream_resource() == &upstream);
		EXPECT_TRUE(mbr.upstream_resource() != hamon::pmr::get_default_resource());

		hamon::pmr::polymorphic_allocator<int> pa{&mbr};
		std::vector<int, hamon::pmr::polymorphic_allocator<int>> v{pa};
		for (int i = 0; i < 2000; ++i)
		{
			v.push_back(i);
		}
		EXPECT_EQ( 0, v[ 0]);
		EXPECT_EQ(99, v[99]);
	}
}
