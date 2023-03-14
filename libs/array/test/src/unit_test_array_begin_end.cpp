/**
 *	@file	unit_test_array_begin_end.cpp
 *
 *	@brief	イテレータのテスト
 *
 *	constexpr iterator               begin()         noexcept;
 *	constexpr const_iterator         begin()   const noexcept;
 *	constexpr iterator               end()           noexcept;
 *	constexpr const_iterator         end()     const noexcept;
 *	constexpr reverse_iterator       rbegin()        noexcept;
 *	constexpr const_reverse_iterator rbegin()  const noexcept;
 *	constexpr reverse_iterator       rend()          noexcept;
 *	constexpr const_reverse_iterator rend()    const noexcept;
 *	constexpr const_iterator         cbegin()  const noexcept;
 *	constexpr const_iterator         cend()    const noexcept;
 *	constexpr const_reverse_iterator crbegin() const noexcept;
 *	constexpr const_reverse_iterator crend()   const noexcept;
 */

#include <hamon/array/array.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_array_test
{

namespace begin_end_test
{

template <typename Array>
void TypeTest()
{
	using Iterator             = typename Array::iterator;
	using ConstIterator        = typename Array::const_iterator;
	using ReverseIterator      = typename Array::reverse_iterator;
	using ConstReverseIterator = typename Array::const_reverse_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Array>().begin()),         Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Array>().end()),           Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Array>().rbegin()),        ReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Array>().rend()),          ReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Array>().cbegin()),        ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Array>().cend()),          ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Array>().crbegin()),       ConstReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Array>().crend()),         ConstReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Array const>().begin()),   ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Array const>().end()),     ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Array const>().rbegin()),  ConstReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Array const>().rend()),    ConstReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Array const>().cbegin()),  ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Array const>().cend()),    ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Array const>().crbegin()), ConstReverseIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Array const>().crend()),   ConstReverseIterator>::value, "");
}

template <typename Array>
void NoexceptTest()
{
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<Array>().begin());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<Array>().end());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<Array>().rbegin());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<Array>().rend());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<Array>().cbegin());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<Array>().cend());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<Array>().crbegin());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<Array>().crend());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<Array const>().begin());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<Array const>().end());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<Array const>().rbegin());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<Array const>().rend());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<Array const>().cbegin());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<Array const>().cend());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<Array const>().crbegin());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<Array const>().crend());
}

