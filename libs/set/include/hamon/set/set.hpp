/**
 *	@file	set.hpp
 *
 *	@brief	set の定義
 */

#ifndef HAMON_SET_SET_HPP
#define HAMON_SET_SET_HPP

#include <hamon/set/set_fwd.hpp>
#include <hamon/set/config.hpp>

#if !defined(HAMON_USE_STD_SET)

#include <hamon/set/multiset_fwd.hpp>
#include <hamon/container/detail/red_black_tree.hpp>
#include <hamon/container/detail/iter_value_type.hpp>
#include <hamon/container/detail/node_handle.hpp>
#include <hamon/container/detail/insert_return_type.hpp>

#include <hamon/compare/detail/synth_three_way.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/memory/detail/equals_allocator.hpp>
#include <hamon/memory/detail/propagate_allocator_on_copy.hpp>
#include <hamon/memory/detail/propagate_allocator_on_move.hpp>
#include <hamon/memory/detail/propagate_allocator_on_swap.hpp>
#include <hamon/ranges/detail/container_compatible_range.hpp>

#include <hamon/algorithm.hpp>
#include <hamon/concepts.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/memory.hpp>
#include <hamon/ranges.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

namespace hamon
{

template <typename Key, typename Compare, typename Allocator>
class set
{
public:
	// types
	using key_type               = Key;
	using key_compare            = Compare;
	using value_type             = Key;
	using value_compare          = Compare;
	using allocator_type         = Allocator;
	using pointer                = typename hamon::allocator_traits<Allocator>::pointer;
	using const_pointer          = typename hamon::allocator_traits<Allocator>::const_pointer;
	using reference              = value_type&;
	using const_reference        = value_type const&;
	using size_type              = typename hamon::allocator_traits<Allocator>::size_type;
	using difference_type        = typename hamon::allocator_traits<Allocator>::difference_type;

private:
	using Tree = hamon::detail::red_black_tree<false, value_type, size_type, difference_type>;
	using TreeNode = typename Tree::node_type;
	using NodeAllocator = typename hamon::allocator_traits<Allocator>::template rebind_alloc<TreeNode>;
	using NodeAllocTraits = typename hamon::allocator_traits<Allocator>::template rebind_traits<TreeNode>;

private:
	HAMON_NO_UNIQUE_ADDRESS	NodeAllocator m_allocator;
	HAMON_NO_UNIQUE_ADDRESS Compare       m_comp;
	Tree                                  m_impl;

public:
	using iterator               = typename Tree::const_iterator;
	using const_iterator         = typename Tree::const_iterator;
	using reverse_iterator       = hamon::reverse_iterator<iterator>;
	using const_reverse_iterator = hamon::reverse_iterator<const_iterator>;
	using node_type              = hamon::detail::node_handle<value_type>;
	using insert_return_type     = hamon::detail::insert_return_type<iterator, node_type>;

	// [set.cons], construct/copy/destroy
	HAMON_CXX11_CONSTEXPR
	set() : set(Compare())
	{}

	explicit HAMON_CXX11_CONSTEXPR
	set(Compare const& comp, Allocator const& a = Allocator())
		: m_allocator(a)
		, m_comp(comp)
		, m_impl()
	{}

