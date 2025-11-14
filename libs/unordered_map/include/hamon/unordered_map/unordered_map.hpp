/**
 *	@file	unordered_map.hpp
 *
 *	@brief	unordered_map の定義
 */

#ifndef HAMON_UNORDERED_MAP_UNORDERED_MAP_HPP
#define HAMON_UNORDERED_MAP_UNORDERED_MAP_HPP

#include <hamon/unordered_map/unordered_map_fwd.hpp>
#include <hamon/unordered_map/config.hpp>

#if !defined(HAMON_USE_STD_UNORDERED_MAP)

#include <hamon/unordered_map/unordered_multimap_fwd.hpp>

#include <hamon/cmath/ceil.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
//#include <hamon/concepts/detail/cpp17_copy_assignable.hpp>
#include <hamon/concepts/detail/cpp17_copy_constructible.hpp>
#include <hamon/concepts/detail/cpp17_default_constructible.hpp>
//#include <hamon/concepts/detail/cpp17_hash.hpp>
#include <hamon/container/detail/container_compatible_range.hpp>
#include <hamon/container/detail/deduced_size_type_t.hpp>
#include <hamon/container/detail/has_is_transparent.hpp>
#include <hamon/container/detail/hash_table.hpp>
#include <hamon/container/detail/insert_return_type.hpp>
#include <hamon/container/detail/iter_key_type.hpp>
#include <hamon/container/detail/iter_mapped_type.hpp>
#include <hamon/container/detail/iter_to_alloc_type.hpp>
#include <hamon/container/detail/is_hasher.hpp>
#include <hamon/container/detail/map_compare.hpp>
#include <hamon/container/detail/map_hash.hpp>
#include <hamon/container/detail/node_handle.hpp>
#include <hamon/container/detail/range_key_type.hpp>
#include <hamon/container/detail/range_mapped_type.hpp>
#include <hamon/container/detail/range_to_alloc_type.hpp>
#include <hamon/container/detail/cpp17_copy_insertable.hpp>
#include <hamon/container/detail/cpp17_emplace_constructible.hpp>
#include <hamon/container/detail/cpp17_erasable.hpp>
#include <hamon/container/detail/cpp17_move_insertable.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/detail/equals_allocator.hpp>
#include <hamon/memory/detail/propagate_allocator_on_copy.hpp>
#include <hamon/memory/detail/propagate_allocator_on_move.hpp>
#include <hamon/memory/detail/propagate_allocator_on_swap.hpp>
#include <hamon/memory/detail/simple_allocator.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/pair/piecewise_construct_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/tuple/forward_as_tuple.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_swappable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>
#include <initializer_list>

namespace hamon
{

// 23.5.3 Class template unordered_map[unord.map]

template <typename Key, typename T, typename Hash, typename Pred, typename Allocator>
class unordered_map
{
private:
	using AllocTraits = hamon::allocator_traits<Allocator>;

public:
	// types
	using key_type             = Key;
	using mapped_type          = T;
	using value_type           = hamon::pair<Key const, T>;
	using hasher               = Hash;
	using key_equal            = Pred;
	using allocator_type       = Allocator;
	using pointer              = typename AllocTraits::pointer;
	using const_pointer        = typename AllocTraits::const_pointer;
	using reference            = value_type&;
	using const_reference      = value_type const&;
	using size_type            = typename AllocTraits::size_type;
	using difference_type      = typename AllocTraits::difference_type;

	static_assert(hamon::is_same<typename allocator_type::value_type, value_type>::value, "[container.alloc.reqmts]/5");

private:
	using MapHash    = hamon::detail::map_hash<hasher>;
	using MapCompare = hamon::detail::map_compare<key_equal>;
	using HashTable  = hamon::detail::hash_table<key_type, value_type, MapHash, MapCompare, allocator_type, false>;

public:
	using iterator             = typename HashTable::iterator;
	using const_iterator       = typename HashTable::const_iterator;
	using local_iterator       = typename HashTable::local_iterator;
	using const_local_iterator = typename HashTable::const_local_iterator;
	using node_type            = hamon::detail::map_node_handle<typename HashTable::node_type, Allocator>;
	using insert_return_type   = hamon::detail::insert_return_type<iterator, node_type>;

	// TODO
	//static_assert(hamon::detail::cpp17_hash_t<Hash, Key>::value, "[unord.req.general]/3");
	static_assert(hamon::detail::cpp17_erasable_t<value_type, allocator_type>::value, "[unord.req.general]/16");
	static_assert(hamon::detail::cpp17_copy_constructible_t<Pred>::value, "[unord.req.general]/20");

private:
	HAMON_NO_UNIQUE_ADDRESS	allocator_type m_allocator;
	HashTable                              m_impl;

public:
	// [unord.map.cnstr], construct/copy/destroy
	HAMON_CXX14_CONSTEXPR
	unordered_map()	// may throw
		: unordered_map(size_type())	// [unord.map.cnstr]/1
	{
		static_assert(hamon::detail::cpp17_default_constructible_t<hasher>::value, "[unord.req.general]/32");
		static_assert(hamon::detail::cpp17_default_constructible_t<key_equal>::value, "[unord.req.general]/32");
	}

	HAMON_CXX14_CONSTEXPR explicit
	unordered_map(
		size_type n,
		hasher const& hf = hasher(),
		key_equal const& eql = key_equal(),
		allocator_type const& a = allocator_type())	// may throw
		: m_allocator(a)
		, m_impl(n, hf, eql, a)	// [unord.map.cnstr]/1
	{}

	HAMON_CXX14_CONSTEXPR
	unordered_map(size_type n, hasher const& hf, allocator_type const& a)	// may throw
		: unordered_map(n, hf, key_equal(), a)
	{
		static_assert(hamon::detail::cpp17_default_constructible_t<key_equal>::value, "[unord.req.general]/26");
	}

