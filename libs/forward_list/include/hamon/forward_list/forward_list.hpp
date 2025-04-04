/**
 *	@file	forward_list.hpp
 *
 *	@brief	forward_list の定義
 */

#ifndef HAMON_FORWARD_LIST_FORWARD_LIST_HPP
#define HAMON_FORWARD_LIST_FORWARD_LIST_HPP

#include <hamon/forward_list/forward_list_fwd.hpp>
#include <hamon/forward_list/config.hpp>

#if !defined(HAMON_USE_STD_FORWARD_LIST)

#include <hamon/forward_list/detail/forward_list_algo.hpp>
#include <hamon/forward_list/detail/forward_list_iterator.hpp>
#include <hamon/forward_list/detail/forward_list_node.hpp>
#include <hamon/algorithm/equal.hpp>
#include <hamon/algorithm/lexicographical_compare.hpp>
#include <hamon/algorithm/lexicographical_compare_three_way.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/compare/detail/synth_three_way.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/container/detail/container_compatible_range.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/iterator/detail/iter_value_type.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/make_move_iterator.hpp>
#include <hamon/limits/numeric_limits.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/detail/equals_allocator.hpp>
#include <hamon/memory/detail/propagate_allocator_on_copy.hpp>
#include <hamon/memory/detail/propagate_allocator_on_move.hpp>
#include <hamon/memory/detail/propagate_allocator_on_swap.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

namespace hamon
{

template <typename T, typename Allocator>
class forward_list
{
private:
	using NodeBase = hamon::detail::forward_list_node_base;
	using Node     = hamon::detail::forward_list_node<T>;
	using NodeAllocator   = typename hamon::allocator_traits<Allocator>::template rebind_alloc<Node>;
	using NodeAllocTraits = typename hamon::allocator_traits<Allocator>::template rebind_traits<Node>;
	using Algo = hamon::detail::forward_list_algo<T, NodeAllocator>;

private:
	HAMON_NO_UNIQUE_ADDRESS	NodeAllocator	m_allocator;
	NodeBase	m_head{};

private:
	HAMON_CXX11_CONSTEXPR NodeBase*
	before_head() const HAMON_NOEXCEPT
	{
		return const_cast<NodeBase*>(hamon::addressof(m_head));
	}

public:
	// types
	using value_type      = T;
	using allocator_type  = Allocator;
	using pointer         = typename hamon::allocator_traits<Allocator>::pointer;
	using const_pointer   = typename hamon::allocator_traits<Allocator>::const_pointer;
	using reference       = value_type&;
	using const_reference = value_type const&;
	using size_type       = typename hamon::allocator_traits<Allocator>::size_type;
	using difference_type = typename hamon::allocator_traits<Allocator>::difference_type;
	using iterator        = hamon::detail::forward_list_iterator<T, Allocator, false>;
	using const_iterator  = hamon::detail::forward_list_iterator<T, Allocator, true>;

	// [forward.list.cons], construct/copy/destroy
	HAMON_CXX11_CONSTEXPR
	forward_list() HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_default_constructible<NodeAllocator>::value)
		: forward_list(Allocator())
	{}

	HAMON_CXX11_CONSTEXPR explicit
	forward_list(Allocator const& a) HAMON_NOEXCEPT	// noexcept as an extension
		: m_allocator(a)
	{
		// [forward.list.cons]/1
	}

	HAMON_CXX14_CONSTEXPR explicit
	forward_list(size_type n, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [forward.list.cons]/4
		Algo::insert_n_after(m_allocator, this->before_head(), n);
	}