	explicit HAMON_CXX11_CONSTEXPR
	set(Allocator const& a)
		: set(Compare(), a)
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	set(InputIterator first, InputIterator last, Compare const& comp = Compare(), Allocator const& a = Allocator())
		: set(comp, a)
	{
		this->insert(first, last);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	set(InputIterator first, InputIterator last, Allocator const& a)
		: set(first, last, Compare(), a)
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	HAMON_CXX14_CONSTEXPR
	set(hamon::from_range_t, R&& rg, Compare const& comp = Compare(), Allocator const& a = Allocator())
		: set(comp, a)
	{
		this->insert_range(hamon::forward<R>(rg));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	HAMON_CXX14_CONSTEXPR
	set(hamon::from_range_t, R&& rg, Allocator const& a)
		: set(hamon::from_range, hamon::forward<R>(rg), Compare(), a)
	{}

	HAMON_CXX14_CONSTEXPR
	set(std::initializer_list<value_type> il, Compare const& comp = Compare(), Allocator const& a = Allocator())
		: set(comp, a)
	{
		this->insert(il);
	}

	HAMON_CXX14_CONSTEXPR
	set(std::initializer_list<value_type> il, Allocator const& a)
		: set(il, Compare(), a)
	{}

	HAMON_CXX14_CONSTEXPR
	set(set const& x)
		: m_allocator(NodeAllocTraits::select_on_container_copy_construction(x.m_allocator))
		, m_comp(x.m_comp)
	{
		this->insert_range(x);
	}

	HAMON_CXX11_CONSTEXPR
	set(set&& x) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<Compare>::value)
		: m_allocator(hamon::move(x.m_allocator))
		, m_comp(hamon::move(x.m_comp))
		, m_impl(hamon::move(x.m_impl))
	{}

	HAMON_CXX14_CONSTEXPR
	set(set const& x, hamon::type_identity_t<Allocator> const& a)
		: m_allocator(a)
		, m_comp(x.m_comp)
	{
		this->insert_range(x);
	}

	HAMON_CXX14_CONSTEXPR
	set(set&& x, hamon::type_identity_t<Allocator> const& a)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::allocator_traits<Allocator>::is_always_equal::value &&
			hamon::is_nothrow_move_constructible<Compare>::value)
		: m_allocator(a)
		, m_comp(hamon::move(x.m_comp))
	{
		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			// アロケータが異なる場合は、
			// 要素をムーブ代入しなければいけない = 要素をstealすることはできない。
			m_impl.insert_range(m_comp, m_allocator,
				hamon::make_move_iterator(hamon::ranges::begin(x)),
				hamon::make_move_iterator(hamon::ranges::end(x)));	// may throw
		}
		else
		{
			// 要素をsteal
			m_impl = hamon::move(x.m_impl);
		}
	}

	HAMON_CXX20_CONSTEXPR
	~set()
	{
		this->clear();
	}

	HAMON_CXX14_CONSTEXPR
	set& operator=(set const& x);

	HAMON_CXX14_CONSTEXPR
	set& operator=(set&& x) noexcept(
		hamon::allocator_traits<Allocator>::is_always_equal::value &&
		hamon::is_nothrow_move_assignable<Compare>::value);

