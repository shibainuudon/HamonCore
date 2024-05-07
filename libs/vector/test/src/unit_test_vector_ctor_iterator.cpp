/**
 *	@file	unit_test_vector_ctor_iterator.cpp
 *
 *	@brief	イテレータを引数に取るコンストラクタのテスト
 *
 *	template<class InputIterator>
 *	constexpr vector(InputIterator first, InputIterator last, const Allocator& = Allocator());
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "iterator_test.hpp"
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace ctor_iterator_test
{

struct S1
{
	int value;
};

HAMON_CXX11_CONSTEXPR bool operator==(S1 const& lhs, S1 const& rhs)
{
	return lhs.value == rhs.value;
}

struct S2
{
	int value;
	HAMON_CXX11_CONSTEXPR S2(int v) : value(v) {}
};

HAMON_CXX11_CONSTEXPR bool operator==(S2 const& lhs, S2 const& rhs)
{
	return lhs.value == rhs.value;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, template <typename> class IteratorWrapper>
HAMON_CXX20_CONSTEXPR bool test2()
{
	using Allocator = std::allocator<T>;
	using Vector = hamon::vector<T, Allocator>;
	using Iterator = IteratorWrapper<T>;
//	using ConstIterator = IteratorWrapper<T const>;

	static_assert( hamon::is_constructible<Vector, Iterator, Iterator>::value, "");
	static_assert( hamon::is_constructible<Vector, Iterator, Iterator, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Vector, Iterator, Iterator>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Vector, Iterator, Iterator, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Vector, Iterator, Iterator>::value, "");
	static_assert( hamon::is_implicitly_constructible<Vector, Iterator, Iterator, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Vector, Iterator, Iterator>::value, "");
	static_assert(!hamon::is_trivially_constructible<Vector, Iterator, Iterator, Allocator const&>::value, "");

	T a[] = {T{1}, T{2}, T{3}};
	{
		Vector v(Iterator{a}, Iterator{a + 3});
		VERIFY(v.size() == 3);
		VERIFY(!v.empty());
		VERIFY(v[0] == a[0]);
		VERIFY(v[1] == a[1]);
		VERIFY(v[2] == a[2]);
	}
	{
		Allocator alloc;
		Vector v(Iterator{a}, Iterator{a + 3}, alloc);
		VERIFY(v.get_allocator() == alloc);
		VERIFY(v.size() == 3);
		VERIFY(!v.empty());
		VERIFY(v[0] == a[0]);
		VERIFY(v[1] == a[1]);
		VERIFY(v[2] == a[2]);
	}
	{
		Vector v(Iterator{a}, Iterator{a});
		VERIFY(v.size() == 0);
		VERIFY(v.empty());
	}
	{
		Allocator alloc;
		Vector v(Iterator{a}, Iterator{a}, alloc);
		VERIFY(v.get_allocator() == alloc);
		VERIFY(v.size() == 0);
		VERIFY(v.empty());
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	return
		test2<T, cpp17_input_iterator_wrapper>() &&
		//test2<T, input_iterator_wrapper>() &&
		test2<T, forward_iterator_wrapper>() &&
		test2<T, bidirectional_iterator_wrapper>() &&
		test2<T, random_access_iterator_wrapper>() &&
		test2<T, contiguous_iterator_wrapper>();
}

#undef VERIFY

GTEST_TEST(VectorTest, CtorIteratorTest)
{
#if !(defined(HAMON_CLANG_VERSION) && defined(HAMON_STDLIB_DINKUMWARE))	// win-clangだとconstexprにできない
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
#else
	EXPECT_TRUE(test<int>());
	EXPECT_TRUE(test<S1>());
	EXPECT_TRUE(test<S2>());
#endif
}

}	// namespace ctor_iterator_test

}	// namespace hamon_vector_test
