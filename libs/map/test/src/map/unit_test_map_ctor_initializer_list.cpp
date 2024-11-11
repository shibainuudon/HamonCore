﻿/**
 *	@file	unit_test_map_ctor_initializer_list.cpp
 *
 *	@brief	initializer_listを引数に取るコンストラクタのテスト
 *
 *	map(initializer_list<value_type>,
 *		const Compare& = Compare(),
 *		const Allocator& = Allocator());
 *
 *	map(initializer_list<value_type> il, const Allocator& a)
 *		: map(il, Compare(), a) { }
 */

#include <hamon/map/map.hpp>
#include <hamon/memory.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace ctor_initializer_list_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

template <typename T>
struct MyAllocator
{
	using value_type = T;

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

struct MyGreater
{
	int id;

	HAMON_CXX11_CONSTEXPR
	MyGreater() : id(0) {}

	HAMON_CXX11_CONSTEXPR
	MyGreater(int i) : id(i) {}

	template <typename T>
	HAMON_CXX11_CONSTEXPR
	bool operator()(T const& x, T const& y) const
	{
		return x > y;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(MyGreater const& rhs) const
	{
		return id == rhs.id;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T, typename Compare, typename Allocator>
MAP_TEST_CONSTEXPR bool test_impl_1(Compare const& comp, Allocator const& alloc)
{
	using Map = hamon::map<Key, T, Compare, Allocator>;
	using ValueType = typename Map::value_type;

	static_assert( hamon::is_constructible<Map, std::initializer_list<ValueType>>::value, "");
	static_assert( hamon::is_constructible<Map, std::initializer_list<ValueType>, Compare const&>::value, "");
	static_assert( hamon::is_constructible<Map, std::initializer_list<ValueType>, Compare const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, std::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, std::initializer_list<ValueType>, Compare const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, std::initializer_list<ValueType>, Compare const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, std::initializer_list<ValueType>>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, std::initializer_list<ValueType>, Compare const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, std::initializer_list<ValueType>, Compare const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, std::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, std::initializer_list<ValueType>, Compare const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, std::initializer_list<ValueType>, Compare const&, Allocator const&>::value, "");

#if !defined(HAMON_USE_STD_MAP) || (HAMON_CXX_STANDARD >= 14)
	static_assert( hamon::is_constructible<Map, std::initializer_list<ValueType>, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, std::initializer_list<ValueType>, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, std::initializer_list<ValueType>, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, std::initializer_list<ValueType>, Allocator const&>::value, "");
#endif

	{
		Map v
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
			{Key{4}, T{30}},
			{Key{1}, T{40}},
			{Key{5}, T{50}},
			{Key{2}, T{60}},
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == Compare{});
		VERIFY(v.get_allocator() == Allocator{});
		{
			auto it = v.begin();
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(it == v.rend());
		}
	}
	{
		Map v
		{
			{
				{Key{3}, T{10}},
				{Key{1}, T{20}},
				{Key{4}, T{30}},
				{Key{1}, T{40}},
				{Key{5}, T{50}},
				{Key{2}, T{60}},
			},
			comp
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.get_allocator() == Allocator{});
		{
			auto it = v.begin();
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(it == v.rend());
		}
	}
	{
		Map v
		{
			{
				{Key{3}, T{10}},
				{Key{1}, T{20}},
				{Key{4}, T{30}},
				{Key{1}, T{40}},
				{Key{5}, T{50}},
				{Key{2}, T{60}},
			},
			comp, alloc
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.get_allocator() == alloc);
		{
			auto it = v.begin();
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(it == v.rend());
		}
	}
#if !defined(HAMON_USE_STD_MAP) || (HAMON_CXX_STANDARD >= 14)
	{
		Map v
		{
			{
				{Key{3}, T{10}},
				{Key{1}, T{20}},
				{Key{4}, T{30}},
				{Key{1}, T{40}},
				{Key{5}, T{50}},
				{Key{2}, T{60}},
			},
			alloc
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == Compare{});
		VERIFY(v.get_allocator() == alloc);
		{
			auto it = v.begin();
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(it == v.rend());
		}
	}
#endif

	return true;
}

template <typename Key, typename T, typename Compare, typename Allocator>
MAP_TEST_CONSTEXPR bool test_impl_2(Compare const& comp, Allocator const& alloc)
{
	using Map = hamon::map<Key, T, Compare, Allocator>;
	using ValueType = typename Map::value_type;

	static_assert( hamon::is_constructible<Map, std::initializer_list<ValueType>>::value, "");
	static_assert( hamon::is_constructible<Map, std::initializer_list<ValueType>, Compare const&>::value, "");
	static_assert( hamon::is_constructible<Map, std::initializer_list<ValueType>, Compare const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, std::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, std::initializer_list<ValueType>, Compare const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, std::initializer_list<ValueType>, Compare const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, std::initializer_list<ValueType>>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, std::initializer_list<ValueType>, Compare const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, std::initializer_list<ValueType>, Compare const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, std::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, std::initializer_list<ValueType>, Compare const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, std::initializer_list<ValueType>, Compare const&, Allocator const&>::value, "");

#if !defined(HAMON_USE_STD_MAP) || (HAMON_CXX_STANDARD >= 14)
	static_assert( hamon::is_constructible<Map, std::initializer_list<ValueType>, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, std::initializer_list<ValueType>, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, std::initializer_list<ValueType>, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, std::initializer_list<ValueType>, Allocator const&>::value, "");
#endif

	{
		Map v
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
			{Key{4}, T{30}},
			{Key{1}, T{40}},
			{Key{5}, T{50}},
			{Key{2}, T{60}},
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == Compare{});
		VERIFY(v.get_allocator() == Allocator{});
		{
			auto it = v.begin();
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(it == v.rend());
		}
	}
	{
		Map v
		{
			{
				{Key{3}, T{10}},
				{Key{1}, T{20}},
				{Key{4}, T{30}},
				{Key{1}, T{40}},
				{Key{5}, T{50}},
				{Key{2}, T{60}},
			},
			comp
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.get_allocator() == Allocator{});
		{
			auto it = v.begin();
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(it == v.rend());
		}
	}
	{
		Map v
		{
			{
				{Key{3}, T{10}},
				{Key{1}, T{20}},
				{Key{4}, T{30}},
				{Key{1}, T{40}},
				{Key{5}, T{50}},
				{Key{2}, T{60}},
			},
			comp, alloc
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.get_allocator() == alloc);
		{
			auto it = v.begin();
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(it == v.rend());
		}
	}
#if !defined(HAMON_USE_STD_MAP) || (HAMON_CXX_STANDARD >= 14)
	{
		Map v
		{
			{
				{Key{3}, T{10}},
				{Key{1}, T{20}},
				{Key{4}, T{30}},
				{Key{1}, T{40}},
				{Key{5}, T{50}},
				{Key{2}, T{60}},
			},
			alloc
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == Compare{});
		VERIFY(v.get_allocator() == alloc);
		{
			auto it = v.begin();
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(it == v.rend());
		}
	}
#endif

	return true;
}

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test1_2()
{
	hamon::allocator<std::pair<const Key, T>> alloc;
	{
		MyLess comp{13};
		VERIFY(test_impl_1<Key, T>(comp, alloc));
	}
	{
		MyGreater comp{14};
		VERIFY(test_impl_2<Key, T>(comp, alloc));
	}

	return true;
}

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test2_2()
{
	MyAllocator<std::pair<const Key, T>> alloc{42};
	{
		MyLess comp{15};
		VERIFY(test_impl_1<Key, T>(comp, alloc));
	}
	{
		MyGreater comp{16};
		VERIFY(test_impl_2<Key, T>(comp, alloc));
	}

	return true;
}

template <typename Key>
MAP_TEST_CONSTEXPR bool test1()
{
	VERIFY(test1_2<Key, int>());
	VERIFY(test1_2<Key, char>());
	VERIFY(test1_2<Key, float>());

	return true;
}

template <typename Key>
MAP_TEST_CONSTEXPR bool test2()
{
	VERIFY(test2_2<Key, int>());
	VERIFY(test2_2<Key, char>());
	VERIFY(test2_2<Key, float>());

	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, CtorInitializerListTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	MAP_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	MAP_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace ctor_initializer_list_test

}	// namespace hamon_map_test
