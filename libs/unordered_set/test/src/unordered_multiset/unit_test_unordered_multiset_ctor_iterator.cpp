/**
 *	@file	unit_test_unordered_multiset_ctor_iterator.cpp
 *
 *	@brief	イテレータを引数に取るコンストラクタのテスト
 *
 *	template<class InputIterator>
 *	constexpr unordered_multiset(
 *		InputIterator f, InputIterator l,
 *		size_type n = see below,
 *		const hasher& hf = hasher(),
 *		const key_equal& eql = key_equal(),
 *		const allocator_type& a = allocator_type());
 *
 *	template<class InputIterator>
 *	constexpr unordered_multiset(
 *		InputIterator f, InputIterator l,
 *		size_type n,
 *		const allocator_type& a);
 *
 *	template<class InputIterator>
 *	constexpr unordered_multiset(
 *		InputIterator f, InputIterator l,
 *		size_type n,
 *		const hasher& hf,
 *		const allocator_type& a);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace ctor_iterator_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
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

	Key a[] = { Key{2}, Key{3}, Key{1}, Key{1}, Key{2}, Key{3}, };

	// (f, l)
	{
		Set v(Iterator{a}, Iterator{a + 6});
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 1);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	// (f, l, n)
	{
		Set v(Iterator{a}, Iterator{a + 6}, 2);
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 2);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	// (f, l, n, hf)
	{
		Set v(Iterator{a}, Iterator{a + 6}, 3, Hasher{});
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 3);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	// (f, l, n, hf, eql)
	{
		Set v(Iterator{a}, Iterator{a + 6}, 4, Hasher{}, KeyEqual{});
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 4);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	// (f, l, n, hf, eql, a)
	{
		Allocator alloc;
		Set v(Iterator{a}, Iterator{a + 6}, 5, Hasher{}, KeyEqual{}, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 5);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.get_allocator() == alloc);
	}

#if !(defined(HAMON_USE_STD_UNORDERED_MULTISET) && (HAMON_CXX_STANDARD < 14))
	static_assert( hamon::is_constructible<Set, Iterator, Iterator, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_constructible<Set, Iterator, Iterator, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, Iterator, Iterator, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, Iterator, Iterator, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, Iterator, Iterator, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, Iterator, Iterator, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Iterator, Iterator, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Iterator, Iterator, SizeType, Hasher const&, Allocator const&>::value, "");

	// (f, l, n, a)
	{
		Allocator alloc;
		Set v(Iterator{a}, Iterator{a + 6}, 1, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 1);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.get_allocator() == alloc);
	}
	// (f, l, n, hf, a)
	{
		Allocator alloc;
		Set v(Iterator{a}, Iterator{a + 6}, 11, Hasher{}, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 11);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.get_allocator() == alloc);
	}
#endif

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)	// TODO(LWG 2713)
	static_assert( hamon::is_constructible<Set, Iterator, Iterator, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, Iterator, Iterator, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, Iterator, Iterator, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Iterator, Iterator, Allocator const&>::value, "");

	// (f, l, a)
	{
		Allocator alloc;
		Set v(Iterator{a}, Iterator{a + 6}, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 1);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.get_allocator() == alloc);
	}
#endif

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

GTEST_TEST(UnorderedMultisetTest, CtorIteratorTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace ctor_iterator_test

}	// namespace hamon_unordered_multiset_test
