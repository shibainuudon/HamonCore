/**
 *	@file	unit_test_inplace_vector_insert_initializer_list.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr iterator insert(const_iterator position, initializer_list<T> il);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace insert_initializer_list_test
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
	using Iterator = typename InplaceVector::iterator;
	using ConstIterator = typename InplaceVector::const_iterator;

	{
		InplaceVector v;
		ConstIterator pos;
		std::initializer_list<T> il;
		static_assert(hamon::is_same<decltype(v.insert(pos, il)), Iterator>::value, "");
		static_assert(!noexcept(v.insert(pos, il)), "");
	}
	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		auto it = v.insert(v.begin(), {});
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
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

		{
			auto it = v.insert(v.end(), {T{1}, T{2}});
			VERIFY(it == v.begin());
			VERIFY(*it == T{1});
		}
		VERIFY(v.size() == 2);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{2});

		{
			auto it = v.insert(v.begin()+1, {T{3}, T{4}, T{5}});
			VERIFY(it == v.begin()+1);
			VERIFY(*it == T{3});
		}
		VERIFY(v.size() == 5);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{3});
		VERIFY(v[2] == T{4});
		VERIFY(v[3] == T{5});
		VERIFY(v[4] == T{2});
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

//	VERIFY((test_impl_5<T, 0>()));
//	VERIFY((test_impl_5<T, 1>()));
//	VERIFY((test_impl_5<T, 2>()));
	VERIFY((test_impl_5<T, 5>()));
	VERIFY((test_impl_5<T, 6>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, InsertInitializerListTest)
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
		EXPECT_THROW(v.insert(v.end(), {1}), hamon::bad_alloc);
		EXPECT_TRUE(v.empty());
		EXPECT_EQ(0u, v.size());
		EXPECT_NO_THROW(v.insert(v.end(), {}));
		EXPECT_TRUE(v.empty());
		EXPECT_EQ(0u, v.size());
	}
	{
		hamon::inplace_vector<int, 1> v;
		EXPECT_NO_THROW(v.insert(v.end(), {1}));
		EXPECT_TRUE(!v.empty());
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_THROW(v.insert(v.end(), {1}), hamon::bad_alloc);
		EXPECT_TRUE(!v.empty());
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(1, v[0]);
	}
	{
		hamon::inplace_vector<ThrowOnCopy, 3> v;
		EXPECT_TRUE(v.empty());
		EXPECT_THROW(v.insert(v.begin(), {{1}, {2}}), ThrowOnCopy::Exception);
		EXPECT_TRUE(v.empty());
		EXPECT_NO_THROW(v.insert(v.begin(), {}));
		EXPECT_TRUE(v.empty());
		v.emplace_back(1);
		v.emplace_back(2);
		v.emplace_back(3);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(1, v[0].value);
		EXPECT_EQ(2, v[1].value);
		EXPECT_EQ(3, v[2].value);
		EXPECT_THROW(v.insert(v.begin(), {{1}, {2}}), hamon::bad_alloc);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(1, v[0].value);
		EXPECT_EQ(2, v[1].value);
		EXPECT_EQ(3, v[2].value);
	}
#endif
}

}	// namespace insert_initializer_list_test

}	// namespace hamon_inplace_vector_test
