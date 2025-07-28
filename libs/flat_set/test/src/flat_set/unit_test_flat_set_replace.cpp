/**
 *	@file	unit_test_flat_set_replace.cpp
 *
 *	@brief	replace のテスト
 *
 *	constexpr void replace(container_type&&);
 */

#include <hamon/flat_set/flat_set.hpp>
#include <hamon/algorithm/ranges/sort.hpp>
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
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace replace_test
{

#if !defined(HAMON_USE_STD_FLAT_SET)
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename Compare>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_set<Key, Compare, KeyContainer>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().replace(hamon::declval<KeyContainer&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().replace(hamon::declval<KeyContainer&&>())), "");

	Set v;
	{
		KeyContainer keys = {Key{3}, Key{1}, Key{4}};
		hamon::ranges::sort(keys, Compare{});
		v.replace(hamon::move(keys));
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 3);
	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 0);
	VERIFY(v.count(Key{3}) == 1);
	VERIFY(v.count(Key{4}) == 1);
	{
		KeyContainer keys = {Key{3}, Key{2}, Key{1}, Key{4}};
		hamon::ranges::sort(keys, Compare{});
		v.replace(hamon::move(keys));
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 4);
	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 1);
	VERIFY(v.count(Key{3}) == 1);
	VERIFY(v.count(Key{4}) == 1);

	return true;
}

#undef VERIFY

void test_exceptions()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	using Key = int;
	using Comp = hamon::less<Key>;
	{
		using KeyContainer = ThrowOnMoveContainer<Key>;
		using Set = hamon::flat_set<Key, Comp, KeyContainer>;

		Set v;
		v.emplace(1);
		v.emplace(2);
		KeyContainer keys{3, 4};
		EXPECT_THROW(v.replace(hamon::move(keys)), int);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatSetTest, ReplaceTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::less<>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<float>, hamon::greater<float>>()));

	test_exceptions();

	{
		hamon::vector<hamon::string> keys = {"Alice", "Bob", "Carol"};

		hamon::flat_set<hamon::string> fs;

		EXPECT_EQ(0u, fs.size());

		fs.replace(hamon::move(keys));

		EXPECT_EQ(3u, fs.size());

		std::stringstream ss;
		for (const auto& i: fs)
		{
			ss << i << ", ";
		}
		EXPECT_EQ("Alice, Bob, Carol, ", ss.str());
	}
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace replace_test

}	// namespace hamon_flat_set_test