	HAMON_CXX14_CONSTEXPR
	forward_list(size_type n, T const& value, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [forward.list.cons]/7
		Algo::insert_n_after(m_allocator, this->before_head(), n, value);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	forward_list(InputIterator first, InputIterator last, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [forward.list.cons]/9
		Algo::insert_range_after(m_allocator, this->before_head(), first, last);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR
	forward_list(hamon::from_range_t, R&& rg, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [forward.list.cons]/11
		Algo::insert_range_after(m_allocator, this->before_head(), hamon::forward<R>(rg));
	}

	HAMON_CXX14_CONSTEXPR
	forward_list(forward_list const& x)
		: m_allocator(NodeAllocTraits::select_on_container_copy_construction(x.m_allocator))
	{
		Algo::insert_range_after(m_allocator, this->before_head(), x);
	}

	HAMON_CXX14_CONSTEXPR
	forward_list(forward_list&& x) HAMON_NOEXCEPT	// noexcept as an extension
		: m_allocator(hamon::move(x.m_allocator))
		, m_head(hamon::move(x.m_head))
	{}

	HAMON_CXX14_CONSTEXPR
	forward_list(forward_list const& x, hamon::type_identity_t<Allocator> const& a)
		: m_allocator(a)
	{
		Algo::insert_range_after(m_allocator, this->before_head(), x);
	}

	HAMON_CXX14_CONSTEXPR
	forward_list(forward_list&& x, hamon::type_identity_t<Allocator> const& a)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::allocator_traits<Allocator>::is_always_equal::value)
		: m_allocator(a)
	{
		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			// アロケータが異なる場合は、
			// 要素をムーブ代入しなければいけない = 要素をstealすることはできない。
			Algo::insert_range_after(m_allocator, this->before_head(),
				hamon::make_move_iterator(hamon::ranges::begin(x)),
				hamon::make_move_iterator(hamon::ranges::end(x)));
			return;
		}

		// 要素をsteal
		m_head = hamon::move(x.m_head);
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

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
		if constexpr (NodeAllocTraits::propagate_on_container_copy_assignment::value)
#else
		if           (NodeAllocTraits::propagate_on_container_copy_assignment::value)
#endif
		{
			if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
			{
				// アロケータを伝播させる場合は、
				// 今のアロケータで確保した要素を破棄しなければいけない
				this->clear();

				// アロケータを伝播
				hamon::detail::propagate_allocator_on_copy(m_allocator, x.m_allocator);
			}
		}

		// 要素をコピー代入
		Algo::assign_range_after(m_allocator, this->before_head(), x);

		return *this;
	}

