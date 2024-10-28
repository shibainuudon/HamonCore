/**
 *	@file	unit_test_vector_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 *
 *	constexpr vector(vector&&) noexcept;
 *	constexpr vector(vector&&, const type_identity_t<Allocator>&);
 */

#include <hamon/vector.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/cstddef.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace ctor_move_test
{

template <typename T>
struct MyAllocator1
{
	using value_type = T;
	using is_always_equal = hamon::false_type;

	int id;

	MyAllocator1() : id(13) {}

	MyAllocator1(int i) : id(i) {}

	MyAllocator1(MyAllocator1 const& x) = default;

	MyAllocator1(MyAllocator1&& x) : id(x.id) { x.id = 0; }

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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Allocator = hamon::allocator<T>;
	using Vector = hamon::vector<T, Allocator>;

	static_assert( hamon::is_constructible<Vector, Vector&&>::value, "");
	static_assert( hamon::is_constructible<Vector, Vector&&, Allocator const&>::value, "");
#if !defined(HAMON_USE_STD_VECTOR)
	static_assert( hamon::is_nothrow_constructible<Vector, Vector&&>::value, "");
	static_assert( hamon::is_nothrow_constructible<Vector, Vector&&, Allocator const&>::value, "");
#endif
	static_assert( hamon::is_implicitly_constructible<Vector, Vector&&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Vector, Vector&&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Vector, Vector&&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Vector, Vector&&, Allocator const&>::value, "");

	{
		Allocator alloc;
		Vector v1{{1,2,3}, alloc};
		Vector v2{hamon::move(v1)};
		VERIFY(v1.get_allocator() == alloc);
		VERIFY(v2.get_allocator() == alloc);
		VERIFY(v1.empty());
		{
			auto it = v2.begin();
			VERIFY(*it++ == 1);
			VERIFY(*it++ == 2);
			VERIFY(*it++ == 3);
			VERIFY(it == v2.end());
		}
	}
	{
		Allocator alloc;
		Vector v1{1,2,3};
		Vector v2{hamon::move(v1), alloc};
		VERIFY(v2.get_allocator() == alloc);
		VERIFY(v1.empty());
		{
			auto it = v2.begin();
			VERIFY(*it++ == 1);
			VERIFY(*it++ == 2);
			VERIFY(*it++ == 3);
			VERIFY(it == v2.end());
		}
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
		Vector v1{{1,2,3}, alloc};
		Vector v2{hamon::move(v1)};
		VERIFY(v1.get_allocator() != v2.get_allocator());
		VERIFY(v1.get_allocator().id == 0);
		VERIFY(v2.get_allocator().id == 42);
	}
	{
		Allocator alloc1{42};
		Allocator alloc2{43};
		Vector v1{{1,2,3}, alloc1};
		Vector v2{hamon::move(v1), alloc2};
		VERIFY(v1.get_allocator() != v2.get_allocator());
		VERIFY(v1.get_allocator().id == 42);
		VERIFY(v2.get_allocator().id == 43);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, CtorMoveTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<float>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());
}

}	// namespace ctor_move_test

}	// namespace hamon_vector_test
