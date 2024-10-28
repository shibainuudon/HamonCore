/**
 *	@file	unit_test_inplace_vector_resize.cpp
 *
 *	@brief	resize のテスト
 *
 *	constexpr void resize(size_type sz);
 *
 *	constexpr void resize(size_type sz, const T& c);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace resize_test
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

	ThrowOnCopy()
	{
	}

	ThrowOnCopy(int)
	{
	}

	ThrowOnCopy(ThrowOnCopy const&)
	{
		throw Exception{};
	}
};

struct ThrowOnDefaultCtor
{
	struct Exception{};

	ThrowOnDefaultCtor()
	{
		throw Exception{};
	}

	ThrowOnDefaultCtor(int)
	{
	}
};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using SizeType = typename InplaceVector::size_type;

	{
		InplaceVector v;
		SizeType const sz{};
		T const c{};
		static_assert(hamon::is_same<decltype(v.resize(sz)), void>::value, "");
		static_assert(hamon::is_same<decltype(v.resize(sz, c)), void>::value, "");
		static_assert(!noexcept(v.resize(sz)), "");
		static_assert(!noexcept(v.resize(sz, c)), "");
	}
	{
		InplaceVector v;

		v.resize(0);
		VERIFY(v.empty());

		v.resize(0, T{42});
		VERIFY(v.empty());
	}

	return true;
}

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_5()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v;

		v.resize(2);
		VERIFY(v.size() == 2);
		VERIFY(v[0] == T{});
		VERIFY(v[1] == T{});

		v.resize(5, T{10});
		VERIFY(v.size() == 5);
		VERIFY(v[0] == T{});
		VERIFY(v[1] == T{});
		VERIFY(v[2] == T{10});
		VERIFY(v[3] == T{10});
		VERIFY(v[4] == T{10});

		v.resize(3, T{11});
		VERIFY(v.size() == 3);
		VERIFY(v[0] == T{});
		VERIFY(v[1] == T{});
		VERIFY(v[2] == T{10});

		v.resize(4, T{12});
		VERIFY(v.size() == 4);
		VERIFY(v[0] == T{});
		VERIFY(v[1] == T{});
		VERIFY(v[2] == T{10});
		VERIFY(v[3] == T{12});

		v.resize(5);
		VERIFY(v.size() == 5);
		VERIFY(v[0] == T{});
		VERIFY(v[1] == T{});
		VERIFY(v[2] == T{10});
		VERIFY(v[3] == T{12});
		VERIFY(v[4] == T{});
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY((test_impl_0<T, 0>()));
	VERIFY((test_impl_0<T, 1>()));
	VERIFY((test_impl_0<T, 5>()));
	VERIFY((test_impl_0<T, 9>()));
	VERIFY((test_impl_0<T, 10>()));

//	VERIFY((test_impl_5<T, 0>()));
//	VERIFY((test_impl_5<T, 1>()));
	VERIFY((test_impl_5<T, 5>()));
	VERIFY((test_impl_5<T, 9>()));
	VERIFY((test_impl_5<T, 10>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, ResizeTest)
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
		EXPECT_NO_THROW(v.resize(0));
		EXPECT_THROW   (v.resize(1), hamon::bad_alloc);
	}
	{
		hamon::inplace_vector<int, 0> v;
		EXPECT_NO_THROW(v.resize(0, 13));
		EXPECT_THROW   (v.resize(1, 13), hamon::bad_alloc);
	}
	{
		hamon::inplace_vector<int, 3> v;
		EXPECT_NO_THROW(v.resize(1));
		EXPECT_NO_THROW(v.resize(2));
		EXPECT_NO_THROW(v.resize(3));
		EXPECT_THROW   (v.resize(4), hamon::bad_alloc);
		EXPECT_NO_THROW(v.resize(3));
	}
	{
		hamon::inplace_vector<int, 4> v;
		EXPECT_NO_THROW(v.resize(1, 42));
		EXPECT_NO_THROW(v.resize(2, 42));
		EXPECT_NO_THROW(v.resize(3, 42));
		EXPECT_NO_THROW(v.resize(4, 42));
		EXPECT_THROW   (v.resize(5, 42), hamon::bad_alloc);
		EXPECT_NO_THROW(v.resize(4, 42));
	}
	{
		hamon::inplace_vector<ThrowOnCopy, 5> v;
		EXPECT_NO_THROW(v.resize(0));
		EXPECT_NO_THROW(v.resize(1));
		EXPECT_NO_THROW(v.resize(5));
		EXPECT_THROW   (v.resize(6), hamon::bad_alloc);
	}
	{
		hamon::inplace_vector<ThrowOnCopy, 5> v;
		EXPECT_NO_THROW(v.resize(0, ThrowOnCopy{42}));
		EXPECT_THROW   (v.resize(1, ThrowOnCopy{42}), ThrowOnCopy::Exception);
		EXPECT_THROW   (v.resize(5, ThrowOnCopy{42}), ThrowOnCopy::Exception);
		EXPECT_THROW   (v.resize(6, ThrowOnCopy{42}), hamon::bad_alloc);
	}
	{
		hamon::inplace_vector<ThrowOnDefaultCtor, 5> v;
		EXPECT_NO_THROW(v.resize(0));
		EXPECT_THROW   (v.resize(1), ThrowOnDefaultCtor::Exception);
		EXPECT_THROW   (v.resize(5), ThrowOnDefaultCtor::Exception);
		EXPECT_THROW   (v.resize(6), hamon::bad_alloc);
	}
	{
		hamon::inplace_vector<ThrowOnDefaultCtor, 5> v;
		EXPECT_NO_THROW(v.resize(0, ThrowOnDefaultCtor{42}));
		EXPECT_NO_THROW(v.resize(1, ThrowOnDefaultCtor{42}));
		EXPECT_NO_THROW(v.resize(5, ThrowOnDefaultCtor{42}));
		EXPECT_THROW   (v.resize(6, ThrowOnDefaultCtor{42}), hamon::bad_alloc);
	}
#endif

	// https://en.cppreference.com/w/cpp/container/inplace_vector/resize
	{
		auto print = [](hamon::inplace_vector<int, 6> const& v)
		{
			std::stringstream ss;
			for (auto const& e : v)
			{
				ss << e << ", ";
			}
			return ss.str();
		};

		hamon::inplace_vector<int, 6> v(6, 9);
		// Initially
		EXPECT_EQ("9, 9, 9, 9, 9, 9, ", print(v));

		v.resize(2);
		// After resize(2)
		EXPECT_EQ("9, 9, ", print(v));

		v.resize(4);
		// After resize(4)
		EXPECT_EQ("9, 9, 0, 0, ", print(v));

		v.resize(6, -1);
		// After resize(6, -1)
		EXPECT_EQ("9, 9, 0, 0, -1, -1, ", print(v));

#if !defined(HAMON_NO_EXCEPTIONS)
		// Trying resize(13)
		EXPECT_THROW(v.resize(13), hamon::bad_alloc); // throws, because count > N; v is left unchanged

		// After exception
		EXPECT_EQ("9, 9, 0, 0, -1, -1, ", print(v));
#endif
	}
}

}	// namespace resize_test

}	// namespace hamon_inplace_vector_test
