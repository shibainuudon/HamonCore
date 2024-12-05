/**
 *	@file	unit_test_multiset_ctor_range.cpp
 *
 *	@brief	rangeを引数に取るコンストラクタのテスト
 *
 *	template<container-compatible-range<value_type> R>
 *	multiset(from_range_t, R&& rg,
 *		const Compare& comp = Compare(), const Allocator& = Allocator());
 *
 *	template<container-compatible-range<value_type> R>
 *	multiset(from_range_t, R&& rg, const Allocator& a))
 *		: multiset(from_range, std::forward<R>(rg), Compare(), a) { }
 */

#include <hamon/set/multiset.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

#if !defined(HAMON_USE_STD_MULTISET) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))

namespace hamon_multiset_test
{

namespace ctor_range_test
{

#if !defined(HAMON_USE_STD_MULTISET)
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR              /**/
#endif

template <typename T>
struct MyAllocator
{
	using value_type = T;

	int id;

	HAMON_CXX11_CONSTEXPR
	MyAllocator() : id(0) {}

	HAMON_CXX11_CONSTEXPR
	MyAllocator(int i) : id(i) {}

	template <typename U>
	HAMON_CXX11_CONSTEXPR
	MyAllocator(MyAllocator<U> const& a) : id(a.id) {}

	HAMON_CXX20_CONSTEXPR
	T* allocate(hamon::size_t n)
	{
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}

	HAMON_CXX20_CONSTEXPR
	void deallocate(T* p, hamon::size_t n)
	{
		// [allocator.members]/11
		::operator delete(p);
		(void)n;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(MyAllocator const& rhs) const
	{
		return id == rhs.id;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator!=(MyAllocator const& rhs) const
	{
		return id != rhs.id;
	}
};

struct MyLess
{
	int id;

	HAMON_CXX11_CONSTEXPR
	MyLess() : id(0) {}

	HAMON_CXX11_CONSTEXPR
	MyLess(int i) : id(i) {}

	template <typename T>
	HAMON_CXX11_CONSTEXPR
	bool operator()(T const& x, T const& y) const
	{
		return x < y;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(MyLess const& rhs) const
	{
		return id == rhs.id;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, template <typename> class RangeWrapper, typename Compare, typename Allocator>
MULTISET_TEST_CONSTEXPR bool test_imp2(Compare const& comp, Allocator const& alloc)
{
	using Set = hamon::multiset<Key, Compare, Allocator>;
	using ValueType = typename Set::value_type;
	using Range = RangeWrapper<ValueType>;

	static_assert(!hamon::is_constructible<Set, Range>::value, "");
	static_assert(!hamon::is_constructible<Set, Range, Allocator const&>::value, "");
	static_assert(!hamon::is_constructible<Set, Range, Compare const&>::value, "");
	static_assert(!hamon::is_constructible<Set, Range, Compare const&, Allocator const&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::from_range_t, Range>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::from_range_t, Range, Allocator const&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::from_range_t, Range, Compare const&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::from_range_t, Range, Compare const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::from_range_t, Range>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::from_range_t, Range, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::from_range_t, Range, Compare const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::from_range_t, Range, Compare const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::from_range_t, Range>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::from_range_t, Range, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::from_range_t, Range, Compare const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::from_range_t, Range, Compare const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::from_range_t, Range>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::from_range_t, Range, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::from_range_t, Range, Compare const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::from_range_t, Range, Compare const&, Allocator const&>::value, "");

	{
		ValueType a[] = {Key{3},Key{1},Key{4},Key{1},Key{5}};
		Range r(a);
		Set v(hamon::from_range, r);
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == Compare{});
		VERIFY(v.value_comp() == Compare{});
		VERIFY(v.get_allocator() == Allocator{});
		{
			auto it = v.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{4});
			VERIFY(*it++ == Key{5});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == Key{5});
			VERIFY(*it++ == Key{4});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{1});
			VERIFY(it == v.rend());
		}
	}
	{
		ValueType a[] = {Key{5},Key{3},Key{1},Key{4},Key{1},Key{5}};
		Range r(a);
		Set v(hamon::from_range, r, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == Compare{});
		VERIFY(v.value_comp() == Compare{});
		VERIFY(v.get_allocator() == alloc);
		{
			auto it = v.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{4});
			VERIFY(*it++ == Key{5});
			VERIFY(*it++ == Key{5});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == Key{5});
			VERIFY(*it++ == Key{5});
			VERIFY(*it++ == Key{4});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{1});
			VERIFY(it == v.rend());
		}
	}
	{
		ValueType a[] = {Key{5},Key{3},Key{5},Key{1},Key{4},Key{1},Key{5}};
		Range r(a);
		Set v(hamon::from_range, r, comp);
		VERIFY(!v.empty());
		VERIFY(v.size() == 7);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.value_comp() == comp);
		VERIFY(v.get_allocator() == Allocator{});
		{
			auto it = v.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{4});
			VERIFY(*it++ == Key{5});
			VERIFY(*it++ == Key{5});
			VERIFY(*it++ == Key{5});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == Key{5});
			VERIFY(*it++ == Key{5});
			VERIFY(*it++ == Key{5});
			VERIFY(*it++ == Key{4});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{1});
			VERIFY(it == v.rend());
		}
	}
	{
		ValueType a[] = {Key{5},Key{3},Key{4},Key{5},Key{1},Key{4},Key{1},Key{5}};
		Range r(a);
		Set v(hamon::from_range, r, comp, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 8);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.value_comp() == comp);
		VERIFY(v.get_allocator() == alloc);
		{
			auto it = v.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{4});
			VERIFY(*it++ == Key{4});
			VERIFY(*it++ == Key{5});
			VERIFY(*it++ == Key{5});
			VERIFY(*it++ == Key{5});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == Key{5});
			VERIFY(*it++ == Key{5});
			VERIFY(*it++ == Key{5});
			VERIFY(*it++ == Key{4});
			VERIFY(*it++ == Key{4});
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{1});
			VERIFY(it == v.rend());
		}
	}

	return true;
}

template <typename Key, typename Compare, typename Allocator>
MULTISET_TEST_CONSTEXPR bool test_impl(Compare const& comp, Allocator const& alloc)
{
	return
		test_imp2<Key, test_input_range>(comp, alloc) &&
		test_imp2<Key, test_forward_range>(comp, alloc) &&
		test_imp2<Key, test_bidirectional_range>(comp, alloc) &&
		test_imp2<Key, test_random_access_range>(comp, alloc) &&
		test_imp2<Key, test_contiguous_range>(comp, alloc) &&
		test_imp2<Key, test_input_sized_range>(comp, alloc) &&
		test_imp2<Key, test_forward_sized_range>(comp, alloc) &&
		test_imp2<Key, test_bidirectional_sized_range>(comp, alloc) &&
		test_imp2<Key, test_random_access_sized_range>(comp, alloc) &&
		test_imp2<Key, test_contiguous_sized_range>(comp, alloc);
}

template <typename Key>
MULTISET_TEST_CONSTEXPR bool test1()
{
	MyLess comp{13};
	hamon::allocator<Key> alloc;
	VERIFY(test_impl<Key>(comp, alloc));
	return true;
}

template <typename Key>
MULTISET_TEST_CONSTEXPR bool test2()
{
	MyLess comp{14};
	MyAllocator<Key> alloc{42};
	VERIFY(test_impl<Key>(comp, alloc));
	return true;
}

#undef VERIFY

GTEST_TEST(MultisetTest, CtorRangeTest)
{
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace ctor_range_test

}	// namespace hamon_multiset_test

#endif
