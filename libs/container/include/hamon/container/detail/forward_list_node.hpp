/**
 *	@file	forward_list_node.hpp
 *
 *	@brief
 */

#ifndef HAMON_FORWARD_LIST_DETAIL_FORWARD_LIST_NODE_HPP
#define HAMON_FORWARD_LIST_DETAIL_FORWARD_LIST_NODE_HPP

#include <hamon/utility/exchange.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

struct forward_list_node_base
{
	forward_list_node_base*	m_next;

	HAMON_CXX11_CONSTEXPR
	forward_list_node_base() HAMON_NOEXCEPT
		: m_next{nullptr}
	{}

	forward_list_node_base(forward_list_node_base const&) = delete;
	forward_list_node_base& operator=(forward_list_node_base const&) = delete;

	HAMON_CXX14_CONSTEXPR
	forward_list_node_base(forward_list_node_base&& x) HAMON_NOEXCEPT
		: m_next{hamon::exchange(x.m_next, nullptr)}
	{}

	HAMON_CXX14_CONSTEXPR
	forward_list_node_base& operator=(forward_list_node_base&& x) HAMON_NOEXCEPT
	{
		m_next = hamon::exchange(x.m_next, nullptr);
		return *this;
	}
};

template <typename T>
struct forward_list_node : public forward_list_node_base
{
	using value_type = T;

	T	m_value;

	template <typename... Args>
	HAMON_CXX11_CONSTEXPR
	forward_list_node(Args&&... args)
		: m_value{hamon::forward<Args>(args)...}
	{}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORWARD_LIST_DETAIL_FORWARD_LIST_NODE_HPP
