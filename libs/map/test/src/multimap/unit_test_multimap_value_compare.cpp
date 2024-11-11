/**
 *	@file	unit_test_multimap_value_compare.cpp
 *
 *	@brief	value_compare のテスト
 *
 *	class value_compare {
 *	protected:
 *		Compare comp;
 *		value_compare(Compare c) : comp(c) { }
 *
 *	public:
 *		bool operator()(const value_type& x, const value_type& y) const {
 *			return comp(x.first, y.first);
 *		}
 *	};
 */

#include <hamon/map/multimap.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multimap_test
{

namespace value_compare_test
{

#if !defined(HAMON_USE_STD_MULTIMAP)
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::multimap<Key, T>;
	using ValueCompare = typename Map::value_compare;
	using ValueType = typename Map::value_type;

	static_assert(!hamon::is_default_constructible<ValueCompare>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<ValueCompare>()(hamon::declval<ValueType>(), hamon::declval<ValueType>())),
		bool>::value, "");

	Map const m;
	ValueCompare const comp = m.value_comp();
	VERIFY(!comp(ValueType{Key{0}, T{10}}, ValueType{Key{0}, T{10}}));
	VERIFY( comp(ValueType{Key{0}, T{10}}, ValueType{Key{1}, T{10}}));
	VERIFY(!comp(ValueType{Key{1}, T{10}}, ValueType{Key{0}, T{10}}));
	VERIFY(!comp(ValueType{Key{1}, T{10}}, ValueType{Key{1}, T{10}}));

	return true;
}

#undef VERIFY

GTEST_TEST(MultimapTest, ValueCompareTest)
{
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace value_compare_test

}	// namespace hamon_multimap_test
