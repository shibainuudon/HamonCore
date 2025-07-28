/**
 *	@file	unit_test_flat_set_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class KeyContainer, class Compare = less<typename KeyContainer::value_type>>
 *	flat_set(KeyContainer, Compare = Compare())
 *	-> flat_set<typename KeyContainer::value_type, Compare, KeyContainer>;
 *
 *	template<class KeyContainer, class Allocator>
 *	flat_set(KeyContainer, Allocator)
 *	-> flat_set<typename KeyContainer::value_type, less<typename KeyContainer::value_type>, KeyContainer>;
 *
 *	template<class KeyContainer, class Compare, class Allocator>
 *	flat_set(KeyContainer, Compare, Allocator)
 *	-> flat_set<typename KeyContainer::value_type, Compare, KeyContainer>;
 *
 *	template<class KeyContainer, class Compare = less<typename KeyContainer::value_type>>
 *	flat_set(sorted_unique_t, KeyContainer, Compare = Compare())
 *	-> flat_set<typename KeyContainer::value_type, Compare, KeyContainer>;
 *
 *	template<class KeyContainer, class Allocator>
 *	flat_set(sorted_unique_t, KeyContainer, Allocator)
 *	-> flat_set<typename KeyContainer::value_type, less<typename KeyContainer::value_type>, KeyContainer>;
 *
 *	template<class KeyContainer, class Compare, class Allocator>
 *	flat_set(sorted_unique_t, KeyContainer, Compare, Allocator)
 *	-> flat_set<typename KeyContainer::value_type, Compare, KeyContainer>;
 *
 *	template<class InputIterator, class Compare = less<iter-value-type<InputIterator>>>
 *	flat_set(InputIterator, InputIterator, Compare = Compare())
 *	-> flat_set<iter-value-type<InputIterator>, Compare>;
 *
 *	template<class InputIterator, class Compare = less<iter-value-type<InputIterator>>>
 *	flat_set(sorted_unique_t, InputIterator, InputIterator, Compare = Compare())
 *	-> flat_set<iter-value-type<InputIterator>, Compare>;
 *
 *	template<ranges::input_range R, class Compare = less<ranges::range_value_t<R>>,
 *		class Allocator = allocator<ranges::range_value_t<R>>>
 *	flat_set(from_range_t, R&&, Compare = Compare(), Allocator = Allocator())
 *	-> flat_set<ranges::range_value_t<R>, Compare,
 *		vector<ranges::range_value_t<R>, alloc-rebind<Allocator, ranges::range_value_t<R>>>>;
 *
 *	template<ranges::input_range R, class Allocator>
 *	flat_set(from_range_t, R&&, Allocator)
 *	-> flat_set<ranges::range_value_t<R>, less<ranges::range_value_t<R>>,
 *		vector<ranges::range_value_t<R>, alloc-rebind<Allocator, ranges::range_value_t<R>>>>;
 *
 *	template<class Key, class Compare = less<Key>>
 *	flat_set(initializer_list<Key>, Compare = Compare())
 *	-> flat_set<Key, Compare>;
 *
 *	template<class Key, class Compare = less<Key>>
 *	flat_set(sorted_unique_t, initializer_list<Key>, Compare = Compare())
 *	-> flat_set<Key, Compare>;
 */

#include <hamon/flat_set/flat_set.hpp>
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
#include "flat_set_test_helper.hpp"

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

