/**
 *	@file	unit_test_iterator_common_iterator_incrementable_traits.cpp
 *
 *	@brief	incrementable_traits のテスト
 *
 *	template<class I, class S>
 *	struct incrementable_traits<common_iterator<I, S>> {
 *		using difference_type = iter_difference_t<I>;
 *	};
 */

#include <hamon/iterator/common_iterator.hpp>
#include <hamon/iterator/incrementable_traits.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_iterator_test {
namespace common_iterator_test {
namespace incrementable_traits_test {

template <typename T>
struct TestIterator
{
	T*	m_ptr;
	using difference_type = short;
	TestIterator& operator++();
	void          operator++(int);
	T             operator*();
};

template <typename I, typename S>
HAMON_CXX14_CONSTEXPR bool test()
{
	using CI = hamon::common_iterator<I, S>;
	using Traits = hamon::incrementable_traits<CI>;
	static_assert(hamon::is_same<typename Traits::difference_type, hamon::iter_difference_t<I>>::value, "");
	return true;
}

GTEST_TEST(CommonIteratorTest, IncrementableTraitsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int*, int const*>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int*, test_sentinel<int*>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int*, hamon::unreachable_sentinel_t>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<input_or_output_iterator_wrapper<int>, hamon::unreachable_sentinel_t>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<input_or_output_iterator_wrapper<int>, test_sentinel<input_or_output_iterator_wrapper<int>>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<TestIterator<int>, hamon::unreachable_sentinel_t>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<TestIterator<int>, test_sentinel<TestIterator<int>>>()));
}

}	// namespace incrementable_traits_test
}	// namespace common_iterator_test
}	// namespace hamon_iterator_test
