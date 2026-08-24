/**
 *	@file	unit_test_stack_op_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class T, class Container>
 *	constexpr bool operator==(const stack<T, Container>& x, const stack<T, Container>& y);
 *
 *	template<class T, class Container>
 *	constexpr bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y);
 *
 *	template<class T, class Container>
 *	constexpr  bool operator< (const stack<T, Container>& x, const stack<T, Container>& y);
 *
 *	template<class T, class Container>
 *	constexpr bool operator> (const stack<T, Container>& x, const stack<T, Container>& y);
 *
 *	template<class T, class Container>
 *	constexpr bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y);
 *
 *	template<class T, class Container>
 *	constexpr bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y);
 *
 *	template<class T, three_way_comparable Container>
 *	constexpr compare_three_way_result_t<Container>
 *	operator<=>(const stack<T, Container>& x, const stack<T, Container>& y);
 */

#include <hamon/stack/stack.hpp>
#include <hamon/compare.hpp>
#include <hamon/deque.hpp>
#include <hamon/vector.hpp>
#include <hamon/list.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_stack_test
{

namespace op_compare_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Stack = hamon::stack<T, Container>;

	static_assert(hamon::is_same<decltype(hamon::declval<Stack const&>() == hamon::declval<Stack const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Stack const&>() != hamon::declval<Stack const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Stack const&>() <  hamon::declval<Stack const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Stack const&>() >  hamon::declval<Stack const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Stack const&>() <= hamon::declval<Stack const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Stack const&>() >= hamon::declval<Stack const&>()), bool>::value, "");

	static_assert(!noexcept(hamon::declval<Stack const&>() == hamon::declval<Stack const&>()), "");
	static_assert(!noexcept(hamon::declval<Stack const&>() != hamon::declval<Stack const&>()), "");
	static_assert(!noexcept(hamon::declval<Stack const&>() <  hamon::declval<Stack const&>()), "");
	static_assert(!noexcept(hamon::declval<Stack const&>() >  hamon::declval<Stack const&>()), "");
	static_assert(!noexcept(hamon::declval<Stack const&>() <= hamon::declval<Stack const&>()), "");
	static_assert(!noexcept(hamon::declval<Stack const&>() >= hamon::declval<Stack const&>()), "");

	Container const c1 {1, 2, 3};
	Container const c2 {1, 2, 3};
	Container const c3 {0, 2, 3};
	Container const c4 {1, 2, 4};
	Container const c5 {1, 2};
	Container const c6 {1, 2, 3, 4};
	Stack const s1(c1);
	Stack const s2(c2);
	Stack const s3(c3);
	Stack const s4(c4);
	Stack const s5(c5);
	Stack const s6(c6);

	VERIFY( (s1 == s1));
	VERIFY( (s1 == s2));
	VERIFY(!(s1 == s3));
	VERIFY(!(s1 == s4));
	VERIFY(!(s1 == s5));
	VERIFY(!(s1 == s6));

	VERIFY(!(s1 != s1));
	VERIFY(!(s1 != s2));
	VERIFY( (s1 != s3));
	VERIFY( (s1 != s4));
	VERIFY( (s1 != s5));
	VERIFY( (s1 != s6));

	VERIFY(!(s1 < s1));
	VERIFY(!(s1 < s2));
	VERIFY(!(s1 < s3));
	VERIFY( (s1 < s4));
	VERIFY(!(s1 < s5));
	VERIFY( (s1 < s6));

	VERIFY(!(s1 > s1));
	VERIFY(!(s1 > s2));
	VERIFY( (s1 > s3));
	VERIFY(!(s1 > s4));
	VERIFY( (s1 > s5));
	VERIFY(!(s1 > s6));

	VERIFY( (s1 <= s1));
	VERIFY( (s1 <= s2));
	VERIFY(!(s1 <= s3));
	VERIFY( (s1 <= s4));
	VERIFY(!(s1 <= s5));
	VERIFY( (s1 <= s6));

	VERIFY( (s1 >= s1));
	VERIFY( (s1 >= s2));
	VERIFY( (s1 >= s3));
	VERIFY(!(s1 >= s4));
	VERIFY( (s1 >= s5));
	VERIFY(!(s1 >= s6));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(hamon::is_same<decltype(hamon::declval<Stack const&>() <=> hamon::declval<Stack const&>()),
		hamon::compare_three_way_result_t<Container>>::value, "");
	static_assert(!noexcept(hamon::declval<Stack const&>() <=> hamon::declval<Stack const&>()), "");

	VERIFY( hamon::is_eq(s1 <=> s1));
	VERIFY( hamon::is_eq(s1 <=> s2));
	VERIFY(!hamon::is_eq(s1 <=> s3));
	VERIFY(!hamon::is_eq(s1 <=> s4));
	VERIFY(!hamon::is_eq(s1 <=> s5));
	VERIFY(!hamon::is_eq(s1 <=> s6));

	VERIFY(!hamon::is_lt(s1 <=> s1));
	VERIFY(!hamon::is_lt(s1 <=> s2));
	VERIFY(!hamon::is_lt(s1 <=> s3));
	VERIFY( hamon::is_lt(s1 <=> s4));
	VERIFY(!hamon::is_lt(s1 <=> s5));
	VERIFY( hamon::is_lt(s1 <=> s6));

	VERIFY(!hamon::is_gt(s1 <=> s1));
	VERIFY(!hamon::is_gt(s1 <=> s2));
	VERIFY( hamon::is_gt(s1 <=> s3));
	VERIFY(!hamon::is_gt(s1 <=> s4));
	VERIFY( hamon::is_gt(s1 <=> s5));
	VERIFY(!hamon::is_gt(s1 <=> s6));
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(StackTest, op_compareTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::deque<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, hamon::deque<float>>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::vector<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, hamon::vector<float>>()));

#if !(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// VS2019でconstexprにすると内部コンパイラエラーになってしまう
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::list<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, hamon::list<float>>()));
#else
	EXPECT_TRUE((test<int,   hamon::list<int>>()));
	EXPECT_TRUE((test<float, hamon::list<float>>()));
#endif

	EXPECT_TRUE((test<int,   std::deque<int>>()));
	EXPECT_TRUE((test<float, std::deque<float>>()));

	EXPECT_TRUE((test<int,   std::vector<int>>()));
	EXPECT_TRUE((test<float, std::vector<float>>()));

	EXPECT_TRUE((test<int,   std::list<int>>()));
	EXPECT_TRUE((test<float, std::list<float>>()));
}

}	// namespace op_compare_test

}	// namespace hamon_stack_test
