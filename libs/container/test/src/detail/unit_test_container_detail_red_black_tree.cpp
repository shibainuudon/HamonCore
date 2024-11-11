/**
 *	@file	unit_test_container_detail_red_black_tree.cpp
 *
 *	@brief	red_black_tree のテスト
 */

#include <hamon/container/detail/red_black_tree.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/memory.hpp>
#include <hamon/ranges.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

//#include <queue>
//#include <iostream>

namespace hamon_container_test
{

namespace red_black_tree_test
{

#if 0
template <typename Tree>
void tree_print(Tree const& t)
{
	using Node = typename Tree::node_type;

	auto root = t.root();
	if (root == nullptr)
	{
		std::cout << "null" << std::endl;
		return;
	}

	struct S
	{
		Node* p;
		int depth;
		int x;
	};

	std::queue<S> q;
	q.push({root, 0, 0});

	while (!q.empty())
	{
		auto n = q.front();
		q.pop();

		auto p = n.p;
		std::cout << "(" << p->value() << ", " << (p->is_black() ? "B" : "R") << ", " << n.depth << ", " << (n.x == 0 ? "L" : "R") << ")\n";

		if (p->left() != nullptr)
		{
			q.push({p->left(), n.depth + 1, 0});
		}
		if (p->right() != nullptr)
		{
			q.push({p->right(), n.depth + 1, 1});
		}
	}
}
#endif

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

HAMON_CXX20_CONSTEXPR bool test_unique()
{
	using Tree = hamon::detail::red_black_tree<false, int>;
	using Node = typename Tree::node_type;

	hamon::allocator<Node> alloc;

	{
		Tree t;
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 1);
		VERIFY(tree_equal(t, {}));
		VERIFY(t.lower_bound(0) == t.end());
		VERIFY(t.upper_bound(0) == t.end());

		t.emplace(alloc, 10);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10}));
		VERIFY(t.lower_bound( 9) != t.end());
		VERIFY(t.lower_bound(10) != t.end());
		VERIFY(t.lower_bound(11) == t.end());
		VERIFY(t.upper_bound( 9) != t.end());
		VERIFY(t.upper_bound(10) == t.end());
		VERIFY(t.upper_bound(11) == t.end());
		VERIFY(*t.lower_bound( 9) == 10);
		VERIFY(*t.lower_bound(10) == 10);
		VERIFY(*t.upper_bound( 9) == 10);

		t.emplace(alloc, 10);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10}));

		t.emplace(alloc, 20);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10, 20}));

		t.emplace(alloc, 20);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10, 20}));

		t.emplace(alloc, 5);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {5, 10, 20}));

		t.emplace(alloc, 15);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 10, 15, 20}));

		t.emplace(alloc, 1);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 5, 10, 15, 20}));

		t.emplace(alloc, 7);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 5, 7, 10, 15, 20}));

		t.emplace(alloc, 23);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 5, 7, 10, 15, 20, 23}));

		t.emplace(alloc, 17);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 5, 7, 10, 15, 17, 20, 23}));

		t.emplace(alloc, 2);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 2, 5, 7, 10, 15, 17, 20, 23}));

		t.emplace(alloc, 22);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 2, 5, 7, 10, 15, 17, 20, 22, 23}));

		t.emplace(alloc, 3);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 2, 3, 5, 7, 10, 15, 17, 20, 22, 23}));

		t.emplace(alloc, 4);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5, 7, 10, 15, 17, 20, 22, 23}));

		t.emplace(alloc,  1);
		t.emplace(alloc,  2);
		t.emplace(alloc,  3);
		t.emplace(alloc,  4);
		t.emplace(alloc,  5);
		t.emplace(alloc,  7);
		t.emplace(alloc, 10);
		t.emplace(alloc, 15);
		t.emplace(alloc, 17);
		t.emplace(alloc, 20);
		t.emplace(alloc, 22);
		t.emplace(alloc, 23);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5, 7, 10, 15, 17, 20, 22, 23}));

		t.emplace(alloc, 11);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5, 7, 10, 11, 15, 17, 20, 22, 23}));

		t.emplace(alloc, 11);
		t.emplace(alloc, 11);
		t.emplace(alloc, 11);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5, 7, 10, 11, 15, 17, 20, 22, 23}));

		t.emplace(alloc, 12);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5, 7, 10, 11, 12, 15, 17, 20, 22, 23}));
		VERIFY(t.lower_bound( 0) != t.end());
		VERIFY(t.lower_bound( 1) != t.end());
		VERIFY(t.lower_bound( 2) != t.end());
		VERIFY(t.lower_bound( 3) != t.end());
		VERIFY(t.lower_bound( 4) != t.end());
		VERIFY(t.lower_bound( 5) != t.end());
		VERIFY(t.lower_bound( 6) != t.end());
		VERIFY(t.lower_bound( 7) != t.end());
		VERIFY(t.lower_bound( 8) != t.end());
		VERIFY(t.lower_bound( 9) != t.end());
		VERIFY(t.lower_bound(10) != t.end());
		VERIFY(t.lower_bound(11) != t.end());
		VERIFY(t.lower_bound(12) != t.end());
		VERIFY(t.lower_bound(13) != t.end());
		VERIFY(t.lower_bound(14) != t.end());
		VERIFY(t.lower_bound(15) != t.end());
		VERIFY(t.lower_bound(16) != t.end());
		VERIFY(t.lower_bound(17) != t.end());
		VERIFY(t.lower_bound(18) != t.end());
		VERIFY(t.lower_bound(19) != t.end());
		VERIFY(t.lower_bound(20) != t.end());
		VERIFY(t.lower_bound(21) != t.end());
		VERIFY(t.lower_bound(22) != t.end());
		VERIFY(t.lower_bound(23) != t.end());
		VERIFY(t.lower_bound(24) == t.end());
		VERIFY(t.lower_bound(25) == t.end());
		VERIFY(*t.lower_bound( 0) ==  1);
		VERIFY(*t.lower_bound( 1) ==  1);
		VERIFY(*t.lower_bound( 2) ==  2);
		VERIFY(*t.lower_bound( 3) ==  3);
		VERIFY(*t.lower_bound( 4) ==  4);
		VERIFY(*t.lower_bound( 5) ==  5);
		VERIFY(*t.lower_bound( 6) ==  7);
		VERIFY(*t.lower_bound( 7) ==  7);
		VERIFY(*t.lower_bound( 8) == 10);
		VERIFY(*t.lower_bound( 9) == 10);
		VERIFY(*t.lower_bound(10) == 10);
		VERIFY(*t.lower_bound(11) == 11);
		VERIFY(*t.lower_bound(12) == 12);
		VERIFY(*t.lower_bound(13) == 15);
		VERIFY(*t.lower_bound(14) == 15);
		VERIFY(*t.lower_bound(15) == 15);
		VERIFY(*t.lower_bound(16) == 17);
		VERIFY(*t.lower_bound(17) == 17);
		VERIFY(*t.lower_bound(18) == 20);
		VERIFY(*t.lower_bound(19) == 20);
		VERIFY(*t.lower_bound(20) == 20);
		VERIFY(*t.lower_bound(21) == 22);
		VERIFY(*t.lower_bound(22) == 22);
		VERIFY(*t.lower_bound(23) == 23);
		VERIFY(t.upper_bound( 0) != t.end());
		VERIFY(t.upper_bound( 1) != t.end());
		VERIFY(t.upper_bound( 2) != t.end());
		VERIFY(t.upper_bound( 3) != t.end());
		VERIFY(t.upper_bound( 4) != t.end());
		VERIFY(t.upper_bound( 5) != t.end());
		VERIFY(t.upper_bound( 6) != t.end());
		VERIFY(t.upper_bound( 7) != t.end());
		VERIFY(t.upper_bound( 8) != t.end());
		VERIFY(t.upper_bound( 9) != t.end());
		VERIFY(t.upper_bound(10) != t.end());
		VERIFY(t.upper_bound(11) != t.end());
		VERIFY(t.upper_bound(12) != t.end());
		VERIFY(t.upper_bound(13) != t.end());
		VERIFY(t.upper_bound(14) != t.end());
		VERIFY(t.upper_bound(15) != t.end());
		VERIFY(t.upper_bound(16) != t.end());
		VERIFY(t.upper_bound(17) != t.end());
		VERIFY(t.upper_bound(18) != t.end());
		VERIFY(t.upper_bound(19) != t.end());
		VERIFY(t.upper_bound(20) != t.end());
		VERIFY(t.upper_bound(21) != t.end());
		VERIFY(t.upper_bound(22) != t.end());
		VERIFY(t.upper_bound(23) == t.end());
		VERIFY(t.upper_bound(24) == t.end());
		VERIFY(t.upper_bound(25) == t.end());
		VERIFY(*t.upper_bound( 0) == 1);
		VERIFY(*t.upper_bound( 1) == 2);
		VERIFY(*t.upper_bound( 2) == 3);
		VERIFY(*t.upper_bound( 3) == 4);
		VERIFY(*t.upper_bound( 4) == 5);
		VERIFY(*t.upper_bound( 5) == 7);
		VERIFY(*t.upper_bound( 6) == 7);
		VERIFY(*t.upper_bound( 7) == 10);
		VERIFY(*t.upper_bound( 8) == 10);
		VERIFY(*t.upper_bound( 9) == 10);
		VERIFY(*t.upper_bound(10) == 11);
		VERIFY(*t.upper_bound(11) == 12);
		VERIFY(*t.upper_bound(12) == 15);
		VERIFY(*t.upper_bound(13) == 15);
		VERIFY(*t.upper_bound(14) == 15);
		VERIFY(*t.upper_bound(15) == 17);
		VERIFY(*t.upper_bound(16) == 17);
		VERIFY(*t.upper_bound(17) == 20);
		VERIFY(*t.upper_bound(18) == 20);
		VERIFY(*t.upper_bound(19) == 20);
		VERIFY(*t.upper_bound(20) == 22);
		VERIFY(*t.upper_bound(21) == 22);
		VERIFY(*t.upper_bound(22) == 23);

		t.erase(alloc, t.begin());
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {2, 3, 4, 5, 7, 10, 11, 12, 15, 17, 20, 22, 23}));

		t.erase(alloc, hamon::next(t.begin(), 3));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {2, 3, 4, 7, 10, 11, 12, 15, 17, 20, 22, 23}));

		t.erase(alloc, hamon::next(t.begin(), 0));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {3, 4, 7, 10, 11, 12, 15, 17, 20, 22, 23}));

		t.erase(alloc, hamon::next(t.begin(), 5));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {3, 4, 7, 10, 11, 15, 17, 20, 22, 23}));

		t.erase(alloc, hamon::next(t.begin(), 8));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {3, 4, 7, 10, 11, 15, 17, 20, 23}));

		t.erase(alloc, hamon::next(t.begin(), 8));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {3, 4, 7, 10, 11, 15, 17, 20}));

		t.erase(alloc, hamon::next(t.begin(), 1));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {3, 7, 10, 11, 15, 17, 20}));

		t.erase(alloc, hamon::next(t.begin(), 3));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {3, 7, 10, 15, 17, 20}));

		t.erase(alloc, hamon::next(t.begin(), 3));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {3, 7, 10, 17, 20}));

		t.erase(alloc, hamon::next(t.begin(), 0));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {7, 10, 17, 20}));

		t.erase(alloc, hamon::next(t.begin(), 0));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {10, 17, 20}));

		t.erase(alloc, hamon::next(t.begin(), 0));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {17, 20}));

		t.erase(alloc, hamon::next(t.begin(), 1));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {17}));

		t.erase(alloc, hamon::next(t.begin(), 0));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 1);
		VERIFY(tree_equal(t, {}));

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

		t.emplace(alloc, 10);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10}));

		t.emplace(alloc, 9);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {9, 10}));

		t.emplace(alloc, 8);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {8, 9, 10}));

		t.emplace(alloc, 7);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {7, 8, 9, 10}));

		t.emplace(alloc, 6);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {6, 7, 8, 9, 10}));

		t.emplace(alloc, 5);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 6, 7, 8, 9, 10}));

		t.emplace(alloc, 4);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {4, 5, 6, 7, 8, 9, 10}));

		t.emplace(alloc, 3);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {3, 4, 5, 6, 7, 8, 9, 10}));

		t.emplace(alloc, 2);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {2, 3, 4, 5, 6, 7, 8, 9, 10}));

		t.emplace(alloc, 1);
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

		t.emplace(alloc, 1);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {1}));

		t.emplace(alloc, 2);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {1, 2}));

		t.emplace(alloc, 3);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {1, 2, 3}));

		t.emplace(alloc, 4);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 2, 3, 4}));

		t.emplace(alloc, 5);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5}));

		t.emplace(alloc, 6);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5, 6}));

		t.emplace(alloc, 7);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5, 6, 7}));

		t.emplace(alloc, 8);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5, 6, 7, 8}));

		t.emplace(alloc, 9);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 2, 3, 4, 5, 6, 7, 8, 9}));

		t.emplace(alloc, 10);
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

		t.emplace_hint(alloc, t.begin(), 10);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10}));

		t.emplace_hint(alloc, t.begin(), 20);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10, 20}));

		t.emplace_hint(alloc, t.begin(), 10);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10, 20}));

		t.emplace_hint(alloc, t.end(), 10);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10, 20}));

		t.emplace_hint(alloc, t.begin(), 20);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10, 20}));

		t.emplace_hint(alloc, t.end(), 20);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10, 20}));

		t.emplace_hint(alloc, t.begin(), 30);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10, 20, 30}));

		t.emplace_hint(alloc, t.end(), 40);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {10, 20, 30, 40}));

		t.emplace_hint(alloc, t.begin(), 0);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {0, 10, 20, 30, 40}));

		t.emplace_hint(alloc, hamon::next(t.begin(), 1), 5);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {0, 5, 10, 20, 30, 40}));

		t.emplace_hint(alloc, hamon::next(t.begin(), 2), 15);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {0, 5, 10, 15, 20, 30, 40}));

		t.emplace_hint(alloc, hamon::next(t.begin(), 2), 13);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {0, 5, 10, 13, 15, 20, 30, 40}));

		t.emplace_hint(alloc, hamon::next(t.begin(), 2), 8);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {0, 5, 8, 10, 13, 15, 20, 30, 40}));

		t.erase(alloc, hamon::next(t.begin(), 0));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 8, 10, 13, 15, 20, 30, 40}));

		t.erase(alloc, hamon::next(t.begin(), 3));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 8, 10, 15, 20, 30, 40}));

		t.erase(alloc, hamon::next(t.begin(), 5));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 8, 10, 15, 20, 40}));

		t.erase(alloc, hamon::next(t.begin(), 5));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 8, 10, 15, 20}));

		t.erase(alloc, hamon::next(t.begin(), 4));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 8, 10, 15}));

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

		t.emplace(alloc, 13);
		t.emplace(alloc, 8);
		t.emplace(alloc, 17);
		t.emplace(alloc, 1);
		t.emplace(alloc, 11);
		t.emplace(alloc, 15);
		t.emplace(alloc, 25);
		t.emplace(alloc, 6);
		t.emplace(alloc, 22);
		t.emplace(alloc, 27);

		VERIFY(tree_equal(t, {1, 6, 8, 11, 13, 15, 17, 22, 25, 27}));

		t.erase(alloc, hamon::next(t.begin(), 1));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 8, 11, 13, 15, 17, 22, 25, 27}));

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

		t.emplace(alloc, 13);
		t.emplace(alloc, 8);
		t.emplace(alloc, 17);
		t.emplace(alloc, 1);
		t.emplace(alloc, 11);
		t.emplace(alloc, 15);
		t.emplace(alloc, 25);
		t.emplace(alloc, 6);
		t.emplace(alloc, 22);
		t.emplace(alloc, 27);

		VERIFY(tree_equal(t, {1, 6, 8, 11, 13, 15, 17, 22, 25, 27}));

		t.erase(alloc, hamon::next(t.begin(), 0));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {6, 8, 11, 13, 15, 17, 22, 25, 27}));

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

		t.emplace(alloc, 13);
		t.emplace(alloc, 8);
		t.emplace(alloc, 17);
		t.emplace(alloc, 1);
		t.emplace(alloc, 11);
		t.emplace(alloc, 15);
		t.emplace(alloc, 25);
		t.emplace(alloc, 6);
		t.emplace(alloc, 22);
		t.emplace(alloc, 27);

		VERIFY(tree_equal(t, {1, 6, 8, 11, 13, 15, 17, 22, 25, 27}));

		t.erase(alloc, hamon::next(t.begin(), 6));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 6, 8, 11, 13, 15, 22, 25, 27}));

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

		t.emplace(alloc, 13);
		t.emplace(alloc, 8);
		t.emplace(alloc, 17);
		t.emplace(alloc, 1);
		t.emplace(alloc, 11);
		t.emplace(alloc, 15);
		t.emplace(alloc, 25);
		t.emplace(alloc, 6);
		t.emplace(alloc, 22);
		t.emplace(alloc, 27);

		VERIFY(tree_equal(t, {1, 6, 8, 11, 13, 15, 17, 22, 25, 27}));

		t.erase(alloc, hamon::next(t.begin(), 8));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 6, 8, 11, 13, 15, 17, 22, 27}));

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

		t.emplace(alloc, 7);
		t.emplace(alloc, 3);
		t.emplace(alloc, 18);
		t.emplace(alloc, 10);
		t.emplace(alloc, 22);
		t.emplace(alloc, 8);
		t.emplace(alloc, 11);
		t.emplace(alloc, 26);

		VERIFY(tree_equal(t, {3, 7, 8, 10, 11, 18, 22, 26}));

		t.erase(alloc, hamon::next(t.begin(), 5));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {3, 7, 8, 10, 11, 22, 26}));

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

		t.emplace(alloc, 5);
		t.emplace(alloc, 2);
		t.emplace(alloc, 8);
		t.emplace(alloc, 1);
		t.emplace(alloc, 4);
		t.emplace(alloc, 7);
		t.emplace(alloc, 9);

		VERIFY(tree_equal(t, {1, 2, 4, 5, 7, 8, 9}));

		t.erase(alloc, hamon::next(t.begin(), 1));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 4, 5, 7, 8, 9}));

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

		t.emplace(alloc, 13);
		t.emplace(alloc, 8);
		t.emplace(alloc, 17);
		t.emplace(alloc, 1);
		t.emplace(alloc, 11);
		t.emplace(alloc, 15);
		t.emplace(alloc, 25);
		t.emplace(alloc, 6);
		t.emplace(alloc, 22);
		t.emplace(alloc, 27);

		VERIFY(tree_equal(t, {1, 6, 8, 11, 13, 15, 17, 22, 25, 27}));

		t.erase(alloc, hamon::next(t.begin(), 4));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 6, 8, 11, 15, 17, 22, 25, 27}));

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

		t.emplace(alloc, 13);
		t.emplace(alloc, 8);
		t.emplace(alloc, 17);
		t.emplace(alloc, 1);
		t.emplace(alloc, 11);
		t.emplace(alloc, 15);
		t.emplace(alloc, 25);
		t.emplace(alloc, 6);
		t.emplace(alloc, 22);
		t.emplace(alloc, 27);

		VERIFY(tree_equal(t, {1, 6, 8, 11, 13, 15, 17, 22, 25, 27}));

		t.erase(alloc, hamon::next(t.begin(), 2));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 6, 11, 13, 15, 17, 22, 25, 27}));

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

		t.emplace(alloc, 7);
		t.emplace(alloc, 3);
		t.emplace(alloc, 18);
		t.emplace(alloc, 10);
		t.emplace(alloc, 22);
		t.emplace(alloc, 8);
		t.emplace(alloc, 11);
		t.emplace(alloc, 26);

		VERIFY(tree_equal(t, {3, 7, 8, 10, 11, 18, 22, 26}));

		t.erase(alloc, hamon::next(t.begin(), 0));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {7, 8, 10, 11, 18, 22, 26}));

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

		t.emplace(alloc, 13);
		t.emplace(alloc, 8);
		t.emplace(alloc, 17);
		t.emplace(alloc, 1);
		t.emplace(alloc, 11);
		t.emplace(alloc, 15);
		t.emplace(alloc, 25);
		t.emplace(alloc, 6);
		t.emplace(alloc, 22);
		t.emplace(alloc, 27);

		VERIFY(tree_equal(t, {1, 6, 8, 11, 13, 15, 17, 22, 25, 27}));

		t.erase(alloc, hamon::next(t.begin(), 3));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {1, 6, 8, 13, 15, 17, 22, 25, 27}));

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

		t.emplace(alloc, 50);
		t.emplace(alloc, 30);
		t.emplace(alloc, 65);
		t.emplace(alloc, 15);
		t.emplace(alloc, 35);
		t.emplace(alloc, 55);
		t.emplace(alloc, 70);
		t.emplace(alloc, 68);
		t.emplace(alloc, 80);
		t.emplace(alloc, 10);
		//t.emplace(alloc,  0);
		t.emplace(alloc, 90);
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {10, 15, 30, 35, 50, 55, 65, 68, 70, 80, 90}));

		t.erase(alloc, hamon::next(t.begin(), 0));
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {15, 30, 35, 50, 55, 65, 68, 70, 80, 90}));

		t.erase(alloc, hamon::next(t.begin(), 4));
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {15, 30, 35, 50, 65, 68, 70, 80, 90}));

		t.erase(alloc, hamon::next(t.begin(), 1));
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {15, 35, 50, 65, 68, 70, 80, 90}));

		t.erase(alloc, hamon::next(t.begin(), 7));
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {15, 35, 50, 65, 68, 70, 80}));

		t.erase(alloc, hamon::next(t.begin(), 6));
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {15, 35, 50, 65, 68, 70}));

		t.erase(alloc, hamon::next(t.begin(), 2));
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {15, 35, 65, 68, 70}));

		t.erase(alloc, hamon::next(t.begin(), 1));
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {15, 65, 68, 70}));

		t.erase(alloc, hamon::next(t.begin(), 0));
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {65, 68, 70}));

		t.erase(alloc, hamon::next(t.begin(), 0));
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {68, 70}));

		t.erase(alloc, hamon::next(t.begin(), 0));
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {70}));

		t.erase(alloc, hamon::next(t.begin(), 0));
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {}));

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

		t.emplace(alloc, 50);
		t.emplace(alloc, 30);
		t.emplace(alloc, 65);
		t.emplace(alloc, 15);
		t.emplace(alloc, 35);
		t.emplace(alloc, 55);
		t.emplace(alloc, 70);
		t.emplace(alloc, 80);
		t.emplace(alloc, 10);
		t.emplace(alloc, 18);
		t.emplace(alloc,  0);
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {0, 10, 15, 18, 30, 35, 50, 55, 65, 70, 80}));

		t.erase(alloc, hamon::next(t.begin(), 10));
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {0, 10, 15, 18, 30, 35, 50, 55, 65, 70}));

		t.erase(alloc, hamon::next(t.begin(), 5));
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {0, 10, 15, 18, 30, 50, 55, 65, 70}));

		t.erase(alloc, hamon::next(t.begin(), 6));
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {0, 10, 15, 18, 30, 50, 65, 70}));

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

		t.emplace(alloc, 10);
		t.emplace(alloc, 5);
		t.emplace(alloc, 30);
		t.emplace(alloc, 2);
		t.emplace(alloc, 9);
		t.emplace(alloc, 25);
		t.emplace(alloc, 40);
		t.emplace(alloc, 38);
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {2, 5, 9, 10, 25, 30, 38, 40}));

		t.erase(alloc, hamon::next(t.begin(), 5));
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {2, 5, 9, 10, 25, 38, 40}));

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

		t.emplace(alloc, 10);
		t.emplace(alloc, 5);
		t.emplace(alloc, 20);
		t.emplace(alloc, 15);
		t.emplace(alloc, 30);
		t.emplace(alloc, 40);
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {5, 10, 15, 20, 30, 40}));

		t.erase(alloc, hamon::next(t.begin(), 5));
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {5, 10, 15, 20, 30}));

		t.erase(alloc, hamon::next(t.begin(), 2));
		VERIFY(tree_invariant(t));
		VERIFY(tree_equal(t, {5, 10, 20, 30}));

		t.clear(alloc);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 1);
		VERIFY(tree_equal(t, {}));
	}

	return true;
}

