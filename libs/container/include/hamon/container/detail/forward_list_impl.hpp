/**
 *	@file	forward_list_impl.hpp
 *
 *	@brief
 */

#ifndef HAMON_FORWARD_LIST_DETAIL_FORWARD_LIST_IMPL_HPP
#define HAMON_FORWARD_LIST_DETAIL_FORWARD_LIST_IMPL_HPP

#include <hamon/container/detail/forward_list_node.hpp>
#include <hamon/container/detail/forward_list_iterator.hpp>
#include <hamon/container/detail/forward_list_algo.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T, typename DifferenceType>
struct forward_list_impl
{
public:
	using node_type      = hamon::detail::forward_list_node<T>;
	using iterator       = hamon::detail::forward_list_iterator<T, DifferenceType, false>;
	using const_iterator = hamon::detail::forward_list_iterator<T, DifferenceType, true>;

private:
	using Algo = hamon::detail::forward_list_algo<T>;

private:
	hamon::detail::forward_list_node_base	m_head{};

private:
	HAMON_CXX11_CONSTEXPR hamon::detail::forward_list_node_base*
	before_head() const HAMON_NOEXCEPT
	{
		return const_cast<hamon::detail::forward_list_node_base*>(hamon::addressof(m_head));
	}

public:
	template <typename Allocator, typename... Args>
	static HAMON_CXX14_CONSTEXPR
	node_type* construct_node(Allocator& alloc, Args&&... args)
	{
		return Algo::construct_node(alloc, hamon::forward<Args>(args)...);
	}

