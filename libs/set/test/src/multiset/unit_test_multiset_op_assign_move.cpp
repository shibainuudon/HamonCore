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
	using propagate_on_container_copy_assignment = hamon::true_type;
	using propagate_on_container_move_assignment = hamon::false_type;
	using is_always_equal = hamon::false_type;

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
	using propagate_on_container_copy_assignment = hamon::false_type;
	using propagate_on_container_move_assignment = hamon::true_type;
	using is_always_equal = hamon::false_type;

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

	template <typename T>
	HAMON_CXX11_CONSTEXPR
	bool operator()(T const& x, T const& y) const
	{
		return x < y;
	}

	HAMON_CXX11_CONSTEXPR
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
	static_assert(!hamon::is_nothrow_move_assignable<Set>::value, "");
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
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace op_assign_move_test

}	// namespace hamon_multiset_test
