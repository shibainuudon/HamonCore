/**
 *	@file	unit_test_inplace_vector_try_push_back.cpp
 *
 *	@brief	try_push_back のテスト
 *
 *	constexpr pointer try_push_back(const T& x);
 *	constexpr pointer try_push_back(T&& x);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/string.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace try_push_back_test
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
};

struct ThrowOnMove
{
	struct Exception{};

	int value;

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
};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using Pointer = typename InplaceVector::pointer;

	{
		InplaceVector v;
		static_assert(hamon::is_same<decltype(v.try_push_back(hamon::declval<T const&>())), Pointer>::value, "");
		static_assert(hamon::is_same<decltype(v.try_push_back(hamon::declval<T&&>())), Pointer>::value, "");
		static_assert(!noexcept(v.try_push_back(hamon::declval<T const&>())), "");
		static_assert(!noexcept(v.try_push_back(hamon::declval<T&&>())), "");
	}

	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		{
			auto p = v.try_push_back(T{42});
			if (v.capacity() == 0)
			{
				VERIFY(p == nullptr);
				VERIFY(v.empty());
				return true;
			}
			VERIFY(p == &v.back());
			VERIFY(*p == T{42});
			VERIFY(!v.empty());
			VERIFY(v.size() == 1);
			VERIFY(v[0] == T{42});
		}
		{
			T const t{43};
			auto p = v.try_push_back(t);
			if (v.capacity() == 1)
			{
				VERIFY(p == nullptr);
				VERIFY(v.size() == 1);
				return true;
			}
			VERIFY(p == &v.back());
			VERIFY(*p == T{43});
			VERIFY(!v.empty());
			VERIFY(v.size() == 2);
			VERIFY(v[0] == T{42});
			VERIFY(v[1] == T{43});
		}
		{
			auto p = v.try_push_back(T{44});
			if (v.capacity() == 2)
			{
				VERIFY(p == nullptr);
				VERIFY(v.size() == 2);
				return true;
			}
			VERIFY(p == &v.back());
			VERIFY(*p == T{44});
			VERIFY(!v.empty());
			VERIFY(v.size() == 3);
			VERIFY(v[0] == T{42});
			VERIFY(v[1] == T{43});
			VERIFY(v[2] == T{44});
		}
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY((test_impl<T, 0>()));
	VERIFY((test_impl<T, 1>()));
	VERIFY((test_impl<T, 2>()));
	VERIFY((test_impl<T, 3>()));
	VERIFY((test_impl<T, 9>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, TryPushBackTest)
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
		EXPECT_NO_THROW(v.try_push_back(1));
		EXPECT_TRUE(v.empty());
		EXPECT_EQ(0u, v.size());
	}
	{
		hamon::inplace_vector<int, 1> v;
		EXPECT_NO_THROW(v.try_push_back(10));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0]);
		EXPECT_NO_THROW(v.try_push_back(20));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0]);
	}
	{
		hamon::inplace_vector<ThrowOnCopy, 3> v;
		EXPECT_TRUE(v.empty());
		ThrowOnCopy const t{42};
		EXPECT_THROW(v.try_push_back(t), ThrowOnCopy::Exception);
		EXPECT_TRUE(v.empty());
		EXPECT_NO_THROW(v.try_push_back(ThrowOnCopy{10}));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_THROW(v.try_push_back(t), ThrowOnCopy::Exception);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_NO_THROW(v.try_push_back(ThrowOnCopy{20}));
		EXPECT_THROW(v.try_push_back(t), ThrowOnCopy::Exception);
		EXPECT_NO_THROW(v.try_push_back(ThrowOnCopy{30}));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_EQ(30, v[2].value);
		EXPECT_NO_THROW(v.try_push_back(t));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_EQ(30, v[2].value);
	}
	{
		ThrowOnMove const t1{10};
		ThrowOnMove const t2{11};
		ThrowOnMove const t3{12};
		hamon::inplace_vector<ThrowOnMove, 3> v;
		EXPECT_TRUE(v.empty());
		EXPECT_THROW(v.try_push_back(ThrowOnMove{10}), ThrowOnMove::Exception);
		EXPECT_TRUE(v.empty());
		EXPECT_NO_THROW(v.try_push_back(t1));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_THROW(v.try_push_back(ThrowOnMove{20}), ThrowOnMove::Exception);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_NO_THROW(v.try_push_back(t2));
		EXPECT_THROW(v.try_push_back(ThrowOnMove{30}), ThrowOnMove::Exception);
		EXPECT_NO_THROW(v.try_push_back(t3));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(11, v[1].value);
		EXPECT_EQ(12, v[2].value);
		EXPECT_NO_THROW(v.try_push_back(t1));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(11, v[1].value);
		EXPECT_EQ(12, v[2].value);
	}
#endif

	// https://en.cppreference.com/w/cpp/container/inplace_vector/try_push_back
	{
		hamon::inplace_vector<hamon::string, 2> pets;
		hamon::string dog {"dog"};

		hamon::string* p1 = pets.try_push_back("cat"); // overload (1)
		EXPECT_TRUE(*p1 == "cat" and pets.size() == 1);

		hamon::string* p2 = pets.try_push_back(hamon::move(dog)); // overload (2)
		EXPECT_TRUE(*p2 == "dog" and pets.size() == 2);

		EXPECT_TRUE(pets[0] == "cat" and pets[1] == "dog");
		EXPECT_TRUE(pets.size() == pets.capacity());

		hamon::string* p3 = pets.try_push_back("bug");
		EXPECT_TRUE(p3 == nullptr and pets.size() == 2);
	}
}

}	// namespace try_push_back_test

}	// namespace hamon_inplace_vector_test
