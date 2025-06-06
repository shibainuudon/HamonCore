/**
 *	@file	flat_multimap.hpp
 *
 *	@brief	flat_multimap の定義
 */

#ifndef HAMON_FLAT_MAP_FLAT_MULTIMAP_HPP
#define HAMON_FLAT_MAP_FLAT_MULTIMAP_HPP

#include <hamon/flat_map/flat_multimap_fwd.hpp>
#include <hamon/flat_map/sorted_equivalent.hpp>
#include <hamon/flat_map/config.hpp>

#if !defined(HAMON_USE_STD_FLAT_MAP)

#include <hamon/compare/detail/synth_three_way.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/container/detail/alloc_rebind.hpp>
#include <hamon/container/detail/container_compatible_range.hpp>
#include <hamon/container/detail/has_is_transparent.hpp>
#include <hamon/container/detail/iter_key_type.hpp>
#include <hamon/container/detail/iter_mapped_type.hpp>
#include <hamon/container/detail/range_key_type.hpp>
#include <hamon/container/detail/range_mapped_type.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/pair.hpp>
#include <hamon/memory.hpp>
#include <hamon/ranges.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/vector.hpp>
#include <initializer_list>
#include <memory>	// uses_allocator

namespace hamon
{

namespace detail
{

template <
	typename KeyContainer,
	typename MappedContainer,
	bool Constant
>
struct flat_multimap_iterator;

}	// namespace detail

template <
	class Key,
	class T,
	class Compare = hamon::less<Key>,
	class KeyContainer = hamon::vector<Key>,
	class MappedContainer = hamon::vector<T>
>
class flat_multimap
{
public:
	// types
	using key_type               = Key;
	using mapped_type            = T;
	using value_type             = hamon::pair<key_type, mapped_type>;
	using key_compare            = Compare;
	using reference              = hamon::pair<key_type const&, mapped_type&>;
	using const_reference        = hamon::pair<key_type const&, mapped_type const&>;
	using size_type              = hamon::size_t;
	using difference_type        = hamon::ptrdiff_t;
	using iterator               = hamon::detail::flat_multimap_iterator<KeyContainer, MappedContainer, false>;
	using const_iterator         = hamon::detail::flat_multimap_iterator<KeyContainer, MappedContainer, true>;
	using reverse_iterator       = hamon::reverse_iterator<iterator>;
	using const_reverse_iterator = hamon::reverse_iterator<const_iterator>;
	using key_container_type     = KeyContainer;
	using mapped_container_type  = MappedContainer;

	class value_compare
	{
	private:
		key_compare comp;

		constexpr
		value_compare(key_compare c)
			: comp(c)
		{}

	public:
		constexpr bool
		operator()(const_reference x, const_reference y) const
		{
			return comp(x.first, y.first);
		}
	};

	struct containers
	{
		key_container_type keys;
		mapped_container_type values;
	};

	// [flat.multimap.cons], constructors
	constexpr
	flat_multimap()
		: flat_multimap(key_compare())
	{}

	constexpr explicit
	flat_multimap(key_compare const& comp)
		: c(), compare(comp)
	{}

	constexpr
	flat_multimap(
		key_container_type key_cont,
		mapped_container_type mapped_cont,
		key_compare const& comp = key_compare());

