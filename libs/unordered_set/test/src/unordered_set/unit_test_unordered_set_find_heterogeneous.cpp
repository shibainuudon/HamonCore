/**
 *	@file	unit_test_unordered_set_find_heterogeneous.cpp
 *
 *	@brief	find のテスト
 *
 *	template<class K>
 *	constexpr iterator       find(const K& k);
 *	template<class K>
 *	constexpr const_iterator find(const K& k) const;
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_set_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_SET) || \
	defined(__cpp_lib_generic_unordered_lookup) && (__cpp_lib_generic_unordered_lookup >= 201811L)

namespace hamon_unordered_set_test
{

namespace find_heterogeneous_test
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
struct is_find_invocable
	: public hamon::false_type {};

template <typename Set, typename K>
struct is_find_invocable<Set, K, hamon::void_t<decltype(hamon::declval<Set>().find(hamon::declval<K>()))>>
	: public hamon::true_type {};

UNORDERED_SET_TEST_CONSTEXPR bool test()
{
	using Key = TransparentKey;
	using Set1 = hamon::unordered_set<Key>;
	using Set2 = hamon::unordered_set<Key, TransparentHash>;
	using Set3 = hamon::unordered_set<Key, hamon::hash<Key>, hamon::equal_to<>>;
	using Set4 = hamon::unordered_set<Key, TransparentHash, hamon::equal_to<>>;

	static_assert(!is_find_invocable<Set1&, int>::value, "");
	static_assert(!is_find_invocable<Set2&, int>::value, "");
	static_assert(!is_find_invocable<Set3&, int>::value, "");
	static_assert( is_find_invocable<Set4&, int>::value, "");

	static_assert(!is_find_invocable<Set1 const&, int>::value, "");
	static_assert(!is_find_invocable<Set2 const&, int>::value, "");
	static_assert(!is_find_invocable<Set3 const&, int>::value, "");
	static_assert( is_find_invocable<Set4 const&, int>::value, "");

	using Set = Set4;
	using Iterator = typename Set::iterator;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().find(hamon::declval<int>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().find(hamon::declval<int>())), ConstIterator>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_SET)
	//static_assert( noexcept(hamon::declval<Set&>().find(hamon::declval<int>())), "");
	//static_assert( noexcept(hamon::declval<Set const&>().find(hamon::declval<int>())), "");
#endif

	{
		Set v{Key{3}, Key{1}, Key{4}, Key{1}};
		{
			auto it = v.find(0);
			VERIFY(it == v.end());
		}
		{
			auto it = v.find(1);
			VERIFY(it != v.end());
			VERIFY(*it == Key{1});
		}
		{
			auto it = v.find(2);
			VERIFY(it == v.end());
		}
		{
			auto it = v.find(3);
			VERIFY(it != v.end());
			VERIFY(*it == Key{3});
		}
	}
	{
		Set const v{Key{3}, Key{1}, Key{4}, Key{1}};
		{
			auto it = v.find(0);
			VERIFY(it == v.end());
		}
		{
			auto it = v.find(1);
			VERIFY(it != v.end());
			VERIFY(*it == Key{1});
		}
		{
			auto it = v.find(2);
			VERIFY(it == v.end());
		}
		{
			auto it = v.find(3);
			VERIFY(it != v.end());
			VERIFY(*it == Key{3});
		}
	}

	return true;
}

UNORDERED_SET_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_SET)
	using Key = TransparentKey;
	{
		using Set = hamon::unordered_set<Key, NoThrowHash<>, NoThrowEqualTo<>>;
		static_assert( noexcept(hamon::declval<Set&>().find(hamon::declval<int>())), "");
		static_assert( noexcept(hamon::declval<Set const&>().find(hamon::declval<int>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, NoThrowHash<>, ThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Set&>().find(hamon::declval<int>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().find(hamon::declval<int>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, ThrowHash<>, NoThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Set&>().find(hamon::declval<int>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().find(hamon::declval<int>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, ThrowHash<>, ThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Set&>().find(hamon::declval<int>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().find(hamon::declval<int>())), "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, FindHeterogeneousTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE(test());

	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE(test_noexcept());
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace find_heterogeneous_test

}	// namespace hamon_unordered_set_test

#endif
