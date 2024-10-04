/**
 *	@file	unit_test_forward_list_assign.cpp
 *
 *	@brief	assign のテスト
 *
 *	template<class InputIterator>
 *	void assign(InputIterator first, InputIterator last)
 *	void assign(size_type n, const T& t);
 *	void assign(initializer_list<T>);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_forward_list_test
{

namespace assign_test
{

#if !defined(HAMON_USE_STD_FORWARD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// MSVCでconstexprにすると内部コンパイラエラーになってしまう TODO
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, template <typename> class IteratorWrapper>
FORWARD_LIST_TEST_CONSTEXPR bool test1()
{
	using ForwardList = hamon::forward_list<T>;
	using Iterator = IteratorWrapper<T>;

	{
		ForwardList v;
		Iterator it;
		static_assert(hamon::is_same<decltype(v.assign(it, it)), void>::value, "");
		static_assert(!noexcept(v.assign(it, it)), "");
	}

	{
		T a[] = {T{1}, T{2}, T{3}, T{4}, T{5}};
		ForwardList v;
		VERIFY(v.empty());

		v.assign(Iterator{a}, Iterator{a + 5});
		VERIFY(!v.empty());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v.end());
		}

		v.assign(Iterator{a + 1}, Iterator{a + 4});
		VERIFY(!v.empty());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(it == v.end());
		}

		v.assign(Iterator{a}, Iterator{a});
		VERIFY(v.empty());
	}

	return true;
}

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test2()
{
	using ForwardList = hamon::forward_list<T>;
	using SizeType = typename ForwardList::size_type;

	{
		ForwardList v;
		SizeType const s{};
		T const t{};
		static_assert(hamon::is_same<decltype(v.assign(s, t)), void>::value, "");
		static_assert(!noexcept(v.assign(s, t)), "");
	}

	{
		ForwardList v;
		VERIFY(v.empty());

		v.assign(3, T{42});
		VERIFY(!v.empty());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{42});
			VERIFY(*it++ == T{42});
			VERIFY(*it++ == T{42});
			VERIFY(it == v.end());
		}

		v.assign(5, T{13});
		VERIFY(!v.empty());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{13});
			VERIFY(*it++ == T{13});
			VERIFY(*it++ == T{13});
			VERIFY(*it++ == T{13});
			VERIFY(*it++ == T{13});
			VERIFY(it == v.end());
		}

		v.assign(1, T{10});
		VERIFY(!v.empty());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}

		v.assign(0, T{99});
		VERIFY(v.empty());
	}

	return true;
}

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test3()
{
	using ForwardList = hamon::forward_list<T>;

	{
		ForwardList v;
		std::initializer_list<T> il;
		static_assert(hamon::is_same<decltype(v.assign(il)), void>::value, "");
		static_assert(!noexcept(v.assign(il)), "");
	}

	{
		ForwardList v;
		VERIFY(v.empty());

		v.assign({T{1},T{2},T{3}});
		VERIFY(!v.empty());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(it == v.end());
		}

		v.assign({T{10},T{11},T{12},T{13}});
		VERIFY(!v.empty());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(*it++ == T{13});
			VERIFY(it == v.end());
		}

		v.assign({T{5},T{6}});
		VERIFY(!v.empty());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{6});
			VERIFY(it == v.end());
		}

		{
			std::initializer_list<T> il;
			v.assign(il);
			VERIFY(v.empty());
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, AssignTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<char,  cpp17_input_iterator_wrapper>()));
//	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<short, input_iterator_wrapper>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<int,   forward_iterator_wrapper>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<long,  bidirectional_iterator_wrapper>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<char,  random_access_iterator_wrapper>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<short, contiguous_iterator_wrapper>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<int,   cpp17_input_iterator_wrapper>()));
//	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<long,  input_iterator_wrapper>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<char,  forward_iterator_wrapper>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<short, bidirectional_iterator_wrapper>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<int,   random_access_iterator_wrapper>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<long,  contiguous_iterator_wrapper>()));

	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test2<char>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test2<short>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test2<long>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test2<float>()));

	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test3<char>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test3<short>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test3<int>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test3<long>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test3<float>()));
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace assign_test

}	// namespace hamon_forward_list_test
