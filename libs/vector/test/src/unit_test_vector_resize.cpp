/**
 *	@file	unit_test_vector_resize.cpp
 *
 *	@brief	resize のテスト
 *
 *	constexpr void resize(size_type sz);
 *	constexpr void resize(size_type sz, const T& c);
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

namespace resize_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Vector = hamon::vector<T>;
	using SizeType = typename Vector::size_type;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().resize(hamon::declval<SizeType>())),
		void
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().resize(hamon::declval<SizeType>(), hamon::declval<T const&>())),
		void
	>::value, "");

	static_assert(!noexcept(
		hamon::declval<Vector&>().resize(hamon::declval<SizeType>())), "");
	static_assert(!noexcept(
		hamon::declval<Vector&>().resize(hamon::declval<SizeType>(), hamon::declval<T const&>())), "");

	{
		Vector v;

		v.resize(2);
		VERIFY(v.size() == 2);
		VERIFY(v.capacity() >= 2);
		VERIFY(v[0] == 0);
		VERIFY(v[1] == 0);

		v.resize(3);
		VERIFY(v.size() == 3);
		VERIFY(v.capacity() >= 3);
		VERIFY(v[0] == 0);
		VERIFY(v[1] == 0);
		VERIFY(v[2] == 0);

		v.resize(1);
		VERIFY(v.size() == 1);
		VERIFY(v.capacity() >= 3);
		VERIFY(v[0] == 0);

		v.resize(10);
		VERIFY(v.size() == 10);
		VERIFY(v.capacity() >= 10);
		VERIFY(v[0] == 0);
		VERIFY(v[9] == 0);

		v.resize(0);
		VERIFY(v.size() == 0);
		VERIFY(v.capacity() >= 10);
	}
	{
		Vector v{1,2,3};
		v.reserve(10);
		v.resize(5);
		VERIFY(v.size() == 5);
		VERIFY(v.capacity() >= 10);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 0);
		VERIFY(v[4] == 0);
	}
	{
		Vector v;

		T const x(10);
		v.resize(2, x);
		VERIFY(v.size() == 2);
		VERIFY(v.capacity() >= 2);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 10);

		v.resize(3, 11);
		VERIFY(v.size() == 3);
		VERIFY(v.capacity() >= 3);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 10);
		VERIFY(v[2] == 11);

		v.resize(1, 12);
		VERIFY(v.size() == 1);
		VERIFY(v.capacity() >= 3);
		VERIFY(v[0] == 10);

		v.resize(10, 13);
		VERIFY(v.size() == 10);
		VERIFY(v.capacity() >= 10);
		VERIFY(v[0] == 10);
		VERIFY(v[9] == 13);

		v.resize(0, 14);
		VERIFY(v.size() == 0);
		VERIFY(v.capacity() >= 10);
	}
	{
		Vector v{1,2,3};
		v.reserve(10);
		T const x(30);
		v.resize(5, x);
		VERIFY(v.size() == 5);
		VERIFY(v.capacity() >= 10);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 30);
		VERIFY(v[4] == 30);
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

struct ThrowOnCountDown
{
	struct Exception{};

	int value;

	static int s_count_down;

	ThrowOnCountDown()
		: value(17)
	{
		--s_count_down;
		if (s_count_down < 0)
		{
			throw Exception{};
		}
	}

	ThrowOnCountDown(int v)
		: value(v)
	{
		--s_count_down;
		if (s_count_down < 0)
		{
			throw Exception{};
		}
	}

	ThrowOnCountDown(ThrowOnCountDown const& other)
		: value(other.value)
	{
		--s_count_down;
		if (s_count_down < 0)
		{
			throw Exception{};
		}
	}

	ThrowOnCountDown(ThrowOnCountDown&& other)
		: value(other.value)
	{
		--s_count_down;
		if (s_count_down < 0)
		{
			throw Exception{};
		}
	}
};

int ThrowOnCountDown::s_count_down = 0;

#endif

GTEST_TEST(VectorTest, ResizeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::vector<int> v;
		EXPECT_THROW(v.resize(v.max_size() + 1), hamon::length_error);
		EXPECT_EQ(0u, v.capacity());
		EXPECT_EQ(0u, v.size());

		v.resize(10);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		EXPECT_THROW(v.resize(v.max_size() + 1), hamon::length_error);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(10u, v.size());
	}
	{
		hamon::vector<int, MayThrowAllocator<int>> v;

		v.resize(10);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		EXPECT_THROW(v.resize(11), MayThrowAllocator<int>::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(10u, v.size());
	}
	{
		hamon::vector<ThrowOnCopy> v;

		ThrowOnCopy x(42);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		EXPECT_THROW(v.resize(3, x), ThrowOnCopy::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(0u, v.size());

		v.resize(3);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(10, v[1].value);
		EXPECT_EQ(10, v[2].value);
	}
	{
		hamon::vector<ThrowOnMove> v;

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
		hamon::vector<ThrowOnDefault> v;

		EXPECT_THROW(v.resize(3), ThrowOnDefault::Exception);
		EXPECT_EQ(0u, v.size());
		EXPECT_EQ(0u, v.capacity());

		ThrowOnDefault x(13);

		v.resize(3, x);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);
		EXPECT_EQ(13, v[2].value);
	}
	{
		ThrowOnCountDown::s_count_down = 3;
		hamon::vector<ThrowOnCountDown> v;
		v.resize(3);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(17, v[0].value);
		EXPECT_EQ(17, v[1].value);
		EXPECT_EQ(17, v[2].value);
	}
	{
		ThrowOnCountDown::s_count_down = 3;
		hamon::vector<ThrowOnCountDown> v;
		EXPECT_THROW(v.resize(4), ThrowOnCountDown::Exception);
		EXPECT_EQ(0u, v.size());
	}
	{
		ThrowOnCountDown::s_count_down = 3;
		hamon::vector<ThrowOnCountDown> v;
		v.resize(2);
		EXPECT_EQ(2u, v.size());
		EXPECT_THROW(v.resize(3), ThrowOnCountDown::Exception);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(17, v[0].value);
		EXPECT_EQ(17, v[1].value);
	}
	{
		ThrowOnCountDown::s_count_down = 3;
		hamon::vector<ThrowOnCountDown> v;
		v.reserve(10);
		v.resize(2);
		EXPECT_EQ(2u, v.size());
		EXPECT_THROW(v.resize(4), ThrowOnCountDown::Exception);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(17, v[0].value);
		EXPECT_EQ(17, v[1].value);
	}
	{
		ThrowOnCountDown::s_count_down = 1;
		ThrowOnCountDown x(42);

		ThrowOnCountDown::s_count_down = 3;
		hamon::vector<ThrowOnCountDown> v;
		v.reserve(10);
		v.resize(2);
		EXPECT_EQ(2u, v.size());
		EXPECT_THROW(v.resize(4, x), ThrowOnCountDown::Exception);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(17, v[0].value);
		EXPECT_EQ(17, v[1].value);
	}
#endif
}

}	// namespace resize_test

}	// namespace hamon_vector_test