HAMON_CXX20_CONSTEXPR bool test_multi()
{
	using Tree = hamon::detail::red_black_tree<true, int>;
	using Node = typename Tree::node_type;

	hamon::allocator<Node> alloc;

	{
		Tree t;
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 1);
		VERIFY(tree_equal(t, {}));

		t.emplace(alloc, 10);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10}));

		t.emplace(alloc, 10);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10, 10}));

		t.emplace(alloc, 5);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {5, 10, 10}));

		t.emplace(alloc, 15);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 10, 10, 15}));

		t.emplace(alloc, 5);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 5, 10, 10, 15}));

		t.emplace(alloc, 6);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 5, 6, 10, 10, 15}));

		t.emplace(alloc, 10);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 5, 6, 10, 10, 10, 15}));

		t.emplace(alloc, 12);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 5, 6, 10, 10, 10, 12, 15}));

		t.emplace(alloc, 15);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 5, 6, 10, 10, 10, 12, 15, 15}));

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

		t.emplace_hint(alloc, t.end(), 10);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10}));

		t.emplace_hint(alloc, t.end(), 10);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {10, 10}));

		t.emplace_hint(alloc, t.end(), 5);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 2);
		VERIFY(tree_equal(t, {5, 10, 10}));

		t.emplace_hint(alloc, t.begin(), 5);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 5, 10, 10}));

		t.emplace_hint(alloc, t.begin(), 7);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 5, 7, 10, 10}));

		t.emplace_hint(alloc, hamon::next(t.begin(), 2), 7);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 5, 7, 7, 10, 10}));

		t.emplace_hint(alloc, hamon::next(t.begin(), 2), 8);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 5, 7, 7, 8, 10, 10}));

		t.emplace_hint(alloc, hamon::next(t.begin(), 1), 6);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {5, 5, 6, 7, 7, 8, 10, 10}));

		t.emplace_hint(alloc, hamon::next(t.begin(), 1), 4);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {4, 5, 5, 6, 7, 7, 8, 10, 10}));

		t.emplace_hint(alloc, hamon::next(t.begin(), 7), 9);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {4, 5, 5, 6, 7, 7, 8, 9, 10, 10}));

		t.emplace_hint(alloc, hamon::next(t.begin(), 7), 10);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {4, 5, 5, 6, 7, 7, 8, 9, 10, 10, 10}));

		t.emplace(alloc, 0);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 3);
		VERIFY(tree_equal(t, {0, 4, 5, 5, 6, 7, 7, 8, 9, 10, 10, 10}));

		t.emplace(alloc, 1);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {0, 1, 4, 5, 5, 6, 7, 7, 8, 9, 10, 10, 10}));

		t.emplace(alloc, 2);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {0, 1, 2, 4, 5, 5, 6, 7, 7, 8, 9, 10, 10, 10}));

		t.emplace(alloc, 2);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {0, 1, 2, 2, 4, 5, 5, 6, 7, 7, 8, 9, 10, 10, 10}));

		t.emplace(alloc, 3);
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {0, 1, 2, 2, 3, 4, 5, 5, 6, 7, 7, 8, 9, 10, 10, 10}));

		t.erase(alloc, hamon::next(t.begin(), 15));
		VERIFY(tree_invariant(t));
		VERIFY(tree_black_height(t) == 4);
		VERIFY(tree_equal(t, {0, 1, 2, 2, 3, 4, 5, 5, 6, 7, 7, 8, 9, 10, 10}));

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
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test_unique());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test_multi());
}

}	// namespace red_black_tree_test

}	// namespace hamon_container_test