	HAMON_CXX14_CONSTEXPR
	unordered_map(size_type n, allocator_type const& a)	// may throw
		: unordered_map(n, hasher(), key_equal(), a)
	{
		static_assert(hamon::detail::cpp17_default_constructible_t<hasher>::value, "[unord.req.general]/29");
		static_assert(hamon::detail::cpp17_default_constructible_t<key_equal>::value, "[unord.req.general]/29");
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	unordered_map(
		InputIterator f, InputIterator l,
		size_type n = size_type(),
		hasher const& hf = hasher(),
		key_equal const& eql = key_equal(),
		allocator_type const& a = allocator_type())	// may throw
		: m_allocator(a)
		, m_impl(n, hf, eql, a)	// [unord.map.cnstr]/3
	{
		static_assert(hamon::detail::cpp17_emplace_constructible_t<
			value_type, allocator_type, decltype(*f)>::value, "[unord.req.general]/35");

		// [unord.map.cnstr]/3
		this->insert(f, l);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	unordered_map(
		InputIterator f, InputIterator l,
		size_type n,
		hasher const& hf,
		allocator_type const& a)	// may throw
		: unordered_map(f, l, n, hf, key_equal(), a)
	{
		static_assert(hamon::detail::cpp17_emplace_constructible_t<
			value_type, allocator_type, decltype(*f)>::value, "[unord.req.general]/38");
		static_assert(hamon::detail::cpp17_default_constructible_t<key_equal>::value, "[unord.req.general]/38");
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	unordered_map(
		InputIterator f, InputIterator l,
		size_type n,
		allocator_type const& a)	// may throw
		: unordered_map(f, l, n, hasher(), key_equal(), a)
	{
		static_assert(hamon::detail::cpp17_emplace_constructible_t<
			value_type, allocator_type, decltype(*f)>::value, "[unord.req.general]/41");
		static_assert(hamon::detail::cpp17_default_constructible_t<hasher>::value, "[unord.req.general]/41");
		static_assert(hamon::detail::cpp17_default_constructible_t<key_equal>::value, "[unord.req.general]/41");
	}

	// LWG 2713
	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	unordered_map(InputIterator f, InputIterator l, allocator_type const& a)	// may throw
		: unordered_map(f, l, size_type(), hasher(), key_equal(), a)
	{
		static_assert(hamon::detail::cpp17_emplace_constructible_t<
			value_type, allocator_type, decltype(*f)>::value, "[unord.req.general]/44");
		static_assert(hamon::detail::cpp17_default_constructible_t<hasher>::value, "[unord.req.general]/44");
		static_assert(hamon::detail::cpp17_default_constructible_t<key_equal>::value, "[unord.req.general]/44");
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	HAMON_CXX14_CONSTEXPR
	unordered_map(
		hamon::from_range_t, R&& rg,
		size_type n = size_type(),
		hasher const& hf = hasher(),
		key_equal const& eql = key_equal(),
		allocator_type const& a = allocator_type())	// may throw
		: m_allocator(a)
		, m_impl(n, hf, eql, a)	// [unord.map.cnstr]/3
	{
		static_assert(hamon::detail::cpp17_emplace_constructible_t<
			value_type, allocator_type, decltype(*ranges::begin(rg))>::value, "[unord.req.general]/47");

		// [unord.map.cnstr]/3
		this->insert_range(hamon::forward<R>(rg));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	HAMON_CXX14_CONSTEXPR
	unordered_map(
		hamon::from_range_t, R&& rg,
		size_type n,
		hasher const& hf,
		allocator_type const& a)	// may throw
		: unordered_map(hamon::from_range, hamon::forward<R>(rg), n, hf, key_equal(), a)
	{
		static_assert(hamon::detail::cpp17_emplace_constructible_t<
			value_type, allocator_type, decltype(*ranges::begin(rg))>::value, "[unord.req.general]/50");
		static_assert(hamon::detail::cpp17_default_constructible_t<key_equal>::value, "[unord.req.general]/50");
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	HAMON_CXX14_CONSTEXPR
	unordered_map(
		hamon::from_range_t, R&& rg,
		size_type n,
		allocator_type const& a)	// may throw
		: unordered_map(hamon::from_range, hamon::forward<R>(rg), n, hasher(), key_equal(), a)
	{
		static_assert(hamon::detail::cpp17_emplace_constructible_t<
			value_type, allocator_type, decltype(*ranges::begin(rg))>::value, "[unord.req.general]/53");
		static_assert(hamon::detail::cpp17_default_constructible_t<hasher>::value, "[unord.req.general]/53");
		static_assert(hamon::detail::cpp17_default_constructible_t<key_equal>::value, "[unord.req.general]/53");
	}

	// LWG 2713
	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	HAMON_CXX14_CONSTEXPR
	unordered_map(hamon::from_range_t, R&& rg, allocator_type const& a)	// may throw
		: unordered_map(hamon::from_range, hamon::forward<R>(rg), size_type(), hasher(), key_equal(), a)
	{
		static_assert(hamon::detail::cpp17_emplace_constructible_t<
			value_type, allocator_type, decltype(*ranges::begin(rg))>::value, "[unord.req.general]/56");
		static_assert(hamon::detail::cpp17_default_constructible_t<hasher>::value, "[unord.req.general]/56");
		static_assert(hamon::detail::cpp17_default_constructible_t<key_equal>::value, "[unord.req.general]/56");
	}

	HAMON_CXX14_CONSTEXPR
	unordered_map(
		std::initializer_list<value_type> il,
		size_type n = size_type(),
		hasher const& hf = hasher(),
		key_equal const& eql = key_equal(),
		allocator_type const& a = allocator_type())	// may throw
		: m_allocator(a)
		, m_impl(n, hf, eql, a)	// [unord.map.cnstr]/3
	{
		// [unord.map.cnstr]/3
		this->insert(il);
	}

	HAMON_CXX14_CONSTEXPR
	unordered_map(
		std::initializer_list<value_type> il,
		size_type n,
		allocator_type const& a)	// may throw
		: unordered_map(il, n, hasher(), key_equal(), a)
	{}

	HAMON_CXX14_CONSTEXPR
	unordered_map(
		std::initializer_list<value_type> il,
		size_type n,
		hasher const& hf,
		allocator_type const& a)	// may throw
		: unordered_map(il, n, hf, key_equal(), a)
	{}

	// LWG 2713
	HAMON_CXX14_CONSTEXPR
	unordered_map(std::initializer_list<value_type> il, allocator_type const& a)	// may throw
		: unordered_map(il, size_type(), hasher(), key_equal(), a)
	{}

	HAMON_CXX14_CONSTEXPR explicit
	unordered_map(Allocator const& a)	// may throw
		: unordered_map(size_type(), hasher(), key_equal(), a)
	{}

	HAMON_CXX14_CONSTEXPR
	unordered_map(unordered_map const& x)	// may throw
		: unordered_map(x.bucket_count(), x.hash_function(), x.key_eq(),
			AllocTraits::select_on_container_copy_construction(x.m_allocator))
	{
		m_impl.copy_from(m_allocator, x.m_impl);	// may throw
	}

	HAMON_CXX11_CONSTEXPR
	unordered_map(unordered_map&& x) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<Allocator>::value &&
		hamon::is_nothrow_move_constructible<Hash>::value &&
		hamon::is_nothrow_move_constructible<Pred>::value)
		: m_allocator(hamon::move(x.m_allocator))
		, m_impl(hamon::move(x.m_impl))
	{}

	HAMON_CXX14_CONSTEXPR
	unordered_map(unordered_map const& x, hamon::type_identity_t<Allocator> const& a)
		: unordered_map(x.bucket_count(), x.hash_function(), x.key_eq(), a)
	{
		m_impl.copy_from(m_allocator, x.m_impl);	// may throw
	}

	HAMON_CXX14_CONSTEXPR
	unordered_map(unordered_map&& x, hamon::type_identity_t<Allocator> const& a)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			AllocTraits::is_always_equal::value &&
			hamon::is_nothrow_move_assignable<Hash>::value &&
			hamon::is_nothrow_move_assignable<Pred>::value)
		: m_allocator(a)
		, m_impl(x.hash_function(), x.key_eq())
	{
		// [container.alloc.reqmts]/18
		static_assert(hamon::detail::cpp17_move_insertable_t<value_type, allocator_type>::value, "");

		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			// アロケータが異なる場合は要素をstealすることはできないので、
			// 要素をムーブ代入しなければいけない。
			m_impl.create_buckets(m_allocator, x.bucket_count());	// may throw
			m_impl.move_from(m_allocator, x.m_impl);	// may throw
		}
		else
		{
			// 要素をsteal
			m_impl = hamon::move(x.m_impl);
		}
	}

	HAMON_CXX20_CONSTEXPR
	~unordered_map() HAMON_NOEXCEPT
	{
		m_impl.clear(m_allocator);
		m_impl.destroy_buckets(m_allocator);
	}

	HAMON_CXX14_CONSTEXPR unordered_map&
	operator=(unordered_map const& x)
	{
		if (hamon::addressof(x) == this)
		{
			return *this;
		}

		m_impl.clear(m_allocator);

		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			m_impl.destroy_buckets(m_allocator);

			// アロケータを伝播
			hamon::detail::propagate_allocator_on_copy(m_allocator, x.m_allocator);

			m_impl.create_buckets(m_allocator, x.bucket_count());	// may throw
		}

		m_impl.copy_from(m_allocator, x.m_impl);	// may throw

		return *this;
	}

	HAMON_CXX14_CONSTEXPR unordered_map&
	operator=(unordered_map&& x) HAMON_NOEXCEPT_IF(
		AllocTraits::is_always_equal::value &&
		hamon::is_nothrow_move_assignable<Hash>::value &&
		hamon::is_nothrow_move_assignable<Pred>::value)
	{
		// [container.alloc.reqmts]/26
		static_assert(AllocTraits::propagate_on_container_move_assignment::value ||
			hamon::detail::cpp17_move_insertable_t<value_type, allocator_type>::value, "");

		if (hamon::addressof(x) == this)
		{
			return *this;
		}

		m_impl.clear(m_allocator);
		m_impl.destroy_buckets(m_allocator);

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
		if constexpr (!AllocTraits::propagate_on_container_move_assignment::value)
#else
		if           (!AllocTraits::propagate_on_container_move_assignment::value)
#endif
		{
			if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
			{
				// アロケータを伝播させない場合は要素をstealすることはできないので、
				// 要素をムーブ代入しなければいけない。
				m_impl.create_buckets(m_allocator, x.bucket_count());	// may throw
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

	HAMON_CXX14_CONSTEXPR unordered_map&
	operator=(std::initializer_list<value_type> il)
	{
		static_assert(hamon::detail::cpp17_copy_insertable_t<
			value_type, allocator_type>::value, "[unord.req.general]/69");
		//static_assert(hamon::detail::cpp17_copy_assignable_t<value_type>::value, "[unord.req.general]/69");

		this->clear();
		this->insert(il);	// may throw
		return *this;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR allocator_type
	get_allocator() const HAMON_NOEXCEPT
	{
		// [container.alloc.reqmts]/6
		return m_allocator;
	}

	// iterators
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	begin() HAMON_NOEXCEPT
	{
		return m_impl.begin();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	begin() const HAMON_NOEXCEPT
	{
		return m_impl.begin();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	end() HAMON_NOEXCEPT
	{
		return m_impl.end();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	end() const HAMON_NOEXCEPT
	{
		return m_impl.end();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	cbegin() const HAMON_NOEXCEPT
	{
		return m_impl.begin();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	cend() const HAMON_NOEXCEPT
	{
		return m_impl.end();
	}

	// capacity
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool
	empty() const HAMON_NOEXCEPT
	{
		// [container.reqmts]/60
		return this->size() == 0;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type
	size() const HAMON_NOEXCEPT
	{
		// [container.reqmts]/53
		return m_impl.size();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type
	max_size() const HAMON_NOEXCEPT
	{
		// [container.reqmts]/57
		return m_impl.max_size(m_allocator);
	}

	// [unord.map.modifiers], modifiers
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	emplace(Args&&... args)
	{
		static_assert(hamon::detail::cpp17_emplace_constructible_t<
			value_type, allocator_type, Args...>::value, "[unord.req.general]/79");

		// [unord.req.general]/80
		return m_impl.emplace(m_allocator, hamon::forward<Args>(args)...);	// may throw
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_hint(const_iterator /*position*/, Args&&... args)
	{
		static_assert(hamon::detail::cpp17_emplace_constructible_t<
			value_type, allocator_type, Args...>::value, "[unord.req.general]/89");

		// [unord.req.general]/90
		return this->emplace(hamon::forward<Args>(args)...).first;	// may throw
	}

	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	insert(value_type const& obj)
	{
		static_assert(hamon::detail::cpp17_copy_insertable_t<
			value_type, allocator_type>::value, "[unord.req.general]/92");

		// [unord.req.general]/93
		return this->emplace(obj);	// may throw
	}

	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	insert(value_type&& obj)
	{
		static_assert(hamon::detail::cpp17_move_insertable_t<
			value_type, allocator_type>::value, "[unord.req.general]/92");

		// [unord.req.general]/93
		return this->emplace(hamon::move(obj));	// may throw
	}

	template <typename P,
		// [unord.map.modifiers]/1
		typename = hamon::enable_if_t<
			hamon::is_constructible<value_type, P&&>::value>>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	insert(P&& obj)
	{
		// [unord.map.modifiers]/2
		return this->emplace(hamon::forward<P>(obj));	// may throw
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator hint, value_type const& obj)
	{
		static_assert(hamon::detail::cpp17_copy_insertable_t<
			value_type, allocator_type>::value, "[unord.req.general]/102");

		// [unord.req.general]/103
		return this->emplace_hint(hint, obj);	// may throw
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator hint, value_type&& obj)
	{
		static_assert(hamon::detail::cpp17_move_insertable_t<
			value_type, allocator_type>::value, "[unord.req.general]/102");

		// [unord.req.general]/103
		return this->emplace_hint(hint, hamon::move(obj));	// may throw
	}

	template <typename P,
		// [unord.map.modifiers]/3
		typename = hamon::enable_if_t<
			hamon::is_constructible<value_type, P&&>::value>>
	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator hint, P&& obj)
	{
		// [unord.map.modifiers]/4
		return this->emplace_hint(hint, hamon::forward<P>(obj));	// may throw
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void
	insert(InputIterator first, InputIterator last)
	{
		static_assert(hamon::detail::cpp17_emplace_constructible_t<
			value_type, allocator_type, decltype(*first)>::value, "[unord.req.general]/109");

		// TODO
		// [unord.req.general]/109
		// Neither first nor last are iterators into *this.

		// [unord.req.general]/110
		m_impl.insert_range(m_allocator, first, last);	// may throw
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	HAMON_CXX14_CONSTEXPR void
	insert_range(R&& rg)
	{
		static_assert(hamon::detail::cpp17_emplace_constructible_t<
			value_type, allocator_type, decltype(*ranges::begin(rg))>::value, "[unord.req.general]/113");

		// TODO
		// [unord.req.general]/113
		// rg and *this do not overlap.

		// [unord.req.general]/114
		m_impl.insert_range(m_allocator, hamon::ranges::begin(rg), hamon::ranges::end(rg));	// may throw
	}

	HAMON_CXX14_CONSTEXPR void
	insert(std::initializer_list<value_type> il)
	{
		// [unord.req.general]/116
		this->insert(il.begin(), il.end());	// may throw
	}

	HAMON_CXX14_CONSTEXPR node_type
	extract(const_iterator position) HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [unord.req.general]/142
		return hamon::detail::node_handle_access::construct<node_type>(
			m_impl.extract(position), m_allocator);
	}

	HAMON_CXX14_CONSTEXPR node_type
	extract(key_type const& x)
		HAMON_NOEXCEPT_IF_EXPR(this->find(x))	// noexcept as an extension
	{
		// [unord.req.general]/134
		auto it = this->find(x);
		if (it == this->end())
		{
			return node_type{};
		}
		return this->extract(it);
	}

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
	extract(K&& x)
		HAMON_NOEXCEPT_IF_EXPR(this->find(hamon::forward<K>(x)))	// noexcept as an extension
	{
		// [unord.req.general]/138
		auto it = this->find(hamon::forward<K>(x));
		if (it == this->end())
		{
			return node_type{};
		}
		return this->extract(it);
	}

	HAMON_CXX14_CONSTEXPR insert_return_type
	insert(node_type&& nh)
	{
		// [unord.req.general]/118
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
		if (!hamon::is_constant_evaluated())
		{
			if (!nh.empty())
			{
				HAMON_ASSERT(this->get_allocator() == nh.get_allocator());
			}
		}
#endif
		// [unord.req.general]/119
		auto r = m_impl.insert_node(
			m_allocator, hamon::detail::node_handle_access::ptr(nh));	// may throw
		if (r.second)
		{
			hamon::detail::node_handle_access::release(nh);
		}
		return insert_return_type{r.first, r.second, hamon::move(nh)};
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator /*hint*/, node_type&& nh)
	{
		// [unord.req.general]/128
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
		if (!hamon::is_constant_evaluated())
		{
			if (!nh.empty())
			{
				HAMON_ASSERT(this->get_allocator() == nh.get_allocator());
			}
		}
#endif
		// [unord.req.general]/129
		auto r = m_impl.insert_node(
			m_allocator, hamon::detail::node_handle_access::ptr(nh));	// may throw
		if (r.second)
		{
			hamon::detail::node_handle_access::release(nh);
		}
		return r.first;
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	try_emplace(key_type const& k, Args&&... args)
	{
		// [unord.map.modifiers]/6
		return m_impl.try_emplace(m_allocator, k,
			hamon::piecewise_construct,
			hamon::forward_as_tuple(k),
			hamon::forward_as_tuple(hamon::forward<Args>(args)...));	// may throw
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	try_emplace(key_type&& k, Args&&... args)
	{
		// [unord.map.modifiers]/10
		return m_impl.try_emplace(m_allocator, k,
			hamon::piecewise_construct,
			hamon::forward_as_tuple(hamon::move(k)),
			hamon::forward_as_tuple(hamon::forward<Args>(args)...));	// may throw
	}

	template <typename K, typename... Args,
		// [unord.map.modifiers]/13
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred),
		typename = hamon::enable_if_t<
			!hamon::disjunction<
				hamon::is_convertible<K&&, iterator>,
				hamon::is_convertible<K&&, const_iterator>
			>::value>>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	try_emplace(K&& k, Args&&... args)
	{
		// [unord.map.modifiers]/15
		return m_impl.try_emplace(m_allocator, k,
			hamon::piecewise_construct,
			hamon::forward_as_tuple(hamon::forward<K>(k)),
			hamon::forward_as_tuple(hamon::forward<Args>(args)...));	// may throw
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	try_emplace(const_iterator /*hint*/, key_type const& k, Args&&... args)
	{
		return this->try_emplace(k, hamon::forward<Args>(args)...).first;	// may throw
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	try_emplace(const_iterator /*hint*/, key_type&& k, Args&&... args)
	{
		return this->try_emplace(hamon::move(k), hamon::forward<Args>(args)...).first;	// may throw
	}

	template <typename K, typename... Args,
		// [unord.map.modifiers]/13
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred)>
	HAMON_CXX14_CONSTEXPR iterator
	try_emplace(const_iterator /*hint*/, K&& k, Args&&... args)
	{
		return this->try_emplace(hamon::forward<K>(k), hamon::forward<Args>(args)...).first;	// may throw
	}

	template <typename M>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	insert_or_assign(key_type const& k, M&& obj)
	{
		// [unord.map.modifiers]/18
		static_assert(hamon::is_assignable<mapped_type&, M&&>::value, "");

		// [unord.map.modifiers]/20
		auto r = m_impl.try_emplace(m_allocator, k,
			hamon::piecewise_construct,
			hamon::forward_as_tuple(k),
			hamon::forward_as_tuple(hamon::forward<M>(obj)));	// may throw
		if (!r.second)
		{
			r.first->second = hamon::forward<M>(obj);
		}

		// [unord.map.modifiers]/21
		return r;
	}

	template <typename M>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	insert_or_assign(key_type&& k, M&& obj)
	{
		// [unord.map.modifiers]/23
		static_assert(hamon::is_assignable<mapped_type&, M&&>::value, "");

		// [unord.map.modifiers]/25
		auto r = m_impl.try_emplace(m_allocator, k,
			hamon::piecewise_construct,
			hamon::forward_as_tuple(hamon::move(k)),
			hamon::forward_as_tuple(hamon::forward<M>(obj)));	// may throw
		if (!r.second)
		{
			r.first->second = hamon::forward<M>(obj);
		}

		// [unord.map.modifiers]/26
		return r;
	}

	template <typename K, typename M,
		// [unord.map.modifiers]/28
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred)>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	insert_or_assign(K&& k, M&& obj)
	{
		// [unord.map.modifiers]/29
		static_assert(hamon::is_assignable<mapped_type&, M&&>::value, "");

		// [unord.map.modifiers]/31
		auto r = m_impl.try_emplace(m_allocator, k,
			hamon::piecewise_construct,
			hamon::forward_as_tuple(hamon::forward<K>(k)),
			hamon::forward_as_tuple(hamon::forward<M>(obj)));	// may throw
		if (!r.second)
		{
			r.first->second = hamon::forward<M>(obj);
		}

		// [unord.map.modifiers]/32
		return r;
	}

	template <typename M>
	HAMON_CXX14_CONSTEXPR iterator
	insert_or_assign(const_iterator /*hint*/, key_type const& k, M&& obj)
	{
		return this->insert_or_assign(k, hamon::forward<M>(obj)).first;	// may throw
	}

	template <typename M>
	HAMON_CXX14_CONSTEXPR iterator
	insert_or_assign(const_iterator /*hint*/, key_type&& k, M&& obj)
	{
		return this->insert_or_assign(hamon::move(k), hamon::forward<M>(obj)).first;	// may throw
	}

	template <typename K, typename M,
		// [unord.map.modifiers]/28
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred)>
	HAMON_CXX14_CONSTEXPR iterator
	insert_or_assign(const_iterator /*hint*/, K&& k, M&& obj)
	{
		return this->insert_or_assign(hamon::forward<K>(k), hamon::forward<M>(obj)).first;	// may throw
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(iterator position) HAMON_NOEXCEPT_IF_EXPR(
		m_impl.erase(m_allocator, position))	// noexcept as an extension
	{
		// [unord.req.general]/163
		return m_impl.erase(m_allocator, position);
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator position) HAMON_NOEXCEPT_IF_EXPR(
		m_impl.erase(m_allocator, position))	// noexcept as an extension
	{
		// [unord.req.general]/159
		return m_impl.erase(m_allocator, position);
	}

	HAMON_CXX14_CONSTEXPR size_type
	erase(key_type const& k) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		HAMON_NOEXCEPT_EXPR(this->equal_range(k)) &&
		HAMON_NOEXCEPT_EXPR(this->erase(hamon::declval<iterator>(), hamon::declval<iterator>())))
	{
		// [unord.req.general]/151
		auto const r = this->equal_range(k);
		auto const n = hamon::distance(r.first, r.second);
		this->erase(r.first, r.second);

		// [unord.req.general]/152
		return static_cast<size_type>(n);
	}

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
	erase(K&& x) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		HAMON_NOEXCEPT_EXPR(this->equal_range(hamon::forward<K>(x))) &&
		HAMON_NOEXCEPT_EXPR(this->erase(hamon::declval<iterator>(), hamon::declval<iterator>())))
	{
		// [unord.req.general]/155
		auto const r = this->equal_range(hamon::forward<K>(x));
		auto const n = hamon::distance(r.first, r.second);
		this->erase(r.first, r.second);

		// [unord.req.general]/156
		return static_cast<size_type>(n);
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator first, const_iterator last)
		HAMON_NOEXCEPT_IF_EXPR(m_impl.erase_range(m_allocator, first, last))	// noexcept as an extension
	{
		// [unord.req.general]/167
		return m_impl.erase_range(m_allocator, first, last);
	}

	HAMON_CXX14_CONSTEXPR void
	swap(unordered_map& x) HAMON_NOEXCEPT_IF(
		AllocTraits::is_always_equal::value &&
		hamon::is_nothrow_swappable<Hash>::value &&
		hamon::is_nothrow_swappable<Pred>::value)
	{
		// [container.alloc.reqmts]/31
		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			hamon::detail::propagate_allocator_on_swap(m_allocator, x.m_allocator);
		}
		// [container.reqmts]/49
		hamon::swap(m_impl, x.m_impl);
	}

	HAMON_CXX14_CONSTEXPR void
	clear() HAMON_NOEXCEPT
	{
		// [unord.req.general]/171
		m_impl.clear(m_allocator);
	}

	template <typename H2, typename P2>
	HAMON_CXX14_CONSTEXPR void
	merge(unordered_map<Key, T, H2, P2, Allocator>& source)
	{
		// [unord.req.general]/146
		HAMON_ASSERT(this->get_allocator() == source.get_allocator());

		// [unord.req.general]/147
		m_impl.merge(m_allocator, source.m_impl);	// may throw
	}

	template <typename H2, typename P2>
	HAMON_CXX14_CONSTEXPR void
	merge(unordered_map<Key, T, H2, P2, Allocator>&& source)
	{
		this->merge(source);	// may throw
	}

	template <typename H2, typename P2>
	HAMON_CXX14_CONSTEXPR void
	merge(unordered_multimap<Key, T, H2, P2, Allocator>& source)
	{
		// [unord.req.general]/146
		HAMON_ASSERT(this->get_allocator() == source.get_allocator());

		// [unord.req.general]/147
		m_impl.merge(m_allocator, source.m_impl);	// may throw
	}

	template <typename H2, typename P2>
	HAMON_CXX14_CONSTEXPR void
	merge(unordered_multimap<Key, T, H2, P2, Allocator>&& source)
	{
		this->merge(source);	// may throw
	}

	// observers
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR hasher
	hash_function() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_copy_constructible<hasher>::value)
	{
		// [unord.req.general]/73
		return m_impl.hash_function();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR key_equal
	key_eq() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_copy_constructible<key_equal>::value)
	{
		// [unord.req.general]/76
		return m_impl.key_eq();
	}

	// map operations
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	find(key_type const& k)
		HAMON_NOEXCEPT_IF_EXPR(m_impl.find(k))	// noexcept as an extension
	{
		// [unord.req.general]/175
		return m_impl.find(k);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	find(key_type const& k) const
		HAMON_NOEXCEPT_IF_EXPR(m_impl.find(k))	// noexcept as an extension
	{
		// [unord.req.general]/175
		return m_impl.find(k);
	}

	template <typename K,
		// [unord.req.general]/247
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	find(K const& k)
		HAMON_NOEXCEPT_IF_EXPR(m_impl.find(k))	// noexcept as an extension
	{
		// [unord.req.general]/178
		return m_impl.find(k);
	}

	template <typename K,
		// [unord.req.general]/247
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	find(K const& k) const
		HAMON_NOEXCEPT_IF_EXPR(m_impl.find(k))	// noexcept as an extension
	{
		// [unord.req.general]/178
		return m_impl.find(k);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type
	count(key_type const& k) const
		HAMON_NOEXCEPT_IF_EXPR(m_impl.count(k))	// noexcept as an extension
	{
		// [unord.req.general]/181
		return m_impl.count(k);
	}

	template <typename K,
		// [unord.req.general]/247
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type
	count(K const& k) const
		HAMON_NOEXCEPT_IF_EXPR(m_impl.count(k))	// noexcept as an extension
	{
		// [unord.req.general]/184
		return m_impl.count(k);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool
	contains(key_type const& k) const
		HAMON_NOEXCEPT_IF_EXPR(this->find(k))	// noexcept as an extension
	{
		// [unord.req.general]/186
		return this->find(k) != this->end();
	}

	template <typename K,
		// [unord.req.general]/247
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool
	contains(K const& k) const
		HAMON_NOEXCEPT_IF_EXPR(this->find(k))	// noexcept as an extension
	{
		// [unord.req.general]/187
		return this->find(k) != this->end();
	}
	
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, iterator>
	equal_range(key_type const& k)
		HAMON_NOEXCEPT_IF_EXPR(m_impl.equal_range(k))	// noexcept as an extension
	{
		// [unord.req.general]/189
		return m_impl.equal_range(k);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR hamon::pair<const_iterator, const_iterator>
	equal_range(key_type const& k) const
		HAMON_NOEXCEPT_IF_EXPR(m_impl.equal_range(k))	// noexcept as an extension
	{
		// [unord.req.general]/189
		return m_impl.equal_range(k);
	}

	template <typename K,
		// [unord.req.general]/247
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, iterator>
	equal_range(K const& k)
		HAMON_NOEXCEPT_IF_EXPR(m_impl.equal_range(k))	// noexcept as an extension
	{
		// [unord.req.general]/192
		return m_impl.equal_range(k);
	}

	template <typename K,
		// [unord.req.general]/247
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR hamon::pair<const_iterator, const_iterator>
	equal_range(K const& k) const
		HAMON_NOEXCEPT_IF_EXPR(m_impl.equal_range(k))	// noexcept as an extension
	{
		// [unord.req.general]/192
		return m_impl.equal_range(k);
	}

	// [unord.map.elem], element access
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR mapped_type&
	operator[](key_type const& k)
	{
		// [unord.map.elem]/1
		return this->try_emplace(k).first->second;	// may throw
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR mapped_type&
	operator[](key_type&& k)
	{
		// [unord.map.elem]/2
		return this->try_emplace(hamon::move(k)).first->second;	// may throw
	}

	template <typename K,
		// [unord.map.elem]/3
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR mapped_type&
	operator[](K&& k)
	{
		// [unord.map.elem]/4
		return this->try_emplace(hamon::forward<K>(k)).first->second;	// may throw
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR mapped_type&
	at(key_type const& k)
	{
		auto it = this->find(k);
		if (it == this->end())
		{
			// [unord.map.elem]/6
			hamon::detail::throw_out_of_range("unordered_map::at");
		}

		// [unord.map.elem]/5
		return it->second;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR mapped_type const&
	at(key_type const& k) const
	{
		auto it = this->find(k);
		if (it == this->end())
		{
			// [unord.map.elem]/6
			hamon::detail::throw_out_of_range("unordered_map::at");
		}

		// [unord.map.elem]/5
		return it->second;
	}

	template <typename K,
		// [unord.map.elem]/7
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR mapped_type&
	at(K const& k)
	{
		auto it = this->find(k);
		if (it == this->end())
		{
			// [unord.map.elem]/10
			hamon::detail::throw_out_of_range("unordered_map::at");
		}

		// [unord.map.elem]/9
		return it->second;
	}

	template <typename K,
		// [unord.map.elem]/7
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR mapped_type const&
	at(K const& k) const
	{
		auto it = this->find(k);
		if (it == this->end())
		{
			// [unord.map.elem]/10
			hamon::detail::throw_out_of_range("unordered_map::at");
		}

		// [unord.map.elem]/9
		return it->second;
	}

	// bucket interface
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type
	bucket_count() const HAMON_NOEXCEPT
	{
		// [unord.req.general]/195
		return m_impl.bucket_count();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type
	max_bucket_count() const HAMON_NOEXCEPT
	{
		// [unord.req.general]/198
		return m_impl.max_bucket_count();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type
	bucket_size(size_type n) const HAMON_NOEXCEPT	// noexcept as an extension
	{
		return
			HAMON_ASSERT(n < this->bucket_count()),	// [unord.req.general]/210
			m_impl.bucket_size(n);					// [unord.req.general]/211
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type
	bucket(key_type const& k) const
		HAMON_NOEXCEPT_IF_EXPR(m_impl.bucket_index(k))	// noexcept as an extension
	{
		return
			HAMON_ASSERT(this->bucket_count() > size_type{0}),	// [unord.req.general]/201
			m_impl.bucket_index(k);								// [unord.req.general]/202
	}

	template <typename K,
		// [unord.req.general]/247
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, H, Hash),
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, P, Pred)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type
	bucket(K const& k) const
		HAMON_NOEXCEPT_IF_EXPR(m_impl.bucket_index(k))	// noexcept as an extension
	{
		return
			HAMON_ASSERT(this->bucket_count() > size_type{0}),	// [unord.req.general]/205
			m_impl.bucket_index(k);								// [unord.req.general]/207
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR local_iterator
	begin(size_type n) HAMON_NOEXCEPT	// noexcept as an extension
	{
		return
			HAMON_ASSERT(n < this->bucket_count()),	// [unord.req.general]/214
			m_impl.begin(n);						// [unord.req.general]/215
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_local_iterator
	begin(size_type n) const HAMON_NOEXCEPT	// noexcept as an extension
	{
		return
			HAMON_ASSERT(n < this->bucket_count()),	// [unord.req.general]/214
			m_impl.begin(n);						// [unord.req.general]/215
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR local_iterator
	end(size_type n) HAMON_NOEXCEPT	// noexcept as an extension
	{
		return
			HAMON_ASSERT(n < this->bucket_count()),	// [unord.req.general]/218
			m_impl.end(n);							// [unord.req.general]/219
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_local_iterator
	end(size_type n) const HAMON_NOEXCEPT	// noexcept as an extension
	{
		return
			HAMON_ASSERT(n < this->bucket_count()),	// [unord.req.general]/218
			m_impl.end(n);							// [unord.req.general]/219
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_local_iterator
	cbegin(size_type n) const HAMON_NOEXCEPT	// noexcept as an extension
	{
		return
			HAMON_ASSERT(n < this->bucket_count()), // [unord.req.general]/222
			m_impl.begin(n);						// [unord.req.general]/223
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_local_iterator
	cend(size_type n) const HAMON_NOEXCEPT	// noexcept as an extension
	{
		return
			HAMON_ASSERT(n < this->bucket_count()),	// [unord.req.general]/226
			m_impl.end(n);							// [unord.req.general]/227
	}

	// hash policy
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR float
	load_factor() const HAMON_NOEXCEPT
	{
		// [unord.req.general]/230
		return m_impl.load_factor();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR float
	max_load_factor() const HAMON_NOEXCEPT
	{
		// [unord.req.general]/233
		return m_impl.max_load_factor();
	}

	HAMON_CXX14_CONSTEXPR void
	max_load_factor(float z) HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [unord.req.general]/236
		HAMON_ASSERT(z > 0.0f);

		// [unord.req.general]/236
		m_impl.max_load_factor(z);
	}

	HAMON_CXX14_CONSTEXPR void
	rehash(size_type n)
	{
		// [unord.req.general]/239
		m_impl.rehash(m_allocator, n);	// may throw
	}

	HAMON_CXX14_CONSTEXPR void
	reserve(size_type n)
	{
		// [unord.req.general]/241
		this->rehash(static_cast<size_type>(
			hamon::ceil(static_cast<float>(n) / this->max_load_factor())));	// may throw
	}

private:
	template <typename, typename, typename, typename, typename>
	friend class unordered_map;

	template <typename, typename, typename, typename, typename>
	friend class unordered_multimap;
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),																// [unord.req.general]/248.1
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::is_hasher, Hash,
		hamon::hash<hamon::detail::iter_key_type<InputIterator>>),				// [unord.req.general]/248.3
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::not_simple_allocator, Pred,
		hamon::equal_to<hamon::detail::iter_key_type<InputIterator>>),			// [unord.req.general]/248.4
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::simple_allocator, Allocator,
		hamon::allocator<hamon::detail::iter_to_alloc_type<InputIterator>>)>	// [unord.req.general]/248.2
unordered_map(
	InputIterator, InputIterator,
	hamon::detail::deduced_size_type_t<Allocator> = 0/*see below*/,
	Hash = Hash(), Pred = Pred(), Allocator = Allocator())
->unordered_map<
	hamon::detail::iter_key_type<InputIterator>,
	hamon::detail::iter_mapped_type<InputIterator>,
	Hash, Pred, Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),	// [unord.req.general]/248.1
	HAMON_CONSTRAINED_PARAM(hamon::detail::simple_allocator, Allocator)>			// [unord.req.general]/248.2
unordered_map(
	InputIterator, InputIterator,
	hamon::detail::deduced_size_type_t<Allocator>, Allocator)
->unordered_map<
	hamon::detail::iter_key_type<InputIterator>,
	hamon::detail::iter_mapped_type<InputIterator>,
	hamon::hash<hamon::detail::iter_key_type<InputIterator>>,
	hamon::equal_to<hamon::detail::iter_key_type<InputIterator>>,
	Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),	// [unord.req.general]/248.1
	HAMON_CONSTRAINED_PARAM(hamon::detail::is_hasher, Hash),						// [unord.req.general]/248.3
	HAMON_CONSTRAINED_PARAM(hamon::detail::simple_allocator, Allocator)>			// [unord.req.general]/248.2
unordered_map(
	InputIterator, InputIterator,
	hamon::detail::deduced_size_type_t<Allocator>,
	Hash, Allocator)
->unordered_map<
	hamon::detail::iter_key_type<InputIterator>,
	hamon::detail::iter_mapped_type<InputIterator>,
	Hash,
	hamon::equal_to<hamon::detail::iter_key_type<InputIterator>>,
	Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),	// [unord.req.general]/248.1
	HAMON_CONSTRAINED_PARAM(hamon::detail::simple_allocator, Allocator)>			// [unord.req.general]/248.2
unordered_map(InputIterator, InputIterator, Allocator)
->unordered_map<
	hamon::detail::iter_key_type<InputIterator>,
	hamon::detail::iter_mapped_type<InputIterator>,
	hamon::hash<hamon::detail::iter_key_type<InputIterator>>,
	hamon::equal_to<hamon::detail::iter_key_type<InputIterator>>,
	Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::is_hasher, Hash,
		hamon::hash<hamon::detail::range_key_type<R>>),						// [unord.req.general]/248.3
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::not_simple_allocator, Pred,
		hamon::equal_to<hamon::detail::range_key_type<R>>),					// [unord.req.general]/248.4
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::simple_allocator, Allocator,
		hamon::allocator<hamon::detail::range_to_alloc_type<R>>)>			// [unord.req.general]/248.2
unordered_map(
	hamon::from_range_t, R&&,
	hamon::detail::deduced_size_type_t<Allocator> = 0/*see below*/,
	Hash = Hash(), Pred = Pred(), Allocator = Allocator())
->unordered_map<
	hamon::detail::range_key_type<R>,
	hamon::detail::range_mapped_type<R>,
	Hash, Pred, Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	HAMON_CONSTRAINED_PARAM(hamon::detail::simple_allocator, Allocator)>	// [unord.req.general]/248.2
unordered_map(
	hamon::from_range_t, R&&,
	hamon::detail::deduced_size_type_t<Allocator>,
	Allocator)
->unordered_map<
	hamon::detail::range_key_type<R>,
	hamon::detail::range_mapped_type<R>,
	hamon::hash<hamon::detail::range_key_type<R>>,
	hamon::equal_to<hamon::detail::range_key_type<R>>,
	Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	HAMON_CONSTRAINED_PARAM(hamon::detail::is_hasher, Hash),				// [unord.req.general]/248.3
	HAMON_CONSTRAINED_PARAM(hamon::detail::simple_allocator, Allocator)>	// [unord.req.general]/248.2
unordered_map(
	hamon::from_range_t, R&&,
	hamon::detail::deduced_size_type_t<Allocator>,
	Hash, Allocator)
->unordered_map<
	hamon::detail::range_key_type<R>,
	hamon::detail::range_mapped_type<R>,
	Hash,
	hamon::equal_to<hamon::detail::range_key_type<R>>,
	Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	HAMON_CONSTRAINED_PARAM(hamon::detail::simple_allocator, Allocator)>	// [unord.req.general]/248.2
unordered_map(hamon::from_range_t, R&&, Allocator)
->unordered_map<
	hamon::detail::range_key_type<R>,
	hamon::detail::range_mapped_type<R>,
	hamon::hash<hamon::detail::range_key_type<R>>,
	hamon::equal_to<hamon::detail::range_key_type<R>>,
	Allocator>;

template <
	typename Key, typename T,
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::is_hasher, Hash, hamon::hash<Key>),					// [unord.req.general]/248.3
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::not_simple_allocator, Pred, hamon::equal_to<Key>),		// [unord.req.general]/248.4
	typename Pair = hamon::pair<Key const, T>,
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::simple_allocator, Allocator, hamon::allocator<Pair>)>	// [unord.req.general]/248.2
unordered_map(
	std::initializer_list<hamon::pair<Key, T>>,
	hamon::detail::deduced_size_type_t<Allocator> = 0/*see below*/,
	Hash = Hash(), Pred = Pred(), Allocator = Allocator())
->unordered_map<Key, T, Hash, Pred, Allocator>;

template <typename Key, typename T,
	HAMON_CONSTRAINED_PARAM(hamon::detail::simple_allocator, Allocator)>	// [unord.req.general]/248.2
unordered_map(
	std::initializer_list<hamon::pair<Key, T>>,
	hamon::detail::deduced_size_type_t<Allocator>,
	Allocator)
->unordered_map<Key, T, hamon::hash<Key>, hamon::equal_to<Key>, Allocator>;

template <typename Key, typename T,
	HAMON_CONSTRAINED_PARAM(hamon::detail::is_hasher, Hash),				// [unord.req.general]/248.3
	HAMON_CONSTRAINED_PARAM(hamon::detail::simple_allocator, Allocator)>	// [unord.req.general]/248.2
unordered_map(
	std::initializer_list<hamon::pair<Key, T>>,
	hamon::detail::deduced_size_type_t<Allocator>,
	Hash, Allocator)
->unordered_map<Key, T, Hash, hamon::equal_to<Key>, Allocator>;

template <typename Key, typename T,
	HAMON_CONSTRAINED_PARAM(hamon::detail::simple_allocator, Allocator)>	// [unord.req.general]/248.2
unordered_map(std::initializer_list<hamon::pair<Key, T>>, Allocator)
->unordered_map<Key, T, hamon::hash<Key>, hamon::equal_to<Key>, Allocator>;

#endif

template <typename Key, typename T, typename Hash, typename Pred, typename Alloc>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool	// nodiscard as an extension
operator==(
	unordered_map<Key, T, Hash, Pred, Alloc> const& a,
	unordered_map<Key, T, Hash, Pred, Alloc> const& b)
{
	// [unord.req.general]/242

	if (a.size() != b.size())
	{
		return false;
	}

	for (auto i = a.begin(); i != a.end(); ++i)
	{
		auto j = b.find(i->first);
		if (j == b.end() || !(*i == *j))
		{
			return false;
		}
	}

	return true;
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename Key, typename T, typename Hash, typename Pred, typename Alloc>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool	// nodiscard as an extension
operator!=(
	unordered_map<Key, T, Hash, Pred, Alloc> const& a,
	unordered_map<Key, T, Hash, Pred, Alloc> const& b)
{
	return !(a == b);
}
#endif

template <typename Key, typename T, typename Hash, typename Pred, typename Alloc>
HAMON_CXX14_CONSTEXPR void
swap(
	unordered_map<Key, T, Hash, Pred, Alloc>& x,
	unordered_map<Key, T, Hash, Pred, Alloc>& y)
	HAMON_NOEXCEPT_IF_EXPR(x.swap(y))
{
	// [container.reqmts]/51
	x.swap(y);
}

}	// namespace hamon

#endif

#endif // HAMON_UNORDERED_MAP_UNORDERED_MAP_HPP
