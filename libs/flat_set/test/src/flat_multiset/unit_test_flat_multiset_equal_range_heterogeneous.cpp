/**
 *	@file	unit_test_flat_multiset_equal_range_heterogeneous.cpp
 *
 *	@brief	equal_range のテスト
 *
 *	template<class K>
 *	constexpr pair<iterator, iterator> equal_range(const K& x);
 *
 *	template<class K>
 *	constexpr pair<const_iterator, const_iterator> equal_range(const K& x) const;
 */

#include <hamon/flat_set/flat_multiset.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace equal_range_heterogeneous_test
{

#if !defined(HAMON_USE_STD_FLAT_SET)
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Set, typename K, typename = void>
struct is_equal_range_invocable
	: public hamon::false_type {};

template <typename Set, typename K>
struct is_equal_range_invocable<Set, K, hamon::void_t<decltype(hamon::declval<Set>().equal_range(hamon::declval<K>()))>>
	: public hamon::true_type {};

template <typename KeyContainer>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set1 = hamon::flat_multiset<Key, hamon::less<>, KeyContainer>;
	using Set2 = hamon::flat_multiset<Key, hamon::less<Key>, KeyContainer>;
	using Set3 = hamon::flat_multiset<Key, hamon::greater<>, KeyContainer>;
	using Set4 = hamon::flat_multiset<Key, hamon::greater<Key>, KeyContainer>;

	static_assert( is_equal_range_invocable<Set1&, int>::value, "");
	static_assert(!is_equal_range_invocable<Set2&, int>::value, "");
	static_assert( is_equal_range_invocable<Set3&, int>::value, "");
	static_assert(!is_equal_range_invocable<Set4&, int>::value, "");

	static_assert( is_equal_range_invocable<Set1 const&, int>::value, "");
	static_assert(!is_equal_range_invocable<Set2 const&, int>::value, "");
	static_assert( is_equal_range_invocable<Set3 const&, int>::value, "");
	static_assert(!is_equal_range_invocable<Set4 const&, int>::value, "");

	{
		using Set = Set1;
		using Iterator = typename Set::iterator;
		using ConstIterator = typename Set::const_iterator;

#if defined(HAMON_USE_STD_FLAT_SET)
		using Result = std::pair<Iterator, Iterator>;
		using ConstResult = std::pair<ConstIterator, ConstIterator>;
#else
		using Result = hamon::pair<Iterator, Iterator>;
		using ConstResult = hamon::pair<ConstIterator, ConstIterator>;
#endif
		static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().equal_range(hamon::declval<int const&>())), ConstResult>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Set&>().equal_range(hamon::declval<int const&>())), Result>::value, "");
		static_assert(!noexcept(hamon::declval<Set const&>().equal_range(hamon::declval<int const&>())), "");
		static_assert(!noexcept(hamon::declval<Set&>().equal_range(hamon::declval<int const&>())), "");

		Set v
		{
			Key{1},
			Key{2},
			Key{1},
			Key{4},
			Key{1},
		};

		VERIFY(v.equal_range(0) == Result{v.begin() + 0, v.begin() + 0});
		VERIFY(v.equal_range(1) == Result{v.begin() + 0, v.begin() + 3});
		VERIFY(v.equal_range(2) == Result{v.begin() + 3, v.begin() + 4});
		VERIFY(v.equal_range(3) == Result{v.begin() + 4, v.begin() + 4});
		VERIFY(v.equal_range(4) == Result{v.begin() + 4, v.end()});
		VERIFY(v.equal_range(5) == Result{v.end(), v.end()});

		auto const& cv = v;
		VERIFY(cv.equal_range(0) == ConstResult{cv.begin() + 0, cv.begin() + 0});
		VERIFY(cv.equal_range(1) == ConstResult{cv.begin() + 0, cv.begin() + 3});
		VERIFY(cv.equal_range(2) == ConstResult{cv.begin() + 3, cv.begin() + 4});
		VERIFY(cv.equal_range(3) == ConstResult{cv.begin() + 4, cv.begin() + 4});
		VERIFY(cv.equal_range(4) == ConstResult{cv.begin() + 4, cv.end()});
		VERIFY(cv.equal_range(5) == ConstResult{cv.end(), cv.end()});
	}
	{
		using Set = Set3;
		using Iterator = typename Set::iterator;
		using ConstIterator = typename Set::const_iterator;

#if defined(HAMON_USE_STD_FLAT_SET)
		using Result = std::pair<Iterator, Iterator>;
		using ConstResult = std::pair<ConstIterator, ConstIterator>;
#else
		using Result = hamon::pair<Iterator, Iterator>;
		using ConstResult = hamon::pair<ConstIterator, ConstIterator>;
#endif
		static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().equal_range(hamon::declval<int const&>())), ConstResult>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Set&>().equal_range(hamon::declval<int const&>())), Result>::value, "");
		static_assert(!noexcept(hamon::declval<Set const&>().equal_range(hamon::declval<int const&>())), "");
		static_assert(!noexcept(hamon::declval<Set&>().equal_range(hamon::declval<int const&>())), "");

		Set v
		{
			Key{2},
			Key{2},
			Key{1},
			Key{2},
			Key{4},
		};

		VERIFY(v.equal_range(0) == Result{v.end(), v.end()});
		VERIFY(v.equal_range(1) == Result{v.begin() + 4, v.end()});
		VERIFY(v.equal_range(2) == Result{v.begin() + 1, v.begin() + 4});
		VERIFY(v.equal_range(3) == Result{v.begin() + 1, v.begin() + 1});
		VERIFY(v.equal_range(4) == Result{v.begin() + 0, v.begin() + 1});
		VERIFY(v.equal_range(5) == Result{v.begin() + 0, v.begin() + 0});

		auto const& cv = v;
		VERIFY(cv.equal_range(0) == ConstResult{cv.end(), cv.end()});
		VERIFY(cv.equal_range(1) == ConstResult{cv.begin() + 4, cv.end()});
		VERIFY(cv.equal_range(2) == ConstResult{cv.begin() + 1, cv.begin() + 4});
		VERIFY(cv.equal_range(3) == ConstResult{cv.begin() + 1, cv.begin() + 1});
		VERIFY(cv.equal_range(4) == ConstResult{cv.begin() + 0, cv.begin() + 1});
		VERIFY(cv.equal_range(5) == ConstResult{cv.begin() + 0, cv.begin() + 0});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultisetTest, EqualRangeHeterogeneousTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<TransparentKey>>()));
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace equal_range_heterogeneous_test

}	// namespace hamon_flat_multiset_test
