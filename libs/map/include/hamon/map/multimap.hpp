/**
 *	@file	multimap.hpp
 *
 *	@brief	multimap の定義
 */

#ifndef HAMON_MAP_MULTIMAP_HPP
#define HAMON_MAP_MULTIMAP_HPP

#include <hamon/map/multimap_fwd.hpp>
#include <hamon/map/config.hpp>

#if !defined(HAMON_USE_STD_MULTIMAP)

#include <hamon/map/map_fwd.hpp>
#include <hamon/map/detail/heterogeneous_compare.hpp>
#include <hamon/container/detail/container_compatible_range.hpp>
#include <hamon/container/detail/red_black_tree.hpp>
#include <hamon/container/detail/node_handle.hpp>
#include <hamon/container/detail/iter_key_type.hpp>
#include <hamon/container/detail/iter_to_alloc_type.hpp>
#include <hamon/container/detail/iter_mapped_type.hpp>
#include <hamon/container/detail/range_key_type.hpp>
#include <hamon/container/detail/range_to_alloc_type.hpp>
#include <hamon/container/detail/range_mapped_type.hpp>
#include <hamon/container/detail/has_is_transparent.hpp>
#include <hamon/container/detail/cpp17_copy_insertable.hpp>
#include <hamon/container/detail/cpp17_move_insertable.hpp>

#include <hamon/algorithm/equal.hpp>
#include <hamon/algorithm/lexicographical_compare.hpp>
#include <hamon/algorithm/lexicographical_compare_three_way.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/compare/detail/synth_three_way.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/detail/cpp17_copy_assignable.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/limits/numeric_limits.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/detail/equals_allocator.hpp>
#include <hamon/memory/detail/propagate_allocator_on_copy.hpp>
#include <hamon/memory/detail/propagate_allocator_on_move.hpp>
#include <hamon/memory/detail/propagate_allocator_on_swap.hpp>
#include <hamon/memory/detail/simple_allocator.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_swappable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

namespace hamon
{

// 23.4.4 Class template multimap[multimap]

template <typename Key, typename T, typename Compare, typename Allocator>
class multimap
{
public:
	// types
	using key_type               = Key;
	using mapped_type            = T;
	using value_type             = hamon::pair<Key const, T>;
	using key_compare            = Compare;
	using allocator_type         = Allocator;
	using pointer                = typename hamon::allocator_traits<Allocator>::pointer;
	using const_pointer          = typename hamon::allocator_traits<Allocator>::const_pointer;
	using reference              = value_type&;
	using const_reference        = value_type const&;
	using size_type              = typename hamon::allocator_traits<Allocator>::size_type;
	using difference_type        = typename hamon::allocator_traits<Allocator>::difference_type;

	static_assert(hamon::is_same<typename allocator_type::value_type, value_type>::value, "[container.alloc.reqmts]/5");

public:
	class value_compare
	{
		friend class multimap;

	protected:
		Compare comp;

		HAMON_CXX11_CONSTEXPR
		value_compare(Compare c) : comp(c) {}

	public:
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator()(value_type const& x, value_type const& y) const
		{
			return comp(x.first, y.first);
		}
	};

private:
	using HeterogeneousCompare = hamon::detail::heterogeneous_compare<Compare>;
	using Tree = hamon::detail::red_black_tree<true, key_type, value_type, HeterogeneousCompare, size_type, difference_type>;
	using TreeNode = typename Tree::node_type;
	using NodeAllocator = typename hamon::allocator_traits<Allocator>::template rebind_alloc<TreeNode>;
	using NodeAllocTraits = typename hamon::allocator_traits<Allocator>::template rebind_traits<TreeNode>;

public:
	using iterator               = typename Tree::iterator;
	using const_iterator         = typename Tree::const_iterator;
	using reverse_iterator       = hamon::reverse_iterator<iterator>;
	using const_reverse_iterator = hamon::reverse_iterator<const_iterator>;
	using node_type              = hamon::detail::map_node_handle<TreeNode, Allocator>;

private:
	HAMON_NO_UNIQUE_ADDRESS	NodeAllocator m_allocator;
	Tree                                  m_impl;

public:
	// [multimap.cons], construct/copy/destroy
	HAMON_CXX11_CONSTEXPR
	multimap() : multimap(Compare())
	{}

