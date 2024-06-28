/**
 *	@file	unit_test_deque_resize.cpp
 *
 *	@brief	resize のテスト
 *
 *	void      resize(size_type sz);
 *	void      resize(size_type sz, const T& c);
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/stdexcept/length_error.hpp>
#include <hamon/cstddef.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace resize_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Deque = hamon::deque<T>;
	using SizeType = typename Deque::size_type;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().resize(hamon::declval<SizeType>())),
		void
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().resize(hamon::declval<SizeType>(), hamon::declval<T const&>())),
		void
	>::value, "");

	static_assert(!noexcept(
		hamon::declval<Deque&>().resize(hamon::declval<SizeType>())), "");
	static_assert(!noexcept(
		hamon::declval<Deque&>().resize(hamon::declval<SizeType>(), hamon::declval<T const&>())), "");

	{
		Deque v;

		v.resize(2);
		VERIFY(v.size() == 2);
		VERIFY(v[0] == 0);
		VERIFY(v[1] == 0);

		v.resize(3);
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 0);
		VERIFY(v[1] == 0);
		VERIFY(v[2] == 0);

		v.resize(1);
		VERIFY(v.size() == 1);
		VERIFY(v[0] == 0);

		v.resize(10);
		VERIFY(v.size() == 10);
		VERIFY(v[0] == 0);
		VERIFY(v[9] == 0);

		v.resize(0);
		VERIFY(v.size() == 0);
	}
	{
		Deque v;

		T const x(10);
		v.resize(2, x);
		VERIFY(v.size() == 2);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 10);

		v.resize(3, 11);
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 10);
		VERIFY(v[2] == 11);

		v.resize(1, 12);
		VERIFY(v.size() == 1);
		VERIFY(v[0] == 10);

		v.resize(10, 13);
		VERIFY(v.size() == 10);
		VERIFY(v[0] == 10);
		VERIFY(v[9] == 13);

		v.resize(0, 14);
		VERIFY(v.size() == 0);
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

struct ThrowOnCopy
{
	struct Exception{};

	int value;

	ThrowOnCopy() : value(10)
	{
	}

	ThrowOnCopy(int v) : value(v)
	{
	}

	ThrowOnCopy(ThrowOnCopy const&)
	{
		throw Exception{};
	}

	ThrowOnCopy(ThrowOnCopy&& other) noexcept
		: value(other.value)
	{
	}

	ThrowOnCopy& operator=(ThrowOnCopy const&)
	{
		throw Exception{};
	}
};

struct ThrowOnMove
{
	struct Exception{};

	int value;

	ThrowOnMove() : value(20)
	{
	}

	ThrowOnMove(int v) : value(v)
	{
	}

	ThrowOnMove(ThrowOnMove const& other)
		: value(other.value)
	{
	}

	ThrowOnMove(ThrowOnMove&&)
	{
		throw Exception{};
	}

	ThrowOnMove& operator=(ThrowOnMove&&)
	{
		throw Exception{};
	}
};

struct ThrowOnDefault
{
	struct Exception{};

	int value;

	ThrowOnDefault()
	{
		throw Exception{};
	}

	ThrowOnDefault(int v) : value(v)
	{
	}
};

#endif

GTEST_TEST(DequeTest, ResizeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

#if !defined(HAMON_NO_EXCEPTIONS)
//	{
//		hamon::deque<int> v;
//		EXPECT_THROW(v.resize(v.max_size() + 1), hamon::length_error);
////		EXPECT_EQ(0u, v.capacity());
//		EXPECT_EQ(0u, v.size());
//
//		v.resize(10);
//
//		//auto const old_capacity = v.capacity();
//		//auto const old_data = v.data();
//		EXPECT_THROW(v.resize(v.max_size() + 1), hamon::length_error);
//		//EXPECT_EQ(old_capacity, v.capacity());
//		//EXPECT_EQ(old_data, v.data());
//		EXPECT_EQ(10u, v.size());
//	}
	//{
	//	hamon::deque<int, MayThrowAllocator<int>> v;

	//	v.resize(10);

	//	//auto const old_capacity = v.capacity();
	//	//auto const old_data = v.data();
	//	EXPECT_THROW(v.resize(11), MayThrowAllocator<int>::Exception);
	//	//EXPECT_EQ(old_capacity, v.capacity());
	//	//EXPECT_EQ(old_data, v.data());
	//	EXPECT_EQ(10u, v.size());
	//}
	{
		hamon::deque<ThrowOnCopy> v;

		ThrowOnCopy x(42);

		EXPECT_THROW(v.resize(3, x), ThrowOnCopy::Exception);
		EXPECT_EQ(0u, v.size());

		v.resize(3);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(10, v[1].value);
		EXPECT_EQ(10, v[2].value);
	}
	{
		hamon::deque<ThrowOnMove> v;

		ThrowOnMove x(42);

		v.resize(3, x);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(42, v[0].value);
		EXPECT_EQ(42, v[1].value);
		EXPECT_EQ(42, v[2].value);

		v.resize(10);
		EXPECT_EQ(10u, v.size());
		EXPECT_EQ(42, v[0].value);
		EXPECT_EQ(42, v[1].value);
		EXPECT_EQ(42, v[2].value);
		EXPECT_EQ(20, v[3].value);
		EXPECT_EQ(20, v[4].value);
		EXPECT_EQ(20, v[5].value);
		EXPECT_EQ(20, v[6].value);
		EXPECT_EQ(20, v[7].value);
		EXPECT_EQ(20, v[8].value);
		EXPECT_EQ(20, v[9].value);
	}
	{
		hamon::deque<ThrowOnDefault> v;

		EXPECT_THROW(v.resize(3), ThrowOnDefault::Exception);
		EXPECT_EQ(0u, v.size());

		ThrowOnDefault x(13);

		v.resize(3, x);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);
		EXPECT_EQ(13, v[2].value);
	}
#endif
}

}	// namespace resize_test

}	// namespace hamon_deque_test
