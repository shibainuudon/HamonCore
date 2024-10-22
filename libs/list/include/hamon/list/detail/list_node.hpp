/**
 *	@file	list_node.hpp
 *
 *	@brief	list_node の定義
 */

#ifndef HAMON_LIST_DETAIL_LIST_NODE_HPP
#define HAMON_LIST_DETAIL_LIST_NODE_HPP

#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

struct list_node_base
{
	list_node_base*	m_next;
	list_node_base*	m_prev;

	HAMON_CXX11_CONSTEXPR
	list_node_base() HAMON_NOEXCEPT
		: m_next{this}
		, m_prev{this}
	{}

	HAMON_CXX14_CONSTEXPR
	list_node_base& operator=(list_node_base&& x) HAMON_NOEXCEPT
	{
		auto next = x.m_next;
		auto prev = x.m_prev;
		next->m_prev = this;
		prev->m_next = this;
		m_next = x.m_next;
		m_prev = x.m_prev;

		x.m_next = x.m_prev = &x;

		return *this;
	}
};

template <typename T>
struct list_node : public list_node_base
{
	T	m_value;

	template <typename... Args>
	HAMON_CXX11_CONSTEXPR
	list_node(Args&&... args)
		: m_value{hamon::forward<Args>(args)...}
	{}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_LIST_DETAIL_LIST_NODE_HPP
