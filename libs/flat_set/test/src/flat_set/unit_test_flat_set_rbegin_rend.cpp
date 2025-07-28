/**
 *	@file	unit_test_flat_set_rbegin_rend.cpp
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

#include <hamon/flat_set/flat_set.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace rbegin_rend_test
{

#if !defined(HAMON_USE_STD_FLAT_SET)
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_set<Key, hamon::less<Key>, KeyContainer>;

	using ReverseIterator = typename Set::reverse_iterator;
	using ConstReverseIterator = typename Set::const_reverse_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().rbegin()),   ReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().rend()),     ReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().crbegin()),  ConstReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().crend()),    ConstReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().rbegin()),  ConstReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().rend()),    ConstReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().crbegin()), ConstReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().crend()),   ConstReverseIterator>::value, "");

	static_assert(noexcept(hamon::declval<Set&>().rbegin()), "");
	static_assert(noexcept(hamon::declval<Set&>().rend()), "");
	static_assert(noexcept(hamon::declval<Set&>().crbegin()), "");
	static_assert(noexcept(hamon::declval<Set&>().crend()), "");
	static_assert(noexcept(hamon::declval<Set const&>().rbegin()), "");
	static_assert(noexcept(hamon::declval<Set const&>().rend()), "");
	static_assert(noexcept(hamon::declval<Set const&>().crbegin()), "");
	static_assert(noexcept(hamon::declval<Set const&>().crend()), "");

	{
		Set v;
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
		Set const cv;
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
		Set v
		{
			Key{2},
			Key{3},
			Key{1},
		};
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(*it == Key{3});
		{
			auto t = ++it;
			VERIFY(*t == Key{2});
		}
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(*it == Key{2});
		{
			auto t = it++;
			VERIFY(*t == Key{2});
		}
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(*it == Key{1});
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it == v.rend());
	}
	{
		Set const v
		{
			Key{4},
			Key{2},
			Key{3},
			Key{1},
		};
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it == v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == Key{4});
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == Key{3});
		it++;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == Key{2});
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == Key{1});
		it++;
		VERIFY(it != v.rbegin());
		VERIFY(it == v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it == v.crend());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatSetTest, RBeginREndTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>>()));

	{
		hamon::flat_set<int> fs = {3, 1, 4};

		std::stringstream ss;
		for (auto i = fs.rbegin(); i != fs.rend(); ++i)
		{
			ss << *i << ", ";
		}
		EXPECT_EQ("4, 3, 1, ", ss.str());
	}
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace rbegin_rend_test

}	// namespace hamon_flat_set_test