	explicit HAMON_CXX11_CONSTEXPR
	multimap(Compare const& comp, Allocator const& a = Allocator())
		: m_allocator(a)
		, m_impl(comp)
	{}

	explicit HAMON_CXX11_CONSTEXPR
	multimap(Allocator const& a)
		: multimap(Compare(), a)
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	multimap(InputIterator first, InputIterator last, Compare const& comp = Compare(), Allocator const& a = Allocator())
		: multimap(comp, a)
	{
		this->insert(first, last);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	multimap(InputIterator first, InputIterator last, Allocator const& a)
		: multimap(first, last, Compare(), a)
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	HAMON_CXX14_CONSTEXPR
	multimap(hamon::from_range_t, R&& rg, Compare const& comp = Compare(), Allocator const& a = Allocator())
		: multimap(comp, a)
	{
		this->insert_range(hamon::forward<R>(rg));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	HAMON_CXX14_CONSTEXPR
	multimap(hamon::from_range_t, R&& rg, Allocator const& a)
		: multimap(hamon::from_range, hamon::forward<R>(rg), Compare(), a)
	{}

	HAMON_CXX14_CONSTEXPR
	multimap(std::initializer_list<value_type> il, Compare const& comp = Compare(), Allocator const& a = Allocator())
		: multimap(comp, a)
	{
		this->insert(il);
	}

	HAMON_CXX14_CONSTEXPR
	multimap(std::initializer_list<value_type> il, Allocator const& a)
		: multimap(il, Compare(), a)
	{}

	HAMON_CXX14_CONSTEXPR
	multimap(multimap const& x)
		: m_allocator(NodeAllocTraits::select_on_container_copy_construction(x.m_allocator))
	{
		m_impl.copy_from(m_allocator, x.m_impl);
	}

	HAMON_CXX11_CONSTEXPR
	multimap(multimap&& x) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<Compare>::value)
		: m_allocator(hamon::move(x.m_allocator))
		, m_impl(hamon::move(x.m_impl))
	{}

	HAMON_CXX14_CONSTEXPR
	multimap(multimap const& x, hamon::type_identity_t<Allocator> const& a)
		: m_allocator(a)
	{
		// [container.alloc.reqmts]/13
		static_assert(hamon::detail::cpp17_copy_insertable_t<value_type, allocator_type>::value, "");

		m_impl.copy_from(m_allocator, x.m_impl);
	}

	HAMON_CXX14_CONSTEXPR
	multimap(multimap&& x, hamon::type_identity_t<Allocator> const& a)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::allocator_traits<Allocator>::is_always_equal::value &&
			hamon::is_nothrow_move_constructible<Compare>::value)
		: m_allocator(a)
	{
		// [container.alloc.reqmts]/18
		static_assert(hamon::detail::cpp17_move_insertable_t<value_type, allocator_type>::value, "");

		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			// アロケータが異なる場合は要素をstealすることはできないので、
			// 要素をムーブ代入しなければいけない。
			m_impl.move_from(m_allocator, x.m_impl);	// may throw
		}
		else
		{
			// 要素をsteal
			m_impl = hamon::move(x.m_impl);
		}
	}

	HAMON_CXX20_CONSTEXPR
	~multimap()
	{
		this->clear();
	}

