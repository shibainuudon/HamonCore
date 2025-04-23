/**
 *	@file	unit_test_map_ctor_iterator.cpp
 *
 *	@brief	iteratorを引数に取るコンストラクタのテスト
 *
 *	template<class InputIterator>
 *	map(InputIterator first, InputIterator last,
 *		const Compare& comp = Compare(), const Allocator& = Allocator());
 *
 *	template<class InputIterator>
 *	map(InputIterator first, InputIterator last, const Allocator& a)
 *		: map(first, last, Compare(), a) { }
 */

#include <hamon/map/map.hpp>
#include <hamon/functional.hpp>
#include <hamon/memory.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_map_test
{

namespace ctor_iterator_test
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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T, template <typename> class IteratorWrapper, typename Compare, typename Allocator>
MAP_TEST_CONSTEXPR bool test_impl2(Compare const& comp, Allocator const& alloc)
{
	using Map = hamon::map<Key, T, Compare, Allocator>;
	using ValueType = typename Map::value_type;
	using Iterator = IteratorWrapper<ValueType>;

	static_assert( hamon::is_constructible<Map, Iterator, Iterator>::value, "");
	static_assert( hamon::is_constructible<Map, Iterator, Iterator, Compare const&>::value, "");
	static_assert( hamon::is_constructible<Map, Iterator, Iterator, Compare const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Iterator, Iterator>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Iterator, Iterator, Compare const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Iterator, Iterator, Compare const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, Iterator, Iterator>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, Iterator, Iterator, Compare const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, Iterator, Iterator, Compare const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Iterator, Iterator>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Iterator, Iterator, Compare const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Iterator, Iterator, Compare const&, Allocator const&>::value, "");

#if !defined(HAMON_USE_STD_MAP) || (HAMON_CXX_STANDARD >= 14)
	static_assert( hamon::is_constructible<Map, Iterator, Iterator, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Iterator, Iterator, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, Iterator, Iterator, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Iterator, Iterator, Allocator const&>::value, "");
#endif

	ValueType a[] =
	{
		{Key{2}, T{10}},
		{Key{3}, T{20}},
		{Key{1}, T{30}},
		{Key{1}, T{40}},
		{Key{2}, T{50}},
		{Key{3}, T{60}},
	};

	{
		Map v(Iterator{a}, Iterator{a + 6});
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == Compare{});
		VERIFY(v.get_allocator() == Allocator{});
		{
			auto it = v.begin();
			VERIFY(*it++ == a[2]);
			VERIFY(*it++ == a[0]);
			VERIFY(*it++ == a[1]);
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == a[1]);
			VERIFY(*it++ == a[0]);
			VERIFY(*it++ == a[2]);
			VERIFY(it == v.rend());
		}
	}
	{
		Map v(Iterator{a}, Iterator{a + 6}, comp);
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.get_allocator() == Allocator{});
		{
			auto it = v.begin();
			VERIFY(*it++ == a[2]);
			VERIFY(*it++ == a[0]);
			VERIFY(*it++ == a[1]);
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == a[1]);
			VERIFY(*it++ == a[0]);
			VERIFY(*it++ == a[2]);
			VERIFY(it == v.rend());
		}
	}
	{
		Map v(Iterator{a}, Iterator{a + 6}, comp, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.get_allocator() == alloc);
		{
			auto it = v.begin();
			VERIFY(*it++ == a[2]);
			VERIFY(*it++ == a[0]);
			VERIFY(*it++ == a[1]);
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == a[1]);
			VERIFY(*it++ == a[0]);
			VERIFY(*it++ == a[2]);
			VERIFY(it == v.rend());
		}
	}
#if !defined(HAMON_USE_STD_MAP) || (HAMON_CXX_STANDARD >= 14)
	{
		Map v(Iterator{a}, Iterator{a + 6}, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == Compare{});
		VERIFY(v.get_allocator() == alloc);
		{
			auto it = v.begin();
			VERIFY(*it++ == a[2]);
			VERIFY(*it++ == a[0]);
			VERIFY(*it++ == a[1]);
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == a[1]);
			VERIFY(*it++ == a[0]);
			VERIFY(*it++ == a[2]);
			VERIFY(it == v.rend());
		}
	}
#endif
	{
		Map v(Iterator{a}, Iterator{a});
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
		VERIFY(v.key_comp() == Compare{});
		VERIFY(v.get_allocator() == Allocator{});
	}
	{
		Map v(Iterator{a}, Iterator{a}, comp);
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.get_allocator() == Allocator{});
	}
	{
		Map v(Iterator{a}, Iterator{a}, comp, alloc);
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.get_allocator() == alloc);
	}
#if !defined(HAMON_USE_STD_MAP) || (HAMON_CXX_STANDARD >= 14)
	{
		Map v(Iterator{a}, Iterator{a}, alloc);
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
		VERIFY(v.key_comp() == Compare{});
		VERIFY(v.get_allocator() == alloc);
	}
#endif

	return true;
}

template <typename Key, typename T, typename Compare, typename Allocator>
MAP_TEST_CONSTEXPR bool test_impl(Compare const& comp, Allocator const& alloc)
{
	return
		test_impl2<Key, T, cpp17_input_iterator_wrapper>(comp, alloc) &&
		//test_impl2<Key, T, input_iterator_wrapper>(comp, alloc) &&
		test_impl2<Key, T, forward_iterator_wrapper>(comp, alloc) &&
		test_impl2<Key, T, bidirectional_iterator_wrapper>(comp, alloc) &&
		test_impl2<Key, T, random_access_iterator_wrapper>(comp, alloc) &&
		test_impl2<Key, T, contiguous_iterator_wrapper>(comp, alloc);
}

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test1_2()
{
	hamon::allocator<typename hamon::map<Key, T>::value_type> alloc;
	MyLess comp{13};
	VERIFY(test_impl<Key, T>(comp, alloc));

	return true;
}

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test2_2()
{
	MyAllocator<typename hamon::map<Key, T>::value_type> alloc{42};
	MyLess comp{14};
	VERIFY(test_impl<Key, T>(comp, alloc));

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

GTEST_TEST(MapTest, CtorIteratorTest)
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

}	// namespace ctor_iterator_test

}	// namespace hamon_map_test
