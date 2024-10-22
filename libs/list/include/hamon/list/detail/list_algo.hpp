/**
 *	@file	list_algo.hpp
 *
 *	@brief	list_algo の定義
 */

#ifndef HAMON_LIST_DETAIL_LIST_ALGO_HPP
#define HAMON_LIST_DETAIL_LIST_ALGO_HPP

#include <hamon/list/detail/list_node.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T, typename Allocator>
struct list_algo
{
	using ValueType = T;
	using AllocatorType = Allocator;
	using AllocTraits = hamon::allocator_traits<Allocator>;
	using SizeType    = typename AllocTraits::size_type;
	using NodeBase = hamon::detail::list_node_base;
	using Node     = hamon::detail::list_node<T>;

	static HAMON_CXX11_CONSTEXPR
	T& get_value(NodeBase* x) HAMON_NOEXCEPT
	{
		return static_cast<Node*>(x)->m_value;
	}

	static HAMON_CXX14_CONSTEXPR NodeBase*
	next(NodeBase* x, SizeType sz, NodeBase* bound) HAMON_NOEXCEPT
	{
		for (; 0 < sz; --sz)
		{
			if (x == bound)
			{
				break;
			}

			x = x->m_next;
		}
		return x;
	}

	static HAMON_CXX14_CONSTEXPR SizeType
	distance(NodeBase* first, NodeBase* last) HAMON_NOEXCEPT
	{
		SizeType result = 0;
		while (first != last)
		{
			++result;
			first = first->m_next;
		}
		return result;
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

	template <typename... Args>
	static HAMON_CXX20_CONSTEXPR NodeBase*
	insert(Allocator& alloc, SizeType& size, NodeBase* pos, Args&&... args)
	{
		HAMON_ASSERT(pos != nullptr);
		auto node = AllocTraits::allocate(alloc, 1);	// may throw
		AllocTraits::construct(alloc, node, hamon::forward<Args>(args)...);	// may throw
		auto prev = pos->m_prev;
		prev->m_next = node;
		node->m_prev = prev;
		node->m_next = pos;
		pos->m_prev  = node;
		++size;
		return node;
	}

HAMON_WARNING_POP()

	template <typename... Args>
	static HAMON_CXX20_CONSTEXPR NodeBase*
	insert_n(Allocator& alloc, SizeType& size, NodeBase* pos, SizeType n, Args&&... args)
	{
		HAMON_ASSERT(pos != nullptr);
		NodeBase* head = nullptr;
#if !defined(HAMON_NO_EXCEPTIONS)
		try
#endif
		{
			for (SizeType i = 0; i < n; ++i)
			{
				auto r = insert(alloc, size, pos, hamon::forward<Args>(args)...);	// may throw
				if (head == nullptr)
				{
					head = r;
				}
			}
			return head;
		}
#if !defined(HAMON_NO_EXCEPTIONS)
		catch (...)
		{
			if (head)
			{
				erase_range(alloc, size, head, pos);
			}
			throw;
		}
#endif
	}

	template <typename Iterator, typename Sentinel>
	static HAMON_CXX20_CONSTEXPR NodeBase*
	insert_range(Allocator& alloc, SizeType& size, NodeBase* pos, Iterator first, Sentinel last)
	{
		HAMON_ASSERT(pos != nullptr);
		NodeBase* head = nullptr;
#if !defined(HAMON_NO_EXCEPTIONS)
		try
#endif
		{
			for (Iterator it = first; it != last; ++it)
			{
				auto r = insert(alloc, size, pos, *it);	// may throw
				if (head == nullptr)
				{
					head = r;
				}
			}
			return head;
		}
#if !defined(HAMON_NO_EXCEPTIONS)
		catch (...)
		{
			if (head)
			{
				erase_range(alloc, size, head, pos);
			}
			throw;
		}
#endif
	}

	static HAMON_CXX20_CONSTEXPR NodeBase*
	erase_range(Allocator& alloc, SizeType& size, NodeBase* first, NodeBase* last) HAMON_NOEXCEPT
	{
		HAMON_ASSERT(first != nullptr);
		auto prev = first->m_prev;
		auto current = first;
		while (current != last)
		{
			auto next = current->m_next;
			auto p = static_cast<Node*>(current);
			AllocTraits::destroy(alloc, p);
			AllocTraits::deallocate(alloc, p, 1);
			--size;
			current = next;
		}
		prev->m_next = last;
		last->m_prev = prev;
		return last;
	}

	static HAMON_CXX20_CONSTEXPR NodeBase*
	erase(Allocator& alloc, SizeType& size, NodeBase* pos) HAMON_NOEXCEPT
	{
		HAMON_ASSERT(pos != nullptr);
		return erase_range(alloc, size, pos, pos->m_next);
	}

	static HAMON_CXX14_CONSTEXPR void
	assign_n(Allocator& alloc, SizeType& size, NodeBase* head, NodeBase* tail, SizeType n, T const& t)
	{
		for (;;)
		{
			if (n == 0)
			{
				erase_range(alloc, size, head, tail);
				return;
			}

			if (head == tail)
			{
				insert_n(alloc, size, head, n, t);	// may throw
				return;
			}

			get_value(head) = t;
			head = head->m_next;
			--n;
		}
	}

	template <typename Iterator, typename Sentinel>
	static HAMON_CXX14_CONSTEXPR void
	assign_range(Allocator& alloc, SizeType& size, NodeBase* head, NodeBase* tail, Iterator first, Sentinel last)
	{
		for (;;)
		{
			if (first == last)
			{
				erase_range(alloc, size, head, tail);
				return;
			}

			if (head == tail)
			{
				insert_range(alloc, size, head, first, last);	// may throw
				return;
			}

			get_value(head) = *first;
			head = head->m_next;
			++first;
		}
	}

	template <typename... Args>
	static HAMON_CXX14_CONSTEXPR void
	resize(Allocator& alloc, SizeType& size, NodeBase* head, NodeBase* tail, SizeType sz, Args&&... args)
	{
		for (;;)
		{
			if (sz == 0)
			{
				erase_range(alloc, size, head, tail);
				return;
			}

			if (head == tail)
			{
				insert_n(alloc, size, head, sz, hamon::forward<Args>(args)...);	// may throw
				return;
			}

			head = head->m_next;
			--sz;
		}
	}

	static HAMON_CXX14_CONSTEXPR void
	splice_range(NodeBase* pos, NodeBase* first, NodeBase* last) HAMON_NOEXCEPT
	{
		if (first == last ||
			pos == first ||
			pos == last)
		{
			return;
		}

		auto first_prev = first->m_prev;
		auto last_prev  = last->m_prev;
		auto pos_prev   = pos->m_prev;

		first_prev->m_next = last;
		last_prev->m_next  = pos;
		pos_prev->m_next   = first;

		pos->m_prev   = last_prev;
		last->m_prev  = first_prev;
		first->m_prev = pos_prev;
	}

	template <typename Predicate>
	static HAMON_CXX14_CONSTEXPR SizeType
	remove_if(Allocator& alloc, SizeType& size, NodeBase* head, NodeBase* tail, Predicate pred)
	{
		SizeType removed_count = 0;

		while (head != tail)
		{
			if (pred(get_value(head)))	// may throw
			{
				head = erase(alloc, size, head);
				++removed_count;
			}
			else
			{
				head = head->m_next;
			}
		}

		return removed_count;
	}

	template <typename BinaryPredicate>
	static HAMON_CXX14_CONSTEXPR SizeType
	unique(Allocator& alloc, SizeType& size, NodeBase* head, NodeBase* tail, BinaryPredicate binary_pred)
	{
		SizeType removed_count = 0;

		while (head != tail)
		{
			auto next = head->m_next;

			if (next == tail)
			{
				break;
			}

			if (binary_pred(get_value(head), get_value(next)))	// may throw
			{
				erase(alloc, size, next);
				++removed_count;
			}
			else
			{
				head = next;
			}
		}

		return removed_count;
	}

	// 2つの連続したソート済みイテレータ範囲 [first, middle) と [middle, last) をマージする。
	template <typename Compare>
	static HAMON_CXX14_CONSTEXPR void
	inplace_merge(NodeBase* first, NodeBase* middle, NodeBase* last, Compare comp)
	{
		HAMON_ASSERT(first != nullptr);
		HAMON_ASSERT(middle != nullptr);
		HAMON_ASSERT(last != nullptr);

		if (middle == last)
		{
			return;
		}

		NodeBase* x = first;
		NodeBase* y = middle;
		NodeBase* tail = nullptr;

		while (x != middle || y != last)
		{
			NodeBase* e = nullptr;
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
			else if (comp(get_value(y), get_value(x)))	// may throw
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
				e->m_prev = tail;
			}
			else
			{
				first->m_prev->m_next = e;
				e->m_prev = first->m_prev;
			}

			tail = e;
		}

		HAMON_ASSERT(tail != nullptr);

		tail->m_next = last;
		last->m_prev = tail;
	}

