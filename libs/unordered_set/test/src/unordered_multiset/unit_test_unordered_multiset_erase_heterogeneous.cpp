/**
 *	@file	unit_test_unordered_multiset_erase_heterogeneous.cpp
 *
 *	@brief	erase のテスト
 *
 *	template<class K> constexpr size_type erase(K&& x);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multiset_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) || \
	(defined(__cpp_lib_associative_heterogeneous_erasure) && (__cpp_lib_associative_heterogeneous_erasure >= 202110L))

namespace hamon_unordered_multiset_test
{

namespace erase_heterogeneous_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Set, typename K, typename = void>
struct is_erase_invocable
	: public hamon::false_type {};

template <typename Set, typename K>
struct is_erase_invocable<Set, K, hamon::void_t<decltype(hamon::declval<Set>().erase(hamon::declval<K>()))>>
	: public hamon::true_type {};

UNORDERED_MULTISET_TEST_CONSTEXPR bool test()
{
	using Key = TransparentKey;
	using Set1 = hamon::unordered_multiset<Key>;
	using Set2 = hamon::unordered_multiset<Key, hamon::remove_const_t<TransparentHash>>;
	using Set3 = hamon::unordered_multiset<Key, hamon::hash<Key>, hamon::equal_to<>>;
	using Set4 = hamon::unordered_multiset<Key, hamon::remove_const_t<TransparentHash>, hamon::equal_to<>>;

	static_assert(!is_erase_invocable<Set1&, int>::value, "");
	static_assert(!is_erase_invocable<Set2&, int>::value, "");
	static_assert(!is_erase_invocable<Set3&, int>::value, "");
	static_assert( is_erase_invocable<Set4&, int>::value, "");

	static_assert(!is_erase_invocable<Set1 const&, int>::value, "");
	static_assert(!is_erase_invocable<Set2 const&, int>::value, "");
	static_assert(!is_erase_invocable<Set3 const&, int>::value, "");
	static_assert(!is_erase_invocable<Set4 const&, int>::value, "");

	using Set = Set4;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().erase(hamon::declval<int>())), SizeType>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
	//static_assert( noexcept(hamon::declval<Set&>().erase(hamon::declval<int>())), "");
#endif

	{
		Set v{Key{0}, Key{0}, Key{1}, Key{1}, Key{2}, Key{2}, Key{1}, Key{1}, Key{1}, Key{4}};
		VERIFY(v.size() == 10);
		VERIFY(v.count(0) == 2);
		VERIFY(v.count(1) == 5);
		VERIFY(v.count(2) == 2);
		VERIFY(v.count(3) == 0);
		VERIFY(v.count(4) == 1);

		{
			auto r = v.erase(0);
			VERIFY(r == 2);
		}
		VERIFY(v.size() == 8);
		VERIFY(v.count(0) == 0);
		VERIFY(v.count(1) == 5);
		VERIFY(v.count(2) == 2);
		VERIFY(v.count(3) == 0);
		VERIFY(v.count(4) == 1);

		{
			auto r = v.erase(1);
			VERIFY(r == 5);
		}
		VERIFY(v.size() == 3);
		VERIFY(v.count(0) == 0);
		VERIFY(v.count(1) == 0);
		VERIFY(v.count(2) == 2);
		VERIFY(v.count(3) == 0);
		VERIFY(v.count(4) == 1);

		{
			auto r = v.erase(2);
			VERIFY(r == 2);
		}
		VERIFY(v.size() == 1);
		VERIFY(v.count(0) == 0);
		VERIFY(v.count(1) == 0);
		VERIFY(v.count(2) == 0);
		VERIFY(v.count(3) == 0);
		VERIFY(v.count(4) == 1);

		{
			auto r = v.erase(3);
			VERIFY(r == 0);
		}
		VERIFY(v.size() == 1);
		VERIFY(v.count(0) == 0);
		VERIFY(v.count(1) == 0);
		VERIFY(v.count(2) == 0);
		VERIFY(v.count(3) == 0);
		VERIFY(v.count(4) == 1);

		{
			auto r = v.erase(4);
			VERIFY(r == 1);
		}
		VERIFY(v.size() == 0);
		VERIFY(v.count(0) == 0);
		VERIFY(v.count(1) == 0);
		VERIFY(v.count(2) == 0);
		VERIFY(v.count(3) == 0);
		VERIFY(v.count(4) == 0);
	}

	return true;
}

UNORDERED_MULTISET_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
	using Key = TransparentKey;
	{
		using Set = hamon::unordered_multiset<Key, NoThrowHash<>, NoThrowEqualTo<>>;
		static_assert( noexcept(hamon::declval<Set&>().erase(hamon::declval<int>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, NoThrowHash<>, ThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<int>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, ThrowHash<>, NoThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<int>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, ThrowHash<>, ThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<int>())), "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, EraseHeterogeneousTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test()));

	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace erase_heterogeneous_test

}	// namespace hamon_unordered_multiset_test

#endif
