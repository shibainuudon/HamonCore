/**
 *	@file	unit_test_unordered_set_ctor_iterator.cpp
 *
 *	@brief	イテレータを引数に取るコンストラクタのテスト
 *
 *	template<class InputIterator>
 *	constexpr unordered_set(
 *		InputIterator f, InputIterator l,
 *		size_type n = see below,
 *		const hasher& hf = hasher(),
 *		const key_equal& eql = key_equal(),
 *		const allocator_type& a = allocator_type());
 *
 *	template<class InputIterator>
 *	constexpr unordered_set(
 *		InputIterator f, InputIterator l,
 *		size_type n,
 *		const allocator_type& a);
 *
 *	template<class InputIterator>
 *	constexpr unordered_set(
 *		InputIterator f, InputIterator l,
 *		size_type n,
 *		const hasher& hf,
 *		const allocator_type& a);
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_unordered_set_test
{

namespace ctor_iterator_test
{

#if !defined(HAMON_USE_STD_UNORDERED_SET)
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, template <typename> class IteratorWrapper>
UNORDERED_SET_TEST_CONSTEXPR bool test_impl()
{
	using Set = hamon::unordered_set<Key>;
	using SizeType  = typename Set::size_type;
	using Hasher    = typename Set::hasher;
	using KeyEqual  = typename Set::key_equal;
	using Allocator = typename Set::allocator_type;
	using ValueType = typename Set::value_type;
	using Iterator = IteratorWrapper<ValueType>;

	static_assert( hamon::is_constructible<Set, Iterator, Iterator>::value, "");
	static_assert( hamon::is_constructible<Set, Iterator, Iterator, SizeType>::value, "");
	static_assert( hamon::is_constructible<Set, Iterator, Iterator, SizeType, Hasher const&>::value, "");
	static_assert( hamon::is_constructible<Set, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert( hamon::is_constructible<Set, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, Iterator, Iterator>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, Iterator, Iterator, SizeType>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, Iterator, Iterator, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, Iterator, Iterator>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, Iterator, Iterator, SizeType>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, Iterator, Iterator, SizeType, Hasher const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Iterator, Iterator>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Iterator, Iterator, SizeType>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Iterator, Iterator, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Iterator, Iterator, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");

#if !(defined(HAMON_USE_STD_UNORDERED_SET) && (HAMON_CXX_STANDARD < 14))
	static_assert( hamon::is_constructible<Set, Iterator, Iterator, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_constructible<Set, Iterator, Iterator, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, Iterator, Iterator, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, Iterator, Iterator, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, Iterator, Iterator, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, Iterator, Iterator, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Iterator, Iterator, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Iterator, Iterator, SizeType, Hasher const&, Allocator const&>::value, "");
#endif

	return true;
}

template <typename Key>
UNORDERED_SET_TEST_CONSTEXPR bool test()
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

GTEST_TEST(UnorderedSetTest, CtorIteratorTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace ctor_iterator_test

}	// namespace hamon_unordered_set_test