	HAMON_CXX14_CONSTEXPR
	set& operator=(std::initializer_list<value_type> il)
	{
		this->clear();
		this->insert(il);
		return *this;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	allocator_type get_allocator() const noexcept
	{
		return static_cast<allocator_type>(m_allocator);
	}

	// iterators
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator begin() noexcept
	{
		return m_impl.begin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator begin() const noexcept
	{
		return m_impl.begin();
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator end() noexcept
	{
		return m_impl.end();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator end() const noexcept
	{
		return m_impl.end();
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	reverse_iterator rbegin() noexcept
	{
		return reverse_iterator(this->end());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reverse_iterator rbegin() const noexcept
	{
		return const_reverse_iterator(this->end());
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	reverse_iterator rend() noexcept
	{
		return reverse_iterator(this->begin());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reverse_iterator rend() const noexcept
	{
		return const_reverse_iterator(this->begin());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator cbegin() const noexcept
	{
		return this->begin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator cend() const noexcept
	{
		return this->end();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reverse_iterator crbegin() const noexcept
	{
		return this->rbegin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reverse_iterator crend() const noexcept
	{
		return this->rend();
	}

	// capacity
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	bool empty() const noexcept
	{
		return this->size() == 0;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	size_type size() const noexcept
	{
		return m_impl.size();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	size_type max_size() const noexcept
	{
		return hamon::min(
			static_cast<size_type>(hamon::numeric_limits<difference_type>::max()),
			static_cast<size_type>(NodeAllocTraits::max_size(m_allocator)));
	}

	// [set.modifiers], modifiers
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR pair<iterator, bool>
	emplace(Args&&... args)
	{
		return m_impl.emplace(m_comp, m_allocator, hamon::forward<Args>(args)...);
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_hint(const_iterator position, Args&&... args);

	HAMON_CXX14_CONSTEXPR pair<iterator, bool>
	insert(value_type const& x)
	{
		return m_impl.insert(m_comp, m_allocator, x);
	}

	HAMON_CXX14_CONSTEXPR pair<iterator, bool>
	insert(value_type&& x)
	{
		return m_impl.insert(m_comp, m_allocator, hamon::move(x));
	}

	template <typename K>
	HAMON_CXX14_CONSTEXPR pair<iterator, bool>
	insert(K&& x);

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, value_type const& x);

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, value_type&& x);

	template <typename K>
	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, K&& x);

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	void insert(InputIterator first, InputIterator last)
	{
		m_impl.insert_range(m_comp, m_allocator, first, last);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	HAMON_CXX14_CONSTEXPR
	void insert_range(R&& rg)
	{
		m_impl.insert_range(m_comp, m_allocator,
			hamon::ranges::begin(rg), hamon::ranges::end(rg));
	}

	HAMON_CXX14_CONSTEXPR
	void insert(std::initializer_list<value_type> il)
	{
		this->insert(il.begin(), il.end());
	}

	HAMON_CXX14_CONSTEXPR
	node_type extract(const_iterator position);

	HAMON_CXX14_CONSTEXPR
	node_type extract(key_type const& x);

	template <typename K>
	HAMON_CXX14_CONSTEXPR
	node_type extract(K&& x);

	HAMON_CXX14_CONSTEXPR
	insert_return_type insert(node_type&& nh);

	HAMON_CXX14_CONSTEXPR
	iterator insert(const_iterator hint, node_type&& nh);

	//HAMON_CXX14_CONSTEXPR
	//iterator erase(iterator position)
	//	requires (!hamon::same_as<iterator, const_iterator>);

	HAMON_CXX14_CONSTEXPR
	iterator erase(const_iterator position);

	HAMON_CXX14_CONSTEXPR
	size_type erase(key_type const& x);

	template <typename K>
	HAMON_CXX14_CONSTEXPR
	size_type erase(K&& x);

	HAMON_CXX14_CONSTEXPR
	iterator erase(const_iterator first, const_iterator last);

	HAMON_CXX14_CONSTEXPR
	void swap(set& x) noexcept(
		hamon::allocator_traits<Allocator>::is_always_equal::value &&
		hamon::is_nothrow_swappable<Compare>::value)
	{
		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			hamon::detail::propagate_allocator_on_swap(m_allocator, x.m_allocator);
		}
		hamon::swap(m_comp, x.m_comp);
		hamon::swap(m_impl, x.m_impl);
	}

	HAMON_CXX14_CONSTEXPR
	void clear() noexcept
	{
		m_impl.clear(m_allocator);
	}

	template <typename C2>
	HAMON_CXX14_CONSTEXPR
	void merge(set<Key, C2, Allocator>& source);

	template <typename C2>
	HAMON_CXX14_CONSTEXPR
	void merge(set<Key, C2, Allocator>&& source);

	template <typename C2>
	HAMON_CXX14_CONSTEXPR
	void merge(multiset<Key, C2, Allocator>& source);

	template <typename C2>
	HAMON_CXX14_CONSTEXPR
	void merge(multiset<Key, C2, Allocator>&& source);

	// observers
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	key_compare key_comp() const
	{
		return m_comp;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	value_compare value_comp() const
	{
		return m_comp;
	}

	// set operations
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator find(key_type const& x);

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator find(key_type const& x) const;

	template <typename K>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator find(K const& x);

	template <typename K>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator find(K const& x) const;

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	size_type count(key_type const& x) const;

	template <typename K>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	size_type count(K const& x) const;

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	bool contains(key_type const& x) const;

	template <typename K>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	bool contains(K const& x) const;

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator lower_bound(key_type const& x);

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator lower_bound(key_type const& x) const;

	template <typename K>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator lower_bound(K const& x);

	template <typename K>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator lower_bound(K const& x) const;

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator upper_bound(key_type const& x);

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator upper_bound(key_type const& x) const;

	template <typename K>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator upper_bound(K const& x);

	template <typename K>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator upper_bound(K const& x) const;

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	pair<iterator, iterator>
	equal_range(key_type const& x);

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	pair<const_iterator, const_iterator>
	equal_range(key_type const& x) const;

	template <typename K>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	pair<iterator, iterator>
	equal_range(K const& x);

	template <typename K>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	pair<const_iterator, const_iterator>
	equal_range(K const& x) const;
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	typename Compare = hamon::less<hamon::detail::iter_value_type<InputIterator>>,
	typename Allocator = hamon::allocator<hamon::detail::iter_value_type<InputIterator>>>
set(InputIterator, InputIterator, Compare = Compare(), Allocator = Allocator())
->set<hamon::detail::iter_value_type<InputIterator>, Compare, Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Compare = hamon::less<ranges::range_value_t<R>>,
	typename Allocator = hamon::allocator<ranges::range_value_t<R>>>
set(hamon::from_range_t, R&&, Compare = Compare(), Allocator = Allocator())
->set<ranges::range_value_t<R>, Compare, Allocator>;

template <
	typename Key,
	typename Compare = hamon::less<Key>,
	typename Allocator = hamon::allocator<Key>>
set(std::initializer_list<Key>, Compare = Compare(), Allocator = Allocator())
->set<Key, Compare, Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	typename Allocator>
set(InputIterator, InputIterator, Allocator)
->set<
	hamon::detail::iter_value_type<InputIterator>,
	hamon::less<hamon::detail::iter_value_type<InputIterator>>,
	Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Allocator>
set(hamon::from_range_t, R&&, Allocator)
->set<
	ranges::range_value_t<R>,
	hamon::less<ranges::range_value_t<R>>,
	Allocator>;

template <typename Key, typename Allocator>
set(std::initializer_list<Key>, Allocator)
->set<Key, hamon::less<Key>, Allocator>;

#endif

template <typename Key, typename Compare, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator==(set<Key, Compare, Allocator> const& x, set<Key, Compare, Allocator> const& y)
{
	return hamon::equal(x.begin(), x.end(), y.begin(), y.end());
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename Key, typename Compare, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
hamon::detail::synth_three_way_result<Key>
operator<=>(set<Key, Compare, Allocator> const& x, set<Key, Compare, Allocator> const& y)
{
	return hamon::lexicographical_compare_three_way(
		x.begin(), x.end(),
		y.begin(), y.end(),
		hamon::detail::synth_three_way);
}

#else

template <typename Key, typename Compare, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator!=(set<Key, Compare, Allocator> const& x, set<Key, Compare, Allocator> const& y)
{
	return !(x == y);
}

template <typename Key, typename Compare, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<(set<Key, Compare, Allocator> const& x, set<Key, Compare, Allocator> const& y)
{
	return hamon::lexicographical_compare(
		x.begin(), x.end(),
		y.begin(), y.end());
}

template <typename Key, typename Compare, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>(set<Key, Compare, Allocator> const& x, set<Key, Compare, Allocator> const& y)
{
	return y < x;
}

template <typename Key, typename Compare, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<=(set<Key, Compare, Allocator> const& x, set<Key, Compare, Allocator> const& y)
{
	return !(x > y);
}

template <typename Key, typename Compare, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>=(set<Key, Compare, Allocator> const& x, set<Key, Compare, Allocator> const& y)
{
	return !(x < y);
}

#endif

template <typename Key, typename Compare, typename Allocator>
HAMON_CXX14_CONSTEXPR void
swap(set<Key, Compare, Allocator>& x, set<Key, Compare, Allocator>& y)
	noexcept(noexcept(x.swap(y)))
{
	x.swap(y);
}

namespace pmr
{
#if 0	// TODO
template <typename Key, typename Compare = hamon::less<Key>>
using set = hamon::set<Key, Compare, hamon::polymorphic_allocator<Key>>;
#endif
}	// namespace pmr

}	// namespace hamon

#endif

#endif // HAMON_SET_SET_HPP
