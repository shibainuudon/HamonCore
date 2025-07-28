/**
 *	@file	unit_test_flat_multiset_lower_bound_heterogeneous.cpp
 *
 *	@brief	lower_bound のテスト
 *
 *	template<class K> constexpr iterator lower_bound(const K& x);
 *	template<class K> constexpr const_iterator lower_bound(const K& x) const;
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
#include <sstream>
#include "constexpr_test.hpp"
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace lower_bound_heterogeneous_test
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
struct is_lower_bound_invocable
	: public hamon::false_type {};

template <typename Set, typename K>
struct is_lower_bound_invocable<Set, K, hamon::void_t<decltype(hamon::declval<Set>().lower_bound(hamon::declval<K>()))>>
	: public hamon::true_type {};

template <typename KeyContainer>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set1 = hamon::flat_multiset<Key, hamon::less<>, KeyContainer>;
	using Set2 = hamon::flat_multiset<Key, hamon::less<Key>, KeyContainer>;
	using Set3 = hamon::flat_multiset<Key, hamon::greater<>, KeyContainer>;
	using Set4 = hamon::flat_multiset<Key, hamon::greater<Key>, KeyContainer>;

	static_assert( is_lower_bound_invocable<Set1&, int>::value, "");
	static_assert(!is_lower_bound_invocable<Set2&, int>::value, "");
	static_assert( is_lower_bound_invocable<Set3&, int>::value, "");
	static_assert(!is_lower_bound_invocable<Set4&, int>::value, "");

	static_assert( is_lower_bound_invocable<Set1 const&, int>::value, "");
	static_assert(!is_lower_bound_invocable<Set2 const&, int>::value, "");
	static_assert( is_lower_bound_invocable<Set3 const&, int>::value, "");
	static_assert(!is_lower_bound_invocable<Set4 const&, int>::value, "");

	static_assert(hamon::is_same<decltype(hamon::declval<Set1 const&>().lower_bound(hamon::declval<int const&>())), typename Set1::const_iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set1&>().lower_bound(hamon::declval<int const&>())), typename Set1::iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set1 const&>().lower_bound(hamon::declval<int const&>())), "");
	static_assert(!noexcept(hamon::declval<Set1&>().lower_bound(hamon::declval<int const&>())), "");

	{
		Set1 v
		{
			Key{5},
			Key{1},
			Key{5},
			Key{3},
			Key{3},
			Key{5},
		};
		// 1, 3, 3, 5, 5, 5

		VERIFY(v.lower_bound(0) == (v.begin() + 0));
		VERIFY(v.lower_bound(1) == (v.begin() + 0));
		VERIFY(v.lower_bound(2) == (v.begin() + 1));
		VERIFY(v.lower_bound(3) == (v.begin() + 1));
		VERIFY(v.lower_bound(4) == (v.begin() + 3));
		VERIFY(v.lower_bound(5) == (v.begin() + 3));
		VERIFY(v.lower_bound(6) == v.end());

		auto const& cv = v;
		VERIFY(cv.lower_bound(0) == (cv.begin() + 0));
		VERIFY(cv.lower_bound(1) == (cv.begin() + 0));
		VERIFY(cv.lower_bound(2) == (cv.begin() + 1));
		VERIFY(cv.lower_bound(3) == (cv.begin() + 1));
		VERIFY(cv.lower_bound(4) == (cv.begin() + 3));
		VERIFY(cv.lower_bound(5) == (cv.begin() + 3));
		VERIFY(cv.lower_bound(6) == cv.end());
	}
	{
		Set3 v
		{
			Key{5},
			Key{1},
			Key{5},
			Key{3},
			Key{3},
			Key{5},
		};
		// 5, 5, 5, 3, 3, 1

		VERIFY(v.lower_bound(0) == v.end());
		VERIFY(v.lower_bound(1) == (v.begin() + 5));
		VERIFY(v.lower_bound(2) == (v.begin() + 5));
		VERIFY(v.lower_bound(3) == (v.begin() + 3));
		VERIFY(v.lower_bound(4) == (v.begin() + 3));
		VERIFY(v.lower_bound(5) == (v.begin() + 0));
		VERIFY(v.lower_bound(6) == (v.begin() + 0));

		auto const& cv = v;
		VERIFY(cv.lower_bound(0) == cv.end());
		VERIFY(cv.lower_bound(1) == (cv.begin() + 5));
		VERIFY(cv.lower_bound(2) == (cv.begin() + 5));
		VERIFY(cv.lower_bound(3) == (cv.begin() + 3));
		VERIFY(cv.lower_bound(4) == (cv.begin() + 3));
		VERIFY(cv.lower_bound(5) == (cv.begin() + 0));
		VERIFY(cv.lower_bound(6) == (cv.begin() + 0));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultisetTest, LowerBoundHeterogeneousTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<TransparentKey>>()));

	{
		hamon::flat_multiset<hamon::string, hamon::less<>> fs = {
			"Alice", "Bob", "Carol", "David"
		};

		// lessのvoidに対する特殊化を使用することで、
		// 文字列リテラルをlower_bound()関数の引数として渡した際に、
		// string型の一時オブジェクトが生成されない。
		decltype(fs)::iterator it = fs.lower_bound((const char*)"Bob");
		decltype(fs)::iterator last = fs.upper_bound((const char*)"David");

		std::stringstream ss;
		while (it != last)
		{
			ss << *it << ", ";
			++it;
		}
		EXPECT_EQ("Bob, Carol, David, ", ss.str());
	}
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace lower_bound_heterogeneous_test

}	// namespace hamon_flat_multiset_test
