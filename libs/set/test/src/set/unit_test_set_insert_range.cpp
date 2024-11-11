/**
 *	@file	unit_test_set_insert_range.cpp
 *
 *	@brief	insert_range のテスト
 *
 *	template<container-compatible-range<value_type> R>
 *	void insert_range(R&& rg);
 */

#include <hamon/set/set.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include <string>
#include <sstream>

#if !defined(HAMON_USE_STD_SET) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))

namespace hamon_set_test
{

namespace insert_range_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
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

	friend constexpr bool operator<(MayThrow const& lhs, MayThrow const& rhs)
	{
		return lhs.value < rhs.value;
	}
};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, template <typename> class RangeWrapper>
SET_TEST_CONSTEXPR bool test_impl()
{
	using Set = hamon::set<Key>;
	using ValueType = typename Set::value_type;
	using Range = RangeWrapper<ValueType>;

	Set v;

	static_assert(hamon::is_same<decltype(v.insert_range(hamon::declval<Range>())), void>::value, "");
	static_assert(!noexcept(v.insert_range(hamon::declval<Range>())), "");

	{
		Key a[] = { Key{3}, Key{2}, Key{3}, Key{1}, Key{2}, Key{3} };
		Range r(a);
		v.insert_range(r);
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		{
			auto it = v.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{2});
			VERIFY(*it++ == Key{3});
			VERIFY(it == v.end());
		}
	}
	{
		Key a[] = { Key{2}, Key{4}, Key{0}, Key{1} };
		v.insert_range(Range(a));
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		{
			auto it = v.begin();
			VERIFY(*it++ == Key{0});
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{2});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{4});
			VERIFY(it == v.end());
		}
	}

	return true;
}

template <typename Key>
SET_TEST_CONSTEXPR bool test()
{
	return
		test_impl<Key, test_input_range>() &&
		test_impl<Key, test_forward_range>() &&
		test_impl<Key, test_bidirectional_range>() &&
		test_impl<Key, test_random_access_range>() &&
		test_impl<Key, test_contiguous_range>() &&
		test_impl<Key, test_input_sized_range>() &&
		test_impl<Key, test_forward_sized_range>() &&
		test_impl<Key, test_bidirectional_sized_range>() &&
		test_impl<Key, test_random_access_sized_range>() &&
		test_impl<Key, test_contiguous_sized_range>();
}

#undef VERIFY

template <typename T, typename C>
std::string ToString(const hamon::set<T, C>& set)
{
	std::stringstream out;
	auto n = set.size();
	out << "{";
	for (auto const& elm : set)
	{
		out << elm << (--n ? ", " : "");
	}
	out << "}";
	return out.str();
}

GTEST_TEST(SetTest, InsertRangeTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		using Set = hamon::set<MayThrow>;

		Set v;
		EXPECT_EQ(0u, v.size());

		{
			MayThrow a[] =
			{
				MayThrow{ 40},
				MayThrow{ 10},
				MayThrow{-30},
				MayThrow{ 20},
			};
			EXPECT_THROW(v.insert_range(a), MayThrow::Exception);
		}
		EXPECT_EQ(2u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ(10, (it++)->value);
			EXPECT_EQ(40, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		v.emplace(-20);
		EXPECT_EQ(3u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ(-20, (it++)->value);
			EXPECT_EQ( 10, (it++)->value);
			EXPECT_EQ( 40, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		{
			MayThrow a[] =
			{
				MayThrow{ 20},
				MayThrow{-20},
				MayThrow{ 30},
			};
			EXPECT_NO_THROW(v.insert_range(a));
		}
		EXPECT_EQ(5u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ(-20, (it++)->value);
			EXPECT_EQ( 10, (it++)->value);
			EXPECT_EQ( 20, (it++)->value);
			EXPECT_EQ( 30, (it++)->value);
			EXPECT_EQ( 40, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}
	}
#endif

	// https://en.cppreference.com/w/cpp/container/set/insert_range
	{
		auto container = hamon::set<int> {1, 3, 2, 4};
		const auto rg = {-1, 3, -2};
		container.insert_range(rg);
		EXPECT_EQ("{-2, -1, 1, 2, 3, 4}", ToString(container));
	}
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace insert_range_test

}	// namespace hamon_set_test

#endif
