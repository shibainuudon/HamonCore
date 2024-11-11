/**
 *	@file	unit_test_set_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class InputIterator,
 *		class Compare = less<iter-value-type<InputIterator>>,
 *		class Allocator = allocator<iter-value-type<InputIterator>>>
 *	set(InputIterator, InputIterator, Compare = Compare(), Allocator = Allocator())
 *		-> set<iter-value-type<InputIterator>, Compare, Allocator>;
 *
 *	template<ranges::input_range R, class Compare = less<ranges::range_value_t<R>>,
 *		class Allocator = allocator<ranges::range_value_t<R>>>
 *	set(from_range_t, R&&, Compare = Compare(), Allocator = Allocator())
 *		-> set<ranges::range_value_t<R>, Compare, Allocator>;
 *
 *	template<class Key, class Compare = less<Key>, class Allocator = allocator<Key>>
 *	set(initializer_list<Key>, Compare = Compare(), Allocator = Allocator())
 *		-> set<Key, Compare, Allocator>;
 *
 *	template<class InputIterator, class Allocator>
 *	set(InputIterator, InputIterator, Allocator)
 *		-> set<iter-value-type<InputIterator>, less<iter-value-type<InputIterator>>, Allocator>;
 *
 *	template<ranges::input_range R, class Allocator>
 *	set(from_range_t, R&&, Allocator)
 *		-> set<ranges::range_value_t<R>, less<ranges::range_value_t<R>>, Allocator>;
 *
 *	template<class Key, class Allocator>
 *	set(initializer_list<Key>, Allocator) -> set<Key, less<Key>, Allocator>;
 */

#include <hamon/set/set.hpp>
#include <hamon/functional.hpp>
#include <hamon/memory.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "ranges_test.hpp"

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

namespace hamon_set_test
{

namespace ctad_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, template <typename> class IteratorWrapper>
SET_TEST_CONSTEXPR bool test1_impl()
{
	using Compare = hamon::less<>;
	using Allocator = hamon::allocator<Key>;
	using Set = hamon::set<Key, Compare, Allocator>;
	using ValueType = typename Set::value_type;
	using Iterator = IteratorWrapper<ValueType>;
	using DefaultAllocator = typename hamon::set<Key>::allocator_type;
	using DefaultCompare = typename hamon::set<Key>::key_compare;

	ValueType a[] =
	{
		Key{2}, Key{3}, Key{1}, Key{1}, Key{2}, Key{3},
	};

	{
		hamon::set v(Iterator{a}, Iterator{a + 6});
		static_assert(hamon::is_same<decltype(v), hamon::set<Key, DefaultCompare, DefaultAllocator>>::value, "");
	}
	{
		hamon::set v(Iterator{a}, Iterator{a + 6}, Compare{});
		static_assert(hamon::is_same<decltype(v), hamon::set<Key, Compare, DefaultAllocator>>::value, "");
	}
	{
		hamon::set v(Iterator{a}, Iterator{a + 6}, Compare{}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::set<Key, Compare, Allocator>>::value, "");
	}
	{
		hamon::set v(Iterator{a}, Iterator{a + 6}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::set<Key, DefaultCompare, Allocator>>::value, "");
	}

	return true;
}

template <typename Key>
SET_TEST_CONSTEXPR bool test1()
{
	VERIFY(test1_impl<Key, cpp17_input_iterator_wrapper>());
//	VERIFY(test1_impl<Key, input_iterator_wrapper>());
	VERIFY(test1_impl<Key, forward_iterator_wrapper>());
	VERIFY(test1_impl<Key, bidirectional_iterator_wrapper>());
	VERIFY(test1_impl<Key, random_access_iterator_wrapper>());
	VERIFY(test1_impl<Key, contiguous_iterator_wrapper>());
	return true;
}

#if !defined(HAMON_USE_STD_SET) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))

template <typename Key, template <typename> class RangeWrapper>
SET_TEST_CONSTEXPR bool test2_impl()
{
	using Compare = hamon::less<>;
	using Allocator = hamon::allocator<Key>;
	using Set = hamon::set<Key, Compare, Allocator>;
	using ValueType = typename Set::value_type;
	using Range = RangeWrapper<ValueType>;
	using DefaultAllocator = typename hamon::set<Key>::allocator_type;
	using DefaultCompare = typename hamon::set<Key>::key_compare;

	ValueType a[] =
	{
		Key{3}, Key{1}, Key{4}, Key{1}, Key{5}, Key{9}, Key{2},
	};

	{
		Range r(a);
		hamon::set v(hamon::from_range, r);
		static_assert(hamon::is_same<decltype(v), hamon::set<Key, DefaultCompare, DefaultAllocator>>::value, "");
	}
	{
		Range r(a);
		hamon::set v(hamon::from_range, r, Compare{});
		static_assert(hamon::is_same<decltype(v), hamon::set<Key, Compare, DefaultAllocator>>::value, "");
	}
	{
		Range r(a);
		hamon::set v(hamon::from_range, r, Compare{}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::set<Key, Compare, Allocator>>::value, "");
	}
	{
		Range r(a);
		hamon::set v(hamon::from_range, r, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::set<Key, DefaultCompare, Allocator>>::value, "");
	}

	return true;
}

template <typename Key>
SET_TEST_CONSTEXPR bool test2()
{
	VERIFY(test2_impl<Key, test_input_range>());
	VERIFY(test2_impl<Key, test_forward_range>());
	VERIFY(test2_impl<Key, test_bidirectional_range>());
	VERIFY(test2_impl<Key, test_random_access_range>());
	VERIFY(test2_impl<Key, test_contiguous_range>());
	VERIFY(test2_impl<Key, test_input_sized_range>());
	VERIFY(test2_impl<Key, test_forward_sized_range>());
	VERIFY(test2_impl<Key, test_bidirectional_sized_range>());
	VERIFY(test2_impl<Key, test_random_access_sized_range>());
	VERIFY(test2_impl<Key, test_contiguous_sized_range>());
	return true;
}

#endif

template <typename Key>
SET_TEST_CONSTEXPR bool test3()
{
	using Compare = hamon::less<>;
	using Allocator = hamon::allocator<Key>;
	using DefaultAllocator = typename hamon::set<Key>::allocator_type;
	using DefaultCompare = typename hamon::set<Key>::key_compare;

	{
		hamon::set v({ Key{3}, Key{1}, Key{4}, Key{1}, Key{5} });
		static_assert(hamon::is_same<decltype(v), hamon::set<Key, DefaultCompare, DefaultAllocator>>::value, "");
	}
	{
		hamon::set v({ Key{3}, Key{1}, Key{4}, Key{1}, Key{5} }, Compare{});
		static_assert(hamon::is_same<decltype(v), hamon::set<Key, Compare, DefaultAllocator>>::value, "");
	}
	{
		hamon::set v({ Key{3}, Key{1}, Key{4}, Key{1}, Key{5} }, Compare{}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::set<Key, Compare, Allocator>>::value, "");
	}
	{
		hamon::set v({ Key{3}, Key{1}, Key{4}, Key{1}, Key{5} }, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::set<Key, DefaultCompare, Allocator>>::value, "");
	}

	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, CtadTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

#if !defined(HAMON_USE_STD_SET) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test2<int>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test2<char>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test2<float>());
#endif

	SET_TEST_CONSTEXPR_EXPECT_TRUE(test3<int>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test3<char>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test3<float>());
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace ctad_test

}	// namespace hamon_set_test

#endif
