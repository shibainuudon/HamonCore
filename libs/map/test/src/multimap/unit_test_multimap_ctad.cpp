/**
 *	@file	unit_test_multimap_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class InputIterator, class Compare = less<iter-key-type<InputIterator>>,
 *		class Allocator = allocator<iter-to-alloc-type<InputIterator>>>
 *	multimap(InputIterator, InputIterator, Compare = Compare(), Allocator = Allocator())
 *	-> multimap<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>, Compare, Allocator>;
 *
 *	template<ranges::input_range R, class Compare = less<range-key-type<R>>,
 *		class Allocator = allocator<range-to-alloc-type<R>>>
 *	multimap(from_range_t, R&&, Compare = Compare(), Allocator = Allocator())
 *	-> multimap<range-key-type<R>, range-mapped-type<R>, Compare, Allocator>;
 *
 *	template<class Key, class T, class Compare = less<Key>,
 *		class Allocator = allocator<pair<const Key, T>>>
 *	multimap(initializer_list<pair<Key, T>>, Compare = Compare(), Allocator = Allocator())
 *	-> multimap<Key, T, Compare, Allocator>;
 *
 *	template<class InputIterator, class Allocator>
 *	multimap(InputIterator, InputIterator, Allocator)
 *	-> multimap<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>, less<iter-key-type<InputIterator>>, Allocator>;
 *
 *	template<ranges::input_range R, class Allocator>
 *	multimap(from_range_t, R&&, Allocator)
 *	-> multimap<range-key-type<R>, range-mapped-type<R>, less<range-key-type<R>>, Allocator>;
 *
 *	template<class Key, class T, class Allocator>
 *	multimap(initializer_list<pair<Key, T>>, Allocator)
 *	-> multimap<Key, T, less<Key>, Allocator>;
 */

#include <hamon/map/multimap.hpp>
#include <hamon/functional.hpp>
#include <hamon/memory.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "ranges_test.hpp"

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