template <typename T>
void BeginEndTest()
{
	{
		using Array = hamon::array<T, 3>;
		TypeTest<Array>();
		NoexceptTest<Array>();
		HAMON_CXX11_CONSTEXPR Array a{T(1), T(2), T(3)};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.begin()   == a.cbegin());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.rbegin()  == a.crbegin());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.end()     == a.cend());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.rend()    == a.crend());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.begin()   != a.end());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.rbegin()  != a.rend());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.cbegin()  != a.cend());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.crbegin() != a.crend());

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.begin()   == hamon::begin(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.cbegin()  == hamon::cbegin(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.rbegin()  == hamon::rbegin(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.crbegin() == hamon::crbegin(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.end()     == hamon::end(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.cend()    == hamon::cend(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.rend()    == hamon::rend(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.crend()   == hamon::crend(a));

		auto i = a.begin();
		EXPECT_EQ(T(1), *i);
		EXPECT_EQ(a.data(), &*i);
	}
	{
		using Array = hamon::array<T, 0>;
		TypeTest<Array>();
		NoexceptTest<Array>();
		HAMON_CXX11_CONSTEXPR Array a{};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.begin()   == a.cbegin());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.rbegin()  == a.crbegin());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.end()     == a.cend());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.rend()    == a.crend());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.begin()   == a.end());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.rbegin()  == a.rend());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.cbegin()  == a.cend());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.crbegin() == a.crend());

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.begin()   == hamon::begin(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.cbegin()  == hamon::cbegin(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.rbegin()  == hamon::rbegin(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.crbegin() == hamon::crbegin(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.end()     == hamon::end(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.cend()    == hamon::cend(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.rend()    == hamon::rend(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(a.crend()   == hamon::crend(a));
	}
	{
		using Array = hamon::array<T, 3>;
		TypeTest<Array>();
		NoexceptTest<Array>();
		Array a{T(1), T(2), T(3)};
		EXPECT_TRUE(a.begin()   == a.cbegin());
		EXPECT_TRUE(a.rbegin()  == a.crbegin());
		EXPECT_TRUE(a.end()     == a.cend());
		EXPECT_TRUE(a.rend()    == a.crend());
		EXPECT_TRUE(a.begin()   != a.end());
		EXPECT_TRUE(a.rbegin()  != a.rend());
		EXPECT_TRUE(a.cbegin()  != a.cend());
		EXPECT_TRUE(a.crbegin() != a.crend());

		EXPECT_TRUE(a.begin()   == hamon::begin(a));
		EXPECT_TRUE(a.cbegin()  == hamon::cbegin(a));
		EXPECT_TRUE(a.rbegin()  == hamon::rbegin(a));
		EXPECT_TRUE(a.crbegin() == hamon::crbegin(a));
		EXPECT_TRUE(a.end()     == hamon::end(a));
		EXPECT_TRUE(a.cend()    == hamon::cend(a));
		EXPECT_TRUE(a.rend()    == hamon::rend(a));
		EXPECT_TRUE(a.crend()   == hamon::crend(a));

		auto i = a.begin();
		EXPECT_EQ(T(1), *i);
		EXPECT_EQ(a.data(), &*i);
		*i = T(4);
		EXPECT_EQ(T(4), a[0]);
		EXPECT_EQ(T(2), a[1]);
		EXPECT_EQ(T(3), a[2]);
	}
	{
		using Array = hamon::array<T, 0>;
		TypeTest<Array>();
		NoexceptTest<Array>();
		Array a{};
		EXPECT_TRUE(a.begin()   == a.cbegin());
		EXPECT_TRUE(a.rbegin()  == a.crbegin());
		EXPECT_TRUE(a.end()     == a.cend());
		EXPECT_TRUE(a.rend()    == a.crend());
		EXPECT_TRUE(a.begin()   == a.end());
		EXPECT_TRUE(a.rbegin()  == a.rend());
		EXPECT_TRUE(a.cbegin()  == a.cend());
		EXPECT_TRUE(a.crbegin() == a.crend());

		EXPECT_TRUE(a.begin()   == hamon::begin(a));
		EXPECT_TRUE(a.cbegin()  == hamon::cbegin(a));
		EXPECT_TRUE(a.rbegin()  == hamon::rbegin(a));
		EXPECT_TRUE(a.crbegin() == hamon::crbegin(a));
		EXPECT_TRUE(a.end()     == hamon::end(a));
		EXPECT_TRUE(a.cend()    == hamon::cend(a));
		EXPECT_TRUE(a.rend()    == hamon::rend(a));
		EXPECT_TRUE(a.crend()   == hamon::crend(a));
	}
	{
		using Array = hamon::array<T, 3>;
		HAMON_CXX11_CONSTEXPR typename Array::iterator i1{};
		HAMON_CXX11_CONSTEXPR typename Array::iterator i2{};
		HAMON_CXX11_CONSTEXPR typename Array::const_iterator ci1{};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(i1 == i2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(i1 == ci1);
	}
	{
		using Array = hamon::array<T, 0>;
		HAMON_CXX11_CONSTEXPR typename Array::iterator i1{};
		HAMON_CXX11_CONSTEXPR typename Array::iterator i2{};
		HAMON_CXX11_CONSTEXPR typename Array::const_iterator ci1{};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(i1 == i2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(i1 == ci1);
	}
}

GTEST_TEST(ArrayTest, BeginEndTest)
{
	BeginEndTest<char>();
	BeginEndTest<int>();
	BeginEndTest<float>();
	BeginEndTest<double>();
}

}	// namespace begin_end_test

}	// namespace hamon_array_test
