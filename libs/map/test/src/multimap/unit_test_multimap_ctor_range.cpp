/**
 *	@file	unit_test_multimap_ctor_range.cpp
 *
 *	@brief	rangeを引数に取るコンストラクタのテスト
 *
 *	template<container-compatible-range<value_type> R>
 *	multimap(from_range_t, R&& rg,
 *		const Compare& comp = Compare(), const Allocator& = Allocator());
 *
 *	template<container-compatible-range<value_type> R>
 *	multimap(from_range_t, R&& rg, const Allocator& a))
 *		: multimap(from_range, std::forward<R>(rg), Compare(), a) { }
 */

#include <hamon/map/multimap.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

#if !defined(HAMON_USE_STD_MULTIMAP) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))

namespace hamon_multimap_test
{

namespace ctor_range_test
{

#if !defined(HAMON_USE_STD_MULTIMAP)
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR              /**/
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

template <typename Key, typename T, template <typename> class RangeWrapper, typename Compare, typename Allocator>
MULTIMAP_TEST_CONSTEXPR bool test_imp2(Compare const& comp, Allocator const& alloc)
{
	using Map = hamon::multimap<Key, T, Compare, Allocator>;
	using ValueType = typename Map::value_type;
	using Range = RangeWrapper<ValueType>;

	static_assert(!hamon::is_constructible<Map, Range>::value, "");
	static_assert(!hamon::is_constructible<Map, Range, Allocator const&>::value, "");
	static_assert(!hamon::is_constructible<Map, Range, Compare const&>::value, "");
	static_assert(!hamon::is_constructible<Map, Range, Compare const&, Allocator const&>::value, "");
	static_assert( hamon::is_constructible<Map, hamon::from_range_t, Range>::value, "");
	static_assert( hamon::is_constructible<Map, hamon::from_range_t, Range, Allocator const&>::value, "");
	static_assert( hamon::is_constructible<Map, hamon::from_range_t, Range, Compare const&>::value, "");
	static_assert( hamon::is_constructible<Map, hamon::from_range_t, Range, Compare const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, hamon::from_range_t, Range>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, hamon::from_range_t, Range, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, hamon::from_range_t, Range, Compare const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, hamon::from_range_t, Range, Compare const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, hamon::from_range_t, Range>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, hamon::from_range_t, Range, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, hamon::from_range_t, Range, Compare const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, hamon::from_range_t, Range, Compare const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, hamon::from_range_t, Range>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, hamon::from_range_t, Range, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, hamon::from_range_t, Range, Compare const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, hamon::from_range_t, Range, Compare const&, Allocator const&>::value, "");

	{
		ValueType a[] =
		{
			{ Key{3}, T{10} },
			{ Key{1}, T{20} },
			{ Key{4}, T{30} },
			{ Key{1}, T{40} },
			{ Key{5}, T{50} },
		};
		Range r(a);
		Map v(hamon::from_range, r);
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == Compare{});
		VERIFY(v.get_allocator() == Allocator{});
		{
			auto it = v.begin();
			VERIFY(*it++ == ValueType{ Key{1}, T{20} });
			VERIFY(*it++ == ValueType{ Key{1}, T{40} });
			VERIFY(*it++ == ValueType{ Key{3}, T{10} });
			VERIFY(*it++ == ValueType{ Key{4}, T{30} });
			VERIFY(*it++ == ValueType{ Key{5}, T{50} });
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == ValueType{ Key{5}, T{50} });
			VERIFY(*it++ == ValueType{ Key{4}, T{30} });
			VERIFY(*it++ == ValueType{ Key{3}, T{10} });
			VERIFY(*it++ == ValueType{ Key{1}, T{40} });
			VERIFY(*it++ == ValueType{ Key{1}, T{20} });
			VERIFY(it == v.rend());
		}
	}
	{
		ValueType a[] =
		{
			{ Key{5}, T{10} },
			{ Key{3}, T{20} },
			{ Key{1}, T{30} },
			{ Key{4}, T{40} },
			{ Key{1}, T{50} },
			{ Key{5}, T{60} },
		};
		Range r(a);
		Map v(hamon::from_range, r, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == Compare{});
		VERIFY(v.get_allocator() == alloc);
		{
			auto it = v.begin();
			VERIFY(*it++ == ValueType{ Key{1}, T{30} });
			VERIFY(*it++ == ValueType{ Key{1}, T{50} });
			VERIFY(*it++ == ValueType{ Key{3}, T{20} });
			VERIFY(*it++ == ValueType{ Key{4}, T{40} });
			VERIFY(*it++ == ValueType{ Key{5}, T{10} });
			VERIFY(*it++ == ValueType{ Key{5}, T{60} });
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == ValueType{ Key{5}, T{60} });
			VERIFY(*it++ == ValueType{ Key{5}, T{10} });
			VERIFY(*it++ == ValueType{ Key{4}, T{40} });
			VERIFY(*it++ == ValueType{ Key{3}, T{20} });
			VERIFY(*it++ == ValueType{ Key{1}, T{50} });
			VERIFY(*it++ == ValueType{ Key{1}, T{30} });
			VERIFY(it == v.rend());
		}
	}
	{
		ValueType a[] =
		{
			{ Key{5}, T{10} },
			{ Key{3}, T{20} },
			{ Key{5}, T{30} },
			{ Key{1}, T{40} },
			{ Key{4}, T{50} },
			{ Key{1}, T{60} },
			{ Key{5}, T{70} },
		};
		Range r(a);
		Map v(hamon::from_range, r, comp);
		VERIFY(!v.empty());
		VERIFY(v.size() == 7);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.get_allocator() == Allocator{});
		{
			auto it = v.begin();
			VERIFY(*it++ == ValueType{ Key{1}, T{40} });
			VERIFY(*it++ == ValueType{ Key{1}, T{60} });
			VERIFY(*it++ == ValueType{ Key{3}, T{20} });
			VERIFY(*it++ == ValueType{ Key{4}, T{50} });
			VERIFY(*it++ == ValueType{ Key{5}, T{10} });
			VERIFY(*it++ == ValueType{ Key{5}, T{30} });
			VERIFY(*it++ == ValueType{ Key{5}, T{70} });
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == ValueType{ Key{5}, T{70} });
			VERIFY(*it++ == ValueType{ Key{5}, T{30} });
			VERIFY(*it++ == ValueType{ Key{5}, T{10} });
			VERIFY(*it++ == ValueType{ Key{4}, T{50} });
			VERIFY(*it++ == ValueType{ Key{3}, T{20} });
			VERIFY(*it++ == ValueType{ Key{1}, T{60} });
			VERIFY(*it++ == ValueType{ Key{1}, T{40} });
			VERIFY(it == v.rend());
		}
	}
	{
		ValueType a[] =
		{
			{ Key{5}, T{10} },
			{ Key{3}, T{20} },
			{ Key{4}, T{30} },
			{ Key{5}, T{40} },
			{ Key{1}, T{50} },
			{ Key{4}, T{60} },
			{ Key{1}, T{70} },
			{ Key{5}, T{80} },
		};
		Range r(a);
		Map v(hamon::from_range, r, comp, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 8);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.get_allocator() == alloc);
		{
			auto it = v.begin();
			VERIFY(*it++ == ValueType{ Key{1}, T{50} });
			VERIFY(*it++ == ValueType{ Key{1}, T{70} });
			VERIFY(*it++ == ValueType{ Key{3}, T{20} });
			VERIFY(*it++ == ValueType{ Key{4}, T{30} });
			VERIFY(*it++ == ValueType{ Key{4}, T{60} });
			VERIFY(*it++ == ValueType{ Key{5}, T{10} });
			VERIFY(*it++ == ValueType{ Key{5}, T{40} });
			VERIFY(*it++ == ValueType{ Key{5}, T{80} });
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == ValueType{ Key{5}, T{80} });
			VERIFY(*it++ == ValueType{ Key{5}, T{40} });
			VERIFY(*it++ == ValueType{ Key{5}, T{10} });
			VERIFY(*it++ == ValueType{ Key{4}, T{60} });
			VERIFY(*it++ == ValueType{ Key{4}, T{30} });
			VERIFY(*it++ == ValueType{ Key{3}, T{20} });
			VERIFY(*it++ == ValueType{ Key{1}, T{70} });
			VERIFY(*it++ == ValueType{ Key{1}, T{50} });
			VERIFY(it == v.rend());
		}
	}

	return true;
}

