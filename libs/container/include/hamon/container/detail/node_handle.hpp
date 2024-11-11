/**
 *	@file	node_handle.hpp
 *
 *	@brief	node_handle の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_NODE_HANDLE_HPP
#define HAMON_CONTAINER_DETAIL_NODE_HANDLE_HPP

#include <hamon/memory/allocator_traits.hpp>
#include <hamon/optional.hpp>
#include <hamon/utility.hpp>
#include <hamon/type_traits.hpp>

namespace hamon
{

namespace detail
{

// node_handle の private メンバにアクセスするためのクラス
// 内部実装で使われるものであって、外部からは使用禁止
struct node_handle_access
{
	template <typename NodeHandle, typename Pointer, typename Allocator>
	static HAMON_CXX11_CONSTEXPR
	NodeHandle construct(Pointer p, Allocator const& a)
	{
		return NodeHandle{p, a};
	}

	template <typename NodeHandle>
	static HAMON_CXX11_CONSTEXPR
	typename NodeHandle::pointer ptr(NodeHandle const& nh) noexcept
	{
		return nh.ptr();
	}

	template <typename NodeHandle>
	static HAMON_CXX14_CONSTEXPR
	typename NodeHandle::pointer release(NodeHandle& nh)
	{
		return nh.release();
	}
};

// node_handle の set 用のベースクラス
template <typename Node, typename Derived>
struct set_node_handle_base
{
	using value_type = typename Node::value_type;

	HAMON_CXX11_CONSTEXPR value_type& value() const
	{
		return node_handle_access::ptr(*static_cast<Derived const*>(this))->value();
	}
};

// node_handle の map 用のベースクラス
template <typename Node, typename Derived>
struct map_node_handle_base
{
	using key_type    = hamon::remove_const_t<typename Node::value_type::first_type>;
	using mapped_type = typename Node::value_type::second_type;

	HAMON_CXX11_CONSTEXPR key_type& key() const
	{
		return const_cast<key_type&>(
			node_handle_access::ptr(*static_cast<Derived const*>(this))->value().first);
	}

	HAMON_CXX11_CONSTEXPR mapped_type& mapped() const
	{
		return node_handle_access::ptr(*static_cast<Derived const*>(this))->value().second;
	}
};

// 23.2.5 Node handles[container.node]

template <typename Node, typename Allocator, template <typename, typename> class Base>
class node_handle : public Base<Node, node_handle<Node, Allocator, Base>>
{
public:
	// These type declarations are described in [associative.reqmts] and [unord.req].
	//using value_type     = see below;     // not present for map containers
	//using key_type       = see below;     // not present for set containers
	//using mapped_type    = see below;     // not present for set containers
	using allocator_type = Allocator;

private:
	friend struct hamon::detail::node_handle_access;

	using container_node_type = Node;
	using ator_traits = hamon::allocator_traits<allocator_type>;
	using pointer = typename ator_traits::template
		rebind_traits<container_node_type>::pointer;

	pointer m_ptr;
	hamon::optional<allocator_type> m_alloc;

public:
	// [container.node.cons], constructors, copy, and assignment
	HAMON_CXX11_CONSTEXPR
	node_handle() noexcept
		: m_ptr(), m_alloc() {}

	HAMON_CXX14_CONSTEXPR
	node_handle(node_handle&& x) noexcept
		: m_ptr(x.m_ptr)
		, m_alloc(hamon::move(x.m_alloc))
	{
		x.m_ptr = nullptr;
		x.m_alloc.reset();
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4127)	// 条件式が定数です。

	HAMON_CXX14_CONSTEXPR node_handle&
	operator=(node_handle&& x)
	{
		clear();
		m_ptr = x.m_ptr;

		if (ator_traits::propagate_on_container_move_assignment::value ||
			m_alloc == hamon::nullopt)
		{
			m_alloc = hamon::move(x.m_alloc);
		}

		x.m_ptr   = nullptr;
		x.m_alloc = hamon::nullopt;

		return *this;
	}

HAMON_WARNING_POP()

	// [container.node.dtor], destructor
	HAMON_CXX20_CONSTEXPR ~node_handle()
	{
		clear();
	}

	// [container.node.observers], observers
//	value_type& value() const;            // not present for map containers
//	key_type& key() const;                // not present for set containers
//	mapped_type& mapped() const;          // not present for set containers

	HAMON_CXX11_CONSTEXPR allocator_type
	get_allocator() const
	{
		return *m_alloc;
	}

	HAMON_CXX11_CONSTEXPR explicit
	operator bool() const noexcept
	{
		return m_ptr != nullptr;
	}

	HAMON_CXX11_CONSTEXPR bool
	empty() const noexcept
	{
		return m_ptr == nullptr;
	}

	// [container.node.modifiers], modifiers
	HAMON_CXX14_CONSTEXPR void
	swap(node_handle& x)
		noexcept(ator_traits::propagate_on_container_swap::value ||
				 ator_traits::is_always_equal::value)
	{
		hamon::swap(m_ptr, x.m_ptr);
		if (ator_traits::propagate_on_container_swap::value ||
			m_alloc == hamon::nullopt || x.m_alloc == hamon::nullopt)
		{
			hamon::swap(m_alloc, x.m_alloc);
		}
	}

	friend HAMON_CXX14_CONSTEXPR void
	swap(node_handle& x, node_handle& y)
		noexcept(noexcept(x.swap(y)))
	{
		x.swap(y);
	}

private:
	HAMON_CXX11_CONSTEXPR
	node_handle(pointer p, allocator_type const& a)
		: m_ptr(p)
		, m_alloc(a)
	{}

	HAMON_CXX11_CONSTEXPR pointer ptr() const noexcept
	{
		return m_ptr;
	}

	HAMON_CXX14_CONSTEXPR pointer release()
	{
		m_alloc.reset();
		return hamon::exchange(m_ptr, nullptr);
	}

	HAMON_CXX14_CONSTEXPR void clear()
	{
		if (m_ptr != nullptr)
		{
			using NodeAllocator = typename hamon::allocator_traits<Allocator>::template rebind_alloc<Node>;
			using NodeAllocTraits = typename hamon::allocator_traits<Allocator>::template rebind_traits<Node>;
			NodeAllocator a{*m_alloc};
			NodeAllocTraits::destroy(a, m_ptr);
			NodeAllocTraits::deallocate(a, m_ptr, 1);
			m_alloc.reset();
			m_ptr = nullptr;
		}
	}
};

template <typename Node, typename Allocator>
using set_node_handle = node_handle<Node, Allocator, set_node_handle_base>;

template <typename Node, typename Allocator>
using map_node_handle = node_handle<Node, Allocator, map_node_handle_base>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_NODE_HANDLE_HPP
