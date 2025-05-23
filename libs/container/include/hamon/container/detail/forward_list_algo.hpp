﻿/**
 *	@file	forward_list_algo.hpp
 *
 *	@brief
 */

#ifndef HAMON_FORWARD_LIST_DETAIL_FORWARD_LIST_ALGO_HPP
#define HAMON_FORWARD_LIST_DETAIL_FORWARD_LIST_ALGO_HPP

#include <hamon/algorithm/min.hpp>
#include <hamon/container/detail/forward_list_node.hpp>
#include <hamon/limits/numeric_limits.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T, typename Allocator>
struct forward_list_algo
{
	using node_type       = hamon::detail::forward_list_node<T>;
	using size_type       = typename hamon::allocator_traits<Allocator>::size_type;
	using difference_type = typename hamon::allocator_traits<Allocator>::difference_type;

	using NodeAllocator   = typename hamon::allocator_traits<Allocator>::template rebind_alloc<node_type>;
	using NodeAllocTraits = typename hamon::allocator_traits<Allocator>::template rebind_traits<node_type>;

	static HAMON_CXX11_CONSTEXPR
	T& get_value(forward_list_node_base* x) HAMON_NOEXCEPT
	{
		return static_cast<node_type*>(x)->m_value;
	}

	static HAMON_CXX14_CONSTEXPR forward_list_node_base*
	next(forward_list_node_base* x, size_type sz) HAMON_NOEXCEPT
	{
		for (; 0 < sz; --sz)
		{
			if (x == nullptr)
			{
				break;
			}

			x = x->m_next;
		}
		return x;
	}

