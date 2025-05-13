/**
 *	@file	unit_test_queue_op_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class T, class Container>
 *	constexpr bool operator==(const queue<T, Container>& x, const queue<T, Container>& y);
 *
 *	template<class T, class Container>
 *	constexpr bool operator!=(const queue<T, Container>& x, const queue<T, Container>& y);
 *
 *	template<class T, class Container>
 *	constexpr bool operator< (const queue<T, Container>& x, const queue<T, Container>& y);
 *
 *	template<class T, class Container>
 *	constexpr bool operator> (const queue<T, Container>& x, const queue<T, Container>& y);
 *
 *	template<class T, class Container>
 *	constexpr bool operator<=(const queue<T, Container>& x, const queue<T, Container>& y);
 *
 *	template<class T, class Container>
 *	constexpr bool operator>=(const queue<T, Container>& x, const queue<T, Container>& y);
 *
 *	template<class T, three_way_comparable Container>
 *	constexpr compare_three_way_result_t<Container>
 *	operator<=>(const queue<T, Container>& x, const queue<T, Container>& y);
 */

#include <hamon/queue/queue.hpp>
#include <hamon/deque.hpp>
#include <hamon/list.hpp>
#include <hamon/compare.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_queue_test
{

namespace op_compare_test
{

#if !defined(HAMON_USE_STD_QUEUE) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// VS2019でconstexprにすると内部コンパイラエラーになってしまう
#define QUEUE_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define QUEUE_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define QUEUE_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define QUEUE_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container>
QUEUE_TEST_CONSTEXPR bool test()
{
	using Queue = hamon::queue<T, Container>;

	static_assert(hamon::is_same<decltype(hamon::declval<Queue const&>() == hamon::declval<Queue const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Queue const&>() != hamon::declval<Queue const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Queue const&>() <  hamon::declval<Queue const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Queue const&>() >  hamon::declval<Queue const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Queue const&>() <= hamon::declval<Queue const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Queue const&>() >= hamon::declval<Queue const&>()), bool>::value, "");

	static_assert(!noexcept(hamon::declval<Queue const&>() == hamon::declval<Queue const&>()), "");
	static_assert(!noexcept(hamon::declval<Queue const&>() != hamon::declval<Queue const&>()), "");
	static_assert(!noexcept(hamon::declval<Queue const&>() <  hamon::declval<Queue const&>()), "");
	static_assert(!noexcept(hamon::declval<Queue const&>() >  hamon::declval<Queue const&>()), "");
	static_assert(!noexcept(hamon::declval<Queue const&>() <= hamon::declval<Queue const&>()), "");
	static_assert(!noexcept(hamon::declval<Queue const&>() >= hamon::declval<Queue const&>()), "");

	Container const c1 {1, 2, 3};
	Container const c2 {1, 2, 3};
	Container const c3 {0, 2, 3};
	Container const c4 {1, 2, 4};
	Container const c5 {1, 2};
	Container const c6 {1, 2, 3, 4};
	Queue const v1(c1);
	Queue const v2(c2);
	Queue const v3(c3);
	Queue const v4(c4);
	Queue const v5(c5);
	Queue const v6(c6);

	VERIFY( (v1 == v1));
	VERIFY( (v1 == v2));
	VERIFY(!(v1 == v3));
	VERIFY(!(v1 == v4));
	VERIFY(!(v1 == v5));
	VERIFY(!(v1 == v6));

	VERIFY(!(v1 != v1));
	VERIFY(!(v1 != v2));
	VERIFY( (v1 != v3));
	VERIFY( (v1 != v4));
	VERIFY( (v1 != v5));
	VERIFY( (v1 != v6));

	VERIFY(!(v1 < v1));
	VERIFY(!(v1 < v2));
	VERIFY(!(v1 < v3));
	VERIFY( (v1 < v4));
	VERIFY(!(v1 < v5));
	VERIFY( (v1 < v6));

	VERIFY(!(v1 > v1));
	VERIFY(!(v1 > v2));
	VERIFY( (v1 > v3));
	VERIFY(!(v1 > v4));
	VERIFY( (v1 > v5));
	VERIFY(!(v1 > v6));

	VERIFY( (v1 <= v1));
	VERIFY( (v1 <= v2));
	VERIFY(!(v1 <= v3));
	VERIFY( (v1 <= v4));
	VERIFY(!(v1 <= v5));
	VERIFY( (v1 <= v6));

	VERIFY( (v1 >= v1));
	VERIFY( (v1 >= v2));
	VERIFY( (v1 >= v3));
	VERIFY(!(v1 >= v4));
	VERIFY( (v1 >= v5));
	VERIFY(!(v1 >= v6));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(hamon::is_same<decltype(hamon::declval<Queue const&>() <=> hamon::declval<Queue const&>()), hamon::compare_three_way_result_t<Container>>::value, "");
	static_assert(!noexcept(hamon::declval<Queue const&>() <=> hamon::declval<Queue const&>()), "");

	VERIFY( hamon::is_eq(v1 <=> v1));
	VERIFY( hamon::is_eq(v1 <=> v2));
	VERIFY(!hamon::is_eq(v1 <=> v3));
	VERIFY(!hamon::is_eq(v1 <=> v4));
	VERIFY(!hamon::is_eq(v1 <=> v5));
	VERIFY(!hamon::is_eq(v1 <=> v6));

	VERIFY(!hamon::is_lt(v1 <=> v1));
	VERIFY(!hamon::is_lt(v1 <=> v2));
	VERIFY(!hamon::is_lt(v1 <=> v3));
	VERIFY( hamon::is_lt(v1 <=> v4));
	VERIFY(!hamon::is_lt(v1 <=> v5));
	VERIFY( hamon::is_lt(v1 <=> v6));

	VERIFY(!hamon::is_gt(v1 <=> v1));
	VERIFY(!hamon::is_gt(v1 <=> v2));
	VERIFY( hamon::is_gt(v1 <=> v3));
	VERIFY(!hamon::is_gt(v1 <=> v4));
	VERIFY( hamon::is_gt(v1 <=> v5));
	VERIFY(!hamon::is_gt(v1 <=> v6));
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(QueueTest, OpCompareTest)
{
	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::deque<int>>()));
	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::deque<float>>()));

	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::list<int>>()));
	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::list<float>>()));

	EXPECT_TRUE((test<int,   std::deque<int>>()));
	EXPECT_TRUE((test<float, std::deque<float>>()));

	EXPECT_TRUE((test<int,   std::list<int>>()));
	EXPECT_TRUE((test<float, std::list<float>>()));
}

#undef QUEUE_TEST_CONSTEXPR_EXPECT_TRUE
#undef QUEUE_TEST_CONSTEXPR

}	// namespace op_compare_test

}	// namespace hamon_queue_test