	template <typename Allocator>
	static HAMON_CXX14_CONSTEXPR
	void destroy_node(Allocator& alloc, hamon::detail::forward_list_node_base* node)
	{
		Algo::destroy_node(alloc, node);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR
	iterator before_begin() HAMON_NOEXCEPT
	{
		using access = hamon::detail::forward_list_iterator_access;
		return access::make<iterator>(this->before_head());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	const_iterator before_begin() const HAMON_NOEXCEPT
	{
		using access = hamon::detail::forward_list_iterator_access;
		return access::make<const_iterator>(this->before_head());
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR
	iterator begin() HAMON_NOEXCEPT
	{
		using access = hamon::detail::forward_list_iterator_access;
		return access::make<iterator>(m_head.m_next);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	const_iterator begin() const HAMON_NOEXCEPT
	{
		using access = hamon::detail::forward_list_iterator_access;
		return access::make<const_iterator>(m_head.m_next);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR
	iterator end() HAMON_NOEXCEPT
	{
		using access = hamon::detail::forward_list_iterator_access;
		return access::make<iterator>(nullptr);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	const_iterator end() const HAMON_NOEXCEPT
	{
		using access = hamon::detail::forward_list_iterator_access;
		return access::make<const_iterator>(nullptr);
	}

	template <typename Allocator>
	HAMON_CXX14_CONSTEXPR iterator
	insert_after(Allocator& alloc, const_iterator pos, node_type* node)
	{
		using access = hamon::detail::forward_list_iterator_access;
		return access::make<iterator>(
			Algo::insert_after(alloc, access::ptr(pos), node));
	}

	template <typename Allocator, typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	insert_after(Allocator& alloc, const_iterator pos, Args&&... args)
	{
		using access = hamon::detail::forward_list_iterator_access;
		return access::make<iterator>(
			Algo::insert_after(alloc, access::ptr(pos), hamon::forward<Args>(args)...));
	}

	template <typename Allocator, typename SizeType, typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	insert_n_after(Allocator& alloc, const_iterator pos, SizeType n, Args&&... args)
	{
		using access = hamon::detail::forward_list_iterator_access;
		return access::make<iterator>(
			Algo::insert_n_after(alloc, access::ptr(pos), n, hamon::forward<Args>(args)...));
	}

	template <typename Allocator, typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR iterator
	insert_range_after(Allocator& alloc, const_iterator pos, Iterator first, Sentinel last)
	{
		using access = hamon::detail::forward_list_iterator_access;
		return access::make<iterator>(
			Algo::insert_range_after(alloc, access::ptr(pos), first, last));
	}

	template <typename Allocator, typename Range>
	HAMON_CXX14_CONSTEXPR iterator
	insert_range_after(Allocator& alloc, const_iterator pos, Range&& rg)
	{
		return this->insert_range_after(alloc, pos, hamon::ranges::begin(rg), hamon::ranges::end(rg));
	}

	template <typename Allocator, typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void
	assign_range(Allocator& alloc, Iterator first, Sentinel last)
	{
		Algo::assign_range_after(alloc, this->before_head(), first, last);
	}

	template <typename Allocator, typename Range>
	HAMON_CXX14_CONSTEXPR void
	assign_range(Allocator& alloc, Range&& rg)
	{
		this->assign_range(alloc, hamon::ranges::begin(rg), hamon::ranges::end(rg));
	}

	template <typename Allocator>
	HAMON_CXX14_CONSTEXPR iterator
	erase_range_after(Allocator& alloc, const_iterator pos, const_iterator last) HAMON_NOEXCEPT
	{
		using access = hamon::detail::forward_list_iterator_access;
		return access::make<iterator>(
			Algo::erase_range_after(alloc, access::ptr(pos), access::ptr(last)));
	}

	template <typename Allocator>
	HAMON_CXX14_CONSTEXPR iterator
	erase_after(Allocator& alloc, const_iterator pos) HAMON_NOEXCEPT
	{
		using access = hamon::detail::forward_list_iterator_access;
		return access::make<iterator>(
			Algo::erase_after(alloc, access::ptr(pos)));
	}

	template <typename Allocator>
	HAMON_CXX14_CONSTEXPR void
	clear(Allocator& alloc) HAMON_NOEXCEPT
	{
		this->erase_range_after(alloc, this->before_begin(), this->end());
	}

	template <typename Allocator, typename SizeType, typename... Args>
	HAMON_CXX14_CONSTEXPR void
	resize(Allocator& alloc, SizeType size, Args&&... args)
	{
		Algo::resize_after(alloc, this->before_head(), size, hamon::forward<Args>(args)...);
	}

	HAMON_CXX14_CONSTEXPR void
	splice_after(const_iterator pos, const_iterator first) HAMON_NOEXCEPT
	{
		using access = hamon::detail::forward_list_iterator_access;
		Algo::splice_after(access::ptr(pos), access::ptr(first));
	}

	HAMON_CXX14_CONSTEXPR void
	splice_range_after(const_iterator pos, const_iterator first, const_iterator last) HAMON_NOEXCEPT
	{
		using access = hamon::detail::forward_list_iterator_access;
		Algo::splice_range_after(access::ptr(pos), access::ptr(first), access::ptr(last));
	}

	template <typename Allocator, typename Predicate>
	HAMON_CXX14_CONSTEXPR hamon::size_t
	remove_if(Allocator& alloc, Predicate pred)
	{
		return Algo::remove_if_after(alloc, this->before_head(), pred);
	}

	template <typename Allocator, typename BinaryPredicate>
	HAMON_CXX14_CONSTEXPR hamon::size_t
	unique(Allocator& alloc, BinaryPredicate binary_pred)
	{
		return Algo::unique_after(alloc, this->before_head(), binary_pred);
	}

	template <typename Compare>
	HAMON_CXX14_CONSTEXPR void
	merge(forward_list_impl& x, Compare comp)
	{
		Algo::merge_after(this->before_head(), x.before_head(), comp);
	}

	template <typename Compare>
	HAMON_CXX14_CONSTEXPR void
	sort(Compare comp)
	{
		Algo::sort_after(this->before_head(), comp);
	}

	HAMON_CXX14_CONSTEXPR void
	reverse() HAMON_NOEXCEPT
	{
		Algo::reverse_after(this->before_head());
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORWARD_LIST_DETAIL_FORWARD_LIST_IMPL_HPP
