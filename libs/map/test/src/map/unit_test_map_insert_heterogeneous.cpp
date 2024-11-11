/**
 *	@file	unit_test_map_insert_heterogeneous.cpp
 *
 *	@brief	insert のテスト
 *
 *	template<class P> pair<iterator, bool> insert(P&& x);
 */

#include <hamon/map/map.hpp>
#include <hamon/array.hpp>
#include <hamon/iterator.hpp>
#include <hamon/pair.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <utility>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace insert_heterogeneous_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

struct S
{
	static int s_ctor_count;
	static int s_dtor_count;

	int value;

	S(int v) : value(v)
	{
		++s_ctor_count;
	}

	~S()
	{
		++s_dtor_count;
	}

	S(S&&)                 = delete;
	S(S const&)            = delete;
	S& operator=(S&&)      = delete;
	S& operator=(S const&) = delete;
};

int S::s_ctor_count = 0;
int S::s_dtor_count = 0;

#if !defined(HAMON_NO_EXCEPTIONS)
struct MayThrow
{
	struct Exception{};

	int value;

	MayThrow(int v) : value(v)
	{
		if (v < 0)
		{
			throw Exception{};
		}
	}
};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

MAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::map<int, double>;
	using ValueType = typename Map::value_type;
	using Iterator = typename Map::iterator;
#if defined(HAMON_USE_STD_MAP)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	Map v;

	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<std::pair<int, float>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<std::pair<char, double>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<std::pair<char, float>>())), Result>::value, "");
	static_assert(!noexcept(v.insert(hamon::declval<std::pair<int, float>>())), "");
	static_assert(!noexcept(v.insert(hamon::declval<std::pair<char, double>>())), "");
	static_assert(!noexcept(v.insert(hamon::declval<std::pair<char, float>>())), "");

#if !defined(HAMON_USE_STD_MAP) || (defined(__cpp_lib_tuple_like) && (__cpp_lib_tuple_like >= 202207L))
	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<std::tuple<int, float>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<std::tuple<char, double>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<std::tuple<char, float>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<std::array<int, 2>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<std::array<double, 2>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<std::array<char, 2>>())), Result>::value, "");
	static_assert(!noexcept(v.insert(hamon::declval<std::tuple<int, float>>())), "");
	static_assert(!noexcept(v.insert(hamon::declval<std::tuple<char, double>>())), "");
	static_assert(!noexcept(v.insert(hamon::declval<std::tuple<char, float>>())), "");
	static_assert(!noexcept(v.insert(hamon::declval<std::array<int, 2>>())), "");
	static_assert(!noexcept(v.insert(hamon::declval<std::array<double, 2>>())), "");
	static_assert(!noexcept(v.insert(hamon::declval<std::array<char, 2>>())), "");
#endif

#if !defined(HAMON_USE_STD_MAP)
	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<hamon::pair<int, float>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<hamon::pair<char, double>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<hamon::pair<char, float>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<hamon::tuple<int, float>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<hamon::tuple<char, double>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<hamon::tuple<char, float>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<hamon::array<int, 2>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<hamon::array<double, 2>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<hamon::array<char, 2>>())), Result>::value, "");
	static_assert(!noexcept(v.insert(hamon::declval<hamon::pair<int, float>>())), "");
	static_assert(!noexcept(v.insert(hamon::declval<hamon::pair<char, double>>())), "");
	static_assert(!noexcept(v.insert(hamon::declval<hamon::pair<char, float>>())), "");
	static_assert(!noexcept(v.insert(hamon::declval<hamon::tuple<int, float>>())), "");
	static_assert(!noexcept(v.insert(hamon::declval<hamon::tuple<char, double>>())), "");
	static_assert(!noexcept(v.insert(hamon::declval<hamon::tuple<char, float>>())), "");
	static_assert(!noexcept(v.insert(hamon::declval<hamon::array<int, 2>>())), "");
	static_assert(!noexcept(v.insert(hamon::declval<hamon::array<double, 2>>())), "");
	static_assert(!noexcept(v.insert(hamon::declval<hamon::array<char, 2>>())), "");
#endif

	// from std::pair
	{
		auto r = v.insert(std::make_pair(1, 0.5f));
		VERIFY(r.first  == hamon::next(v.begin(), 0));
		VERIFY(r.second == true);

		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{1, 0.5});
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(std::make_pair(char{2}, 1.5));
		VERIFY(r.first  == hamon::next(v.begin(), 1));
		VERIFY(r.second == true);

		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{1, 0.5});
		VERIFY(*it++ == ValueType{2, 1.5});
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(std::make_pair(short{0}, 2.5));
		VERIFY(r.first  == hamon::next(v.begin(), 0));
		VERIFY(r.second == true);

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{0, 2.5});
		VERIFY(*it++ == ValueType{1, 0.5});
		VERIFY(*it++ == ValueType{2, 1.5});
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(std::make_pair(char{1}, 3.5f));
		VERIFY(r.first  == hamon::next(v.begin(), 1));
		VERIFY(r.second == false);

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{0, 2.5});
		VERIFY(*it++ == ValueType{1, 0.5});
		VERIFY(*it++ == ValueType{2, 1.5});
		VERIFY(it == v.end());
	}

