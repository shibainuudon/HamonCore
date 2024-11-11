/**
 *	@file	unit_test_multimap_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	void swap(multimap&)
 *		noexcept(allocator_traits<Allocator>::is_always_equal::value &&
 *			is_nothrow_swappable_v<Compare>);
 *
 *	template<class Key, class T, class Compare, class Allocator>
 *	void swap(multimap<Key, T, Compare, Allocator>& x,
 *			multimap<Key, T, Compare, Allocator>& y)
 *		noexcept(noexcept(x.swap(y)));
 */

#include <hamon/map/multimap.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include <string>
#include <sstream>

namespace hamon_multimap_test
{

namespace swap_test
{

#if !defined(HAMON_USE_STD_MULTIMAP)
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR              /**/
#endif

template <typename T>
struct MyAllocator
{
	using value_type = T;
#if !defined(HAMON_USE_STD_MULTIMAP)
	using is_always_equal = hamon::false_type;
	using propagate_on_container_swap = hamon::true_type;
#else
	using is_always_equal = std::false_type;
	using propagate_on_container_swap = std::true_type;
#endif

	int id;

	HAMON_CXX11_CONSTEXPR
	MyAllocator() : id(0) {}

	HAMON_CXX11_CONSTEXPR
	MyAllocator(int i) : id(i) {}

	template <typename U>
	HAMON_CXX11_CONSTEXPR
	MyAllocator(MyAllocator<U> const& a) : id(a.id) {}

	HAMON_CXX20_CONSTEXPR
	T* allocate(hamon::size_t n)
	{
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}

