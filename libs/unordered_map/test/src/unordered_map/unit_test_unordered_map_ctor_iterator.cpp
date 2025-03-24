/**
 *	@file	unit_test_unordered_map_ctor_iterator.cpp
 *
 *	@brief	イテレータを引数に取るコンストラクタのテスト
 *
 *	template<class InputIterator>
 *	constexpr unordered_map(
 *		InputIterator f, InputIterator l,
 *		size_type n = see below,
 *		const hasher& hf = hasher(),
 *		const key_equal& eql = key_equal(),
 *		const allocator_type& a = allocator_type());
 *
 *	template<class InputIterator>
 *	constexpr unordered_map(
 *		InputIterator f, InputIterator l,
 *		size_type n,
 *		const allocator_type& a);
 *
 *	template<class InputIterator>
 *	constexpr unordered_map(
 *		InputIterator f, InputIterator l,
 *		size_type n,
 *		const hasher& hf,
 *		const allocator_type& a);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_unordered_map_test
{

namespace ctor_iterator_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MAP)
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T, template <typename> class IteratorWrapper>
UNORDERED_MAP_TEST_CONSTEXPR bool test_impl()
{
	using Map = hamon::unordered_map<Key, T>;
	using SizeType  = typename Map::size_type;
	using Hasher    = typename Map::hasher;
	using KeyEqual  = typename Map::key_equal;
	using Allocator = typename Map::allocator_type;
	using ValueType = typename Map::value_type;
	using Iterator = IteratorWrapper<ValueType>;

	static_assert( hamon::is_constructible<Map, Iterator, Iterator>::value, "");
	static_assert( hamon::is_constructible<Map, Iterator, Iterator, SizeType>::value, "");
	static_assert( hamon::is_constructible<Map, Iterator, Iterator, SizeType, Hasher const&>::value, "");
	static_assert( hamon::is_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert( hamon::is_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert( hamon::is_constructible<Map, Iterator, Iterator, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Iterator, Iterator>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Iterator, Iterator, SizeType>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Iterator, Iterator, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Iterator, Iterator, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, Iterator, Iterator>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, Iterator, Iterator, SizeType>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, Iterator, Iterator, SizeType, Hasher const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, Iterator, Iterator, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Iterator, Iterator>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Iterator, Iterator, SizeType>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Iterator, Iterator, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Iterator, Iterator, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, Allocator const&>::value, "");

#if 0
	ValueType a[] =
	{
		{Key{2}, T{10}},
		{Key{3}, T{20}},
		{Key{1}, T{30}},
		{Key{1}, T{40}},
		{Key{2}, T{50}},
		{Key{3}, T{60}},
	};

	{
		Map v(Iterator{a}, Iterator{a + 6});
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.max_load_factor() == 1.0);
	}
	{
		Map v(Iterator{a}, Iterator{a + 6}, 2);
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 2);
		VERIFY(v.max_load_factor() == 1.0);
	}
	{
		Map v(Iterator{a}, Iterator{a + 6}, 3, Hasher{});
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 3);
		VERIFY(v.max_load_factor() == 1.0);
	}
	{
		Map v(Iterator{a}, Iterator{a + 6}, 4, Hasher{}, KeyEqual{});
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 4);
		VERIFY(v.max_load_factor() == 1.0);
	}
	{
		Allocator alloc;
		Map v(Iterator{a}, Iterator{a + 6}, 5, Hasher{}, KeyEqual{}, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 5);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.get_allocator() == alloc);
	}
	{
		Allocator alloc;
		Map v(Iterator{a}, Iterator{a + 6}, 1, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 1);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.get_allocator() == alloc);
	}
	{
		Allocator alloc;
		Map v(Iterator{a}, Iterator{a + 6}, 11, Hasher{}, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 11);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.get_allocator() == alloc);
	}
#endif

	return true;
}

template <typename Key, typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test()
{
	return
		test_impl<Key, T, cpp17_input_iterator_wrapper>() &&
		//test_impl<Key, T, input_iterator_wrapper>() &&
		test_impl<Key, T, forward_iterator_wrapper>() &&
		test_impl<Key, T, bidirectional_iterator_wrapper>() &&
		test_impl<Key, T, random_access_iterator_wrapper>() &&
		test_impl<Key, T, contiguous_iterator_wrapper>();
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, CtorIteratorTest)
{
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace ctor_iterator_test

}	// namespace hamon_unordered_map_test
