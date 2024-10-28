/**
 *	@file	unit_test_inplace_vector_rbegin_rend.cpp
 *
 *	@brief	rbegin, rend のテスト
 *
 *	constexpr reverse_iterator       rbegin()        noexcept;
 *	constexpr const_reverse_iterator rbegin()  const noexcept;
 *	constexpr reverse_iterator       rend()          noexcept;
 *	constexpr const_reverse_iterator rend()    const noexcept;
 *	constexpr const_reverse_iterator crbegin() const noexcept;
 *	constexpr const_reverse_iterator crend()   const noexcept;
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/algorithm.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace rbegin_rend_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using ReverseIterator = typename InplaceVector::reverse_iterator;
	using ConstReverseIterator = typename InplaceVector::const_reverse_iterator;

	{
		InplaceVector v;
		InplaceVector const cv;
		static_assert(hamon::is_same<decltype( v.rbegin()),  ReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.rbegin()),  ConstReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype( v.crbegin()), ConstReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.crbegin()), ConstReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype( v.rend()),  ReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.rend()),  ConstReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype( v.crend()), ConstReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.crend()), ConstReverseIterator>::value, "");
		static_assert( noexcept( v.rbegin()), "");
		static_assert( noexcept(cv.rbegin()), "");
		static_assert( noexcept( v.crbegin()), "");
		static_assert( noexcept(cv.crbegin()), "");
		static_assert( noexcept( v.rend()), "");
		static_assert( noexcept(cv.rend()), "");
		static_assert( noexcept( v.crend()), "");
		static_assert( noexcept(cv.crend()), "");
	}
	{
		InplaceVector v;
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it == v.rend());
		VERIFY(it == v.crbegin());
		VERIFY(it == v.crend());
	}
	{
		InplaceVector const v;
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it == v.rend());
		VERIFY(it == v.crbegin());
		VERIFY(it == v.crend());
	}

	return true;
}

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_3()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector const v{11,12,13};
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it == v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == 13);
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == 12);
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == 11);
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it == v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it == v.crend());
	}
	{
		InplaceVector v{11,12,13};
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it == v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == 13);
		*it = 42;
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == 12);
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == 11);
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it == v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it == v.crend());
		VERIFY(v[0] == 11);
		VERIFY(v[1] == 12);
		VERIFY(v[2] == 42);
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY((test_impl_0<T, 0>()));
	VERIFY((test_impl_0<T, 1>()));
	VERIFY((test_impl_0<T, 3>()));
	VERIFY((test_impl_0<T, 5>()));
	VERIFY((test_impl_0<T, 6>()));
	VERIFY((test_impl_0<T, 9>()));

//	VERIFY((test_impl_3<T, 0>()));
//	VERIFY((test_impl_3<T, 1>()));
	VERIFY((test_impl_3<T, 3>()));
	VERIFY((test_impl_3<T, 5>()));
	VERIFY((test_impl_3<T, 6>()));
	VERIFY((test_impl_3<T, 9>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, RBeginREndTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

	// https://en.cppreference.com/w/cpp/container/inplace_vector/rbegin
	{
		const hamon::inplace_vector<hamon::string_view, 8> data
		{
			"a", "b", "c", "d", "e", "f", "g", "h"
		};
		hamon::inplace_vector<hamon::string, 8> arr(8);

		hamon::copy(data.cbegin(), data.cend(), arr.begin());

		{
			std::stringstream ss;
			hamon::for_each(arr.cbegin(), arr.cend(), [&](const hamon::string_view s){ ss << s << ' '; });
			EXPECT_EQ("a b c d e f g h ", ss.str());
		}
		{
			std::stringstream ss;
			hamon::for_each(arr.crbegin(), arr.crend(), [&](const hamon::string_view s){ ss << s << ' '; });
			EXPECT_EQ("h g f e d c b a ", ss.str());
		}
	}

	// https://en.cppreference.com/w/cpp/container/inplace_vector/rend
	{
		hamon::inplace_vector<int, 11> a {1, 11, 11, 35, 0, 12, 79, 76, 76, 69, 40};

		{
			// Print elements of container in reverse order using const_reverse_iterator's.
			std::stringstream ss;
			hamon::for_each(a.crbegin(), a.crend(), [&](int e){ ss << e << ' '; });
			EXPECT_EQ("40 69 76 76 79 12 0 35 11 11 1 ", ss.str());
		}

		// Modify each element of container using non-const reverse_iterator's.
		hamon::for_each(a.rbegin(), a.rend(), [](int& e){ e += 32; });

		{
			// Print elements as chars in reverse order using const_reverse_iterator's.
			std::stringstream ss;
			hamon::for_each(a.crbegin(), a.crend(), [&](int e){ ss << static_cast<char>(e); });
			EXPECT_EQ("Hello, C++!", ss.str());
		}
	}
}

}	// namespace rbegin_rend_test

}	// namespace hamon_inplace_vector_test
