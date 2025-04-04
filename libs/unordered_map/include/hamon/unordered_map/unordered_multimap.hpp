﻿/**
 *	@file	unordered_multimap.hpp
 *
 *	@brief	unordered_multimap の定義
 */

#ifndef HAMON_UNORDERED_MAP_UNORDERED_MULTIMAP_HPP
#define HAMON_UNORDERED_MAP_UNORDERED_MULTIMAP_HPP

#include <hamon/unordered_map/unordered_multimap_fwd.hpp>
#include <hamon/unordered_map/config.hpp>

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)

#include <hamon/unordered_map/unordered_map_fwd.hpp>

#include <hamon/container/detail/has_is_transparent.hpp>
#include <hamon/container/detail/hash_table.hpp>
#include <hamon/container/detail/iter_key_type.hpp>
#include <hamon/container/detail/iter_mapped_type.hpp>
#include <hamon/container/detail/iter_to_alloc_type.hpp>
#include <hamon/container/detail/node_handle.hpp>
#include <hamon/container/detail/range_key_type.hpp>
#include <hamon/container/detail/range_mapped_type.hpp>
#include <hamon/container/detail/range_to_alloc_type.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory_resource/polymorphic_allocator.hpp>
#include <hamon/pair.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/detail/container_compatible_range.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_swappable.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

namespace hamon
{

// 23.5.4 Class template unordered_multimap[unord.multimap]

template <typename Key, typename T, typename Hash, typename Pred, typename Allocator>
class unordered_multimap
{
public:
	// types
	using key_type             = Key;
	using mapped_type          = T;
	using value_type           = hamon::pair<Key const, T>;
	using hasher               = Hash;
	using key_equal            = Pred;
	using allocator_type       = Allocator;
	using pointer              = typename hamon::allocator_traits<Allocator>::pointer;
	using const_pointer        = typename hamon::allocator_traits<Allocator>::const_pointer;
	using reference            = value_type&;
	using const_reference      = value_type const&;
	using size_type            = typename hamon::allocator_traits<Allocator>::size_type;
	using difference_type      = typename hamon::allocator_traits<Allocator>::difference_type;

private:
	using HashTable = hamon::detail::hash_table<true, key_type, value_type, hasher, key_equal>;
	using HashTableNode = typename HashTable::node_type;

	static constexpr size_type kDefaultBucketCount = 0;

public:
	using iterator             = typename HashTable::iterator;
	using const_iterator       = typename HashTable::const_iterator;
	using local_iterator       = typename HashTable::local_iterator;
	using const_local_iterator = typename HashTable::const_local_iterator;
	using node_type            = hamon::detail::map_node_handle<HashTableNode, Allocator>;

	// [unord.multimap.cnstr], construct/copy/destroy
	constexpr unordered_multimap();

	constexpr explicit
	unordered_multimap(
		size_type n,
		hasher const& hf = hasher(),
		key_equal const& eql = key_equal(),
		allocator_type const& a = allocator_type());

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	constexpr
	unordered_multimap(
		InputIterator f,
		InputIterator l,
		size_type n = kDefaultBucketCount,
		hasher const& hf = hasher(),
		key_equal const& eql = key_equal(),
		allocator_type const& a = allocator_type());

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	constexpr
	unordered_multimap(
		hamon::from_range_t,
		R&& rg,
		size_type n = kDefaultBucketCount,
		hasher const& hf = hasher(),
		key_equal const& eql = key_equal(),
		allocator_type const& a = allocator_type());

	constexpr
	unordered_multimap(unordered_multimap const&);

	constexpr
	unordered_multimap(unordered_multimap&&);

	constexpr explicit
	unordered_multimap(Allocator const&);

	constexpr
	unordered_multimap(unordered_multimap const&, hamon::type_identity_t<Allocator> const&);

	constexpr
	unordered_multimap(unordered_multimap&&, hamon::type_identity_t<Allocator> const&);

