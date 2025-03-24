/**
 *	@file	unit_test_unordered_set_ctor_range.cpp
 *
 *	@brief	rangeを引数に取るコンストラクタのテスト
 *
 *	template<container-compatible-range<value_type> R>
 *	constexpr unordered_set(
 *		from_range_t, R&& rg,
 *		size_type n = see below,
 *		const hasher& hf = hasher(),
 *		const key_equal& eql = key_equal(),
 *		const allocator_type& a = allocator_type());
 *
 *	template<container-compatible-range<value_type> R>
 *	constexpr unordered_set(
 *		from_range_t, R&& rg,
 *		size_type n,
 *		const allocator_type& a);
 *
 *	template<container-compatible-range<value_type> R>
 *	constexpr unordered_set(
 *		from_range_t, R&& rg,
 *		size_type n,
 *		const hasher& hf,
 *		const allocator_type& a);
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_SET) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))

namespace hamon_unordered_set_test
{

namespace ctor_range_test
{

#if !defined(HAMON_USE_STD_UNORDERED_SET)
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, template <typename> class RangeWrapper>
UNORDERED_SET_TEST_CONSTEXPR bool test_impl()
{
	using Set = hamon::unordered_set<Key>;
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

	return true;
}

template <typename Key>
UNORDERED_SET_TEST_CONSTEXPR bool test()
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

GTEST_TEST(UnorderedSetTest, CtorRangeTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace ctor_range_test

}	// namespace hamon_unordered_set_test

#endif
