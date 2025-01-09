/**
 *	@file	unit_test_memory_resource_synchronized_pool_resource.cpp
 *
 *	@brief	synchronized_pool_resource のテスト
 */

#include <hamon/memory_resource/synchronized_pool_resource.hpp>
#include <hamon/memory_resource/memory_resource.hpp>
#include <hamon/memory_resource/pool_options.hpp>
#include <hamon/memory_resource/get_default_resource.hpp>
#include <hamon/memory_resource/polymorphic_allocator.hpp>
#include <hamon/memory_resource/monotonic_buffer_resource.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <vector>

GTEST_TEST(MemoryResourceTest, SynchronizedPoolResourceTest)
{
	using SPR = hamon::pmr::synchronized_pool_resource;

	static_assert( hamon::is_default_constructible<SPR>::value, "");
#if !defined(HAMON_USE_STD_MEMORY_RESOURCE)
	static_assert(!hamon::is_nothrow_default_constructible<SPR>::value, "");
#endif
	static_assert(!hamon::is_trivially_default_constructible<SPR>::value, "");
	static_assert( hamon::is_implicitly_default_constructible<SPR>::value, "");

	static_assert( hamon::is_constructible<SPR, hamon::pmr::memory_resource*>::value, "");
#if !defined(HAMON_USE_STD_MEMORY_RESOURCE)
	static_assert(!hamon::is_nothrow_constructible<SPR, hamon::pmr::memory_resource*>::value, "");
#endif
	static_assert(!hamon::is_implicitly_constructible<SPR, hamon::pmr::memory_resource*>::value, "");

	static_assert( hamon::is_constructible<SPR, hamon::pmr::pool_options const&>::value, "");
#if !defined(HAMON_USE_STD_MEMORY_RESOURCE)
	static_assert(!hamon::is_nothrow_constructible<SPR, hamon::pmr::pool_options const&>::value, "");
#endif
	static_assert(!hamon::is_implicitly_constructible<SPR, hamon::pmr::pool_options const&>::value, "");

	static_assert( hamon::is_constructible<SPR, hamon::pmr::pool_options const&, hamon::pmr::memory_resource*>::value, "");
#if !defined(HAMON_USE_STD_MEMORY_RESOURCE)
	static_assert(!hamon::is_nothrow_constructible<SPR, hamon::pmr::pool_options const&, hamon::pmr::memory_resource*>::value, "");
#endif
	static_assert( hamon::is_implicitly_constructible<SPR, hamon::pmr::pool_options const&, hamon::pmr::memory_resource*>::value, "");

	static_assert(!hamon::is_copy_constructible<SPR>::value, "");
	static_assert(!hamon::is_move_constructible<SPR>::value, "");

	{
		SPR spr;
		EXPECT_TRUE(spr.upstream_resource() == hamon::pmr::get_default_resource());

		hamon::pmr::polymorphic_allocator<int> pa{&spr};
		std::vector<int, hamon::pmr::polymorphic_allocator<int>> v{pa};
		for (int i = 0; i < 100; ++i)
		{
			v.push_back(i);
		}
		EXPECT_EQ( 0, v[ 0]);
		EXPECT_EQ(99, v[99]);
	}
	{
		hamon::pmr::monotonic_buffer_resource upstream;
		SPR spr(&upstream);
		EXPECT_TRUE(spr.upstream_resource() == &upstream);
		EXPECT_TRUE(spr.upstream_resource() != hamon::pmr::get_default_resource());
		EXPECT_FALSE(spr == upstream);
		EXPECT_TRUE (spr != upstream);
		EXPECT_FALSE(upstream == spr);
		EXPECT_TRUE (upstream != spr);
		EXPECT_TRUE (*spr.upstream_resource() == upstream);
		EXPECT_FALSE(*spr.upstream_resource() != upstream);

		hamon::pmr::polymorphic_allocator<int> pa{&spr};
		std::vector<int, hamon::pmr::polymorphic_allocator<int>> v{pa};
		for (int i = 0; i < 100; ++i)
		{
			v.push_back(i);
		}
		EXPECT_EQ( 0, v[ 0]);
		EXPECT_EQ(99, v[99]);
	}
	{
		hamon::pmr::pool_options opt;
		opt.largest_required_pool_block = 1024u;
		opt.max_blocks_per_chunk        = 100u;

		SPR spr(opt);
		EXPECT_TRUE(spr.upstream_resource() == hamon::pmr::get_default_resource());
		EXPECT_EQ(1024u, spr.options().largest_required_pool_block);
		EXPECT_EQ( 100u, spr.options().max_blocks_per_chunk);

		hamon::pmr::polymorphic_allocator<int> pa{&spr};
		std::vector<int, hamon::pmr::polymorphic_allocator<int>> v{pa};
		for (int i = 0; i < 100; ++i)
		{
			v.push_back(i);
		}
		EXPECT_EQ( 0, v[ 0]);
		EXPECT_EQ(99, v[99]);
	}
	{
		hamon::pmr::pool_options opt;
		opt.largest_required_pool_block = 512u;
		opt.max_blocks_per_chunk        = 256u;

		hamon::pmr::monotonic_buffer_resource upstream;
		SPR spr(opt, &upstream);
		EXPECT_TRUE(spr.upstream_resource() == &upstream);
		EXPECT_TRUE(spr.upstream_resource() != hamon::pmr::get_default_resource());
		EXPECT_EQ(512u, spr.options().largest_required_pool_block);
		EXPECT_EQ(256u, spr.options().max_blocks_per_chunk);

		hamon::pmr::polymorphic_allocator<int> pa{&spr};
		std::vector<int, hamon::pmr::polymorphic_allocator<int>> v{pa};
		for (int i = 0; i < 100; ++i)
		{
			v.push_back(i);
		}
		EXPECT_EQ( 0, v[ 0]);
		EXPECT_EQ(99, v[99]);
	}
}
