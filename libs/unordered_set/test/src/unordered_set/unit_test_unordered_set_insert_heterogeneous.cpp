/**
 *	@file	unit_test_unordered_set_insert_heterogeneous.cpp
 *
 *	@brief	insert のテスト
 *
 *	template<class K> constexpr pair<iterator, bool> insert(K&& obj);
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include <utility>
#include "constexpr_test.hpp"
#include "unordered_set_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_SET) || \
	(defined(__cpp_lib_associative_heterogeneous_insertion) && (__cpp_lib_associative_heterogeneous_insertion >= 202306L))

namespace hamon_unordered_set_test
{

namespace insert_heterogeneous_test
{

#if !defined(HAMON_USE_STD_UNORDERED_SET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Set, typename K, typename = void>
struct is_insert_invocable
	: public hamon::false_type {};

template <typename Set, typename K>
struct is_insert_invocable<Set, K, hamon::void_t<decltype(hamon::declval<Set>().insert(hamon::declval<K>()))>>
	: public hamon::true_type {};

UNORDERED_SET_TEST_CONSTEXPR bool test()
{
	using Key = TransparentKey;
	using Set1 = hamon::unordered_set<Key>;
	using Set2 = hamon::unordered_set<Key, TransparentHash>;
	using Set3 = hamon::unordered_set<Key, hamon::hash<Key>, hamon::equal_to<>>;
	using Set4 = hamon::unordered_set<Key, TransparentHash, hamon::equal_to<>>;

	static_assert(!is_insert_invocable<Set1&, int>::value, "");
	static_assert(!is_insert_invocable<Set2&, int>::value, "");
	static_assert(!is_insert_invocable<Set3&, int>::value, "");
	static_assert( is_insert_invocable<Set4&, int>::value, "");

	static_assert(!is_insert_invocable<Set1 const&, int>::value, "");
	static_assert(!is_insert_invocable<Set2 const&, int>::value, "");
	static_assert(!is_insert_invocable<Set3 const&, int>::value, "");
	static_assert(!is_insert_invocable<Set4 const&, int>::value, "");

	using Set = Set4;
	using Iterator = typename Set::iterator;
#if defined(HAMON_USE_STD_UNORDERED_SET)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().insert(hamon::declval<char>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().insert(hamon::declval<char>())), "");

	Set v;

	{
		auto r = v.insert(13);
		VERIFY(r.first->value == 13);
		VERIFY(r.second);

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		auto r = v.insert(13);
		VERIFY(r.first->value == 13);
		VERIFY(!r.second);

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		auto r = v.insert(11);
		VERIFY(r.first->value == 11);
		VERIFY(r.second);

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, InsertHeterogeneousTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE(test());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		using Set = hamon::unordered_set<ThrowIfNegative, TransparentHash, hamon::equal_to<>>;

		Set v;

		EXPECT_NO_THROW(v.insert(10));
		EXPECT_EQ(1u, v.size());

		EXPECT_THROW(v.insert(-10), ThrowIfNegative::Exception);
		EXPECT_EQ(1u, v.size());

		{
			ThrowIfNegative x{0};
			x.value = -1;
			EXPECT_NO_THROW(v.insert(x));
			EXPECT_EQ(2u, v.size());
		}

		EXPECT_NO_THROW(v.insert(-1));	// 要素が既に挿入されている場合は何もしない
		EXPECT_EQ(2u, v.size());
	}
#endif
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace insert_heterogeneous_test

}	// namespace hamon_unordered_set_test

#endif
