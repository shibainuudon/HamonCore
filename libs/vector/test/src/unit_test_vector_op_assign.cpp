/**
 *	@file	unit_test_vector_op_assign.cpp
 *
 *	@brief	代入演算子のテスト
 *
 *	constexpr vector& operator=(const vector& x);
 *  constexpr vector& operator=(vector&& x)
 *    noexcept(allocator_traits<Allocator>::propagate_on_container_move_assignment::value ||
 *             allocator_traits<Allocator>::is_always_equal::value);
 *  constexpr vector& operator=(initializer_list<T>);
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/cstddef.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace op_assign_test
{

template <typename T>
struct MyAllocator : std::allocator<T>
{
	using base_type = std::allocator<T>;

	using value_type = T;
	using size_type = hamon::size_t;
	using difference_type = hamon::ptrdiff_t;
	using pointer = T*;
	using propagate_on_container_move_assignment = hamon::false_type;
	using is_always_equal = hamon::false_type;

	HAMON_CXX11_CONSTEXPR MyAllocator() noexcept
		: base_type()
	{}

	HAMON_CXX11_CONSTEXPR MyAllocator(const MyAllocator&) noexcept
		: base_type()
	{}

	template <typename U>
	HAMON_CXX11_CONSTEXPR MyAllocator(const MyAllocator<U>&) noexcept
		: base_type()
	{}

	HAMON_CXX14_CONSTEXPR MyAllocator&
	operator=(const MyAllocator&) noexcept { return *this; }

	HAMON_CXX11_CONSTEXPR bool operator==(MyAllocator const&) const
	{
		return false;
	}

	HAMON_CXX11_CONSTEXPR bool operator!=(MyAllocator const& rhs) const
	{
		return !(*this == rhs);
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR bool test1()
{
	{
		hamon::vector<int> v1;
		hamon::vector<int> const v2{10,20,30,40};

		{
			auto& t = (v1 = v2);
			VERIFY(&t == &v1);
			VERIFY(&t != &v2);
		}
		VERIFY(v1.size() == 4);
		VERIFY(v1[0] == 10);
		VERIFY(v1[1] == 20);
		VERIFY(v1[2] == 30);
		VERIFY(v1[3] == 40);

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
		{
			auto& t = (v1 = v1);
			VERIFY(&t == &v1);
			VERIFY(&t != &v2);
		}
HAMON_WARNING_POP()
		VERIFY(v1.size() == 4);
		VERIFY(v1[0] == 10);
		VERIFY(v1[1] == 20);
		VERIFY(v1[2] == 30);
		VERIFY(v1[3] == 40);
	}
	return true;
}

template <typename T, template <typename> class TAllocator>
HAMON_CXX20_CONSTEXPR bool test2()
{
	using Allocator = TAllocator<T>;
	using Vector = hamon::vector<T, Allocator>;
	{
		Vector v;

		{
			auto& t = (v = Vector{4,5,6});
			VERIFY(&t == &v);
		}
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 4);
		VERIFY(v[1] == 5);
		VERIFY(v[2] == 6);

		{
			auto& t = (v = hamon::move(v));
			VERIFY(&t == &v);
		}
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 4);
		VERIFY(v[1] == 5);
		VERIFY(v[2] == 6);

		{
			auto& t = (v = Vector{1,2});
			VERIFY(&t == &v);
		}
		VERIFY(v.size() == 2);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
	}
	return true;
}

HAMON_CXX20_CONSTEXPR bool test3()
{
	{
		hamon::vector<int> v;

		{
			auto& t = (v = {1,2,3});
			VERIFY(&t == &v);
		}
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);

		{
			auto& t = (v = {10,11,12,13,14,15,16});
			VERIFY(&t == &v);
		}
		VERIFY(v.size() == 7);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 11);
		VERIFY(v[2] == 12);
		VERIFY(v[3] == 13);
		VERIFY(v[4] == 14);
		VERIFY(v[5] == 15);
		VERIFY(v[6] == 16);

		{
			auto& t = (v = {42});
			VERIFY(&t == &v);
		}
		VERIFY(v.size() == 1);
		VERIFY(v[0] == 42);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, OpAssignTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<int, std::allocator>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<int, MyAllocator>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test3());
}

}	// namespace op_assign_test

}	// namespace hamon_vector_test
