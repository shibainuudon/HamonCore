/**
 *	@file	unit_test_unordered_multiset_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class InputIterator,
 *		class Hash = hash<iter-value-type<InputIterator>>,
 *		class Pred = equal_to<iter-value-type<InputIterator>>,
 *		class Allocator = allocator<iter-value-type<InputIterator>>>
 *	unordered_multiset(InputIterator, InputIterator, see below::size_type = see below,
 *		Hash = Hash(), Pred = Pred(), Allocator = Allocator())
 *	-> unordered_multiset<iter-value-type<InputIterator>, Hash, Pred, Allocator>;
 *
 *	template<class InputIterator, class Allocator>
 *	unordered_multiset(InputIterator, InputIterator, typename see below::size_type, Allocator)
 *	-> unordered_multiset<iter-value-type<InputIterator>,
 *		hash<iter-value-type<InputIterator>>,
 *		equal_to<iter-value-type<InputIterator>>,
 *		Allocator>;
 *
 *	template<class InputIterator, class Hash, class Allocator>
 *	unordered_multiset(InputIterator, InputIterator, typename see below::size_type,
 *		Hash, Allocator)
 *	-> unordered_multiset<iter-value-type<InputIterator>, Hash,
 *		equal_to<iter-value-type<InputIterator>>,
 *		Allocator>;
 *
 *	template<ranges::input_range R,
 *		class Hash = hash<ranges::range_value_t<R>>,
 *		class Pred = equal_to<ranges::range_value_t<R>>,
 *		class Allocator = allocator<ranges::range_value_t<R>>>
 *	unordered_multiset(from_range_t, R&&, typename see below::size_type = see below,
 *		Hash = Hash(), Pred = Pred(), Allocator = Allocator())
 *	-> unordered_multiset<ranges::range_value_t<R>, Hash, Pred, Allocator>;
 *
 *	template<ranges::input_range R, class Allocator>
 *	unordered_multiset(from_range_t, R&&, typename see below::size_type, Allocator)
 *	-> unordered_multiset<ranges::range_value_t<R>, hash<ranges::range_value_t<R>>,
 *		equal_to<ranges::range_value_t<R>>, Allocator>;
 *
 *	template<ranges::input_range R, class Allocator>
 *	unordered_multiset(from_range_t, R&&, Allocator)
 *	-> unordered_multiset<ranges::range_value_t<R>, hash<ranges::range_value_t<R>>,
 *		equal_to<ranges::range_value_t<R>>, Allocator>;
 *
 *	template<ranges::input_range R, class Hash, class Allocator>
 *	unordered_multiset(from_range_t, R&&, typename see below::size_type, Hash, Allocator)
 *	-> unordered_multiset<ranges::range_value_t<R>, Hash, equal_to<ranges::range_value_t<R>>, Allocator>;
 *
 *	template<class T, class Hash = hash<T>,
 *		class Pred = equal_to<T>, class Allocator = allocator<T>>
 *	unordered_multiset(initializer_list<T>, typename see below::size_type = see below,
 *		Hash = Hash(), Pred = Pred(), Allocator = Allocator())
 *	-> unordered_multiset<T, Hash, Pred, Allocator>;
 *
 *	template<class T, class Allocator>
 *	unordered_multiset(initializer_list<T>, typename see below::size_type, Allocator)
 *	-> unordered_multiset<T, hash<T>, equal_to<T>, Allocator>;
 *
 *	template<class T, class Hash, class Allocator>
 *	unordered_multiset(initializer_list<T>, typename see below::size_type, Hash, Allocator)
 *	-> unordered_multiset<T, Hash, equal_to<T>, Allocator>;
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "ranges_test.hpp"
#include "unordered_multiset_test_helper.hpp"

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

namespace hamon_unordered_multiset_test
{

namespace ctad_test
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
UNORDERED_MULTISET_TEST_CONSTEXPR bool test1_impl()
{
	using Set = hamon::unordered_multiset<Key>;
	using ValueType = typename Set::value_type;
	using Iterator = IteratorWrapper<ValueType>;

	ValueType a[] =
	{
		Key{2}, Key{3}, Key{1}, Key{1}, Key{2}, Key{3},
	};

	// (f, l)
	{
		hamon::unordered_multiset v(Iterator{a}, Iterator{a + 6});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key>>::value, "");
	}
	// (f, l, n)
	{
		hamon::unordered_multiset v(Iterator{a}, Iterator{a + 6}, 8);
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key>>::value, "");
	}
	// (f, l, n, hf)
	{
		using Hash = TransparentHash;
		hamon::unordered_multiset v(Iterator{a}, Iterator{a + 6}, 8, Hash{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key, Hash>>::value, "");
	}
	// (f, l, n, hf, eql)
	{
		using Hash = TransparentHash;
		using Pred = hamon::equal_to<>;
		hamon::unordered_multiset v(Iterator{a}, Iterator{a + 6}, 8, Hash{}, Pred{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key, Hash, Pred>>::value, "");
	}
	// (f, l, n, hf, eql, a)
	{
		using Hash = TransparentHash;
		using Pred = hamon::equal_to<>;
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multiset v(Iterator{a}, Iterator{a + 6}, 8, Hash{}, Pred{}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key, Hash, Pred, Allocator>>::value, "");
	}
	// (f, l, n, a)
	{
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multiset v(Iterator{a}, Iterator{a + 6}, 8, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key, typename Set::hasher, typename Set::key_equal, Allocator>>::value, "");
	}
	// (f, l, n, hf, a)
	{
		using Hash = TransparentHash;
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multiset v(Iterator{a}, Iterator{a + 6}, 8, Hash{}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key, Hash, typename Set::key_equal, Allocator>>::value, "");
	}
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)	// TODO(LWG 2713)
	// (f, l, a)
	{
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multiset v(Iterator{a}, Iterator{a + 6}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key, typename Set::hasher, typename Set::key_equal, Allocator>>::value, "");
	}
#endif

	return true;
}

template <typename Key>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test1()
{
	VERIFY(test1_impl<Key, cpp17_input_iterator_wrapper>());
//	VERIFY(test1_impl<Key, input_iterator_wrapper>());
	VERIFY(test1_impl<Key, forward_iterator_wrapper>());
	VERIFY(test1_impl<Key, bidirectional_iterator_wrapper>());
	VERIFY(test1_impl<Key, random_access_iterator_wrapper>());
	VERIFY(test1_impl<Key, contiguous_iterator_wrapper>());
	return true;
}

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))

template <typename Key, template <typename> class RangeWrapper>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test2_impl()
{
	using Set = hamon::unordered_multiset<Key>;
	using ValueType = typename Set::value_type;
	using Range = RangeWrapper<ValueType>;

	ValueType a[] =
	{
		Key{3}, Key{1}, Key{4}, Key{1}, Key{5}, Key{9}, Key{2},
	};
	Range r(a);

	// (from_range, rg)
	{
		hamon::unordered_multiset v(hamon::from_range, r);
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key>>::value, "");
	}
	// (from_range, rg, n)
	{
		hamon::unordered_multiset v(hamon::from_range, r, 8);
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key>>::value, "");
	}
	// (from_range, rg, n, hf)
	{
		using Hash = TransparentHash;
		hamon::unordered_multiset v(hamon::from_range, r, 8, Hash{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key, Hash>>::value, "");
	}
	// (from_range, rg, n, hf, eql)
	{
		using Hash = TransparentHash;
		using Pred = hamon::equal_to<>;
		hamon::unordered_multiset v(hamon::from_range, r, 8, Hash{}, Pred{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key, Hash, Pred>>::value, "");
	}
	// (from_range, rg, n, hf, eql, a)
	{
		using Hash = TransparentHash;
		using Pred = hamon::equal_to<>;
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multiset v(hamon::from_range, r, 8, Hash{}, Pred{}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key, Hash, Pred, Allocator>>::value, "");
	}
	// (from_range, rg, n, a)
	{
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multiset v(hamon::from_range, r, 8, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key, typename Set::hasher, typename Set::key_equal, Allocator>>::value, "");
	}
	// (from_range, rg, n, hf, a)
	{
		using Hash = TransparentHash;
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multiset v(hamon::from_range, r, 8, Hash{}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key, Hash, typename Set::key_equal, Allocator>>::value, "");
	}
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)	// TODO(LWG 2713)
	// (from_range, rg, a)
	{
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multiset v(hamon::from_range, r, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key, typename Set::hasher, typename Set::key_equal, Allocator>>::value, "");
	}
#endif

	return true;
}

template <typename Key>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test2()
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
UNORDERED_MULTISET_TEST_CONSTEXPR bool test3()
{
	using Set = hamon::unordered_multiset<Key>;
	using ValueType = typename Set::value_type;

	// (il)
	{
		hamon::unordered_multiset v({Key{1}, Key{2}, Key{3}});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key>>::value, "");
	}
	// (il, n)
	{
		hamon::unordered_multiset v({Key{1}, Key{2}, Key{3}}, 8);
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key>>::value, "");
	}
	// (il, n, hf)
	{
		using Hash = TransparentHash;
		hamon::unordered_multiset v({Key{1}, Key{2}, Key{3}}, 8, Hash{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key, Hash>>::value, "");
	}
	// (il, n, hf, eql)
	{
		using Hash = TransparentHash;
		using Pred = hamon::equal_to<>;
		hamon::unordered_multiset v({Key{1}, Key{2}, Key{3}}, 8, Hash{}, Pred{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key, Hash, Pred>>::value, "");
	}
	// (il, n, hf, eql, a)
	{
		using Hash = TransparentHash;
		using Pred = hamon::equal_to<>;
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multiset v({Key{1}, Key{2}, Key{3}}, 8, Hash{}, Pred{}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key, Hash, Pred, Allocator>>::value, "");
	}
	// (il, n, a)
	{
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multiset v({Key{1}, Key{2}, Key{3}}, 8, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key, typename Set::hasher, typename Set::key_equal, Allocator>>::value, "");
	}
	// (il, n, hf, a)
	{
		using Hash = TransparentHash;
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multiset v({Key{1}, Key{2}, Key{3}}, 8, Hash{}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key, Hash, typename Set::key_equal, Allocator>>::value, "");
	}
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)	// TODO(LWG 2713)
	// (il, a)
	{
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multiset v({Key{1}, Key{2}, Key{3}}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multiset<Key, typename Set::hasher, typename Set::key_equal, Allocator>>::value, "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, CtadTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<float>()));
#endif

	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test3<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test3<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test3<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace ctad_test

}	// namespace hamon_unordered_multiset_test

#endif
