/**
 *	@file	unit_test_flat_map_ctor_move_alloc.cpp
 *
 *	@brief	ムーブとアロケータを引数に取るコンストラクタのテスト
 *
 *	template<class Alloc>
 *	constexpr flat_map(flat_map&&, const Alloc& a);
 */

#include <hamon/flat_map/flat_map.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace ctor_move_alloc_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_map<Key, T, Compare, KeyContainer, MappedContainer>;
	using Alloc = hamon::allocator<char>;

	static_assert( hamon::is_constructible<Map, Map&&, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Map&&, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, Map&&, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Map&&, Alloc const&>::value, "");

	{
		Map v1
		{
			{Key{1}, T{10}},
			{Key{3}, T{20}},
			{Key{2}, T{30}},
		};
		Alloc const alloc;
		Map v2(hamon::move(v1), alloc);
		VERIFY(check_invariant(v2));
		VERIFY(v2.size() == 3);
		VERIFY(v2[Key{1}] == T{10});
		VERIFY(v2[Key{2}] == T{30});
		VERIFY(v2[Key{3}] == T{20});
	}

	return true;
}

#undef VERIFY

template <template <typename...> class TKeyContainer, template <typename...> class TValueContainer>
void test_exceptions()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	using Key = int;
	using T = int;
	using Comp = hamon::less<Key>;
	{
		using KeyContainer = TKeyContainer<Key, ThrowAllocator<Key>>;
		using ValueContainer = TValueContainer<T, ThrowAllocator<T>>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		int throw_after = 1;
		ThrowAllocator<Key> alloc{&throw_after};

		EXPECT_THROW(Map v2(hamon::move(v), alloc), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key, ThrowAllocator<Key>>;
		using ValueContainer = TValueContainer<T, ThrowAllocator<T>>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;

		int throw_after = INT_MAX;
		ThrowAllocator<Key> alloc{&throw_after};

		KeyContainer   a({Key{1}, Key{2}, Key{3}, Key{4}}, alloc);
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		throw_after = 1;

		EXPECT_THROW(Map v2(hamon::move(v), alloc), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMapTest, CtorMoveAllocTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<UseAllocContainer<int>, UseAllocContainer<char>, hamon::less<>>()));

	test_exceptions<hamon::vector, hamon::deque>();
	test_exceptions<hamon::deque, hamon::vector>();
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace ctor_move_alloc_test

}	// namespace hamon_flat_map_test
