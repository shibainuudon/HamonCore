/**
 *	@file	unit_test_multimap_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 *
 *	multimap(multimap&& x);
 */

#include <hamon/map/multimap.hpp>
#include <hamon/functional.hpp>
#include <hamon/memory.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multimap_test
{

namespace ctor_move_test
{

#if !defined(HAMON_USE_STD_MULTIMAP)
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR              /**/
#endif

template <typename T>
struct MyAllocator1
{
	using value_type = T;
	using is_always_equal = std::false_type;

	int id;

	HAMON_CXX11_CONSTEXPR
	MyAllocator1() : id(0) {}

	HAMON_CXX11_CONSTEXPR
	MyAllocator1(int i) : id(i) {}

	template <typename U>
	HAMON_CXX11_CONSTEXPR
	MyAllocator1(MyAllocator1<U> const& a) : id(a.id) {}

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
	bool operator==(MyAllocator1 const& rhs) const
	{
		return id == rhs.id;
	}
};

template <typename T>
struct MyAllocator2
{
	using value_type = T;
	using is_always_equal = std::false_type;

	int id;

	HAMON_CXX11_CONSTEXPR
	MyAllocator2() : id(0) {}

	HAMON_CXX11_CONSTEXPR
	MyAllocator2(int i) : id(i) {}

	template <typename U>
	HAMON_CXX11_CONSTEXPR
	MyAllocator2(MyAllocator2<U> const& a) : id(a.id) {}

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
	bool operator==(MyAllocator2 const& rhs) const
	{
		return id == rhs.id;
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

struct S
{
	static int s_ctor_count;
	static int s_copy_ctor_count;
	static int s_move_ctor_count;
	static int s_dtor_count;

	int value;

	S(int v) : value(v)
	{
		++s_ctor_count;
	}

	S(S const& x) : value(x.value)
	{
		++s_copy_ctor_count;
	}

	S(S&& x) noexcept : value(x.value)
	{
		++s_move_ctor_count;
	}

	~S()
	{
		++s_dtor_count;
	}

	S& operator=(S&&)      = delete;
	S& operator=(S const&) = delete;
};

int S::s_ctor_count = 0;
int S::s_copy_ctor_count = 0;
int S::s_move_ctor_count = 0;
int S::s_dtor_count = 0;

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T, typename Compare, typename Allocator>
MULTIMAP_TEST_CONSTEXPR bool test_impl(Compare const& comp, Allocator const& alloc)
{
	using Map = hamon::multimap<Key, T, Compare, Allocator>;
	using ValueType = typename Map::value_type;

	static_assert( hamon::is_move_constructible<Map>::value, "");
#if !defined(HAMON_USE_STD_MULTIMAP)
	static_assert( hamon::is_nothrow_move_constructible<Map>::value, "");
#endif
	static_assert( hamon::is_implicitly_move_constructible<Map>::value, "");
	static_assert(!hamon::is_trivially_move_constructible<Map>::value, "");

	{
		Map v1
		{
			{
				{Key{3}, T{10}},
				{Key{1}, T{20}},
				{Key{4}, T{30}},
				{Key{1}, T{40}},
				{Key{5}, T{50}},
				{Key{2}, T{60}},
				{Key{3}, T{70}},
			},
			comp, alloc
		};
		Map v2{hamon::move(v1)};
		VERIFY(!v2.empty());
		VERIFY(v2.size() == 7);
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.rbegin() != v2.rend());
		VERIFY(v2.key_comp() == comp);
		VERIFY(v2.get_allocator() == alloc);
		{
			auto it = v2.begin();
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(*it++ == ValueType{Key{1}, T{40}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{3}, T{70}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(it == v2.end());
		}
		{
			auto it = v2.rbegin();
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(*it++ == ValueType{Key{3}, T{70}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{2}, T{60}});
			VERIFY(*it++ == ValueType{Key{1}, T{40}});
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(it == v2.rend());
		}
	}
	return true;
}

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test1_2()
{
	MyLess comp{13};
	hamon::allocator<typename hamon::multimap<Key, T>::value_type> alloc;
	VERIFY(test_impl<Key, T>(comp, alloc));

	return true;
}

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test2_2()
{
	MyLess comp{14};
	MyAllocator1<typename hamon::multimap<Key, T>::value_type> alloc{42};
	VERIFY(test_impl<Key, T>(comp, alloc));

	return true;
}

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test3_2()
{
	MyLess comp{15};
	MyAllocator2<typename hamon::multimap<Key, T>::value_type> alloc{42};
	VERIFY(test_impl<Key, T>(comp, alloc));

	return true;
}

template <typename Key>
MULTIMAP_TEST_CONSTEXPR bool test1()
{
	VERIFY(test1_2<Key, int>());
	VERIFY(test1_2<Key, char>());
	VERIFY(test1_2<Key, float>());

	return true;
}

template <typename Key>
MULTIMAP_TEST_CONSTEXPR bool test2()
{
	VERIFY(test2_2<Key, int>());
	VERIFY(test2_2<Key, char>());
	VERIFY(test2_2<Key, float>());

	return true;
}

template <typename Key>
MULTIMAP_TEST_CONSTEXPR bool test3()
{
	VERIFY(test3_2<Key, int>());
	VERIFY(test3_2<Key, char>());
	VERIFY(test3_2<Key, float>());

	return true;
}

bool test4()
{
	using Map = hamon::multimap<int, int>;
	using ValueType = typename Map::value_type;

	Map v1;
	v1.emplace_hint(v1.end(),   1, 10);
	v1.emplace_hint(v1.begin(), 2, 20);
	v1.emplace_hint(v1.begin(), 1, 30);
	v1.emplace_hint(v1.begin(), 3, 40);
	v1.emplace_hint(v1.end(),   3, 50);
	v1.emplace_hint(v1.begin(), 3, 60);

	Map v2{hamon::move(v1)};
	auto it = v2.begin();
	VERIFY(*it++ == ValueType{1, 30});
	VERIFY(*it++ == ValueType{1, 10});
	VERIFY(*it++ == ValueType{2, 20});
	VERIFY(*it++ == ValueType{3, 60});
	VERIFY(*it++ == ValueType{3, 40});
	VERIFY(*it++ == ValueType{3, 50});
	VERIFY(it == v2.end());

	return true;
}

#undef VERIFY

GTEST_TEST(MultimapTest, CtorMoveTest)
{
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());

	EXPECT_TRUE(test3<int>());
	EXPECT_TRUE(test3<char>());
	EXPECT_TRUE(test3<float>());

	EXPECT_TRUE(test4());

	using Allocator = MyAllocator1<typename hamon::multimap<int, S>::value_type>;
	using Map = hamon::multimap<int, S, hamon::less<>, Allocator>;

	S::s_ctor_count = 0;
	S::s_copy_ctor_count = 0;
	S::s_move_ctor_count = 0;
	S::s_dtor_count = 0;
	{
		Map v1{Allocator{10}};
		v1.emplace(1, 10);
		v1.emplace(1, 20);
		v1.emplace(2, 30);
		v1.emplace(3, 40);
		EXPECT_EQ(4, S::s_ctor_count);
		EXPECT_EQ(0, S::s_copy_ctor_count);
		EXPECT_EQ(0, S::s_move_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);

		Map v2{hamon::move(v1)};
		EXPECT_EQ(4, S::s_ctor_count);
		EXPECT_EQ(0, S::s_copy_ctor_count);
		EXPECT_EQ(0, S::s_move_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);
	}
	EXPECT_EQ(4, S::s_ctor_count);
	EXPECT_EQ(0, S::s_copy_ctor_count);
	EXPECT_EQ(0, S::s_move_ctor_count);
	EXPECT_EQ(4, S::s_dtor_count);
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace ctor_move_test

}	// namespace hamon_multimap_test
