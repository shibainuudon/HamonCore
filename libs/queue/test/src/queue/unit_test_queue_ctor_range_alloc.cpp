/**
 *	@file	unit_test_queue_ctor_range_alloc.cpp
 *
 *	@brief	range と Alloc を引数に取るコンストラクタのテスト
 *
 *	template<container-compatible-range<T> R, class Alloc>
 *	constexpr queue(from_range_t, R&& rg, const Alloc&);
 */

#include <hamon/queue/queue.hpp>
#include <hamon/deque.hpp>
#include <hamon/list.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "queue_test_helper.hpp"

#if !defined(HAMON_USE_STD_QUEUE) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))

namespace hamon_queue_test
{

namespace ctor_range_alloc_test
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

template <typename T, typename Container, template <typename> class RangeWrapper>
QUEUE_TEST_CONSTEXPR bool test_impl()
{
	using Queue = hamon::queue<T, Container>;
	using Range = RangeWrapper<T>;
	using Alloc = TestAllocator<T>;

	static_assert( hamon::is_constructible<Queue, hamon::from_range_t, Range, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Queue, hamon::from_range_t, Range, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Queue, hamon::from_range_t, Range, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Queue, hamon::from_range_t, Range, Alloc const&>::value, "");

	T v[] = { T{1}, T{2}, T{3}, T{4}, T{5}, };
	Range r(v);
	Alloc a{};
	Queue const q(hamon::from_range, r, a);
	VERIFY(!q.empty());
	VERIFY(q.size()  == 5);
	VERIFY(q.front() == T{1});
	VERIFY(q.back()  == T{5});

	return true;
}

template <typename T, typename Container>
QUEUE_TEST_CONSTEXPR bool test()
{
	VERIFY((test_impl<T, Container, test_input_range>()));
	VERIFY((test_impl<T, Container, test_forward_range>()));
	VERIFY((test_impl<T, Container, test_bidirectional_range>()));
	VERIFY((test_impl<T, Container, test_random_access_range>()));
	VERIFY((test_impl<T, Container, test_contiguous_range>()));
	VERIFY((test_impl<T, Container, test_input_sized_range>()));
	VERIFY((test_impl<T, Container, test_forward_sized_range>()));
	VERIFY((test_impl<T, Container, test_bidirectional_sized_range>()));
	VERIFY((test_impl<T, Container, test_random_access_sized_range>()));
	VERIFY((test_impl<T, Container, test_contiguous_sized_range>()));
	return true;
}

#undef VERIFY

GTEST_TEST(QueueTest, CtorRangeAllocTest)
{
	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::deque<int>>()));
	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::deque<float>>()));

	EXPECT_TRUE((test<int,   hamon::list<int>>()));
	EXPECT_TRUE((test<float, hamon::list<float>>()));

	EXPECT_TRUE((test<int,   std::deque<int,   hamon::allocator<int>>>()));
	EXPECT_TRUE((test<float, std::deque<float, hamon::allocator<float>>>()));

	EXPECT_TRUE((test<int,   std::list<int,   hamon::allocator<int>>>()));
	EXPECT_TRUE((test<float, std::list<float, hamon::allocator<float>>>()));
}

#undef QUEUE_TEST_CONSTEXPR_EXPECT_TRUE
#undef QUEUE_TEST_CONSTEXPR

}	// namespace ctor_range_alloc_test

}	// namespace hamon_queue_test

#endif
