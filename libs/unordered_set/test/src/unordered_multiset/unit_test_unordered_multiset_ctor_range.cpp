/**
 *	@file	unit_test_unordered_multiset_ctor_range.cpp
 *
 *	@brief	rangeを引数に取るコンストラクタのテスト
 *
 *	template<container-compatible-range<value_type> R>
 *	constexpr unordered_multiset(
 *		from_range_t, R&& rg,
 *		size_type n = see below,
 *		const hasher& hf = hasher(),
 *		const key_equal& eql = key_equal(),
 *		const allocator_type& a = allocator_type());
 *
 *	template<container-compatible-range<value_type> R>
 *	constexpr unordered_multiset(
 *		from_range_t, R&& rg,
 *		size_type n,
 *		const allocator_type& a);
 *
 *	template<container-compatible-range<value_type> R>
 *	constexpr unordered_multiset(
 *		from_range_t, R&& rg,
 *		size_type n,
 *		const hasher& hf,
 *		const allocator_type& a);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))

namespace hamon_unordered_multiset_test
{

namespace ctor_range_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, template <typename> class RangeWrapper>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test_impl()
{
	using Set = hamon::unordered_multiset<Key>;
	using SizeType  = typename Set::size_type;
	using Hasher    = typename Set::hasher;
	using KeyEqual  = typename Set::key_equal;
	using Allocator = typename Set::allocator_type;
	using ValueType = typename Set::value_type;
	using Range = RangeWrapper<ValueType>;

	static_assert( hamon::is_constructible<Set, hamon::from_range_t, Range>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::from_range_t, Range, SizeType>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::from_range_t, Range, SizeType, Hasher const&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::from_range_t, Range, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::from_range_t, Range, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::from_range_t, Range, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::from_range_t, Range, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::from_range_t, Range>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::from_range_t, Range, SizeType>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::from_range_t, Range, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::from_range_t, Range, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::from_range_t, Range, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::from_range_t, Range, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::from_range_t, Range, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::from_range_t, Range>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::from_range_t, Range, SizeType>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::from_range_t, Range, SizeType, Hasher const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::from_range_t, Range, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::from_range_t, Range, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::from_range_t, Range, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::from_range_t, Range, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::from_range_t, Range>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::from_range_t, Range, SizeType>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::from_range_t, Range, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::from_range_t, Range, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::from_range_t, Range, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::from_range_t, Range, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::from_range_t, Range, SizeType, Hasher const&, Allocator const&>::value, "");

	Key a[] = { Key{3}, Key{1}, Key{4}, Key{1}, Key{5}, };
	Range r(a);

	// (from_range, rg)
	{
		Set v(hamon::from_range, r);
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 1);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	// (from_range, rg, n)
	{
		Set v(hamon::from_range, r, 10);
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 10);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	// (from_range, rg, n, hf)
	{
		Set v(hamon::from_range, r, 13, Hasher{});
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 13);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	// (from_range, rg, n, hf, eql)
	{
		Set v(hamon::from_range, r, 14, Hasher{}, KeyEqual{});
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 14);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	// (from_range, rg, n, hf, eql, a)
	{
		Allocator alloc;
		Set v(hamon::from_range, r, 15, Hasher{}, KeyEqual{}, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 15);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.get_allocator() == alloc);
	}
	// (from_range, rg, n, a)
	{
		Allocator alloc;
		Set v(hamon::from_range, r, 16, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 16);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.get_allocator() == alloc);
	}
	// (from_range, rg, n, hf, a)
	{
		Allocator alloc;
		Set v(hamon::from_range, r, 5, Hasher{}, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 5);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.get_allocator() == alloc);
	}

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)	// TODO(LWG 2713)
	static_assert( hamon::is_constructible<Set, hamon::from_range_t, Range, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::from_range_t, Range, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::from_range_t, Range, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::from_range_t, Range, Allocator const&>::value, "");

	// (from_range, rg, a)
	{
		Allocator alloc;
		Set v(hamon::from_range, r, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
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
		test_impl<Key, test_input_range>() &&
		test_impl<Key, test_forward_range>() &&
		test_impl<Key, test_bidirectional_range>() &&
		test_impl<Key, test_random_access_range>() &&
		test_impl<Key, test_contiguous_range>() &&
		test_impl<Key, test_input_sized_range>() &&
		test_impl<Key, test_forward_sized_range>() &&
		test_impl<Key, test_bidirectional_sized_range>() &&
		test_impl<Key, test_random_access_sized_range>() &&
		test_impl<Key, test_contiguous_sized_range>();
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, CtorRangeTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace ctor_range_test

}	// namespace hamon_unordered_multiset_test

#endif
