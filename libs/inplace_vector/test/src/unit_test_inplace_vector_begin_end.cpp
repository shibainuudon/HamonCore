/**
 *	@file	unit_test_inplace_vector_begin_end.cpp
 *
 *	@brief	begin, end のテスト
 *
 *	constexpr iterator               begin()         noexcept;
 *	constexpr const_iterator         begin()   const noexcept;
 *	constexpr iterator               end()           noexcept;
 *	constexpr const_iterator         end()     const noexcept;
 *	constexpr const_iterator         cbegin()  const noexcept;
 *	constexpr const_iterator         cend()    const noexcept;
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace begin_end_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using Iterator = typename InplaceVector::iterator;
	using ConstIterator = typename InplaceVector::const_iterator;

	{
		InplaceVector v;
		InplaceVector const cv;
		static_assert(hamon::is_same<decltype( v.begin()),  Iterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.begin()),  ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype( v.cbegin()), ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.cbegin()), ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype( v.end()),  Iterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.end()),  ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype( v.cend()), ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.cend()), ConstIterator>::value, "");
		static_assert( noexcept( v.begin()), "");
		static_assert( noexcept(cv.begin()), "");
		static_assert( noexcept( v.cbegin()), "");
		static_assert( noexcept(cv.cbegin()), "");
		static_assert( noexcept( v.end()), "");
		static_assert( noexcept(cv.end()), "");
		static_assert( noexcept( v.cend()), "");
		static_assert( noexcept(cv.cend()), "");
	}
	{
		InplaceVector v;
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
		VERIFY(it == v.cbegin());
		VERIFY(it == v.cend());
	}
	{
		InplaceVector const v;
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
		VERIFY(it == v.cbegin());
		VERIFY(it == v.cend());
	}

	return true;
}

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_3()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector const v{11,12,13};
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(it == v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == 11);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == 12);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == 13);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
	}
	{
		InplaceVector v{11,12,13};
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(it == v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == 11);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == 12);
		*it = 42;
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == 13);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
		VERIFY(v[0] == 11);
		VERIFY(v[1] == 42);
		VERIFY(v[2] == 13);
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

GTEST_TEST(InplaceVectorTest, BeginEndTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace begin_end_test

}	// namespace hamon_inplace_vector_test
