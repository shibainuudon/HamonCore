/**
 *	@file	unit_test_multiset_equal_range.cpp
 *
 *	@brief	equal_range のテスト
 *
 *	pair<iterator, iterator>               equal_range(const key_type& x);
 *	pair<const_iterator, const_iterator>   equal_range(const key_type& x) const;
 *	template<class K>
 *	pair<iterator, iterator>             equal_range(const K& x);
 *	template<class K>
 *	pair<const_iterator, const_iterator> equal_range(const K& x) const;
 */

#include <hamon/set/multiset.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multiset_test
{

namespace equal_range_test
{

#if !defined(HAMON_USE_STD_MULTISET)
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// pair<iterator, iterator> equal_range(const key_type& x);
template <typename Key>
MULTISET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::multiset<Key>;
	using Iterator = typename Set::iterator;
#if defined(HAMON_USE_STD_MULTISET)
	using Result = std::pair<Iterator, Iterator>;
#else
	using Result = hamon::pair<Iterator, Iterator>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().equal_range(hamon::declval<Key const&>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().equal_range(hamon::declval<Key const&>())), "");

	Set v;

	VERIFY(v.equal_range(0) == Result{v.end(), v.end()});
	VERIFY(v.equal_range(1) == Result{v.end(), v.end()});
	VERIFY(v.equal_range(2) == Result{v.end(), v.end()});

	v.emplace(Key{1});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 0)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 0), v.end()});
	VERIFY(v.equal_range(2) == Result{v.end(), v.end()});

	v.emplace(Key{1});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 0)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 0), v.end()});
	VERIFY(v.equal_range(2) == Result{v.end(), v.end()});

	v.emplace(Key{2});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 0)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 2), v.end()});

	v.emplace(Key{0});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 3), v.end()});

	v.emplace(Key{2});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 3), v.end()});

	v.emplace(Key{2});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 3), v.end()});

	return true;
}

// pair<const_iterator, const_iterator> equal_range(const key_type& x) const;
template <typename Key>
MULTISET_TEST_CONSTEXPR bool test2()
{
	using Set = hamon::multiset<Key>;
	using ConstIterator = typename Set::const_iterator;
#if defined(HAMON_USE_STD_MULTISET)
	using Result = std::pair<ConstIterator, ConstIterator>;
#else
	using Result = hamon::pair<ConstIterator, ConstIterator>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().equal_range(hamon::declval<Key const&>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>().equal_range(hamon::declval<Key const&>())), "");

	Set const v {Key{1}, Key{1}, Key{1}, Key{3}, Key{3}, Key{4}};

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 0)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 3), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(3) == Result{hamon::next(v.begin(), 3), hamon::next(v.begin(), 5)});
	VERIFY(v.equal_range(4) == Result{hamon::next(v.begin(), 5), v.end()});
	VERIFY(v.equal_range(5) == Result{v.end(), v.end()});

	return true;
}

#if !defined(HAMON_USE_STD_MULTISET) || \
	defined(__cpp_lib_generic_associative_lookup) && (__cpp_lib_generic_associative_lookup >= 201304L)

struct S
{
	int value;

	constexpr explicit S(int v) : value(v) {}

	friend constexpr bool operator<(S const& lhs, S const& rhs)
	{
		return lhs.value < rhs.value;
	}

	friend constexpr bool operator<(S const& lhs, int rhs)
	{
		return lhs.value < rhs;
	}

	friend constexpr bool operator<(int lhs, S const& rhs)
	{
		return lhs < rhs.value;
	}
};

// template<class K> pair<iterator, iterator> equal_range(const K& x);
MULTISET_TEST_CONSTEXPR bool test3()
{
	using Set = hamon::multiset<S, hamon::less<>>;
	using Iterator = typename Set::iterator;
#if defined(HAMON_USE_STD_MULTISET)
	using Result = std::pair<Iterator, Iterator>;
#else
	using Result = hamon::pair<Iterator, Iterator>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().equal_range(hamon::declval<int const&>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().equal_range(hamon::declval<int const&>())), "");

	Set v;

	VERIFY(v.equal_range(0) == Result{v.end(), v.end()});
	VERIFY(v.equal_range(1) == Result{v.end(), v.end()});
	VERIFY(v.equal_range(2) == Result{v.end(), v.end()});

	v.emplace(S{0});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), v.end()});
	VERIFY(v.equal_range(1) == Result{v.end(), v.end()});
	VERIFY(v.equal_range(2) == Result{v.end(), v.end()});

	v.emplace(S{2});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 1), v.end()});

	v.emplace(S{0});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 2), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 2), v.end()});

	v.emplace(S{1});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 2), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 3), v.end()});

	v.emplace(S{1});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 2), hamon::next(v.begin(), 4)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 4), v.end()});

	v.emplace(S{0});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 3), hamon::next(v.begin(), 5)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 5), v.end()});

	return true;
}

// template<class K> pair<const_iterator, const_iterator> equal_range(const K& x) const;
MULTISET_TEST_CONSTEXPR bool test4()
{
	using Set = hamon::multiset<S, hamon::less<>>;
	using ConstIterator = typename Set::const_iterator;
#if defined(HAMON_USE_STD_MULTISET)
	using Result = std::pair<ConstIterator, ConstIterator>;
#else
	using Result = hamon::pair<ConstIterator, ConstIterator>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().equal_range(hamon::declval<int const&>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>().equal_range(hamon::declval<int const&>())), "");

	Set const v {S{0}, S{1}, S{1}, S{4}, S{5}, S{5}, S{5}};

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 3), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(3) == Result{hamon::next(v.begin(), 3), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(4) == Result{hamon::next(v.begin(), 3), hamon::next(v.begin(), 4)});
	VERIFY(v.equal_range(5) == Result{hamon::next(v.begin(), 4), v.end()});
	VERIFY(v.equal_range(6) == Result{v.end(), v.end()});

	return true;
}

#endif

#undef VERIFY

GTEST_TEST(MultisetTest, EqualRangeTest)
{
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<char>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<float>()));

#if !defined(HAMON_USE_STD_MULTISET) || \
	defined(__cpp_lib_generic_associative_lookup) && (__cpp_lib_generic_associative_lookup >= 201304L)
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test3());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test4());
#endif
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace equal_range_test

}	// namespace hamon_multiset_test
