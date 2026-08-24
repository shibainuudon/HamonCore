/**
 *	@file	unit_test_unordered_map_at.cpp
 *
 *	@brief	at のテスト
 *
 *	constexpr mapped_type& at(const key_type& k);
 *	constexpr const mapped_type& at(const key_type& k) const;
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_map_test
{

namespace at_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Map = hamon::unordered_map<Key, T>;
	using MappedType = typename Map::mapped_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().at(hamon::declval<Key const&>())), MappedType&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().at(hamon::declval<Key const&>())), MappedType const&>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().at(hamon::declval<Key const&>())), "");
	static_assert(!noexcept(hamon::declval<Map const&>().at(hamon::declval<Key const&>())), "");

	{
		Map v
		{
			{Key{2}, T{10}},
			{Key{1}, T{20}},
			{Key{3}, T{30}},
		};

		VERIFY(v.at(Key{1}) == T{20});
		VERIFY(v.at(Key{2}) == T{10});
		VERIFY(v.at(Key{3}) == T{30});

		v.at(Key{2}) = T{40};

		VERIFY(v.at(Key{1}) == T{20});
		VERIFY(v.at(Key{2}) == T{40});
		VERIFY(v.at(Key{3}) == T{30});
	}
	{
		Map const v
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
			{Key{4}, T{30}},
		};

		VERIFY(v.at(Key{1}) == T{20});
		VERIFY(v.at(Key{3}) == T{10});
		VERIFY(v.at(Key{4}) == T{30});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, AtTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

#if !defined(HAMON_NO_EXCEPTIONS)
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4834)	// 'nodiscard' 属性を持つ関数の戻り値を破棄しています
HAMON_WARNING_DISABLE_CLANG("-Wunused-result")
HAMON_WARNING_DISABLE_GCC("-Wunused-result")
	{
		hamon::unordered_map<int, float> v
		{
			{ 1, 0.5f },
			{ 7, 1.5f },
			{ 3, 2.5f },
		};

		EXPECT_THROW   (v.at(0), hamon::out_of_range);
		EXPECT_NO_THROW(v.at(1));
		EXPECT_THROW   (v.at(2), hamon::out_of_range);
		EXPECT_NO_THROW(v.at(3));

		v[0] = 3.5f;

		EXPECT_NO_THROW(v.at(0));
		EXPECT_NO_THROW(v.at(1));
		EXPECT_THROW   (v.at(2), hamon::out_of_range);
		EXPECT_NO_THROW(v.at(3));
	}
	{
		hamon::unordered_map<int, float> const v
		{
			{ 2, 0.5f },
			{ 0, 1.5f },
			{ 3, 2.5f },
		};

		EXPECT_NO_THROW(v.at(0));
		EXPECT_THROW   (v.at(1), hamon::out_of_range);
		EXPECT_NO_THROW(v.at(2));
		EXPECT_NO_THROW(v.at(3));
	}
HAMON_WARNING_POP()
#endif
}

}	// namespace at_test

}	// namespace hamon_unordered_map_test
