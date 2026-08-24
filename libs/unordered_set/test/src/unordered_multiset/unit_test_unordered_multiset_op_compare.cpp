/**
 *	@file	unit_test_unordered_multiset_op_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class Key, class T, class Hash, class Pred, class Alloc>
 *	constexpr bool operator==(
 *		const unordered_multiset<Key, T, Hash, Pred, Alloc>& a,
 *		const unordered_multiset<Key, T, Hash, Pred, Alloc>& b);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace op_compare_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>() == hamon::declval<Set const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>() != hamon::declval<Set const&>()), bool>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>() == hamon::declval<Set const&>()), "");
	static_assert(!noexcept(hamon::declval<Set const&>() != hamon::declval<Set const&>()), "");

	{
		Set v1;
		v1.emplace(Key{10});
		v1.emplace(Key{20});
		v1.emplace(Key{30});
		v1.emplace(Key{30});

		Set v2;
		v2.emplace(Key{30});
		v2.emplace(Key{10});
		v2.emplace(Key{30});
		v2.emplace(Key{20});

		VERIFY((v1 == v2) == true);
		VERIFY((v1 != v2) == false);

		v2.emplace(Key{30});

		VERIFY((v1 == v2) == false);
		VERIFY((v1 != v2) == true);
	}
	{
		Set const v1
		{
			Key{10}, Key{20}, Key{20}, Key{30}, Key{40}, Key{40}, Key{40},
		};

		Set const v2
		{
			Key{10}, Key{20}, Key{20}, Key{30}, Key{40}, Key{40}, Key{40},
		};

		VERIFY((v1 == v2) == true);
		VERIFY((v1 != v2) == false);
	}
	{
		Set const v1
		{
			Key{10}, Key{20}, Key{20}, Key{30}, Key{40}, Key{40}, Key{40},
		};

		Set const v2
		{
			Key{10}, Key{20}, Key{30}, Key{40}, Key{40}, Key{40},
		};

		VERIFY((v1 == v2) == false);
		VERIFY((v1 != v2) == true);
	}
	{
		Set const v1
		{
			Key{10}, Key{20}, Key{20}, Key{30}, Key{40}, Key{40}, Key{40},
		};

		Set const v2
		{
			Key{10}, Key{20}, Key{30}, Key{30}, Key{40}, Key{40}, Key{40},
		};

		VERIFY((v1 == v2) == false);
		VERIFY((v1 != v2) == true);
	}
	{
		Set const v1
		{
			Key{10}, Key{20}, Key{20}, Key{30}, Key{40}, Key{40}, Key{40},
		};

		Set const v2
		{
			Key{10}, Key{20}, Key{20}, Key{30}, Key{30}, Key{40}, Key{40},
		};

		VERIFY((v1 == v2) == false);
		VERIFY((v1 != v2) == true);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, OpCompareTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace op_compare_test

}	// namespace hamon_unordered_multiset_test
