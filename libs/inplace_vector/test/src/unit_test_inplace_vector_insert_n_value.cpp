/**
 *	@file	unit_test_inplace_vector_insert_n_value.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr iterator insert(const_iterator position, size_type n, T& x);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace insert_n_value_test
{

struct S1
{
	int m_value;
	constexpr bool operator==(S1 const& y) const { return m_value == y.m_value; }
};

struct S2
{
	int m_value;
	S2() = default;
	constexpr S2(int v) : m_value(v) {}
	constexpr S2(S2 const& x) : m_value(x.m_value) {}
	S2& operator=(S2 const&) = default;
	S2& operator=(S2 &&) = default;
	constexpr bool operator==(S2 const& y) const { return m_value == y.m_value; }
};

struct S3
{
	int m_value;
	constexpr S3() : m_value(0) {}
	constexpr S3(int v) : m_value(v) {}
	constexpr S3(S3 const& x) : m_value(x.m_value) {}
	S3& operator=(S3 const&) = default;
	S3& operator=(S3 &&) = default;
	constexpr bool operator==(S3 const& y) const { return m_value == y.m_value; }
};

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnCopy
{
	struct Exception{};

	int value;

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

	ThrowOnCopy& operator=(ThrowOnCopy const&) = default;
	ThrowOnCopy& operator=(ThrowOnCopy &&) = default;
};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using SizeType = typename InplaceVector::size_type;
	using Iterator = typename InplaceVector::iterator;
	using ConstIterator = typename InplaceVector::const_iterator;

	{
		InplaceVector v;
		ConstIterator it;
		SizeType sz;
		static_assert(hamon::is_same<decltype(v.insert(it, sz, hamon::declval<T const&>())), Iterator>::value, "");
		static_assert(!noexcept(v.insert(it, sz, hamon::declval<T const&>())), "");
	}

	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		T const t{43};
		auto it = v.insert(v.end(), 0, t);
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
	}

	return true;
}

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_1()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		T const t{43};
		auto it = v.insert(v.end(), 1, t);
		VERIFY(it == v.begin());
		VERIFY(*it == t);
		VERIFY(!v.empty());
		VERIFY(v.size() == 1);
		VERIFY(v[0] == t);
	}

	return true;
}

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_5()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		{
			T const t{10};
			auto it = v.insert(v.end(), 3, t);
			VERIFY(it == v.begin());
			VERIFY(*it == T{10});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v[0] == T{10});
		VERIFY(v[1] == T{10});
		VERIFY(v[2] == T{10});
		{
			T const t{10};
			auto it = v.insert(v.end(), 0, t);
			VERIFY(it == v.end());
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v[0] == T{10});
		VERIFY(v[1] == T{10});
		VERIFY(v[2] == T{10});
		{
			auto it = v.insert(v.begin() + 1, 2, T{20});
			VERIFY(it == v.begin() + 1);
			VERIFY(*it == T{20});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v[0] == T{10});
		VERIFY(v[1] == T{20});
		VERIFY(v[2] == T{20});
		VERIFY(v[3] == T{10});
		VERIFY(v[4] == T{10});
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY((test_impl_0<T, 0>()));
	VERIFY((test_impl_0<T, 1>()));
	VERIFY((test_impl_0<T, 2>()));
	VERIFY((test_impl_0<T, 5>()));
	VERIFY((test_impl_0<T, 6>()));
	VERIFY((test_impl_0<T, 9>()));

//	VERIFY((test_impl_1<T, 0>()));
	VERIFY((test_impl_1<T, 1>()));
	VERIFY((test_impl_1<T, 2>()));
	VERIFY((test_impl_1<T, 5>()));
	VERIFY((test_impl_1<T, 6>()));
	VERIFY((test_impl_1<T, 9>()));

//	VERIFY((test_impl_5<T, 0>()));
//	VERIFY((test_impl_5<T, 1>()));
//	VERIFY((test_impl_5<T, 2>()));
	VERIFY((test_impl_5<T, 5>()));
	VERIFY((test_impl_5<T, 6>()));
	VERIFY((test_impl_5<T, 9>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, InsertNValueTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
	EXPECT_TRUE(test<S3>());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::inplace_vector<int, 0> v;
		EXPECT_THROW(v.insert(v.end(), 1, 1), hamon::bad_alloc);
		EXPECT_TRUE(v.empty());
		EXPECT_EQ(0u, v.size());
		EXPECT_NO_THROW(v.insert(v.end(), 0, 1));
		EXPECT_TRUE(v.empty());
		EXPECT_EQ(0u, v.size());
	}
	{
		hamon::inplace_vector<int, 1> v;
		EXPECT_NO_THROW(v.insert(v.begin(), 1, 10));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0]);
		EXPECT_THROW(v.insert(v.begin(), 1, 20), hamon::bad_alloc);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0]);
		EXPECT_NO_THROW(v.insert(v.begin(), 0, 20));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0]);
	}
	{
		hamon::inplace_vector<ThrowOnCopy, 3> v;
		EXPECT_TRUE(v.empty());
		ThrowOnCopy const t{42};
		EXPECT_THROW(v.insert(v.begin(), 1, t), ThrowOnCopy::Exception);
		EXPECT_TRUE(v.empty());
		EXPECT_NO_THROW(v.emplace(v.begin(), ThrowOnCopy{10}));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_NO_THROW(v.insert(v.begin(), 0, t));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_NO_THROW(v.emplace(v.begin(), ThrowOnCopy{20}));
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(20, v[0].value);
		EXPECT_EQ(10, v[1].value);
		EXPECT_NO_THROW(v.emplace(v.begin(), ThrowOnCopy{30}));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(30, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_EQ(10, v[2].value);
		EXPECT_THROW(v.insert(v.begin(), 1, t), hamon::bad_alloc);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(30, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_EQ(10, v[2].value);
		EXPECT_NO_THROW(v.insert(v.begin(), 0, t));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(30, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_EQ(10, v[2].value);
	}
#endif
}

}	// namespace insert_n_value_test

}	// namespace hamon_inplace_vector_test
