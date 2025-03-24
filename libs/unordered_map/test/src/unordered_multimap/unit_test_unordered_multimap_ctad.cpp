/**
 *	@file	unit_test_unordered_multimap_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class InputIterator,
 *		class Hash = hash<iter-key-type<InputIterator>>,
 *		class Pred = equal_to<iter-key-type<InputIterator>>,
 *		class Allocator = allocator<iter-to-alloc-type<InputIterator>>>
 *	unordered_multimap(InputIterator, InputIterator, typename see below::size_type = see below,
 *		Hash = Hash(), Pred = Pred(), Allocator = Allocator())
 *	-> unordered_multimap<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>, Hash, Pred, Allocator>;
 *
 *	template<ranges::input_range R, class Hash = hash<range-key-type<R>>,
 *		class Pred = equal_to<range-key-type<R>>,
 *		class Allocator = allocator<range-to-alloc-type<R>>>
 *	unordered_multimap(from_range_t, R&&, typename see below::size_type = see below,
 *		Hash = Hash(), Pred = Pred(), Allocator = Allocator())
 *	-> unordered_multimap<range-key-type<R>, range-mapped-type<R>, Hash, Pred, Allocator>;
 *
 *	template<class Key, class T, class Hash = hash<Key>,
 *		class Pred = equal_to<Key>, class Allocator = allocator<pair<const Key, T>>>
 *	unordered_multimap(initializer_list<pair<Key, T>>,
 *		typename see below::size_type = see below, Hash = Hash(),
 *		Pred = Pred(), Allocator = Allocator())
 *	-> unordered_multimap<Key, T, Hash, Pred, Allocator>;
 *
 *	template<class InputIterator, class Allocator>
 *	unordered_multimap(InputIterator, InputIterator, typename see below::size_type, Allocator)
 *	-> unordered_multimap<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>,
 *		hash<iter-key-type<InputIterator>>,
 *		equal_to<iter-key-type<InputIterator>>, Allocator>;
 *
 *	template<class InputIterator, class Allocator>
 *	unordered_multimap(InputIterator, InputIterator, Allocator)
 *	-> unordered_multimap<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>,
 *		hash<iter-key-type<InputIterator>>,
 *		equal_to<iter-key-type<InputIterator>>, Allocator>;
 *
 *	template<class InputIterator, class Hash, class Allocator>
 *	unordered_multimap(InputIterator, InputIterator, typename see below::size_type, Hash, Allocator)
 *	-> unordered_multimap<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>, Hash,
 *		equal_to<iter-key-type<InputIterator>>, Allocator>;
 *
 *	template<ranges::input_range R, class Allocator>
 *	unordered_multimap(from_range_t, R&&, typename see below::size_type, Allocator)
 *	-> unordered_multimap<range-key-type<R>, range-mapped-type<R>, hash<range-key-type<R>>,
 *		equal_to<range-key-type<R>>, Allocator>;
 *
 *	template<ranges::input_range R, class Allocator>
 *	unordered_multimap(from_range_t, R&&, Allocator)
 *	-> unordered_multimap<range-key-type<R>, range-mapped-type<R>, hash<range-key-type<R>>,
 *		equal_to<range-key-type<R>>, Allocator>;
 *
 *	template<ranges::input_range R, class Hash, class Allocator>
 *	unordered_multimap(from_range_t, R&&, typename see below::size_type, Hash, Allocator)
 *	-> unordered_multimap<range-key-type<R>, range-mapped-type<R>, Hash,
 *		equal_to<range-key-type<R>>, Allocator>;
 *
 *	template<class Key, class T, class Allocator>
 *	unordered_multimap(initializer_list<pair<Key, T>>, typename see below::size_type, Allocator)
 *	-> unordered_multimap<Key, T, hash<Key>, equal_to<Key>, Allocator>;
 *
 *	template<class Key, class T, class Allocator>
 *	unordered_multimap(initializer_list<pair<Key, T>>, Allocator)
 *	-> unordered_multimap<Key, T, hash<Key>, equal_to<Key>, Allocator>;
 *
 *	template<class Key, class T, class Hash, class Allocator>
 *	unordered_multimap(initializer_list<pair<Key, T>>, typename see below::size_type, Hash, Allocator)
 *	-> unordered_multimap<Key, T, Hash, equal_to<Key>, Allocator>;
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "ranges_test.hpp"
#include "unordered_multimap_test_helper.hpp"

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

namespace hamon_unordered_multimap_test
{

namespace ctad_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T, template <typename> class IteratorWrapper>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test1_impl()
{
	using Map = hamon::unordered_multimap<Key, T>;
	using ValueType = typename Map::value_type;
	using Iterator = IteratorWrapper<ValueType>;

	ValueType a[] =
	{
		{ Key{2}, T{10} },
		{ Key{3}, T{20} },
		{ Key{1}, T{30} },
		{ Key{1}, T{40} },
		{ Key{2}, T{50} },
		{ Key{3}, T{60} },
	};

	// (f, l)
	{
		hamon::unordered_multimap v(Iterator{a}, Iterator{a + 6});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T>>::value, "");
	}
	// (f, l, n)
	{
		hamon::unordered_multimap v(Iterator{a}, Iterator{a + 6}, 8);
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T>>::value, "");
	}
	// (f, l, n, hf)
	{
		using Hash = TransparentHash;
		hamon::unordered_multimap v(Iterator{a}, Iterator{a + 6}, 8, Hash{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T, Hash>>::value, "");
	}
	// (f, l, n, hf, eql)
	{
		using Hash = TransparentHash;
		using Pred = hamon::equal_to<>;
		hamon::unordered_multimap v(Iterator{a}, Iterator{a + 6}, 8, Hash{}, Pred{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T, Hash, Pred>>::value, "");
	}
	// (f, l, n, hf, eql, a)
	{
		using Hash = TransparentHash;
		using Pred = hamon::equal_to<>;
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multimap v(Iterator{a}, Iterator{a + 6}, 8, Hash{}, Pred{}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T, Hash, Pred, Allocator>>::value, "");
	}
	// (f, l, n, a)
	{
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multimap v(Iterator{a}, Iterator{a + 6}, 8, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T, typename Map::hasher, typename Map::key_equal, Allocator>>::value, "");
	}
	// (f, l, n, hf, a)
	{
		using Hash = TransparentHash;
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multimap v(Iterator{a}, Iterator{a + 6}, 8, Hash{}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T, Hash, typename Map::key_equal, Allocator>>::value, "");
	}
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)	// TODO(LWG 2713)
	// (f, l, a)
	{
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multimap v(Iterator{a}, Iterator{a + 6}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T, typename Map::hasher, typename Map::key_equal, Allocator>>::value, "");
	}
#endif

	return true;
}

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test1()
{
	VERIFY(test1_impl<Key, T, cpp17_input_iterator_wrapper>());
//	VERIFY(test1_impl<Key, T, input_iterator_wrapper>());
	VERIFY(test1_impl<Key, T, forward_iterator_wrapper>());
	VERIFY(test1_impl<Key, T, bidirectional_iterator_wrapper>());
	VERIFY(test1_impl<Key, T, random_access_iterator_wrapper>());
	VERIFY(test1_impl<Key, T, contiguous_iterator_wrapper>());
	return true;
}

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))

template <typename Key, typename T, template <typename> class RangeWrapper>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test2_impl()
{
	using Map = hamon::unordered_multimap<Key, T>;
	using ValueType = typename Map::value_type;
	using Range = RangeWrapper<ValueType>;

	ValueType a[] =
	{
		{ Key{2}, T{10} },
		{ Key{3}, T{20} },
		{ Key{1}, T{30} },
		{ Key{1}, T{40} },
		{ Key{2}, T{50} },
		{ Key{3}, T{60} },
	};
	Range r(a);

	// (from_range, rg)
	{
		hamon::unordered_multimap v(hamon::from_range, r);
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T>>::value, "");
	}
	// (from_range, rg, n)
	{
		hamon::unordered_multimap v(hamon::from_range, r, 8);
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T>>::value, "");
	}
	// (from_range, rg, n, hf)
	{
		using Hash = TransparentHash;
		hamon::unordered_multimap v(hamon::from_range, r, 8, Hash{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T, Hash>>::value, "");
	}
	// (from_range, rg, n, hf, eql)
	{
		using Hash = TransparentHash;
		using Pred = hamon::equal_to<>;
		hamon::unordered_multimap v(hamon::from_range, r, 8, Hash{}, Pred{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T, Hash, Pred>>::value, "");
	}
	// (from_range, rg, n, hf, eql, a)
	{
		using Hash = TransparentHash;
		using Pred = hamon::equal_to<>;
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multimap v(hamon::from_range, r, 8, Hash{}, Pred{}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T, Hash, Pred, Allocator>>::value, "");
	}
	// (from_range, rg, n, a)
	{
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multimap v(hamon::from_range, r, 8, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T, typename Map::hasher, typename Map::key_equal, Allocator>>::value, "");
	}
	// (from_range, rg, n, hf, a)
	{
		using Hash = TransparentHash;
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multimap v(hamon::from_range, r, 8, Hash{}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T, Hash, typename Map::key_equal, Allocator>>::value, "");
	}
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)	// TODO(LWG 2713)
	// (from_range, rg, a)
	{
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multimap v(hamon::from_range, r, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T, typename Map::hasher, typename Map::key_equal, Allocator>>::value, "");
	}
#endif

	return true;
}

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test2()
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
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test3()
{
	using Map = hamon::unordered_multimap<Key, T>;
	using ValueType = typename Map::value_type;
#if defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	using PairType = std::pair<Key, T>;
#else
	using PairType = hamon::pair<Key, T>;
#endif

	// (il)
	{
		hamon::unordered_multimap v({
			PairType{ Key{2}, T{10} },
			PairType{ Key{3}, T{20} },
			PairType{ Key{1}, T{30} },
		});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T>>::value, "");
	}
	// (il, n)
	{
		hamon::unordered_multimap v({
			PairType{ Key{2}, T{10} },
			PairType{ Key{3}, T{20} },
			PairType{ Key{1}, T{30} },
		},8);
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T>>::value, "");
	}
	// (il, n, hf)
	{
		using Hash = TransparentHash;
		hamon::unordered_multimap v({
			PairType{ Key{2}, T{10} },
			PairType{ Key{3}, T{20} },
			PairType{ Key{1}, T{30} },
		}, 8, Hash{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T, Hash>>::value, "");
	}
	// (il, n, hf, eql)
	{
		using Hash = TransparentHash;
		using Pred = hamon::equal_to<>;
		hamon::unordered_multimap v({
			PairType{ Key{2}, T{10} },
			PairType{ Key{3}, T{20} },
			PairType{ Key{1}, T{30} },
		}, 8, Hash{}, Pred{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T, Hash, Pred>>::value, "");
	}
	// (il, n, hf, eql, a)
	{
		using Hash = TransparentHash;
		using Pred = hamon::equal_to<>;
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multimap v({
			PairType{ Key{2}, T{10} },
			PairType{ Key{3}, T{20} },
			PairType{ Key{1}, T{30} },
		}, 8, Hash{}, Pred{}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T, Hash, Pred, Allocator>>::value, "");
	}
	// (il, n, a)
	{
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multimap v({
			PairType{ Key{2}, T{10} },
			PairType{ Key{3}, T{20} },
			PairType{ Key{1}, T{30} },
		}, 8, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T, typename Map::hasher, typename Map::key_equal, Allocator>>::value, "");
	}
	// (il, n, hf, a)
	{
		using Hash = TransparentHash;
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multimap v({
			PairType{ Key{2}, T{10} },
			PairType{ Key{3}, T{20} },
			PairType{ Key{1}, T{30} },
		}, 8, Hash{}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T, Hash, typename Map::key_equal, Allocator>>::value, "");
	}
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)	// TODO(LWG 2713)
	// (il, a)
	{
		using Allocator = hamon::allocator<ValueType>;
		hamon::unordered_multimap v({
			PairType{ Key{2}, T{10} },
			PairType{ Key{3}, T{20} },
			PairType{ Key{1}, T{30} },
		}, Allocator{});
		static_assert(hamon::is_same<decltype(v), hamon::unordered_multimap<Key, T, typename Map::hasher, typename Map::key_equal, Allocator>>::value, "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, CtadTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, float>()));
#endif

	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<float, float>()));
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace ctad_test

}	// namespace hamon_unordered_multimap_test

#endif
