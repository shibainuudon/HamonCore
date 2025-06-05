/**
 *	@file	unit_test_flat_map_emplace.cpp
 *
 *	@brief	emplace のテスト
 *
 *	template<class... Args>
 *	constexpr pair<iterator, bool> emplace(Args&&... args);
 */

#include <hamon/flat_map/flat_map.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace emplace_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_map<Key, T, Compare, KeyContainer, MappedContainer>;
	using ValueType = typename Map::value_type;
	using Iterator = typename Map::iterator;
#if defined(HAMON_USE_STD_FLAT_MAP)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace()), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace(hamon::declval<ValueType const&>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace(hamon::declval<ValueType&&>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace(hamon::declval<Key>(), hamon::declval<T>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace()), "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace(hamon::declval<ValueType const&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace(hamon::declval<ValueType&&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace(hamon::declval<Key>(), hamon::declval<T>())), "");

	Map v;
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 0);
	{
		auto r = v.emplace(Key{1}, T{10});
		VERIFY(r.first->first == Key{1});
		VERIFY(r.first->second == T{10});
		VERIFY(r.second == true);
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 1);
	VERIFY(v.at(1) == 10);
	{
		auto r = v.emplace(Key{1}, T{20});
		VERIFY(r.first->first == Key{1});
		VERIFY(r.first->second == T{10});
		VERIFY(r.second == false);
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 1);
	VERIFY(v.at(1) == 10);
	{
		ValueType const t{Key{2}, T{30}};
		auto r = v.emplace(t);
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{30});
		VERIFY(r.second == true);
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	VERIFY(v.at(1) == 10);
	VERIFY(v.at(2) == 30);
	{
		ValueType const t{Key{2}, T{40}};
		auto r = v.emplace(t);
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{30});
		VERIFY(r.second == false);
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	VERIFY(v.at(1) == 10);
	VERIFY(v.at(2) == 30);
	{
		ValueType t{Key{2}, T{50}};
		auto r = v.emplace(hamon::move(t));
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{30});
		VERIFY(r.second == false);
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	VERIFY(v.at(1) == 10);
	VERIFY(v.at(2) == 30);
	{
		ValueType t{Key{0}, T{60}};
		auto r = v.emplace(hamon::move(t));
		VERIFY(r.first->first == Key{0});
		VERIFY(r.first->second == T{60});
		VERIFY(r.second == true);
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 3);
	VERIFY(v.at(0) == 60);
	VERIFY(v.at(1) == 10);
	VERIFY(v.at(2) == 30);

	return true;
}

template <typename Void, typename T, typename... Args>
struct is_emplace_invocable_impl
	: hamon::false_type {};

template <typename T, typename... Args>
struct is_emplace_invocable_impl<
	hamon::void_t<decltype(hamon::declval<T>().emplace(hamon::declval<Args>()...))>, T, Args...>
	: hamon::true_type {};

template <typename T, typename... Args>
using is_emplace_invocable = is_emplace_invocable_impl<void, T, Args...>;

struct S1
{
	int x;
	int y;

	constexpr S1(int i, int j) : x(i), y(j) {}
};

FLAT_MAP_TEST_CONSTEXPR bool test2()
{
#if defined(HAMON_USE_STD_FLAT_MAP)
	namespace ns = std;
#else
	namespace ns = hamon;
#endif

	using Map = hamon::flat_map<int, S1>;

	static_assert( is_emplace_invocable<Map&, int, S1>::value, "");
	static_assert(!is_emplace_invocable<Map&, int, int>::value, "");
	static_assert(!is_emplace_invocable<Map&, int, int, int>::value, "");
	static_assert( is_emplace_invocable<Map&, ns::piecewise_construct_t, ns::tuple<int>, ns::tuple<int, int>>::value, "");
	static_assert(!is_emplace_invocable<Map const&, int, S1>::value, "");
	static_assert(!is_emplace_invocable<Map const&, int, int>::value, "");
	static_assert(!is_emplace_invocable<Map const&, int, int, int>::value, "");
	static_assert(!is_emplace_invocable<Map const&, ns::piecewise_construct_t, ns::tuple<int>, ns::tuple<int, int>>::value, "");

	Map v;

	{
		auto r = v.emplace(
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(10, 20));
		VERIFY(r.first->first == 1);
		VERIFY(r.first->second.x == 10);
		VERIFY(r.first->second.y == 20);
		VERIFY(r.second == true);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 1);
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
	}
	{
		auto r = v.emplace(
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(30, 40));
		VERIFY(r.first->first == 1);
		VERIFY(r.first->second.x == 10);
		VERIFY(r.first->second.y == 20);
		VERIFY(r.second == false);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 1);
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
	}
	{
		auto r = v.emplace(
			ns::piecewise_construct,
			ns::forward_as_tuple(2),
			ns::forward_as_tuple(50, 60));
		VERIFY(r.first->first == 2);
		VERIFY(r.first->second.x == 50);
		VERIFY(r.first->second.y == 60);
		VERIFY(r.second == true);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 2);
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
		VERIFY(v.at(2).x == 50);
		VERIFY(v.at(2).y == 60);
	}

	return true;
}

