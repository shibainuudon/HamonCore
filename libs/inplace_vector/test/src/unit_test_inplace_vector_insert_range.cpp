/**
 *	@file	unit_test_inplace_vector_insert_range.cpp
 *
 *	@brief	insert_range のテスト
 *
 *	template<container-compatible-range<T> R>
 *	constexpr iterator insert_range(const_iterator position, R&& rg);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_inplace_vector_test
{

namespace insert_range_test
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

template <typename T, hamon::size_t N, template <typename> class RangeWrapper>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using Iterator = typename InplaceVector::iterator;
	using ConstIterator = typename InplaceVector::const_iterator;
	using Range = RangeWrapper<T>;

	{
		InplaceVector v;
		ConstIterator pos;
		Range r;
		static_assert(hamon::is_same<decltype(v.insert_range(pos, r)), Iterator>::value, "");
		static_assert(!noexcept(v.insert_range(pos, r)), "");
	}
	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		T a[] = {T{1}, T{2}, T{3}};
		auto it = v.insert_range(v.begin(), Range(a, a));
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
	}

	return true;
}

template <typename T, hamon::size_t N, template <typename> class RangeWrapper>
HAMON_CXX14_CONSTEXPR bool test_impl_5()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using Range = RangeWrapper<T>;

	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		{
			T a[] = {T{1}, T{2}, T{3}};
			auto it = v.insert_range(v.end(), Range{a});
			VERIFY(it == v.begin());
			VERIFY(*it == T{1});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{2});
		VERIFY(v[2] == T{3});

		{
			T b[] = {T{4}, T{5}};
			auto it = v.insert_range(v.begin() + 2, Range{b});
			VERIFY(it == v.begin() + 2);
			VERIFY(*it == T{4});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{2});
		VERIFY(v[2] == T{4});
		VERIFY(v[3] == T{5});
		VERIFY(v[4] == T{3});
	}
	return true;
}

template <typename T, template <typename> class RangeWrapper>
HAMON_CXX14_CONSTEXPR bool test_impl()
{
	VERIFY((test_impl_0<T, 0, RangeWrapper>()));
	VERIFY((test_impl_0<T, 1, RangeWrapper>()));
	VERIFY((test_impl_0<T, 2, RangeWrapper>()));
	VERIFY((test_impl_0<T, 5, RangeWrapper>()));
	VERIFY((test_impl_0<T, 6, RangeWrapper>()));

//	VERIFY((test_impl_5<T, 0, RangeWrapper>()));
//	VERIFY((test_impl_5<T, 1, RangeWrapper>()));
//	VERIFY((test_impl_5<T, 2, RangeWrapper>()));
	VERIFY((test_impl_5<T, 5, RangeWrapper>()));
	VERIFY((test_impl_5<T, 6, RangeWrapper>()));

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY((test_impl<T, test_input_range>()));
	VERIFY((test_impl<T, test_forward_range>()));
	VERIFY((test_impl<T, test_bidirectional_range>()));
	VERIFY((test_impl<T, test_random_access_range>()));
	VERIFY((test_impl<T, test_contiguous_range>()));

	VERIFY((test_impl<T, test_input_sized_range>()));
	VERIFY((test_impl<T, test_forward_sized_range>()));
	VERIFY((test_impl<T, test_bidirectional_sized_range>()));
	VERIFY((test_impl<T, test_random_access_sized_range>()));
	VERIFY((test_impl<T, test_contiguous_sized_range>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, InsertRangeTest)
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
		int const a[]{1};
		EXPECT_THROW(v.insert_range(v.end(), a), hamon::bad_alloc);
		EXPECT_TRUE(v.empty());
		EXPECT_EQ(0u, v.size());
	}
	{
		hamon::inplace_vector<int, 1> v;
		int const a[]{1};
		EXPECT_NO_THROW(v.insert_range(v.end(), a));
		EXPECT_TRUE(!v.empty());
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_THROW(v.insert_range(v.end(), a), hamon::bad_alloc);
		EXPECT_TRUE(!v.empty());
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(1, v[0]);
	}
	{
		hamon::inplace_vector<ThrowOnCopy, 5> v;
		EXPECT_TRUE(v.empty());
		ThrowOnCopy const a[]{1,2,3,4,5};
		EXPECT_THROW(v.insert_range(v.begin(), a), ThrowOnCopy::Exception);
		v.emplace_back(10);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_THROW(v.insert_range(v.begin(), a), hamon::bad_alloc);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0].value);
	}
#endif

	// https://en.cppreference.com/w/cpp/container/inplace_vector/insert_range
	{
		auto print = [](hamon::inplace_vector<int, 8> const& v)
		{
			std::stringstream ss;
			for (auto const& e : v)
			{
				ss << e << ", ";
			}
			return ss.str();
		};

		auto v = hamon::inplace_vector<int, 8> {0, 1, 2, 3};
		auto pos = hamon::next(v.begin(), 2);
		EXPECT_TRUE(*pos == 2);
		const auto rg = {-1, -2, -3};
		v.insert_range(pos, rg);
		EXPECT_EQ("0, 1, -1, -2, -3, 2, 3, ", print(v));

#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_TRUE(v.size() + rg.size() > v.capacity());
		EXPECT_THROW(v.insert_range(pos, rg), hamon::bad_alloc); // throws: no space
#endif
	}
}

}	// namespace insert_range_test

}	// namespace hamon_inplace_vector_test
