/**
 *	@file	unit_test_multimap_node_type.cpp
 *
 *	@brief	node_type のテスト
 */

#include <hamon/map/multimap.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multimap_test
{

namespace node_type_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Map = hamon::multimap<Key, T>;
	using NodeType = typename Map::node_type;
	using AllocType = typename Map::allocator_type;

	static_assert(hamon::is_same<typename NodeType::key_type, Key>::value, "");
	static_assert(hamon::is_same<typename NodeType::mapped_type, T>::value, "");
	static_assert(hamon::is_same<typename NodeType::allocator_type, AllocType>::value, "");

	static_assert( hamon::is_default_constructible<NodeType>::value, "");
	static_assert( hamon::is_nothrow_default_constructible<NodeType>::value, "");
	static_assert(!hamon::is_trivially_default_constructible<NodeType>::value, "");
	static_assert( hamon::is_implicitly_default_constructible<NodeType>::value, "");

	static_assert(!hamon::is_copy_constructible<NodeType>::value, "");

	static_assert( hamon::is_move_constructible<NodeType>::value, "");
	static_assert( hamon::is_nothrow_move_constructible<NodeType>::value, "");
	static_assert(!hamon::is_trivially_move_constructible<NodeType>::value, "");
	static_assert( hamon::is_implicitly_move_constructible<NodeType>::value, "");

	static_assert(!hamon::is_copy_assignable<NodeType>::value, "");

	static_assert( hamon::is_move_assignable<NodeType>::value, "");
	static_assert(!hamon::is_nothrow_move_assignable<NodeType>::value, "");
	static_assert(!hamon::is_trivially_move_assignable<NodeType>::value, "");

	static_assert(hamon::is_same<decltype(hamon::declval<NodeType const&>().empty()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<NodeType const&>().operator bool()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<NodeType const&>().get_allocator()), AllocType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<NodeType const&>().key()), Key&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<NodeType const&>().mapped()), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<NodeType&>().swap(hamon::declval<NodeType&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(swap(hamon::declval<NodeType&>(), hamon::declval<NodeType&>())), void>::value, "");

	static_assert( noexcept(hamon::declval<NodeType const&>().empty()), "");
	static_assert( noexcept(hamon::declval<NodeType const&>().operator bool()), "");
	static_assert(!noexcept(hamon::declval<NodeType const&>().get_allocator()), "");
	static_assert(!noexcept(hamon::declval<NodeType const&>().key()), "");
	static_assert(!noexcept(hamon::declval<NodeType const&>().mapped()), "");
	static_assert( noexcept(hamon::declval<NodeType&>().swap(hamon::declval<NodeType&>())), "");
	static_assert( noexcept(swap(hamon::declval<NodeType&>(), hamon::declval<NodeType&>())), "");

	{
		NodeType node;
		VERIFY(node.empty());
		VERIFY(bool(node) == false);
	}
	{
		Map m
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
		};
		NodeType n1 = m.extract(Key{1});
		NodeType n2 = m.extract(Key{2});
		NodeType n3 = m.extract(Key{3});

		VERIFY(!n1.empty());
		VERIFY( n2.empty());
		VERIFY(!n3.empty());

		VERIFY(bool(n1) == true);
		VERIFY(bool(n2) == false);
		VERIFY(bool(n3) == true);

		VERIFY(n1.key() == Key{1});
		VERIFY(n3.key() == Key{3});

		VERIFY(n1.mapped() == T{20});
		VERIFY(n3.mapped() == T{10});

#if !defined(HAMON_MSVC)	// MSVC だと constexpr にできない
		VERIFY(n1.get_allocator() == m.get_allocator());
		VERIFY(n3.get_allocator() == m.get_allocator());
#endif

//		n1.key() = Key{2};	// key() の書き換えはconstexprにできない
		n3.mapped() = T{30};

		n1.swap(n3);

		VERIFY(n1.key() == Key{3});
		VERIFY(n3.key() == Key{1});

		VERIFY(n1.mapped() == T{30});
		VERIFY(n3.mapped() == T{20});

		swap(n1, n3);

		VERIFY(n1.key() == Key{1});
		VERIFY(n3.key() == Key{3});

		VERIFY(n1.mapped() == T{20});
		VERIFY(n3.mapped() == T{30});

#if !defined(HAMON_MSVC)	// MSVC だと constexpr にできない
		n1.swap(n2);

		VERIFY( n1.empty());
		VERIFY(!n2.empty());
		VERIFY(!n3.empty());

		VERIFY(n2.key() == Key{1});
		VERIFY(n3.key() == Key{3});

		VERIFY(n2.mapped() == T{20});
		VERIFY(n3.mapped() == T{30});

		VERIFY(n2.get_allocator() == m.get_allocator());
		VERIFY(n3.get_allocator() == m.get_allocator());
#endif
	}

	return true;
}

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test2()
{
	using Map = hamon::multimap<Key, T>;
	using NodeType = typename Map::node_type;

	{
		Map m
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
		};
		NodeType n1 = m.extract(Key{1});
		NodeType n2 = m.extract(Key{2});
		NodeType n3 = m.extract(Key{3});

		VERIFY(!n1.empty());
		VERIFY( n2.empty());
		VERIFY(!n3.empty());

		VERIFY(bool(n1) == true);
		VERIFY(bool(n2) == false);
		VERIFY(bool(n3) == true);

		VERIFY(n1.key() == Key{1});
		VERIFY(n3.key() == Key{3});

		VERIFY(n1.mapped() == T{20});
		VERIFY(n3.mapped() == T{10});

		VERIFY(n1.get_allocator() == m.get_allocator());
		VERIFY(n3.get_allocator() == m.get_allocator());

		n1.key() = Key{2};
		n3.mapped() = T{30};

		n1.swap(n3);

		VERIFY(n1.key() == Key{3});
		VERIFY(n3.key() == Key{2});

		VERIFY(n1.mapped() == T{30});
		VERIFY(n3.mapped() == T{20});

		swap(n1, n3);

		VERIFY(n1.key() == Key{2});
		VERIFY(n3.key() == Key{3});

		VERIFY(n1.mapped() == T{20});
		VERIFY(n3.mapped() == T{30});

		n1.swap(n2);

		VERIFY( n1.empty());
		VERIFY(!n2.empty());
		VERIFY(!n3.empty());

		VERIFY(n2.key() == Key{2});
		VERIFY(n3.key() == Key{3});

		VERIFY(n2.mapped() == T{20});
		VERIFY(n3.mapped() == T{30});

		VERIFY(n2.get_allocator() == m.get_allocator());
		VERIFY(n3.get_allocator() == m.get_allocator());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MultimapTest, NodeTypeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

	EXPECT_TRUE((test2<int, int>()));
	EXPECT_TRUE((test2<int, char>()));
	EXPECT_TRUE((test2<int, float>()));
	EXPECT_TRUE((test2<char, int>()));
	EXPECT_TRUE((test2<char, char>()));
	EXPECT_TRUE((test2<char, float>()));
	EXPECT_TRUE((test2<float, int>()));
	EXPECT_TRUE((test2<float, char>()));
	EXPECT_TRUE((test2<float, float>()));
}

}	// namespace node_type_test

}	// namespace hamon_multimap_test
