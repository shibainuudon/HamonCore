﻿/**
 *	@file	red_black_tree.hpp
 *
 *	@brief	red_black_tree の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_RED_BLACK_TREE_HPP
#define HAMON_CONTAINER_DETAIL_RED_BLACK_TREE_HPP

#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/iterator/prev.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/pointer_traits.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/utility/exchange.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
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

		while (p->is_rightchild())
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

		while (p->is_leftchild())
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
		Node* y  = p->m_right;
		p->m_right = y->m_left;
		if (p->m_right != nullptr)
		{
			p->m_right->m_parent = p;
		}
		y->m_parent = p->m_parent;
		if (p->m_parent)
		{
			if (p->is_leftchild())
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
			if (p->is_leftchild())
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
			if (parent->is_leftchild())
			{
				if (p->is_rightchild())
				{
					rotate_left(parent);
					hamon::swap(p, parent);
				}

				rotate_right(grandparent);
			}
			else
			{
				if (p->is_leftchild())
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

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。
	template <typename Allocator, typename... Args>
	static HAMON_CXX14_CONSTEXPR Node*
	construct_node(Allocator& alloc, Args&&... args)
	{
		using AllocTraits = hamon::allocator_traits<Allocator>;
		auto node = AllocTraits::allocate(alloc, 1);	// may throw
		AllocTraits::construct(alloc, node, hamon::forward<Args>(args)...);	// may throw
		return node;
	}
HAMON_WARNING_POP()

	template <typename Allocator>
	static HAMON_CXX14_CONSTEXPR void
	destruct_node(Allocator& alloc, Node* p)
	{
		using AllocTraits = hamon::allocator_traits<Allocator>;
		AllocTraits::destroy(alloc, p);
		AllocTraits::deallocate(alloc, p, 1);
	}

	template <typename Allocator>
	static HAMON_CXX14_CONSTEXPR void
	clear(Allocator& alloc, Node* p) noexcept
	{
		if (p == nullptr)
		{
			return;
		}

		clear(alloc, p->m_left);
		clear(alloc, p->m_right);
		destruct_node(alloc, p);
	}
};

template <typename T>
struct red_black_tree_node
{
private:
	using Node = red_black_tree_node;
	using Algo = red_black_tree_algo<Node>;

	friend struct red_black_tree_algo<Node>;

	enum class Color : char
	{
		Black,
		Red,
	};

	Node* m_parent{};
	Node* m_left{};
	Node* m_right{};
	Color m_color = Color::Black;
	T m_value;

public:
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR
	red_black_tree_node(Args&&... args)
		: m_value(hamon::forward<Args>(args)...)
	{}

	HAMON_CXX11_CONSTEXPR Node*
	parent() const noexcept
	{
		return m_parent;
	}

	HAMON_CXX11_CONSTEXPR Node*
	left() const noexcept
	{
		return m_left;
	}

	HAMON_CXX11_CONSTEXPR Node*
	right() const noexcept
	{
		return m_right;
	}

	// 兄弟ノード(親の子ノードのうち自分ではない方)を返す
	// 親ノードがnullの場合はnullを返す
	HAMON_CXX14_CONSTEXPR Node*
	sibling() const noexcept
	{
		if (m_parent == nullptr)
		{
			return nullptr;
		}

		if (is_leftchild())
		{
			return m_parent->m_right;
		}
		else
		{
			return m_parent->m_left;
		}
	}

	// 叔父ノード(親の兄弟ノード)を返す
	// 親ノードか祖父ノードがnullの場合はnullを返す
	HAMON_CXX14_CONSTEXPR Node*
	uncle() const noexcept
	{
		if (m_parent == nullptr)
		{
			return nullptr;
		}

		return m_parent->sibling();
	}

	HAMON_CXX14_CONSTEXPR T&
	value() noexcept
	{
		return m_value;
	}

	HAMON_CXX11_CONSTEXPR T const&
	value() const noexcept
	{
		return m_value;
	}

	HAMON_CXX11_CONSTEXPR bool
	is_black() const noexcept
	{
		return m_color == Color::Black;
	}

	HAMON_CXX11_CONSTEXPR bool
	is_red() const noexcept
	{
		return m_color == Color::Red;
	}

	HAMON_CXX11_CONSTEXPR bool
	is_leftchild() const noexcept
	{
		return m_parent != nullptr && m_parent->m_left == this;
	}

	HAMON_CXX11_CONSTEXPR bool
	is_rightchild() const noexcept
	{
		return m_parent != nullptr && m_parent->m_right == this;
	}

	HAMON_CXX14_CONSTEXPR Node*
	root() const noexcept
	{
		return Algo::root(const_cast<Node*>(this));
	}

	HAMON_CXX14_CONSTEXPR Node*
	leftmost() const noexcept
	{
		return Algo::leftmost(const_cast<Node*>(this));
	}

	HAMON_CXX14_CONSTEXPR Node*
	rightmost() const noexcept
	{
		return Algo::rightmost(const_cast<Node*>(this));
	}

	HAMON_CXX14_CONSTEXPR Node*
	next() const noexcept
	{
		return Algo::next(const_cast<Node*>(this));
	}

	HAMON_CXX14_CONSTEXPR Node*
	prev() const noexcept
	{
		return Algo::prev(const_cast<Node*>(this));
	}
};

template <typename Tree, bool Const>
struct red_black_tree_iterator
{
public:
	using iterator_category = hamon::bidirectional_iterator_tag;
	using value_type        = typename Tree::value_type;
	using difference_type   = typename Tree::difference_type;
	using pointer           = hamon::conditional_t<Const, value_type const*, value_type*>;
	using reference         = hamon::conditional_t<Const, value_type const&, value_type&>;

private:
	using Node = typename Tree::node_type;
	using NodePointer = hamon::conditional_t<Const, Node const*, Node*>;

	Tree const* m_tree;
	NodePointer m_node;

public:
	HAMON_CXX11_CONSTEXPR
	red_black_tree_iterator() HAMON_NOEXCEPT
		: m_tree(nullptr)
		, m_node(nullptr)
	{}

	explicit HAMON_CXX11_CONSTEXPR
	red_black_tree_iterator(Tree const* tree, NodePointer node) HAMON_NOEXCEPT
		: m_tree(tree)
		, m_node(node)
	{}

	template <bool C, typename = hamon::enable_if_t<C == Const || Const>>
	HAMON_CXX11_CONSTEXPR
	red_black_tree_iterator(red_black_tree_iterator<Tree, C> const& i) HAMON_NOEXCEPT
		: m_tree(i.m_tree)
		, m_node(i.m_node)
	{}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	reference operator*() const HAMON_NOEXCEPT
	{
#if HAMON_CXX_STANDARD >= 14
		HAMON_ASSERT(m_node != nullptr);
#endif
		return m_node->value();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	pointer operator->() const HAMON_NOEXCEPT
	{
		return hamon::pointer_traits<pointer>::pointer_to(**this);
	}

	HAMON_CXX14_CONSTEXPR red_black_tree_iterator&
	operator++() HAMON_NOEXCEPT
	{
		HAMON_ASSERT(m_tree != nullptr);
		if (m_node == nullptr)
		{
			m_node = m_tree->leftmost();
		}
		else
		{
			m_node = m_node->next();
		}
		return *this;
	}

	HAMON_CXX14_CONSTEXPR red_black_tree_iterator
	operator++(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;
		++*this;
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR red_black_tree_iterator&
	operator--() HAMON_NOEXCEPT
	{
		HAMON_ASSERT(m_tree != nullptr);
		if (m_node == nullptr)
		{
			m_node = m_tree->rightmost();
		}
		else
		{
			m_node = m_node->prev();
		}
		return *this;
	}

	HAMON_CXX14_CONSTEXPR red_black_tree_iterator
	operator--(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;
		--*this;
		return tmp;
	}

private:
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator==(red_black_tree_iterator const& lhs, red_black_tree_iterator const& rhs) HAMON_NOEXCEPT
	{
		return lhs.m_node == rhs.m_node;
	}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator!=(red_black_tree_iterator const& lhs, red_black_tree_iterator const& rhs) HAMON_NOEXCEPT
	{
		return !(lhs == rhs);
	}
#endif

private:
	friend struct red_black_tree_iterator<Tree, !Const>;
	friend struct red_black_tree_algo<Node>;
};

template <bool Multi, typename ValueType, typename KeyType = ValueType, typename SizeType = hamon::size_t, typename DifferenceType = hamon::ptrdiff_t>
struct red_black_tree
{
public:
	using value_type = ValueType;
	using key_type = KeyType;
	using size_type = SizeType;
	using difference_type = DifferenceType;
private:
	using Node = red_black_tree_node<value_type>;
	using Algo = red_black_tree_algo<Node>;
public:
	using node_type = Node;
	using iterator       = hamon::detail::red_black_tree_iterator<red_black_tree, false>;
	using const_iterator = hamon::detail::red_black_tree_iterator<red_black_tree, true>;

private:
	Node* m_root{};
	Node* m_leftmost{};
	Node* m_rightmost{};
	size_type m_size{};

public:
	red_black_tree() = default;

	red_black_tree(red_black_tree const&) = delete;

	HAMON_CXX14_CONSTEXPR
	red_black_tree(red_black_tree&& x)
		: m_root(hamon::exchange(x.m_root, nullptr))
		, m_leftmost(hamon::exchange(x.m_leftmost, nullptr))
		, m_rightmost(hamon::exchange(x.m_rightmost, nullptr))
		, m_size(hamon::exchange(x.m_size, size_type{}))
	{}

	red_black_tree& operator=(red_black_tree const&) = delete;

	HAMON_CXX14_CONSTEXPR
	red_black_tree& operator=(red_black_tree&& x) HAMON_NOEXCEPT
	{
		red_black_tree(hamon::move(x)).swap(*this);
		return *this;
	}

	HAMON_CXX14_CONSTEXPR void
	swap(red_black_tree& x) HAMON_NOEXCEPT
	{
		hamon::swap(m_root,      x.m_root);
		hamon::swap(m_leftmost,  x.m_leftmost);
		hamon::swap(m_rightmost, x.m_rightmost);
		hamon::swap(m_size,      x.m_size);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR Node*
	root() const noexcept
	{
		return m_root;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR Node*
	leftmost() const noexcept
	{
		return m_leftmost;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR Node*
	rightmost() const noexcept
	{
		return m_rightmost;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type
	size() const noexcept
	{
		return m_size;
	}

private:
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR
	iterator to_iterator(Node* p) const noexcept
	{
		return iterator{this, p};
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	const_iterator to_const_iterator(Node* p) const noexcept
	{
		return const_iterator{this, p};
	}

public:
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR
	iterator begin() const noexcept
	{
		return to_iterator(m_leftmost);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	const_iterator cbegin() const noexcept
	{
		return to_const_iterator(m_leftmost);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR
	iterator end() const noexcept
	{
		return to_iterator(nullptr);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	const_iterator cend() const noexcept
	{
		return to_const_iterator(nullptr);
	}

	template <typename Compare, typename K>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR iterator
	find(Compare const& comp, K const& x) const
	{
		auto r = this->lower_bound(comp, x);
		if (r != this->end() && !comp(x, *r))
		{
			return r;
		}
		return this->end();
	}

	template <typename Compare, typename K>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR size_type
	count(Compare const& comp, K const& x) const
	{
		if (Multi)
		{
			auto r = this->equal_range(comp, x);
			return static_cast<size_type>(
				hamon::ranges::distance(r.first, r.second));
		}
		else
		{
			return this->contains(comp, x) ? 1 : 0;
		}
	}

	template <typename Compare, typename K>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool
	contains(Compare const& comp, K const& x) const
	{
		return this->find(comp, x) != this->end();
	}

	template <typename Compare, typename K>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR iterator
	lower_bound(Compare const& comp, K const& x) const
	{
		if (m_root == nullptr)
		{
			return this->end();
		}

		auto r = Algo::lower_bound(m_root, x, comp);
		if (r.second == Algo::ChildDir::Right)
		{
			return to_iterator(Algo::next(r.first));
		}
		return to_iterator(r.first);
	}

	template <typename Compare, typename K>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR iterator
	upper_bound(Compare const& comp, K const& x) const
	{
		if (m_root == nullptr)
		{
			return this->end();
		}

		auto r = Algo::upper_bound(m_root, x, comp);
		if (r.second == Algo::ChildDir::Right)
		{
			return to_iterator(Algo::next(r.first));
		}
		return to_iterator(r.first);
	}

	template <typename Compare, typename K>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR
	pair<iterator, iterator>
	equal_range(Compare const& comp, K const& x) const
	{
		// TODO unique な場合はもっと効率的に実装できる
		return
		{
			this->lower_bound(comp, x),
			this->upper_bound(comp, x)
		};
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

	template <typename Compare, typename Allocator, typename K, typename... Args>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	try_emplace(Compare const& comp, Allocator& alloc, K const& k, Args&&... args)
	{
		if (m_root == nullptr)
		{
			auto new_node = Algo::construct_node(alloc, hamon::forward<Args>(args)...);	// may throw
			m_root = new_node;
			m_leftmost = new_node;
			m_rightmost = new_node;
			m_size = 1;
			return {to_iterator(new_node), true};
		}

		auto r = Algo::find_to_insert(comp, k, m_root, Multi);
		if (r.second != Algo::ChildDir::None)
		{
			auto new_node = Algo::construct_node(alloc, hamon::forward<Args>(args)...);	// may throw
			Algo::insert_at(r.first, r.second, new_node, m_root, m_leftmost, m_rightmost);
			++m_size;
			return {to_iterator(new_node), true};
		}
		else
		{
			return {to_iterator(r.first), false};
		}
	}

	template <typename Compare, typename Allocator, typename K, typename... Args>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	try_emplace_hint(Compare const& comp, Allocator& alloc, const_iterator hint, K const& k, Args&&... args)
	{
		if (m_root == nullptr)
		{
			auto new_node = Algo::construct_node(alloc, hamon::forward<Args>(args)...);	// may throw
			m_root = new_node;
			m_leftmost = new_node;
			m_rightmost = new_node;
			m_size = 1;
			return {to_iterator(new_node), true};
		}

		auto r = Algo::find_to_insert_hint(comp, k, m_root, Multi, hint, this->cbegin(), this->cend());
		if (r.second != Algo::ChildDir::None)
		{
			auto new_node = Algo::construct_node(alloc, hamon::forward<Args>(args)...);	// may throw
			Algo::insert_at(r.first, r.second, new_node, m_root, m_leftmost, m_rightmost);
			++m_size;
			return {to_iterator(new_node), true};
		}
		else
		{
			return {to_iterator(r.first), false};
		}
	}

private:
	template <typename Compare, typename Allocator, typename Arg0, typename... Args,
		typename = hamon::enable_if_t<
			hamon::disjunction<
				hamon::is_same<hamon::remove_cvref_t<Arg0>, hamon::remove_cvref_t<value_type>>,
				hamon::is_same<hamon::remove_cvref_t<Arg0>, hamon::remove_cvref_t<key_type>>
			>::value
		>
	>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	emplace_impl(hamon::detail::overload_priority<1>,
		Compare const& comp, Allocator& alloc, Arg0&& arg0, Args&&... args)
	{
		auto r = Algo::find_to_insert(comp, hamon::forward<Arg0>(arg0), m_root, Multi);
		if (r.second != Algo::ChildDir::None)
		{
			auto new_node = Algo::construct_node(alloc, hamon::forward<Arg0>(arg0), hamon::forward<Args>(args)...);	// may throw
			Algo::insert_at(r.first, r.second, new_node, m_root, m_leftmost, m_rightmost);
			++m_size;
			return {to_iterator(new_node), true};
		}
		else
		{
			return {to_iterator(r.first), false};
		}
	}

	template <typename Compare, typename Allocator, typename... Args>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	emplace_impl(hamon::detail::overload_priority<0>,
		Compare const& comp, Allocator& alloc, Args&&... args)
	{
		auto new_node = Algo::construct_node(alloc, hamon::forward<Args>(args)...);	// may throw
		auto r = Algo::find_to_insert(comp, new_node->value(), m_root, Multi);
		if (r.second != Algo::ChildDir::None)
		{
			Algo::insert_at(r.first, r.second, new_node, m_root, m_leftmost, m_rightmost);
			++m_size;
			return {to_iterator(new_node), true};
		}
		else
		{
			Algo::destruct_node(alloc, new_node);
			return {to_iterator(r.first), false};
		}
	}

	template <typename Compare, typename Allocator, typename Arg0, typename... Args,
		typename = hamon::enable_if_t<
			hamon::disjunction<
				hamon::is_same<hamon::remove_cvref_t<Arg0>, hamon::remove_cvref_t<value_type>>,
				hamon::is_same<hamon::remove_cvref_t<Arg0>, hamon::remove_cvref_t<key_type>>
			>::value
		>
	>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	emplace_hint_impl(hamon::detail::overload_priority<1>,
		Compare const& comp, Allocator& alloc, const_iterator position, Arg0&& arg0, Args&&... args)
	{
		auto r = Algo::find_to_insert_hint(comp, hamon::forward<Arg0>(arg0), m_root, Multi, position, this->cbegin(), this->cend());
		if (r.second != Algo::ChildDir::None)
		{
			auto new_node = Algo::construct_node(alloc, hamon::forward<Arg0>(arg0), hamon::forward<Args>(args)...);	// may throw
			Algo::insert_at(r.first, r.second, new_node, m_root, m_leftmost, m_rightmost);
			++m_size;
			return {to_iterator(new_node), true};
		}
		else
		{
			return {to_iterator(r.first), false};
		}
	}

	template <typename Compare, typename Allocator, typename... Args>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	emplace_hint_impl(hamon::detail::overload_priority<0>,
		Compare const& comp, Allocator& alloc, const_iterator position, Args&&... args)
	{
		auto new_node = Algo::construct_node(alloc, hamon::forward<Args>(args)...);	// may throw
		auto r = Algo::find_to_insert_hint(comp, new_node->value(), m_root, Multi, position, this->cbegin(), this->cend());
		if (r.second != Algo::ChildDir::None)
		{
			Algo::insert_at(r.first, r.second, new_node, m_root, m_leftmost, m_rightmost);
			++m_size;
			return {to_iterator(new_node), true};
		}
		else
		{
			Algo::destruct_node(alloc, new_node);
			return {to_iterator(r.first), false};
		}
	}

public:
	template <typename Compare, typename Allocator, typename... Args>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	emplace(Compare const& comp, Allocator& alloc, Args&&... args)
	{
		if (m_root == nullptr)
		{
			auto new_node = Algo::construct_node(alloc, hamon::forward<Args>(args)...);	// may throw
			m_root = new_node;
			m_leftmost = new_node;
			m_rightmost = new_node;
			m_size = 1;
			return {to_iterator(new_node), true};
		}

		return emplace_impl(hamon::detail::overload_priority<1>{},
			comp, alloc, hamon::forward<Args>(args)...);
	}

	template <typename Compare, typename Allocator, typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_hint(Compare const& comp, Allocator& alloc, const_iterator position, Args&&... args)
	{
		if (m_root == nullptr)
		{
			auto new_node = Algo::construct_node(alloc, hamon::forward<Args>(args)...);	// may throw
			m_root = new_node;
			m_leftmost = new_node;
			m_rightmost = new_node;
			m_size = 1;
			return to_iterator(new_node);
		}

		return emplace_hint_impl(hamon::detail::overload_priority<1>{},
			comp, alloc, position, hamon::forward<Args>(args)...).first;
	}

HAMON_WARNING_POP()

	template <typename Compare, typename Allocator, typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void
	insert_range(Compare const& comp, Allocator& alloc, Iterator first, Sentinel last)
	{
		for (; first != last; ++first)
		{
			this->emplace(comp, alloc, *first);
		}
	}

	template <typename Allocator>
	HAMON_CXX14_CONSTEXPR void clear(Allocator& alloc)
	{
		Algo::clear(alloc, m_root);
		m_root = nullptr;
		m_leftmost = nullptr;
		m_rightmost = nullptr;
		m_size = 0;
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_RED_BLACK_TREE_HPP