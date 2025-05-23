﻿/**
 *	@file	forward_list_iterator.hpp
 *
 *	@brief
 */

#ifndef HAMON_FORWARD_LIST_DETAIL_FORWARD_LIST_ITERATOR_HPP
#define HAMON_FORWARD_LIST_DETAIL_FORWARD_LIST_ITERATOR_HPP

#include <hamon/container/detail/forward_list_node.hpp>
#include <hamon/container/detail/forward_list_algo.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/memory/pointer_traits.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

struct forward_list_iterator_access;

template <typename T, typename Allocator, bool Const>
struct forward_list_iterator
{
public:
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = typename hamon::allocator_traits<Allocator>::difference_type;
	using pointer           = hamon::conditional_t<Const, value_type const*, value_type*>;
	using reference         = hamon::conditional_t<Const, value_type const&, value_type&>;

private:
	using NodeBase = hamon::detail::forward_list_node_base;
	using Node     = hamon::detail::forward_list_node<value_type>;

private:
	NodeBase*	m_ptr;

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。
	explicit HAMON_CXX11_CONSTEXPR
	forward_list_iterator(NodeBase* ptr) HAMON_NOEXCEPT
		: m_ptr(ptr)
	{}
HAMON_WARNING_POP()

public:
	HAMON_CXX11_CONSTEXPR
	forward_list_iterator() HAMON_NOEXCEPT
		: m_ptr(nullptr)
	{}

	template <bool C, typename = hamon::enable_if_t<C == Const || Const>>
	HAMON_CXX11_CONSTEXPR
	forward_list_iterator(forward_list_iterator<T, Allocator, C> const& i) HAMON_NOEXCEPT
		: m_ptr(i.m_ptr)
	{}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	reference operator*() const HAMON_NOEXCEPT
	{
#if HAMON_CXX_STANDARD >= 14
		HAMON_ASSERT(m_ptr != nullptr);
#endif
		return hamon::detail::forward_list_algo<T, Allocator>::get_value(m_ptr);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	pointer operator->() const HAMON_NOEXCEPT
	{
		return hamon::pointer_traits<pointer>::pointer_to(**this);
	}

	HAMON_CXX14_CONSTEXPR forward_list_iterator&
	operator++() HAMON_NOEXCEPT
	{
		HAMON_ASSERT(m_ptr != nullptr);
		m_ptr = m_ptr->m_next;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR forward_list_iterator
	operator++(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;
		++*this;
		return tmp;
	}

private:
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator==(forward_list_iterator const& lhs, forward_list_iterator const& rhs) HAMON_NOEXCEPT
	{
		return lhs.m_ptr == rhs.m_ptr;
	}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator!=(forward_list_iterator const& lhs, forward_list_iterator const& rhs) HAMON_NOEXCEPT
	{
		return !(lhs == rhs);
	}
#endif

private:
	friend struct forward_list_iterator<T, Allocator, !Const>;
	friend struct forward_list_iterator_access;
};

struct forward_list_iterator_access
{
	template <typename Iterator>
	static HAMON_CXX11_CONSTEXPR Iterator
	make(typename Iterator::NodeBase* ptr) HAMON_NOEXCEPT
	{
		return Iterator{ptr};
	}

	template <typename T, typename A, bool C>
	static HAMON_CXX11_CONSTEXPR
	typename forward_list_iterator<T, A, C>::NodeBase*
	ptr(forward_list_iterator<T, A, C> const& it) HAMON_NOEXCEPT
	{
		return it.m_ptr;
	}
};

template <typename T, typename A>
HAMON_CXX11_CONSTEXPR forward_list_iterator<T, A, false>
const_iterator_cast(forward_list_iterator<T, A, true> const& x) HAMON_NOEXCEPT
{
	using access = hamon::detail::forward_list_iterator_access;
	return access::make<forward_list_iterator<T, A, false>>(access::ptr(x));
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORWARD_LIST_DETAIL_FORWARD_LIST_ITERATOR_HPP