	constexpr
	unordered_multimap(
		std::initializer_list<value_type> il,
		size_type n = kDefaultBucketCount,
		hasher const& hf = hasher(),
		key_equal const& eql = key_equal(),
		allocator_type const& a = allocator_type());

	constexpr
	unordered_multimap(size_type n, allocator_type const& a)
		: unordered_multimap(n, hasher(), key_equal(), a)
	{}

	constexpr
	unordered_multimap(size_type n, hasher const& hf, allocator_type const& a)
		: unordered_multimap(n, hf, key_equal(), a)
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	constexpr
	unordered_multimap(
		InputIterator f, InputIterator l,
		size_type n,
		allocator_type const& a)
		: unordered_multimap(f, l, n, hasher(), key_equal(), a)
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	constexpr
	unordered_multimap(
		InputIterator f, InputIterator l,
		size_type n,
		hasher const& hf,
		allocator_type const& a)
		: unordered_multimap(f, l, n, hf, key_equal(), a)
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	constexpr
	unordered_multimap(
		hamon::from_range_t,
		R&& rg,
		size_type n,
		allocator_type const& a)
		: unordered_multimap(hamon::from_range, hamon::forward<R>(rg), n, hasher(), key_equal(), a)
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	constexpr
	unordered_multimap(
		hamon::from_range_t,
		R&& rg,
		size_type n,
		hasher const& hf,
		allocator_type const& a)
		: unordered_multimap(hamon::from_range, hamon::forward<R>(rg), n, hf, key_equal(), a)
	{}

	constexpr
	unordered_multimap(
		std::initializer_list<value_type> il,
		size_type n,
		allocator_type const& a)
		: unordered_multimap(il, n, hasher(), key_equal(), a)
	{}

	constexpr
	unordered_multimap(
		std::initializer_list<value_type> il,
		size_type n,
		hasher const& hf,
		allocator_type const& a)
		: unordered_multimap(il, n, hf, key_equal(), a)
	{}

	HAMON_CXX20_CONSTEXPR
	~unordered_multimap();

	HAMON_CXX14_CONSTEXPR unordered_multimap&
	operator=(unordered_multimap const&);

	HAMON_CXX14_CONSTEXPR unordered_multimap&
	operator=(unordered_multimap&&) noexcept(
		hamon::allocator_traits<Allocator>::is_always_equal::value &&
		hamon::is_nothrow_move_assignable<Hash>::value &&
		hamon::is_nothrow_move_assignable<Pred>::value);

	HAMON_CXX14_CONSTEXPR unordered_multimap&
	operator=(std::initializer_list<value_type>);

	constexpr allocator_type
	get_allocator() const noexcept;

	// iterators
	HAMON_CXX14_CONSTEXPR iterator
	begin() noexcept;

	constexpr const_iterator
	begin() const noexcept;

	HAMON_CXX14_CONSTEXPR iterator
	end() noexcept;

	constexpr const_iterator
	end() const noexcept;

	constexpr const_iterator
	cbegin() const noexcept;

	constexpr const_iterator
	cend() const noexcept;

	// capacity
	constexpr bool
	empty() const noexcept;

	constexpr size_type
	size() const noexcept;

	constexpr size_type
	max_size() const noexcept;

	// [unord.multimap.modifiers], modifiers
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace(Args&&... args);

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_hint(const_iterator position, Args&&... args);

	HAMON_CXX14_CONSTEXPR iterator
	insert(value_type const& obj);

	HAMON_CXX14_CONSTEXPR iterator
	insert(value_type&& obj);

	template <typename P,
		// [unord.multimap.modifiers]/1
		typename = hamon::enable_if_t<
			hamon::is_constructible<value_type, P&&>::value>>
	HAMON_CXX14_CONSTEXPR iterator
	insert(P&& obj)
	{
		// [unord.multimap.modifiers]/2
		return emplace(hamon::forward<P>(obj));
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator hint, value_type const& obj);

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator hint, value_type&& obj);

