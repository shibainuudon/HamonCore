/**
 *	@file	unit_test_inplace_vector_push_back.cpp
 *
 *	@brief	push_back のテスト
 *
 *	constexpr reference push_back(const T& x);
 *	constexpr reference push_back(T&& x);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/string.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace push_back_test
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
HAMON_CXX14_CONSTEXPR bool test_impl_1()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using Reference = typename InplaceVector::reference;

	{
		InplaceVector v;
		static_assert(hamon::is_same<decltype(v.push_back(hamon::declval<T const&>())), Reference>::value, "");
		static_assert(hamon::is_same<decltype(v.push_back(hamon::declval<T&&>())), Reference>::value, "");
		static_assert(!noexcept(v.push_back(hamon::declval<T const&>())), "");
		static_assert(!noexcept(v.push_back(hamon::declval<T&&>())), "");
	}

	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		T const t{43};
		auto& r = v.push_back(t);
		VERIFY(&r == &v.back());
		VERIFY(r == t);
		VERIFY(!v.empty());
		VERIFY(v.size() == 1);
		VERIFY(v[0] == t);
	}
	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		auto& r = v.push_back(T{42});
		VERIFY(&r == &v.back());
		VERIFY(r == T{42});
		VERIFY(!v.empty());
		VERIFY(v.size() == 1);
		VERIFY(v[0] == T{42});
	}

	return true;
}

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_3()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		{
			T const t{10};
			auto& r = v.push_back(t);
			VERIFY(&r == &v.back());
			VERIFY(r == T{10});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 1);
		VERIFY(v[0] == T{10});
		{
			auto& r = v.push_back(T{20});
			VERIFY(&r == &v.back());
			VERIFY(r == T{20});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 2);
		VERIFY(v[0] == T{10});
		VERIFY(v[1] == T{20});
		{
			auto& r = v.push_back(T{30});
			VERIFY(&r == &v.back());
			VERIFY(r == T{30});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v[0] == T{10});
		VERIFY(v[1] == T{20});
		VERIFY(v[2] == T{30});
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY((test_impl_1<T, 1>()));
	VERIFY((test_impl_1<T, 2>()));
	VERIFY((test_impl_1<T, 3>()));
	VERIFY((test_impl_1<T, 9>()));

//	VERIFY((test_impl_3<T, 1>()));
//	VERIFY((test_impl_3<T, 2>()));
	VERIFY((test_impl_3<T, 3>()));
	VERIFY((test_impl_3<T, 9>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, PushBackTest)
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
		EXPECT_THROW(v.push_back(1), hamon::bad_alloc);
		EXPECT_TRUE(v.empty());
		EXPECT_EQ(0u, v.size());
	}
	{
		hamon::inplace_vector<int, 1> v;
		EXPECT_NO_THROW(v.push_back(10));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0]);
		EXPECT_THROW(v.push_back(20), hamon::bad_alloc);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0]);
	}
	{
		hamon::inplace_vector<ThrowOnCopy, 3> v;
		EXPECT_TRUE(v.empty());
		ThrowOnCopy const t{42};
		EXPECT_THROW(v.push_back(t), ThrowOnCopy::Exception);
		EXPECT_TRUE(v.empty());
		EXPECT_NO_THROW(v.push_back(ThrowOnCopy{10}));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_THROW(v.push_back(t), ThrowOnCopy::Exception);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_NO_THROW(v.push_back(ThrowOnCopy{20}));
		EXPECT_THROW(v.push_back(t), ThrowOnCopy::Exception);
		EXPECT_NO_THROW(v.push_back(ThrowOnCopy{30}));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_EQ(30, v[2].value);
		EXPECT_THROW(v.push_back(t), hamon::bad_alloc);
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
		EXPECT_THROW(v.push_back(ThrowOnMove{10}), ThrowOnMove::Exception);
		EXPECT_TRUE(v.empty());
		EXPECT_NO_THROW(v.push_back(t1));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_THROW(v.push_back(ThrowOnMove{20}), ThrowOnMove::Exception);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_NO_THROW(v.push_back(t2));
		EXPECT_THROW(v.push_back(ThrowOnMove{30}), ThrowOnMove::Exception);
		EXPECT_NO_THROW(v.push_back(t3));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(11, v[1].value);
		EXPECT_EQ(12, v[2].value);
		EXPECT_THROW(v.push_back(t1), hamon::bad_alloc);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(11, v[1].value);
		EXPECT_EQ(12, v[2].value);
	}
#endif

	// https://en.cppreference.com/w/cpp/container/inplace_vector/push_back
	{
		auto print = [](hamon::inplace_vector<hamon::string, 2> const& v)
		{
			std::stringstream ss;
			for (auto const& e : v)
			{
				ss << e << ", ";
			}
			return ss.str();
		};

		hamon::inplace_vector<hamon::string, 2> fauna;
		hamon::string cat {"CAT"};
		hamon::string dog {"DOG"};

		fauna.push_back(cat); // overload (1)
		EXPECT_EQ("CAT, ", print(fauna));

		fauna.push_back(hamon::move(dog)); // overload (2)
		EXPECT_EQ("CAT, DOG, ", print(fauna));

#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW(fauna.push_back("BUG"), hamon::bad_alloc); // throws: there is no space
		EXPECT_EQ("CAT, DOG, ", print(fauna));
#endif
	}
}

}	// namespace push_back_test

}	// namespace hamon_inplace_vector_test
