/**
 *	@file	list.hpp
 *
 *	@brief	list の定義
 */

#ifndef HAMON_LIST_LIST_HPP
#define HAMON_LIST_LIST_HPP

#include <hamon/list/list_fwd.hpp>
#include <hamon/list/config.hpp>

#if !defined(HAMON_USE_STD_LIST)

#include <hamon/list/detail/list_iterator.hpp>
#include <hamon/list/detail/list_node.hpp>
#include <hamon/list/detail/list_algo.hpp>
#include <hamon/list/detail/list_impl.hpp>
#include <hamon/algorithm/equal.hpp>
#include <hamon/algorithm/lexicographical_compare.hpp>
#include <hamon/algorithm/lexicographical_compare_three_way.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/compare/detail/synth_three_way.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/detail/iter_value_type.hpp>
#include <hamon/iterator/make_move_iterator.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/limits/numeric_limits.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/detail/equals_allocator.hpp>
#include <hamon/memory/detail/propagate_allocator_on_copy.hpp>
#include <hamon/memory/detail/propagate_allocator_on_move.hpp>
#include <hamon/memory/detail/propagate_allocator_on_swap.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/detail/container_compatible_range.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

namespace hamon
{

// 23.3.9 Class template list[list]

template <typename T, typename Allocator>
class list
{
private:
	using NodeBase = hamon::detail::list_node_base;
	using Node     = hamon::detail::list_node<T>;
	using NodeAllocator   = typename hamon::allocator_traits<Allocator>::template rebind_alloc<Node>;
	using NodeAllocTraits = typename hamon::allocator_traits<Allocator>::template rebind_traits<Node>;
	using Algo = hamon::detail::list_algo<T, NodeAllocator>;

public:
	// types
	using value_type             = T;
	using allocator_type         = Allocator;
	using pointer                = typename hamon::allocator_traits<Allocator>::pointer;
	using const_pointer          = typename hamon::allocator_traits<Allocator>::const_pointer;
	using reference              = value_type&;
	using const_reference        = value_type const&;
	using size_type              = typename hamon::allocator_traits<Allocator>::size_type;
	using difference_type        = typename hamon::allocator_traits<Allocator>::difference_type;
	using iterator               = hamon::detail::list_iterator<T, Allocator, false>;
	using const_iterator         = hamon::detail::list_iterator<T, Allocator, true>;
	using reverse_iterator       = hamon::reverse_iterator<iterator>;
	using const_reverse_iterator = hamon::reverse_iterator<const_iterator>;

private:
	HAMON_NO_UNIQUE_ADDRESS	NodeAllocator	m_allocator;
	hamon::detail::list_impl<Algo>			m_impl{};

public:
	// [list.cons], construct/copy/destroy
	HAMON_CXX11_CONSTEXPR
	list() : list(Allocator())
	{}

	explicit HAMON_CXX11_CONSTEXPR
	list(Allocator const& a)
		: m_allocator(a)
	{
		// [list.cons]/1
	}

	explicit HAMON_CXX14_CONSTEXPR
	list(size_type n, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [list.cons]/4
		m_impl.insert_n(m_allocator, m_impl.tail(), n);	// may throw
	}