	template <typename P,
		// [unord.multimap.modifiers]/3
		typename = hamon::enable_if_t<
			hamon::is_constructible<value_type, P&&>::value>>
	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator hint, P&& obj)
	{
		// [unord.multimap.modifiers]/3
		return emplace_hint(hint, hamon::forward<P>(obj));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void
	insert(InputIterator first, InputIterator last);

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	HAMON_CXX14_CONSTEXPR void
	insert_range(R&& rg);

	HAMON_CXX14_CONSTEXPR void
	insert(std::initializer_list<value_type>);

	HAMON_CXX14_CONSTEXPR node_type
	extract(const_iterator position);

	HAMON_CXX14_CONSTEXPR node_type
	extract(key_type const& x);

	template <typename K,
		// [unord.req.general]/247
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred),
		typename = hamon::enable_if_t<
			!hamon::disjunction<
				hamon::is_convertible<K&&, iterator>,
				hamon::is_convertible<K&&, const_iterator>
			>::value>>
	HAMON_CXX14_CONSTEXPR node_type
	extract(K&& x);

	HAMON_CXX14_CONSTEXPR iterator
	insert(node_type&& nh);

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator hint, node_type&& nh);

	HAMON_CXX14_CONSTEXPR iterator
	erase(iterator position);

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator position);

	HAMON_CXX14_CONSTEXPR size_type
	erase(key_type const& k);

	template <typename K,
		// [unord.req.general]/247
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred),
		typename = hamon::enable_if_t<
			!hamon::disjunction<
				hamon::is_convertible<K&&, iterator>,
				hamon::is_convertible<K&&, const_iterator>
			>::value>>
	HAMON_CXX14_CONSTEXPR size_type
	erase(K&& x);

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator first, const_iterator last);

	HAMON_CXX14_CONSTEXPR void
	swap(unordered_multimap&) noexcept(
		hamon::allocator_traits<Allocator>::is_always_equal::value &&
		hamon::is_nothrow_swappable<Hash>::value &&
		hamon::is_nothrow_swappable<Pred>::value);

	HAMON_CXX14_CONSTEXPR void
	clear() noexcept;

	template <typename H2, typename P2>
	HAMON_CXX14_CONSTEXPR void
	merge(unordered_multimap<Key, T, H2, P2, Allocator>& source);

	template <typename H2, typename P2>
	HAMON_CXX14_CONSTEXPR void
	merge(unordered_multimap<Key, T, H2, P2, Allocator>&& source);

	template <typename H2, typename P2>
	HAMON_CXX14_CONSTEXPR void
	merge(unordered_map<Key, T, H2, P2, Allocator>& source);

	template <typename H2, typename P2>
	HAMON_CXX14_CONSTEXPR void
	merge(unordered_map<Key, T, H2, P2, Allocator>&& source);

	// observers
	constexpr hasher
	hash_function() const;

	constexpr key_equal
	key_eq() const;

	// map operations
	HAMON_CXX14_CONSTEXPR iterator
	find(key_type const& k);

	constexpr const_iterator
	find(key_type const& k) const;

	template <typename K,
		// [unord.req.general]/247
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred)>
	HAMON_CXX14_CONSTEXPR iterator
	find(K const& k);

	template <typename K,
		// [unord.req.general]/247
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred)>
	constexpr const_iterator
	find(K const& k) const;

	constexpr size_type
	count(key_type const& k) const;

	template <typename K,
		// [unord.req.general]/247
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred)>
	constexpr size_type
	count(K const& k) const;

	constexpr bool
	contains(key_type const& k) const;

	template <typename K,
		// [unord.req.general]/247
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred)>
	constexpr bool
	contains(K const& k) const;

	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, iterator>
	equal_range(key_type const& k);

	constexpr hamon::pair<const_iterator, const_iterator>
	equal_range(key_type const& k) const;

	template <typename K,
		// [unord.req.general]/247
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred)>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, iterator>
	equal_range(K const& k);

	template <typename K,
		// [unord.req.general]/247
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred)>
	constexpr hamon::pair<const_iterator, const_iterator>
	equal_range(K const& k) const;

	// bucket interface
	constexpr size_type
	bucket_count() const noexcept;

	constexpr size_type
	max_bucket_count() const noexcept;

	constexpr size_type
	bucket_size(size_type n) const;

	constexpr size_type
	bucket(key_type const& k) const;

	template <typename K,
		// [unord.req.general]/247
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred)>
	constexpr size_type
	bucket(K const& k) const;

	HAMON_CXX14_CONSTEXPR local_iterator
	begin(size_type n);

	constexpr const_local_iterator
	begin(size_type n) const;

	HAMON_CXX14_CONSTEXPR local_iterator
	end(size_type n);

	constexpr const_local_iterator
	end(size_type n) const;

	constexpr const_local_iterator
	cbegin(size_type n) const;

	constexpr const_local_iterator
	cend(size_type n) const;

	// hash policy
	constexpr float
	load_factor() const noexcept;

	constexpr float
	max_load_factor() const noexcept;

	HAMON_CXX14_CONSTEXPR void
	max_load_factor(float z);

	HAMON_CXX14_CONSTEXPR void
	rehash(size_type n);

	HAMON_CXX14_CONSTEXPR void
	reserve(size_type n);
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	typename Hash = hamon::hash<hamon::detail::iter_key_type<InputIterator>>,
	typename Pred = hamon::equal_to<hamon::detail::iter_key_type<InputIterator>>,
	typename Allocator = hamon::allocator<hamon::detail::iter_to_alloc_type<InputIterator>>>