template <typename Key, typename T, typename Compare, typename Allocator>
MULTIMAP_TEST_CONSTEXPR bool test_impl(Compare const& comp, Allocator const& alloc)
{
	return
		test_imp2<Key, T, test_input_range>(comp, alloc) &&
		test_imp2<Key, T, test_forward_range>(comp, alloc) &&
		test_imp2<Key, T, test_bidirectional_range>(comp, alloc) &&
		test_imp2<Key, T, test_random_access_range>(comp, alloc) &&
		test_imp2<Key, T, test_contiguous_range>(comp, alloc) &&
		test_imp2<Key, T, test_input_sized_range>(comp, alloc) &&
		test_imp2<Key, T, test_forward_sized_range>(comp, alloc) &&
		test_imp2<Key, T, test_bidirectional_sized_range>(comp, alloc) &&
		test_imp2<Key, T, test_random_access_sized_range>(comp, alloc) &&
		test_imp2<Key, T, test_contiguous_sized_range>(comp, alloc);
}

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test1_2()
{
	MyLess comp{13};
	hamon::allocator<std::pair<const Key, T>> alloc;
	VERIFY(test_impl<Key, T>(comp, alloc));

	return true;
}

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test2_2()
{
	MyLess comp{14};
	MyAllocator<std::pair<const Key, T>> alloc{42};
	VERIFY(test_impl<Key, T>(comp, alloc));

	return true;
}

template <typename Key>
MULTIMAP_TEST_CONSTEXPR bool test1()
{
	VERIFY(test1_2<Key, int>());
	VERIFY(test1_2<Key, char>());
	VERIFY(test1_2<Key, float>());

	return true;
}

template <typename Key>
MULTIMAP_TEST_CONSTEXPR bool test2()
{
	VERIFY(test2_2<Key, int>());
	VERIFY(test2_2<Key, char>());
	VERIFY(test2_2<Key, float>());

	return true;
}

#undef VERIFY

GTEST_TEST(MultimapTest, CtorRangeTest)
{
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace ctor_range_test

}	// namespace hamon_multimap_test

#endif
