﻿/**
 *	@file	unit_test_container_detail_red_black_tree.cpp
 *
 *	@brief	red_black_tree のテスト
 */

#include <hamon/container/detail/red_black_tree.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/functional.hpp>
#include <hamon/memory.hpp>
#include <hamon/ranges.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_container_test
{

namespace red_black_tree_test
{

template <typename Node>
HAMON_CXX14_CONSTEXPR int
tree_black_height_sub(Node const* p)
{
	if (p == nullptr)
	{
		return 1;
	}

	auto h1 = tree_black_height_sub(p->left());
	auto h2 = tree_black_height_sub(p->right());

	if (h1 == 0 || h2 == 0)
	{
		return 0;
	}

	if (h1 != h2)
	{
		return 0;
	}

	return p->is_black() ? 1 + h1 : h1;
}

template <typename Node>
HAMON_CXX14_CONSTEXPR bool
tree_invariant_sub(Node const* p)
{
	if (p == nullptr)
	{
		return true;
	}

	// 親子関係が双方向に正しく設定されているか
	if (p->left() != nullptr)
	{
		if (p->left()->parent() != p)
		{
			return false;
		}
	}

	if (p->right() != nullptr)
	{
		if (p->right()->parent() != p)
		{
			return false;
		}
	}

	// Left == Right は有り得ない
	if (p->left() != nullptr)
	{
		if (p->left() == p->right())
		{
			return false;
		}
	}

	// 各ノードは黒か赤
	if (!(p->is_black() || p->is_red()))
	{
		return false;
	}

	// 赤ノードの子は黒ノード
	if (p->is_red())
	{
		if (p->left() != nullptr && p->left()->is_red())
		{
			return false;
		}

		if (p->right() != nullptr && p->right()->is_red())
		{
			return false;
		}
	}

	// Leftのチェック
	if (!tree_invariant_sub(p->left()))
	{
		return false;
	}

	// Rightのチェック
	if (!tree_invariant_sub(p->right()))
	{
		return false;
	}

	return true;
}

// 赤黒木の不変条件
template <typename Tree>
HAMON_CXX14_CONSTEXPR bool
tree_invariant(Tree const& t)
{
	auto root = t.root();

	// Rootはnullでも良い
	if (root == nullptr)
	{
		return true;
	}

	// Rootの親はnull
	if (root->parent() != nullptr)
	{
		return false;
	}

	// Rootは黒
	if (root->is_red())
	{
		return false;
	}

	// t.leftmost()の正しさチェック
	if (t.leftmost()->root() != root)
	{
		return false;
	}

	if (root->leftmost() != t.leftmost())
	{
		return false;
	}

	// t.rightmost()の正しさチェック
	if (t.rightmost()->root() != root)
	{
		return false;
	}

	if (root->rightmost() != t.rightmost())
	{
		return false;
	}

	// サブツリーを再帰的にチェック
	if (!tree_invariant_sub(root))
	{
		return false;
	}

	// 葉ノードまでの黒の数チェック
	return tree_black_height_sub(root) != 0;
}

template <typename Tree>
HAMON_CXX14_CONSTEXPR int
tree_black_height(Tree const& t)
{
	return tree_black_height_sub(t.root());
}

template <typename Tree, typename T = typename Tree::value_type>
HAMON_CXX14_CONSTEXPR bool
tree_equal(Tree const& t, std::initializer_list<T> il)
{
	if (t.size() != il.size())
	{
		return false;
	}

	{
		auto p = t.leftmost();
		auto it = hamon::ranges::begin(il);
		for (; it != hamon::ranges::end(il); ++it)
		{
			if (p == nullptr)
			{
				return false;
			}

			if (p->value() != *it)
			{
				return false;
			}

			p = p->next();
		}

		if (p != nullptr)
		{
			return false;
		}
	}
	{
		auto p = t.rightmost();
		auto it = hamon::ranges::rbegin(il);
		for (; it != hamon::ranges::rend(il); ++it)
		{
			if (p == nullptr)
			{
				return false;
			}

			if (p->value() != *it)
			{
				return false;
			}

			p = p->prev();
		}

		if (p != nullptr)
		{
			return false;
		}
	}

	return true;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR bool test1()
{
	using Tree = hamon::detail::red_black_tree<false, int>;
	using Node = typename Tree::node_type;

	hamon::allocator<Node> alloc;
	hamon::less<> comp;

	{
		Tree t;
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 1);
		VERIFY(tree_equal(t, {}));
		VERIFY(t.lower_bound(comp, 0) == t.end());
		VERIFY(t.upper_bound(comp, 0) == t.end());

		t.emplace(comp, alloc, 10);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10}));
		VERIFY(t.lower_bound(comp,  9) != t.end());
		VERIFY(t.lower_bound(comp, 10) != t.end());
		VERIFY(t.lower_bound(comp, 11) == t.end());
		VERIFY(t.upper_bound(comp,  9) != t.end());
		VERIFY(t.upper_bound(comp, 10) == t.end());
		VERIFY(t.upper_bound(comp, 11) == t.end());
		VERIFY(*t.lower_bound(comp,  9) == 10);
		VERIFY(*t.lower_bound(comp, 10) == 10);
		VERIFY(*t.upper_bound(comp,  9) == 10);

		t.emplace(comp, alloc, 10);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10}));

		t.emplace(comp, alloc, 20);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10, 20}));

		t.emplace(comp, alloc, 20);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10, 20}));

		t.emplace(comp, alloc, 5);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {5, 10, 20}));

		t.emplace(comp, alloc, 15);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 10, 15, 20}));

		t.emplace(comp, alloc, 1);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 5, 10, 15, 20}));

		t.emplace(comp, alloc, 7);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 5, 7, 10, 15, 20}));

		t.emplace(comp, alloc, 23);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 5, 7, 10, 15, 20, 23}));

		t.emplace(comp, alloc, 17);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 5, 7, 10, 15, 17, 20, 23}));

		t.emplace(comp, alloc, 2);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 2, 5, 7, 10, 15, 17, 20, 23}));

		t.emplace(comp, alloc, 22);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 2, 5, 7, 10, 15, 17, 20, 22, 23}));

		t.emplace(comp, alloc, 3);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 2, 3, 5, 7, 10, 15, 17, 20, 22, 23}));

		t.emplace(comp, alloc, 4);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5, 7, 10, 15, 17, 20, 22, 23}));

		t.emplace(comp, alloc,  1);
		t.emplace(comp, alloc,  2);
		t.emplace(comp, alloc,  3);
		t.emplace(comp, alloc,  4);
		t.emplace(comp, alloc,  5);
		t.emplace(comp, alloc,  7);
		t.emplace(comp, alloc, 10);
		t.emplace(comp, alloc, 15);
		t.emplace(comp, alloc, 17);
		t.emplace(comp, alloc, 20);
		t.emplace(comp, alloc, 22);
		t.emplace(comp, alloc, 23);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5, 7, 10, 15, 17, 20, 22, 23}));

		t.emplace(comp, alloc, 11);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5, 7, 10, 11, 15, 17, 20, 22, 23}));

		t.emplace(comp, alloc, 11);
		t.emplace(comp, alloc, 11);
		t.emplace(comp, alloc, 11);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5, 7, 10, 11, 15, 17, 20, 22, 23}));

		t.emplace(comp, alloc, 12);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5, 7, 10, 11, 12, 15, 17, 20, 22, 23}));
		VERIFY(t.lower_bound(comp,  0) != t.end());
		VERIFY(t.lower_bound(comp,  1) != t.end());
		VERIFY(t.lower_bound(comp,  2) != t.end());
		VERIFY(t.lower_bound(comp,  3) != t.end());
		VERIFY(t.lower_bound(comp,  4) != t.end());
		VERIFY(t.lower_bound(comp,  5) != t.end());
		VERIFY(t.lower_bound(comp,  6) != t.end());
		VERIFY(t.lower_bound(comp,  7) != t.end());
		VERIFY(t.lower_bound(comp,  8) != t.end());
		VERIFY(t.lower_bound(comp,  9) != t.end());
		VERIFY(t.lower_bound(comp, 10) != t.end());
		VERIFY(t.lower_bound(comp, 11) != t.end());
		VERIFY(t.lower_bound(comp, 12) != t.end());
		VERIFY(t.lower_bound(comp, 13) != t.end());
		VERIFY(t.lower_bound(comp, 14) != t.end());
		VERIFY(t.lower_bound(comp, 15) != t.end());
		VERIFY(t.lower_bound(comp, 16) != t.end());
		VERIFY(t.lower_bound(comp, 17) != t.end());
		VERIFY(t.lower_bound(comp, 18) != t.end());
		VERIFY(t.lower_bound(comp, 19) != t.end());
		VERIFY(t.lower_bound(comp, 20) != t.end());
		VERIFY(t.lower_bound(comp, 21) != t.end());
		VERIFY(t.lower_bound(comp, 22) != t.end());
		VERIFY(t.lower_bound(comp, 23) != t.end());
		VERIFY(t.lower_bound(comp, 24) == t.end());
		VERIFY(t.lower_bound(comp, 25) == t.end());
		VERIFY(*t.lower_bound(comp,  0) ==  1);
		VERIFY(*t.lower_bound(comp,  1) ==  1);
		VERIFY(*t.lower_bound(comp,  2) ==  2);
		VERIFY(*t.lower_bound(comp,  3) ==  3);
		VERIFY(*t.lower_bound(comp,  4) ==  4);
		VERIFY(*t.lower_bound(comp,  5) ==  5);
		VERIFY(*t.lower_bound(comp,  6) ==  7);
		VERIFY(*t.lower_bound(comp,  7) ==  7);
		VERIFY(*t.lower_bound(comp,  8) == 10);
		VERIFY(*t.lower_bound(comp,  9) == 10);
		VERIFY(*t.lower_bound(comp, 10) == 10);
		VERIFY(*t.lower_bound(comp, 11) == 11);
		VERIFY(*t.lower_bound(comp, 12) == 12);
		VERIFY(*t.lower_bound(comp, 13) == 15);
		VERIFY(*t.lower_bound(comp, 14) == 15);
		VERIFY(*t.lower_bound(comp, 15) == 15);
		VERIFY(*t.lower_bound(comp, 16) == 17);
		VERIFY(*t.lower_bound(comp, 17) == 17);
		VERIFY(*t.lower_bound(comp, 18) == 20);
		VERIFY(*t.lower_bound(comp, 19) == 20);
		VERIFY(*t.lower_bound(comp, 20) == 20);
		VERIFY(*t.lower_bound(comp, 21) == 22);
		VERIFY(*t.lower_bound(comp, 22) == 22);
		VERIFY(*t.lower_bound(comp, 23) == 23);
		VERIFY(t.upper_bound(comp,  0) != t.end());
		VERIFY(t.upper_bound(comp,  1) != t.end());
		VERIFY(t.upper_bound(comp,  2) != t.end());
		VERIFY(t.upper_bound(comp,  3) != t.end());
		VERIFY(t.upper_bound(comp,  4) != t.end());
		VERIFY(t.upper_bound(comp,  5) != t.end());
		VERIFY(t.upper_bound(comp,  6) != t.end());
		VERIFY(t.upper_bound(comp,  7) != t.end());
		VERIFY(t.upper_bound(comp,  8) != t.end());
		VERIFY(t.upper_bound(comp,  9) != t.end());
		VERIFY(t.upper_bound(comp, 10) != t.end());
		VERIFY(t.upper_bound(comp, 11) != t.end());
		VERIFY(t.upper_bound(comp, 12) != t.end());
		VERIFY(t.upper_bound(comp, 13) != t.end());
		VERIFY(t.upper_bound(comp, 14) != t.end());
		VERIFY(t.upper_bound(comp, 15) != t.end());
		VERIFY(t.upper_bound(comp, 16) != t.end());
		VERIFY(t.upper_bound(comp, 17) != t.end());
		VERIFY(t.upper_bound(comp, 18) != t.end());
		VERIFY(t.upper_bound(comp, 19) != t.end());
		VERIFY(t.upper_bound(comp, 20) != t.end());
		VERIFY(t.upper_bound(comp, 21) != t.end());
		VERIFY(t.upper_bound(comp, 22) != t.end());
		VERIFY(t.upper_bound(comp, 23) == t.end());
		VERIFY(t.upper_bound(comp, 24) == t.end());
		VERIFY(t.upper_bound(comp, 25) == t.end());
		VERIFY(*t.upper_bound(comp,  0) == 1);
		VERIFY(*t.upper_bound(comp,  1) == 2);
		VERIFY(*t.upper_bound(comp,  2) == 3);
		VERIFY(*t.upper_bound(comp,  3) == 4);
		VERIFY(*t.upper_bound(comp,  4) == 5);
		VERIFY(*t.upper_bound(comp,  5) == 7);
		VERIFY(*t.upper_bound(comp,  6) == 7);
		VERIFY(*t.upper_bound(comp,  7) == 10);
		VERIFY(*t.upper_bound(comp,  8) == 10);
		VERIFY(*t.upper_bound(comp,  9) == 10);
		VERIFY(*t.upper_bound(comp, 10) == 11);
		VERIFY(*t.upper_bound(comp, 11) == 12);
		VERIFY(*t.upper_bound(comp, 12) == 15);
		VERIFY(*t.upper_bound(comp, 13) == 15);
		VERIFY(*t.upper_bound(comp, 14) == 15);
		VERIFY(*t.upper_bound(comp, 15) == 17);
		VERIFY(*t.upper_bound(comp, 16) == 17);
		VERIFY(*t.upper_bound(comp, 17) == 20);
		VERIFY(*t.upper_bound(comp, 18) == 20);
		VERIFY(*t.upper_bound(comp, 19) == 20);
		VERIFY(*t.upper_bound(comp, 20) == 22);
		VERIFY(*t.upper_bound(comp, 21) == 22);
		VERIFY(*t.upper_bound(comp, 22) == 23);

		t.clear(alloc);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 1);
		VERIFY(tree_equal(t, {}));
	}
	{
		Tree t;
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 1);
		VERIFY(tree_equal(t, {}));

		t.emplace(comp, alloc, 10);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10}));

		t.emplace(comp, alloc, 9);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {9, 10}));

		t.emplace(comp, alloc, 8);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {8, 9, 10}));

		t.emplace(comp, alloc, 7);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {7, 8, 9, 10}));

		t.emplace(comp, alloc, 6);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {6, 7, 8, 9, 10}));

		t.emplace(comp, alloc, 5);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 6, 7, 8, 9, 10}));

		t.emplace(comp, alloc, 4);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {4, 5, 6, 7, 8, 9, 10}));

		t.emplace(comp, alloc, 3);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {3, 4, 5, 6, 7, 8, 9, 10}));

		t.emplace(comp, alloc, 2);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {2, 3, 4, 5, 6, 7, 8, 9, 10}));

		t.emplace(comp, alloc, 1);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));

		t.clear(alloc);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 1);
		VERIFY(tree_equal(t, {}));
	}
	{
		Tree t;
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 1);
		VERIFY(tree_equal(t, {}));

		t.emplace(comp, alloc, 1);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {1}));

		t.emplace(comp, alloc, 2);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {1, 2}));

		t.emplace(comp, alloc, 3);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {1, 2, 3}));

		t.emplace(comp, alloc, 4);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 2, 3, 4}));

		t.emplace(comp, alloc, 5);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5}));

		t.emplace(comp, alloc, 6);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5, 6}));

		t.emplace(comp, alloc, 7);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5, 6, 7}));

		t.emplace(comp, alloc, 8);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5, 6, 7, 8}));

		t.emplace(comp, alloc, 9);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5, 6, 7, 8, 9}));

		t.emplace(comp, alloc, 10);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));

		t.clear(alloc);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 1);
		VERIFY(tree_equal(t, {}));
	}

	return true;
}

HAMON_CXX20_CONSTEXPR bool test2()
{
	using Tree = hamon::detail::red_black_tree<true, int>;
	using Node = typename Tree::node_type;

	hamon::allocator<Node> alloc;
	hamon::less<> comp;

	{
		Tree t;
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 1);
		VERIFY(tree_equal(t, {}));

		t.emplace(comp, alloc, 10);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10}));

		t.emplace(comp, alloc, 10);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10, 10}));

		t.emplace(comp, alloc, 5);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {5, 10, 10}));

		t.emplace(comp, alloc, 15);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 10, 10, 15}));

		t.emplace(comp, alloc, 5);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 5, 10, 10, 15}));

		t.emplace(comp, alloc, 6);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 5, 6, 10, 10, 15}));

		t.emplace(comp, alloc, 10);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 5, 6, 10, 10, 10, 15}));

		t.emplace(comp, alloc, 12);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 5, 6, 10, 10, 10, 12, 15}));

		t.emplace(comp, alloc, 15);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 5, 6, 10, 10, 10, 12, 15, 15}));

		t.clear(alloc);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 1);
		VERIFY(tree_equal(t, {}));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ContainerTest, RedBlackTreeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());
}

}	// namespace red_black_tree_test

}	// namespace hamon_container_test