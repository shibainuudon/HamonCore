/**
 *	@file	unit_test_vector_insert.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr iterator insert(const_iterator position, const T& x);
 *	constexpr iterator insert(const_iterator position, T&& x);
 *	constexpr iterator insert(const_iterator position, size_type n, const T& x);
 *	template<class InputIterator>
 *	constexpr iterator insert(const_iterator position,
 *	                          InputIterator first, InputIterator last);
 *	constexpr iterator insert(const_iterator position, initializer_list<T> il);
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_vector_test
{

namespace insert_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR bool test1()
{
	using T = int;
	using Vector = hamon::vector<T>;
	using Iterator = typename Vector::iterator;
	using ConstIterator = typename Vector::const_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().insert(hamon::declval<ConstIterator>(), hamon::declval<T const&>())),
		Iterator
	>::value, "");
	static_assert(!noexcept(
		hamon::declval<Vector&>().insert(hamon::declval<ConstIterator>(), hamon::declval<T const&>())), "");

	{
		Vector v;
		int const x = 10;
		auto ret = v.insert(v.end(), x);
		VERIFY(ret == v.begin());
		VERIFY(v.size() == 1);
		VERIFY(v[0] == 10);
	}
	{
		Vector v{1,2,3};
		int const x = 10;
		auto ret = v.insert(v.begin() + 1, x);
		VERIFY(ret == v.begin() + 1);
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 10);
		VERIFY(v[2] == 2);
		VERIFY(v[3] == 3);
	}
	{
		Vector v{1,2,3};
		int const x = 20;
		v.reserve(4);
		// メモリの再確保が行われないときは、挿入位置より前のイテレータは無効にならない
		auto it1 = v.begin();
		auto it2 = v.begin() + 1;
		auto ret = v.insert(v.begin() + 2, x);
		VERIFY(ret == v.begin() + 2);
		VERIFY(it1 == v.begin());
		VERIFY(it2 == v.begin() + 1);
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 3);
	}

	return true;
}

HAMON_CXX20_CONSTEXPR bool test2()
{
	using T = int;
	using Vector = hamon::vector<T>;
	using Iterator = typename Vector::iterator;
	using ConstIterator = typename Vector::const_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().insert(hamon::declval<ConstIterator>(), hamon::declval<T&&>())),
		Iterator
	>::value, "");
	static_assert(!noexcept(
		hamon::declval<Vector&>().insert(hamon::declval<ConstIterator>(), hamon::declval<T&&>())), "");

	{
		Vector v;
		auto ret = v.insert(v.begin(), 10);
		VERIFY(ret == v.begin());
		VERIFY(v.size() == 1);
		VERIFY(v[0] == 10);
	}
	{
		Vector v{1,2,3};
		{
			auto ret = v.insert(v.begin() + 2, 20);
			VERIFY(ret == v.begin() + 2);
		}
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 3);
		{
			auto ret = v.insert(v.end(), 30);
			VERIFY(ret == v.begin() + 4);
		}
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 3);
		VERIFY(v[4] == 30);
		{
			auto ret = v.insert(v.begin(), 40);
			VERIFY(ret == v.begin());
		}
		VERIFY(v.size() == 6);
		VERIFY(v[0] == 40);
		VERIFY(v[1] == 1);
		VERIFY(v[2] == 2);
		VERIFY(v[3] == 20);
		VERIFY(v[4] == 3);
		VERIFY(v[5] == 30);
	}
	{
		Vector v{1,2,3};
		v.reserve(4);
		// メモリの再確保が行われないときは、挿入位置より前のイテレータは無効にならない
		auto it1 = v.begin();
		auto it2 = v.begin() + 1;
		auto ret = v.insert(v.begin() + 2, 20);
		VERIFY(ret == v.begin() + 2);
		VERIFY(it1 == v.begin());
		VERIFY(it2 == v.begin() + 1);
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 3);
	}

	return true;
}

HAMON_CXX20_CONSTEXPR bool test3()
{
	using T = int;
	using Vector = hamon::vector<T>;
	using SizeType = typename Vector::size_type;
	using Iterator = typename Vector::iterator;
	using ConstIterator = typename Vector::const_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().insert(hamon::declval<ConstIterator>(), hamon::declval<SizeType>(), hamon::declval<T const&>())),
		Iterator
	>::value, "");
	static_assert(!noexcept(
		hamon::declval<Vector&>().insert(hamon::declval<ConstIterator>(), hamon::declval<SizeType>(), hamon::declval<T const&>())), "");

	{
		Vector v;
		auto ret = v.insert(v.begin(), 3, 13);
		VERIFY(ret == v.begin());
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 13);
		VERIFY(v[1] == 13);
		VERIFY(v[2] == 13);
	}
	{
		Vector v{1,2,3};
		{
			auto ret = v.insert(v.begin() + 2, 4, 42);
			VERIFY(ret == v.begin() + 2);
		}
		VERIFY(v.size() == 7);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 42);
		VERIFY(v[3] == 42);
		VERIFY(v[4] == 42);
		VERIFY(v[5] == 42);
		VERIFY(v[6] == 3);
		{
			auto ret = v.insert(v.begin(), 3, 43);
			VERIFY(ret == v.begin());
		}
		VERIFY(v.size() == 10);
		VERIFY(v[0] == 43);
		VERIFY(v[1] == 43);
		VERIFY(v[2] == 43);
		VERIFY(v[3] == 1);
		VERIFY(v[4] == 2);
		VERIFY(v[5] == 42);
		VERIFY(v[6] == 42);
		VERIFY(v[7] == 42);
		VERIFY(v[8] == 42);
		VERIFY(v[9] == 3);
		{
			auto ret = v.insert(v.end(), 5, 44);
			VERIFY(ret == v.begin() + 10);
		}
		VERIFY(v.size() == 15);
		VERIFY(v[0] == 43);
		VERIFY(v[1] == 43);
		VERIFY(v[2] == 43);
		VERIFY(v[3] == 1);
		VERIFY(v[4] == 2);
		VERIFY(v[5] == 42);
		VERIFY(v[6] == 42);
		VERIFY(v[7] == 42);
		VERIFY(v[8] == 42);
		VERIFY(v[9] == 3);
		VERIFY(v[10] == 44);
		VERIFY(v[11] == 44);
		VERIFY(v[12] == 44);
		VERIFY(v[13] == 44);
		VERIFY(v[14] == 44);
	}
	{
		Vector v{1,2,3};
		int const x = 20;
		v.reserve(6);
		// メモリの再確保が行われないときは、挿入位置より前のイテレータは無効にならない
		auto it1 = v.begin();
		auto it2 = v.begin() + 1;
		auto ret = v.insert(v.begin() + 2, 3, x);
		VERIFY(ret == v.begin() + 2);
		VERIFY(it1 == v.begin());
		VERIFY(it2 == v.begin() + 1);
		VERIFY(v.size() == 6);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 20);
		VERIFY(v[4] == 20);
		VERIFY(v[5] == 3);
	}

	return true;
}

template <template <typename> class IteratorWrapper>
HAMON_CXX20_CONSTEXPR bool test4()
{
	using T = int;
	using Vector = hamon::vector<T>;
	using Iterator = typename Vector::iterator;
	using ConstIterator = typename Vector::const_iterator;
	using InputIterator = IteratorWrapper<int>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().insert(hamon::declval<ConstIterator>(), hamon::declval<InputIterator>(), hamon::declval<InputIterator>())),
		Iterator
	>::value, "");
	static_assert(!noexcept(
		hamon::declval<Vector&>().insert(hamon::declval<ConstIterator>(), hamon::declval<InputIterator>(), hamon::declval<InputIterator>())), "");

	{
		Vector v;
		int a[] = {11,12,13,14,15};
		auto ret = v.insert(v.begin(), InputIterator{a}, InputIterator{a + 4});
		VERIFY(ret == v.begin());
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 11);
		VERIFY(v[1] == 12);
		VERIFY(v[2] == 13);
		VERIFY(v[3] == 14);
	}
	{
		Vector v{1,2,3};
		int a[] = {11,12,13,14,15};
		{
			auto ret = v.insert(v.begin() + 1, InputIterator{a}, InputIterator{a + 3});
			VERIFY(ret == v.begin() + 1);
		}
		VERIFY(v.size() == 6);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 11);
		VERIFY(v[2] == 12);
		VERIFY(v[3] == 13);
		VERIFY(v[4] == 2);
		VERIFY(v[5] == 3);
		{
			auto ret = v.insert(v.end(), InputIterator{a + 2}, InputIterator{a + 5});
			VERIFY(ret == v.begin() + 6);
		}
		VERIFY(v.size() == 9);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 11);
		VERIFY(v[2] == 12);
		VERIFY(v[3] == 13);
		VERIFY(v[4] == 2);
		VERIFY(v[5] == 3);
		VERIFY(v[6] == 13);
		VERIFY(v[7] == 14);
		VERIFY(v[8] == 15);
	}
	{
		Vector v{1,2,3};
		int a[] = {11,12,13,14,15};
		v.reserve(8);
		// メモリの再確保が行われないときは、挿入位置より前のイテレータは無効にならない
		auto it1 = v.begin();
		auto it2 = v.begin() + 1;
		auto ret = v.insert(v.begin() + 2, InputIterator{a}, InputIterator{a + 5});
		VERIFY(ret == v.begin() + 2);
		VERIFY(it1 == v.begin());
		VERIFY(it2 == v.begin() + 1);
		VERIFY(v.size() == 8);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 11);
		VERIFY(v[3] == 12);
		VERIFY(v[4] == 13);
		VERIFY(v[5] == 14);
		VERIFY(v[6] == 15);
		VERIFY(v[7] == 3);
	}

	return true;
}

HAMON_CXX20_CONSTEXPR bool test5()
{
	using T = int;
	using Vector = hamon::vector<T>;
	using Iterator = typename Vector::iterator;
	using ConstIterator = typename Vector::const_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().insert(hamon::declval<ConstIterator>(), hamon::declval<std::initializer_list<T>>())),
		Iterator
	>::value, "");
	static_assert(!noexcept(
		hamon::declval<Vector&>().insert(hamon::declval<ConstIterator>(), hamon::declval<std::initializer_list<T>>())), "");

	{
		Vector v;
		auto ret = v.insert(v.begin(), {1,2,3});
		VERIFY(ret == v.begin());
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
	}
	{
		Vector v{1,2,3};
		auto ret = v.insert(v.begin() + 2, {11,12,13,14});
		VERIFY(ret == v.begin() + 2);
		VERIFY(v.size() == 7);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 11);
		VERIFY(v[3] == 12);
		VERIFY(v[4] == 13);
		VERIFY(v[5] == 14);
		VERIFY(v[6] == 3);
	}
	{
		Vector v{1,2,3};
		v.reserve(8);
		// メモリの再確保が行われないときは、挿入位置より前のイテレータは無効にならない
		auto it1 = v.begin();
		auto it2 = v.begin() + 1;
		auto ret = v.insert(v.begin() + 2, {11,12,13,14,15});
		VERIFY(ret == v.begin() + 2);
		VERIFY(it1 == v.begin());
		VERIFY(it2 == v.begin() + 1);
		VERIFY(v.size() == 8);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 11);
		VERIFY(v[3] == 12);
		VERIFY(v[4] == 13);
		VERIFY(v[5] == 14);
		VERIFY(v[6] == 15);
		VERIFY(v[7] == 3);
	}

	return true;
}

#undef VERIFY

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnCopy
{
	struct Exception{};

	int value;

	ThrowOnCopy() : value(13)
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

	ThrowOnMove() : value(14)
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
#endif

GTEST_TEST(VectorTest, InsertTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test3());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test4<cpp17_input_iterator_wrapper>());
//	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test4<input_iterator_wrapper>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test4<forward_iterator_wrapper>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test4<bidirectional_iterator_wrapper>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test4<random_access_iterator_wrapper>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test4<contiguous_iterator_wrapper>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test5());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::vector<ThrowOnCopy> v;

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		ThrowOnCopy const t(1);
		EXPECT_THROW(v.insert(v.end(), t), ThrowOnCopy::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(0u, v.size());

		v.insert(v.end(), ThrowOnCopy(2));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 2, v[0].value);
	}
	{
		hamon::vector<ThrowOnCopy> v(2);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		ThrowOnCopy const t(1);
		EXPECT_THROW(v.insert(v.end(), t), ThrowOnCopy::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);

		v.insert(v.end(), ThrowOnCopy(2));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);
		EXPECT_EQ( 2, v[2].value);
	}
	{
		hamon::vector<ThrowOnCopy> v(2);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		EXPECT_THROW(v.insert(v.end(), 3, ThrowOnCopy(2)), ThrowOnCopy::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);
	}
	{
		hamon::vector<ThrowOnCopy> v(2);
		v.reserve(10);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		ThrowOnCopy const t(1);
		EXPECT_THROW(v.insert(v.end(), t), ThrowOnCopy::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);

		v.insert(v.end(), ThrowOnCopy(2));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);
		EXPECT_EQ( 2, v[2].value);
	}
	{
		hamon::vector<ThrowOnCopy> v1(3);
		hamon::vector<ThrowOnCopy> v2(2);

		auto const old_capacity = v2.capacity();
		auto const old_data = v2.data();
		EXPECT_THROW(v2.insert(v2.end(), v1.begin(), v1.end()), ThrowOnCopy::Exception);
		EXPECT_EQ(old_capacity, v2.capacity());
		EXPECT_EQ(old_data, v2.data());
		EXPECT_EQ(2u, v2.size());
		EXPECT_EQ(13, v2[0].value);
		EXPECT_EQ(13, v2[1].value);
	}
	{
		hamon::vector<ThrowOnMove> v(3);

		ThrowOnMove const t(1);
		v.insert(v.end(), t);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(14, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ( 1, v[3].value);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		EXPECT_THROW(v.insert(v.end(), ThrowOnMove(2)), ThrowOnMove::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(14, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ( 1, v[3].value);
	}
	{
		hamon::vector<ThrowOnMove> v(3);
		v.reserve(10);

		ThrowOnMove const t(1);
		v.insert(v.end(), t);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(14, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ( 1, v[3].value);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		EXPECT_THROW(v.insert(v.end(), ThrowOnMove(2)), ThrowOnMove::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(14, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ( 1, v[3].value);
	}
#endif
}

}	// namespace insert_test

}	// namespace hamon_vector_test