namespace hamon_multimap_test
{

namespace ctad_test
{

#if !defined(HAMON_USE_STD_MULTIMAP)
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T, template <typename> class IteratorWrapper>
MULTIMAP_TEST_CONSTEXPR bool test1_impl()
{
	using DefaultValueType = typename hamon::multimap<Key, T>::value_type;
	using DefaultAllocator = typename hamon::multimap<Key, T>::allocator_type;
	using DefaultCompare = typename hamon::multimap<Key, T>::key_compare;

	using Compare = hamon::less<>;
	using Allocator = hamon::allocator<DefaultValueType>;
	using Set = hamon::multimap<Key, T, Compare, Allocator>;
	using ValueType = typename Set::value_type;
	using Iterator = IteratorWrapper<ValueType>;

	ValueType a[] =
	{
		{Key{3}, T{10}},
		{Key{1}, T{20}},
		{Key{4}, T{30}},
		{Key{1}, T{40}},
		{Key{5}, T{50}},
		{Key{2}, T{60}},
	};

	{
		hamon::multimap v(Iterator{a}, Iterator{a + 6});
		static_assert(hamon::is_same<decltype(v), hamon::multimap<Key, T, DefaultCompare, DefaultAllocator>>::value, "");
	}
	{
		hamon::multimap v(Iterator{a}, Iterator{a + 6}, Compare{});
		static_assert(hamon::is_same<decltype(v), hamon::multimap<Key, T, Compare, DefaultAllocator>>::value, "");
	}
	{
		hamon::multimap v(Iterator{a}, Iterator{a + 6}, Compare{}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::multimap<Key, T, Compare, Allocator>>::value, "");
	}
	{
		hamon::multimap v(Iterator{a}, Iterator{a + 6}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::multimap<Key, T, DefaultCompare, Allocator>>::value, "");
	}

	return true;
}

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test1()
{
	VERIFY(test1_impl<Key, T, cpp17_input_iterator_wrapper>());
//	VERIFY(test1_impl<Key, T, input_iterator_wrapper>());
	VERIFY(test1_impl<Key, T, forward_iterator_wrapper>());
	VERIFY(test1_impl<Key, T, bidirectional_iterator_wrapper>());
	VERIFY(test1_impl<Key, T, random_access_iterator_wrapper>());
	VERIFY(test1_impl<Key, T, contiguous_iterator_wrapper>());
	return true;
}

#if !defined(HAMON_USE_STD_MULTIMAP) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))

template <typename Key, typename T, template <typename> class RangeWrapper>
MULTIMAP_TEST_CONSTEXPR bool test2_impl()
{
	using DefaultValueType = typename hamon::multimap<Key, T>::value_type;
	using DefaultAllocator = typename hamon::multimap<Key, T>::allocator_type;
	using DefaultCompare = typename hamon::multimap<Key, T>::key_compare;

	using Compare = hamon::less<>;
	using Allocator = hamon::allocator<DefaultValueType>;
	using Set = hamon::multimap<Key, T, Compare, Allocator>;
	using ValueType = typename Set::value_type;
	using Range = RangeWrapper<ValueType>;

	ValueType a[] =
	{
		{Key{3}, T{10}},
		{Key{1}, T{20}},
		{Key{4}, T{30}},
		{Key{1}, T{40}},
		{Key{5}, T{50}},
		{Key{2}, T{60}},
	};

	{
		Range r(a);
		hamon::multimap v(hamon::from_range, r);
		static_assert(hamon::is_same<decltype(v), hamon::multimap<Key, T, DefaultCompare, DefaultAllocator>>::value, "");
	}
	{
		Range r(a);
		hamon::multimap v(hamon::from_range, r, Compare{});
		static_assert(hamon::is_same<decltype(v), hamon::multimap<Key, T, Compare, DefaultAllocator>>::value, "");
	}
	{
		Range r(a);
		hamon::multimap v(hamon::from_range, r, Compare{}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::multimap<Key, T, Compare, Allocator>>::value, "");
	}
	{
		Range r(a);
		hamon::multimap v(hamon::from_range, r, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::multimap<Key, T, DefaultCompare, Allocator>>::value, "");
	}

	return true;
}

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test2()
{
	VERIFY(test2_impl<Key, T, test_input_range>());
	VERIFY(test2_impl<Key, T, test_forward_range>());
	VERIFY(test2_impl<Key, T, test_bidirectional_range>());
	VERIFY(test2_impl<Key, T, test_random_access_range>());
	VERIFY(test2_impl<Key, T, test_contiguous_range>());
	VERIFY(test2_impl<Key, T, test_input_sized_range>());
	VERIFY(test2_impl<Key, T, test_forward_sized_range>());
	VERIFY(test2_impl<Key, T, test_bidirectional_sized_range>());
	VERIFY(test2_impl<Key, T, test_random_access_sized_range>());
	VERIFY(test2_impl<Key, T, test_contiguous_sized_range>());
	return true;
}

#endif

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test3()
{
	using DefaultValueType = typename hamon::multimap<Key, T>::value_type;
	using DefaultAllocator = typename hamon::multimap<Key, T>::allocator_type;
	using DefaultCompare = typename hamon::multimap<Key, T>::key_compare;

	using Compare = hamon::less<>;
	using Allocator = hamon::allocator<DefaultValueType>;
#if defined(HAMON_USE_STD_MULTIMAP)
	using ValueType = std::pair<Key, T>;
#else
	using ValueType = hamon::pair<Key, T>;
#endif

	{
		hamon::multimap v({
			ValueType{Key{3}, T{10}},
			ValueType{Key{1}, T{20}},
			ValueType{Key{4}, T{30}},
			ValueType{Key{1}, T{40}},
			ValueType{Key{5}, T{50}},
			ValueType{Key{2}, T{60}},
		});
		static_assert(hamon::is_same<decltype(v), hamon::multimap<Key, T, DefaultCompare, DefaultAllocator>>::value, "");
	}
	{
		hamon::multimap v({
			ValueType{Key{3}, T{10}},
			ValueType{Key{1}, T{20}},
			ValueType{Key{4}, T{30}},
			ValueType{Key{1}, T{40}},
			ValueType{Key{5}, T{50}},
			ValueType{Key{2}, T{60}},
		}, Compare{});
		static_assert(hamon::is_same<decltype(v), hamon::multimap<Key, T, Compare, DefaultAllocator>>::value, "");
	}
	{
		hamon::multimap v{{
			ValueType{Key{3}, T{10}},
			ValueType{Key{1}, T{20}},
			ValueType{Key{4}, T{30}},
			ValueType{Key{1}, T{40}},
			ValueType{Key{5}, T{50}},
			ValueType{Key{2}, T{60}},
		}, Compare{}, Allocator{}};
		static_assert(hamon::is_same<decltype(v), hamon::multimap<Key, T, Compare, Allocator>>::value, "");
	}
	{
		hamon::multimap v({
			ValueType{Key{3}, T{10}},
			ValueType{Key{1}, T{20}},
			ValueType{Key{4}, T{30}},
			ValueType{Key{1}, T{40}},
			ValueType{Key{5}, T{50}},
			ValueType{Key{2}, T{60}},
		}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::multimap<Key, T, DefaultCompare, Allocator>>::value, "");
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MultimapTest, CtadTest)
{
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

#if !defined(HAMON_USE_STD_MULTIMAP) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, float>()));
#endif

	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<int, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<int, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<int, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<char, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<char, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<char, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<float, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<float, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<float, float>()));
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace ctad_test

}	// namespace hamon_multimap_test

#endif
