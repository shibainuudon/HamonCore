/**
 *	@file	unit_test_unordered_multiset_begin_end.cpp
 *
 *	@brief	begin, end のテスト
 *
 *	constexpr iterator       begin() noexcept;
 *	constexpr const_iterator begin() const noexcept;
 *	constexpr iterator       end() noexcept;
 *	constexpr const_iterator end() const noexcept;
 *	constexpr const_iterator cbegin() const noexcept;
 *	constexpr const_iterator cend() const noexcept;
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace begin_end_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key>;
	using Iterator = typename Set::iterator;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().begin()),   Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().end()),     Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().cbegin()),  ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().cend()),    ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().begin()),  ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().end()),    ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().cbegin()), ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().cend()),   ConstIterator>::value, "");

	static_assert(noexcept(hamon::declval<Set&>().begin()), "");
	static_assert(noexcept(hamon::declval<Set&>().end()), "");
	static_assert(noexcept(hamon::declval<Set&>().cbegin()), "");
	static_assert(noexcept(hamon::declval<Set&>().cend()), "");
	static_assert(noexcept(hamon::declval<Set const&>().begin()), "");
	static_assert(noexcept(hamon::declval<Set const&>().end()), "");
	static_assert(noexcept(hamon::declval<Set const&>().cbegin()), "");
	static_assert(noexcept(hamon::declval<Set const&>().cend()), "");

	{
		Set v;
		{
			auto it = v.begin();
			VERIFY(it == v.begin());
			VERIFY(it == v.end());
		}
		{
			auto it = v.cbegin();
			VERIFY(it == v.cbegin());
			VERIFY(it == v.cend());
		}
		Set const cv;
		{
			auto it = cv.begin();
			VERIFY(it == cv.begin());
			VERIFY(it == cv.end());
		}
		{
			auto it = cv.cbegin();
			VERIFY(it == cv.cbegin());
			VERIFY(it == cv.cend());
		}
	}
	{
		Set v{Key{3}, Key{1}, Key{4}, Key{1}};

		auto check = [](Iterator it)
		{
			return
				*it == 1 ||
				*it == 3 ||
				*it == 4;
		};

		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(it == v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(check(it));

		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(check(it));

		it++;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(check(it));

		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(check(it));

		it++;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
	}
	{
		Set const v{Key{3}, Key{1}, Key{4}, Key{1}};

		auto check = [](ConstIterator it)
		{
			return
				*it == 1 ||
				*it == 3 ||
				*it == 4;
		};

		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(it == v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(check(it));

		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(check(it));

		it++;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(check(it));

		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(check(it));

		it++;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, BeginEndTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace begin_end_test

}	// namespace hamon_unordered_multiset_test
