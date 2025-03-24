/**
 *	@file	unit_test_unordered_multimap_ctor_iterator.cpp
 *
 *	@brief	イテレータを引数に取るコンストラクタのテスト
 *
 *	template<class InputIterator>
 *	constexpr unordered_multimap(
 *		InputIterator f, InputIterator l,
 *		size_type n = see below,
 *		const hasher& hf = hasher(),
 *		const key_equal& eql = key_equal(),
 *		const allocator_type& a = allocator_type());
 *
 *	template<class InputIterator>
 *	constexpr unordered_multimap(
 *		InputIterator f, InputIterator l,
 *		size_type n,
 *		const allocator_type& a);
 *
 *	template<class InputIterator>
 *	constexpr unordered_multimap(
 *		InputIterator f, InputIterator l,
 *		size_type n,
 *		const hasher& hf,
 *		const allocator_type& a);
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_unordered_multimap_test
{

namespace ctor_iterator_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T, template <typename> class IteratorWrapper>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test_impl()
{
	using Map = hamon::unordered_multimap<Key, T>;
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
	static_assert(!hamon::is_nothrow_constructible<Map, Iterator, Iterator>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Iterator, Iterator, SizeType>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Iterator, Iterator, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, Iterator, Iterator>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, Iterator, Iterator, SizeType>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, Iterator, Iterator, SizeType, Hasher const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Iterator, Iterator>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Iterator, Iterator, SizeType>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Iterator, Iterator, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");

	ValueType a[] =
	{
		{Key{2}, T{10}},
		{Key{3}, T{20}},
		{Key{1}, T{30}},
		{Key{1}, T{40}},
		{Key{2}, T{50}},
		{Key{3}, T{60}},
	};

	// (f, l)
	{
		Map v(Iterator{a}, Iterator{a + 6});
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 1);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	// (f, l, n)
	{
		Map v(Iterator{a}, Iterator{a + 6}, 2);
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 2);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	// (f, l, n, hf)
	{
		Map v(Iterator{a}, Iterator{a + 6}, 3, Hasher{});
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 3);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	// (f, l, n, hf, eql)
	{
		Map v(Iterator{a}, Iterator{a + 6}, 4, Hasher{}, KeyEqual{});
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 4);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	// (f, l, n, hf, eql, a)
	{
		Allocator alloc;
		Map v(Iterator{a}, Iterator{a + 6}, 5, Hasher{}, KeyEqual{}, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 5);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.get_allocator() == alloc);
	}

#if !(defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && (HAMON_CXX_STANDARD < 14))
	static_assert( hamon::is_constructible<Map, Iterator, Iterator, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Iterator, Iterator, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, Iterator, Iterator, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Iterator, Iterator, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Iterator, Iterator, SizeType, Hasher const&, Allocator const&>::value, "");

	// (f, l, n, a)
	{
		Allocator alloc;
		Map v(Iterator{a}, Iterator{a + 6}, 1, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 1);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.get_allocator() == alloc);
	}
	// (f, l, n, hf, a)
	{
		Allocator alloc;
		Map v(Iterator{a}, Iterator{a + 6}, 11, Hasher{}, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 11);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.get_allocator() == alloc);
	}
#endif

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)	// TODO(LWG 2713)
	static_assert( hamon::is_constructible<Map, Iterator, Iterator, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Iterator, Iterator, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, Iterator, Iterator, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Iterator, Iterator, Allocator const&>::value, "");

	// (f, l, n, a)
	{
		Allocator alloc;
		Map v(Iterator{a}, Iterator{a + 6}, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 1);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.get_allocator() == alloc);
	}
#endif

	ValueType b[] =
	{
		{Key{0}, T{10}}, {Key{10}, T{10}}, {Key{20}, T{10}}, {Key{30}, T{10}}, {Key{40}, T{10}},
		{Key{1}, T{10}}, {Key{11}, T{10}}, {Key{21}, T{10}}, {Key{31}, T{10}}, {Key{41}, T{10}},
		{Key{2}, T{10}}, {Key{12}, T{10}}, {Key{22}, T{10}}, {Key{32}, T{10}}, {Key{42}, T{10}},
		{Key{3}, T{10}}, {Key{13}, T{10}}, {Key{23}, T{10}}, {Key{33}, T{10}}, {Key{43}, T{10}},
		{Key{4}, T{10}}, {Key{14}, T{10}}, {Key{24}, T{10}}, {Key{34}, T{10}}, {Key{44}, T{10}},
		{Key{5}, T{10}}, {Key{15}, T{10}}, {Key{25}, T{10}}, {Key{35}, T{10}}, {Key{45}, T{10}},
		{Key{6}, T{10}}, {Key{16}, T{10}}, {Key{26}, T{10}}, {Key{36}, T{10}}, {Key{46}, T{10}},
		{Key{7}, T{10}}, {Key{17}, T{10}}, {Key{27}, T{10}}, {Key{37}, T{10}}, {Key{47}, T{10}},
		{Key{8}, T{10}}, {Key{18}, T{10}}, {Key{28}, T{10}}, {Key{38}, T{10}}, {Key{48}, T{10}},
		{Key{9}, T{10}}, {Key{19}, T{10}}, {Key{29}, T{10}}, {Key{39}, T{10}}, {Key{49}, T{10}},
	};
	{
		Map v(Iterator{b}, Iterator{b + 50});
		VERIFY(!v.empty());
		VERIFY(v.size() == 50);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 1);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}

	return true;
}

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test()
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

GTEST_TEST(UnorderedMultimapTest, CtorIteratorTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace ctor_iterator_test

}	// namespace hamon_unordered_multimap_test