	HAMON_CXX20_CONSTEXPR
	void deallocate(T* p, hamon::size_t n)
	{
		// [allocator.members]/11
		::operator delete(p);
		(void)n;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(MyAllocator const& rhs) const
	{
		return id == rhs.id;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator!=(MyAllocator const& rhs) const
	{
		return id != rhs.id;
	}
};

struct MyLess
{
	int id;

	HAMON_CXX11_CONSTEXPR
	MyLess() : id(0) {}

	HAMON_CXX11_CONSTEXPR
	MyLess(int i) : id(i) {}

	template <typename T>
	HAMON_CXX11_CONSTEXPR
	bool operator()(T const& x, T const& y) const
	{
		return x < y;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(MyLess const& rhs) const
	{
		return id == rhs.id;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::multimap<Key, T>;
	using ValueType = typename Map::value_type;

	{
		Map v;
		static_assert(hamon::is_same<decltype(v.swap(v)), void>::value, "");
		static_assert(hamon::is_same<decltype(swap(v, v)), void>::value, "");
#if !defined(HAMON_USE_STD_MULTIMAP) && (HAMON_CXX_STANDARD >= 17)
		static_assert(noexcept(v.swap(v)), "");
		static_assert(noexcept(swap(v, v)), "");
#endif
	}
	{
		Map v1
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
			{Key{4}, T{30}},
			{Key{1}, T{40}},
			{Key{5}, T{50}},
			{Key{2}, T{60}},
		};
		Map v2
		{
			{Key{1}, T{70}},
			{Key{7}, T{80}},
			{Key{3}, T{90}},
		};

		v1.swap(v2);
		VERIFY(v1.size() == 3);
		VERIFY(v2.size() == 6);
		{
			auto it = v1.begin();
			VERIFY(*it++ == ValueType{Key{1}, T{70}});
			VERIFY(*it++ == ValueType{Key{3}, T{90}});
			VERIFY(*it++ == ValueType{Key{7}, T{80}});
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(*it++ == ValueType{Key{1}, T{40}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(it == v2.end());
		}

		swap(v1, v2);
		VERIFY(v1.size() == 6);
		VERIFY(v2.size() == 3);
		{
			auto it = v1.begin();
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(*it++ == ValueType{Key{1}, T{40}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == ValueType{Key{1}, T{70}});
			VERIFY(*it++ == ValueType{Key{3}, T{90}});
			VERIFY(*it++ == ValueType{Key{7}, T{80}});
			VERIFY(it == v2.end());
		}
	}

	return true;
}

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test2()
{
#if defined(HAMON_USE_STD_MULTIMAP)
	using ValueType = std::pair<Key const, T>;
#else
	using ValueType = hamon::pair<Key const, T>;
#endif
	using Compare = MyLess;
	using Allocator = MyAllocator<ValueType>;
	using Map = hamon::multimap<Key, T, Compare, Allocator>;

	{
		Map v;
		static_assert(hamon::is_same<decltype(v.swap(v)), void>::value, "");
		static_assert(hamon::is_same<decltype(swap(v, v)), void>::value, "");
#if !defined(HAMON_USE_STD_MULTIMAP)
		static_assert(!noexcept(v.swap(v)), "");
		static_assert(!noexcept(swap(v, v)), "");
#endif
	}
	{
		Compare c1{10};
		Compare c2{20};
		Allocator a1{30};
		Allocator a2{40};
		Map v1
		{
			{
				{Key{3}, T{10}},
				{Key{1}, T{20}},
				{Key{4}, T{30}},
				{Key{1}, T{40}},
				{Key{5}, T{50}},
				{Key{2}, T{60}},
			},
			c1, a1
		};
		Map v2
		{
			{
				{Key{1}, T{70}},
				{Key{7}, T{80}},
				{Key{3}, T{90}},
			},
			c2, a2
		};

		v1.swap(v2);
		VERIFY(v1.size() == 3);
		VERIFY(v2.size() == 6);
		VERIFY(v1.key_comp() == c2);
		VERIFY(v2.key_comp() == c1);
		VERIFY(v1.get_allocator() == a2);
		VERIFY(v2.get_allocator() == a1);
		{
			auto it = v1.begin();
			VERIFY(*it++ == ValueType{Key{1}, T{70}});
			VERIFY(*it++ == ValueType{Key{3}, T{90}});
			VERIFY(*it++ == ValueType{Key{7}, T{80}});
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(*it++ == ValueType{Key{1}, T{40}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(it == v2.end());
		}

		swap(v1, v2);
		VERIFY(v1.size() == 6);
		VERIFY(v2.size() == 3);
		VERIFY(v1.key_comp() == c1);
		VERIFY(v2.key_comp() == c2);
		VERIFY(v1.get_allocator() == a1);
		VERIFY(v2.get_allocator() == a2);
		{
			auto it = v1.begin();
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(*it++ == ValueType{Key{1}, T{40}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == ValueType{Key{1}, T{70}});
			VERIFY(*it++ == ValueType{Key{3}, T{90}});
			VERIFY(*it++ == ValueType{Key{7}, T{80}});
			VERIFY(it == v2.end());
		}
	}

	return true;
}

#undef VERIFY

template <typename Key, typename T, typename C>
std::string ToString(const hamon::multimap<Key, T, C>& m)
{
	std::stringstream out;
	for (const auto& n : m)
	{
		out << "[" << n.first << "] = " << n.second << ", ";
	}
	return out.str();
}

GTEST_TEST(MultimapTest, SwapTest)
{
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

	EXPECT_TRUE((test2<int, int>()));
	EXPECT_TRUE((test2<int, char>()));
	EXPECT_TRUE((test2<int, float>()));
	EXPECT_TRUE((test2<char, int>()));
	EXPECT_TRUE((test2<char, char>()));
	EXPECT_TRUE((test2<char, float>()));
	EXPECT_TRUE((test2<float, int>()));
	EXPECT_TRUE((test2<float, char>()));
	EXPECT_TRUE((test2<float, float>()));

	// https://en.cppreference.com/w/cpp/container/multimap/swap
	{
		hamon::multimap<std::string, std::string>
			m1 {{"c", "gamma"}, {"b", "beta"}, {"a", "alpha"}, {"c", "gamma"}},
			m2 {{"e", "epsilon"}, {"d", "delta"}, {"e", "epsilon"}};

		const auto& ref = *(m1.begin());
		const auto iter = hamon::next(m1.cbegin());

		EXPECT_EQ("[a] = alpha, [b] = beta, [c] = gamma, [c] = gamma, ", ToString(m1));
		EXPECT_EQ("[d] = delta, [e] = epsilon, [e] = epsilon, ", ToString(m2));
		EXPECT_EQ("a", ref.first);
		EXPECT_EQ("alpha", ref.second);
		EXPECT_EQ("b", iter->first);
		EXPECT_EQ("beta", iter->second);

		m1.swap(m2);

		EXPECT_EQ("[d] = delta, [e] = epsilon, [e] = epsilon, ", ToString(m1));
		EXPECT_EQ("[a] = alpha, [b] = beta, [c] = gamma, [c] = gamma, ", ToString(m2));
		EXPECT_EQ("a", ref.first);
		EXPECT_EQ("alpha", ref.second);
		EXPECT_EQ("b", iter->first);
		EXPECT_EQ("beta", iter->second);

		swap(m1, m2);

		EXPECT_EQ("[a] = alpha, [b] = beta, [c] = gamma, [c] = gamma, ", ToString(m1));
		EXPECT_EQ("[d] = delta, [e] = epsilon, [e] = epsilon, ", ToString(m2));
		EXPECT_EQ("a", ref.first);
		EXPECT_EQ("alpha", ref.second);
		EXPECT_EQ("b", iter->first);
		EXPECT_EQ("beta", iter->second);
	}
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace swap_test

}	// namespace hamon_multimap_test
