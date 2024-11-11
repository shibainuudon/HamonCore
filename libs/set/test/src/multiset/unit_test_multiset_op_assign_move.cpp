/**
 *	@file	unit_test_multiset_op_assign_move.cpp
 *
 *	@brief	ムーブ代入演算子のテスト
 *
 *	multiset& operator=(multiset&& x)
 *		noexcept(allocator_traits<Allocator>::is_always_equal::value &&
 *			is_nothrow_move_assignable_v<Compare>);
 */

#include <hamon/set/multiset.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multiset_test
{

namespace op_assign_move_test
{

#if !defined(HAMON_USE_STD_MULTISET)
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR              /**/
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

template <typename Key>
MULTISET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::multiset<Key>;

	static_assert( hamon::is_move_assignable<Set>::value, "");
	static_assert( hamon::is_nothrow_move_assignable<Set>::value, "");
	static_assert(!hamon::is_trivially_move_assignable<Set>::value, "");

	Set v1;
	VERIFY(v1.empty());

	{
		Set v2 {Key{3}, Key{1}, Key{4}};
		auto& r = (v1 = hamon::move(v2));
		VERIFY(&r == &v1);
		VERIFY(&r != &v2);
		VERIFY(v1.size() == 3);
		{
			auto it = v1.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{4});
			VERIFY(it == v1.end());
		}
	}
	//{
	//	auto& r = (v1 = hamon::move(v1));
	//	VERIFY(&r == &v1);
	//	VERIFY(v1.size() == 3);
	//	{
	//		auto it = v1.begin();
	//		VERIFY(*it++ == Key{1});
	//		VERIFY(*it++ == Key{3});
	//		VERIFY(*it++ == Key{4});
	//		VERIFY(it == v1.end());
	//	}
	//}
	{
		Set v2 {Key{1}, Key{2}, Key{3}, Key{4}, Key{5}};
		auto& r = (v1 = hamon::move(v2));
		VERIFY(&r == &v1);
		VERIFY(&r != &v2);
		VERIFY(v1.size() == 5);
		{
			auto it = v1.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{2});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{4});
			VERIFY(*it++ == Key{5});
			VERIFY(it == v1.end());
		}
	}
	{
		Set v2;
		auto& r = (v1 = hamon::move(v2));
		VERIFY(&r == &v1);
		VERIFY(&r != &v2);
		VERIFY(v1.size() == 0);
	}

	return true;
}

template <typename Key>
MULTISET_TEST_CONSTEXPR bool test2()
{
	using Compare = hamon::less<>;
	using Allocator = MyAllocator1<Key>;
	using Set = hamon::multiset<Key, Compare, Allocator>;

	static_assert( hamon::is_move_assignable<Set>::value, "");
	static_assert(!hamon::is_nothrow_move_assignable<Set>::value, "");
	static_assert(!hamon::is_trivially_move_assignable<Set>::value, "");

	Set v1{Allocator{10}};
	VERIFY(v1.empty());

	{
		Set v2 {{Key{3}, Key{1}, Key{4}}, Allocator{20}};
		v1 = hamon::move(v2);

		// アロケータを伝播しない
		VERIFY(v1.get_allocator().id == 10);
		VERIFY(v2.get_allocator().id == 20);
	}

	return true;
}

template <typename Key>
MULTISET_TEST_CONSTEXPR bool test3()
{
	using Compare = hamon::less<>;
	using Allocator = MyAllocator2<Key>;
	using Set = hamon::multiset<Key, Compare, Allocator>;

	static_assert( hamon::is_move_assignable<Set>::value, "");
#if !defined(HAMON_USE_STD_MULTISET)
	static_assert(!hamon::is_nothrow_move_assignable<Set>::value, "");
#endif
	static_assert(!hamon::is_trivially_move_assignable<Set>::value, "");

	Set v1{Allocator{10}};
	VERIFY(v1.empty());

	{
		Set v2 {{Key{3}, Key{1}, Key{4}}, Allocator{20}};
		v1 = hamon::move(v2);

		// アロケータを伝播する
		VERIFY(v1.get_allocator().id == 20);
		VERIFY(v2.get_allocator().id == 20);
	}

	return true;
}

template <typename Key>
MULTISET_TEST_CONSTEXPR bool test4()
{
	using Compare = MyLess;
	using Set = hamon::multiset<Key, Compare>;

	static_assert( hamon::is_move_assignable<Set>::value, "");
	static_assert(!hamon::is_nothrow_move_assignable<Set>::value, "");
	static_assert(!hamon::is_trivially_move_assignable<Set>::value, "");

	Set v1{Compare{10}};
	VERIFY(v1.empty());

	{
		Set v2 {{Key{3}, Key{1}, Key{4}}, Compare{20}};
		v1 = hamon::move(v2);

		VERIFY(v1.key_comp().id == 20);
		VERIFY(v2.key_comp().id == 20);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MultisetTest, OpAssignMoveTest)
{
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());

	EXPECT_TRUE(test3<int>());
	EXPECT_TRUE(test3<char>());
	EXPECT_TRUE(test3<float>());

	EXPECT_TRUE(test4<int>());
	EXPECT_TRUE(test4<char>());
	EXPECT_TRUE(test4<float>());

#if !defined(HAMON_USE_STD_MULTISET)
	S::s_ctor_count = 0;
	S::s_copy_ctor_count = 0;
	S::s_move_ctor_count = 0;
	S::s_dtor_count = 0;
	{
		hamon::multiset<S, hamon::less<>, MyAllocator1<S>> v1{MyAllocator1<S>{10}};
		hamon::multiset<S, hamon::less<>, MyAllocator1<S>> v2{MyAllocator1<S>{10}};

		v1.emplace(1);
		v1.emplace(1);
		v1.emplace(2);
		v1.emplace(3);

		v2.emplace(2);
		v2.emplace(5);

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
		hamon::multiset<S, hamon::less<>, MyAllocator1<S>> v1{MyAllocator1<S>{10}};
		hamon::multiset<S, hamon::less<>, MyAllocator1<S>> v2{MyAllocator1<S>{20}};

		v1.emplace(1);
		v1.emplace(1);
		v1.emplace(2);
		v1.emplace(3);

		v2.emplace(2);
		v2.emplace(5);

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

	S::s_ctor_count = 0;
	S::s_copy_ctor_count = 0;
	S::s_move_ctor_count = 0;
	S::s_dtor_count = 0;
	{
		hamon::multiset<S, hamon::less<>, MyAllocator2<S>> v1{MyAllocator2<S>{10}};
		hamon::multiset<S, hamon::less<>, MyAllocator2<S>> v2{MyAllocator2<S>{10}};

		v1.emplace(1);
		v1.emplace(1);
		v1.emplace(2);
		v1.emplace(3);

		v2.emplace(2);
		v2.emplace(5);

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
		hamon::multiset<S, hamon::less<>, MyAllocator2<S>> v1{MyAllocator2<S>{10}};
		hamon::multiset<S, hamon::less<>, MyAllocator2<S>> v2{MyAllocator2<S>{20}};

		v1.emplace(1);
		v1.emplace(1);
		v1.emplace(2);
		v1.emplace(3);

		v2.emplace(2);
		v2.emplace(5);

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
#endif
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace op_assign_move_test

}	// namespace hamon_multiset_test
