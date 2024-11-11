/**
 *	@file	unit_test_multiset_begin_end.cpp
 *
 *	@brief	begin, end のテスト
 *
 *	iterator               begin() noexcept;
 *	const_iterator         begin() const noexcept;
 *	iterator               end() noexcept;
 *	const_iterator         end() const noexcept;
 *	const_iterator         cbegin() const noexcept;
 *	const_iterator         cend() const noexcept;
 */

#include <hamon/set/multiset.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include <string>
#include <sstream>

namespace hamon_multiset_test
{

namespace begin_end_test
{

#if !defined(HAMON_USE_STD_MULTISET)
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
MULTISET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::multiset<Key>;
	using Iterator = typename Set::iterator;
	using ConstIterator = typename Set::const_iterator;

	{
		Set v;
		Set const cv;
		static_assert(hamon::is_same<decltype(v.begin()),   Iterator>::value, "");
		static_assert(hamon::is_same<decltype(v.end()),     Iterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.begin()),  ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.end()),    ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype(v.cbegin()),  ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype(v.cend()),    ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.cbegin()), ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.cend()),   ConstIterator>::value, "");

		static_assert(noexcept(v.begin()), "");
		static_assert(noexcept(v.end()), "");
		static_assert(noexcept(cv.begin()), "");
		static_assert(noexcept(cv.end()), "");
		static_assert(noexcept(v.cbegin()), "");
		static_assert(noexcept(v.cend()), "");
		static_assert(noexcept(cv.cbegin()), "");
		static_assert(noexcept(cv.cend()), "");
	}
	{
		Set v;
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
	}
	{
		Set const v;
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
	}
	{
		Set v;
		auto it = v.cbegin();
		VERIFY(it == v.cbegin());
		VERIFY(it == v.cend());
	}
	{
		Set v
		{
			Key{1},
			Key{4},
			Key{1},
			Key{4},
			Key{2},
			Key{1},
		};
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(it == v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == Key{1});
		VERIFY(*(++it) == Key{1});
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*(it++) == Key{1});
		VERIFY(*it == Key{1});
		++it;
		VERIFY(*it == Key{2});
		it++;
		VERIFY(*it == Key{4});
		++it;
		VERIFY(*it == Key{4});
		it++;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
		VERIFY(*(--it) == Key{4});
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*(it--) == Key{4});
		VERIFY(*it == Key{4});
		--it;
		VERIFY(*it == Key{2});
	}
	{
		Set const v
		{
			Key{1},
			Key{4},
			Key{1},
			Key{4},
			Key{2},
			Key{1},
		};
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(it == v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == Key{1});
		VERIFY(*(++it) == Key{1});
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*(it++) == Key{1});
		VERIFY(*it == Key{1});
		++it;
		VERIFY(*it == Key{2});
		it++;
		VERIFY(*it == Key{4});
		++it;
		VERIFY(*it == Key{4});
		it++;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
		VERIFY(*(--it) == Key{4});
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*(it--) == Key{4});
		VERIFY(*it == Key{4});
		--it;
		VERIFY(*it == Key{2});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MultisetTest, BeginEndTest)
{
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());

	// https://en.cppreference.com/w/cpp/container/multiset/begin
	{
		const hamon::multiset<std::string> words =
		{
			"some", "not", "sorted", "words",
			"will", "come", "out", "sorted",
		};

		std::stringstream out;
		for (auto it = words.begin(); it != words.end(); )
		{
			auto count = words.count(*it);
			out << *it << ":" << count << ", ";
			hamon::advance(it, count); // all count elements have equivalent keys
		}

		EXPECT_EQ("come:1, not:1, out:1, some:1, sorted:2, will:1, words:1, ", out.str());
	}
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace begin_end_test

}	// namespace hamon_multiset_test
