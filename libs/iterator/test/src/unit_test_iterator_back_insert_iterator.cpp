﻿/**
 *	@file	unit_test_iterator_back_insert_iterator.cpp
 *
 *	@brief	back_insert_iterator のテスト
 */

#include <hamon/iterator/back_insert_iterator.hpp>
#include <hamon/iterator/output_iterator_tag.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_iterator_test {
namespace back_insert_iterator_test {

struct MyContainer
{
	using value_type = int;

	HAMON_CXX11_CONSTEXPR value_type const* begin() const
	{
		return m_arr;
	}

	HAMON_CXX11_CONSTEXPR value_type const* end() const
	{
		return m_arr + m_size;
	}

	HAMON_CXX14_CONSTEXPR void push_back(value_type const& v)
	{
		m_arr[m_size] = v;
		++m_size;
	}

	hamon::size_t	m_size = 0;
	value_type		m_arr[10] {};
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Container>
HAMON_CXX14_CONSTEXPR bool test()
{
	using I = hamon::back_insert_iterator<Container>;
	static_assert(hamon::is_same<typename I::iterator_category, hamon::output_iterator_tag>::value, "");
	static_assert(hamon::is_same<typename I::value_type, void>::value, "");
	static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	static_assert(hamon::is_same<typename I::pointer, void>::value, "");
	static_assert(hamon::is_same<typename I::reference, void>::value, "");
	static_assert(hamon::is_same<typename I::container_type, Container>::value, "");

	static_assert( hamon::is_constructible<I, Container&>::value, "");
	static_assert(!hamon::is_constructible<I, Container&&>::value, "");
	static_assert(!hamon::is_constructible<I, Container const&>::value, "");
	static_assert(!hamon::is_constructible<I, Container const&&>::value, "");

//	static_assert(!hamon::is_default_constructible<I>::value, "");
	static_assert( hamon::is_copy_constructible<I>::value, "");
	static_assert( hamon::is_move_constructible<I>::value, "");

	Container c;
	I it(c);

	static_assert(hamon::is_same<decltype(it = hamon::declval<int const&>()), I&>::value, "");
	static_assert(hamon::is_same<decltype(it = hamon::declval<int &&>()), I&>::value, "");
	static_assert(hamon::is_same<decltype(*it), I&>::value, "");
	static_assert(hamon::is_same<decltype(++it), I&>::value, "");
	static_assert(hamon::is_same<decltype(it++), I>::value, "");

	int const n = 3;
	it = n;
	VERIFY(hamon::ranges::equal(c, hamon::array<int, 1>{3}));
	it = 1;
	VERIFY(hamon::ranges::equal(c, hamon::array<int, 2>{3, 1}));
	*it = 4;
	VERIFY(hamon::ranges::equal(c, hamon::array<int, 3>{3, 1, 4}));
	*++it = 1;
	VERIFY(hamon::ranges::equal(c, hamon::array<int, 4>{3, 1, 4, 1}));
	*it++ = 5;
	VERIFY(hamon::ranges::equal(c, hamon::array<int, 5>{3, 1, 4, 1, 5}));

	return true;
}

#undef VERIFY

GTEST_TEST(IteratorTest, BackInsertIteratorTest)
{
	EXPECT_TRUE(test<hamon::vector<int>>());
	EXPECT_TRUE(test<hamon::list<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<MyContainer>());
}

}	// namespace back_insert_iterator_test
}	// namespace hamon_iterator_test
