/**
 *	@file	list_iterator.hpp
 *
 *	@brief	list_iterator の定義
 */

#ifndef HAMON_LIST_DETAIL_LIST_ITERATOR_HPP
#define HAMON_LIST_DETAIL_LIST_ITERATOR_HPP

#include <hamon/list/list_fwd.hpp>
#include <hamon/list/detail/list_node.hpp>
#include <hamon/list/detail/list_algo.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/pointer_traits.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T, typename Allocator, bool Const>
struct list_iterator
{
public:
	using iterator_category = hamon::bidirectional_iterator_tag;
	using value_type        = T;
	using difference_type   = typename hamon::allocator_traits<Allocator>::difference_type;
	using pointer           = hamon::conditional_t<Const, value_type const*, value_type*>;
	using reference         = hamon::conditional_t<Const, value_type const&, value_type&>;

private:
	using NodeBase = hamon::detail::list_node_base;

private:
	NodeBase*	m_ptr;

private:
	HAMON_CXX11_CONSTEXPR NodeBase*
	ptr() const HAMON_NOEXCEPT { return m_ptr; }

public:
	HAMON_CXX11_CONSTEXPR
	list_iterator() HAMON_NOEXCEPT
		: m_ptr(nullptr)
	{}

	explicit HAMON_CXX11_CONSTEXPR
	list_iterator(NodeBase* ptr) HAMON_NOEXCEPT
		: m_ptr(ptr)
	{}

	template <bool C, typename = hamon::enable_if_t<C == Const || Const>>
	HAMON_CXX11_CONSTEXPR
	list_iterator(list_iterator<T, Allocator, C> const& i) HAMON_NOEXCEPT
		: m_ptr(i.m_ptr)
	{}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	reference operator*() const HAMON_NOEXCEPT
	{
#if HAMON_CXX_STANDARD >= 14
		HAMON_ASSERT(m_ptr != nullptr);
#endif
		return hamon::detail::list_algo<T, Allocator>::get_value(m_ptr);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	pointer operator->() const HAMON_NOEXCEPT
	{
		return hamon::pointer_traits<pointer>::pointer_to(**this);
	}

	HAMON_CXX14_CONSTEXPR list_iterator&
	operator++() HAMON_NOEXCEPT
	{
		HAMON_ASSERT(m_ptr != nullptr);
		m_ptr = m_ptr->m_next;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR list_iterator
	operator++(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;
		++*this;
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR list_iterator&
	operator--() HAMON_NOEXCEPT
	{
		HAMON_ASSERT(m_ptr != nullptr);
		m_ptr = m_ptr->m_prev;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR list_iterator
	operator--(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;
		--*this;
		return tmp;
	}

private:
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator==(list_iterator const& lhs, list_iterator const& rhs) HAMON_NOEXCEPT
	{
		return lhs.m_ptr == rhs.m_ptr;
	}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator!=(list_iterator const& lhs, list_iterator const& rhs) HAMON_NOEXCEPT
	{
		return !(lhs == rhs);
	}
#endif

private:
	friend struct list_iterator<T, Allocator, !Const>;
	friend class hamon::list<T, Allocator>;
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_LIST_DETAIL_LIST_ITERATOR_HPP