template <typename KeyContainer, typename MappedContainer>
FLAT_MAP_TEST_CONSTEXPR bool test3()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_map<Key, T, hamon::less<Key>, KeyContainer, MappedContainer>;
	using ValueType = typename Map::value_type;

	{
		// was empty
		Map m;
		auto r = m.emplace(ValueType(2, 3.5));
		VERIFY(r.second);
		VERIFY(r.first == m.begin());
		VERIFY(m.size() == 1);
		VERIFY(r.first->first == 2);
		VERIFY(r.first->second == 3.5);
	}
	{
		// key does not exist and inserted at the begin
		Map m = {{3, 4.0}, {5, 3.0}, {6, 1.0}, {7, 0.0}};
		auto r = m.emplace(ValueType(2, 2.0));
		VERIFY(r.second);
		VERIFY(r.first == m.begin());
		VERIFY(m.size() == 5);
		VERIFY(r.first->first == 2);
		VERIFY(r.first->second == 2.0);
	}
	{
		// key does not exist and inserted in the middle
		Map m = {{0, 4.0}, {1, 3.0}, {3, 1.0}, {4, 0.0}};
		auto r = m.emplace(ValueType(2, 2.0));
		VERIFY(r.second);
		VERIFY(r.first == m.begin() + 2);
		VERIFY(m.size() == 5);
		VERIFY(r.first->first == 2);
		VERIFY(r.first->second == 2.0);
	}
	{
		// key does not exist and inserted at the end
		Map m = {{0, 4.0}, {1, 3.0}};
		auto r = m.emplace(ValueType(2, 2.0));
		VERIFY(r.second);
		VERIFY(r.first == m.begin() + 2);
		VERIFY(m.size() == 3);
		VERIFY(r.first->first == 2);
		VERIFY(r.first->second == 2.0);
	}
	{
		// key already exists and original at the begin
		Map m = {{2, 4.0}, {3, 3.0}, {5, 1.0}, {6, 0.0}};
		auto r = m.emplace(ValueType(2, 2.0));
		VERIFY(!r.second);
		VERIFY(r.first == m.begin());
		VERIFY(m.size() == 4);
		VERIFY(r.first->first == 2);
		VERIFY(r.first->second == 4.0);
	}
	{
		// key already exists and original in the middle
		Map m = {{0, 4.0}, {2, 3.0}, {3, 1.0}, {4, 0.0}};
		auto r = m.emplace(ValueType(2, 2.0));
		VERIFY(!r.second);
		VERIFY(r.first == m.begin() + 1);
		VERIFY(m.size() == 4);
		VERIFY(r.first->first == 2);
		VERIFY(r.first->second == 3.0);
	}
	{
		// key already exists and original at the end
		Map m = {{0, 4.0}, {1, 3.0}, {2, 1.0}};
		auto r = m.emplace(ValueType(2, 2.0));
		VERIFY(!r.second);
		VERIFY(r.first == m.begin() + 2);
		VERIFY(m.size() == 3);
		VERIFY(r.first->first == 2);
		VERIFY(r.first->second == 1.0);
	}

	return true;
}

#undef VERIFY

