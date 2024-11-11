/**
 *	@file	unit_test_map_insert_range.cpp
 *
 *	@brief	insert_range のテスト
 *
 *	template<container-compatible-range<value_type> R>
 *	void insert_range(R&& rg);
 */

#include <hamon/map/map.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

#if !defined(HAMON_USE_STD_MAP) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))

namespace hamon_map_test
{

namespace insert_range_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

#if !defined(HAMON_NO_EXCEPTIONS)
struct MayThrow
{
	struct Exception{};

	int value;

	MayThrow(int v) : value(v)
	{}

	MayThrow(MayThrow const& x)
		: value(x.value)
	{
		if (x.value < 0)
		{
			throw Exception{};
		}
	}

	MayThrow(MayThrow&&)                 = default;
	MayThrow& operator=(MayThrow&&)      = delete;
	MayThrow& operator=(MayThrow const&) = delete;
};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T, template <typename> class RangeWrapper>
MAP_TEST_CONSTEXPR bool test_impl()
{
	using Map = hamon::map<Key, T>;
	using ValueType = typename Map::value_type;
	using Range = RangeWrapper<ValueType>;

	Map v;

	static_assert(hamon::is_same<decltype(v.insert_range(hamon::declval<Range>())), void>::value, "");
	static_assert(!noexcept(v.insert_range(hamon::declval<Range>())), "");

	VERIFY(v.empty());

	{
		ValueType a[] =
		{
			{Key{3}, T{10}},
			{Key{2}, T{20}},
			{Key{3}, T{30}},
			{Key{1}, T{40}},
			{Key{2}, T{50}},
			{Key{3}, T{60}},
		};
		Range r(a);
		v.insert_range(r);
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		{
			auto it = v.begin();
			VERIFY(*it++ == ValueType{Key{1}, T{40}});
			VERIFY(*it++ == ValueType{Key{2}, T{20}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(it == v.end());
		}
	}
	{
		ValueType a[] =
		{
			{Key{2}, T{70}},
			{Key{4}, T{80}},
			{Key{0}, T{90}},
			{Key{1}, T{40}},
		};
		v.insert_range(Range(a));
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		{
			auto it = v.begin();
			VERIFY(*it++ == ValueType{Key{0}, T{90}});
			VERIFY(*it++ == ValueType{Key{1}, T{40}});
			VERIFY(*it++ == ValueType{Key{2}, T{20}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{4}, T{80}});
			VERIFY(it == v.end());
		}
	}

	return true;
}

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test()
{
	return
		test_impl<Key, T, test_input_range>() &&
		test_impl<Key, T, test_forward_range>() &&
		test_impl<Key, T, test_bidirectional_range>() &&
		test_impl<Key, T, test_random_access_range>() &&
		test_impl<Key, T, test_contiguous_range>() &&
		test_impl<Key, T, test_input_sized_range>() &&
		test_impl<Key, T, test_forward_sized_range>() &&
		test_impl<Key, T, test_bidirectional_sized_range>() &&
		test_impl<Key, T, test_random_access_sized_range>() &&
		test_impl<Key, T, test_contiguous_sized_range>();
}

#undef VERIFY

template <typename Key, typename T, typename C>
std::string ToString(const hamon::map<Key, T, C>& m)
{
	std::stringstream out;
	for (const auto& n : m)
	{
		out << "[" << n.first << "] = " << n.second << ", ";
	}
	return out.str();
}

GTEST_TEST(MapTest, InsertRangeTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		using Map = hamon::map<int, MayThrow>;
		using ValueType = typename Map::value_type;

		Map v;
		EXPECT_EQ(0u, v.size());

		{
			ValueType a[] =
			{
				{ 3, MayThrow{ 10}},
				{ 1, MayThrow{ 20}},
				{ 4, MayThrow{-30}},
				{ 1, MayThrow{ 40}},
			};
			EXPECT_THROW(v.insert_range(a), MayThrow::Exception);
		}
		EXPECT_EQ(2u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ( 1, it->first);
			EXPECT_EQ(20, it->second.value);
			++it;
			EXPECT_EQ( 3, it->first);
			EXPECT_EQ(10, it->second.value);
			++it;
			EXPECT_TRUE(it == v.end());
		}
		{
			ValueType a[] =
			{
				{ 1, MayThrow{ 50}},
				{ 2, MayThrow{ 60}},
				{ 3, MayThrow{-70}},
				{ 0, MayThrow{ 80}},
			};
			EXPECT_NO_THROW(v.insert_range(a));
		}
		EXPECT_EQ(4u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ( 0, it->first);
			EXPECT_EQ(80, it->second.value);
			++it;
			EXPECT_EQ( 1, it->first);
			EXPECT_EQ(20, it->second.value);
			++it;
			EXPECT_EQ( 2, it->first);
			EXPECT_EQ(60, it->second.value);
			++it;
			EXPECT_EQ( 3, it->first);
			EXPECT_EQ(10, it->second.value);
			++it;
			EXPECT_TRUE(it == v.end());
		}
	}
#endif

	// https://en.cppreference.com/w/cpp/container/map/insert_range
	{
		auto container = hamon::map<int, int> {std::pair<int, int> {1, 11}, {3, 33}, {2, 22}, {4, 44}};
		const auto rg = {std::pair<int, int> {-1, -11}, {3, -33}, {-2, -22}};
		container.insert_range(rg);
		EXPECT_EQ("[-2] = -22, [-1] = -11, [1] = 11, [2] = 22, [3] = 33, [4] = 44, ", ToString(container));
	}
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace insert_range_test

}	// namespace hamon_map_test

#endif
