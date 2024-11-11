/**
 *	@file	unit_test_multiset_rbegin_rend.cpp
 *
 *	@brief	rbegin, rend のテスト
 *
 *	reverse_iterator       rbegin() noexcept;
 *	const_reverse_iterator rbegin() const noexcept;
 *	reverse_iterator       rend() noexcept;
 *	const_reverse_iterator rend() const noexcept;
 *	const_reverse_iterator crbegin() const noexcept;
 *	const_reverse_iterator crend() const noexcept;
 */

#include <hamon/set/multiset.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include <sstream>

namespace hamon_multiset_test
{

namespace rbegin_rend_test
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
	using ReverseIterator = typename Set::reverse_iterator;
	using ConstReverseIterator = typename Set::const_reverse_iterator;

	{
		Set v;
		Set const cv;
		static_assert(hamon::is_same<decltype(v.rbegin()),   ReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(v.rend()),     ReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.rbegin()),  ConstReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.rend()),    ConstReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(v.crbegin()),  ConstReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(v.crend()),    ConstReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.crbegin()), ConstReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.crend()),   ConstReverseIterator>::value, "");

		static_assert(noexcept(v.rbegin()), "");
		static_assert(noexcept(v.rend()), "");
		static_assert(noexcept(cv.rbegin()), "");
		static_assert(noexcept(cv.rend()), "");
		static_assert(noexcept(v.crbegin()), "");
		static_assert(noexcept(v.crend()), "");
		static_assert(noexcept(cv.crbegin()), "");
		static_assert(noexcept(cv.crend()), "");
	}
	{
		Set v;
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it == v.rend());
	}
	{
		Set const v;
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it == v.rend());
	}
	{
		Set v;
		auto it = v.crbegin();
		VERIFY(it == v.crbegin());
		VERIFY(it == v.crend());
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
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it == v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == Key{4});
		VERIFY(*(++it) == Key{4});
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*(it++) == Key{4});
		VERIFY(*it == Key{2});
		++it;
		VERIFY(*it == Key{1});
		it++;
		VERIFY(*it == Key{1});
		++it;
		VERIFY(*it == Key{1});
		it++;
		VERIFY(it != v.rbegin());
		VERIFY(it == v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it == v.crend());
		VERIFY(*(--it) == Key{1});
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*(it--) == Key{1});
		VERIFY(*it == Key{1});
		--it;
		VERIFY(*it == Key{1});
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
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it == v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == Key{4});
		VERIFY(*(++it) == Key{4});
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*(it++) == Key{4});
		VERIFY(*it == Key{2});
		++it;
		VERIFY(*it == Key{1});
		it++;
		VERIFY(*it == Key{1});
		++it;
		VERIFY(*it == Key{1});
		it++;
		VERIFY(it != v.rbegin());
		VERIFY(it == v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it == v.crend());
		VERIFY(*(--it) == Key{1});
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*(it--) == Key{1});
		VERIFY(*it == Key{1});
		--it;
		VERIFY(*it == Key{1});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MultisetTest, RBeginREndTest)
{
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());

	// https://en.cppreference.com/w/cpp/container/multiset/rbegin
	{
		hamon::multiset<unsigned> rep {1, 2, 3, 4, 1, 2, 3, 4};
		std::stringstream out;
		for (auto it = rep.crbegin(); it != rep.crend(); ++it)
		{
			out << *it << ' ';
		}
		EXPECT_EQ("4 4 3 3 2 2 1 1 ", out.str());
	}
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace rbegin_rend_test

}	// namespace hamon_multiset_test
