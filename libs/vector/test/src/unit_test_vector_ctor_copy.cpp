/**
 *	@file	unit_test_vector_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	constexpr vector(const vector& x);
 *	constexpr vector(const vector&, const type_identity_t<Allocator>&);
 */

#include <hamon/vector.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace ctor_copy_test
{

template <typename T>
struct MyAllocator1
{
	using value_type = T;

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

	MyAllocator2 select_on_container_copy_construction() const noexcept
	{
		// don't propagate on copy
		return {};
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Allocator = hamon::allocator<T>;
	using Vector = hamon::vector<T, Allocator>;

	static_assert( hamon::is_constructible<Vector, Vector const&>::value, "");
	static_assert( hamon::is_constructible<Vector, Vector const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Vector, Vector const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Vector, Vector const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Vector, Vector const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Vector, Vector const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Vector, Vector const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Vector, Vector const&, Allocator const&>::value, "");

	{
		Allocator alloc;
		Vector const v1{{1,2,3}, alloc};
		Vector v2{v1};
		VERIFY(v1.get_allocator() == alloc);
		VERIFY(v2.get_allocator() == alloc);
		VERIFY(v1.size() == 3);
		VERIFY(v1[0] == 1);
		VERIFY(v1[1] == 2);
		VERIFY(v1[2] == 3);
		VERIFY(v2.size() == 3);
		VERIFY(v2[0] == 1);
		VERIFY(v2[1] == 2);
		VERIFY(v2[2] == 3);
	}
	{
		Allocator alloc;
		Vector const v1{1,2,3};
		Vector v2{v1, alloc};
		VERIFY(v2.get_allocator() == alloc);
		VERIFY(v1.size() == 3);
		VERIFY(v1[0] == 1);
		VERIFY(v1[1] == 2);
		VERIFY(v1[2] == 3);
		VERIFY(v2.size() == 3);
		VERIFY(v2[0] == 1);
		VERIFY(v2[1] == 2);
		VERIFY(v2[2] == 3);
	}

	return true;
}

template <typename T>
bool test2()
{
	using Allocator = MyAllocator1<T>;
	using Vector = hamon::vector<T, Allocator>;

	{
		Allocator alloc{42};
		Vector const v1{{1,2,3}, alloc};
		Vector v2{v1};
		VERIFY(v1.get_allocator() == v2.get_allocator());
		VERIFY(v1.get_allocator() == alloc);
		VERIFY(v2.get_allocator() == alloc);
	}
	{
		Allocator alloc1{42};
		Allocator alloc2{43};
		Vector const v1{{1,2,3}, alloc1};
		Vector v2{v1, alloc2};
		VERIFY(v1.get_allocator() != v2.get_allocator());
		VERIFY(v1.get_allocator() == alloc1);
		VERIFY(v2.get_allocator() == alloc2);
	}

	return true;
}

template <typename T>
bool test3()
{
	using Allocator = MyAllocator2<T>;
	using Vector = hamon::vector<T, Allocator>;

	{
		Allocator alloc{42};
		Vector const v1{{1,2,3}, alloc};
		Vector v2{v1};
		VERIFY(v1.get_allocator() != v2.get_allocator());
		VERIFY(v1.get_allocator() == alloc);
		VERIFY(v2.get_allocator() != alloc);
	}
	{
		Allocator alloc1{42};
		Allocator alloc2{43};
		Vector const v1{{1,2,3}, alloc1};
		Vector v2{v1, alloc2};
		VERIFY(v1.get_allocator() != v2.get_allocator());
		VERIFY(v1.get_allocator() == alloc1);
		VERIFY(v2.get_allocator() == alloc2);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, CtorCopyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<float>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());

	EXPECT_TRUE(test3<int>());
	EXPECT_TRUE(test3<char>());
	EXPECT_TRUE(test3<float>());
}

}	// namespace ctor_copy_test

}	// namespace hamon_vector_test
