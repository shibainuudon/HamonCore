/**
 *	@file	unit_test_basic_const_iterator_ctor.cpp
 *
 *	@brief	コンストラクタのテスト
 * 
 *	basic_const_iterator() requires default_initializable<Iterator> = default;
 * 
 *	constexpr basic_const_iterator(Iterator current);
 * 
 *	template<convertible_to<Iterator> U>
 *	constexpr basic_const_iterator(basic_const_iterator<U> current);
 * 
 *	template<different-from<basic_const_iterator> T>
 *	requires convertible_to<T, Iterator>
 *	constexpr basic_const_iterator(T&& current);
 */

#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test
{

namespace basic_const_iterator_test
{

namespace ctor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
struct input_iterator_wrapper2
{
	T*	m_ptr;
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX14_CONSTEXPR input_iterator_wrapper2(T* p) : m_ptr(p) {}
	HAMON_CXX14_CONSTEXPR input_iterator_wrapper2(input_iterator_wrapper<T> p) : m_ptr(p.m_ptr) {}
	HAMON_CXX14_CONSTEXPR input_iterator_wrapper2& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR void                    operator++(int) { ++m_ptr; }
	HAMON_CXX11_CONSTEXPR T&                      operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const input_iterator_wrapper2& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const input_iterator_wrapper2& rhs) const { return !(*this == rhs); }
};

// デフォルトコンストラクタ
HAMON_CXX14_CONSTEXPR bool test01()
{
	static_assert( hamon::is_default_constructible<hamon::basic_const_iterator<int*>>::value, "");
	static_assert( hamon::is_default_constructible<hamon::basic_const_iterator<input_iterator_wrapper<int>>>::value, "");
	static_assert(!hamon::is_default_constructible<hamon::basic_const_iterator<input_iterator_wrapper2<int>>>::value, "");

	using Iter = input_iterator_wrapper<int>;
	hamon::basic_const_iterator<Iter> ci;
	(void)ci;
	return true;
}

// イテレータから構築
HAMON_CXX14_CONSTEXPR bool test02()
{
	using Iter1 = input_iterator_wrapper<int>;
	using Iter2 = input_iterator_wrapper2<int>;
	static_assert( hamon::is_constructible<hamon::basic_const_iterator<int*>, int*>::value, "");
	static_assert(!hamon::is_constructible<hamon::basic_const_iterator<int*>, const int*>::value, "");
	static_assert( hamon::is_constructible<hamon::basic_const_iterator<Iter1>, Iter1>::value, "");
	static_assert( hamon::is_constructible<hamon::basic_const_iterator<Iter2>, Iter2>::value, "");

	using Iter = input_iterator_wrapper<int>;
	int a[3] = {1, 2, 3};
	Iter it{a};
	hamon::basic_const_iterator<Iter> ci{it};
	VERIFY(*ci == 1);
	return true;
}

// 別のbasic_const_iteratorから構築
HAMON_CXX14_CONSTEXPR bool test03()
{
	using Iter1 = input_iterator_wrapper<int>;
	using Iter2 = input_iterator_wrapper2<int>;
	static_assert( hamon::is_constructible<hamon::basic_const_iterator<int*>, hamon::basic_const_iterator<int*>>::value, "");
	static_assert( hamon::is_constructible<hamon::basic_const_iterator<Iter1>, hamon::basic_const_iterator<Iter1>>::value, "");
	static_assert(!hamon::is_constructible<hamon::basic_const_iterator<Iter1>, hamon::basic_const_iterator<Iter2>>::value, "");
	static_assert( hamon::is_constructible<hamon::basic_const_iterator<Iter2>, hamon::basic_const_iterator<Iter1>>::value, "");
	static_assert( hamon::is_constructible<hamon::basic_const_iterator<Iter2>, hamon::basic_const_iterator<Iter2>>::value, "");

	{
		using Iter = input_iterator_wrapper<int>;
		int a[3] = {1, 2, 3};
		Iter it{a};
		hamon::basic_const_iterator<Iter> ci1{it};
		hamon::basic_const_iterator<Iter> ci2{ci1};
		VERIFY(*ci2 == 1);
	}

	// Microsoft-STLのbasic_const_iteratorは、
	// basic_const_iterator<It2>をfriend指定していないので以下のコードがエラーになる
#if defined(HAMON_STDLIB_DINKUMWARE) && !defined(HAMON_USE_STD_BASIC_CONST_ITERATOR)
	{
		int a[3] = {1, 2, 3};
		hamon::basic_const_iterator<int*> ci1{a};
		hamon::basic_const_iterator<int const*> ci2{ci1};
		VERIFY(*ci2 == 1);
	}
#endif
	return true;
}

// Iに変換可能な型から構築
HAMON_CXX14_CONSTEXPR bool test04()
{
	using Iter1 = input_iterator_wrapper<int>;
	using Iter2 = input_iterator_wrapper2<int>;
	static_assert(!hamon::is_constructible<hamon::basic_const_iterator<int*>, const int*>::value, "");
	static_assert(!hamon::is_constructible<hamon::basic_const_iterator<Iter1>, Iter2>::value, "");
	static_assert( hamon::is_constructible<hamon::basic_const_iterator<Iter2>, Iter1>::value, "");

	int a[3] = {1, 2, 3};
	Iter1 it{a};
	hamon::basic_const_iterator<Iter2> ci{it};
	VERIFY(*ci == 1);
	return true;
}

#undef VERIFY

GTEST_TEST(BasicConstIteratorTest, CtorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace ctor_test

}	// namespace basic_const_iterator_test

}	// namespace hamon_iterator_test
