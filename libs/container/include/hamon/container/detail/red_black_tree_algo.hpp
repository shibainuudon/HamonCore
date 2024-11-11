/**
 *	@file	red_black_tree_algo.hpp
 *
 *	@brief	red_black_tree_algo の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_RED_BLACK_TREE_ALGO_HPP
#define HAMON_CONTAINER_DETAIL_RED_BLACK_TREE_ALGO_HPP

//#include <hamon/container/detail/red_black_tree_node.hpp>
//
//#include <hamon/cstddef/ptrdiff_t.hpp>
//#include <hamon/cstddef/size_t.hpp>
//#include <hamon/detail/overload_priority.hpp>
//#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/iterator/prev.hpp>
//#include <hamon/iterator/ranges/distance.hpp>
//#include <hamon/memory/allocator_traits.hpp>
//#include <hamon/memory/pointer_traits.hpp>
#include <hamon/pair/pair.hpp>
//#include <hamon/type_traits/conditional.hpp>
//#include <hamon/type_traits/enable_if.hpp>
//#include <hamon/type_traits/is_invocable.hpp>
//#include <hamon/utility/exchange.hpp>
//#include <hamon/utility/forward.hpp>
//#include <hamon/utility/move.hpp>
//#include <hamon/utility/swap.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>

namespace hamon
{

namespace detail
{

template <typename Node>
struct red_black_tree_algo
{
	static HAMON_CXX14_CONSTEXPR Node*
	root(Node* p) noexcept
	{
		HAMON_ASSERT(p != nullptr);

		while (p->m_parent != nullptr)
		{
			p = p->m_parent;
		}

		return p;
	}

	static HAMON_CXX14_CONSTEXPR Node*
	leftmost(Node* p) noexcept
	{
		HAMON_ASSERT(p != nullptr);

		while (p->m_left != nullptr)
		{
			p = p->m_left;
		}

		return p;
	}

	static HAMON_CXX14_CONSTEXPR Node*
	rightmost(Node* p) noexcept
	{
		HAMON_ASSERT(p != nullptr);

		while (p->m_right != nullptr)
		{
			p = p->m_right;
		}

		return p;
	}

	static HAMON_CXX14_CONSTEXPR Node*
	next(Node* p) noexcept
	{
		HAMON_ASSERT(p != nullptr);

		if (p->m_right != nullptr)
		{
			return leftmost(p->m_right);
		}

		while (p->is_right_child())
		{
			p = p->m_parent;
		}

		return p->m_parent;
	}

	static HAMON_CXX14_CONSTEXPR Node*
	prev(Node* p) noexcept
	{
		HAMON_ASSERT(p != nullptr);

		if (p->m_left != nullptr)
		{
			return rightmost(p->m_left);
		}

		while (p->is_left_child())
		{
			p = p->m_parent;
		}

		return p->m_parent;
	}

	enum class ChildDir
	{
		Left,
		Right,
		None,
	};


	template <typename T, typename Compare>
	static HAMON_CXX14_CONSTEXPR hamon::pair<Node*, ChildDir>
	lower_bound(Node* p, T const& x, Compare const& comp) noexcept
	{
		HAMON_ASSERT(p != nullptr);

		for (;;)
		{
			if (!comp(p->m_value, x))	// x <= p->m_value
			{
				if (p->m_left == nullptr)
				{
					return {p, ChildDir::Left};
				}
				else
				{
					p = p->m_left;
				}
			}
			else
			{
				if (p->m_right == nullptr)
				{
					return {p, ChildDir::Right};
				}
				else
				{
					p = p->m_right;
				}
			}
		}
	}

	template <typename T, typename Compare>
	static HAMON_CXX14_CONSTEXPR hamon::pair<Node*, ChildDir>
	upper_bound(Node* p, T const& x, Compare const& comp) noexcept
	{
		HAMON_ASSERT(p != nullptr);

		for (;;)
		{
			if (comp(x, p->m_value))	// x < p->m_value
			{
				if (p->m_left == nullptr)
				{
					return {p, ChildDir::Left};
				}
				else
				{
					p = p->m_left;
				}
			}
			else
			{
				if (p->m_right == nullptr)
				{
					return {p, ChildDir::Right};
				}
				else
				{
					p = p->m_right;
				}
			}
		}
	}

	static HAMON_CXX14_CONSTEXPR void
	rotate_left(Node* p) noexcept
	{
		HAMON_ASSERT(p != nullptr);
		HAMON_ASSERT(p->m_right != nullptr);
		Node* y = p->m_right;
		p->m_right = y->m_left;
		if (p->m_right != nullptr)
		{
			p->m_right->m_parent = p;
		}
		y->m_parent = p->m_parent;
		if (p->m_parent)
		{
			if (p->is_left_child())
			{
				p->m_parent->m_left = y;
			}
			else
			{
				p->m_parent->m_right = y;
			}
		}
		y->m_left = p;
		p->m_parent = y;
	}

	static HAMON_CXX14_CONSTEXPR void
	rotate_right(Node* p) noexcept
	{
		HAMON_ASSERT(p != nullptr);
		HAMON_ASSERT(p->m_left != nullptr);
		Node* y = p->m_left;
		p->m_left = y->m_right;
		if (p->m_left != nullptr)
		{
			p->m_left->m_parent = p;
		}
		y->m_parent = p->m_parent;
		if (p->m_parent)
		{
			if (p->is_left_child())
			{
				p->m_parent->m_left = y;
			}
			else
			{
				p->m_parent->m_right = y;
			}
		}
		y->m_right = p;
		p->m_parent = y;
	}

	static HAMON_CXX14_CONSTEXPR void
	balance(Node* p, Node*& root) noexcept
	{
		HAMON_ASSERT(p != nullptr);
		HAMON_ASSERT(p->is_red());

		if (p->parent() == nullptr)
		{
			p->m_color = Node::Color::Black;
			return;
		}

		if (p->m_parent->is_black())
		{
			return;
		}

		if (p->parent()->parent() == nullptr)
		{
			return;
		}

		auto parent = p->parent();
		auto grandparent = parent->parent();
		auto uncle = p->uncle();
		if (uncle && uncle->is_red())
		{
			parent->m_color = Node::Color::Black;
			uncle->m_color = Node::Color::Black;
			grandparent->m_color = Node::Color::Red;
			balance(grandparent, root);
		}
		else if (uncle == nullptr || uncle->is_black())
		{
			if (parent->is_left_child())
			{
				if (p->is_right_child())
				{
					rotate_left(parent);
					hamon::swap(p, parent);
				}

				rotate_right(grandparent);
			}
			else
			{
				if (p->is_left_child())
				{
					rotate_right(parent);
					hamon::swap(p, parent);
				}

				rotate_left(grandparent);
			}

			parent->m_color = Node::Color::Black;
			grandparent->m_color = Node::Color::Red;
			if (root == grandparent)
			{
				root = parent;
			}
		}
	}

	template <typename Compare, typename T>
	static HAMON_CXX14_CONSTEXPR hamon::pair<Node*, ChildDir>
	find_to_insert(Compare const& comp, T const& value, Node* root, bool multi) noexcept
	{
		HAMON_ASSERT(root != nullptr);

		if (multi)
		{
			return upper_bound(root, value, comp);
		}

		auto p = root;
		for (;;)
		{
			HAMON_ASSERT(p != nullptr);

			if (comp(value, p->m_value))
			{
				if (p->m_left == nullptr)
				{
					return {p, ChildDir::Left};
				}
				else
				{
					p = p->m_left;
				}
			}
			else if (comp(p->m_value, value))
			{
				if (p->m_right == nullptr)
				{
					return {p, ChildDir::Right};
				}
				else
				{
					p = p->m_right;
				}
			}
			else
			{
				return {p, ChildDir::None};
			}
		}
	}

	template <typename Compare, typename T, typename Iterator>
	static HAMON_CXX14_CONSTEXPR hamon::pair<Node*, ChildDir>
	find_to_insert_hint(Compare const& comp, T const& value, Node* root, bool multi, Iterator hint, Iterator first, Iterator last) noexcept
	{
		if (multi)
		{
			if (hint == first)
			{
				if (!comp(*hint, value))	// (value <= *hint)
				{
					return {const_cast<Node*>(hint.m_node), ChildDir::Left};
				}

				return lower_bound(root, value, comp);
			}
			else if (hint == last)
			{
				auto prev = hamon::prev(hint);
				if (!comp(value, *prev))	// (value >= *prev)
				{
					return {const_cast<Node*>(prev.m_node), ChildDir::Right};
				}

				return upper_bound(root, value, comp);
			}
			else
			{
				if (!comp(*hint, value))	// (value <= *hint)
				{
					auto prev = hamon::prev(hint);
					if (!comp(value, *prev))	// (value >= *prev)
					{
						// *prev <= value && value <= *hint
						if (prev.m_node->m_right == nullptr)
						{
							return {const_cast<Node*>(prev.m_node), ChildDir::Right};
						}
						else
						{
							return {const_cast<Node*>(hint.m_node), ChildDir::Left};
						}
					}

					return upper_bound(root, value, comp);
				}
				else	// (value > *hint)
				{
					auto next = hamon::next(hint);
					if (next == last || !comp(*next, value))	// (value <= *next)
					{
						// *hint < value && value <= *next
						if (hint.m_node->m_right == nullptr)
						{
							return {const_cast<Node*>(hint.m_node), ChildDir::Right};
						}
						else
						{
							return {const_cast<Node*>(next.m_node), ChildDir::Left};
						}
					}

					return lower_bound(root, value, comp);
				}
			}
		}
		else
		{
			if (hint == first)
			{
				if (comp(value, *hint))		// (value < *hint)
				{
					return {const_cast<Node*>(hint.m_node), ChildDir::Left};
				}
			}
			else if (hint == last)
			{
				auto prev = hamon::prev(hint);
				if (comp(*prev, value))		// (value > *prev)
				{
					return {const_cast<Node*>(prev.m_node), ChildDir::Right};
				}
			}
			else
			{
				if (comp(value, *hint))		// (value < *hint)
				{
					auto prev = hamon::prev(hint);
					if (comp(*prev, value))		// (value > *prev)
					{
						// *prev < value && value < *hint
						if (prev.m_node->m_right == nullptr)
						{
							return {const_cast<Node*>(prev.m_node), ChildDir::Right};
						}
						else
						{
							return {const_cast<Node*>(hint.m_node), ChildDir::Left};
						}
					}
				}
				else if (comp(*hint, value))	// (value > *hint)
				{
					auto next = hamon::next(hint);
					if (next == last || comp(value, *next))	// (value < *next)
					{
						// *hint < value && value < *next
						if (hint.m_node->m_right == nullptr)
						{
							return {const_cast<Node*>(hint.m_node), ChildDir::Right};
						}
						else
						{
							return {const_cast<Node*>(next.m_node), ChildDir::Left};
						}
					}
				}
			}
		}

		return find_to_insert(comp, value, root, multi);
	}

	static HAMON_CXX14_CONSTEXPR void
	insert_at(Node* p, ChildDir insert_to, Node* new_node, Node*& root, Node*& leftmost, Node*& rightmost) noexcept
	{
		HAMON_ASSERT(p != nullptr);
		HAMON_ASSERT(new_node != nullptr);

		new_node->m_color = Node::Color::Red;
		new_node->m_parent = p;

		if (insert_to == ChildDir::Left)
		{
			if (leftmost == p)
			{
				leftmost = new_node;
			}
			p->m_left = new_node;
		}
		else
		{
			if (rightmost == p)
			{
				rightmost = new_node;
			}
			p->m_right = new_node;
		}

		balance(new_node, root);
	}

	static HAMON_CXX14_CONSTEXPR Node*
	erase(Node* root, Node* z)
	{
		//_LIBCPP_ASSERT_INTERNAL(root != nullptr, "Root node should not be null");
		//_LIBCPP_ASSERT_INTERNAL(z != nullptr, "The node to remove should not be null");
		//_LIBCPP_ASSERT_INTERNAL(std::__tree_invariant(root), "The tree invariants should hold");
		// z will be removed from the tree.  Client still needs to destruct/deallocate it
		// y is either z, or if z has two children, __tree_next(z).
		// y will have at most one child.
		// y will be the initial hole in the tree (make the hole at a leaf)
		Node* y = (z->m_left == nullptr || z->m_right == nullptr) ? z : z->next()/*std::__tree_next(z)*/;
		// x is y's possibly null single child
		Node* x = y->m_left != nullptr ? y->m_left : y->m_right;
		// w is x's possibly null uncle (will become x's sibling)
		Node* w = nullptr;
		// link x to y's parent, and find w
		if (x != nullptr)
		{
			x->m_parent = y->m_parent;
		}

		if (y->is_left_child())//std::__tree_is_left_child(y))
		{
			y->m_parent->m_left = x;
			//if (y != root)
			{
				w = y->m_parent->m_right;
			}
			//else
			//{
			//	root = x; // w == nullptr
			//}
		}
		else if (y->is_right_child())
		{
			y->m_parent->m_right = x;
			// y can't be root if it is a right child
			w = y->m_parent->m_left;
		}
		else
		{
			root = x;
			// w == nullptr
		}

		bool removed_black = y->is_black();
		// If we didn't remove z, do so now by splicing in y for z,
		//    but copy z's color.  This does not impact x or w.
		if (y != z)
		{
			// z->m_left != nulptr but z->m_right might == x == nullptr
			y->m_parent = z->m_parent;
			if (z->is_left_child())//std::__tree_is_left_child(z))
			{
				y->m_parent->m_left = y;
			}
			else if (z->is_right_child())
			{
				y->m_parent->m_right = y;
			}
			y->m_left = z->m_left;
			y->m_left->m_parent = y;
			y->m_right = z->m_right;
			if (y->m_right != nullptr)
			{
				y->m_right->m_parent = y;
			}
			y->m_color = z->m_color;
			if (root == z)
			{
				root = y;
			}
		}


		// There is no need to rebalance if we removed a red, or if we removed
		//     the last node.
		if (removed_black && root != nullptr)
		{
			// Rebalance:
			// x has an implicit black color (transferred from the removed __y)
			//    associated with it, no matter what its color is.
			// If x is root (in which case it can't be null), it is supposed
			//    to be black anyway, and if it is doubly black, then the double
			//    can just be ignored.
			// If x is red (in which case it can't be null), then it can absorb
			//    the implicit black just by setting its color to black.
			// Since __y was black and only had one child (which x points to), x
			//   is either red with no children, else null, otherwise __y would have
			//   different black heights under left and right pointers.
			// if (x == root || x != nullptr && !x->__is_black_)
			if (x != nullptr)
			{
				//x->__is_black_ = true;
				x->m_color = Node::Color::Black;
			}
			else
			{
				//  Else x isn't root, and is "doubly black", even though it may
				//     be null.  w can not be null here, else the parent would
				//     see a black height >= 2 on the x side and a black height
				//     of 1 on the w side (w must be a non-null black or a red
				//     with a non-null black child).
				while (true)
				{
					if (!w->is_left_child()/*std::__tree_is_left_child(w)*/) // if x is left child
					{
						if (!w->is_black())
						{
							w->m_color = Node::Color::Black;
							w->m_parent->m_color = Node::Color::Red;//__is_black_ = false;
							rotate_left(w->m_parent);//std::__tree_left_rotate(w->m_parent);
							// x is still valid
							// reset root only if necessary
							if (root == w->m_left)
							{
								root = w;
							}
							// reset sibling, and it still can't be null
							w = w->m_left->m_right;
						}
						// w->__is_black_ is now true, w may have null children
						if ((w->m_left == nullptr || w->m_left->is_black()) &&
							(w->m_right == nullptr || w->m_right->is_black()))
						{
							w->m_color = Node::Color::Red;//__is_black_ = false;
							x              = w->m_parent;
							// x can no longer be null
							if (x == root || !x->is_black())
							{
								x->m_color = Node::Color::Black;//__is_black_ = true;
								break;
							}
							// reset sibling, and it still can't be null
							w = x->is_left_child()/*std::__tree_is_left_child(x)*/ ? x->m_parent->m_right : x->m_parent->m_left;
							// continue;
						}
						else // w has a red child
						{
							if (w->m_right == nullptr || w->m_right->is_black())
							{
								// w left child is non-null and red
								w->m_left->m_color = Node::Color::Black;//__is_black_ = true;
								w->m_color = Node::Color::Red;//__is_black_          = false;
								rotate_right(w);//std::__tree_right_rotate(w);
								// w is known not to be root, so root hasn't changed
								// reset sibling, and it still can't be null
								w = w->m_parent;
							}
							// w has a right red child, left child may be null
							w->m_color                    = w->m_parent->m_color;
							w->m_parent->m_color = Node::Color::Black;//__is_black_ = true;
							w->m_right->m_color = Node::Color::Black;//__is_black_          = true;
							rotate_left(w->m_parent);//std::__tree_left_rotate(w->m_parent);
							break;
						}
					}
					else
					{
						if (!w->is_black())
						{
							w->m_color = Node::Color::Black;//__is_black_                    = true;
							w->m_parent->m_color = Node::Color::Red;//__is_black_ = false;
							rotate_right(w->m_parent);//std::__tree_right_rotate(w->m_parent);
							// x is still valid
							// reset root only if necessary
							if (root == w->m_right)
							{
								root = w;
							}
							// reset sibling, and it still can't be null
							w = w->m_right->m_left;
						}
						// w->__is_black_ is now true, w may have null children
						if ((w->m_left == nullptr || w->m_left->is_black()) &&
							(w->m_right == nullptr || w->m_right->is_black()))
						{
							w->m_color = Node::Color::Red;//__is_black_ = false;
							x              = w->m_parent;
							// x can no longer be null
							if (!x->is_black() || x == root || x->m_parent == nullptr)
							{
								x->m_color = Node::Color::Black;//__is_black_ = true;
								break;
							}
							// reset sibling, and it still can't be null
							w = x->is_left_child()/*std::__tree_is_left_child(x)*/ ? x->m_parent->m_right : x->m_parent->m_left;
							// continue;
						}
						else // w has a red child
						{
							if (w->m_left == nullptr || w->m_left->is_black())
							{
								// w right child is non-null and red
								w->m_right->m_color = Node::Color::Black;//__is_black_ = true;
								w->m_color = Node::Color::Red;//__is_black_           = false;
								rotate_left(w);//std::__tree_left_rotate(w);
								// w is known not to be root, so root hasn't changed
								// reset sibling, and it still can't be null
								w = w->m_parent;
							}
							// w has a left red child, right child may be null
							w->m_color = w->m_parent->m_color;
							w->m_parent->m_color = Node::Color::Black;//__is_black_ = true;
							w->m_left->m_color = Node::Color::Black;//__is_black_           = true;
							rotate_right(w->m_parent);//std::__tree_right_rotate(w->m_parent);
							break;
						}
					}
				}
			}
		}

		z->m_parent = nullptr;
		z->m_left = nullptr;
		z->m_right = nullptr;

		// TODO
		return root;
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_RED_BLACK_TREE_ALGO_HPP
