/**
 *	@file	list_impl.hpp
 *
 *	@brief	list_impl の定義
 */

#ifndef HAMON_LIST_DETAIL_LIST_IMPL_HPP
#define HAMON_LIST_DETAIL_LIST_IMPL_HPP

#include <hamon/memory/addressof.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/utility/exchange.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename Algo>
struct list_impl
{
private:
	using T = typename Algo::ValueType;
	using Allocator = typename Algo::AllocatorType;
	using NodeBase = typename Algo::NodeBase;
	using SizeType = typename Algo::SizeType;

private:
	NodeBase	m_node{};
	SizeType	m_size{};

public:
	HAMON_CXX11_CONSTEXPR
	list_impl() HAMON_NOEXCEPT
	{}

	HAMON_CXX14_CONSTEXPR
	list_impl(list_impl&& x) HAMON_NOEXCEPT
	{
		*this = hamon::move(x);
	}

	HAMON_CXX14_CONSTEXPR
	list_impl& operator=(list_impl&& x) HAMON_NOEXCEPT
	{
		m_node = hamon::move(x.m_node);
		m_size = hamon::exchange(x.m_size, SizeType{});
		return *this;
	}

	HAMON_CXX11_CONSTEXPR NodeBase*
	head() const HAMON_NOEXCEPT
	{
		return const_cast<NodeBase*>(m_node.m_next);
	}

	HAMON_CXX11_CONSTEXPR NodeBase*
	tail() const HAMON_NOEXCEPT
	{
		return const_cast<NodeBase*>(hamon::addressof(m_node));
	}

	HAMON_CXX11_CONSTEXPR SizeType const&
	size() const HAMON_NOEXCEPT
	{
		return m_size;
	}

	template <typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void
	assign_range(Allocator& alloc, Iterator first, Sentinel last)
	{
		Algo::assign_range(alloc, m_size, this->head(), this->tail(), first, last);	// may throw
	}

	template <typename Range>
	HAMON_CXX14_CONSTEXPR void
	assign_range(Allocator& alloc, Range&& rg)
	{
		this->assign_range(alloc, hamon::ranges::begin(rg), hamon::ranges::end(rg));	// may throw
	}

	HAMON_CXX14_CONSTEXPR void
	assign_n(Allocator& alloc, SizeType n, T const& t)
	{
		Algo::assign_n(alloc, m_size, this->head(), this->tail(), n, t);	// may throw
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR void
	resize(Allocator& alloc, SizeType sz, Args&&... args)
	{
		Algo::resize(alloc, m_size, this->head(), this->tail(), sz, hamon::forward<Args>(args)...);	// may throw
	}

	HAMON_CXX14_CONSTEXPR NodeBase*
	insert_n(Allocator& alloc, NodeBase* pos, SizeType n, T const& x)
	{
		return Algo::insert_n(alloc, m_size, pos, n, x);	// may throw
	}

	template <typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR NodeBase*
	insert_range(Allocator& alloc, NodeBase* pos, Iterator first, Sentinel last)
	{
		return Algo::insert_range(alloc, m_size, pos, first, last);	// may throw
	}

	template <typename Range>
	HAMON_CXX14_CONSTEXPR NodeBase*
	insert_range(Allocator& alloc, NodeBase* pos, Range&& rg)
	{
		return this->insert_range(alloc, pos, hamon::ranges::begin(rg), hamon::ranges::end(rg));	// may throw
	}

	template <typename Range>
	HAMON_CXX14_CONSTEXPR NodeBase*
	prepend_range(Allocator& alloc, Range&& rg)
	{
		return this->insert_range(alloc, this->head(), hamon::forward<Range>(rg));	// may throw
	}

	template <typename Range>
	HAMON_CXX14_CONSTEXPR NodeBase*
	append_range(Allocator& alloc, Range&& rg)
	{
		return this->insert_range(alloc, this->tail(), hamon::forward<Range>(rg));	// may throw
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR NodeBase*
	emplace(Allocator& alloc, NodeBase* pos, Args&&... args)
	{
		return Algo::insert(alloc, m_size, pos, hamon::forward<Args>(args)...);	// may throw
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR NodeBase*
	emplace_front(Allocator& alloc, Args&&... args)
	{
		return this->emplace(alloc, this->head(), hamon::forward<Args>(args)...);	// may throw
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR NodeBase*
	emplace_back(Allocator& alloc, Args&&... args)
	{
		return this->emplace(alloc, this->tail(), hamon::forward<Args>(args)...);	// may throw
	}

	HAMON_CXX14_CONSTEXPR NodeBase*
	erase(Allocator& alloc, NodeBase* pos)
	{
		return Algo::erase(alloc, m_size, pos);
	}

	HAMON_CXX14_CONSTEXPR NodeBase*
	erase_range(Allocator& alloc, NodeBase* pos, NodeBase* last)
	{
		return Algo::erase_range(alloc, m_size, pos, last);
	}

	HAMON_CXX14_CONSTEXPR void
	pop_front(Allocator& alloc)
	{
		this->erase(alloc, this->head());
	}

	HAMON_CXX14_CONSTEXPR void
	pop_back(Allocator& alloc)
	{
		this->erase(alloc, this->tail()->m_prev);
	}

	HAMON_CXX14_CONSTEXPR void
	clear(Allocator& alloc)
	{
		this->erase_range(alloc, this->head(), this->tail());
	}

	HAMON_CXX14_CONSTEXPR void
	splice_range(NodeBase* pos, list_impl& x, NodeBase* first, NodeBase* last)
	{
		if (hamon::addressof(x) != this)
		{
			auto const d = Algo::distance(first, last);
			m_size += d;
			x.m_size -= d;
		}
		Algo::splice_range(pos, first, last);
	}

	template <typename Predicate>
	HAMON_CXX14_CONSTEXPR SizeType
	remove_if(Allocator& alloc, Predicate pred)
	{
		return Algo::remove_if(alloc, m_size, this->head(), this->tail(), pred);	// may throw
	}

	template <typename BinaryPredicate>
	HAMON_CXX14_CONSTEXPR SizeType
	unique(Allocator& alloc, BinaryPredicate binary_pred)
	{
		return Algo::unique(alloc, m_size, this->head(), this->tail(), binary_pred);	// may throw
	}

	template <typename Compare>
	HAMON_CXX14_CONSTEXPR void
	merge(list_impl& x, Compare comp)
	{
		Algo::merge(this->head(), this->tail(), x.head(), x.tail(), comp);	// may throw
		m_size += x.m_size;
		x.m_size = 0;
	}

	template <typename Compare>
	HAMON_CXX14_CONSTEXPR void
	sort(Compare comp)
	{
		Algo::sort(this->head(), this->tail(), comp);	// may throw
	}

	HAMON_CXX14_CONSTEXPR void
	reverse() HAMON_NOEXCEPT
	{
		Algo::reverse(this->head(), this->tail());
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_LIST_DETAIL_LIST_IMPL_HPP
