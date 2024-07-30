/**
 *	@file	unit_test_functional_default_searcher.cpp
 *
 *	@brief	default_searcher のテスト
 */

#include <hamon/functional/default_searcher.hpp>
#include <hamon/algorithm/search.hpp>
#include <hamon/string_view.hpp>
#include <gtest/gtest.h>
#include <cctype>
#include "constexpr_test.hpp"

namespace hamon_functional_test
{

namespace default_searcher_test
{

struct icmp
{
	bool operator()(char c1, char c2) const
	{
		return std::tolower(c1) == std::tolower(c2);
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test()
{
#if !defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	using I = hamon::string_view::iterator;
#endif

	{
		hamon::string_view in =
			"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed "
			"do eiusmod tempor incididunt ut labore et dolore magna aliqua";
		{
			hamon::string_view needle = "pisci";
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
			hamon::default_searcher    searcher{needle.begin(), needle.end()};
#else
			hamon::default_searcher<I> searcher{needle.begin(), needle.end()};
#endif
			auto ret = searcher(in.begin(), in.end());
			VERIFY(ret.first  != in.end());
			VERIFY(ret.second != in.end());
			VERIFY((ret.first  - in.begin()) == 43);
			VERIFY((ret.second - in.begin()) == 48);
			VERIFY(hamon::string_view(ret.first, ret.second) == needle);

			auto it = hamon::search(in.begin(), in.end(), searcher);
			VERIFY(it != in.end());
			VERIFY((it - in.begin()) == 43);
		}
		{
			hamon::string_view needle = "pisco";
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
			hamon::default_searcher    searcher{needle.begin(), needle.end()};
#else
			hamon::default_searcher<I> searcher{needle.begin(), needle.end()};
#endif
			auto ret = searcher(in.begin(), in.end());
			VERIFY(ret.first  == in.end());
			VERIFY(ret.second == in.end());

			auto it = hamon::search(in.begin(), in.end(), searcher);
			VERIFY(it == in.end());
		}
	}
	{
		hamon::string_view text = "babcabaabaac";
		{
			hamon::string_view pattern = "ab";
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
			hamon::default_searcher    searcher{pattern.begin(), pattern.end()};
#else
			hamon::default_searcher<I> searcher{pattern.begin(), pattern.end()};
#endif
			auto ret = searcher(text.begin(), text.end());
			VERIFY(ret.first  != text.end());
			VERIFY(ret.second != text.end());
			VERIFY((ret.first  - text.begin()) == 1);
			VERIFY((ret.second - text.begin()) == 3);
			VERIFY(hamon::string_view(ret.first, ret.second) == pattern);

			auto it = hamon::search(text.begin(), text.end(), searcher);
			VERIFY(it != text.end());
			VERIFY((it - text.begin()) == 1);
		}
		{
			hamon::string_view pattern = "aba";
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
			hamon::default_searcher    searcher{pattern.begin(), pattern.end()};
#else
			hamon::default_searcher<I> searcher{pattern.begin(), pattern.end()};
#endif
			auto ret = searcher(text.begin(), text.end());
			VERIFY(ret.first  != text.end());
			VERIFY(ret.second != text.end());
			VERIFY((ret.first  - text.begin()) == 4);
			VERIFY((ret.second - text.begin()) == 7);
			VERIFY(hamon::string_view(ret.first, ret.second) == pattern);

			auto it = hamon::search(text.begin(), text.end(), searcher);
			VERIFY(it != text.end());
			VERIFY((it - text.begin()) == 4);
		}
		{
			hamon::string_view pattern = "abab";
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
			hamon::default_searcher    searcher{pattern.begin(), pattern.end()};
#else
			hamon::default_searcher<I> searcher{pattern.begin(), pattern.end()};
#endif
			auto ret = searcher(text.begin(), text.end());
			VERIFY(ret.first  == text.end());
			VERIFY(ret.second == text.end());

			auto it = hamon::search(text.begin(), text.end(), searcher);
			VERIFY(it == text.end());
		}
	}
	return true;
}

#undef VERIFY

GTEST_TEST(FunctionalTest, DefaultSearcherTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());

	{
#if !defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		using I = hamon::string_view::iterator;
#endif

		hamon::string_view text = "abcABC";
		hamon::string_view pattern = "AB";
		{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
			hamon::default_searcher    searcher{pattern.begin(), pattern.end()};
#else
			hamon::default_searcher<I> searcher{pattern.begin(), pattern.end()};
#endif
			auto ret = searcher(text.begin(), text.end());
			EXPECT_TRUE(ret.first  != text.end());
			EXPECT_TRUE(ret.second != text.end());
			EXPECT_TRUE((ret.first  - text.begin()) == 3);
			EXPECT_TRUE((ret.second - text.begin()) == 5);
		}
		{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
			hamon::default_searcher          searcher{pattern.begin(), pattern.end(), icmp{}};
#else
			hamon::default_searcher<I, icmp> searcher{pattern.begin(), pattern.end(), icmp{}};
#endif
			auto ret = searcher(text.begin(), text.end());
			EXPECT_TRUE(ret.first  != text.end());
			EXPECT_TRUE(ret.second != text.end());
			EXPECT_TRUE((ret.first  - text.begin()) == 0);
			EXPECT_TRUE((ret.second - text.begin()) == 2);
		}
	}
}

}	// namespace default_searcher_test

}	// namespace hamon_functional_test