	HAMON_CXX14_CONSTEXPR multimap&
	operator=(multimap const& x)
	{
		// [container.alloc.reqmts]/22
		static_assert(hamon::detail::cpp17_copy_insertable_t<value_type, allocator_type>::value, "");
		//static_assert(hamon::detail::cpp17_copy_assignable_t<value_type>::value, "");

		if (hamon::addressof(x) == this)
		{
			return *this;
		}

		this->clear();

		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			// アロケータを伝播
			hamon::detail::propagate_allocator_on_copy(m_allocator, x.m_allocator);
		}

		m_impl.copy_from(m_allocator, x.m_impl);

		return *this;
	}

	HAMON_CXX14_CONSTEXPR multimap&
	operator=(multimap&& x) noexcept(
		hamon::allocator_traits<Allocator>::is_always_equal::value &&
		hamon::is_nothrow_move_assignable<Compare>::value)
	{
		// [container.alloc.reqmts]/26
		static_assert(NodeAllocTraits::propagate_on_container_move_assignment::value ||
			hamon::detail::cpp17_move_insertable_t<value_type, allocator_type>::value, "");

		if (hamon::addressof(x) == this)
		{
			return *this;
		}

		this->clear();

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
		if constexpr (!NodeAllocTraits::propagate_on_container_move_assignment::value)
#else
		if           (!NodeAllocTraits::propagate_on_container_move_assignment::value)
#endif
		{
			if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
			{
				// アロケータを伝播させない場合は要素をstealすることはできないので、
				// 要素をムーブ代入しなければいけない。
				m_impl.move_from(m_allocator, x.m_impl);	// may throw
				return *this;
			}
		}

		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			// アロケータを伝播
			hamon::detail::propagate_allocator_on_move(m_allocator, x.m_allocator);
		}

		// 要素をsteal
		m_impl = hamon::move(x.m_impl);

		return *this;
	}

	HAMON_CXX14_CONSTEXPR multimap&
	operator=(std::initializer_list<value_type> il)
	{
		// [associative.reqmts.general]/38
		static_assert(hamon::detail::cpp17_copy_insertable_t<value_type, allocator_type>::value, "");
		//static_assert(hamon::detail::cpp17_copy_assignable_t<value_type>::value, "");

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
		return m_impl.cbegin();
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator end() noexcept
	{
		return m_impl.end();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator end() const noexcept
	{
		return m_impl.cend();
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

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

	// [multimap.modifiers], modifiers
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace(Args&&... args)
	{
		return m_impl.emplace(m_allocator, hamon::forward<Args>(args)...).first;
	}

HAMON_WARNING_POP()

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_hint(const_iterator position, Args&&... args)
	{
		return m_impl.emplace_hint(m_allocator, position, hamon::forward<Args>(args)...);
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(value_type const& x)
	{
		static_assert(hamon::detail::cpp17_copy_insertable_t<
			value_type, allocator_type>::value, "[associative.reqmts.general]/67");

		// [associative.reqmts.general]/68
		return this->emplace(x);
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(value_type&& x)
	{
		static_assert(hamon::detail::cpp17_move_insertable_t<
			value_type, allocator_type>::value, "[associative.reqmts.general]/67");

		// [associative.reqmts.general]/68
		return this->emplace(hamon::move(x));
	}

	template <typename P,
		// [multimap.modifiers]/1
		typename = hamon::enable_if_t<
			hamon::is_constructible<value_type, P&&>::value>>
	HAMON_CXX14_CONSTEXPR iterator
	insert(P&& x)
	{
		return this->emplace(hamon::forward<P>(x));
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, value_type const& x)
	{
		static_assert(hamon::detail::cpp17_copy_insertable_t<
			value_type, allocator_type>::value, "[associative.reqmts.general]/71");

		// [associative.reqmts.general]/72
		return this->emplace_hint(position, x);
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, value_type&& x)
	{
		static_assert(hamon::detail::cpp17_move_insertable_t<
			value_type, allocator_type>::value, "[associative.reqmts.general]/71");

		// [associative.reqmts.general]/72
		return this->emplace_hint(position, hamon::move(x));
	}

	template <typename P,
		// [multimap.modifiers]/1
		typename = hamon::enable_if_t<
			hamon::is_constructible<value_type, P&&>::value>>
	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, P&& x)
	{
		return this->emplace_hint(position, hamon::forward<P>(x));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void
	insert(InputIterator first, InputIterator last)
	{
		m_impl.insert_range(m_allocator, first, last);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	HAMON_CXX14_CONSTEXPR void
	insert_range(R&& rg)
	{
		m_impl.insert_range(m_allocator, hamon::ranges::begin(rg), hamon::ranges::end(rg));
	}

	HAMON_CXX14_CONSTEXPR void
	insert(std::initializer_list<value_type> il)
	{
		this->insert(il.begin(), il.end());
	}

	HAMON_CXX14_CONSTEXPR node_type
	extract(const_iterator position)
	{
		return hamon::detail::node_handle_access::construct<node_type>(
			m_impl.extract(position), m_allocator);
	}

	HAMON_CXX14_CONSTEXPR node_type
	extract(key_type const& x)
	{
		auto it = this->find(x);
		if (it == this->end())
		{
			return node_type{};
		}
		return this->extract(it);
	}

	template <typename K,
		// [associative.reqmts.general]/180
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare),
		typename = hamon::enable_if_t<
			!hamon::disjunction<
				hamon::is_convertible<K&&, iterator>,
				hamon::is_convertible<K&&, const_iterator>
			>::value>>
	HAMON_CXX14_CONSTEXPR node_type
	extract(K&& x)
	{
		auto it = this->find(hamon::forward<K>(x));
		if (it == this->end())
		{
			return node_type{};
		}
		return this->extract(it);
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(node_type&& nh)
	{
		return m_impl.insert_node(hamon::detail::node_handle_access::release(nh)).first;
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator hint, node_type&& nh)
	{
		return m_impl.insert_node_hint(hint, hamon::detail::node_handle_access::release(nh)).first;
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(iterator position)
	{
		return m_impl.erase(m_allocator, position);
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator position)
	{
		return m_impl.erase(m_allocator, position);
	}

	HAMON_CXX14_CONSTEXPR size_type
	erase(key_type const& x)
	{
		auto const r = this->equal_range(x);
		auto const n = hamon::distance(r.first, r.second);
		this->erase(r.first, r.second);
		return static_cast<size_type>(n);
	}

	template <typename K,
		// [associative.reqmts.general]/180
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare),
		typename = hamon::enable_if_t<
			!hamon::disjunction<
				hamon::is_convertible<K&&, iterator>,
				hamon::is_convertible<K&&, const_iterator>
			>::value>>
	HAMON_CXX14_CONSTEXPR size_type
	erase(K&& x)
	{
		auto const r = this->equal_range(hamon::forward<K>(x));
		auto const n = hamon::distance(r.first, r.second);
		this->erase(r.first, r.second);
		return static_cast<size_type>(n);
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator first, const_iterator last)
	{
		return m_impl.erase(m_allocator, first, last);
	}

	HAMON_CXX14_CONSTEXPR void
	swap(multimap& x) noexcept(
		hamon::allocator_traits<Allocator>::is_always_equal::value &&
		hamon::is_nothrow_swappable<Compare>::value)
	{
		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			hamon::detail::propagate_allocator_on_swap(m_allocator, x.m_allocator);
		}
		hamon::swap(m_impl, x.m_impl);
	}

	HAMON_CXX14_CONSTEXPR void
	clear() noexcept
	{
		m_impl.clear(m_allocator);
	}

	template <typename C2>
	HAMON_CXX14_CONSTEXPR void
	merge(multimap<Key, T, C2, Allocator>& source)
	{
		m_impl.merge(source.m_impl);
	}

	template <typename C2>
	HAMON_CXX14_CONSTEXPR void
	merge(multimap<Key, T, C2, Allocator>&& source)
	{
		this->merge(source);
	}

	template <typename C2>
	HAMON_CXX14_CONSTEXPR void
	merge(map<Key, T, C2, Allocator>& source)
	{
		m_impl.merge(source.m_impl);
	}

	template <typename C2>
	HAMON_CXX14_CONSTEXPR void
	merge(map<Key, T, C2, Allocator>&& source)
	{
		this->merge(source);
	}

	// observers
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	key_compare key_comp() const
	{
		return m_impl.comp().comp;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	value_compare value_comp() const
	{
		return m_impl.comp().comp;
	}

	// map operations
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator find(key_type const& x)
	{
		return m_impl.find(x);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator find(key_type const& x) const
	{
		return m_impl.find(x);
	}

	template <typename K,
		// [associative.reqmts.general]/180
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator find(K const& x)
	{
		return m_impl.find(x);
	}

	template <typename K,
		// [associative.reqmts.general]/180
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator find(K const& x) const
	{
		return m_impl.find(x);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	size_type count(key_type const& x) const
	{
		return m_impl.count(x);
	}

	template <typename K,
		// [associative.reqmts.general]/180
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	size_type count(K const& x) const
	{
		return m_impl.count(x);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	bool contains(key_type const& x) const
	{
		return m_impl.contains(x);
	}

	template <typename K,
		// [associative.reqmts.general]/180
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	bool contains(K const& x) const
	{
		return m_impl.contains(x);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator lower_bound(key_type const& x)
	{
		return m_impl.lower_bound(x);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator lower_bound(key_type const& x) const
	{
		return m_impl.lower_bound(x);
	}

	template <typename K,
		// [associative.reqmts.general]/180
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator lower_bound(K const& x)
	{
		return m_impl.lower_bound(x);
	}

	template <typename K,
		// [associative.reqmts.general]/180
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator lower_bound(K const& x) const
	{
		return m_impl.lower_bound(x);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator upper_bound(key_type const& x)
	{
		return m_impl.upper_bound(x);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator upper_bound(key_type const& x) const
	{
		return m_impl.upper_bound(x);
	}

	template <typename K,
		// [associative.reqmts.general]/180
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator upper_bound(K const& x)
	{
		return m_impl.upper_bound(x);
	}

	template <typename K,
		// [associative.reqmts.general]/180
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator upper_bound(K const& x) const
	{
		return m_impl.upper_bound(x);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	hamon::pair<iterator, iterator>
	equal_range(key_type const& x)
	{
		return m_impl.equal_range(x);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	hamon::pair<const_iterator, const_iterator>
	equal_range(key_type const& x) const
	{
		return m_impl.equal_range(x);
	}

	template <typename K,
		// [associative.reqmts.general]/180
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	hamon::pair<iterator, iterator>
	equal_range(K const& x)
	{
		return m_impl.equal_range(x);
	}

	template <typename K,
		// [associative.reqmts.general]/180
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	hamon::pair<const_iterator, const_iterator>
	equal_range(K const& x) const
	{
		return m_impl.equal_range(x);
	}

private:
	template <typename, typename, typename, typename>
	friend class map;

	template <typename, typename, typename, typename>
	friend class multimap;
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::not_simple_allocator, Compare, hamon::less<hamon::detail::iter_key_type<InputIterator>>),
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::simple_allocator, Allocator, hamon::allocator<hamon::detail::iter_to_alloc_type<InputIterator>>)>
multimap(InputIterator, InputIterator, Compare = Compare(), Allocator = Allocator())
->multimap<
	hamon::detail::iter_key_type<InputIterator>,
	hamon::detail::iter_mapped_type<InputIterator>,
	Compare,
	Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::not_simple_allocator, Compare, hamon::less<hamon::detail::range_key_type<R>>),
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::simple_allocator, Allocator, hamon::allocator<hamon::detail::range_to_alloc_type<R>>)>
multimap(hamon::from_range_t, R&&, Compare = Compare(), Allocator = Allocator())
->multimap<
	hamon::detail::range_key_type<R>,
	hamon::detail::range_mapped_type<R>,
	Compare,
	Allocator>;

template <
	typename Key, typename T,
	typename A = hamon::allocator<hamon::pair<Key const, T>>,
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::not_simple_allocator, Compare, hamon::less<Key>),
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::simple_allocator, Allocator, A)>
multimap(std::initializer_list<hamon::pair<Key, T>>, Compare = Compare(), Allocator = Allocator())
->multimap<Key, T, Compare, Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	HAMON_CONSTRAINED_PARAM(hamon::detail::simple_allocator, Allocator)>
multimap(InputIterator, InputIterator, Allocator)
->multimap<
	hamon::detail::iter_key_type<InputIterator>,
	hamon::detail::iter_mapped_type<InputIterator>,
	hamon::less<hamon::detail::iter_key_type<InputIterator>>,
	Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	HAMON_CONSTRAINED_PARAM(hamon::detail::simple_allocator, Allocator)>
multimap(hamon::from_range_t, R&&, Allocator)
->multimap<
	hamon::detail::range_key_type<R>,
	hamon::detail::range_mapped_type<R>,
	hamon::less<hamon::detail::range_key_type<R>>,
	Allocator>;

template <
	typename Key, typename T,
	HAMON_CONSTRAINED_PARAM(hamon::detail::simple_allocator, Allocator)>
multimap(std::initializer_list<hamon::pair<Key, T>>, Allocator)
->multimap<Key, T, hamon::less<Key>, Allocator>;

#endif

template <typename Key, typename T, typename Compare, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator==(multimap<Key, T, Compare, Allocator> const& x, multimap<Key, T, Compare, Allocator> const& y)
{
	return hamon::equal(x.begin(), x.end(), y.begin(), y.end());
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename Key, typename T, typename Compare, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
hamon::detail::synth_three_way_result<hamon::pair<Key const, T>>
operator<=>(multimap<Key, T, Compare, Allocator> const& x, multimap<Key, T, Compare, Allocator> const& y)
{
	return hamon::lexicographical_compare_three_way(
		x.begin(), x.end(),
		y.begin(), y.end(),
		hamon::detail::synth_three_way);
}

#else

template <typename Key, typename T, typename Compare, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator!=(multimap<Key, T, Compare, Allocator> const& x, multimap<Key, T, Compare, Allocator> const& y)
{
	return !(x == y);
}

template <typename Key, typename T, typename Compare, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<(multimap<Key, T, Compare, Allocator> const& x, multimap<Key, T, Compare, Allocator> const& y)
{
	return hamon::lexicographical_compare(
		x.begin(), x.end(),
		y.begin(), y.end());
}

template <typename Key, typename T, typename Compare, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>(multimap<Key, T, Compare, Allocator> const& x, multimap<Key, T, Compare, Allocator> const& y)
{
	return y < x;
}

template <typename Key, typename T, typename Compare, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<=(multimap<Key, T, Compare, Allocator> const& x, multimap<Key, T, Compare, Allocator> const& y)
{
	return !(x > y);
}

template <typename Key, typename T, typename Compare, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>=(multimap<Key, T, Compare, Allocator> const& x, multimap<Key, T, Compare, Allocator> const& y)
{
	return !(x < y);
}

#endif

template <typename Key, typename T, typename Compare, typename Allocator>
HAMON_CXX14_CONSTEXPR void
swap(multimap<Key, T, Compare, Allocator>& x, multimap<Key, T, Compare, Allocator>& y)
	noexcept(noexcept(x.swap(y)))
{
	x.swap(y);
}

}	// namespace hamon

#endif

#endif // HAMON_MAP_MULTIMAP_HPP