unordered_multimap(
	InputIterator, InputIterator,
	typename hamon::allocator_traits<Allocator>::size_type = 0/*see below*/,
	Hash = Hash(), Pred = Pred(), Allocator = Allocator())
->unordered_multimap<
	hamon::detail::iter_key_type<InputIterator>,
	hamon::detail::iter_mapped_type<InputIterator>,
	Hash, Pred, Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Hash = hamon::hash<hamon::detail::range_key_type<R>>,
	typename Pred = hamon::equal_to<hamon::detail::range_key_type<R>>,
	typename Allocator = hamon::allocator<hamon::detail::range_to_alloc_type<R>>>
unordered_multimap(
	hamon::from_range_t, R&&,
	typename hamon::allocator_traits<Allocator>::size_type = 0/*see below*/,
	Hash = Hash(), Pred = Pred(), Allocator = Allocator())
->unordered_multimap<
	hamon::detail::range_key_type<R>,
	hamon::detail::range_mapped_type<R>,
	Hash, Pred, Allocator>;

template <
	typename Key, typename T,
	typename Hash = hamon::hash<Key>,
	typename Pred = hamon::equal_to<Key>,
	typename Allocator = hamon::allocator<hamon::pair<Key const, T>>>
unordered_multimap(
	std::initializer_list<hamon::pair<Key, T>>,
	typename hamon::allocator_traits<Allocator>::size_type = 0/*see below*/,
	Hash = Hash(), Pred = Pred(), Allocator = Allocator())
->unordered_multimap<Key, T, Hash, Pred, Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	typename Allocator>
unordered_multimap(
	InputIterator, InputIterator,
	typename hamon::allocator_traits<Allocator>::size_type,
	Allocator)
->unordered_multimap<
	hamon::detail::iter_key_type<InputIterator>,
	hamon::detail::iter_mapped_type<InputIterator>,
	hamon::hash<hamon::detail::iter_key_type<InputIterator>>,
	hamon::equal_to<hamon::detail::iter_key_type<InputIterator>>,
	Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	typename Allocator>
unordered_multimap(InputIterator, InputIterator, Allocator)
->unordered_multimap<
	hamon::detail::iter_key_type<InputIterator>,
	hamon::detail::iter_mapped_type<InputIterator>,
	hamon::hash<hamon::detail::iter_key_type<InputIterator>>,
	hamon::equal_to<hamon::detail::iter_key_type<InputIterator>>,
	Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	typename Hash,
	typename Allocator>
