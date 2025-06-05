/**
 *	@file	unit_test_flat_map_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class KeyContainer, class MappedContainer, class Compare = less<typename KeyContainer::value_type>>
 *	flat_map(KeyContainer, MappedContainer, Compare = Compare())
 *	-> flat_map<typename KeyContainer::value_type, typename MappedContainer::value_type, Compare, KeyContainer, MappedContainer>;
 *
 *	template<class KeyContainer, class MappedContainer, class Allocator>
 *	flat_map(KeyContainer, MappedContainer, Allocator)
 *	-> flat_map<typename KeyContainer::value_type, typename MappedContainer::value_type, less<typename KeyContainer::value_type>, KeyContainer, MappedContainer>;
 *
 *	template<class KeyContainer, class MappedContainer, class Compare, class Allocator>
 *	flat_map(KeyContainer, MappedContainer, Compare, Allocator)
 *	-> flat_map<typename KeyContainer::value_type, typename MappedContainer::value_type, Compare, KeyContainer, MappedContainer>;
 *
 *	template<class KeyContainer, class MappedContainer, class Compare = less<typename KeyContainer::value_type>>
 *	flat_map(sorted_unique_t, KeyContainer, MappedContainer, Compare = Compare())
 *	-> flat_map<typename KeyContainer::value_type, typename MappedContainer::value_type, Compare, KeyContainer, MappedContainer>;
 *
 *	template<class KeyContainer, class MappedContainer, class Allocator>
 *	flat_map(sorted_unique_t, KeyContainer, MappedContainer, Allocator)
 *	-> flat_map<typename KeyContainer::value_type, typename MappedContainer::value_type, less<typename KeyContainer::value_type>, KeyContainer, MappedContainer>;
 *
 *	template<class KeyContainer, class MappedContainer, class Compare, class Allocator>
 *	flat_map(sorted_unique_t, KeyContainer, MappedContainer, Compare, Allocator)
 *	-> flat_map<typename KeyContainer::value_type, typename MappedContainer::value_type, Compare, KeyContainer, MappedContainer>;
 *
 *	template<class InputIterator, class Compare = less<iter-key-type<InputIterator>>>
 *	flat_map(InputIterator, InputIterator, Compare = Compare())
 *	-> flat_map<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>, Compare>;
 *
 *	template<class InputIterator, class Compare = less<iter-key-type<InputIterator>>>
 *	flat_map(sorted_unique_t, InputIterator, InputIterator, Compare = Compare())
 *	-> flat_map<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>, Compare>;
 *
 *	template<ranges::input_range R, class Compare = less<range-key-type<R>>, class Allocator = allocator<byte>>
 *	flat_map(from_range_t, R&&, Compare = Compare(), Allocator = Allocator())
 *	-> flat_map<range-key-type<R>, range-mapped-type<R>, Compare,
 *		vector<range-key-type<R>, alloc-rebind<Allocator, range-key-type<R>>>,
 *		vector<range-mapped-type<R>, alloc-rebind<Allocator, range-mapped-type<R>>>>;
 *
 *	template<ranges::input_range R, class Allocator>
 *	flat_map(from_range_t, R&&, Allocator)
 *	-> flat_map<range-key-type<R>, range-mapped-type<R>, less<range-key-type<R>>,
 *		vector<range-key-type<R>, alloc-rebind<Allocator, range-key-type<R>>>,
 *		vector<range-mapped-type<R>, alloc-rebind<Allocator, range-mapped-type<R>>>>;
 *
 *	template<class Key, class T, class Compare = less<Key>>
 *	flat_map(initializer_list<pair<Key, T>>, Compare = Compare())
 *	-> flat_map<Key, T, Compare>;
 *
 *	template<class Key, class T, class Compare = less<Key>>
 *	flat_map(sorted_unique_t, initializer_list<pair<Key, T>>, Compare = Compare())
 *	-> flat_map<Key, T, Compare>;
 */

#include <hamon/flat_map/flat_map.hpp>
#include <hamon/algorithm.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "ranges_test.hpp"
#include "flat_map_test_helper.hpp"

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

