/**
 *	@file	unit_test_flat_set_ctor_move_alloc.cpp
 *
 *	@brief	ムーブとアロケータを引数に取るコンストラクタのテスト
 *
 *	template<class Alloc>
 *	constexpr flat_set(flat_set&&, const Alloc& a);
 */

#include <hamon/flat_set/flat_set.hpp>
#include <hamon/functional.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace ctor_move_alloc_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename Compare>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_set<Key, Compare, KeyContainer>;
	using Alloc = hamon::allocator<char>;

	static_assert( hamon::is_constructible<Set, Set&&, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, Set&&, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, Set&&, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Set&&, Alloc const&>::value, "");

	{
		Set v1
		{
			Key{1},
			Key{3},
			Key{2},
		};
		Alloc const alloc;
		Set v2(hamon::move(v1), alloc);
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		VERIFY(v2.size() == 3);
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 1);
		VERIFY(v2.count(Key{2}) == 1);
		VERIFY(v2.count(Key{3}) == 1);
		VERIFY(v2.count(Key{4}) == 0);
	}

	return true;
}

#undef VERIFY

template <template <typename...> class TKeyContainer>
void test_exceptions()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	using Key = int;
	using Comp = hamon::less<Key>;
	{
		using KeyContainer = TKeyContainer<Key, ThrowAllocator<Key>>;
		using Set = hamon::flat_set<Key, Comp, KeyContainer>;

		KeyContainer a{Key{1}, Key{2}, Key{3}, Key{4}};
		Set v(hamon::sorted_unique, hamon::move(a));

		int throw_after = 1;
		ThrowAllocator<Key> alloc{&throw_after};

		EXPECT_THROW(Set v2(hamon::move(v), alloc), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatSetTest, CtorMoveAllocTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::greater<>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<UseAllocContainer<int>, hamon::less<>>()));

	test_exceptions<hamon::vector>();
	test_exceptions<hamon::deque>();
}

}	// namespace ctor_move_alloc_test

}	// namespace hamon_flat_set_test
