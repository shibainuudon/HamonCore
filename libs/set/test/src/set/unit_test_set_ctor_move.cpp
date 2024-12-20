/**
 *	@file	unit_test_set_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 *
 *	set(set&& x);
 */

#include <hamon/set/set.hpp>
#include <hamon/functional.hpp>
#include <hamon/memory.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace ctor_move_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
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

	HAMON_CXX11_CONSTEXPR
	bool operator!=(MyAllocator1 const& rhs) const
	{
		return id != rhs.id;
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

	HAMON_CXX11_CONSTEXPR
	bool operator!=(MyAllocator2 const& rhs) const
	{
		return id != rhs.id;
	}

	MyAllocator2 select_on_container_copy_construction() const noexcept
	{
		// don't propagate on copy
		return {};
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

	friend bool operator<(S const& lhs, S const& rhs)
	{
		return lhs.value < rhs.value;
	}
};

int S::s_ctor_count = 0;
int S::s_copy_ctor_count = 0;
int S::s_move_ctor_count = 0;
int S::s_dtor_count = 0;

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename Compare, typename Allocator>
SET_TEST_CONSTEXPR bool test_impl(Compare const& comp, Allocator const& alloc)
{
	using Set = hamon::set<Key, Compare, Allocator>;

	static_assert( hamon::is_move_constructible<Set>::value, "");
#if !defined(HAMON_USE_STD_SET)
	static_assert( hamon::is_nothrow_move_constructible<Set>::value, "");
#endif
	static_assert( hamon::is_implicitly_move_constructible<Set>::value, "");
	static_assert(!hamon::is_trivially_move_constructible<Set>::value, "");

	{
		Set v1
		{
			{
				Key{3},
				Key{1},
				Key{4},
				Key{1},
				Key{5},
				Key{2},
				Key{3},
			},
			comp, alloc
		};
		Set v2{hamon::move(v1)};
		VERIFY(!v2.empty());
		VERIFY(v2.size() == 5);
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.rbegin() != v2.rend());
		VERIFY(v2.key_comp() == comp);
		VERIFY(v2.get_allocator() == alloc);
		{
			auto it = v2.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{2});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{4});
			VERIFY(*it++ == Key{5});
			VERIFY(it == v2.end());
		}
		{
			auto it = v2.rbegin();
			VERIFY(*it++ == Key{5});
			VERIFY(*it++ == Key{4});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{2});
			VERIFY(*it++ == Key{1});
			VERIFY(it == v2.rend());
		}
	}
	return true;
}

template <typename Key>
SET_TEST_CONSTEXPR bool test1()
{
	MyLess comp{13};
	hamon::allocator<Key> alloc;
	VERIFY(test_impl<Key>(comp, alloc));

	return true;
}

template <typename Key>
SET_TEST_CONSTEXPR bool test2()
{
	MyLess comp{14};
	MyAllocator1<Key> alloc{42};
	VERIFY(test_impl<Key>(comp, alloc));

	return true;
}

template <typename Key>
SET_TEST_CONSTEXPR bool test3()
{
	MyLess comp{15};
	MyAllocator2<Key> alloc{42};
	VERIFY(test_impl<Key>(comp, alloc));

	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, CtorMoveTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());

	EXPECT_TRUE(test3<int>());
	EXPECT_TRUE(test3<char>());
	EXPECT_TRUE(test3<float>());

	S::s_ctor_count = 0;
	S::s_copy_ctor_count = 0;
	S::s_move_ctor_count = 0;
	S::s_dtor_count = 0;
	{
		hamon::set<S, hamon::less<>, MyAllocator1<S>> v1{MyAllocator1<S>{10}};
		v1.emplace(1);
		v1.emplace(1);
		v1.emplace(2);
		v1.emplace(3);
		EXPECT_EQ(4, S::s_ctor_count);
		EXPECT_EQ(0, S::s_copy_ctor_count);
		EXPECT_EQ(0, S::s_move_ctor_count);
		EXPECT_EQ(1, S::s_dtor_count);

		hamon::set<S, hamon::less<>, MyAllocator1<S>> v2{hamon::move(v1)};
		EXPECT_EQ(4, S::s_ctor_count);
		EXPECT_EQ(0, S::s_copy_ctor_count);
		EXPECT_EQ(0, S::s_move_ctor_count);
		EXPECT_EQ(1, S::s_dtor_count);
	}
	EXPECT_EQ(4, S::s_ctor_count);
	EXPECT_EQ(0, S::s_copy_ctor_count);
	EXPECT_EQ(0, S::s_move_ctor_count);
	EXPECT_EQ(4, S::s_dtor_count);
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace ctor_move_test

}	// namespace hamon_set_test