	HAMON_CXX14_CONSTEXPR
	forward_list& operator=(forward_list&& x)
		HAMON_NOEXCEPT_IF(hamon::allocator_traits<Allocator>::is_always_equal::value)
	{
		if (hamon::addressof(x) == this)
		{
			return *this;
		}

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
		if constexpr (!NodeAllocTraits::propagate_on_container_move_assignment::value)
#else
		if           (!NodeAllocTraits::propagate_on_container_move_assignment::value)
#endif
		{
			if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
			{
				// アロケータを伝播させない場合は、
				// 要素をムーブ代入しなければいけない = 要素をstealすることはできない。
				Algo::assign_range_after(m_allocator, this->before_head(),
					hamon::make_move_iterator(hamon::ranges::begin(x)),
					hamon::make_move_iterator(hamon::ranges::end(x)));
				return *this;
			}
		}

		// 今の要素を破棄
		this->clear();

		// アロケータを伝播
		hamon::detail::propagate_allocator_on_move(m_allocator, x.m_allocator);

		// 要素をsteal
		m_head = hamon::move(x.m_head);

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
		Algo::assign_range_after(m_allocator, this->before_head(), first, last);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR
	void assign_range(R&& rg)
	{
		// [sequence.reqmts]/62
		Algo::assign_range_after(m_allocator, this->before_head(), hamon::forward<R>(rg));
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

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	allocator_type get_allocator() const HAMON_NOEXCEPT
	{
		return static_cast<allocator_type>(m_allocator);
	}

	// [forward.list.iter], iterators
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator before_begin() HAMON_NOEXCEPT
	{
		// [forward.list.iter]/2
		return iterator(this->before_head());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator before_begin() const HAMON_NOEXCEPT
	{
		// [forward.list.iter]/2
		return const_iterator(this->before_head());
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator begin() HAMON_NOEXCEPT
	{
		return iterator(m_head.m_next);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator begin() const HAMON_NOEXCEPT
	{
		return const_iterator(m_head.m_next);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator end() HAMON_NOEXCEPT
	{
		return iterator(nullptr);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator end() const HAMON_NOEXCEPT
	{
		return const_iterator(nullptr);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator cbegin() const HAMON_NOEXCEPT
	{
		return this->begin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator cbefore_begin() const HAMON_NOEXCEPT
	{
		// [forward.list.iter]/1
		return this->before_begin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator cend() const HAMON_NOEXCEPT
	{
		return this->end();
	}

	// capacity
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	bool empty() const HAMON_NOEXCEPT
	{
		return this->begin() == this->end();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	size_type max_size() const HAMON_NOEXCEPT
	{
		return hamon::min(
			static_cast<size_type>(hamon::numeric_limits<difference_type>::max()),
			static_cast<size_type>(NodeAllocTraits::max_size(m_allocator)));
	}

	// [forward.list.access], element access
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	reference front() HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [forward.list.access]/1
		return *this->begin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reference front() const HAMON_NOEXCEPT	// noexcept as an extension
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
		Algo::insert_after(m_allocator, this->before_head(), hamon::forward<Args>(args)...);
		return front();
	}

	HAMON_CXX14_CONSTEXPR
	void push_front(T const& x)
	{
		// [forward.list.modifiers]/3
		Algo::insert_after(m_allocator, this->before_head(), x);
	}

	HAMON_CXX14_CONSTEXPR
	void push_front(T&& x)
	{
		// [forward.list.modifiers]/3
		Algo::insert_after(m_allocator, this->before_head(), hamon::move(x));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR
	void prepend_range(R&& rg)
	{
		// [forward.list.modifiers]/4
		Algo::insert_range_after(m_allocator, this->before_head(), hamon::forward<R>(rg));
	}

	HAMON_CXX14_CONSTEXPR
	void pop_front() HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [forward.list.modifiers]/5
		this->erase_after(this->before_begin());
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR
	iterator emplace_after(const_iterator position, Args&&... args)
	{
		// [forward.list.modifiers]/23
		return iterator{Algo::insert_after(m_allocator, position.ptr(), hamon::forward<Args>(args)...)};
	}

	HAMON_CXX14_CONSTEXPR
	iterator insert_after(const_iterator position, T const& x)
	{
		// [forward.list.modifiers]/7
		return iterator{Algo::insert_after(m_allocator, position.ptr(), x)};
	}

	HAMON_CXX14_CONSTEXPR
	iterator insert_after(const_iterator position, T&& x)
	{
		// [forward.list.modifiers]/10
		return iterator{Algo::insert_after(m_allocator, position.ptr(), hamon::move(x))};
	}

	HAMON_CXX14_CONSTEXPR
	iterator insert_after(const_iterator position, size_type n, T const& x)
	{
		// [forward.list.modifiers]/13
		return iterator{Algo::insert_n_after(m_allocator, position.ptr(), n, x)};
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	iterator insert_after(const_iterator position, InputIterator first, InputIterator last)
	{
		// [forward.list.modifiers]/16
		return iterator{Algo::insert_range_after(m_allocator, position.ptr(), first, last)};
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
		return iterator{Algo::insert_range_after(m_allocator, position.ptr(), hamon::forward<R>(rg))};
	}

	HAMON_CXX14_CONSTEXPR
	iterator erase_after(const_iterator position)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [forward.list.modifiers]/26
		// [forward.list.modifiers]/27
		return iterator{Algo::erase_after(m_allocator, position.ptr())};
	}

	HAMON_CXX14_CONSTEXPR
	iterator erase_after(const_iterator position, const_iterator last)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [forward.list.modifiers]/30
		// [forward.list.modifiers]/31
		return iterator{Algo::erase_range_after(m_allocator, position.ptr(), last.ptr())};
	}

	HAMON_CXX14_CONSTEXPR
	void swap(forward_list& x)
		HAMON_NOEXCEPT_IF(hamon::allocator_traits<Allocator>::is_always_equal::value)
	{
		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			hamon::detail::propagate_allocator_on_swap(m_allocator, x.m_allocator);
		}
		hamon::swap(m_head, x.m_head);
	}

	HAMON_CXX14_CONSTEXPR
	void resize(size_type sz)
	{
		// [forward.list.modifiers]/34
		Algo::resize_after(m_allocator, this->before_head(), sz);
	}

	HAMON_CXX14_CONSTEXPR
	void resize(size_type sz, value_type const& c)
	{
		// [forward.list.modifiers]/36
		Algo::resize_after(m_allocator, this->before_head(), sz, c);
	}

	HAMON_CXX14_CONSTEXPR
	void clear() HAMON_NOEXCEPT
	{
		// [forward.list.modifiers]/37
		Algo::clear_after(m_allocator, this->before_head());
	}

	// [forward.list.ops], forward_list operations
	HAMON_CXX14_CONSTEXPR
	void splice_after(const_iterator position, forward_list& x)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [forward.list.ops]/3
		this->splice_after(position, x, x.before_begin(), x.end());
	}

	HAMON_CXX14_CONSTEXPR
	void splice_after(const_iterator position, forward_list&& x)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [forward.list.ops]/3
		this->splice_after(position, x, x.before_begin(), x.end());
	}

	HAMON_CXX14_CONSTEXPR
	void splice_after(const_iterator position, forward_list& x, const_iterator i)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [forward.list.ops]/6
		HAMON_ASSERT(hamon::detail::equals_allocator(m_allocator, x.m_allocator));
		// TODO
		// * position が before_begin() または [begin(), end()) の間接参照可能なイテレータであること
		// * i に続くイテレータが x 内の間接参照可能なイテレータであること

		// [forward.list.ops]/7
		Algo::splice_after(position.ptr(), i.ptr());
	}

	HAMON_CXX14_CONSTEXPR
	void splice_after(const_iterator position, forward_list&& x, const_iterator i)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [forward.list.ops]/7
		this->splice_after(position, x, i);
	}

	HAMON_CXX14_CONSTEXPR
	void splice_after(const_iterator position, forward_list& x, const_iterator first, const_iterator last)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [forward.list.ops]/10
		HAMON_ASSERT(hamon::detail::equals_allocator(m_allocator, x.m_allocator));
		// TODO
		// * position が before_begin() または [begin(), end()) の間接参照可能なイテレータであること
		// * (first, last) が x の有効な範囲で、全てのイテレータが間接参照可能であること
		// * position が (first, last) の範囲内のイテレータでないこと

		// [forward.list.ops]/11
		Algo::splice_range_after(position.ptr(), first.ptr(), last.ptr());
	}

	HAMON_CXX14_CONSTEXPR
	void splice_after(const_iterator position, forward_list&& x, const_iterator first, const_iterator last)
		HAMON_NOEXCEPT	// noexcept as an extension
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
		return Algo::remove_if_after(m_allocator, this->before_head(), pred);
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
		return Algo::unique_after(m_allocator, this->before_head(), binary_pred);
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

		Algo::merge_after(this->before_head(), x.before_head(), comp);
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
		Algo::sort_after(this->before_head(), comp);
	}

	HAMON_CXX14_CONSTEXPR
	void reverse() HAMON_NOEXCEPT
	{
		// [forward.list.ops]/32
		Algo::reverse_after(this->before_head());
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
HAMON_CXX14_CONSTEXPR void
swap(forward_list<T, Allocator>& x, forward_list<T, Allocator>& y)
	HAMON_NOEXCEPT_IF_EXPR(x.swap(y))
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

#endif

#endif // HAMON_FORWARD_LIST_FORWARD_LIST_HPP