	constexpr
	flat_multimap(
		hamon::sorted_equivalent_t,
		key_container_type key_cont,
		mapped_container_type mapped_cont,
		key_compare const& comp = key_compare());

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	constexpr
	flat_multimap(
		InputIterator first,
		InputIterator last,
		key_compare const& comp = key_compare())
		: c(), compare(comp)
	{
		insert(first, last);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	constexpr
	flat_multimap(
		hamon::sorted_equivalent_t,
		InputIterator first,
		InputIterator last,
		key_compare const& comp = key_compare())
		: c(), compare(comp)
	{
		insert(hamon::sorted_equivalent, first, last);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	constexpr
	flat_multimap(hamon::from_range_t, R&& rg)
		: flat_multimap(hamon::from_range, hamon::forward<R>(rg), key_compare())
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	constexpr
	flat_multimap(hamon::from_range_t, R&& rg, key_compare const& comp)
		: flat_multimap(comp)
	{
		insert_range(hamon::forward<R>(rg));
	}

	constexpr
	flat_multimap(
		std::initializer_list<value_type> il,
		key_compare const& comp = key_compare())
		: flat_multimap(il.begin(), il.end(), comp)
	{}

	constexpr
	flat_multimap(
		hamon::sorted_equivalent_t,
		std::initializer_list<value_type> il,
		key_compare const& comp = key_compare())
		: flat_multimap(hamon::sorted_equivalent, il.begin(), il.end(), comp)
	{}

	// [flat.multimap.cons.alloc], constructors with allocators

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr explicit
	flat_multimap(Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_multimap(
		key_compare const& comp,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_multimap(
		key_container_type const& key_cont,
		mapped_container_type const& mapped_cont,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_multimap(
		key_container_type const& key_cont,
		mapped_container_type const& mapped_cont,
		key_compare const& comp,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_multimap(
		hamon::sorted_equivalent_t,
		key_container_type const& key_cont,
		mapped_container_type const& mapped_cont,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_multimap(
		hamon::sorted_equivalent_t,
		key_container_type const& key_cont,
		mapped_container_type const& mapped_cont,
		key_compare const& comp,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_multimap(
		flat_multimap const&,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_multimap(
		flat_multimap&&,
		Alloc const& a);

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_multimap(
		InputIterator first,
		InputIterator last,
		Alloc const& a);

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_multimap(
		InputIterator first,
		InputIterator last,
		key_compare const& comp,
		Alloc const& a);

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_multimap(
		hamon::sorted_equivalent_t,
		InputIterator first,
		InputIterator last,
		Alloc const& a);

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_multimap(
		hamon::sorted_equivalent_t,
		InputIterator first,
		InputIterator last,
		key_compare const& comp,
		Alloc const& a);

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_multimap(
		hamon::from_range_t,
		R&& rg,
		Alloc const& a);

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_multimap(
		hamon::from_range_t,
		R&& rg,
		key_compare const& comp,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_multimap(
		std::initializer_list<value_type> il,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_multimap(
		std::initializer_list<value_type> il,
		key_compare const& comp,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_multimap(
		hamon::sorted_equivalent_t,
		std::initializer_list<value_type> il,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_multimap(
		hamon::sorted_equivalent_t,
		std::initializer_list<value_type> il,
		key_compare const& comp,
		Alloc const& a);

	flat_multimap&
	operator=(std::initializer_list<value_type>);

	// iterators
	constexpr iterator
	begin() noexcept;

	constexpr const_iterator
	begin() const noexcept;

	constexpr iterator
	end() noexcept;

	constexpr const_iterator
	end() const noexcept;

	constexpr reverse_iterator
	rbegin() noexcept;

	constexpr const_reverse_iterator
	rbegin() const noexcept;

	constexpr reverse_iterator
	rend() noexcept;

	constexpr const_reverse_iterator
	rend() const noexcept;

	constexpr const_iterator
	cbegin() const noexcept;

	constexpr const_iterator
	cend() const noexcept;

	constexpr const_reverse_iterator
	crbegin() const noexcept;

	constexpr const_reverse_iterator
	crend() const noexcept;

	// capacity
	constexpr bool
	empty() const noexcept;

	constexpr size_type
	size() const noexcept;

	constexpr size_type
	max_size() const noexcept;

	// modifiers
	template <typename... Args>
	constexpr iterator
	emplace(Args&&... args);

	template <typename... Args>
	constexpr iterator
	emplace_hint(const_iterator position, Args&&... args);

	constexpr iterator
	insert(value_type const& x)
	{
		return emplace(x);
	}

	constexpr iterator
	insert(value_type&& x)
	{
		return emplace(hamon::move(x));
	}

	constexpr iterator
	insert(const_iterator position, value_type const& x)
	{
		return emplace_hint(position, x);
	}

	constexpr iterator
	insert(const_iterator position, value_type&& x)
	{
		return emplace_hint(position, hamon::move(x));
	}

	template <class P>
	constexpr iterator
	insert(P&& x);

	template <class P>
	constexpr iterator
	insert(const_iterator position, P&&);

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	constexpr void
	insert(InputIterator first, InputIterator last);

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	constexpr void
	insert(hamon::sorted_equivalent_t, InputIterator first, InputIterator last);

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	constexpr void
	insert_range(R&& rg);

	constexpr void
	insert(std::initializer_list<value_type> il)
	{
		insert(il.begin(), il.end());
	}

	constexpr void
	insert(hamon::sorted_equivalent_t, std::initializer_list<value_type> il)
	{
		insert(hamon::sorted_equivalent, il.begin(), il.end());
	}

	constexpr containers
	extract() &&;

	constexpr void
	replace(key_container_type&& key_cont, mapped_container_type&& mapped_cont);

	constexpr iterator
	erase(iterator position);

	constexpr iterator
	erase(const_iterator position);

	constexpr size_type
	erase(key_type const& x);

	template <typename K>
	constexpr size_type
	erase(K&& x);

	constexpr iterator
	erase(const_iterator first, const_iterator last);

	constexpr void
	swap(flat_multimap&) noexcept;

	constexpr void
	clear() noexcept;

	// observers
	constexpr key_compare
	key_comp() const;

	constexpr value_compare
	value_comp() const;

	constexpr key_container_type const&
	keys() const noexcept
	{
		return c.keys;
	}

	constexpr mapped_container_type const&
	values() const noexcept
	{
		return c.values;
	}

	// map operations
	constexpr iterator
	find(key_type const& x);

	constexpr const_iterator
	find(key_type const& x) const;

	template <typename K>
	constexpr iterator
	find(K const& x);

	template <typename K>
	constexpr const_iterator
	find(K const& x) const;

	constexpr size_type
	count(key_type const& x) const;

	template <typename K>
	constexpr size_type
	count(K const& x) const;

	constexpr bool
	contains(key_type const& x) const;

	template <typename K>
	constexpr bool
	contains(K const& x) const;

	constexpr iterator
	lower_bound(key_type const& x);

	constexpr const_iterator
	lower_bound(key_type const& x) const;

	template <typename K>
	constexpr iterator
	lower_bound(K const& x);

	template <typename K>
	constexpr const_iterator
	lower_bound(K const& x) const;

	constexpr iterator
	upper_bound(key_type const& x);

	constexpr const_iterator
	upper_bound(key_type const& x) const;

	template <typename K>
	constexpr iterator
	upper_bound(K const& x);

	template <typename K>
	constexpr const_iterator
	upper_bound(K const& x) const;

	constexpr hamon::pair<iterator, iterator>
	equal_range(key_type const& x);

	constexpr hamon::pair<const_iterator, const_iterator>
	equal_range(key_type const& x) const;

	template <typename K>
	constexpr hamon::pair<iterator, iterator>
	equal_range(K const& x);

	template <typename K>
	constexpr hamon::pair<const_iterator, const_iterator>
	equal_range(K const& x) const;

	constexpr friend bool
	operator==(flat_multimap const& x, flat_multimap const& y);

	constexpr friend
	hamon::detail::synth_three_way_result<value_type>
	operator<=>(flat_multimap const& x, flat_multimap const& y);

	constexpr friend void
	swap(flat_multimap& x, flat_multimap& y) noexcept
	{
		x.swap(y);
	}

private:
	containers c;               // exposition only
	key_compare compare;        // exposition only
};

template <
	class KeyContainer,
	class MappedContainer,
	class Compare = hamon::less<typename KeyContainer::value_type>
>
flat_multimap(
	KeyContainer,
	MappedContainer,
	Compare = Compare())
->flat_multimap<
	typename KeyContainer::value_type,
	typename MappedContainer::value_type,
	Compare,
	KeyContainer,
	MappedContainer>;

template <
	class KeyContainer,
	class MappedContainer,
	class Allocator
>
flat_multimap(
	KeyContainer,
	MappedContainer,
	Allocator)
->flat_multimap<
	typename KeyContainer::value_type,
	typename MappedContainer::value_type,
	hamon::less<typename KeyContainer::value_type>,
	KeyContainer,
	MappedContainer>;

template <
	class KeyContainer,
	class MappedContainer,
	class Compare,
	class Allocator>
flat_multimap(
	KeyContainer,
	MappedContainer,
	Compare,
	Allocator)
->flat_multimap<
	typename KeyContainer::value_type,
	typename MappedContainer::value_type,
	Compare,
	KeyContainer,
	MappedContainer>;

template <
	class KeyContainer,
	class MappedContainer,
	class Compare = hamon::less<typename KeyContainer::value_type>
>
flat_multimap(
	hamon::sorted_equivalent_t,
	KeyContainer,
	MappedContainer,
	Compare = Compare())
->flat_multimap<
	typename KeyContainer::value_type,
	typename MappedContainer::value_type,
	Compare,
	KeyContainer,
	MappedContainer>;

template <
	class KeyContainer,
	class MappedContainer,
	class Allocator
>
flat_multimap(
	hamon::sorted_equivalent_t,
	KeyContainer,
	MappedContainer,
	Allocator)
->flat_multimap<
	typename KeyContainer::value_type,
	typename MappedContainer::value_type,
	hamon::less<typename KeyContainer::value_type>,
	KeyContainer,
	MappedContainer>;

template <
	class KeyContainer,
	class MappedContainer,
	class Compare,
	class Allocator
>
flat_multimap(
	hamon::sorted_equivalent_t,
	KeyContainer,
	MappedContainer,
	Compare,
	Allocator)
->flat_multimap<
	typename KeyContainer::value_type,
	typename MappedContainer::value_type,
	Compare,
	KeyContainer,
	MappedContainer>;

template <
	class InputIterator,
	class Compare = hamon::less<hamon::detail::iter_key_type<InputIterator>>
>
flat_multimap(
	InputIterator,
	InputIterator,
	Compare = Compare())
->flat_multimap<
	hamon::detail::iter_key_type<InputIterator>,
	hamon::detail::iter_mapped_type<InputIterator>,
	Compare>;

template <
	class InputIterator,
	class Compare = hamon::less<hamon::detail::iter_key_type<InputIterator>>
>
flat_multimap(
	hamon::sorted_equivalent_t,
	InputIterator,
	InputIterator,
	Compare = Compare())
->flat_multimap<
	hamon::detail::iter_key_type<InputIterator>,
	hamon::detail::iter_mapped_type<InputIterator>,
	Compare>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	class Compare = hamon::less<hamon::detail::range_key_type<R>>,
	class Allocator = hamon::allocator<byte>
>
flat_multimap(
	hamon::from_range_t, R&&,
	Compare = Compare(),
	Allocator = Allocator())
->flat_multimap<
	hamon::detail::range_key_type<R>,
	hamon::detail::range_mapped_type<R>,
	Compare,
	hamon::vector<hamon::detail::range_key_type<R>, hamon::detail::alloc_rebind<Allocator, hamon::detail::range_key_type<R>>>,
	hamon::vector<hamon::detail::range_mapped_type<R>, hamon::detail::alloc_rebind<Allocator, hamon::detail::range_mapped_type<R>>>>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	class Allocator
>
flat_multimap(
	hamon::from_range_t, R&&,
	Allocator)
->flat_multimap<
	hamon::detail::range_key_type<R>,
	hamon::detail::range_mapped_type<R>,
	hamon::less<hamon::detail::range_key_type<R>>,
	hamon::vector<hamon::detail::range_key_type<R>, hamon::detail::alloc_rebind<Allocator, hamon::detail::range_key_type<R>>>,
	hamon::vector<hamon::detail::range_mapped_type<R>, hamon::detail::alloc_rebind<Allocator, hamon::detail::range_mapped_type<R>>>>;

template <
	class Key,
	class T,
	class Compare = hamon::less<Key>
>
flat_multimap(
	std::initializer_list<hamon::pair<Key, T>>,
	Compare = Compare())
->flat_multimap<
	Key,
	T,
	Compare>;

template <
	class Key,
	class T,
	class Compare = hamon::less<Key>
>
flat_multimap(
	hamon::sorted_equivalent_t,
	std::initializer_list<hamon::pair<Key, T>>,
	Compare = Compare())
->flat_multimap<
	Key,
	T,
	Compare>;

//template <class Key, class T, class Compare, class KeyContainer, class MappedContainer, class Allocator>
//struct uses_allocator<flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>, Allocator>
//	: hamon::bool_constant<uses_allocator_v<KeyContainer, Allocator> && uses_allocator_v<MappedContainer, Allocator>> {};

// [flat.multimap.erasure], erasure for flat_multimap
template <class Key, class T, class Compare, class KeyContainer, class MappedContainer, class Predicate>
constexpr typename flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>::size_type
erase_if(flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>& c, Predicate pred);

}	// namespace hamon

#endif

#endif // HAMON_FLAT_MAP_FLAT_MULTIMAP_HPP
