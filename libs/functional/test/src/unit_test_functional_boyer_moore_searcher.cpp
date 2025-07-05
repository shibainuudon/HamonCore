/**
 *	@file	unit_test_functional_boyer_moore_searcher.cpp
 *
 *	@brief	boyer_moore_searcher のテスト
 */

#include <hamon/functional/boyer_moore_searcher.hpp>
#include <hamon/algorithm/search.hpp>
#include <hamon/string_view.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_functional_test
{

namespace boyer_moore_searcher_test
{

inline HAMON_CXX11_CONSTEXPR char tolower(char c)
{
	return ('A' <= c && c <= 'Z') ? (c - 'A' + 'a') : c;
}

struct icmp
{
	HAMON_CXX11_CONSTEXPR bool operator()(char c1, char c2) const
	{
		return tolower(c1) == tolower(c2);
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX20_CONSTEXPR bool test()
{
#if !defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	using I = hamon::string_view::iterator;
#endif
	using Hash = hamon::hash<hamon::string_view::value_type>;

	{
		hamon::string_view in =
			"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed "
			"do eiusmod tempor incididunt ut labore et dolore magna aliqua";
		{
			hamon::string_view needle = "pisci";
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
			hamon::boyer_moore_searcher    searcher{needle.begin(), needle.end()};
#else
			hamon::boyer_moore_searcher<I> searcher{needle.begin(), needle.end()};
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
			hamon::boyer_moore_searcher    searcher{needle.begin(), needle.end()};
#else
			hamon::boyer_moore_searcher<I> searcher{needle.begin(), needle.end()};
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
			hamon::boyer_moore_searcher    searcher{pattern.begin(), pattern.end()};
#else
			hamon::boyer_moore_searcher<I> searcher{pattern.begin(), pattern.end()};
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
			hamon::boyer_moore_searcher    searcher{pattern.begin(), pattern.end()};
#else
			hamon::boyer_moore_searcher<I> searcher{pattern.begin(), pattern.end()};
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
			hamon::boyer_moore_searcher                searcher{pattern.begin(), pattern.end(), Hash{}, icmp{}};
#else
			hamon::boyer_moore_searcher<I, Hash, icmp> searcher{pattern.begin(), pattern.end(), Hash{}, icmp{}};
#endif
			auto ret = searcher(text.begin(), text.end());
			VERIFY(ret.first  == text.end());
			VERIFY(ret.second == text.end());

			auto it = hamon::search(text.begin(), text.end(), searcher);
			VERIFY(it == text.end());
		}
		{
			hamon::string_view pattern = "";
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
			hamon::boyer_moore_searcher                searcher{pattern.begin(), pattern.end(), Hash{}, icmp{}};
#else
			hamon::boyer_moore_searcher<I, Hash, icmp> searcher{pattern.begin(), pattern.end(), Hash{}, icmp{}};
#endif
			auto ret = searcher(text.begin(), text.end());
			VERIFY(ret.first  == text.begin());
			VERIFY(ret.second == text.begin());
		}
		{
			hamon::string_view pattern = "babcabaabaaca";
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
			hamon::boyer_moore_searcher                searcher{pattern.begin(), pattern.end(), Hash{}, icmp{}};
#else
			hamon::boyer_moore_searcher<I, Hash, icmp> searcher{pattern.begin(), pattern.end(), Hash{}, icmp{}};
#endif
			auto ret = searcher(text.begin(), text.end());
			VERIFY(ret.first  == text.end());
			VERIFY(ret.second == text.end());

			auto it = hamon::search(text.begin(), text.end(), searcher);
			VERIFY(it == text.end());
		}
	}
	{
		hamon::string_view text = "abcABC";
		{
			hamon::string_view pattern = "AB";
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
			hamon::boyer_moore_searcher    searcher{pattern.begin(), pattern.end()};
#else
			hamon::boyer_moore_searcher<I> searcher{pattern.begin(), pattern.end()};
#endif
			auto ret = searcher(text.begin(), text.end());
			VERIFY(ret.first  != text.end());
			VERIFY(ret.second != text.end());
			VERIFY((ret.first  - text.begin()) == 3);
			VERIFY((ret.second - text.begin()) == 5);
		}
		{
			hamon::string_view pattern = "AB";
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
			hamon::boyer_moore_searcher                searcher{pattern.begin(), pattern.end(), Hash{}, icmp{}};
#else
			hamon::boyer_moore_searcher<I, Hash, icmp> searcher{pattern.begin(), pattern.end(), Hash{}, icmp{}};
#endif
			auto ret = searcher(text.begin(), text.end());
			VERIFY(ret.first  != text.end());
			VERIFY(ret.second != text.end());
			VERIFY((ret.first  - text.begin()) == 0);
			VERIFY((ret.second - text.begin()) == 2);
		}
	}
	{
		hamon::string_view text = "";
		{
			hamon::string_view pattern = "a";
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
			hamon::boyer_moore_searcher    searcher{pattern.begin(), pattern.end()};
#else
			hamon::boyer_moore_searcher<I> searcher{pattern.begin(), pattern.end()};
#endif
			auto ret = searcher(text.begin(), text.end());
			VERIFY(ret.first  == text.end());
			VERIFY(ret.second == text.end());
		}
		{
			hamon::string_view pattern = "";
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
			hamon::boyer_moore_searcher    searcher{pattern.begin(), pattern.end()};
#else
			hamon::boyer_moore_searcher<I> searcher{pattern.begin(), pattern.end()};
#endif
			auto ret = searcher(text.begin(), text.end());
			VERIFY(ret.first  == text.end());
			VERIFY(ret.second == text.end());
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FunctionalTest, BoyerMooreSearcherTest)
{
#if !(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// MSVCでconstexprにすると内部コンパイラエラーになってしまう
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
#else
	EXPECT_TRUE(test());
#endif
}

}	// namespace boyer_moore_searcher_test

}	// namespace hamon_functional_test