namespace hamon_flat_map_test
{

namespace ctad_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare>
FLAT_MAP_TEST_CONSTEXPR bool test1()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using DefaultCompare = typename hamon::flat_map<Key, T>::key_compare;
	using Alloc = hamon::allocator<char>;

	// (key_cont, mapped_cont)
	{
		KeyContainer const key_cont {Key{3}, Key{1}, Key{4}};
		MappedContainer const mapped_cont {T{10}, T{20}, T{30}};
		hamon::flat_map v{key_cont, mapped_cont};
		static_assert(hamon::is_same<decltype(v), hamon::flat_map<Key, T, DefaultCompare, KeyContainer, MappedContainer>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (key_cont, mapped_cont, comp)
	{
		KeyContainer const key_cont {Key{3}, Key{1}, Key{4}};
		MappedContainer const mapped_cont {T{10}, T{20}, T{30}};
		Compare const comp;
		hamon::flat_map v{key_cont, mapped_cont, comp};
		static_assert(hamon::is_same<decltype(v), hamon::flat_map<Key, T, Compare, KeyContainer, MappedContainer>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (key_cont, mapped_cont, alloc)
	{
		KeyContainer const key_cont {Key{3}, Key{1}, Key{4}};
		MappedContainer const mapped_cont {T{10}, T{20}, T{30}};
		Alloc const alloc;
		hamon::flat_map v{key_cont, mapped_cont, alloc};
		static_assert(hamon::is_same<decltype(v), hamon::flat_map<Key, T, DefaultCompare, KeyContainer, MappedContainer>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (key_cont, mapped_cont, comp, alloc)
	{
		KeyContainer const key_cont {Key{3}, Key{1}, Key{4}};
		MappedContainer const mapped_cont {T{10}, T{20}, T{30}};
		Compare const comp;
		Alloc const alloc;
		hamon::flat_map v{key_cont, mapped_cont, comp, alloc};
		static_assert(hamon::is_same<decltype(v), hamon::flat_map<Key, T, Compare, KeyContainer, MappedContainer>>::value, "");
		VERIFY(check_invariant(v));
	}

	// (sorted_unique, key_cont, mapped_cont)
	{
		KeyContainer key_cont {Key{3}, Key{1}, Key{4}};
		MappedContainer const mapped_cont {T{10}, T{20}, T{30}};
		hamon::ranges::sort(key_cont, DefaultCompare{});
		hamon::flat_map v{hamon::sorted_unique, key_cont, mapped_cont};
		static_assert(hamon::is_same<decltype(v), hamon::flat_map<Key, T, DefaultCompare, KeyContainer, MappedContainer>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (sorted_unique, key_cont, mapped_cont, comp)
	{
		KeyContainer key_cont {Key{3}, Key{1}, Key{4}};
		MappedContainer const mapped_cont {T{10}, T{20}, T{30}};
		Compare const comp;
		hamon::ranges::sort(key_cont, comp);
		hamon::flat_map v{hamon::sorted_unique, key_cont, mapped_cont, comp};
		static_assert(hamon::is_same<decltype(v), hamon::flat_map<Key, T, Compare, KeyContainer, MappedContainer>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (sorted_unique, key_cont, mapped_cont, alloc)
	{
		KeyContainer key_cont {Key{3}, Key{1}, Key{4}};
		MappedContainer const mapped_cont {T{10}, T{20}, T{30}};
		Alloc const alloc;
		hamon::ranges::sort(key_cont, DefaultCompare{});
		hamon::flat_map v{hamon::sorted_unique, key_cont, mapped_cont, alloc};
		static_assert(hamon::is_same<decltype(v), hamon::flat_map<Key, T, DefaultCompare, KeyContainer, MappedContainer>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (sorted_unique, key_cont, mapped_cont, comp, alloc)
	{
		KeyContainer key_cont {Key{3}, Key{1}, Key{4}};
		MappedContainer const mapped_cont {T{10}, T{20}, T{30}};
		Compare const comp;
		Alloc const alloc;
		hamon::ranges::sort(key_cont, comp);
		hamon::flat_map v{hamon::sorted_unique, key_cont, mapped_cont, comp, alloc};
		static_assert(hamon::is_same<decltype(v), hamon::flat_map<Key, T, Compare, KeyContainer, MappedContainer>>::value, "");
		VERIFY(check_invariant(v));
	}

	return true;
}

template <typename KeyContainer, typename MappedContainer, typename Compare, template <typename> class IteratorWrapper>
FLAT_MAP_TEST_CONSTEXPR bool test2_impl()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using ValueType = typename hamon::flat_map<Key, T>::value_type;
	using InputIterator = IteratorWrapper<ValueType>;

	ValueType a[] =
	{
		{Key{1}, T{10}},
		{Key{2}, T{20}},
		{Key{4}, T{30}},
	};

	// (first, last)
	{
		hamon::flat_map v{InputIterator{a}, InputIterator{a + 3}};
		static_assert(hamon::is_same<decltype(v), hamon::flat_map<Key, T>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (first, last, comp)
	{
		Compare const comp;
		hamon::flat_map v{InputIterator{a}, InputIterator{a + 3}, comp};
		static_assert(hamon::is_same<decltype(v), hamon::flat_map<Key, T, Compare>>::value, "");
		VERIFY(check_invariant(v));
	}

	// (sorted_unique, first, last)
	{
		hamon::flat_map v{hamon::sorted_unique, InputIterator{a}, InputIterator{a + 3}};
		static_assert(hamon::is_same<decltype(v), hamon::flat_map<Key, T>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (sorted_unique, first, last, comp)
	{
		hamon::less<> const comp;
		hamon::flat_map v{hamon::sorted_unique, InputIterator{a}, InputIterator{a + 3}, comp};
		static_assert(hamon::is_same<decltype(v), hamon::flat_map<Key, T, hamon::less<>>>::value, "");
		VERIFY(check_invariant(v));
	}

	return true;
}

template <typename KeyContainer, typename MappedContainer, typename Compare>
FLAT_MAP_TEST_CONSTEXPR bool test2()
{
	VERIFY(test2_impl<KeyContainer, MappedContainer, Compare, cpp17_input_iterator_wrapper>());
//	VERIFY(test2_impl<KeyContainer, MappedContainer, Compare, input_iterator_wrapper>());
	VERIFY(test2_impl<KeyContainer, MappedContainer, Compare, forward_iterator_wrapper>());
	VERIFY(test2_impl<KeyContainer, MappedContainer, Compare, bidirectional_iterator_wrapper>());
	VERIFY(test2_impl<KeyContainer, MappedContainer, Compare, random_access_iterator_wrapper>());
	VERIFY(test2_impl<KeyContainer, MappedContainer, Compare, contiguous_iterator_wrapper>());

	return true;
}

template <typename KeyContainer, typename MappedContainer, typename Compare, template <typename> class RangeWrapper>
FLAT_MAP_TEST_CONSTEXPR bool test3_impl()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using ValueType = typename hamon::flat_map<Key, T>::value_type;
	using Range = RangeWrapper<ValueType>;
	using Alloc = hamon::allocator<char>;

	ValueType a[] =
	{
		{Key{1}, T{10}},
		{Key{2}, T{20}},
		{Key{4}, T{30}},
	};

	// (from_range, rg)
	{
		hamon::flat_map v{hamon::from_range, Range{a}};
		static_assert(hamon::is_same<decltype(v), hamon::flat_map<Key, T>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (from_range, rg, compare)
	{
		Compare const comp;
		hamon::flat_map v{hamon::from_range, Range{a}, comp};
		static_assert(hamon::is_same<decltype(v), hamon::flat_map<Key, T, Compare>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (from_range, rg, compare, alloc)
	{
		Compare const comp;
		Alloc const alloc;
		hamon::flat_map v{hamon::from_range, Range{a}, comp, alloc};
		static_assert(hamon::is_same<decltype(v), hamon::flat_map<Key, T, Compare>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (from_range, rg, alloc)
	{
		Alloc const alloc;
		hamon::flat_map v{hamon::from_range, Range{a}, alloc};
		static_assert(hamon::is_same<decltype(v), hamon::flat_map<Key, T>>::value, "");
		VERIFY(check_invariant(v));
	}

	return true;
}

template <typename KeyContainer, typename MappedContainer, typename Compare>
FLAT_MAP_TEST_CONSTEXPR bool test3()
{
	VERIFY(test3_impl<KeyContainer, MappedContainer, Compare, test_input_range>());
	VERIFY(test3_impl<KeyContainer, MappedContainer, Compare, test_forward_range>());
	VERIFY(test3_impl<KeyContainer, MappedContainer, Compare, test_bidirectional_range>());
	VERIFY(test3_impl<KeyContainer, MappedContainer, Compare, test_random_access_range>());
	VERIFY(test3_impl<KeyContainer, MappedContainer, Compare, test_contiguous_range>());
	VERIFY(test3_impl<KeyContainer, MappedContainer, Compare, test_input_sized_range>());
	VERIFY(test3_impl<KeyContainer, MappedContainer, Compare, test_forward_sized_range>());
	VERIFY(test3_impl<KeyContainer, MappedContainer, Compare, test_bidirectional_sized_range>());
	VERIFY(test3_impl<KeyContainer, MappedContainer, Compare, test_random_access_sized_range>());
	VERIFY(test3_impl<KeyContainer, MappedContainer, Compare, test_contiguous_sized_range>());

	return true;
}

template <typename KeyContainer, typename MappedContainer, typename Compare>
FLAT_MAP_TEST_CONSTEXPR bool test4()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using ValueType = typename hamon::flat_map<Key, T>::value_type;

	// (initializer_list)
	{
		hamon::flat_map v
		{
			ValueType{Key{1}, T{10}},
			ValueType{Key{3}, T{20}},
			ValueType{Key{2}, T{30}},
		};
		static_assert(hamon::is_same<decltype(v), hamon::flat_map<Key, T>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (initializer_list, comp)
	{
		Compare const comp;
		hamon::flat_map v
		{
			{
				ValueType{Key{1}, T{10}},
				ValueType{Key{3}, T{20}},
				ValueType{Key{2}, T{30}},
			},
			comp
		};
		static_assert(hamon::is_same<decltype(v), hamon::flat_map<Key, T, Compare>>::value, "");
		VERIFY(check_invariant(v));
	}

	// (sorted_unique, initializer_list)
	{
		hamon::flat_map v
		{
			hamon::sorted_unique,
			{
				ValueType{Key{1}, T{10}},
				ValueType{Key{2}, T{20}},
				ValueType{Key{3}, T{30}},
			}
		};
		static_assert(hamon::is_same<decltype(v), hamon::flat_map<Key, T>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (sorted_unique, initializer_list, comp)
	{
		hamon::flat_map v
		{
			hamon::sorted_unique,
			{
				ValueType{Key{4}, T{10}},
				ValueType{Key{2}, T{20}},
				ValueType{Key{1}, T{30}},
			},
			hamon::greater<>{}
		};
		static_assert(hamon::is_same<decltype(v), hamon::flat_map<Key, T, hamon::greater<>>>::value, "");
		VERIFY(check_invariant(v));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMapTest, CtadTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<hamon::vector<float>, hamon::deque<char>, hamon::greater<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<UseAllocContainer<int>, UseAllocContainer<char>, hamon::less<>>()));

	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<hamon::vector<float>, hamon::deque<char>, hamon::greater<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<UseAllocContainer<int>, UseAllocContainer<char>, hamon::less<>>()));

	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<hamon::vector<float>, hamon::deque<char>, hamon::greater<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<UseAllocContainer<int>, UseAllocContainer<char>, hamon::less<>>()));

	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test4<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test4<hamon::vector<float>, hamon::deque<char>, hamon::greater<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test4<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test4<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test4<UseAllocContainer<int>, UseAllocContainer<char>, hamon::less<>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace ctad_test

}	// namespace hamon_flat_map_test

#endif
