/**
 *	@file	unit_test_list_assign.cpp
 *
 *	@brief	assign のテスト
 *
 *	template<class InputIterator>
 *	void assign(InputIterator first, InputIterator last);
 *	void assign(size_type n, const T& t);
 *	void assign(initializer_list<T>);
 */

#include <hamon/list/list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_list_test
{

namespace assign_test
{

#if !defined(HAMON_USE_STD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// VS2019でconstexprにすると内部コンパイラエラーになってしまう
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, template <typename> class IteratorWrapper>
LIST_TEST_CONSTEXPR bool test1()
{
	using List = hamon::list<T>;
	using Iterator = IteratorWrapper<T>;

	{
		List v;
		Iterator it;
		static_assert(hamon::is_same<decltype(v.assign(it, it)), void>::value, "");
		static_assert(!noexcept(v.assign(it, it)), "");
	}

	{
		T a[] = {T{1}, T{2}, T{3}, T{4}, T{5}};
		List v;
		VERIFY(v.empty());

		v.assign(Iterator{a}, Iterator{a + 5});
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.rend());
		}

		v.assign(Iterator{a + 1}, Iterator{a + 4});
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{4});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(it == v.rend());
		}

		v.assign(Iterator{a}, Iterator{a});
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
	}

	return true;
}

template <typename T>
LIST_TEST_CONSTEXPR bool test2()
{
	using List = hamon::list<T>;
	using SizeType = typename List::size_type;

	{
		List v;
		SizeType const s{};
		T const t{};
		static_assert(hamon::is_same<decltype(v.assign(s, t)), void>::value, "");
		static_assert(!noexcept(v.assign(s, t)), "");
	}

	{
		List v;
		VERIFY(v.empty());

		v.assign(3, T{42});
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{42});
			VERIFY(*it++ == T{42});
			VERIFY(*it++ == T{42});
			VERIFY(it == v.end());
		}

		v.assign(5, T{13});
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
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
		VERIFY(v.size() == 1);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}

		v.assign(0, T{99});
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
	}

	return true;
}

template <typename T>
LIST_TEST_CONSTEXPR bool test3()
{
	using List = hamon::list<T>;

	{
		List v;
		std::initializer_list<T> il;
		static_assert(hamon::is_same<decltype(v.assign(il)), void>::value, "");
		static_assert(!noexcept(v.assign(il)), "");
	}

	{
		List v;
		VERIFY(v.empty());

		v.assign({T{1},T{2},T{3}});
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{3});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{1});
			VERIFY(it == v.rend());
		}

		v.assign({T{10},T{11},T{12},T{13}});
		VERIFY(!v.empty());
		VERIFY(v.size() == 4);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{12});
			VERIFY(*it++ == T{13});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{13});
			VERIFY(*it++ == T{12});
			VERIFY(*it++ == T{11});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.rend());
		}

		v.assign({T{5},T{6}});
		VERIFY(!v.empty());
		VERIFY(v.size() == 2);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{6});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{6});
			VERIFY(*it++ == T{5});
			VERIFY(it == v.rend());
		}

		{
			std::initializer_list<T> il;
			v.assign(il);
			VERIFY(v.empty());
			VERIFY(v.size() == 0);
			VERIFY(v.begin() == v.end());
			VERIFY(v.rbegin() == v.rend());
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ListTest, AssignTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<char,  cpp17_input_iterator_wrapper>()));
//	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<short, input_iterator_wrapper>()));
	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<int,   forward_iterator_wrapper>()));
	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<long,  bidirectional_iterator_wrapper>()));
	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<char,  random_access_iterator_wrapper>()));
	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<short, contiguous_iterator_wrapper>()));
	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<int,   cpp17_input_iterator_wrapper>()));
//	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<long,  input_iterator_wrapper>()));
	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<char,  forward_iterator_wrapper>()));
	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<short, bidirectional_iterator_wrapper>()));
	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<int,   random_access_iterator_wrapper>()));
	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test1<long,  contiguous_iterator_wrapper>()));

	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test2<char>()));
	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test2<short>()));
	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test2<long>()));
	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test2<float>()));

	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test3<char>()));
	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test3<short>()));
	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test3<int>()));
	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test3<long>()));
	LIST_TEST_CONSTEXPR_EXPECT_TRUE((test3<float>()));
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace assign_test

}	// namespace hamon_list_test