#if !defined(HAMON_USE_STD_MAP) || (defined(__cpp_lib_tuple_like) && (__cpp_lib_tuple_like >= 202207L))
	// from std::tuple
	{
		auto r = v.insert(std::make_tuple(char{6}, 4.5f));
		VERIFY(r.first  == hamon::next(v.begin(), 3));
		VERIFY(r.second == true);

		VERIFY(v.size() == 4);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{0, 2.5});
		VERIFY(*it++ == ValueType{1, 0.5});
		VERIFY(*it++ == ValueType{2, 1.5});
		VERIFY(*it++ == ValueType{6, 4.5});
		VERIFY(it == v.end());
	}
	// from std::array
	{
		auto r = v.insert(std::array<int, 2>{3, 5});
		VERIFY(r.first  == hamon::next(v.begin(), 3));
		VERIFY(r.second == true);

		VERIFY(v.size() == 5);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{0, 2.5});
		VERIFY(*it++ == ValueType{1, 0.5});
		VERIFY(*it++ == ValueType{2, 1.5});
		VERIFY(*it++ == ValueType{3, 5.0});
		VERIFY(*it++ == ValueType{6, 4.5});
		VERIFY(it == v.end());
	}
#endif

#if !defined(HAMON_USE_STD_MAP)
	// from hamon::pair
	{
		auto r = v.insert(hamon::make_pair(4, 6.5f));
		VERIFY(r.first  == hamon::next(v.begin(), 4));
		VERIFY(r.second == true);

		VERIFY(v.size() == 6);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{0, 2.5});
		VERIFY(*it++ == ValueType{1, 0.5});
		VERIFY(*it++ == ValueType{2, 1.5});
		VERIFY(*it++ == ValueType{3, 5.0});
		VERIFY(*it++ == ValueType{4, 6.5});
		VERIFY(*it++ == ValueType{6, 4.5});
		VERIFY(it == v.end());
	}
	// from hamon::tuple
	{
		auto r = v.insert(hamon::make_tuple(7, 7.5f));
		VERIFY(r.first  == hamon::next(v.begin(), 6));
		VERIFY(r.second == true);

		VERIFY(v.size() == 7);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{0, 2.5});
		VERIFY(*it++ == ValueType{1, 0.5});
		VERIFY(*it++ == ValueType{2, 1.5});
		VERIFY(*it++ == ValueType{3, 5.0});
		VERIFY(*it++ == ValueType{4, 6.5});
		VERIFY(*it++ == ValueType{6, 4.5});
		VERIFY(*it++ == ValueType{7, 7.5});
		VERIFY(it == v.end());
	}
	// from hamon::array
	{
		auto r = v.insert(hamon::array<int, 2>{5, 8});
		VERIFY(r.first  == hamon::next(v.begin(), 5));
		VERIFY(r.second == true);

		VERIFY(v.size() == 8);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{0, 2.5});
		VERIFY(*it++ == ValueType{1, 0.5});
		VERIFY(*it++ == ValueType{2, 1.5});
		VERIFY(*it++ == ValueType{3, 5.0});
		VERIFY(*it++ == ValueType{4, 6.5});
		VERIFY(*it++ == ValueType{5, 8.0});
		VERIFY(*it++ == ValueType{6, 4.5});
		VERIFY(*it++ == ValueType{7, 7.5});
		VERIFY(it == v.end());
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, InsertHeterogeneousTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE(test1());

	S::s_ctor_count = 0;
	S::s_dtor_count = 0;
	{
		hamon::map<int, S> v;
		EXPECT_EQ(0u, v.size());
		EXPECT_EQ(0, S::s_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);

		v.insert(std::pair<int, int>{1, 10});
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(1, S::s_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);

#if 0	// 要素が挿入されないときに一時オブジェクトが作成されるかどうかは実装依存
		v.insert(std::pair<int, int>{1, 20});
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(1, S::s_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);
#endif

		v.insert(std::pair<int, int>{2, 30});
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(2, S::s_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);
	}
	EXPECT_EQ(2, S::s_ctor_count);
	EXPECT_EQ(2, S::s_dtor_count);

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::map<int, MayThrow> v;
		EXPECT_TRUE(v.empty());

		EXPECT_THROW(v.insert(std::pair<int, int>{1, -10}), MayThrow::Exception);
		EXPECT_EQ(0u, v.size());

		EXPECT_NO_THROW(v.insert(std::pair<int, int>{1, 10}));
		EXPECT_EQ(1u, v.size());

		EXPECT_THROW(v.insert(std::pair<int, int>{2, -10}), MayThrow::Exception);
		EXPECT_EQ(1u, v.size());

		EXPECT_NO_THROW(v.insert(std::pair<int, int>{2, 10}));
		EXPECT_EQ(2u, v.size());

#if 0	// 要素が挿入されないときに一時オブジェクトが作成されるかどうかは実装依存
		EXPECT_NO_THROW(v.insert(std::pair<int, int>{1, -10}));
		EXPECT_EQ(2u, v.size());
#endif

		EXPECT_NO_THROW(v.insert(std::pair<int, int>{1, 20}));
		EXPECT_EQ(2u, v.size());
	}
#endif
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace insert_heterogeneous_test

}	// namespace hamon_map_test