	HAMON_CXX14_CONSTEXPR
	list(size_type n, T const& value, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [list.cons]/7
		m_impl.insert_n(m_allocator, m_impl.tail(), n, value);	// may throw
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	list(InputIterator first, InputIterator last, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [list.cons]/9
		m_impl.insert_range(m_allocator, m_impl.tail(), first, last);	// may throw
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR
	list(hamon::from_range_t, R&& rg, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [list.cons]/11
		m_impl.insert_range(m_allocator, m_impl.tail(), hamon::ranges::begin(rg), hamon::ranges::end(rg));	// may throw
	}

	HAMON_CXX14_CONSTEXPR
	list(list const& x)
		: m_allocator(NodeAllocTraits::select_on_container_copy_construction(x.m_allocator))
	{
		m_impl.insert_range(m_allocator, m_impl.tail(), hamon::ranges::begin(x), hamon::ranges::end(x));	// may throw
	}

	HAMON_CXX14_CONSTEXPR
	list(list&& x) HAMON_NOEXCEPT	// noexcept as an extension
		: m_allocator(hamon::move(x.m_allocator))
		, m_impl(hamon::move(x.m_impl))
	{}

	HAMON_CXX14_CONSTEXPR
	list(list const& x, hamon::type_identity_t<Allocator> const& a)
		: m_allocator(a)
	{
		m_impl.insert_range(m_allocator, m_impl.tail(), hamon::ranges::begin(x), hamon::ranges::end(x));	// may throw
	}

	HAMON_CXX14_CONSTEXPR
	list(list&& x, hamon::type_identity_t<Allocator> const& a)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::allocator_traits<Allocator>::is_always_equal::value)
		: m_allocator(a)
	{
		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			// アロケータが異なる場合は、
			// 要素をムーブ代入しなければいけない = 要素をstealすることはできない。
			m_impl.insert_range(m_allocator, m_impl.tail(),
				hamon::make_move_iterator(hamon::ranges::begin(x)),
				hamon::make_move_iterator(hamon::ranges::end(x)));	// may throw
			return;
		}

		// 要素をsteal
		m_impl = hamon::move(x.m_impl);
	}

	HAMON_CXX11_CONSTEXPR
	list(std::initializer_list<T> il, Allocator const& a = Allocator())
		: list(il.begin(), il.end(), a)
	{}

	HAMON_CXX20_CONSTEXPR
	~list() HAMON_NOEXCEPT
	{
		this->clear();
	}

	HAMON_CXX14_CONSTEXPR list&
	operator=(list const& x)
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
		m_impl.assign_range(m_allocator, hamon::ranges::begin(x), hamon::ranges::end(x));	// may throw

		return *this;
	}

