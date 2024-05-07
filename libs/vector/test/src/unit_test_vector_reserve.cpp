/**
 *	@file	unit_test_vector_reserve.cpp
 *
 *	@brief	reserve のテスト
 *
 *	constexpr void reserve(size_type n);
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/stdexcept/length_error.hpp>
#include <hamon/cstddef.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace reserve_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Vector = hamon::vector<T>;
	using SizeType = typename Vector::size_type;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().reserve(hamon::declval<SizeType>())),
		void
	>::value, "");

	static_assert(!noexcept(
		hamon::declval<Vector&>().reserve(hamon::declval<SizeType>())), "");

	{
		Vector v;
		VERIFY(v.capacity() == 0);
		v.reserve(10);
		VERIFY(v.capacity() == 10);
		v.reserve(15);
		VERIFY(v.capacity() == 15);
		v.reserve(12);
		VERIFY(v.capacity() == 15);
	}
	return true;
}

#undef VERIFY

#if !defined(HAMON_NO_EXCEPTIONS)

template <typename T>
struct MayThrowAllocator
{
	using value_type = T;
	using size_type = hamon::size_t;
	using difference_type = hamon::ptrdiff_t;
	using pointer = T*;
	using propagate_on_container_move_assignment = hamon::true_type;
	using is_always_equal = hamon::true_type;

	struct Exception{};

	MayThrowAllocator() noexcept {}

	MayThrowAllocator(const MayThrowAllocator&) noexcept {}

	template <typename U>
	MayThrowAllocator(const MayThrowAllocator<U>&) noexcept {}

	pointer allocate(size_type n)
	{
		if (n > 10)
		{
			throw Exception{};
		}
		return static_cast<pointer>(::operator new(n * sizeof(T)));
	}

	void deallocate(pointer p, size_type /*n*/)
	{
		::operator delete(p/*, n*/);
	}
};

#endif

GTEST_TEST(VectorTest, ReserveTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::vector<int> v;
		EXPECT_THROW(v.reserve(v.max_size() + 1), hamon::length_error);
		EXPECT_EQ(0u, v.capacity());

		v.reserve(10);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		EXPECT_THROW(v.reserve(v.max_size() + 1), hamon::length_error);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
	}
	{
		hamon::vector<int, MayThrowAllocator<int>> v;

		v.reserve(10);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		EXPECT_THROW(v.reserve(11), MayThrowAllocator<int>::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
	}
#endif
}

}	// namespace reserve_test

}	// namespace hamon_vector_test