unordered_multimap(
	InputIterator, InputIterator,
	typename hamon::allocator_traits<Allocator>::size_type,
	Hash, Allocator)
->unordered_multimap<
	hamon::detail::iter_key_type<InputIterator>,
	hamon::detail::iter_mapped_type<InputIterator>,
	Hash,
	hamon::equal_to<hamon::detail::iter_key_type<InputIterator>>,
	Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Allocator>
unordered_multimap(
	hamon::from_range_t, R&&,
	typename hamon::allocator_traits<Allocator>::size_type,
	Allocator)
->unordered_multimap<
	hamon::detail::range_key_type<R>,
	hamon::detail::range_mapped_type<R>,
	hamon::hash<hamon::detail::range_key_type<R>>,
	hamon::equal_to<hamon::detail::range_key_type<R>>,
	Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Allocator>
unordered_multimap(hamon::from_range_t, R&&, Allocator)
->unordered_multimap<
	hamon::detail::range_key_type<R>,
	hamon::detail::range_mapped_type<R>,
	hamon::hash<hamon::detail::range_key_type<R>>,
	hamon::equal_to<hamon::detail::range_key_type<R>>,
	Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Hash, typename Allocator>
unordered_multimap(
	hamon::from_range_t, R&&,
	typename hamon::allocator_traits<Allocator>::size_type,
	Hash, Allocator)
->unordered_multimap<
	hamon::detail::range_key_type<R>,
	hamon::detail::range_mapped_type<R>,
	Hash,
	hamon::equal_to<hamon::detail::range_key_type<R>>,
	Allocator>;

template <typename Key, typename T, typename Allocator>
unordered_multimap(
	std::initializer_list<hamon::pair<Key, T>>,
	typename hamon::allocator_traits<Allocator>::size_type,
	Allocator)
->unordered_multimap<Key, T, hamon::hash<Key>, hamon::equal_to<Key>, Allocator>;

template <typename Key, typename T, typename Allocator>
unordered_multimap(
	std::initializer_list<hamon::pair<Key, T>>,
	Allocator)
->unordered_multimap<Key, T, hamon::hash<Key>, hamon::equal_to<Key>, Allocator>;

template <typename Key, typename T, typename Hash, typename Allocator>
unordered_multimap(
	std::initializer_list<hamon::pair<Key, T>>,
	typename hamon::allocator_traits<Allocator>::size_type,
	Hash, Allocator)
->unordered_multimap<Key, T, Hash, hamon::equal_to<Key>, Allocator>;

#endif

template <typename Key, typename T, typename Hash, typename Pred, typename Alloc>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator==(
	unordered_multimap<Key, T, Hash, Pred, Alloc> const& a,
	unordered_multimap<Key, T, Hash, Pred, Alloc> const& b);

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename Key, typename T, typename Hash, typename Pred, typename Alloc>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator!=(
	unordered_multimap<Key, T, Hash, Pred, Alloc> const& a,
	unordered_multimap<Key, T, Hash, Pred, Alloc> const& b)
{
	return !(a == b);
}
#endif

template <typename Key, typename T, typename Hash, typename Pred, typename Alloc>
HAMON_CXX14_CONSTEXPR void
swap(
	unordered_multimap<Key, T, Hash, Pred, Alloc>& x,
	unordered_multimap<Key, T, Hash, Pred, Alloc>& y)
	noexcept(noexcept(x.swap(y)));

namespace pmr
{

template <
	typename Key,
	typename T,
	typename Hash = hamon::hash<Key>,
	typename Pred = hamon::equal_to<Key>
>
using unordered_multimap =
	hamon::unordered_multimap<Key, T, Hash, Pred,
		hamon::pmr::polymorphic_allocator<hamon::pair<Key const, T>>>;

}	// namespace pmr

}	// namespace hamon

#endif

#endif // HAMON_UNORDERED_MAP_UNORDERED_MULTIMAP_HPP
