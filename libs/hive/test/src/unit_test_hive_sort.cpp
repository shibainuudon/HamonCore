/**
 *	@file	unit_test_hive_sort.cpp
 *
 *	@brief	sort のテスト
 *
 *	template<class Compare = less<T>>
 *	void sort(Compare comp = Compare());
 */

#include <hamon/hive.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/string.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace sort_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Hive = hamon::hive<T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().sort()), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().sort(hamon::ranges::less{})), void>::value, "");
	static_assert(!noexcept(hamon::declval<Hive>().sort()), "");
	static_assert(!noexcept(hamon::declval<Hive>().sort(hamon::ranges::less{})), "");

	{
		Hive v{3,1,4,1,5,9,2,6,5,3,5};
		v.sort();
		VERIFY(v.size() == 11u);
		{
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{6});
			VERIFY(*it++ == T{9});
			VERIFY(it == v.end());
		}
		v.sort(hamon::greater<T>{});
		VERIFY(v.size() == 11u);
		{
			auto it = v.begin();
			VERIFY(*it++ == T{9});
			VERIFY(*it++ == T{6});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.end());
		}
	}

	return true;
}

HAMON_CXX20_CONSTEXPR bool test2()
{
	hamon::hive<hamon::string> v;
	v.emplace(static_cast<const char*>("The"));
	v.emplace(static_cast<const char*>("quick"));
	v.emplace(static_cast<const char*>("brown"));
	v.emplace(static_cast<const char*>("fox"));
	v.emplace(static_cast<const char*>("jumps"));
	v.emplace(static_cast<const char*>("over"));
	v.emplace(static_cast<const char*>("the"));
	v.emplace(static_cast<const char*>("lazy"));
	v.emplace(static_cast<const char*>("dog"));

	v.sort();

	auto it = v.begin();
	VERIFY(*it++ == "The");
	VERIFY(*it++ == "brown");
	VERIFY(*it++ == "dog");
	VERIFY(*it++ == "fox");
	VERIFY(*it++ == "jumps");
	VERIFY(*it++ == "lazy");
	VERIFY(*it++ == "over");
	VERIFY(*it++ == "quick");
	VERIFY(*it++ == "the");
	VERIFY(it == v.end());

	return true;
}

struct MoveOnly
{
	int value;

	HAMON_CXX14_CONSTEXPR MoveOnly(int v) : value(v) {}

	MoveOnly(MoveOnly const&) = delete;
	MoveOnly& operator=(MoveOnly const&) = delete;

	HAMON_CXX14_CONSTEXPR MoveOnly(MoveOnly&& x) HAMON_NOEXCEPT : value(x.value) {}
	HAMON_CXX14_CONSTEXPR MoveOnly& operator=(MoveOnly&& x) HAMON_NOEXCEPT { value = x.value; return *this; }
};

HAMON_CXX20_CONSTEXPR bool test3()
{
	hamon::hive<MoveOnly> v;
	v.emplace(10);
	v.emplace(30);
	v.emplace(20);

	v.sort([](MoveOnly const& lhs, MoveOnly const& rhs) {return lhs.value < rhs.value;});

	auto it = v.begin();
	VERIFY(it->value == 10);
	++it;
	VERIFY(it->value == 20);
	++it;
	VERIFY(it->value == 30);
	++it;
	VERIFY(it == v.end());

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, SortTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<float>());

#if (defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 120000))
	// gcc11 のときはconstexprにできない
	EXPECT_TRUE(test2());
#else
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());
#endif

#if (defined(HAMON_MSVC) && (HAMON_MSVC < 1930))
	// Visual Studio 2019 のとき、constexprとして評価しようとするとコンパイルエラーになる
	// (呼び出されないはずのコピーコンストラクタを呼び出そうとしてエラーになる)
	// Visual Studio 2019 のバグかと思われる
	EXPECT_TRUE(test3());
#else
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test3());
#endif
}

}	// namespace sort_test

}	// namespace hamon_hive_test
