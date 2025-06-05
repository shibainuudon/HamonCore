/**
 *	@file	unit_test_flat_multimap_replace.cpp
 *
 *	@brief	replace のテスト
 *
 *	constexpr void replace(key_container_type&& key_cont, mapped_container_type&& mapped_cont);
 */

#include <hamon/flat_map/flat_multimap.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace replace_test
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
	using Map = hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().replace(hamon::declval<KeyContainer&&>(), hamon::declval<MappedContainer&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().replace(hamon::declval<KeyContainer&&>(), hamon::declval<MappedContainer&&>())), "");

	Map v;
	{
		KeyContainer keys = {Key{3}, Key{1}, Key{4}};
		MappedContainer values = {T{10}, T{20}, T{30}};
		hamon::ranges::sort(keys, Compare{});
		v.replace(hamon::move(keys), hamon::move(values));
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 3);
	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 0);
	VERIFY(v.count(Key{3}) == 1);
	VERIFY(v.count(Key{4}) == 1);
	{
		KeyContainer keys = {Key{1}, Key{2}, Key{1}, Key{4}};
		MappedContainer values = {T{10}, T{20}, T{30}, T{40}};
		hamon::ranges::sort(keys, Compare{});
		v.replace(hamon::move(keys), hamon::move(values));
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 4);
	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 2);
	VERIFY(v.count(Key{2}) == 1);
	VERIFY(v.count(Key{3}) == 0);
	VERIFY(v.count(Key{4}) == 1);

	return true;
}

#undef VERIFY

template <template <typename...> class TKeyContainer, template <typename...> class TValueContainer>
void test_exceptions()
{
#if !defined(HAMON_NO_EXCEPTIONS)
#if !(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 140000)) // gcc12,13 でリリースビルドのとき、abortしてしまう
	using Key = int;
	using T = int;
	using Comp = hamon::less<Key>;
	{
		using KeyContainer = ThrowOnMoveContainer<Key>;
		using ValueContainer = TValueContainer<T>;
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;

		Map v;
		v.emplace(1, 1);
		v.emplace(2, 2);
		KeyContainer keys{3, 4};
		ValueContainer values{5, 6};
		EXPECT_THROW(v.replace(hamon::move(keys), hamon::move(values)), int);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key>;
		using ValueContainer = ThrowOnMoveContainer<T>;
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;

		Map v;
		v.emplace(1, 1);
		v.emplace(2, 2);
		KeyContainer keys{3, 4};
		ValueContainer values{5, 6};
		EXPECT_THROW(v.replace(hamon::move(keys), hamon::move(values)), int);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
#endif
}

GTEST_TEST(FlatMultimapTest, ReplaceTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
//	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));

	test_exceptions<hamon::vector, hamon::vector>();
	test_exceptions<hamon::deque, hamon::deque>();

	{
		hamon::vector<hamon::string> keys = {"Alice", "Bob", "Carol"};
		hamon::vector<int> values = {3, 1, 4};

		hamon::flat_multimap<hamon::string, int> fm;
		EXPECT_TRUE(fm.size() == 0);

		fm.replace(hamon::move(keys), hamon::move(values));
		EXPECT_TRUE(fm.size() == 3);

		std::stringstream ss;
		for (const auto& p : fm)
		{
			ss << p.first << ":" << p.second << ", ";
		}
		EXPECT_EQ("Alice:3, Bob:1, Carol:4, ", ss.str());
	}
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace replace_test

}	// namespace hamon_flat_multimap_test
