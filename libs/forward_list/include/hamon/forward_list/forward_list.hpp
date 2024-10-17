/**
 *	@file	forward_list.hpp
 *
 *	@brief	forward_list の定義
 */

#ifndef HAMON_FORWARD_LIST_FORWARD_LIST_HPP
#define HAMON_FORWARD_LIST_FORWARD_LIST_HPP

#include <hamon/forward_list/config.hpp>

#if defined(HAMON_USE_STD_FORWARD_LIST)

#include <forward_list>

namespace hamon
{

using std::forward_list;

}	// namespace hamon

#else

#include <hamon/algorithm.hpp>
#include <hamon/compare/detail/synth_three_way.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/iterator/detail/iter_value_type.hpp>
#include <hamon/memory.hpp>
#include <hamon/memory/detail/equals_allocator.hpp>
#include <hamon/memory/detail/propagate_allocator_on_copy.hpp>
#include <hamon/memory/detail/propagate_allocator_on_move.hpp>
#include <hamon/memory/detail/propagate_allocator_on_swap.hpp>
#include <hamon/ranges/detail/container_compatible_range.hpp>
#include <hamon/ranges.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <initializer_list>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

namespace hamon
{

namespace detail
{

template <typename T>
struct forward_list_impl;

struct forward_list_node_base
{
	forward_list_node_base*	m_next;

	HAMON_CXX11_CONSTEXPR
	forward_list_node_base()
		: m_next{nullptr}
	{}

	forward_list_node_base(forward_list_node_base const&) = default;

	HAMON_CXX14_CONSTEXPR
	forward_list_node_base(forward_list_node_base&& x)
		: m_next{hamon::exchange(x.m_next, nullptr)}
	{}

	forward_list_node_base& operator=(forward_list_node_base const&) = default;

	HAMON_CXX14_CONSTEXPR
	forward_list_node_base& operator=(forward_list_node_base&& x)
	{
		m_next = hamon::exchange(x.m_next, nullptr);
		return *this;
	}
};

template <typename T>
struct forward_list_node : public forward_list_node_base
{
	T	m_value;

	template <typename... Args>
	HAMON_CXX11_CONSTEXPR
	forward_list_node(Args&&... args)
		: m_value{hamon::forward<Args>(args)...}
	{}
};

template <typename T, typename D, bool Const>
struct forward_list_iterator
{
public:
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = D;
	using pointer           = hamon::conditional_t<Const, value_type const*, value_type*>;
	using reference         = hamon::conditional_t<Const, value_type const&, value_type&>;

private:
	using Node = forward_list_node<value_type>;

private:
	forward_list_node_base*	m_ptr;

public:
	HAMON_CXX11_CONSTEXPR
	forward_list_iterator() HAMON_NOEXCEPT
		: m_ptr(nullptr)
	{}

	HAMON_CXX11_CONSTEXPR
	forward_list_iterator(forward_list_node_base* ptr) HAMON_NOEXCEPT
		: m_ptr(ptr)
	{}

