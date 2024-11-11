/**
 *	@file	red_black_tree_iterator.hpp
 *
 *	@brief	red_black_tree_iterator の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_RED_BLACK_TREE_ITERATOR_HPP
#define HAMON_CONTAINER_DETAIL_RED_BLACK_TREE_ITERATOR_HPP

#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/memory/pointer_traits.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>

namespace hamon
{

namespace detail
{

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

private:
	Tree const* m_tree;
	NodePointer m_node;

public:
	HAMON_CXX11_CONSTEXPR NodePointer node() const HAMON_NOEXCEPT
	{
		return m_node;
	}

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
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_RED_BLACK_TREE_ITERATOR_HPP
