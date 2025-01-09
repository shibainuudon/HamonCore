/**
 *	@file	unit_test_memory_resource_unsynchronized_pool_resource.cpp
 *
 *	@brief	unsynchronized_pool_resource のテスト
 */

#include <hamon/memory_resource/unsynchronized_pool_resource.hpp>
#include <hamon/memory_resource/memory_resource.hpp>
#include <hamon/memory_resource/pool_options.hpp>
#include <hamon/memory_resource/get_default_resource.hpp>
#include <hamon/memory_resource/polymorphic_allocator.hpp>
#include <hamon/memory_resource/monotonic_buffer_resource.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <vector>

GTEST_TEST(MemoryResourceTest, UnsynchronizedPoolResourceTest)
{
	using UPR = hamon::pmr::unsynchronized_pool_resource;

	static_assert( hamon::is_default_constructible<UPR>::value, "");
#if !defined(HAMON_USE_STD_MEMORY_RESOURCE)
	static_assert(!hamon::is_nothrow_default_constructible<UPR>::value, "");
#endif
	static_assert(!hamon::is_trivially_default_constructible<UPR>::value, "");
	static_assert( hamon::is_implicitly_default_constructible<UPR>::value, "");

	static_assert( hamon::is_constructible<UPR, hamon::pmr::memory_resource*>::value, "");
#if !defined(HAMON_USE_STD_MEMORY_RESOURCE)
	static_assert(!hamon::is_nothrow_constructible<UPR, hamon::pmr::memory_resource*>::value, "");
#endif
	static_assert(!hamon::is_implicitly_constructible<UPR, hamon::pmr::memory_resource*>::value, "");

	static_assert( hamon::is_constructible<UPR, hamon::pmr::pool_options const&>::value, "");
#if !defined(HAMON_USE_STD_MEMORY_RESOURCE)
	static_assert(!hamon::is_nothrow_constructible<UPR, hamon::pmr::pool_options const&>::value, "");
#endif
	static_assert(!hamon::is_implicitly_constructible<UPR, hamon::pmr::pool_options const&>::value, "");

	static_assert( hamon::is_constructible<UPR, hamon::pmr::pool_options const&, hamon::pmr::memory_resource*>::value, "");
#if !defined(HAMON_USE_STD_MEMORY_RESOURCE)
	static_assert(!hamon::is_nothrow_constructible<UPR, hamon::pmr::pool_options const&, hamon::pmr::memory_resource*>::value, "");
#endif
	static_assert( hamon::is_implicitly_constructible<UPR, hamon::pmr::pool_options const&, hamon::pmr::memory_resource*>::value, "");

	static_assert(!hamon::is_copy_constructible<UPR>::value, "");
	static_assert(!hamon::is_move_constructible<UPR>::value, "");

	{
		UPR upr;
		EXPECT_TRUE(upr.upstream_resource() == hamon::pmr::get_default_resource());

		hamon::pmr::polymorphic_allocator<int> pa{&upr};
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
		UPR upr(&upstream);
		EXPECT_TRUE(upr.upstream_resource() == &upstream);
		EXPECT_TRUE(upr.upstream_resource() != hamon::pmr::get_default_resource());
		EXPECT_FALSE(upr == upstream);
		EXPECT_TRUE (upr != upstream);
		EXPECT_FALSE(upstream == upr);
		EXPECT_TRUE (upstream != upr);
		EXPECT_TRUE (*upr.upstream_resource() == upstream);
		EXPECT_FALSE(*upr.upstream_resource() != upstream);

		hamon::pmr::polymorphic_allocator<int> pa{&upr};
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

		UPR upr(opt);
		EXPECT_TRUE(upr.upstream_resource() == hamon::pmr::get_default_resource());
		EXPECT_EQ(1024u, upr.options().largest_required_pool_block);
		EXPECT_EQ( 100u, upr.options().max_blocks_per_chunk);

		hamon::pmr::polymorphic_allocator<int> pa{&upr};
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
		UPR upr(opt, &upstream);
		EXPECT_TRUE(upr.upstream_resource() == &upstream);
		EXPECT_TRUE(upr.upstream_resource() != hamon::pmr::get_default_resource());
		EXPECT_EQ(512u, upr.options().largest_required_pool_block);
		EXPECT_EQ(256u, upr.options().max_blocks_per_chunk);

		hamon::pmr::polymorphic_allocator<int> pa{&upr};
		std::vector<int, hamon::pmr::polymorphic_allocator<int>> v{pa};
		for (int i = 0; i < 100; ++i)
		{
			v.push_back(i);
		}
		EXPECT_EQ( 0, v[ 0]);
		EXPECT_EQ(99, v[99]);
	}
}
