/**
 *	@file	unit_test_multimap_op_assign_move.cpp
 *
 *	@brief	ムーブ代入演算子のテスト
 *
 *	multimap& operator=(multimap&& x)
 *		noexcept(allocator_traits<Allocator>::is_always_equal::value &&
 *			is_nothrow_move_assignable_v<Compare>);
 */

#include <hamon/map/multimap.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multimap_test
{

namespace op_assign_move_test
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
MULTIMAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::multimap<Key, T>;
	using ValueType = typename Map::value_type;

	static_assert( hamon::is_move_assignable<Map>::value, "");
	static_assert( hamon::is_nothrow_move_assignable<Map>::value, "");
	static_assert(!hamon::is_trivially_move_assignable<Map>::value, "");

	Map v1;
	VERIFY(v1.empty());

	{
		Map v2
		{
			{ Key{3}, T{10}},
			{ Key{1}, T{20}},
			{ Key{4}, T{30}},
		};
		auto& r = (v1 = hamon::move(v2));
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
	//{
	//	auto& r = (v1 = hamon::move(v1));
	//	VERIFY(&r == &v1);
	//	VERIFY(v1.size() == 3);
	//	{
	//		auto it = v1.begin();
	//		VERIFY(*it++ == ValueType{Key{1}, T{20}});
	//		VERIFY(*it++ == ValueType{Key{3}, T{10}});
	//		VERIFY(*it++ == ValueType{Key{4}, T{30}});
	//		VERIFY(it == v1.end());
	//	}
	//}
	{
		Map v2
		{
			{ Key{1}, T{10}},
			{ Key{2}, T{20}},
			{ Key{3}, T{30}},
			{ Key{4}, T{40}},
			{ Key{5}, T{50}},
		};
		auto& r = (v1 = hamon::move(v2));
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
		auto& r = (v1 = hamon::move(v2));
		VERIFY(&r == &v1);
		VERIFY(&r != &v2);
		VERIFY(v1.size() == 0);
	}

	return true;
}

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test2()
{
	using Compare = hamon::less<>;
	using Allocator = MyAllocator1<typename hamon::multimap<Key, T>::value_type>;
	using Map = hamon::multimap<Key, T, Compare, Allocator>;

	static_assert( hamon::is_move_assignable<Map>::value, "");
	static_assert(!hamon::is_nothrow_move_assignable<Map>::value, "");
	static_assert(!hamon::is_trivially_move_assignable<Map>::value, "");

	Map v1{Allocator{10}};
	VERIFY(v1.empty());

	{
		Map v2
		{
			{
				{ Key{3}, T{10} },
				{ Key{1}, T{20} },
				{ Key{4}, T{30} },
			},
			Allocator{20}
		};
		v1 = hamon::move(v2);

		// アロケータを伝播しない
		VERIFY(v1.get_allocator().id == 10);
		VERIFY(v2.get_allocator().id == 20);
	}

	return true;
}

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test3()
{
	using Compare = hamon::less<>;
	using Allocator = MyAllocator2<typename hamon::multimap<Key, T>::value_type>;
	using Map = hamon::multimap<Key, T, Compare, Allocator>;

	static_assert( hamon::is_move_assignable<Map>::value, "");
#if !defined(HAMON_USE_STD_MULTIMAP)
	static_assert(!hamon::is_nothrow_move_assignable<Map>::value, "");
#endif
	static_assert(!hamon::is_trivially_move_assignable<Map>::value, "");

	Map v1{Allocator{10}};
	VERIFY(v1.empty());

	{
		Map v2
		{
			{
				{ Key{3}, T{10} },
				{ Key{1}, T{20} },
				{ Key{4}, T{30} },
			},
			Allocator{20}
		};
		v1 = hamon::move(v2);

		// アロケータを伝播する
		VERIFY(v1.get_allocator().id == 20);
		VERIFY(v2.get_allocator().id == 20);
	}

	return true;
}

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test4()
{
	using Compare = MyLess;
	using Map = hamon::multimap<Key, T, Compare>;

	static_assert( hamon::is_move_assignable<Map>::value, "");
	static_assert(!hamon::is_nothrow_move_assignable<Map>::value, "");
	static_assert(!hamon::is_trivially_move_assignable<Map>::value, "");

	Map v1{Compare{10}};
	VERIFY(v1.empty());

	{
		Map v2
		{
			{
				{ Key{3}, T{10} },
				{ Key{1}, T{20} },
				{ Key{4}, T{30} },
			},
			Compare{20}
		};
		v1 = hamon::move(v2);

		VERIFY(v1.key_comp().id == 20);
		VERIFY(v2.key_comp().id == 20);
	}

	return true;
}

bool test5()
{
	using Allocator = MyAllocator1<typename hamon::multimap<int, int>::value_type>;
	using Map = hamon::multimap<int, int, hamon::less<>, Allocator>;
	using ValueType = typename Map::value_type;

	{
		Map v1{Allocator{10}};
		Map v2{Allocator{10}};

		v1.emplace_hint(v1.end(),   1, 10);
		v1.emplace_hint(v1.begin(), 2, 20);
		v1.emplace_hint(v1.begin(), 1, 30);
		v1.emplace_hint(v1.begin(), 3, 40);
		v1.emplace_hint(v1.end(),   3, 50);
		v1.emplace_hint(v1.begin(), 3, 60);

		v2 = hamon::move(v1);
		auto it = v2.begin();
		VERIFY(*it++ == ValueType{1, 30});
		VERIFY(*it++ == ValueType{1, 10});
		VERIFY(*it++ == ValueType{2, 20});
		VERIFY(*it++ == ValueType{3, 60});
		VERIFY(*it++ == ValueType{3, 40});
		VERIFY(*it++ == ValueType{3, 50});
		VERIFY(it == v2.end());
	}
	{
		Map v1{Allocator{10}};
		Map v2{Allocator{20}};

		v1.emplace_hint(v1.end(),   1, 10);
		v1.emplace_hint(v1.begin(), 2, 20);
		v1.emplace_hint(v1.begin(), 1, 30);
		v1.emplace_hint(v1.begin(), 3, 40);
		v1.emplace_hint(v1.end(),   3, 50);
		v1.emplace_hint(v1.begin(), 3, 60);

		v2 = hamon::move(v1);
		auto it = v2.begin();
		VERIFY(*it++ == ValueType{1, 30});
		VERIFY(*it++ == ValueType{1, 10});
		VERIFY(*it++ == ValueType{2, 20});
		VERIFY(*it++ == ValueType{3, 60});
		VERIFY(*it++ == ValueType{3, 40});
		VERIFY(*it++ == ValueType{3, 50});
		VERIFY(it == v2.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MultimapTest, OpAssignMoveTest)
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

	EXPECT_TRUE(test5());

#if !defined(HAMON_USE_STD_MULTIMAP)
	{
		using Allocator = MyAllocator1<typename hamon::multimap<int, S>::value_type>;
		using Map = hamon::multimap<int, S, hamon::less<>, Allocator>;

		S::s_ctor_count = 0;
		S::s_copy_ctor_count = 0;
		S::s_move_ctor_count = 0;
		S::s_dtor_count = 0;
		{
			Map v1{Allocator{10}};
			Map v2{Allocator{10}};

			v1.emplace(1, 10);
			v1.emplace(1, 20);
			v1.emplace(2, 30);
			v1.emplace(3, 40);

			v2.emplace(2, 50);
			v2.emplace(5, 60);

			EXPECT_EQ(6, S::s_ctor_count);
			EXPECT_EQ(0, S::s_copy_ctor_count);
			EXPECT_EQ(0, S::s_move_ctor_count);
			EXPECT_EQ(0, S::s_dtor_count);

			v1 = hamon::move(v2);
			EXPECT_EQ(6, S::s_ctor_count);
			EXPECT_EQ(0, S::s_copy_ctor_count);
			EXPECT_EQ(0, S::s_move_ctor_count);
			EXPECT_EQ(4, S::s_dtor_count);
		}
		EXPECT_EQ(6, S::s_ctor_count);
		EXPECT_EQ(0, S::s_copy_ctor_count);
		EXPECT_EQ(0, S::s_move_ctor_count);
		EXPECT_EQ(6, S::s_dtor_count);

		S::s_ctor_count = 0;
		S::s_copy_ctor_count = 0;
		S::s_move_ctor_count = 0;
		S::s_dtor_count = 0;
		{
			Map v1{Allocator{10}};
			Map v2{Allocator{20}};

			v1.emplace(1, 10);
			v1.emplace(1, 20);
			v1.emplace(2, 30);
			v1.emplace(3, 40);

			v2.emplace(2, 50);
			v2.emplace(5, 60);

			EXPECT_EQ(6, S::s_ctor_count);
			EXPECT_EQ(0, S::s_copy_ctor_count);
			EXPECT_EQ(0, S::s_move_ctor_count);
			EXPECT_EQ(0, S::s_dtor_count);

			v1 = hamon::move(v2);
			EXPECT_EQ(6, S::s_ctor_count);
			EXPECT_EQ(0, S::s_copy_ctor_count);
			EXPECT_EQ(2, S::s_move_ctor_count);
			//EXPECT_EQ(4, S::s_dtor_count);
		}
		EXPECT_EQ(6, S::s_ctor_count);
		EXPECT_EQ(0, S::s_copy_ctor_count);
		EXPECT_EQ(2, S::s_move_ctor_count);
		EXPECT_EQ(8, S::s_dtor_count);
	}
	{
		using Allocator = MyAllocator2<typename hamon::multimap<int, S>::value_type>;
		using Map = hamon::multimap<int, S, hamon::less<>, Allocator>;

		S::s_ctor_count = 0;
		S::s_copy_ctor_count = 0;
		S::s_move_ctor_count = 0;
		S::s_dtor_count = 0;
		{
			Map v1{Allocator{10}};
			Map v2{Allocator{10}};

			v1.emplace(1, 10);
			v1.emplace(1, 20);
			v1.emplace(2, 30);
			v1.emplace(3, 40);

			v2.emplace(2, 50);
			v2.emplace(5, 60);

			EXPECT_EQ(6, S::s_ctor_count);
			EXPECT_EQ(0, S::s_copy_ctor_count);
			EXPECT_EQ(0, S::s_move_ctor_count);
			EXPECT_EQ(0, S::s_dtor_count);

			v1 = hamon::move(v2);
			EXPECT_EQ(6, S::s_ctor_count);
			EXPECT_EQ(0, S::s_copy_ctor_count);
			EXPECT_EQ(0, S::s_move_ctor_count);
			EXPECT_EQ(4, S::s_dtor_count);
		}
		EXPECT_EQ(6, S::s_ctor_count);
		EXPECT_EQ(0, S::s_copy_ctor_count);
		EXPECT_EQ(0, S::s_move_ctor_count);
		EXPECT_EQ(6, S::s_dtor_count);

		S::s_ctor_count = 0;
		S::s_copy_ctor_count = 0;
		S::s_move_ctor_count = 0;
		S::s_dtor_count = 0;
		{
			Map v1{Allocator{10}};
			Map v2{Allocator{20}};

			v1.emplace(1, 10);
			v1.emplace(1, 20);
			v1.emplace(2, 30);
			v1.emplace(3, 40);

			v2.emplace(2, 50);
			v2.emplace(5, 60);

			EXPECT_EQ(6, S::s_ctor_count);
			EXPECT_EQ(0, S::s_copy_ctor_count);
			EXPECT_EQ(0, S::s_move_ctor_count);
			EXPECT_EQ(0, S::s_dtor_count);

			v1 = hamon::move(v2);
			EXPECT_EQ(6, S::s_ctor_count);
			EXPECT_EQ(0, S::s_copy_ctor_count);
			EXPECT_EQ(0, S::s_move_ctor_count);
			EXPECT_EQ(4, S::s_dtor_count);
		}
		EXPECT_EQ(6, S::s_ctor_count);
		EXPECT_EQ(0, S::s_copy_ctor_count);
		EXPECT_EQ(0, S::s_move_ctor_count);
		EXPECT_EQ(6, S::s_dtor_count);
	}
#endif
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace op_assign_move_test

}	// namespace hamon_multimap_test
