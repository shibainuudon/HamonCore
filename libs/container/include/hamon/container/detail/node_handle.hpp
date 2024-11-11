/**
 *	@file	node_handle.hpp
 *
 *	@brief	node_handle の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_NODE_HANDLE_HPP
#define HAMON_CONTAINER_DETAIL_NODE_HANDLE_HPP

namespace hamon
{

namespace detail
{

// 23.2.5 Node handles[container.node]

template <typename>
class node_handle
{
#if 0
public:
	// These type declarations are described in [associative.reqmts] and [unord.req].
	using value_type     = see below;     // not present for map containers
	using key_type       = see below;     // not present for set containers
	using mapped_type    = see below;     // not present for set containers
	using allocator_type = see below;

private:
	using container_node_type = unspecified;                  // exposition only
	using ator_traits = allocator_traits<allocator_type>;     // exposition only

	typename ator_traits::template
		rebind_traits<container_node_type>::pointer ptr_;       // exposition only
	optional<allocator_type> alloc_;                          // exposition only

public:
	// [container.node.cons], constructors, copy, and assignment
	constexpr node_handle() noexcept : ptr_(), alloc_() {}
	node_handle(node_handle&&) noexcept;
	node_handle& operator=(node_handle&&);

	// [container.node.dtor], destructor
	~node_handle();

	// [container.node.observers], observers
	value_type& value() const;            // not present for map containers
	key_type& key() const;                // not present for set containers
	mapped_type& mapped() const;          // not present for set containers

	allocator_type get_allocator() const;
	explicit operator bool() const noexcept;
	bool empty() const noexcept;

	// [container.node.modifiers], modifiers
	void swap(node_handle&)
		noexcept(ator_traits::propagate_on_container_swap::value ||
				 ator_traits::is_always_equal::value);

	friend void
	swap(node_handle& x, node_handle& y)
		noexcept(noexcept(x.swap(y)))
	{
		x.swap(y);
	}
#endif
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_NODE_HANDLE_HPP
