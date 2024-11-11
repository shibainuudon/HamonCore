/**
 *	@file	red_black_tree_node.hpp
 *
 *	@brief	red_black_tree_node の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_RED_BLACK_TREE_NODE_HPP
#define HAMON_CONTAINER_DETAIL_RED_BLACK_TREE_NODE_HPP

#include <hamon/container/detail/red_black_tree_algo.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
struct red_black_tree_node
{
public:
	using value_type = T;

private:
	using Node = red_black_tree_node;
	using Algo = red_black_tree_algo<Node>;

public:
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

		if (is_left_child())
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
	is_left_child() const noexcept
	{
		return m_parent != nullptr && m_parent->m_left == this;
	}

	HAMON_CXX11_CONSTEXPR bool
	is_right_child() const noexcept
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

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_RED_BLACK_TREE_NODE_HPP
