/**
 *	@file	unit_test_unordered_multimap_insert_heterogeneous.cpp
 *
 *	@brief	insert のテスト
 *
 *	template<class P> constexpr iterator insert(P&& obj);
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/array.hpp>
#include <hamon/pair.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include <array>
#include <tuple>
#include <utility>
#include "constexpr_test.hpp"
#include "unordered_multimap_test_helper.hpp"

namespace hamon_unordered_multimap_test
{

namespace insert_heterogeneous_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '初期化中': '_Ty' から '_Ty2' への変換です。データが失われる可能性があります。

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::unordered_multimap<Key, T>;
	using Iterator = typename Map::iterator;

	// from std::pair

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::pair<int, float>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::pair<char, int>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::pair<float, char>>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::pair<int, float>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::pair<char, int>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::pair<float, char>>())), "");

	{
		Map v;
		v.max_load_factor(0.1f);

		{
			auto r = v.insert(std::make_pair(1, 0.5f));
			VERIFY(r->first == 1);
			VERIFY(r->second == 0.5);

			VERIFY(v.size() == 1);
			VERIFY(v.load_factor() <= v.max_load_factor());
		}
		{
			auto r = v.insert(std::make_pair(char{2}, 1.5));
			VERIFY(r->first == 2);
			VERIFY(r->second == 1.5);

			VERIFY(v.size() == 2);
			VERIFY(v.load_factor() <= v.max_load_factor());
		}
		{
			auto r = v.insert(std::make_pair(short{0}, 2.5));
			VERIFY(r->first == 0);
			VERIFY(r->second == 2.5);

			VERIFY(v.size() == 3);
			VERIFY(v.load_factor() <= v.max_load_factor());
		}
		{
			auto r = v.insert(std::make_pair(char{1}, 3.5f));
			VERIFY(r->first == 1);
			VERIFY(r->second == 3.5);

			VERIFY(v.size() == 4);
			VERIFY(v.load_factor() <= v.max_load_factor());
		}

		for (int i = 0; i < 100; ++i)
		{
			auto r = v.insert(std::make_pair(i, 4.5f));
			VERIFY(r->first == static_cast<Key>(i));
			VERIFY(r->second == 4.5);

			VERIFY(v.load_factor() <= v.max_load_factor());
		}
	}

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) || (defined(__cpp_lib_tuple_like) && (__cpp_lib_tuple_like >= 202207L))
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::tuple<int, float>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::tuple<char, double>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::tuple<char, float>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::array<int, 2>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::array<double, 2>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::array<char, 2>>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::tuple<int, float>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::tuple<char, double>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::tuple<char, float>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::array<int, 2>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::array<double, 2>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::array<char, 2>>())), "");

	{
		Map v;

		// from std::tuple
		{
			auto r = v.insert(std::make_tuple(char{6}, 4.5f));
			VERIFY(r->first == 6);
			VERIFY(r->second == 4.5);

			VERIFY(v.size() == 1);
			VERIFY(v.load_factor() <= v.max_load_factor());
		}
		// from std::array
		{
			auto r = v.insert(std::array<int, 2>{3, 5});
			VERIFY(r->first == 3);
			VERIFY(r->second == 5.0);

			VERIFY(v.size() == 2);
			VERIFY(v.load_factor() <= v.max_load_factor());
		}
	}
#endif

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<hamon::pair<int, float>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<hamon::pair<char, double>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<hamon::pair<char, float>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<hamon::tuple<int, float>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<hamon::tuple<char, double>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<hamon::tuple<char, float>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<hamon::array<int, 2>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<hamon::array<double, 2>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<hamon::array<char, 2>>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<hamon::pair<int, float>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<hamon::pair<char, double>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<hamon::pair<char, float>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<hamon::tuple<int, float>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<hamon::tuple<char, double>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<hamon::tuple<char, float>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<hamon::array<int, 2>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<hamon::array<double, 2>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<hamon::array<char, 2>>())), "");

	{
		Map v;

		// from hamon::pair
		{
			auto r = v.insert(hamon::make_pair(4, 6.5f));
			VERIFY(r->first == 4);
			VERIFY(r->second == 6.5);

			VERIFY(v.size() == 1);
			VERIFY(v.load_factor() <= v.max_load_factor());
		}
		// from hamon::tuple
		{
			auto r = v.insert(hamon::make_tuple(7, 7.5f));
			VERIFY(r->first == 7);
			VERIFY(r->second == 7.5);

			VERIFY(v.size() == 2);
			VERIFY(v.load_factor() <= v.max_load_factor());
		}
		// from hamon::array
		{
			auto r = v.insert(hamon::array<int, 2>{5, 8});
			VERIFY(r->first == 5);
			VERIFY(r->second == 8.0);

			VERIFY(v.size() == 3);
			VERIFY(v.load_factor() <= v.max_load_factor());
		}
	}
#endif

	return true;
}

HAMON_WARNING_POP()

template <typename Map, typename P, typename = void>
struct is_insert_invocable
	: public hamon::false_type {};

template <typename Map, typename P>
struct is_insert_invocable<Map, P, hamon::void_t<decltype(hamon::declval<Map>().insert(hamon::declval<P>()))>>
	: public hamon::true_type {};

struct S1
{
	explicit S1(int);
};

struct S2
{
	explicit S2(S1 const&);
};

UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test2()
{
	using Map1 = hamon::unordered_multimap<int, S1>;
	using Map2 = hamon::unordered_multimap<int, S2>;

	static_assert( is_insert_invocable<Map1&, std::pair<int, int>>::value, "");
	static_assert(!is_insert_invocable<Map2&, std::pair<int, int>>::value, "");
	static_assert( is_insert_invocable<Map2&, std::pair<int, S1>>::value, "");

	static_assert(!is_insert_invocable<Map1 const&, std::pair<int, int>>::value, "");
	static_assert(!is_insert_invocable<Map2 const&, std::pair<int, int>>::value, "");
	static_assert(!is_insert_invocable<Map2 const&, std::pair<int, S1>>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, InsertHeterogeneousTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, double>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, double>()));

	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test2());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::unordered_multimap<int, ThrowIfNegative> v;
		EXPECT_TRUE(v.empty());

		EXPECT_THROW(v.insert(std::pair<int, int>{1, -10}), ThrowIfNegative::Exception);
		EXPECT_EQ(0u, v.size());

		EXPECT_NO_THROW(v.insert(std::pair<int, int>{1, 10}));
		EXPECT_EQ(1u, v.size());

		EXPECT_THROW(v.insert(std::pair<int, int>{2, -10}), ThrowIfNegative::Exception);
		EXPECT_EQ(1u, v.size());

		EXPECT_NO_THROW(v.insert(std::pair<int, int>{2, 10}));
		EXPECT_EQ(2u, v.size());

		EXPECT_THROW(v.insert(std::pair<int, int>{1, -10}), ThrowIfNegative::Exception);
		EXPECT_EQ(2u, v.size());

		EXPECT_NO_THROW(v.insert(std::pair<int, int>{1, 20}));
		EXPECT_EQ(3u, v.size());
	}
#endif
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace insert_heterogeneous_test

}	// namespace hamon_unordered_multimap_test