	template <typename Compare>
	static HAMON_CXX14_CONSTEXPR void
	merge(NodeBase* head1, NodeBase* tail1, NodeBase* head2, NodeBase* tail2, Compare comp)
	{
		if (head2 == tail2)
		{
			return;
		}

		if (head1 == tail1)
		{
			splice_range(tail1, head2, tail2);
			return;
		}

		splice_range(tail1, head2, tail2);
		inplace_merge(head1, head2, tail1, comp);	// may throw
	}

	template <typename Compare>
	static HAMON_CXX14_CONSTEXPR void
	sort(NodeBase* head, NodeBase* tail, Compare comp)
	{
		auto head_prev = head->m_prev;
		SizeType sz = 1;
		for (;;)
		{
			SizeType merge_count = 0;
			auto first = head_prev->m_next;
			while (first != tail)
			{
				auto middle = next(first, sz, tail);
				auto last   = next(middle, sz, tail);
				inplace_merge(first, middle, last, comp);	// may throw
				first = last;
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
	reverse(NodeBase* head, NodeBase* tail) HAMON_NOEXCEPT
	{
		for (;;)
		{
			hamon::swap(head->m_prev, head->m_next);
			if (head == tail)
			{
				break;
			}
			head = head->m_prev;
		}
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_LIST_DETAIL_LIST_ALGO_HPP