	static HAMON_CXX14_CONSTEXPR
	size_type max_size(Allocator const& alloc)
	{
		return hamon::min(
			static_cast<size_type>(hamon::numeric_limits<difference_type>::max()),
			static_cast<size_type>(NodeAllocTraits::max_size(NodeAllocator{alloc})));
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

	template <typename... Args>
	static HAMON_CXX14_CONSTEXPR
	node_type* construct_node(Allocator& alloc, Args&&... args)
	{
#if defined(HAMON_MSVC) && (HAMON_MSVC < 1930) && \
	defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
		if (hamon::is_constant_evaluated())
		{
			return new node_type(hamon::forward<Args>(args)...);	// may throw
		}
		// Visual Studio 2019 かつ、constexprに評価されたときのみ、
		// ↓のallocator_traitsを使うバージョンだと内部コンパイルエラーになる。
 		// 原因はわからないが、new で構築すればエラーは起こらなくなる。
#endif

		NodeAllocator node_alloc{alloc};
		auto node = NodeAllocTraits::allocate(node_alloc, 1);	// may throw
		NodeAllocTraits::construct(node_alloc, node, hamon::forward<Args>(args)...);	// may throw
		return node;
	}

HAMON_WARNING_POP()

	static HAMON_CXX14_CONSTEXPR
	void destroy_node(Allocator& alloc, forward_list_node_base* node)
	{
		NodeAllocator node_alloc{alloc};
		auto p = static_cast<node_type*>(node);
		NodeAllocTraits::destroy(node_alloc, p);
		NodeAllocTraits::deallocate(node_alloc, p, 1);
	}

	static HAMON_CXX14_CONSTEXPR forward_list_node_base*
	insert_node_after(forward_list_node_base* pos, node_type* node)
	{
		auto next = pos->m_next;
		pos->m_next = node;
		node->m_next = next;
		return node;
	}

	static HAMON_CXX14_CONSTEXPR forward_list_node_base*
	insert_after(Allocator& /*alloc*/, forward_list_node_base* pos, node_type* node)
	{
		return insert_node_after(pos, node);
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

	template <typename... Args>
	static HAMON_CXX14_CONSTEXPR forward_list_node_base*
	insert_after(Allocator& alloc, forward_list_node_base* pos, Args&&... args)
	{
		HAMON_ASSERT(pos != nullptr);
		auto node = construct_node(alloc, hamon::forward<Args>(args)...);	// may throw
		return insert_after(alloc, pos, node);
	}

HAMON_WARNING_POP()

	template <typename... Args>
	static HAMON_CXX20_CONSTEXPR forward_list_node_base*
	insert_n_after(Allocator& alloc, forward_list_node_base* pos, size_type n, Args&&... args)
	{
		HAMON_ASSERT(pos != nullptr);
		auto current = pos;
#if !defined(HAMON_NO_EXCEPTIONS)
		try
#endif
		{
			for (size_type i = 0; i < n; ++i)
			{
				current = insert_after(alloc, current, hamon::forward<Args>(args)...);
			}
			return current;
		}
#if !defined(HAMON_NO_EXCEPTIONS)
		catch (...)
		{
			erase_range_after(alloc, pos, current->m_next);
			throw;
		}
#endif
	}

	template <typename Iterator, typename Sentinel>
	static HAMON_CXX20_CONSTEXPR forward_list_node_base*
	insert_range_after(Allocator& alloc, forward_list_node_base* pos, Iterator first, Sentinel last)
	{
		HAMON_ASSERT(pos != nullptr);
		auto current = pos;
#if !defined(HAMON_NO_EXCEPTIONS)
		try
#endif
		{
			for (Iterator it = first; it != last; ++it)
			{
				current = insert_after(alloc, current, *it);
			}
			return current;
		}
#if !defined(HAMON_NO_EXCEPTIONS)
		catch (...)
		{
			erase_range_after(alloc, pos, current->m_next);
			throw;
		}
#endif
	}

	static HAMON_CXX14_CONSTEXPR forward_list_node_base*
	erase_range_after(Allocator& alloc, forward_list_node_base* pos, forward_list_node_base* last) HAMON_NOEXCEPT
	{
		HAMON_ASSERT(pos != nullptr);

		auto current = pos->m_next;
		while (current != last)
		{
			auto next = current->m_next;
			destroy_node(alloc, current);
			current = next;
		}
		pos->m_next = last;
		return current;
	}

	static HAMON_CXX14_CONSTEXPR forward_list_node_base*
	erase_after(Allocator& alloc, forward_list_node_base* pos) HAMON_NOEXCEPT
	{
		HAMON_ASSERT(pos != nullptr);
		HAMON_ASSERT(pos->m_next != nullptr);
		return erase_range_after(alloc, pos, pos->m_next->m_next);
	}

	template <typename Iterator, typename Sentinel>
	static HAMON_CXX14_CONSTEXPR void
	assign_range_after(Allocator& alloc, forward_list_node_base* pos, Iterator first, Sentinel last)
	{
		auto prev = pos;

		for (;;)
		{
			auto curr = prev->m_next;

			if (first == last)
			{
				erase_range_after(alloc, prev, nullptr);
				return;
			}

			if (curr == nullptr)
			{
				insert_range_after(alloc, prev, first, last);
				return;
			}

			get_value(curr) = *first;

			prev = curr;
			++first;
		}
	}

	template <typename... Args>
	static HAMON_CXX14_CONSTEXPR void
	resize_after(Allocator& alloc, forward_list_node_base* pos, size_type size, Args&&... args)
	{
		auto prev = pos;

		for (;;)
		{
			auto curr = prev->m_next;

			if (size == 0)
			{
				erase_range_after(alloc, prev, nullptr);
				return;
			}

			if (curr == nullptr)
			{
				insert_n_after(alloc, prev, size, hamon::forward<Args>(args)...);
				return;
			}

			prev = curr;
			--size;
		}
	}

	template <typename Predicate>
	static HAMON_CXX14_CONSTEXPR hamon::size_t
	remove_if_after(Allocator& alloc, forward_list_node_base* pos, Predicate pred)
	{
		auto prev = pos;
		hamon::size_t removed_count = 0;

		while (prev)
		{
			auto curr = prev->m_next;

			if (curr == nullptr)
			{
				break;
			}

			if (pred(get_value(curr)))
			{
				erase_after(alloc, prev);
				++removed_count;
			}
			else
			{
				prev = curr;
			}
		}

		return removed_count;
	}

	template <typename BinaryPredicate>
	static HAMON_CXX14_CONSTEXPR hamon::size_t
	unique_after(Allocator& alloc, forward_list_node_base* pos, BinaryPredicate binary_pred)
	{
		auto curr = pos->m_next;
		hamon::size_t removed_count = 0;

		while (curr)
		{
			auto next = curr->m_next;

			if (next == nullptr)
			{
				break;
			}

			if (binary_pred(get_value(curr), get_value(next)))
			{
				erase_after(alloc, curr);
				++removed_count;
			}
			else
			{
				curr = next;
			}
		}

		return removed_count;
	}

	static HAMON_CXX14_CONSTEXPR forward_list_node_base*
	extract_after(forward_list_node_base* pos) HAMON_NOEXCEPT
	{
		HAMON_ASSERT(pos != nullptr);
		HAMON_ASSERT(pos->m_next != nullptr);

		auto next = pos->m_next;
		pos->m_next = next->m_next;
		next->m_next = nullptr;
		return next;
	}

	static HAMON_CXX14_CONSTEXPR void
	splice_after(forward_list_node_base* pos, forward_list_node_base* first) HAMON_NOEXCEPT
	{
		auto next = first->m_next;
		first->m_next = next->m_next;
		next->m_next = pos->m_next;
		pos->m_next = next;
	}

	static HAMON_CXX14_CONSTEXPR void
	splice_range_after(forward_list_node_base* pos, forward_list_node_base* first, forward_list_node_base* last) HAMON_NOEXCEPT
	{
		if (first == last)
		{
			return;
		}

		if (first->m_next == last)
		{
			return;
		}

		auto prev_last = first->m_next;
		while(prev_last->m_next != last)
		{
			prev_last = prev_last->m_next;
		}

		auto next = first->m_next;
		first->m_next = prev_last->m_next;
		prev_last->m_next = pos->m_next;
		pos->m_next = next;
	}

	template <typename Compare>
	static HAMON_CXX14_CONSTEXPR void
	merge_after(forward_list_node_base* x, forward_list_node_base* y, Compare comp)
	{
		while (x->m_next && y->m_next)
		{
			if (comp(get_value(y->m_next), get_value(x->m_next)))
			{
				splice_after(x, y);
			}

			x = x->m_next;
		}

		if (y->m_next)
		{
			x->m_next = y->m_next;
			y->m_next = nullptr;
		}
	}

	// 2つの連続したソート済みイテレータ範囲 (first, middle) と [middle, last) をマージする。
	// マージした範囲のうち最後の要素を返す(lastの1つ前)
	template <typename Compare>
	static HAMON_CXX14_CONSTEXPR forward_list_node_base*
	inplace_merge_after(forward_list_node_base* first, forward_list_node_base* middle, forward_list_node_base* last, Compare comp)
	{
		HAMON_ASSERT(first != nullptr);
		forward_list_node_base* x = first->m_next;
		forward_list_node_base* y = middle;
		forward_list_node_base* tail = nullptr;

		while (x != middle || y != last)
		{
			forward_list_node_base* e = nullptr;
			if (x == middle)
			{
				e = y;
				y = y->m_next;
			}
			else if (y == last)
			{
				e = x;
				x = x->m_next;
			}
			else if (comp(get_value(y), get_value(x)))
			{
				e = y;
				y = y->m_next;
			}
			else
			{
				e = x;
				x = x->m_next;
			}

			if (tail)
			{
				tail->m_next = e;
			}
			else
			{
				first->m_next = e;
			}

			tail = e;
		}

		HAMON_ASSERT(tail != nullptr);
		tail->m_next = last;

		return tail;
	}

	template <typename Compare>
	static HAMON_CXX14_CONSTEXPR void
	sort_after(forward_list_node_base* x, Compare comp)
	{
		size_type sz = 1;
		for (;;)
		{
			size_type merge_count = 0;
			auto first = x;
			while (first->m_next)
			{
				auto middle = next(first->m_next, sz);
				auto last   = next(middle, sz);
				first = inplace_merge_after(first, middle, last, comp);
				++merge_count;
			}

			if (merge_count <= 1)
			{
				break;
			}

			sz *= 2;
		}
	}

	static HAMON_CXX14_CONSTEXPR void
	reverse_after(forward_list_node_base* x) HAMON_NOEXCEPT
	{
		auto curr = x->m_next;
		if (curr != nullptr)
		{
			auto next = curr->m_next;
			curr->m_next = nullptr;
			while (next != nullptr)
			{
				auto t = next->m_next;
				next->m_next = curr;
				curr         = next;
				next         = t;
			}
			x->m_next = curr;
		}
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORWARD_LIST_DETAIL_FORWARD_LIST_ALGO_HPP
