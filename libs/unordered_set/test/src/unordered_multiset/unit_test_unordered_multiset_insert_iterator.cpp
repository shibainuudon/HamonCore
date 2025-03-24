/**
 *	@file	unit_test_unordered_multiset_insert_iterator.cpp
 *
 *	@brief	insert のテスト
 *
 *	template<class InputIterator> constexpr void insert(InputIterator first, InputIterator last);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace insert_iterator_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, template <typename> class IteratorWrapper>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test_impl()
{
	using Set = hamon::unordered_multiset<Key>;
	using ValueType = typename Set::value_type;
	using InputIterator = IteratorWrapper<ValueType>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().insert(hamon::declval<InputIterator>(), hamon::declval<InputIterator>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().insert(hamon::declval<InputIterator>(), hamon::declval<InputIterator>())), "");

	return true;
}

template <typename Key>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test()
{
	return
		test_impl<Key, cpp17_input_iterator_wrapper>() &&
		//test_impl<Key, input_iterator_wrapper>() &&
		test_impl<Key, forward_iterator_wrapper>() &&
		test_impl<Key, bidirectional_iterator_wrapper>() &&
		test_impl<Key, random_access_iterator_wrapper>() &&
		test_impl<Key, contiguous_iterator_wrapper>();
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, InsertIteratorTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace insert_iterator_test

}	// namespace hamon_unordered_multiset_test
