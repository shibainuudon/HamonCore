﻿/**
 *	@file	forward_list_algo.hpp
 *
 *	@brief
 */

#ifndef HAMON_FORWARD_LIST_DETAIL_FORWARD_LIST_ALGO_HPP
#define HAMON_FORWARD_LIST_DETAIL_FORWARD_LIST_ALGO_HPP

#include <hamon/forward_list/detail/forward_list_node.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
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
	using AllocTraits = hamon::allocator_traits<Allocator>;
	using SizeType    = typename AllocTraits::size_type;

	static HAMON_CXX11_CONSTEXPR
	T& get_value(forward_list_node_base* x) HAMON_NOEXCEPT
	{
		return static_cast<forward_list_node<T>*>(x)->m_value;
	}

	template <typename SizeType>
	static HAMON_CXX14_CONSTEXPR forward_list_node_base*
	next(forward_list_node_base* x, SizeType sz) HAMON_NOEXCEPT
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

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

	template <typename... Args>
	static HAMON_CXX14_CONSTEXPR forward_list_node_base*
	insert_after(Allocator& alloc, forward_list_node_base* pos, Args&&... args)
	{
		HAMON_ASSERT(pos != nullptr);
		auto node = AllocTraits::allocate(alloc, 1);	// may throw
		AllocTraits::construct(alloc, node, hamon::forward<Args>(args)...);	// may throw
		auto next = pos->m_next;
		pos->m_next = node;
		node->m_next = next;
		return node;
	}

HAMON_WARNING_POP()

	template <typename SizeType, typename... Args>
	static HAMON_CXX20_CONSTEXPR forward_list_node_base*
	insert_n_after(Allocator& alloc, forward_list_node_base* pos, SizeType n, Args&&... args)
	{
		HAMON_ASSERT(pos != nullptr);
		auto current = pos;
#if !defined(HAMON_NO_EXCEPTIONS)
		try
#endif
		{
			for (SizeType i = 0; i < n; ++i)
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

	template <typename Range>
	static HAMON_CXX14_CONSTEXPR forward_list_node_base*
	insert_range_after(Allocator& alloc, forward_list_node_base* pos, Range&& rg)
	{
		return insert_range_after(alloc, pos, hamon::ranges::begin(rg), hamon::ranges::end(rg));
	}

	static HAMON_CXX14_CONSTEXPR forward_list_node_base*
	erase_range_after(Allocator& alloc, forward_list_node_base* pos, forward_list_node_base* last) HAMON_NOEXCEPT
	{
		HAMON_ASSERT(pos != nullptr);

		auto current = pos->m_next;
		while (current != last)
		{
			auto next = current->m_next;
			auto p = static_cast<forward_list_node<T>*>(current);
			AllocTraits::destroy(alloc, p);
			AllocTraits::deallocate(alloc, p, 1);
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

	static HAMON_CXX14_CONSTEXPR forward_list_node_base*
	clear_after(Allocator& alloc, forward_list_node_base* pos) HAMON_NOEXCEPT
	{
		return erase_range_after(alloc, pos, nullptr);
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
				clear_after(alloc, prev);
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

	template <typename Range>
	static HAMON_CXX14_CONSTEXPR void
	assign_range_after(Allocator& alloc, forward_list_node_base* pos, Range&& rg)
	{
		assign_range_after(alloc, pos, hamon::ranges::begin(rg), hamon::ranges::end(rg));
	}

	template <typename SizeType, typename... Args>
	static HAMON_CXX14_CONSTEXPR void
	resize_after(Allocator& alloc, forward_list_node_base* pos, SizeType size, Args&&... args)
	{
		auto prev = pos;

		for (;;)
		{
			auto curr = prev->m_next;

			if (size == 0)
			{
				clear_after(alloc, prev);
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
	static HAMON_CXX14_CONSTEXPR SizeType
	remove_if_after(Allocator& alloc, forward_list_node_base* pos, Predicate pred)
	{
		auto prev = pos;
		SizeType removed_count = 0;

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
	static HAMON_CXX14_CONSTEXPR SizeType
	unique_after(Allocator& alloc, forward_list_node_base* pos, BinaryPredicate binary_pred)
	{
		auto curr = pos->m_next;
		SizeType removed_count = 0;

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
		SizeType sz = 1;
		for (;;)
		{
			SizeType merge_count = 0;
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
