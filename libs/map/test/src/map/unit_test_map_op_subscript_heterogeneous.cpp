/**
 *	@file	unit_test_map_op_subscript_heterogeneous.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	template<class K> mapped_type& operator[](K&& x);
 */

#include <hamon/map/map.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_MAP) || \
	(defined(__cpp_lib_associative_heterogeneous_insertion) && (__cpp_lib_associative_heterogeneous_insertion >= 202306L))

namespace hamon_map_test
{

namespace op_subscript_heterogeneous_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

struct Key
{
	int value;

	explicit constexpr Key(int v) : value(v) {}

	friend constexpr bool operator==(Key const& lhs, Key const& rhs)
	{
		return lhs.value == rhs.value;
	}

	friend constexpr bool operator==(Key const& lhs, int rhs)
	{
		return lhs.value == rhs;
	}

	friend constexpr bool operator<(Key const& lhs, Key const& rhs)
	{
		return lhs.value < rhs.value;
	}

	friend constexpr bool operator<(Key const& lhs, int rhs)
	{
		return lhs.value < rhs;
	}

	friend constexpr bool operator<(int lhs, Key const& rhs)
	{
		return lhs < rhs.value;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
MAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::map<Key, T, hamon::less<>>;
	using MappedType = typename Map::mapped_type;
	using ValueType = typename Map::value_type;

	{
		Map v;
		static_assert(hamon::is_same<decltype(v[hamon::declval<int const&>()]), MappedType&>::value, "");
		static_assert(hamon::is_same<decltype(v[hamon::declval<int&&>()]), MappedType&>::value, "");
		static_assert(!noexcept(v[hamon::declval<int const&>()]), "");
		static_assert(!noexcept(v[hamon::declval<int&&>()]), "");
	}

	Map v
	{
		{Key{1}, T{10}},
		{Key{3}, T{20}},
	};

	{
		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(*it++ == ValueType{Key{3}, T{20}});
		VERIFY(it == v.end());
	}

	v[1] = T{30};
	{
		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{30}});
		VERIFY(*it++ == ValueType{Key{3}, T{20}});
		VERIFY(it == v.end());
	}

	v[2] = T{40};
	{
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{30}});
		VERIFY(*it++ == ValueType{Key{2}, T{40}});
		VERIFY(*it++ == ValueType{Key{3}, T{20}});
		VERIFY(it == v.end());
	}

	{
		int const k{3};
		v[k] = T{50};
	}
	{
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{30}});
		VERIFY(*it++ == ValueType{Key{2}, T{40}});
		VERIFY(*it++ == ValueType{Key{3}, T{50}});
		VERIFY(it == v.end());
	}

	{
		int const k{0};
		v[k] = T{60};
	}
	{
		VERIFY(v.size() == 4);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{0}, T{60}});
		VERIFY(*it++ == ValueType{Key{1}, T{30}});
		VERIFY(*it++ == ValueType{Key{2}, T{40}});
		VERIFY(*it++ == ValueType{Key{3}, T{50}});
		VERIFY(it == v.end());
	}

	VERIFY(v[0] == T{60});
	VERIFY(v[1] == T{30});
	VERIFY(v[2] == T{40});
	VERIFY(v[3] == T{50});
	VERIFY(v[4] == T{});
	{
		VERIFY(v.size() == 5);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{0}, T{60}});
		VERIFY(*it++ == ValueType{Key{1}, T{30}});
		VERIFY(*it++ == ValueType{Key{2}, T{40}});
		VERIFY(*it++ == ValueType{Key{3}, T{50}});
		VERIFY(*it++ == ValueType{Key{4}, T{}});
		VERIFY(it == v.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, OpSubscriptHeterogeneousTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace op_subscript_heterogeneous_test

}	// namespace hamon_map_test

#endif
