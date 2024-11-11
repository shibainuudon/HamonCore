/**
 *	@file	unit_test_map_insert_iterator.cpp
 *
 *	@brief	insert のテスト
 *
 *	template<class InputIterator>
 *	void insert(InputIterator first, InputIterator last);
 */

#include <hamon/map/map.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_map_test
{

namespace insert_iterator_test
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

template <typename Key, typename T, template <typename> class IteratorWrapper>
MAP_TEST_CONSTEXPR bool test_impl()
{
	using Map = hamon::map<Key, T>;
	using ValueType = typename Map::value_type;
	using InputIterator = IteratorWrapper<ValueType>;

	Map v;

	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<InputIterator>(), hamon::declval<InputIterator>())), void>::value, "");
	static_assert(!noexcept(v.insert(hamon::declval<InputIterator>(), hamon::declval<InputIterator>())), "");

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
		v.insert(InputIterator{a}, InputIterator{a + 6});
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
		v.insert(InputIterator{a}, InputIterator{a + 4});
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
		test_impl<Key, T, cpp17_input_iterator_wrapper>() &&
		//test_impl<Key, T, input_iterator_wrapper>() &&
		test_impl<Key, T, forward_iterator_wrapper>() &&
		test_impl<Key, T, bidirectional_iterator_wrapper>() &&
		test_impl<Key, T, random_access_iterator_wrapper>() &&
		test_impl<Key, T, contiguous_iterator_wrapper>();
}

#undef VERIFY

GTEST_TEST(MapTest, InsertIteratorTest)
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
			EXPECT_THROW(v.insert(a, a + 4), MayThrow::Exception);
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
			EXPECT_NO_THROW(v.insert(a, a + 4));
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
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace insert_iterator_test

}	// namespace hamon_map_test