namespace hamon_flat_set_test
{

namespace ctad_test
{

#if !defined(HAMON_USE_STD_FLAT_SET)
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename Compare>
FLAT_SET_TEST_CONSTEXPR bool test1()
{
	using Key = typename KeyContainer::value_type;
	using DefaultCompare = typename hamon::flat_set<Key>::key_compare;
	using Alloc = hamon::allocator<char>;

	// (key_cont)
	{
		KeyContainer const key_cont {Key{3}, Key{1}, Key{4}};
		hamon::flat_set v(key_cont);
		static_assert(hamon::is_same<decltype(v), hamon::flat_set<Key, DefaultCompare, KeyContainer>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (key_cont, comp)
	{
		KeyContainer const key_cont {Key{3}, Key{1}, Key{4}};
		Compare const comp;
		hamon::flat_set v{key_cont, comp};
		static_assert(hamon::is_same<decltype(v), hamon::flat_set<Key, Compare, KeyContainer>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (key_cont, alloc)
	{
		KeyContainer const key_cont {Key{3}, Key{1}, Key{4}};
		Alloc const alloc;
		hamon::flat_set v{key_cont, alloc};
		static_assert(hamon::is_same<decltype(v), hamon::flat_set<Key, DefaultCompare, KeyContainer>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (key_cont, comp, alloc)
	{
		KeyContainer const key_cont {Key{3}, Key{1}, Key{4}};
		Compare const comp;
		Alloc const alloc;
		hamon::flat_set v{key_cont, comp, alloc};
		static_assert(hamon::is_same<decltype(v), hamon::flat_set<Key, Compare, KeyContainer>>::value, "");
		VERIFY(check_invariant(v));
	}

	// (sorted_unique, key_cont)
	{
		KeyContainer key_cont {Key{3}, Key{1}, Key{4}};
		hamon::ranges::sort(key_cont, DefaultCompare{});
		hamon::flat_set v{hamon::sorted_unique, key_cont};
		static_assert(hamon::is_same<decltype(v), hamon::flat_set<Key, DefaultCompare, KeyContainer>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (sorted_unique, key_cont, comp)
	{
		KeyContainer key_cont {Key{3}, Key{1}, Key{4}};
		Compare const comp;
		hamon::ranges::sort(key_cont, comp);
		hamon::flat_set v{hamon::sorted_unique, key_cont, comp};
		static_assert(hamon::is_same<decltype(v), hamon::flat_set<Key, Compare, KeyContainer>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (sorted_unique, key_cont, alloc)
	{
		KeyContainer key_cont {Key{3}, Key{1}, Key{4}};
		Alloc const alloc;
		hamon::ranges::sort(key_cont, DefaultCompare{});
		hamon::flat_set v{hamon::sorted_unique, key_cont, alloc};
		static_assert(hamon::is_same<decltype(v), hamon::flat_set<Key, DefaultCompare, KeyContainer>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (sorted_unique, key_cont, comp, alloc)
	{
		KeyContainer key_cont {Key{3}, Key{1}, Key{4}};
		Compare const comp;
		Alloc const alloc;
		hamon::ranges::sort(key_cont, comp);
		hamon::flat_set v{hamon::sorted_unique, key_cont, comp, alloc};
		static_assert(hamon::is_same<decltype(v), hamon::flat_set<Key, Compare, KeyContainer>>::value, "");
		VERIFY(check_invariant(v));
	}

	return true;
}

template <typename KeyContainer, typename Compare, template <typename> class IteratorWrapper>
FLAT_SET_TEST_CONSTEXPR bool test2_impl()
{
	using Key = typename KeyContainer::value_type;
	using ValueType = typename hamon::flat_set<Key>::value_type;
	using InputIterator = IteratorWrapper<ValueType>;

	ValueType a[] =
	{
		Key{1},
		Key{2},
		Key{4},
	};

	// (first, last)
	{
		hamon::flat_set v(InputIterator{a}, InputIterator{a + 3});
		static_assert(hamon::is_same<decltype(v), hamon::flat_set<Key>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (first, last, comp)
	{
		Compare const comp;
		hamon::flat_set v{InputIterator{a}, InputIterator{a + 3}, comp};
		static_assert(hamon::is_same<decltype(v), hamon::flat_set<Key, Compare>>::value, "");
		VERIFY(check_invariant(v));
	}

	// (sorted_unique, first, last)
	{
		hamon::flat_set v{hamon::sorted_unique, InputIterator{a}, InputIterator{a + 3}};
		static_assert(hamon::is_same<decltype(v), hamon::flat_set<Key>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (sorted_unique, first, last, comp)
	{
		hamon::less<> const comp;
		hamon::flat_set v{hamon::sorted_unique, InputIterator{a}, InputIterator{a + 3}, comp};
		static_assert(hamon::is_same<decltype(v), hamon::flat_set<Key, hamon::less<>>>::value, "");
		VERIFY(check_invariant(v));
	}

	return true;
}

template <typename KeyContainer, typename Compare>
FLAT_SET_TEST_CONSTEXPR bool test2()
{
	VERIFY(test2_impl<KeyContainer, Compare, cpp17_input_iterator_wrapper>());
//	VERIFY(test2_impl<KeyContainer, Compare, input_iterator_wrapper>());
	VERIFY(test2_impl<KeyContainer, Compare, forward_iterator_wrapper>());
	VERIFY(test2_impl<KeyContainer, Compare, bidirectional_iterator_wrapper>());
	VERIFY(test2_impl<KeyContainer, Compare, random_access_iterator_wrapper>());
	VERIFY(test2_impl<KeyContainer, Compare, contiguous_iterator_wrapper>());

	return true;
}

template <typename KeyContainer, typename Compare, template <typename> class RangeWrapper>
FLAT_SET_TEST_CONSTEXPR bool test3_impl()
{
	using Key = typename KeyContainer::value_type;
	using ValueType = typename hamon::flat_set<Key>::value_type;
	using Range = RangeWrapper<ValueType>;
	using Alloc = hamon::allocator<char>;

	ValueType a[] =
	{
		Key{1},
		Key{2},
		Key{4},
	};

	// (from_range, rg)
	{
		hamon::flat_set v{hamon::from_range, Range{a}};
		static_assert(hamon::is_same<decltype(v), hamon::flat_set<Key>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (from_range, rg, compare)
	{
		Compare const comp;
		hamon::flat_set v{hamon::from_range, Range{a}, comp};
		static_assert(hamon::is_same<decltype(v), hamon::flat_set<Key, Compare>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (from_range, rg, compare, alloc)
	{
		Compare const comp;
		Alloc const alloc;
		hamon::flat_set v{hamon::from_range, Range{a}, comp, alloc};
		static_assert(hamon::is_same<decltype(v), hamon::flat_set<Key, Compare>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (from_range, rg, alloc)
	{
		Alloc const alloc;
		hamon::flat_set v{hamon::from_range, Range{a}, alloc};
		static_assert(hamon::is_same<decltype(v), hamon::flat_set<Key>>::value, "");
		VERIFY(check_invariant(v));
	}

	return true;
}

template <typename KeyContainer, typename Compare>
FLAT_SET_TEST_CONSTEXPR bool test3()
{
	VERIFY(test3_impl<KeyContainer, Compare, test_input_range>());
	VERIFY(test3_impl<KeyContainer, Compare, test_forward_range>());
	VERIFY(test3_impl<KeyContainer, Compare, test_bidirectional_range>());
	VERIFY(test3_impl<KeyContainer, Compare, test_random_access_range>());
	VERIFY(test3_impl<KeyContainer, Compare, test_contiguous_range>());
	VERIFY(test3_impl<KeyContainer, Compare, test_input_sized_range>());
	VERIFY(test3_impl<KeyContainer, Compare, test_forward_sized_range>());
	VERIFY(test3_impl<KeyContainer, Compare, test_bidirectional_sized_range>());
	VERIFY(test3_impl<KeyContainer, Compare, test_random_access_sized_range>());
	VERIFY(test3_impl<KeyContainer, Compare, test_contiguous_sized_range>());

	return true;
}

template <typename KeyContainer, typename Compare>
FLAT_SET_TEST_CONSTEXPR bool test4()
{
	using Key = typename KeyContainer::value_type;

	// (initializer_list)
	{
		hamon::flat_set v
		{
			Key{1},
			Key{3},
			Key{2},
		};
		static_assert(hamon::is_same<decltype(v), hamon::flat_set<Key>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (initializer_list, comp)
	{
		Compare const comp;
		hamon::flat_set v
		{
			{
				Key{1},
				Key{3},
				Key{2},
			},
			comp
		};
		static_assert(hamon::is_same<decltype(v), hamon::flat_set<Key, Compare>>::value, "");
		VERIFY(check_invariant(v));
	}

	// (sorted_unique, initializer_list)
	{
		hamon::flat_set v
		{
			hamon::sorted_unique,
			{
				Key{1},
				Key{2},
				Key{3},
			}
		};
		static_assert(hamon::is_same<decltype(v), hamon::flat_set<Key>>::value, "");
		VERIFY(check_invariant(v));
	}
	// (sorted_unique, initializer_list, comp)
	{
		hamon::flat_set v
		{
			hamon::sorted_unique,
			{
				Key{4},
				Key{2},
				Key{1},
			},
			hamon::greater<>{}
		};
		static_assert(hamon::is_same<decltype(v), hamon::flat_set<Key, hamon::greater<>>>::value, "");
		VERIFY(check_invariant(v));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatSetTest, CtadTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<hamon::deque<double>, hamon::greater<double>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<UseAllocContainer<int>, hamon::less<>>()));

	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test2<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test2<hamon::deque<double>, hamon::greater<double>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test2<UseAllocContainer<int>, hamon::less<>>()));

	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test3<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test3<hamon::deque<double>, hamon::greater<double>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test3<UseAllocContainer<int>, hamon::less<>>()));

	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test4<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test4<hamon::deque<double>, hamon::greater<double>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test4<UseAllocContainer<int>, hamon::less<>>()));
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace ctad_test

}	// namespace hamon_flat_set_test

#endif