	template <bool C, typename = hamon::enable_if_t<C == Const || Const>>
	HAMON_CXX11_CONSTEXPR
	forward_list_iterator(forward_list_iterator<T, D, C> const& i) HAMON_NOEXCEPT
		: m_ptr(i.m_ptr)
	{}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	reference operator*() const HAMON_NOEXCEPT
	{
#if HAMON_CXX_STANDARD >= 14
		HAMON_ASSERT(m_ptr != nullptr);
#endif
		return static_cast<Node*>(m_ptr)->m_value;
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
	friend struct forward_list_iterator<T, D, !Const>;
	friend struct forward_list_impl<T>;
};

template <typename T>
HAMON_CXX11_CONSTEXPR
T const& get_value(forward_list_node_base* x)
{
	return static_cast<forward_list_node<T>*>(x)->m_value;
}

template <typename SizeType>
HAMON_CXX14_CONSTEXPR
forward_list_node_base* next(forward_list_node_base* x, SizeType sz)
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

inline HAMON_CXX14_CONSTEXPR
void splice_after(forward_list_node_base* pos, forward_list_node_base* first)
{
	auto next = first->m_next;
	first->m_next = next->m_next;
	next->m_next = pos->m_next;
	pos->m_next = next;
}

inline HAMON_CXX14_CONSTEXPR
void splice_after(forward_list_node_base* pos, forward_list_node_base* first, forward_list_node_base* last)
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

template <typename T, typename Compare>
HAMON_CXX14_CONSTEXPR void
merge_after(forward_list_node_base* x, forward_list_node_base* y, Compare comp)
{
	while (x->m_next && y->m_next)
	{
		if (comp(
			hamon::detail::get_value<T>(y->m_next),
			hamon::detail::get_value<T>(x->m_next)))
		{
			hamon::detail::splice_after(x, y);
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
template <typename T, typename Compare>
HAMON_CXX14_CONSTEXPR forward_list_node_base*
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
		else if (comp(
			hamon::detail::get_value<T>(y),
			hamon::detail::get_value<T>(x)))
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

template <typename T, typename Compare>
HAMON_CXX14_CONSTEXPR void
sort_after(forward_list_node_base* x, Compare comp)
{
	hamon::size_t sz = 1;
	for (;;)
	{
		hamon::size_t merge_count = 0;
		auto first = x;
		while (first->m_next)
		{
			auto middle = hamon::detail::next(first->m_next, sz);
			auto last   = hamon::detail::next(middle, sz);
			first = hamon::detail::inplace_merge_after<T>(first, middle, last, comp);
			++merge_count;
		}

		if (merge_count <= 1)
		{
			break;
		}

		sz *= 2;
	}
}

inline HAMON_CXX14_CONSTEXPR void
reverse_after(forward_list_node_base* x)
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

template <typename T>
struct forward_list_impl
{
public:
	using NodeBase = hamon::detail::forward_list_node_base;
	using Node = hamon::detail::forward_list_node<T>;

private:
	NodeBase	m_head{};

public:
	template <typename D, bool Const>
	static HAMON_CXX11_CONSTEXPR NodeBase*
	ToNode(forward_list_iterator<T, D, Const>& it)
	{
		return it.m_ptr;
	}

	HAMON_CXX11_CONSTEXPR
	NodeBase* BeforeBegin() const noexcept
	{
		return const_cast<NodeBase*>(hamon::addressof(m_head));
	}

	HAMON_CXX11_CONSTEXPR
	NodeBase* Begin() const noexcept
	{
		return const_cast<NodeBase*>(m_head.m_next);
	}

	HAMON_CXX11_CONSTEXPR
	NodeBase* End() const noexcept
	{
		return nullptr;
	}

	template <typename Allocator, typename SizeType, typename... Args>
	HAMON_CXX14_CONSTEXPR
	NodeBase* InsertNAfter(Allocator& alloc, NodeBase* pos, SizeType n, Args&&... args)
	{
		using AllocTraits = hamon::allocator_traits<Allocator>;

		HAMON_ASSERT(pos != nullptr);

		NodeBase* current = pos;
		NodeBase* next = pos->m_next;
		for (SizeType i = 0; i < n; ++i)
		{
			auto node = AllocTraits::allocate(alloc, 1);
			AllocTraits::construct(alloc, node, hamon::forward<Args>(args)...);
			current->m_next = node;
			current = current->m_next;
		}
		current->m_next = next;
		return current;
	}

	template <typename Allocator, typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR
	NodeBase* InsertRangeAfter(Allocator& alloc, NodeBase* pos, Iterator first, Sentinel last)
	{
		using AllocTraits = hamon::allocator_traits<Allocator>;

		HAMON_ASSERT(pos != nullptr);

		NodeBase* current = pos;
		NodeBase* next = pos->m_next;
		for (Iterator it = first; it != last; ++it)
		{
			auto node = AllocTraits::allocate(alloc, 1);
			AllocTraits::construct(alloc, node, *it);
			current->m_next = node;
			current = current->m_next;
		}
		HAMON_ASSERT(current != nullptr);
		current->m_next = next;
		return current;
	}

	template <typename Allocator>
	HAMON_CXX14_CONSTEXPR
	NodeBase* EraseAfter(Allocator& alloc, NodeBase* pos, NodeBase* last)
	{
		using AllocTraits = hamon::allocator_traits<Allocator>;

		HAMON_ASSERT(pos != nullptr);

		NodeBase* current = pos->m_next;
		while (current != last)
		{
			NodeBase* next = current->m_next;
			Node* p = static_cast<Node*>(current);
			AllocTraits::destroy(alloc, p);
			AllocTraits::deallocate(alloc, p, 1);
			current = next;
		}
		pos->m_next = last;
		return current;
	}

	template <typename Allocator>
	HAMON_CXX14_CONSTEXPR
	NodeBase* EraseAfter(Allocator& alloc, NodeBase* pos)
	{
		HAMON_ASSERT(pos != nullptr);
		HAMON_ASSERT(pos->m_next != nullptr);
		return EraseAfter(alloc, pos, pos->m_next->m_next);
	}

	template <typename Allocator>
	HAMON_CXX14_CONSTEXPR
	void Clear(Allocator& alloc)
	{
		this->EraseAfter(alloc, this->BeforeBegin(), this->End());
	}

	template <typename Allocator, typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR
	void Assign(Allocator& alloc, Iterator first, Sentinel last)
	{
		auto prev = this->BeforeBegin();
		auto end  = this->End();

		for (;;)
		{
			auto curr = prev->m_next;

			if (first == last)
			{
				this->EraseAfter(alloc, prev, end);
				return;
			}

			if (curr == end)
			{
				this->InsertRangeAfter(alloc, prev, first, last);
				return;
			}

			static_cast<Node*>(curr)->m_value = *first;

			prev = curr;
			++first;
		}

	}

	template <typename Allocator, typename SizeType, typename... Args>
	HAMON_CXX14_CONSTEXPR
	void Resize(Allocator& alloc, SizeType size, Args&&... args)
	{
		auto prev = this->BeforeBegin();
		auto end  = this->End();

		for (;;)
		{
			auto curr = prev->m_next;

			if (size == 0)
			{
				this->EraseAfter(alloc, prev, end);
				return;
			}

			if (curr == end)
			{
				this->InsertNAfter(alloc, prev, size, hamon::forward<Args>(args)...);
				return;
			}

			prev = curr;
			--size;
		}
	}

	template <typename Allocator, typename Predicate>
	HAMON_CXX14_CONSTEXPR
	hamon::size_t RemoveIf(Allocator& alloc, Predicate pred)
	{
		auto prev = this->BeforeBegin();
		hamon::size_t removed_count = 0;

		while (prev)
		{
			auto curr = prev->m_next;

			if (!curr)
			{
				break;
			}

			if (pred(static_cast<Node*>(curr)->m_value))
			{
				this->EraseAfter(alloc, prev);
				++removed_count;
			}
			else
			{
				prev = curr;
			}
		}

		return removed_count;
	}

	template <typename Allocator, typename BinaryPredicate>
	HAMON_CXX14_CONSTEXPR
	hamon::size_t Unique(Allocator& alloc, BinaryPredicate binary_pred)
	{
		auto curr = this->Begin();
		hamon::size_t removed_count = 0;

		while (curr)
		{
			auto next = curr->m_next;

			if (!next)
			{
				break;
			}

			if (binary_pred(
				static_cast<Node*>(curr)->m_value,
				static_cast<Node*>(next)->m_value))
			{
				this->EraseAfter(alloc, curr);
				++removed_count;
			}
			else
			{
				curr = next;
			}
		}

		return removed_count;
	}

	template <typename Compare>
	HAMON_CXX14_CONSTEXPR
	void Merge(forward_list_impl& x, Compare comp)
	{
		hamon::detail::merge_after<T>(this->BeforeBegin(), x.BeforeBegin(), comp);
	}

	template <typename Compare>
	HAMON_CXX14_CONSTEXPR
	void Sort(Compare comp)
	{
		hamon::detail::sort_after<T>(this->BeforeBegin(), comp);
	}

	HAMON_CXX14_CONSTEXPR
	void Reverse()
	{
		hamon::detail::reverse_after(this->BeforeBegin());
	}
};

}	// namespace detail

template <typename T, typename Allocator = hamon::allocator<T>>
class forward_list
{
private:
	using Impl = hamon::detail::forward_list_impl<T>;
	using Node = typename Impl::Node;
	using NodeAllocator = typename hamon::allocator_traits<Allocator>::template rebind_alloc<Node>;
	using NodeAllocTraits = typename hamon::allocator_traits<Allocator>::template rebind_traits<Node>;

private:
	HAMON_NO_UNIQUE_ADDRESS	NodeAllocator	m_allocator;
	Impl	m_impl{};

public:
	// types
	using value_type      = T;
	using allocator_type  = Allocator;
	using pointer         = typename hamon::allocator_traits<Allocator>::pointer;
	using const_pointer   = typename hamon::allocator_traits<Allocator>::const_pointer;
	using reference       = value_type&;
	using const_reference = value_type const&;
	using size_type       = typename hamon::allocator_traits<Allocator>::size_type;       // see [container.requirements]
	using difference_type = typename hamon::allocator_traits<Allocator>::difference_type; // see [container.requirements]
	using iterator        = hamon::detail::forward_list_iterator<T, difference_type, false>; // see [container.requirements]
	using const_iterator  = hamon::detail::forward_list_iterator<T, difference_type, true>;  // see [container.requirements]

	// [forward.list.cons], construct/copy/destroy
	HAMON_CXX11_CONSTEXPR
	forward_list() : forward_list(Allocator()) {}

	HAMON_CXX11_CONSTEXPR explicit
	forward_list(Allocator const& a)
		: m_allocator(a)
	{
		// [forward.list.cons]/1
	}

	HAMON_CXX14_CONSTEXPR explicit
	forward_list(size_type n, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [forward.list.cons]/4
		m_impl.InsertNAfter(m_allocator, m_impl.BeforeBegin(), n);
	}

	HAMON_CXX14_CONSTEXPR
	forward_list(size_type n, T const& value, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [forward.list.cons]/7
		m_impl.InsertNAfter(m_allocator, m_impl.BeforeBegin(), n, value);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	forward_list(InputIterator first, InputIterator last, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [forward.list.cons]/9
		m_impl.InsertRangeAfter(m_allocator, m_impl.BeforeBegin(), first, last);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR
	forward_list(hamon::from_range_t, R&& rg, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [forward.list.cons]/11
		m_impl.InsertRangeAfter(
			m_allocator,
			m_impl.BeforeBegin(),
			hamon::ranges::begin(rg),
			hamon::ranges::end(rg));
	}

	HAMON_CXX14_CONSTEXPR
	forward_list(forward_list const& x)
		: m_allocator(NodeAllocTraits::select_on_container_copy_construction(x.m_allocator))
	{
		m_impl.InsertRangeAfter(
			m_allocator,
			m_impl.BeforeBegin(),
			hamon::ranges::begin(x),
			hamon::ranges::end(x));
	}

	HAMON_CXX14_CONSTEXPR
	forward_list(forward_list&& x)
		: m_allocator(hamon::move(x.m_allocator))
		, m_impl(hamon::move(x.m_impl))
	{}

	HAMON_CXX14_CONSTEXPR
	forward_list(forward_list const& x, hamon::type_identity_t<Allocator> const& a)
		: m_allocator(a)
	{
		m_impl.InsertRangeAfter(
			m_allocator,
			m_impl.BeforeBegin(),
			hamon::ranges::begin(x),
			hamon::ranges::end(x));
	}

// TODO
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
#define HAMON_IF_CONSTEXPR	if constexpr
#else
#define HAMON_IF_CONSTEXPR	if
#endif

	HAMON_CXX14_CONSTEXPR
	forward_list(forward_list&& x, hamon::type_identity_t<Allocator> const& a)
		: m_allocator(a)
	{
		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			// アロケータが異なる場合は、
			// 要素をムーブ代入しなければいけない = 要素をstealすることはできない。
			m_impl.InsertRangeAfter(m_allocator, m_impl.BeforeBegin(),
				hamon::make_move_iterator(hamon::ranges::begin(x)),
				hamon::make_move_iterator(hamon::ranges::end(x)));
			return;
		}

		// 要素をsteal
		m_impl = hamon::move(x.m_impl);
	}

	HAMON_CXX14_CONSTEXPR
	forward_list(std::initializer_list<T> il, Allocator const& a = Allocator())
		: forward_list(il.begin(), il.end(), a)
	{}

	HAMON_CXX20_CONSTEXPR
	~forward_list()
	{
		clear();
	}

	HAMON_CXX14_CONSTEXPR
	forward_list& operator=(forward_list const& x)
	{
		if (hamon::addressof(x) == this)
		{
			return *this;
		}

		HAMON_IF_CONSTEXPR (NodeAllocTraits::propagate_on_container_copy_assignment::value)
		{
			if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
			{
				// アロケータを伝播させる場合は、
				// 今のアロケータで確保した要素を破棄しなければいけない
				m_impl.Clear(m_allocator);

				// アロケータを伝播
				hamon::detail::propagate_allocator_on_copy(m_allocator, x.m_allocator);
			}
		}

		// 要素をコピー代入
		m_impl.Assign(m_allocator, hamon::ranges::begin(x), hamon::ranges::end(x));

		return *this;
	}

	HAMON_CXX14_CONSTEXPR
	forward_list& operator=(forward_list&& x)
		noexcept(hamon::allocator_traits<Allocator>::is_always_equal::value)
	{
		if (hamon::addressof(x) == this)
		{
			return *this;
		}

		HAMON_IF_CONSTEXPR (!NodeAllocTraits::propagate_on_container_move_assignment::value)
		{
			if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
			{
				// アロケータを伝播させない場合は、
				// 要素をムーブ代入しなければいけない = 要素をstealすることはできない。
				m_impl.Assign(m_allocator,
					hamon::make_move_iterator(hamon::ranges::begin(x)),
					hamon::make_move_iterator(hamon::ranges::end(x)));
				return *this;
			}
		}

		// 今の要素を破棄
		m_impl.Clear(m_allocator);

		// アロケータを伝播
		hamon::detail::propagate_allocator_on_move(m_allocator, x.m_allocator);

		// 要素をsteal
		m_impl = hamon::move(x.m_impl);

		return *this;
	}

	HAMON_CXX14_CONSTEXPR
	forward_list& operator=(std::initializer_list<T> il)
	{
		// [sequence.reqmts]/17
		this->assign(il.begin(), il.end());

		// [sequence.reqmts]/18
		return *this;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	void assign(InputIterator first, InputIterator last)
	{
		// [sequence.reqmts]/58
		m_impl.Assign(m_allocator, first, last);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR
	void assign_range(R&& rg)
	{
		// [sequence.reqmts]/62
		m_impl.Assign(m_allocator, hamon::ranges::begin(rg), hamon::ranges::end(rg));
	}

	HAMON_CXX14_CONSTEXPR
	void assign(size_type n, T const& t)
	{
		// [sequence.reqmts]/66
		this->clear();
		this->insert_after(before_begin(), n, t);
	}

	HAMON_CXX14_CONSTEXPR
	void assign(std::initializer_list<T> il)
	{
		// [sequence.reqmts]/63
		this->assign(il.begin(), il.end());
	}

	HAMON_CXX11_CONSTEXPR allocator_type get_allocator() const noexcept
	{
		return static_cast<allocator_type>(m_allocator);
	}

	// [forward.list.iter], iterators
	HAMON_CXX14_CONSTEXPR iterator before_begin() noexcept
	{
		// [forward.list.iter]/2
		return iterator(m_impl.BeforeBegin());
	}

	HAMON_CXX11_CONSTEXPR const_iterator before_begin() const noexcept
	{
		// [forward.list.iter]/2
		return const_iterator(m_impl.BeforeBegin());
	}

	HAMON_CXX14_CONSTEXPR iterator begin() noexcept
	{
		return iterator(m_impl.Begin());
	}

	HAMON_CXX11_CONSTEXPR const_iterator begin() const noexcept
	{
		return const_iterator(m_impl.Begin());
	}

	HAMON_CXX14_CONSTEXPR iterator end() noexcept
	{
		return iterator(m_impl.End());
	}

	HAMON_CXX11_CONSTEXPR const_iterator end() const noexcept
	{
		return const_iterator(m_impl.End());
	}

	HAMON_CXX11_CONSTEXPR const_iterator cbegin() const noexcept
	{
		return this->begin();
	}

	HAMON_CXX11_CONSTEXPR const_iterator cbefore_begin() const noexcept
	{
		// [forward.list.iter]/1
		return this->before_begin();
	}

	HAMON_CXX11_CONSTEXPR const_iterator cend() const noexcept
	{
		return this->end();
	}

	// capacity
	HAMON_CXX11_CONSTEXPR bool empty() const noexcept
	{
		return this->begin() == this->end();
	}

	HAMON_CXX11_CONSTEXPR size_type max_size() const noexcept
	{
		return hamon::min(
			static_cast<size_type>(hamon::numeric_limits<difference_type>::max()),
			static_cast<size_type>(NodeAllocTraits::max_size(m_allocator)));
	}

	// [forward.list.access], element access
	HAMON_CXX14_CONSTEXPR
	reference front()
	{
		// [forward.list.access]/1
		return *this->begin();
	}

	HAMON_CXX11_CONSTEXPR const_reference front() const
	{
		// [forward.list.access]/1
		return *this->begin();
	}

	// [forward.list.modifiers], modifiers
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR
	reference emplace_front(Args&&... args)
	{
		// [forward.list.modifiers]/2
		m_impl.InsertNAfter(m_allocator, m_impl.BeforeBegin(), 1, hamon::forward<Args>(args)...);
		return front();
	}

	HAMON_CXX14_CONSTEXPR
	void push_front(T const& x)
	{
		// [forward.list.modifiers]/3
		m_impl.InsertNAfter(m_allocator, m_impl.BeforeBegin(), 1, x);
	}

	HAMON_CXX14_CONSTEXPR
	void push_front(T&& x)
	{
		// [forward.list.modifiers]/3
		m_impl.InsertNAfter(m_allocator, m_impl.BeforeBegin(), 1, hamon::move(x));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR
	void prepend_range(R&& rg)
	{
		// [forward.list.modifiers]/4
		m_impl.InsertRangeAfter(
			m_allocator,
			m_impl.BeforeBegin(),
			hamon::ranges::begin(rg),
			hamon::ranges::end(rg));
	}

	HAMON_CXX14_CONSTEXPR
	void pop_front()
	{
		// [forward.list.modifiers]/5
		this->erase_after(this->before_begin());
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR
	iterator emplace_after(const_iterator position, Args&&... args)
	{
		// [forward.list.modifiers]/23
		return iterator{m_impl.InsertNAfter(
			m_allocator,
			m_impl.ToNode(position),
			1, hamon::forward<Args>(args)...)};
	}

	HAMON_CXX14_CONSTEXPR
	iterator insert_after(const_iterator position, T const& x)
	{
		// [forward.list.modifiers]/7
		return iterator{m_impl.InsertNAfter(
			m_allocator,
			m_impl.ToNode(position),
			1, x)};
	}

	HAMON_CXX14_CONSTEXPR
	iterator insert_after(const_iterator position, T&& x)
	{
		// [forward.list.modifiers]/10
		return iterator{m_impl.InsertNAfter(
			m_allocator,
			m_impl.ToNode(position),
			1, hamon::move(x))};
	}

	HAMON_CXX14_CONSTEXPR
	iterator insert_after(const_iterator position, size_type n, T const& x)
	{
		// [forward.list.modifiers]/13
		return iterator{m_impl.InsertNAfter(
			m_allocator,
			m_impl.ToNode(position),
			n, x)};
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	iterator insert_after(const_iterator position, InputIterator first, InputIterator last)
	{
		// [forward.list.modifiers]/16
		return iterator{m_impl.InsertRangeAfter(
			m_allocator,
			m_impl.ToNode(position),
			first, last)};
	}

	HAMON_CXX14_CONSTEXPR
	iterator insert_after(const_iterator position, std::initializer_list<T> il)
	{
		// [forward.list.modifiers]/21
		return this->insert_after(position, il.begin(), il.end());
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR
	iterator insert_range_after(const_iterator position, R&& rg)
	{
		// [forward.list.modifiers]/19
		return iterator{m_impl.InsertRangeAfter(
			m_allocator,
			m_impl.ToNode(position),
			hamon::ranges::begin(rg),
			hamon::ranges::end(rg))};
	}

	HAMON_CXX14_CONSTEXPR
	iterator erase_after(const_iterator position)
	{
		// [forward.list.modifiers]/26
		// [forward.list.modifiers]/27
		return iterator{m_impl.EraseAfter(
			m_allocator,
			m_impl.ToNode(position))};
	}

	HAMON_CXX14_CONSTEXPR
	iterator erase_after(const_iterator position, const_iterator last)
	{
		// [forward.list.modifiers]/30
		// [forward.list.modifiers]/31
		return iterator{m_impl.EraseAfter(
			m_allocator,
			m_impl.ToNode(position),
			m_impl.ToNode(last))};
	}

	HAMON_CXX14_CONSTEXPR
	void swap(forward_list& x)
		noexcept(hamon::allocator_traits<Allocator>::is_always_equal::value)
	{
		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			hamon::detail::propagate_allocator_on_swap(m_allocator, x.m_allocator);
		}
		hamon::swap(m_impl, x.m_impl);
	}

	HAMON_CXX14_CONSTEXPR
	void resize(size_type sz)
	{
		// [forward.list.modifiers]/34
		m_impl.Resize(m_allocator, sz);
	}

	HAMON_CXX14_CONSTEXPR
	void resize(size_type sz, value_type const& c)
	{
		// [forward.list.modifiers]/36
		m_impl.Resize(m_allocator, sz, c);
	}

	HAMON_CXX14_CONSTEXPR
	void clear() noexcept
	{
		// [forward.list.modifiers]/37
		m_impl.Clear(m_allocator);
	}

	// [forward.list.ops], forward_list operations
	HAMON_CXX14_CONSTEXPR
	void splice_after(const_iterator position, forward_list& x)
	{
		// [forward.list.ops]/3
		this->splice_after(position, x, x.before_begin(), x.end());
	}

	HAMON_CXX14_CONSTEXPR
	void splice_after(const_iterator position, forward_list&& x)
	{
		// [forward.list.ops]/3
		this->splice_after(position, x, x.before_begin(), x.end());
	}

	HAMON_CXX14_CONSTEXPR
	void splice_after(const_iterator position, forward_list& x, const_iterator i)
	{
		HAMON_ASSERT(hamon::detail::equals_allocator(m_allocator, x.m_allocator));

		// [forward.list.ops]/7
		hamon::detail::splice_after(m_impl.ToNode(position), x.m_impl.ToNode(i));
	}

	HAMON_CXX14_CONSTEXPR
	void splice_after(const_iterator position, forward_list&& x, const_iterator i)
	{
		// [forward.list.ops]/7
		this->splice_after(position, x, i);
	}

	HAMON_CXX14_CONSTEXPR
	void splice_after(const_iterator position, forward_list& x, const_iterator first, const_iterator last)
	{
		HAMON_ASSERT(hamon::detail::equals_allocator(m_allocator, x.m_allocator));

		// [forward.list.ops]/11
		hamon::detail::splice_after(m_impl.ToNode(position), x.m_impl.ToNode(first), x.m_impl.ToNode(last));
	}

	HAMON_CXX14_CONSTEXPR
	void splice_after(const_iterator position, forward_list&& x, const_iterator first, const_iterator last)
	{
		// [forward.list.ops]/11
		this->splice_after(position, x, first, last);
	}

	HAMON_CXX14_CONSTEXPR
	size_type remove(T const& value)
	{
		// [forward.list.ops]/13
		// [forward.list.ops]/14
		return this->remove_if([&](T const& x) { return x == value; });
	}

	template <typename Predicate>
	HAMON_CXX14_CONSTEXPR
	size_type remove_if(Predicate pred)
	{
		// [forward.list.ops]/13
		// [forward.list.ops]/14
		return static_cast<size_type>(m_impl.RemoveIf(m_allocator, pred));
	}

	HAMON_CXX14_CONSTEXPR
	size_type unique()
	{
		// [forward.list.ops]/18
		return this->unique(hamon::equal_to<>{});
	}

	template <typename BinaryPredicate>
	HAMON_CXX14_CONSTEXPR
	size_type unique(BinaryPredicate binary_pred)
	{
		// [forward.list.ops]/20
		// [forward.list.ops]/21
		return static_cast<size_type>(m_impl.Unique(m_allocator, binary_pred));
	}

	HAMON_CXX14_CONSTEXPR
	void merge(forward_list& x)
	{
		// [forward.list.ops]/24
		this->merge(x, hamon::less<>{});
	}

	HAMON_CXX14_CONSTEXPR
	void merge(forward_list&& x)
	{
		// [forward.list.ops]/24
		this->merge(hamon::move(x), hamon::less<>{});
	}

	template <typename Compare>
	HAMON_CXX14_CONSTEXPR
	void merge(forward_list& x, Compare comp)
	{
		// [forward.list.ops]/26
		if (hamon::addressof(x) == this)
		{
			return;
		}

		m_impl.Merge(x.m_impl, comp);
	}

	template <typename Compare>
	HAMON_CXX14_CONSTEXPR
	void merge(forward_list&& x, Compare comp)
	{
		// [forward.list.ops]/26
		this->merge(x, comp);
	}

	HAMON_CXX14_CONSTEXPR
	void sort()
	{
		// [forward.list.ops]/29
		this->sort(hamon::less<>{});
	}

	template <typename Compare>
	HAMON_CXX14_CONSTEXPR
	void sort(Compare comp)
	{
		// [forward.list.ops]/29
		m_impl.Sort(comp);
	}

	HAMON_CXX14_CONSTEXPR
	void reverse() noexcept
	{
		// [forward.list.ops]/32
		m_impl.Reverse();
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	typename Allocator = hamon::allocator<hamon::detail::iter_value_type<InputIterator>>>
forward_list(InputIterator, InputIterator, Allocator = Allocator())
	->forward_list<hamon::detail::iter_value_type<InputIterator>, Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Allocator = hamon::allocator<ranges::range_value_t<R>>>
forward_list(hamon::from_range_t, R&&, Allocator = Allocator())
	->forward_list<ranges::range_value_t<R>, Allocator>;

#endif

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator==(forward_list<T, Allocator> const& x, forward_list<T, Allocator> const& y)
{
	return hamon::equal(x.begin(), x.end(), y.begin(), y.end());
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
hamon::detail::synth_three_way_result<T>
operator<=>(forward_list<T, Allocator> const&x, forward_list<T, Allocator> const&y)
{
	return hamon::lexicographical_compare_three_way(
		x.begin(), x.end(),
		y.begin(), y.end(),
		hamon::detail::synth_three_way);
}

#else

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator!=(forward_list<T, Allocator> const& x, forward_list<T, Allocator> const& y)
{
	return !(x == y);
}

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator<(forward_list<T, Allocator> const& x, forward_list<T, Allocator> const& y)
{
	return hamon::lexicographical_compare(
		x.begin(), x.end(),
		y.begin(), y.end());
}

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator>(forward_list<T, Allocator> const& x, forward_list<T, Allocator> const& y)
{
	return y < x;
}

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator<=(forward_list<T, Allocator> const& x, forward_list<T, Allocator> const& y)
{
	return !(x > y);
}

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator>=(forward_list<T, Allocator> const& x, forward_list<T, Allocator> const& y)
{
	return !(x < y);
}

#endif

template <typename T, typename Allocator>
HAMON_CXX14_CONSTEXPR
void swap(forward_list<T, Allocator>& x, forward_list<T, Allocator>& y)
	noexcept(noexcept(x.swap(y)))
{
	x.swap(y);
}

#if 0	// TODO
namespace pmr
{

template <class T>
using forward_list = hamon::forward_list<T, polymorphic_allocator<T>>;

}	// namespace pmr
#endif

}	// namespace hamon

HAMON_WARNING_POP()

#endif

#endif // HAMON_FORWARD_LIST_FORWARD_LIST_HPP
