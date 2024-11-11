/**
 *	@file	unit_test_map_op_assign_copy.cpp
 *
 *	@brief	コピー代入演算子のテスト
 *
 *	map& operator=(const map& x);
 */

#include <hamon/map/map.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace op_assign_copy_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

template <typename T>
struct MyAllocator1
{
	using value_type = T;
	using propagate_on_container_copy_assignment = std::true_type;
	using propagate_on_container_move_assignment = std::false_type;
	using is_always_equal = std::false_type;

	int id;

	MyAllocator1() : id(13) {}

	MyAllocator1(int i) : id(i) {}

	template <typename U>
	MyAllocator1(MyAllocator1<U> const& a) : id(a.id) {}

	T* allocate(hamon::size_t n)
	{
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}

	void deallocate(T* p, hamon::size_t n)
	{
		// [allocator.members]/11
		::operator delete(p);
		(void)n;
	}

	bool operator==(MyAllocator1 const& rhs) const
	{
		return id == rhs.id;
	}

	bool operator!=(MyAllocator1 const& rhs) const
	{
		return id != rhs.id;
	}
};

template <typename T>
struct MyAllocator2
{
	using value_type = T;
	using propagate_on_container_copy_assignment = std::false_type;
	using propagate_on_container_move_assignment = std::true_type;
	using is_always_equal = std::false_type;

	int id;

	MyAllocator2() : id(13) {}

	MyAllocator2(int i) : id(i) {}

	template <typename U>
	MyAllocator2(MyAllocator2<U> const& a) : id(a.id) {}

	T* allocate(hamon::size_t n)
	{
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}

	void deallocate(T* p, hamon::size_t n)
	{
		// [allocator.members]/11
		::operator delete(p);
		(void)n;
	}

	bool operator==(MyAllocator2 const& rhs) const
	{
		return id == rhs.id;
	}

	bool operator!=(MyAllocator2 const& rhs) const
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

	MyLess(MyLess const&) = default;

	template <typename T>
	HAMON_CXX11_CONSTEXPR
	bool operator()(T const& x, T const& y) const
	{
		return x < y;
	}

