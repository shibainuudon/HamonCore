/**
 *	@file	unit_test_vector_assign.cpp
 *
 *	@brief	assign のテスト
 *
 *	template<class InputIterator>
 *	constexpr void assign(InputIterator first, InputIterator last);
 *	constexpr void assign(size_type n, const T& u);
 *	constexpr void assign(initializer_list<T>);
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_vector_test
{

namespace assign_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, template <typename> class IteratorWrapper>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Vector = hamon::vector<T>;
	using Iterator = IteratorWrapper<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector>().assign(hamon::declval<Iterator>(), hamon::declval<Iterator>())),
		void
	>::value, "");
	static_assert(!noexcept(
		hamon::declval<Vector>().assign(hamon::declval<Iterator>(), hamon::declval<Iterator>())), "");

	{
		T a[] = {1, 2, 3, 4, 5};
		Vector v;

		v.assign(Iterator{a}, Iterator{a + 5});
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 4);
		VERIFY(v[4] == 5);

		v.assign(Iterator{a + 1}, Iterator{a + 4});
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 2);
		VERIFY(v[1] == 3);
		VERIFY(v[2] == 4);
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test2()
{
	using Vector = hamon::vector<T>;
	using SizeType = typename Vector::size_type;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector>().assign(hamon::declval<SizeType>(), hamon::declval<T const&>())),
		void
	>::value, "");
	static_assert(!noexcept(
		hamon::declval<Vector>().assign(hamon::declval<SizeType>(), hamon::declval<T const&>())), "");

	{
		Vector v;

		v.assign(3, 42);
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 42);
		VERIFY(v[1] == 42);
		VERIFY(v[2] == 42);

		v.assign(5, 13);
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 13);
		VERIFY(v[1] == 13);
		VERIFY(v[2] == 13);
		VERIFY(v[3] == 13);
		VERIFY(v[4] == 13);

		v.assign(1, 10);
		VERIFY(v.size() == 1);
		VERIFY(v[0] == 10);

		v.assign(0, 99);
		VERIFY(v.size() == 0);
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test3()
{
	using Vector = hamon::vector<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector>().assign(hamon::declval<std::initializer_list<T>>())),
		void
	>::value, "");
	static_assert(!noexcept(
		hamon::declval<Vector>().assign(hamon::declval<std::initializer_list<T>>())), "");

	{
		Vector v;

		v.assign({1,2,3});
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);

		v.assign({10,11,12,13});
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 11);
		VERIFY(v[2] == 12);
		VERIFY(v[3] == 13);

		v.assign({5,6});
		VERIFY(v.size() == 2);
		VERIFY(v[0] == 5);
		VERIFY(v[1] == 6);

		v.assign({});
		VERIFY(v.size() == 0);
	}

	return true;
}

#undef VERIFY

struct S
{
	static int default_ctor_count;
	static int copy_ctor_count;
	static int move_ctor_count;
	static int copy_assign_count;
	static int move_assign_count;
	static int dtor_count;

	S() noexcept
	{
		++default_ctor_count;
	}

	S(S const&) noexcept
	{
		++copy_ctor_count;
	}

	S(S&&) noexcept
	{
		++move_ctor_count;
	}

	S& operator=(S const&) noexcept
	{
		++copy_assign_count;
		return *this;
	}

	S& operator=(S&&) noexcept
	{
		++move_assign_count;
		return *this;
	}

	~S() noexcept
	{
		++dtor_count;
	}

	static void Reset()
	{
		default_ctor_count = 0;
		copy_ctor_count = 0;
		move_ctor_count = 0;
		copy_assign_count = 0;
		move_assign_count = 0;
		dtor_count = 0;
	}
};

int S::default_ctor_count = 0;
int S::copy_ctor_count = 0;
int S::move_ctor_count = 0;
int S::copy_assign_count = 0;
int S::move_assign_count = 0;
int S::dtor_count = 0;

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
#endif

GTEST_TEST(VectorTest, AssignTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int, cpp17_input_iterator_wrapper>()));
//	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int, input_iterator_wrapper>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int, forward_iterator_wrapper>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int, bidirectional_iterator_wrapper>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int, random_access_iterator_wrapper>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int, contiguous_iterator_wrapper>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<char, cpp17_input_iterator_wrapper>()));
//	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<char, input_iterator_wrapper>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<char, forward_iterator_wrapper>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<char, bidirectional_iterator_wrapper>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<char, random_access_iterator_wrapper>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<char, contiguous_iterator_wrapper>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2<unsigned int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test3<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test3<unsigned char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test3<float>());

	S::Reset();
	{
		using Iterator = cpp17_input_iterator_wrapper<S>;
		hamon::vector<S> v;
		{
			S a[3]{};
			EXPECT_EQ(3, S::default_ctor_count);
			EXPECT_EQ(0, S::copy_ctor_count);
			EXPECT_EQ(0, S::move_ctor_count);
			EXPECT_EQ(0, S::copy_assign_count);
			EXPECT_EQ(0, S::move_assign_count);
			EXPECT_EQ(0, S::dtor_count);

			v.assign(Iterator{a}, Iterator{a + 2});
			EXPECT_EQ(3, S::default_ctor_count);
			EXPECT_EQ(2, S::copy_ctor_count);
			EXPECT_EQ(3, S::move_ctor_count);
			EXPECT_EQ(0, S::copy_assign_count);
			EXPECT_EQ(0, S::move_assign_count);
//			EXPECT_EQ(3, S::dtor_count);

			v.assign(Iterator{a}, Iterator{a});
			EXPECT_EQ(3, S::default_ctor_count);
			EXPECT_EQ(2, S::copy_ctor_count);
			EXPECT_EQ(3, S::move_ctor_count);
			EXPECT_EQ(0, S::copy_assign_count);
			EXPECT_EQ(0, S::move_assign_count);
//			EXPECT_EQ(5, S::dtor_count);

			v.assign(Iterator{a}, Iterator{a + 1});
			EXPECT_EQ(3, S::default_ctor_count);
			EXPECT_EQ(3, S::copy_ctor_count);
			EXPECT_EQ(4, S::move_ctor_count);
			EXPECT_EQ(0, S::copy_assign_count);
			EXPECT_EQ(0, S::move_assign_count);
//			EXPECT_EQ(6, S::dtor_count);

			v.assign(Iterator{a}, Iterator{a + 3});
			EXPECT_EQ(3, S::default_ctor_count);
			EXPECT_EQ(6, S::copy_ctor_count);
			EXPECT_EQ(8, S::move_ctor_count);
			EXPECT_EQ(0, S::copy_assign_count);
			EXPECT_EQ(1, S::move_assign_count);
//			EXPECT_EQ(11, S::dtor_count);
		}
		EXPECT_EQ(3, S::default_ctor_count);
		EXPECT_EQ(6, S::copy_ctor_count);
		EXPECT_EQ(8, S::move_ctor_count);
		EXPECT_EQ(0, S::copy_assign_count);
		EXPECT_EQ(1, S::move_assign_count);
//		EXPECT_EQ(14, S::dtor_count);
	}
	EXPECT_EQ(3, S::default_ctor_count);
	EXPECT_EQ(6, S::copy_ctor_count);
	EXPECT_EQ(8, S::move_ctor_count);
	EXPECT_EQ(0, S::copy_assign_count);
	EXPECT_EQ(1, S::move_assign_count);
//	EXPECT_EQ(17, S::dtor_count);

	S::Reset();
	{
		using Iterator = forward_iterator_wrapper<S>;
		hamon::vector<S> v;
		{
			S a[3]{};
			EXPECT_EQ(3, S::default_ctor_count);
			EXPECT_EQ(0, S::copy_ctor_count);
			EXPECT_EQ(0, S::move_ctor_count);
			EXPECT_EQ(0, S::copy_assign_count);
			EXPECT_EQ(0, S::move_assign_count);
			EXPECT_EQ(0, S::dtor_count);

			v.assign(Iterator{a}, Iterator{a + 2});
			EXPECT_EQ(3, S::default_ctor_count);
			EXPECT_EQ(2, S::copy_ctor_count);
			EXPECT_EQ(0, S::move_ctor_count);
			EXPECT_EQ(0, S::copy_assign_count);
			EXPECT_EQ(0, S::move_assign_count);
			EXPECT_EQ(0, S::dtor_count);

			v.assign(Iterator{a}, Iterator{a});
			EXPECT_EQ(3, S::default_ctor_count);
			EXPECT_EQ(2, S::copy_ctor_count);
			EXPECT_EQ(0, S::move_ctor_count);
			EXPECT_EQ(0, S::copy_assign_count);
			EXPECT_EQ(0, S::move_assign_count);
			EXPECT_EQ(2, S::dtor_count);

			v.assign(Iterator{a}, Iterator{a + 1});
			EXPECT_EQ(3, S::default_ctor_count);
			EXPECT_EQ(3, S::copy_ctor_count);
			EXPECT_EQ(0, S::move_ctor_count);
			EXPECT_EQ(0, S::copy_assign_count);
			EXPECT_EQ(0, S::move_assign_count);
			EXPECT_EQ(2, S::dtor_count);

			v.assign(Iterator{a}, Iterator{a + 3});
			EXPECT_EQ(3, S::default_ctor_count);
			EXPECT_EQ(6, S::copy_ctor_count);
			EXPECT_EQ(0, S::move_ctor_count);
			EXPECT_EQ(0, S::copy_assign_count);
			EXPECT_EQ(0, S::move_assign_count);
			EXPECT_EQ(3, S::dtor_count);
		}
		EXPECT_EQ(3, S::default_ctor_count);
		EXPECT_EQ(6, S::copy_ctor_count);
		EXPECT_EQ(0, S::move_ctor_count);
		EXPECT_EQ(0, S::copy_assign_count);
		EXPECT_EQ(0, S::move_assign_count);
		EXPECT_EQ(6, S::dtor_count);
	}
	EXPECT_EQ(3, S::default_ctor_count);
	EXPECT_EQ(6, S::copy_ctor_count);
	EXPECT_EQ(0, S::move_ctor_count);
	EXPECT_EQ(0, S::copy_assign_count);
	EXPECT_EQ(0, S::move_assign_count);
	EXPECT_EQ(9, S::dtor_count);

	S::Reset();
	{
		hamon::vector<S> v;
		{
			S x;
			EXPECT_EQ(1, S::default_ctor_count);
			EXPECT_EQ(0, S::copy_ctor_count);
			EXPECT_EQ(0, S::move_ctor_count);
			EXPECT_EQ(0, S::copy_assign_count);
			EXPECT_EQ(0, S::move_assign_count);
			EXPECT_EQ(0, S::dtor_count);

			v.assign(5, x);
			EXPECT_EQ(1, S::default_ctor_count);
			EXPECT_EQ(5, S::copy_ctor_count);
			EXPECT_EQ(0, S::move_ctor_count);
			EXPECT_EQ(0, S::copy_assign_count);
			EXPECT_EQ(0, S::move_assign_count);
			EXPECT_EQ(0, S::dtor_count);

			v.assign(2, x);
			EXPECT_EQ(1, S::default_ctor_count);
			EXPECT_EQ(5, S::copy_ctor_count);
			EXPECT_EQ(0, S::move_ctor_count);
			EXPECT_EQ(2, S::copy_assign_count);
			EXPECT_EQ(0, S::move_assign_count);
			EXPECT_EQ(3, S::dtor_count);

			v.assign(5, x);
			EXPECT_EQ(1, S::default_ctor_count);
			EXPECT_EQ(8, S::copy_ctor_count);
			EXPECT_EQ(0, S::move_ctor_count);
			EXPECT_EQ(4, S::copy_assign_count);
			EXPECT_EQ(0, S::move_assign_count);
			EXPECT_EQ(3, S::dtor_count);
		}
		EXPECT_EQ(1, S::default_ctor_count);
		EXPECT_EQ(8, S::copy_ctor_count);
		EXPECT_EQ(0, S::move_ctor_count);
		EXPECT_EQ(4, S::copy_assign_count);
		EXPECT_EQ(0, S::move_assign_count);
		EXPECT_EQ(4, S::dtor_count);
	}
	EXPECT_EQ(1, S::default_ctor_count);
	EXPECT_EQ(8, S::copy_ctor_count);
	EXPECT_EQ(0, S::move_ctor_count);
	EXPECT_EQ(4, S::copy_assign_count);
	EXPECT_EQ(0, S::move_assign_count);
	EXPECT_EQ(9, S::dtor_count);

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::vector<ThrowOnCopy> v;

		ThrowOnCopy x(12);

		EXPECT_THROW(v.assign(3, x), ThrowOnCopy::Exception);
		EXPECT_EQ(0u, v.size());

		v.emplace_back(10);
		v.emplace_back(11);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		EXPECT_THROW(v.assign(3, x), ThrowOnCopy::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(11, v[1].value);

		v.assign(0, x);
		EXPECT_EQ(0u, v.size());
	}
	{
		using Iterator = cpp17_input_iterator_wrapper<ThrowOnCopy>;

		hamon::vector<ThrowOnCopy> v;

		ThrowOnCopy a[] = {ThrowOnCopy{1}, ThrowOnCopy{2}, ThrowOnCopy{3}};

		EXPECT_THROW(v.assign(Iterator{a}, Iterator{a + 3}), ThrowOnCopy::Exception);
		EXPECT_EQ(0u, v.size());

		v.emplace_back(10);
		v.emplace_back(11);
		v.emplace_back(12);
		v.emplace_back(13);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		EXPECT_THROW(v.assign(Iterator{a}, Iterator{a + 2}), ThrowOnCopy::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(11, v[1].value);
		EXPECT_EQ(12, v[2].value);
		EXPECT_EQ(13, v[3].value);

		v.assign(Iterator{a}, Iterator{a});
		EXPECT_EQ(0u, v.size());
	}
	{
		using Iterator = forward_iterator_wrapper<ThrowOnCopy>;

		hamon::vector<ThrowOnCopy> v;

		ThrowOnCopy a[] = {ThrowOnCopy{1}, ThrowOnCopy{2}, ThrowOnCopy{3}};

		EXPECT_THROW(v.assign(Iterator{a}, Iterator{a + 3}), ThrowOnCopy::Exception);
		EXPECT_EQ(0u, v.size());

		v.emplace_back(10);
		v.emplace_back(11);
		v.emplace_back(12);
		v.emplace_back(13);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		EXPECT_THROW(v.assign(Iterator{a}, Iterator{a + 2}), ThrowOnCopy::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(11, v[1].value);
		EXPECT_EQ(12, v[2].value);
		EXPECT_EQ(13, v[3].value);

		v.assign(Iterator{a}, Iterator{a});
		EXPECT_EQ(0u, v.size());
	}
#endif
}

}	// namespace assign_test

}	// namespace hamon_vector_test
