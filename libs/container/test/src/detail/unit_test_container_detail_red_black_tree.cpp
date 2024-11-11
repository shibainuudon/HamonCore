/**
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
	using Tree = hamon::detail::red_black_tree<false, int, hamon::size_t, hamon::ptrdiff_t>;
	using Node = typename Tree::node_type;

	hamon::allocator<Node> alloc;
	hamon::less<> comp;

	{
		Tree t;
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 1);
		VERIFY(tree_equal(t, {}));
		VERIFY(t.lower_bound(0, comp) == nullptr);
		VERIFY(t.upper_bound(0, comp) == nullptr);

		t.emplace(comp, alloc, 10);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10}));
		VERIFY(t.lower_bound( 9, comp) != nullptr);
		VERIFY(t.lower_bound(10, comp) != nullptr);
		VERIFY(t.lower_bound(11, comp) == nullptr);
		VERIFY(t.upper_bound( 9, comp) != nullptr);
		VERIFY(t.upper_bound(10, comp) == nullptr);
		VERIFY(t.upper_bound(11, comp) == nullptr);
		VERIFY(t.lower_bound( 9, comp)->value() == 10);
		VERIFY(t.lower_bound(10, comp)->value() == 10);
		VERIFY(t.upper_bound( 9, comp)->value() == 10);

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
		VERIFY(t.lower_bound( 0, comp) != nullptr);
		VERIFY(t.lower_bound( 1, comp) != nullptr);
		VERIFY(t.lower_bound( 2, comp) != nullptr);
		VERIFY(t.lower_bound( 3, comp) != nullptr);
		VERIFY(t.lower_bound( 4, comp) != nullptr);
		VERIFY(t.lower_bound( 5, comp) != nullptr);
		VERIFY(t.lower_bound( 6, comp) != nullptr);
		VERIFY(t.lower_bound( 7, comp) != nullptr);
		VERIFY(t.lower_bound( 8, comp) != nullptr);
		VERIFY(t.lower_bound( 9, comp) != nullptr);
		VERIFY(t.lower_bound(10, comp) != nullptr);
		VERIFY(t.lower_bound(11, comp) != nullptr);
		VERIFY(t.lower_bound(12, comp) != nullptr);
		VERIFY(t.lower_bound(13, comp) != nullptr);
		VERIFY(t.lower_bound(14, comp) != nullptr);
		VERIFY(t.lower_bound(15, comp) != nullptr);
		VERIFY(t.lower_bound(16, comp) != nullptr);
		VERIFY(t.lower_bound(17, comp) != nullptr);
		VERIFY(t.lower_bound(18, comp) != nullptr);
		VERIFY(t.lower_bound(19, comp) != nullptr);
		VERIFY(t.lower_bound(20, comp) != nullptr);
		VERIFY(t.lower_bound(21, comp) != nullptr);
		VERIFY(t.lower_bound(22, comp) != nullptr);
		VERIFY(t.lower_bound(23, comp) != nullptr);
		VERIFY(t.lower_bound(24, comp) == nullptr);
		VERIFY(t.lower_bound(25, comp) == nullptr);
		VERIFY(t.lower_bound( 0, comp)->value() ==  1);
		VERIFY(t.lower_bound( 1, comp)->value() ==  1);
		VERIFY(t.lower_bound( 2, comp)->value() ==  2);
		VERIFY(t.lower_bound( 3, comp)->value() ==  3);
		VERIFY(t.lower_bound( 4, comp)->value() ==  4);
		VERIFY(t.lower_bound( 5, comp)->value() ==  5);
		VERIFY(t.lower_bound( 6, comp)->value() ==  7);
		VERIFY(t.lower_bound( 7, comp)->value() ==  7);
		VERIFY(t.lower_bound( 8, comp)->value() == 10);
		VERIFY(t.lower_bound( 9, comp)->value() == 10);
		VERIFY(t.lower_bound(10, comp)->value() == 10);
		VERIFY(t.lower_bound(11, comp)->value() == 11);
		VERIFY(t.lower_bound(12, comp)->value() == 12);
		VERIFY(t.lower_bound(13, comp)->value() == 15);
		VERIFY(t.lower_bound(14, comp)->value() == 15);
		VERIFY(t.lower_bound(15, comp)->value() == 15);
		VERIFY(t.lower_bound(16, comp)->value() == 17);
		VERIFY(t.lower_bound(17, comp)->value() == 17);
		VERIFY(t.lower_bound(18, comp)->value() == 20);
		VERIFY(t.lower_bound(19, comp)->value() == 20);
		VERIFY(t.lower_bound(20, comp)->value() == 20);
		VERIFY(t.lower_bound(21, comp)->value() == 22);
		VERIFY(t.lower_bound(22, comp)->value() == 22);
		VERIFY(t.lower_bound(23, comp)->value() == 23);
		VERIFY(t.upper_bound( 0, comp) != nullptr);
		VERIFY(t.upper_bound( 1, comp) != nullptr);
		VERIFY(t.upper_bound( 2, comp) != nullptr);
		VERIFY(t.upper_bound( 3, comp) != nullptr);
		VERIFY(t.upper_bound( 4, comp) != nullptr);
		VERIFY(t.upper_bound( 5, comp) != nullptr);
		VERIFY(t.upper_bound( 6, comp) != nullptr);
		VERIFY(t.upper_bound( 7, comp) != nullptr);
		VERIFY(t.upper_bound( 8, comp) != nullptr);
		VERIFY(t.upper_bound( 9, comp) != nullptr);
		VERIFY(t.upper_bound(10, comp) != nullptr);
		VERIFY(t.upper_bound(11, comp) != nullptr);
		VERIFY(t.upper_bound(12, comp) != nullptr);
		VERIFY(t.upper_bound(13, comp) != nullptr);
		VERIFY(t.upper_bound(14, comp) != nullptr);
		VERIFY(t.upper_bound(15, comp) != nullptr);
		VERIFY(t.upper_bound(16, comp) != nullptr);
		VERIFY(t.upper_bound(17, comp) != nullptr);
		VERIFY(t.upper_bound(18, comp) != nullptr);
		VERIFY(t.upper_bound(19, comp) != nullptr);
		VERIFY(t.upper_bound(20, comp) != nullptr);
		VERIFY(t.upper_bound(21, comp) != nullptr);
		VERIFY(t.upper_bound(22, comp) != nullptr);
		VERIFY(t.upper_bound(23, comp) == nullptr);
		VERIFY(t.upper_bound(24, comp) == nullptr);
		VERIFY(t.upper_bound(25, comp) == nullptr);
		VERIFY(t.upper_bound( 0, comp)->value() == 1);
		VERIFY(t.upper_bound( 1, comp)->value() == 2);
		VERIFY(t.upper_bound( 2, comp)->value() == 3);
		VERIFY(t.upper_bound( 3, comp)->value() == 4);
		VERIFY(t.upper_bound( 4, comp)->value() == 5);
		VERIFY(t.upper_bound( 5, comp)->value() == 7);
		VERIFY(t.upper_bound( 6, comp)->value() == 7);
		VERIFY(t.upper_bound( 7, comp)->value() == 10);
		VERIFY(t.upper_bound( 8, comp)->value() == 10);
		VERIFY(t.upper_bound( 9, comp)->value() == 10);
		VERIFY(t.upper_bound(10, comp)->value() == 11);
		VERIFY(t.upper_bound(11, comp)->value() == 12);
		VERIFY(t.upper_bound(12, comp)->value() == 15);
		VERIFY(t.upper_bound(13, comp)->value() == 15);
		VERIFY(t.upper_bound(14, comp)->value() == 15);
		VERIFY(t.upper_bound(15, comp)->value() == 17);
		VERIFY(t.upper_bound(16, comp)->value() == 17);
		VERIFY(t.upper_bound(17, comp)->value() == 20);
		VERIFY(t.upper_bound(18, comp)->value() == 20);
		VERIFY(t.upper_bound(19, comp)->value() == 20);
		VERIFY(t.upper_bound(20, comp)->value() == 22);
		VERIFY(t.upper_bound(21, comp)->value() == 22);
		VERIFY(t.upper_bound(22, comp)->value() == 23);

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
	using Tree = hamon::detail::red_black_tree<true, int, hamon::size_t, hamon::ptrdiff_t>;
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