template <template <typename...> class TKeyContainer, template <typename...> class TValueContainer>
void test_exceptions()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	using Key = int;
	using T = int;
	using Comp = hamon::less<Key>;
	{
		using KeyContainer = TKeyContainer<Key, ThrowAllocator<Key>>;
		using ValueContainer = TValueContainer<T>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;
		using ValueType = typename Map::value_type;

		int throw_after = INT_MAX;

		KeyContainer   a({Key{1}, Key{2}, Key{3}, Key{4}}, ThrowAllocator<Key>{&throw_after});
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		throw_after = 1;

		EXPECT_THROW(v.emplace(ValueType(0, 0)), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key>;
		using ValueContainer = TValueContainer<T, ThrowAllocator<T>>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;
		using ValueType = typename Map::value_type;

		int throw_after = INT_MAX;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b({5, 6, 7, 8}, ThrowAllocator<T>{&throw_after});
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		throw_after = 1;

		EXPECT_THROW(v.emplace(ValueType(0, 0)), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = EmplaceUnsafeContainer<Key>;
		using ValueContainer = TValueContainer<T>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;
		using ValueType = typename Map::value_type;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		EXPECT_THROW(v.emplace(ValueType(0, 0)), int);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key>;
		using ValueContainer = EmplaceUnsafeContainer<T>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;
		using ValueType = typename Map::value_type;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		EXPECT_THROW(v.emplace(ValueType(0, 0)), int);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = ThrowOnEraseContainer<Key>;
		using ValueContainer = TValueContainer<T, ThrowAllocator<T>>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;
		using ValueType = typename Map::value_type;

		int throw_after = INT_MAX;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b({5, 6, 7, 8}, ThrowAllocator<T>{&throw_after});
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		throw_after = 1;

		EXPECT_THROW(v.emplace(ValueType(0, 0)), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key, ThrowAllocator<Key>>;
		using ValueContainer = ThrowOnEraseContainer<T>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;
		using ValueType = typename Map::value_type;

		int throw_after = INT_MAX;

		KeyContainer   a({Key{1}, Key{2}, Key{3}, Key{4}}, ThrowAllocator<Key>{&throw_after});
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		throw_after = 1;

		EXPECT_THROW(v.emplace(ValueType(0, 0)), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMapTest, EmplaceTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));

	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test2());

	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<hamon::vector<int>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<hamon::vector<int>, hamon::deque<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<hamon::vector<int>, MinSequenceContainer<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<hamon::deque<int>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<hamon::deque<int>, hamon::deque<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<hamon::deque<int>, MinSequenceContainer<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<MinSequenceContainer<int>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<MinSequenceContainer<int>, hamon::deque<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<MinSequenceContainer<int>, MinSequenceContainer<double>>()));

	test_exceptions<hamon::vector, hamon::vector>();
	test_exceptions<hamon::deque, hamon::deque>();

	{
#if defined(HAMON_USE_STD_FLAT_MAP)
		namespace ns = std;
#else
		namespace ns = hamon;
#endif

		struct Point
		{
			int x, y;
			Point(int x_, int y_) : x(x_), y(y_) {}
		};

		hamon::flat_map<hamon::string, Point> fm;

		fm.emplace(
			ns::piecewise_construct,
			ns::forward_as_tuple(static_cast<hamon::size_t>(3), 'C'), // キーの型std::stringのコンストラクタ引数を渡す
			ns::forward_as_tuple(1, 2));  // 値の型Pointのコンストラクタ引数を渡す

		fm.emplace(
			ns::piecewise_construct,
			ns::forward_as_tuple(static_cast<hamon::size_t>(3), 'A'),
			ns::forward_as_tuple(3, 4));

		fm.emplace(
			ns::piecewise_construct,
			ns::forward_as_tuple(static_cast<hamon::size_t>(3), 'C'),
			ns::forward_as_tuple(7, 8));

		fm.emplace(
			ns::piecewise_construct,
			ns::forward_as_tuple(static_cast<hamon::size_t>(3), 'B'),
			ns::forward_as_tuple(5, 6));

		std::stringstream ss;
		for (const auto& p : fm)
		{
			ss << p.first << ":(" << p.second.x << ", " << p.second.y << ')' << ", ";
		}
		EXPECT_EQ("AAA:(3, 4), BBB:(5, 6), CCC:(1, 2), ", ss.str());
	}
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace emplace_test

}	// namespace hamon_flat_map_test