	HAMON_CXX14_CONSTEXPR list&
	operator=(list&& x)
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
				m_impl.assign_range(m_allocator,
					hamon::make_move_iterator(hamon::ranges::begin(x)),
					hamon::make_move_iterator(hamon::ranges::end(x)));	// may throw
				return *this;
			}
		}

		// 今の要素を破棄
		this->clear();

		// アロケータを伝播
		hamon::detail::propagate_allocator_on_move(m_allocator, x.m_allocator);

		// 要素をsteal
		m_impl = hamon::move(x.m_impl);

		return *this;
	}

	HAMON_CXX14_CONSTEXPR list&
	operator=(std::initializer_list<T> il)
	{
		this->assign(il.begin(), il.end());	// may throw

		return *this;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void
	assign(InputIterator first, InputIterator last)
	{
		m_impl.assign_range(m_allocator, first, last);	// may throw
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR void
	assign_range(R&& rg)
	{
		m_impl.assign_range(m_allocator, hamon::ranges::begin(rg), hamon::ranges::end(rg));	// may throw
	}

	HAMON_CXX14_CONSTEXPR void
	assign(size_type n, T const& t)
	{
		m_impl.assign_n(m_allocator, n, t);	// may throw
	}

	HAMON_CXX14_CONSTEXPR void
	assign(std::initializer_list<T> il)
	{
		this->assign(il.begin(), il.end());	// may throw
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	allocator_type get_allocator() const HAMON_NOEXCEPT
	{
		return static_cast<allocator_type>(m_allocator);
	}

	// iterators
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator begin() HAMON_NOEXCEPT
	{
		return iterator(m_impl.head());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator begin() const HAMON_NOEXCEPT
	{
		return const_iterator(m_impl.head());
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator end() HAMON_NOEXCEPT
	{
		return iterator(m_impl.tail());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator end() const HAMON_NOEXCEPT
	{
		return const_iterator(m_impl.tail());
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	reverse_iterator rbegin() HAMON_NOEXCEPT
	{
		return reverse_iterator(this->end());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reverse_iterator rbegin() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(this->end());
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	reverse_iterator rend() HAMON_NOEXCEPT
	{
		return reverse_iterator(this->begin());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reverse_iterator rend() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(this->begin());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator cbegin() const HAMON_NOEXCEPT
	{
		return this->begin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator cend() const HAMON_NOEXCEPT
	{
		return this->end();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reverse_iterator crbegin() const HAMON_NOEXCEPT
	{
		return this->rbegin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reverse_iterator crend() const HAMON_NOEXCEPT
	{
		return this->rend();
	}

	// [list.capacity], capacity
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	bool empty() const HAMON_NOEXCEPT
	{
		return this->size() == 0;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	size_type size() const HAMON_NOEXCEPT
	{
		return m_impl.size();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	size_type max_size() const HAMON_NOEXCEPT
	{
		return hamon::min(
			static_cast<size_type>(hamon::numeric_limits<difference_type>::max()),
			static_cast<size_type>(NodeAllocTraits::max_size(m_allocator)));
	}

	HAMON_CXX14_CONSTEXPR void
	resize(size_type sz)
	{
		// [list.capacity]/2
		m_impl.resize(m_allocator, sz);	// may throw
	}

	HAMON_CXX14_CONSTEXPR void
	resize(size_type sz, T const& c)
	{
		// [list.capacity]/4
		m_impl.resize(m_allocator, sz, c);	// may throw
	}

	// element access
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	reference front() HAMON_NOEXCEPT	// noexcept as an extension
	{
		return *this->begin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reference front() const HAMON_NOEXCEPT	// noexcept as an extension
	{
		return *this->begin();
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	reference back() HAMON_NOEXCEPT	// noexcept as an extension
	{
		return *this->rbegin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reference back() const HAMON_NOEXCEPT	// noexcept as an extension
	{
		return *this->rbegin();
	}

	// [list.modifiers], modifiers
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR reference
	emplace_front(Args&&... args)
	{
		m_impl.insert(m_allocator, m_impl.head(), hamon::forward<Args>(args)...);	// may throw
		return front();
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR reference
	emplace_back(Args&&... args)
	{
		m_impl.insert(m_allocator, m_impl.tail(), hamon::forward<Args>(args)...);	// may throw
		return back();
	}

	HAMON_CXX14_CONSTEXPR void
	push_front(T const& x)
	{
		m_impl.insert(m_allocator, m_impl.head(), x);	// may throw
	}

	HAMON_CXX14_CONSTEXPR void
	push_front(T&& x)
	{
		m_impl.insert(m_allocator, m_impl.head(), hamon::move(x));	// may throw
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR void
	prepend_range(R&& rg)
	{
		m_impl.insert_range(m_allocator, m_impl.head(), hamon::ranges::begin(rg), hamon::ranges::end(rg));	// may throw
	}

	HAMON_CXX14_CONSTEXPR void
	pop_front() HAMON_NOEXCEPT	// noexcept as an extension
	{
		m_impl.erase(m_allocator, m_impl.head());
	}

	HAMON_CXX14_CONSTEXPR void
	push_back(T const& x)
	{
		m_impl.insert(m_allocator, m_impl.tail(), x);	// may throw
	}

	HAMON_CXX14_CONSTEXPR void
	push_back(T&& x)
	{
		m_impl.insert(m_allocator, m_impl.tail(), hamon::move(x));	// may throw
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR void
	append_range(R&& rg)
	{
		m_impl.insert_range(m_allocator, m_impl.tail(), hamon::ranges::begin(rg), hamon::ranges::end(rg));	// may throw
	}

	HAMON_CXX14_CONSTEXPR void
	pop_back() HAMON_NOEXCEPT	// noexcept as an extension
	{
		m_impl.erase(m_allocator, m_impl.tail()->m_prev);
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace(const_iterator position, Args&&... args)
	{
		return iterator{ m_impl.insert(m_allocator, position.ptr(), hamon::forward<Args>(args)...) };	// may throw
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, T const& x)
	{
		return iterator{ m_impl.insert(m_allocator, position.ptr(), x) };	// may throw
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, T&& x)
	{
		return iterator{ m_impl.insert(m_allocator, position.ptr(), hamon::move(x)) };	// may throw
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, size_type n, T const& x)
	{
		return iterator{ m_impl.insert_n(m_allocator, position.ptr(), n, x) };	// may throw
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, InputIterator first, InputIterator last)
	{
		return iterator{ m_impl.insert_range(m_allocator, position.ptr(), first, last) };	// may throw
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR iterator
	insert_range(const_iterator position, R&& rg)
	{
		return iterator{ m_impl.insert_range(m_allocator, position.ptr(), hamon::ranges::begin(rg), hamon::ranges::end(rg)) };	// may throw
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, std::initializer_list<T> il)
	{
		return this->insert(position, il.begin(), il.end());	// may throw
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator position)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		return iterator{ m_impl.erase(m_allocator, position.ptr()) };
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator position, const_iterator last)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		return iterator{ m_impl.erase_range(m_allocator, position.ptr(), last.ptr()) };
	}

	HAMON_CXX14_CONSTEXPR
	void swap(list& x)
		HAMON_NOEXCEPT_IF(hamon::allocator_traits<Allocator>::is_always_equal::value)
	{
		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			hamon::detail::propagate_allocator_on_swap(m_allocator, x.m_allocator);
		}
		hamon::swap(m_impl, x.m_impl);
	}

	HAMON_CXX14_CONSTEXPR
	void clear() HAMON_NOEXCEPT
	{
		m_impl.erase_range(m_allocator, m_impl.head(), m_impl.tail());
	}

	// [list.ops], list operations
	HAMON_CXX14_CONSTEXPR void
	splice(const_iterator position, list& x)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [list.ops]/4
		this->splice(position, x, x.begin(), x.end());
	}

	HAMON_CXX14_CONSTEXPR void
	splice(const_iterator position, list&& x)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [list.ops]/4
		this->splice(position, x);
	}

	HAMON_CXX14_CONSTEXPR void
	splice(const_iterator position, list& x, const_iterator i)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [list.ops]/8
		this->splice(position, x, i, hamon::next(i));
	}

	HAMON_CXX14_CONSTEXPR void
	splice(const_iterator position, list&& x, const_iterator i)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [list.ops]/8
		this->splice(position, x, i);
	}

	HAMON_CXX14_CONSTEXPR void
	splice(const_iterator position, list& x, const_iterator first, const_iterator last)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [list.ops]/12
		m_impl.splice_range(position.ptr(), x.m_impl, first.ptr(), last.ptr());
	}

	HAMON_CXX14_CONSTEXPR void
	splice(const_iterator position, list&& x, const_iterator first, const_iterator last)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [list.ops]/12
		this->splice(position, x, first, last);
	}

	HAMON_CXX14_CONSTEXPR size_type
	remove(T const& value)
	{
		// [list.ops]/15
		// [list.ops]/16
		return this->remove_if([&](T const& x) { return x == value; });	// may throw
	}

	template <typename Predicate>
	HAMON_CXX14_CONSTEXPR size_type
	remove_if(Predicate pred)
	{
		// [list.ops]/15
		// [list.ops]/16
		return m_impl.remove_if(m_allocator, pred);	// may throw
	}

	HAMON_CXX14_CONSTEXPR size_type
	unique()
	{
		// [list.ops]/20
		return this->unique(hamon::equal_to<>{});	// may throw
	}

	template <typename BinaryPredicate>
	HAMON_CXX14_CONSTEXPR size_type
	unique(BinaryPredicate binary_pred)
	{
		// [list.ops]/22
		// [list.ops]/23
		return m_impl.unique(m_allocator, binary_pred);	// may throw
	}

	HAMON_CXX14_CONSTEXPR void
	merge(list& x)
	{
		// [list.ops]/26
		this->merge(x, hamon::less<>{});	// may throw
	}

	HAMON_CXX14_CONSTEXPR void
	merge(list&& x)
	{
		// [list.ops]/26
		this->merge(x, hamon::less<>{});	// may throw
	}

	template <typename Compare>
	HAMON_CXX14_CONSTEXPR void
	merge(list& x, Compare comp)
	{
		// [list.ops]/28
		if (hamon::addressof(x) == this)
		{
			return;
		}

		m_impl.merge(x.m_impl, comp);	// may throw
	}

	template <typename Compare>
	HAMON_CXX14_CONSTEXPR void
	merge(list&& x, Compare comp)
	{
		// [list.ops]/28
		this->merge(x, comp);	// may throw
	}

	HAMON_CXX14_CONSTEXPR void
	sort()
	{
		// [list.ops]/33
		this->sort(hamon::less<>{});	// may throw
	}

	template <typename Compare>
	HAMON_CXX14_CONSTEXPR void
	sort(Compare comp)
	{
		// [list.ops]/33
		m_impl.sort(comp);	// may throw
	}

	HAMON_CXX14_CONSTEXPR void
	reverse() HAMON_NOEXCEPT
	{
		// [list.ops]/31
		m_impl.reverse();
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	typename Allocator = hamon::allocator<hamon::detail::iter_value_type<InputIterator>>>
list(InputIterator, InputIterator, Allocator = Allocator())
	->list<hamon::detail::iter_value_type<InputIterator>, Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Allocator = hamon::allocator<ranges::range_value_t<R>>>
list(hamon::from_range_t, R&&, Allocator = Allocator())
	->list<ranges::range_value_t<R>, Allocator>;

#endif

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator==(list<T, Allocator> const& x, list<T, Allocator> const& y)
{
	return hamon::equal(x.begin(), x.end(), y.begin(), y.end());
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
hamon::detail::synth_three_way_result<T>
operator<=>(list<T, Allocator> const&x, list<T, Allocator> const&y)
{
	return hamon::lexicographical_compare_three_way(
		x.begin(), x.end(),
		y.begin(), y.end(),
		hamon::detail::synth_three_way);
}

#else

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator!=(list<T, Allocator> const& x, list<T, Allocator> const& y)
{
	return !(x == y);
}

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator<(list<T, Allocator> const& x, list<T, Allocator> const& y)
{
	return hamon::lexicographical_compare(
		x.begin(), x.end(),
		y.begin(), y.end());
}

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator>(list<T, Allocator> const& x, list<T, Allocator> const& y)
{
	return y < x;
}

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator<=(list<T, Allocator> const& x, list<T, Allocator> const& y)
{
	return !(x > y);
}

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator>=(list<T, Allocator> const& x, list<T, Allocator> const& y)
{
	return !(x < y);
}

#endif

template <typename T, typename Allocator>
HAMON_CXX14_CONSTEXPR void
swap(list<T, Allocator>& x, list<T, Allocator>& y)
	HAMON_NOEXCEPT_IF_EXPR(x.swap(y))
{
	x.swap(y);
}

#if 0	// TODO
namespace pmr
{

template <typename T>
using list = hamon::list<T, polymorphic_allocator<T>>;

}	// namespace pmr
#endif

}	// namespace hamon

// シリアライズ対応

#include <hamon/serialization/detail/save_vector.hpp>
#include <hamon/serialization/detail/load_vector.hpp>

namespace hamon
{

template <typename Archive, typename T, typename Allocator>
void save_value(Archive& oa, hamon::list<T, Allocator> const& t)
{
	hamon::serialization::detail::save_vector(oa, t);
}

template <typename Archive, typename T, typename Allocator>
void load_value(Archive& ia, hamon::list<T, Allocator>& t)
{
	t.clear();
	hamon::serialization::detail::load_vector(ia, t);
}

}	// namespace hamon

#endif

#endif // HAMON_LIST_LIST_HPP
