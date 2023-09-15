/**
 *	@file	unit_test_span_ctor_copy.cpp
 *
 *	@brief	span::span(const span& other) のテスト
 */

#include <hamon/span.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/remove_volatile.hpp>
#include <hamon/type_traits/is_class.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_span_test
{

namespace ctor_copy_test
{

template <typename T>
HAMON_CXX14_CONSTEXPR bool do_copy(T const& rhs)
{
	HAMON_ASSERT_NOEXCEPT_TRUE(T{ rhs });
	T lhs{ rhs };
	return
		lhs.data() == rhs.data() &&
		lhs.size() == rhs.size();
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool test2()
{
	using U = hamon::conditional_t<
		hamon::is_class<T>::value,
		hamon::remove_volatile_t<T>,
		T
	>;
	U a[3]{};
	return
		do_copy(hamon::span<T   >()) &&
		do_copy(hamon::span<T, 0>()) &&
		do_copy(hamon::span<T   >(a, 1)) &&
		do_copy(hamon::span<T, 1>(a, 1)) &&
		do_copy(hamon::span<T   >(a, 2)) &&
		do_copy(hamon::span<T, 2>(a, 2)) &&
		do_copy(hamon::span<T   >(a, 3)) &&
		do_copy(hamon::span<T, 3>(a, 3));
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
test()
{
	return
		test2<T      >() &&
		test2<T const>();
}

struct A{};

GTEST_TEST(SpanTest, CtorCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<A>()));
	                      EXPECT_TRUE((test<hamon::string>()));
}

}	// namespace ctor_copy_test

}	// namespace hamon_span_test
