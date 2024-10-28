/**
 *	@file	unit_test_inplace_vector_insert.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr iterator insert(const_iterator position, const T& x);
 *	constexpr iterator insert(const_iterator position, T&& x);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/iterator/size.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace insert_test
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
HAMON_CXX14_CONSTEXPR bool test_impl_1()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using Iterator = typename InplaceVector::iterator;
	using ConstIterator = typename InplaceVector::const_iterator;

	{
		InplaceVector v;
		ConstIterator it;
		static_assert(hamon::is_same<decltype(v.insert(it, hamon::declval<T const&>())), Iterator>::value, "");
		static_assert(hamon::is_same<decltype(v.insert(it, hamon::declval<T&&>())), Iterator>::value, "");
		static_assert(!noexcept(v.insert(it, hamon::declval<T const&>())), "");
		static_assert(!noexcept(v.insert(it, hamon::declval<T&&>())), "");
	}

	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		T const t{43};
		auto it = v.insert(v.end(), t);
		VERIFY(it == v.begin());
		VERIFY(*it == t);
		VERIFY(!v.empty());
		VERIFY(v.size() == 1);
		VERIFY(v[0] == t);
	}
	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		auto it = v.insert(v.begin(), T{42});
		VERIFY(it == v.begin());
		VERIFY(*it == T{42});
		VERIFY(!v.empty());
		VERIFY(v.size() == 1);
		VERIFY(v[0] == T{42});
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
			auto it = v.insert(v.end(), t);
			VERIFY(it == v.begin());
			VERIFY(*it == T{10});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 1);
		VERIFY(v[0] == T{10});
		{
			auto it = v.insert(v.end(), T{20});
			VERIFY(it == v.begin() + 1);
			VERIFY(*it == T{20});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 2);
		VERIFY(v[0] == T{10});
		VERIFY(v[1] == T{20});
		{
			auto it = v.insert(v.end(), T{30});
			VERIFY(it == v.begin() + 2);
			VERIFY(*it == T{30});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v[0] == T{10});
		VERIFY(v[1] == T{20});
		VERIFY(v[2] == T{30});
		{
			auto it = v.insert(v.begin(), T{40});
			VERIFY(it == v.begin());
			VERIFY(*it == T{40});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 4);
		VERIFY(v[0] == T{40});
		VERIFY(v[1] == T{10});
		VERIFY(v[2] == T{20});
		VERIFY(v[3] == T{30});
		{
			auto it = v.insert(v.begin() + 3, T{50});
			VERIFY(it == v.begin() + 3);
			VERIFY(*it == T{50});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v[0] == T{40});
		VERIFY(v[1] == T{10});
		VERIFY(v[2] == T{20});
		VERIFY(v[3] == T{50});
		VERIFY(v[4] == T{30});
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY((test_impl_1<T, 1>()));
	VERIFY((test_impl_1<T, 2>()));
	VERIFY((test_impl_1<T, 5>()));
	VERIFY((test_impl_1<T, 6>()));
	VERIFY((test_impl_1<T, 9>()));

//	VERIFY((test_impl_5<T, 1>()));
//	VERIFY((test_impl_5<T, 2>()));
	VERIFY((test_impl_5<T, 5>()));
	VERIFY((test_impl_5<T, 6>()));
	VERIFY((test_impl_5<T, 9>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, InsertTest)
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
		EXPECT_THROW(v.insert(v.end(), 1), hamon::bad_alloc);
		EXPECT_TRUE(v.empty());
		EXPECT_EQ(0u, v.size());
	}
	{
		hamon::inplace_vector<int, 1> v;
		EXPECT_NO_THROW(v.insert(v.begin(), 10));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0]);
		EXPECT_THROW(v.insert(v.begin(), 20), hamon::bad_alloc);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0]);
	}
	{
		hamon::inplace_vector<ThrowOnCopy, 3> v;
		EXPECT_TRUE(v.empty());
		ThrowOnCopy const t{42};
		EXPECT_THROW(v.insert(v.begin(), t), ThrowOnCopy::Exception);
		EXPECT_TRUE(v.empty());
		EXPECT_NO_THROW(v.insert(v.begin(), ThrowOnCopy{10}));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_THROW(v.insert(v.begin(), t), ThrowOnCopy::Exception);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_NO_THROW(v.insert(v.begin(), ThrowOnCopy{20}));
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(20, v[0].value);
		EXPECT_EQ(10, v[1].value);
		EXPECT_THROW(v.insert(v.begin(), t), ThrowOnCopy::Exception);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(20, v[0].value);
		EXPECT_EQ(10, v[1].value);
		EXPECT_NO_THROW(v.insert(v.begin(), ThrowOnCopy{30}));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(30, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_EQ(10, v[2].value);
		EXPECT_THROW(v.insert(v.begin(), t), hamon::bad_alloc);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(30, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_EQ(10, v[2].value);
	}
#endif

	// https://en.cppreference.com/w/cpp/container/inplace_vector/insert
	{
		auto print = [](hamon::inplace_vector<int, 14> const& v)
		{
			std::stringstream ss;
			for (auto const& e : v)
			{
				ss << e << ", ";
			}
			return ss.str();
		};

		hamon::inplace_vector<int, 14> v(3, 100);
		EXPECT_EQ("100, 100, 100, ", print(v));

		auto pos = v.begin();
		pos = v.insert(pos, 200); // overload (1)
		EXPECT_EQ("200, 100, 100, 100, ", print(v));

		v.insert(pos, 2, 300); // overload (3)
		EXPECT_EQ("300, 300, 200, 100, 100, 100, ", print(v));

		int arr[] = {501, 502, 503};
		v.insert(v.begin(), arr, arr + hamon::size(arr)); // overload (4)
		EXPECT_EQ("501, 502, 503, 300, 300, 200, 100, 100, 100, ", print(v));

		v.insert(v.end(), {601, 602, 603}); // overload (5)
		EXPECT_EQ("501, 502, 503, 300, 300, 200, 100, 100, 100, 601, 602, 603, ", print(v));

#if !defined(HAMON_NO_EXCEPTIONS)
		const auto list = {-13, -12, -11};
		EXPECT_THROW(v.insert(v.begin(), list), hamon::bad_alloc); // throws: no space
#endif
	}
}

}	// namespace insert_test

}	// namespace hamon_inplace_vector_test