	HAMON_CXX14_CONSTEXPR
	MyLess& operator=(MyLess const& rhs)
	{
		id = rhs.id;
		return *this;
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

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::map<Key, T>;
	using ValueType = typename Map::value_type;

	static_assert( hamon::is_copy_assignable<Map>::value, "");
	static_assert(!hamon::is_nothrow_copy_assignable<Map>::value, "");
	static_assert(!hamon::is_trivially_copy_assignable<Map>::value, "");

	Map v1;
	VERIFY(v1.empty());

	{
		Map const v2
		{
			{ Key{3}, T{10}},
			{ Key{1}, T{20}},
			{ Key{4}, T{30}},
		};
		auto& r = (v1 = v2);
		VERIFY(&r == &v1);
		VERIFY(&r != &v2);
		VERIFY(v1.size() == 3);
		{
			auto it = v1.begin();
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(it == v1.end());
		}
	}
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
	{
		auto& r = (v1 = v1);
		VERIFY(&r == &v1);
		VERIFY(v1.size() == 3);
		{
			auto it = v1.begin();
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(it == v1.end());
		}
	}
HAMON_WARNING_POP()
	{
		Map const v2
		{
			{ Key{1}, T{10}},
			{ Key{2}, T{20}},
			{ Key{3}, T{30}},
			{ Key{4}, T{40}},
			{ Key{5}, T{50}},
		};
		auto& r = (v1 = v2);
		VERIFY(&r == &v1);
		VERIFY(&r != &v2);
		VERIFY(v1.size() == 5);
		{
			auto it = v1.begin();
			VERIFY(*it++ == ValueType{Key{1}, T{10}});
			VERIFY(*it++ == ValueType{Key{2}, T{20}});
			VERIFY(*it++ == ValueType{Key{3}, T{30}});
			VERIFY(*it++ == ValueType{Key{4}, T{40}});
			VERIFY(*it++ == ValueType{Key{5}, T{50}});
			VERIFY(it == v1.end());
		}
	}
	{
		Map const v2;
		auto& r = (v1 = v2);
		VERIFY(&r == &v1);
		VERIFY(&r != &v2);
		VERIFY(v1.size() == 0);
	}

	return true;
}

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test2()
{
	using Compare = hamon::less<>;
	using Allocator = MyAllocator1<std::pair<const Key, T>>;
	using Map = hamon::map<Key, T, Compare, Allocator>;

	static_assert( hamon::is_copy_assignable<Map>::value, "");
	static_assert(!hamon::is_nothrow_copy_assignable<Map>::value, "");
	static_assert(!hamon::is_trivially_copy_assignable<Map>::value, "");

	Map v1{Allocator{10}};
	VERIFY(v1.empty());

	{
		Map const v2
		{
			{
				{ Key{3}, T{10} },
				{ Key{1}, T{20} },
				{ Key{4}, T{30} },
			},
			Allocator{20}
		};
		v1 = v2;

		// アロケータを伝播する
		VERIFY(v1.get_allocator().id == 20);
		VERIFY(v2.get_allocator().id == 20);
	}

	return true;
}

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test3()
{
	using Compare = hamon::less<>;
	using Allocator = MyAllocator2<std::pair<const Key, T>>;
	using Map = hamon::map<Key, T, Compare, Allocator>;

	static_assert( hamon::is_copy_assignable<Map>::value, "");
	static_assert(!hamon::is_nothrow_copy_assignable<Map>::value, "");
	static_assert(!hamon::is_trivially_copy_assignable<Map>::value, "");

	Map v1{Allocator{10}};
	VERIFY(v1.empty());

	{
		Map const v2
		{
			{
				{ Key{3}, T{10} },
				{ Key{1}, T{20} },
				{ Key{4}, T{30} },
			},
			Allocator{20}
		};
		v1 = v2;

		// アロケータを伝播しない
		VERIFY(v1.get_allocator().id == 10);
		VERIFY(v2.get_allocator().id == 20);
	}

	return true;
}

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test4()
{
	using Compare = MyLess;
	using Map = hamon::map<Key, T, Compare>;

	static_assert( hamon::is_copy_assignable<Map>::value, "");
	static_assert(!hamon::is_nothrow_copy_assignable<Map>::value, "");
	static_assert(!hamon::is_trivially_copy_assignable<Map>::value, "");

	Map v1{Compare{10}};
	VERIFY(v1.empty());

	{
		Map const v2
		{
			{
				{ Key{3}, T{10} },
				{ Key{1}, T{20} },
				{ Key{4}, T{30} },
			},
			Compare{20}
		};
		v1 = v2;

		VERIFY(v1.key_comp().id == 20);
		VERIFY(v2.key_comp().id == 20);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, OpAssignCopyTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

	EXPECT_TRUE((test2<int, int>()));
	EXPECT_TRUE((test2<int, char>()));
	EXPECT_TRUE((test2<int, float>()));
	EXPECT_TRUE((test2<char, int>()));
	EXPECT_TRUE((test2<char, char>()));
	EXPECT_TRUE((test2<char, float>()));
	EXPECT_TRUE((test2<float, int>()));
	EXPECT_TRUE((test2<float, char>()));
	EXPECT_TRUE((test2<float, float>()));

	EXPECT_TRUE((test3<int, int>()));
	EXPECT_TRUE((test3<int, char>()));
	EXPECT_TRUE((test3<int, float>()));
	EXPECT_TRUE((test3<char, int>()));
	EXPECT_TRUE((test3<char, char>()));
	EXPECT_TRUE((test3<char, float>()));
	EXPECT_TRUE((test3<float, int>()));
	EXPECT_TRUE((test3<float, char>()));
	EXPECT_TRUE((test3<float, float>()));

	EXPECT_TRUE((test4<int, int>()));
	EXPECT_TRUE((test4<int, char>()));
	EXPECT_TRUE((test4<int, float>()));
	EXPECT_TRUE((test4<char, int>()));
	EXPECT_TRUE((test4<char, char>()));
	EXPECT_TRUE((test4<char, float>()));
	EXPECT_TRUE((test4<float, int>()));
	EXPECT_TRUE((test4<float, char>()));
	EXPECT_TRUE((test4<float, float>()));

#if !defined(HAMON_USE_STD_MAP)
	S::s_ctor_count = 0;
	S::s_copy_ctor_count = 0;
	S::s_move_ctor_count = 0;
	S::s_dtor_count = 0;
	{
		using Allocator = MyAllocator1<std::pair<int const, S>>;
		hamon::map<int, S, hamon::less<>, Allocator> v1{Allocator{10}};
		hamon::map<int, S, hamon::less<>, Allocator> v2{Allocator{10}};

		v1.try_emplace(1, 10);
		v1.try_emplace(1, 20);
		v1.try_emplace(2, 30);
		v1.try_emplace(3, 40);

		v2.try_emplace(2, 50);
		v2.try_emplace(5, 60);

		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(0, S::s_copy_ctor_count);
		EXPECT_EQ(0, S::s_move_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);

		v1 = v2;
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(2, S::s_copy_ctor_count);
		EXPECT_EQ(0, S::s_move_ctor_count);
		EXPECT_EQ(3, S::s_dtor_count);
	}
	EXPECT_EQ(5, S::s_ctor_count);
	EXPECT_EQ(2, S::s_copy_ctor_count);
	EXPECT_EQ(0, S::s_move_ctor_count);
	EXPECT_EQ(7, S::s_dtor_count);

	S::s_ctor_count = 0;
	S::s_copy_ctor_count = 0;
	S::s_move_ctor_count = 0;
	S::s_dtor_count = 0;
	{
		using Allocator = MyAllocator1<std::pair<int const, S>>;
		hamon::map<int, S, hamon::less<>, Allocator> v1{Allocator{10}};
		hamon::map<int, S, hamon::less<>, Allocator> v2{Allocator{20}};

		v1.try_emplace(1, 10);
		v1.try_emplace(1, 20);
		v1.try_emplace(2, 30);
		v1.try_emplace(3, 40);

		v2.try_emplace(2, 50);
		v2.try_emplace(5, 60);

		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(0, S::s_copy_ctor_count);
		EXPECT_EQ(0, S::s_move_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);

		v1 = v2;
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(2, S::s_copy_ctor_count);
		EXPECT_EQ(0, S::s_move_ctor_count);
		EXPECT_EQ(3, S::s_dtor_count);
	}
	EXPECT_EQ(5, S::s_ctor_count);
	EXPECT_EQ(2, S::s_copy_ctor_count);
	EXPECT_EQ(0, S::s_move_ctor_count);
	EXPECT_EQ(7, S::s_dtor_count);

	S::s_ctor_count = 0;
	S::s_copy_ctor_count = 0;
	S::s_move_ctor_count = 0;
	S::s_dtor_count = 0;
	{
		using Allocator = MyAllocator2<std::pair<int const, S>>;
		hamon::map<int, S, hamon::less<>, Allocator> v1{Allocator{10}};
		hamon::map<int, S, hamon::less<>, Allocator> v2{Allocator{10}};

		v1.try_emplace(1, 10);
		v1.try_emplace(1, 20);
		v1.try_emplace(2, 30);
		v1.try_emplace(3, 40);

		v2.try_emplace(2, 50);
		v2.try_emplace(5, 60);

		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(0, S::s_copy_ctor_count);
		EXPECT_EQ(0, S::s_move_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);

		v1 = v2;
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(2, S::s_copy_ctor_count);
		EXPECT_EQ(0, S::s_move_ctor_count);
		EXPECT_EQ(3, S::s_dtor_count);
	}
	EXPECT_EQ(5, S::s_ctor_count);
	EXPECT_EQ(2, S::s_copy_ctor_count);
	EXPECT_EQ(0, S::s_move_ctor_count);
	EXPECT_EQ(7, S::s_dtor_count);

	S::s_ctor_count = 0;
	S::s_copy_ctor_count = 0;
	S::s_move_ctor_count = 0;
	S::s_dtor_count = 0;
	{
		using Allocator = MyAllocator2<std::pair<int const, S>>;
		hamon::map<int, S, hamon::less<>, Allocator> v1{Allocator{10}};
		hamon::map<int, S, hamon::less<>, Allocator> v2{Allocator{20}};

		v1.try_emplace(1, 10);
		v1.try_emplace(1, 20);
		v1.try_emplace(2, 30);
		v1.try_emplace(3, 40);

		v2.try_emplace(2, 50);
		v2.try_emplace(5, 60);

		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(0, S::s_copy_ctor_count);
		EXPECT_EQ(0, S::s_move_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);

		v1 = v2;
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(2, S::s_copy_ctor_count);
		EXPECT_EQ(0, S::s_move_ctor_count);
		EXPECT_EQ(3, S::s_dtor_count);
	}
	EXPECT_EQ(5, S::s_ctor_count);
	EXPECT_EQ(2, S::s_copy_ctor_count);
	EXPECT_EQ(0, S::s_move_ctor_count);
	EXPECT_EQ(7, S::s_dtor_count);
#endif
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace op_assign_copy_test

}	// namespace hamon_map_test
