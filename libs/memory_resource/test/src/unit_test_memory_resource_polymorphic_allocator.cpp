/**
 *	@file	unit_test_memory_resource_polymorphic_allocator.cpp
 *
 *	@brief	polymorphic_allocator のテスト
 */

#include <hamon/memory_resource/polymorphic_allocator.hpp>
#include <hamon/memory_resource/memory_resource.hpp>
#include <hamon/memory_resource/monotonic_buffer_resource.hpp>
#include <hamon/memory_resource/get_default_resource.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/limits.hpp>
#include <hamon/new.hpp>
#include <hamon/pair.hpp>
#include <hamon/string.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4996)	// polymorphic_allocator<>::destroy() is deprecated in C++17
HAMON_WARNING_DISABLE_CLANG("-Wdeprecated-declarations")
HAMON_WARNING_DISABLE_GCC("-Wdeprecated-declarations")

GTEST_TEST(MemoryResourceTest, PolymorphicAllocatorTest)
{
	{
		using PA = hamon::pmr::polymorphic_allocator<>;
		static_assert(hamon::is_default_constructible<PA>::value, "");
		static_assert(hamon::is_copy_constructible<PA>::value, "");
		static_assert(hamon::is_move_constructible<PA>::value, "");
		static_assert(hamon::is_constructible<PA, hamon::pmr::memory_resource*>::value, "");
		static_assert(hamon::is_constructible<PA, hamon::pmr::polymorphic_allocator<float> const&>::value, "");

		static_assert(!hamon::is_copy_assignable<PA>::value, "");
		static_assert(!hamon::is_move_assignable<PA>::value, "");
	}
	{
		hamon::pmr::polymorphic_allocator<int> alloc{};
		EXPECT_TRUE(alloc.resource() == hamon::pmr::get_default_resource());

		  //メモリの確保
		int* arr = alloc.allocate(4);

		//要素を構築
		for (int i = 0; i < 4; ++i)
		{
			alloc.construct(arr + i, i);
		}

		EXPECT_EQ(0, arr[0]);
		EXPECT_EQ(1, arr[1]);
		EXPECT_EQ(2, arr[2]);
		EXPECT_EQ(3, arr[3]);

		//要素を破棄
		for (int i = 0; i < 4; ++i)
		{
			alloc.destroy(arr + i);
		}

		//メモリの解放
		alloc.deallocate(arr, 4);
	}

#if defined(HAMON_USE_STD_MEMORY_RESOURCE)
	namespace ns = std;
#else
	namespace ns = hamon;
#endif

	using pmr_string = hamon::basic_string<char, hamon::char_traits<char>, hamon::pmr::polymorphic_allocator<char>>;
	{
		//intとpolymorphic_allocatorを用いるstringのpair
		using pair = ns::pair<int, pmr_string>;

		//memory_resourceとしてmonotonic_buffer_resourceを使用
		hamon::pmr::monotonic_buffer_resource mr{};
		hamon::pmr::polymorphic_allocator<pair> alloc{&mr};
		EXPECT_TRUE(alloc.resource() == &mr);

		//(2)
		{
			pair* p = alloc.allocate(1);

			alloc.construct(p,
				ns::piecewise_construct,
				ns::make_tuple(128),         //intを128で初期化
				ns::make_tuple("string", 3u) //string("string", 3)で初期化（最初の3文字を保持する）
			);

			EXPECT_EQ(128, p->first);
			EXPECT_EQ("str", p->second);
			//アロケータが伝播している
			EXPECT_TRUE(p->second.get_allocator() == alloc);
		}

		//(3)
		{
			pair* p = alloc.allocate(1);

			alloc.construct(p);  //両要素をデフォルト構築

			EXPECT_EQ(0, p->first);
			EXPECT_EQ("", p->second);
			//アロケータが伝播している
			EXPECT_TRUE(p->second.get_allocator() == alloc);
		}

		//(4)
		{
			pair* p = alloc.allocate(1);

			alloc.construct(p, 128, "string");  //両要素をこれらの値からムーブ構築

			EXPECT_EQ(128, p->first);
			EXPECT_EQ("string", p->second);
			//アロケータが伝播している
			EXPECT_TRUE(p->second.get_allocator() == alloc);
		}

		//(5)
		{
			pair* p = alloc.allocate(1);

			const auto v = ns::make_pair(128, "copy");
			alloc.construct(p, v);  //両要素を変換可能なpairからコピー構築

			EXPECT_EQ(128, p->first);
			EXPECT_EQ("copy", p->second);
			//アロケータが伝播している
			EXPECT_TRUE(p->second.get_allocator() == alloc);
		}

		//(6)
		{
			pair* p = alloc.allocate(1);

			alloc.construct(p, ns::make_pair(128, "move"));  //両要素を変換可能なpairからムーブ構築

			EXPECT_EQ(128, p->first);
			EXPECT_EQ("move", p->second);
			//アロケータが伝播している
			EXPECT_TRUE(p->second.get_allocator() == alloc);
		}
	}
	{
		// ネストした  pair  の例
		using pair = ns::pair<ns::pair<int, pmr_string>, pmr_string>;

		hamon::pmr::monotonic_buffer_resource mr{};
		hamon::pmr::polymorphic_allocator<pair> alloc{&mr};

		pair* p = alloc.allocate(1);

		alloc.construct(p);

		EXPECT_TRUE(p->first.second.get_allocator() == alloc);
		EXPECT_TRUE(p->second.get_allocator() == alloc);
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::pmr::polymorphic_allocator<hamon::uint32_t> alloc;
		EXPECT_THROW((void)alloc.allocate(hamon::numeric_limits<hamon::size_t>::max()), hamon::bad_array_new_length);
	}
	{
		hamon::pmr::polymorphic_allocator<> alloc;
		EXPECT_THROW((void)alloc.allocate_object<int>(hamon::numeric_limits<hamon::size_t>::max()), hamon::bad_array_new_length);
	}
#endif
	{
		hamon::pmr::monotonic_buffer_resource mr{};
		hamon::pmr::polymorphic_allocator<> alloc{&mr};

		int* p = alloc.new_object<int>(20);
		EXPECT_EQ(20, *p);
		alloc.delete_object(p);

		std::string* s = alloc.new_object<std::string>(10u, 'c');
		EXPECT_EQ("cccccccccc", *s);
		alloc.delete_object(s);
	}
	{
		hamon::pmr::monotonic_buffer_resource mr{};
		hamon::pmr::polymorphic_allocator<>    alloc1{&mr};
		hamon::pmr::polymorphic_allocator<>    alloc2{&mr};
		hamon::pmr::polymorphic_allocator<int> alloc3{&mr};
		hamon::pmr::polymorphic_allocator<>    alloc4;
		hamon::pmr::polymorphic_allocator<int> alloc5;

		EXPECT_TRUE (alloc1 == alloc2);
		EXPECT_TRUE (alloc1 == alloc3);
		EXPECT_FALSE(alloc1 == alloc4);
		EXPECT_FALSE(alloc1 == alloc5);

		EXPECT_FALSE(alloc1 != alloc2);
		EXPECT_FALSE(alloc1 != alloc3);
		EXPECT_TRUE (alloc1 != alloc4);
		EXPECT_TRUE (alloc1 != alloc5);
	}
	{
		hamon::pmr::monotonic_buffer_resource mr{};
		hamon::pmr::polymorphic_allocator<> alloc1{&mr};
		hamon::pmr::polymorphic_allocator<> alloc2 = alloc1.select_on_container_copy_construction();
		EXPECT_FALSE(alloc1 == alloc2);
	}
}

HAMON_WARNING_POP()
