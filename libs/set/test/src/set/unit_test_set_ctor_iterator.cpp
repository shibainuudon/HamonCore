/**
 *	@file	unit_test_set_ctor_iterator.cpp
 *
 *	@brief	iteratorを引数に取るコンストラクタのテスト
 *
 *	template<class InputIterator>
 *	set(InputIterator first, InputIterator last,
 *		const Compare& comp = Compare(), const Allocator& = Allocator());
 *
 *	template<class InputIterator>
 *	set(InputIterator first, InputIterator last, const Allocator& a)
 *		: set(first, last, Compare(), a) { }
 */

#include <hamon/set/set.hpp>
#include <hamon/functional.hpp>
#include <hamon/memory.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_set_test
{

namespace ctor_iterator_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
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

template <typename Key, template <typename> class IteratorWrapper, typename Compare, typename Allocator>
SET_TEST_CONSTEXPR bool test_impl2(Compare const& comp, Allocator const& alloc)
{
	using Set = hamon::set<Key, Compare, Allocator>;
	using ValueType = typename Set::value_type;
	using Iterator = IteratorWrapper<ValueType>;

	static_assert( hamon::is_constructible<Set, Iterator, Iterator>::value, "");
	static_assert( hamon::is_constructible<Set, Iterator, Iterator, Compare const&>::value, "");
	static_assert( hamon::is_constructible<Set, Iterator, Iterator, Compare const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, Iterator, Iterator>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, Iterator, Iterator, Compare const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, Iterator, Iterator, Compare const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, Iterator, Iterator>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, Iterator, Iterator, Compare const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, Iterator, Iterator, Compare const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Iterator, Iterator>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Iterator, Iterator, Compare const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Iterator, Iterator, Compare const&, Allocator const&>::value, "");

#if !defined(HAMON_USE_STD_SET) || (HAMON_CXX_STANDARD >= 14)
	static_assert( hamon::is_constructible<Set, Iterator, Iterator, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, Iterator, Iterator, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, Iterator, Iterator, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Iterator, Iterator, Allocator const&>::value, "");
#endif

	ValueType a[] =
	{
		Key{3}, Key{2}, Key{3}, Key{1}, Key{2}, Key{1},
	};

	{
		Set v(Iterator{a}, Iterator{a + 6});
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == Compare{});
		VERIFY(v.value_comp() == Compare{});
		VERIFY(v.get_allocator() == Allocator{});
		{
			auto it = v.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{2});
			VERIFY(*it++ == Key{3});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{2});
			VERIFY(*it++ == Key{1});
			VERIFY(it == v.rend());
		}
	}
	{
		Set v(Iterator{a}, Iterator{a + 6}, comp);
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.value_comp() == comp);
		VERIFY(v.get_allocator() == Allocator{});
		{
			auto it = v.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{2});
			VERIFY(*it++ == Key{3});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{2});
			VERIFY(*it++ == Key{1});
			VERIFY(it == v.rend());
		}
	}
	{
		Set v(Iterator{a}, Iterator{a + 6}, comp, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.value_comp() == comp);
		VERIFY(v.get_allocator() == alloc);
		{
			auto it = v.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{2});
			VERIFY(*it++ == Key{3});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{2});
			VERIFY(*it++ == Key{1});
			VERIFY(it == v.rend());
		}
	}
#if !defined(HAMON_USE_STD_SET) || (HAMON_CXX_STANDARD >= 14)
	{
		Set v(Iterator{a}, Iterator{a + 6}, alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		VERIFY(v.key_comp() == Compare{});
		VERIFY(v.value_comp() == Compare{});
		VERIFY(v.get_allocator() == alloc);
		{
			auto it = v.begin();
			VERIFY(*it++ == Key{1});
			VERIFY(*it++ == Key{2});
			VERIFY(*it++ == Key{3});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == Key{3});
			VERIFY(*it++ == Key{2});
			VERIFY(*it++ == Key{1});
			VERIFY(it == v.rend());
		}
	}
#endif
	{
		Set v(Iterator{a}, Iterator{a});
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
		VERIFY(v.key_comp() == Compare{});
		VERIFY(v.value_comp() == Compare{});
		VERIFY(v.get_allocator() == Allocator{});
	}
	{
		Set v(Iterator{a}, Iterator{a}, comp);
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.value_comp() == comp);
		VERIFY(v.get_allocator() == Allocator{});
	}
	{
		Set v(Iterator{a}, Iterator{a}, comp, alloc);
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.value_comp() == comp);
		VERIFY(v.get_allocator() == alloc);
	}
#if !defined(HAMON_USE_STD_SET) || (HAMON_CXX_STANDARD >= 14)
	{
		Set v(Iterator{a}, Iterator{a}, alloc);
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
		VERIFY(v.key_comp() == Compare{});
		VERIFY(v.value_comp() == Compare{});
		VERIFY(v.get_allocator() == alloc);
	}
#endif

	return true;
}

template <typename Key, typename Compare, typename Allocator>
SET_TEST_CONSTEXPR bool test_impl(Compare const& comp, Allocator const& alloc)
{
	return
		test_impl2<Key, cpp17_input_iterator_wrapper>(comp, alloc) &&
		//test_impl2<Key, input_iterator_wrapper>(comp, alloc) &&
		test_impl2<Key, forward_iterator_wrapper>(comp, alloc) &&
		test_impl2<Key, bidirectional_iterator_wrapper>(comp, alloc) &&
		test_impl2<Key, random_access_iterator_wrapper>(comp, alloc) &&
		test_impl2<Key, contiguous_iterator_wrapper>(comp, alloc);
}

template <typename Key>
SET_TEST_CONSTEXPR bool test1()
{
	MyLess comp{13};
	hamon::allocator<Key> alloc;
	VERIFY(test_impl<Key>(comp, alloc));

	return true;
}

template <typename Key>
SET_TEST_CONSTEXPR bool test2()
{
	MyLess comp{14};
	MyAllocator<Key> alloc{42};
	VERIFY(test_impl<Key>(comp, alloc));

	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, CtorIteratorTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace ctor_iterator_test

}	// namespace hamon_set_test
