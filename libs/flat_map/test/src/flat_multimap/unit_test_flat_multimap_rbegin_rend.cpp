/**
 *	@file	unit_test_flat_multimap_rbegin_rend.cpp
 *
 *	@brief	rbegin, rend のテスト
 *
 *	constexpr reverse_iterator       rbegin() noexcept;
 *	constexpr const_reverse_iterator rbegin() const noexcept;
 *	constexpr reverse_iterator       rend() noexcept;
 *	constexpr const_reverse_iterator rend() const noexcept;
 *	constexpr const_reverse_iterator crbegin() const noexcept;
 *	constexpr const_reverse_iterator crend() const noexcept;
 */

#include <hamon/flat_map/flat_multimap.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace rbegin_rend_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_multimap<Key, T, hamon::less<Key>, KeyContainer, MappedContainer>;

	using ReverseIterator = typename Map::reverse_iterator;
	using ConstReverseIterator = typename Map::const_reverse_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().rbegin()),   ReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().rend()),     ReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().crbegin()),  ConstReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().crend()),    ConstReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().rbegin()),  ConstReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().rend()),    ConstReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().crbegin()), ConstReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().crend()),   ConstReverseIterator>::value, "");

	static_assert(noexcept(hamon::declval<Map&>().rbegin()), "");
	static_assert(noexcept(hamon::declval<Map&>().rend()), "");
	static_assert(noexcept(hamon::declval<Map&>().crbegin()), "");
	static_assert(noexcept(hamon::declval<Map&>().crend()), "");
	static_assert(noexcept(hamon::declval<Map const&>().rbegin()), "");
	static_assert(noexcept(hamon::declval<Map const&>().rend()), "");
	static_assert(noexcept(hamon::declval<Map const&>().crbegin()), "");
	static_assert(noexcept(hamon::declval<Map const&>().crend()), "");

	{
		Map v;
		{
			auto it = v.rbegin();
			VERIFY(it == v.rbegin());
			VERIFY(it == v.rend());
		}
		{
			auto it = v.crbegin();
			VERIFY(it == v.crbegin());
			VERIFY(it == v.crend());
		}
		Map const cv;
		{
			auto it = cv.rbegin();
			VERIFY(it == cv.rbegin());
			VERIFY(it == cv.rend());
		}
		{
			auto it = cv.crbegin();
			VERIFY(it == cv.crbegin());
			VERIFY(it == cv.crend());
		}
	}
	{
		Map v
		{
			{Key{2}, T{10}},
			{Key{3}, T{20}},
			{Key{1}, T{30}},
		};
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it->first == Key{3});
		VERIFY(it->second == T{20});
		{
			auto t = ++it;
			VERIFY(t->first == Key{2});
			VERIFY(t->second == T{10});
		}
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it->first == Key{2});
		VERIFY(it->second == T{10});
		{
			auto t = it++;
			VERIFY(t->first == Key{2});
			VERIFY(t->second == T{10});
		}
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY((*it).first == Key{1});
		VERIFY((*it).second == T{30});
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it == v.rend());
	}
	{
		Map const v
		{
			{Key{4}, T{10}},
			{Key{2}, T{20}},
			{Key{3}, T{30}},
			{Key{1}, T{40}},
		};
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it == v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(it->first == Key{4});
		VERIFY(it->second == T{10});
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY((*it).first == Key{3});
		VERIFY((*it).second == T{30});
		it++;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(it->first == Key{2});
		VERIFY(it->second == T{20});
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(it->first == Key{1});
		VERIFY(it->second == T{40});
		it++;
		VERIFY(it != v.rbegin());
		VERIFY(it == v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it == v.crend());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultimapTest, RBeginREndTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>>()));

	{
		hamon::flat_multimap<int, char> fm =
		{
			{10, 'A'}, {11, 'B'}, {12, 'C'},
			{10, 'a'}, {11, 'b'}, {12, 'c'},
		};

		{
			auto i = fm.rbegin();
			EXPECT_TRUE(i->first == 12);
			EXPECT_TRUE(i->second == 'c');
			++i;
			EXPECT_TRUE(i->first == 12);
			EXPECT_TRUE(i->second == 'C');
			++i;
			EXPECT_TRUE(i->first == 11);
			EXPECT_TRUE(i->second == 'b');
			++i;
			EXPECT_TRUE(i->first == 11);
			EXPECT_TRUE(i->second == 'B');
			++i;
			EXPECT_TRUE(i->first == 10);
			EXPECT_TRUE(i->second == 'a');
			++i;
			EXPECT_TRUE(i->first == 10);
			EXPECT_TRUE(i->second == 'A');
			++i;
			EXPECT_TRUE(i == fm.rend());
		}
		{
			auto i = fm.crbegin();
			EXPECT_TRUE(i->first == 12);
			EXPECT_TRUE(i->second == 'c');
			++i;
			EXPECT_TRUE(i->first == 12);
			EXPECT_TRUE(i->second == 'C');
			++i;
			EXPECT_TRUE(i->first == 11);
			EXPECT_TRUE(i->second == 'b');
			++i;
			EXPECT_TRUE(i->first == 11);
			EXPECT_TRUE(i->second == 'B');
			++i;
			EXPECT_TRUE(i->first == 10);
			EXPECT_TRUE(i->second == 'a');
			++i;
			EXPECT_TRUE(i->first == 10);
			EXPECT_TRUE(i->second == 'A');
			++i;
			EXPECT_TRUE(i == fm.crend());
		}
	}
}

}	// namespace rbegin_rend_test

}	// namespace hamon_flat_multimap_test
