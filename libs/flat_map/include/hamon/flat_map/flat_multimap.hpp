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

#include <hamon/flat_map/detail/flat_map_iterator.hpp>
#include <hamon/flat_map/detail/reserve_append_size.hpp>
#include <hamon/algorithm.hpp>
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
#include <hamon/detail/exception_guard.hpp>
#include <hamon/detail/scope_guard.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/detail/cpp17_random_access_iterator.hpp>
#include <hamon/pair.hpp>
#include <hamon/memory.hpp>
#include <hamon/memory/detail/simple_allocator.hpp>
#include <hamon/ranges.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/vector.hpp>
#include <initializer_list>
#include <memory>	// uses_allocator

namespace hamon
{

template <typename Key, typename T, typename Compare, typename KeyContainer, typename MappedContainer>
class flat_multimap
{
	// [flat.multimap.overview]/7
	static_assert(hamon::detail::cpp17_random_access_iterator_t<typename KeyContainer::iterator>::value, "");
	static_assert(noexcept(hamon::declval<KeyContainer>().size()), "");
	static_assert(noexcept(hamon::declval<KeyContainer>().max_size()), "");
	static_assert(hamon::detail::cpp17_random_access_iterator_t<typename MappedContainer::iterator>::value, "");
	static_assert(noexcept(hamon::declval<MappedContainer>().size()), "");
	static_assert(noexcept(hamon::declval<MappedContainer>().max_size()), "");

	// [flat.multimap.overview]/8
	static_assert(hamon::is_same<Key, typename KeyContainer::value_type>::value, "");
	static_assert(hamon::is_same<T, typename MappedContainer::value_type>::value, "");

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
	using iterator               = hamon::detail::flat_map_iterator<flat_multimap, KeyContainer, MappedContainer, false>;
	using const_iterator         = hamon::detail::flat_map_iterator<flat_multimap, KeyContainer, MappedContainer, true>;
	using reverse_iterator       = hamon::reverse_iterator<iterator>;
	using const_reverse_iterator = hamon::reverse_iterator<const_iterator>;
	using key_container_type     = KeyContainer;
	using mapped_container_type  = MappedContainer;

	class value_compare
	{
	private:
		friend flat_multimap;

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

	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		key_container_type key_cont,
		mapped_container_type mapped_cont,
		key_compare const& comp = key_compare())
		// [flat.multimap.cons]/1
		: c{hamon::move(key_cont), hamon::move(mapped_cont)}
		, compare(comp)
	{
		// [flat.multimap.overview]/9
		HAMON_ASSERT(c.keys.size() == c.values.size());

		// [flat.multimap.cons]/1
		this->sort();
	}

	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		hamon::sorted_equivalent_t,
		key_container_type key_cont,
		mapped_container_type mapped_cont,
		key_compare const& comp = key_compare())
		// [flat.multimap.cons]/3
		: c{hamon::move(key_cont), hamon::move(mapped_cont)}
		, compare(comp)
	{
		// [flat.multimap.overview]/9
		HAMON_ASSERT(c.keys.size() == c.values.size());

		// [flat.multimap.overview]/10
		HAMON_ASSERT(this->is_sorted(c.keys));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		InputIterator first,
		InputIterator last,
		key_compare const& comp = key_compare())
		: c(), compare(comp)
	{
		this->insert(first, last);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		hamon::sorted_equivalent_t,
		InputIterator first,
		InputIterator last,
		key_compare const& comp = key_compare())
		: c(), compare(comp)
	{
		this->insert(hamon::sorted_equivalent, first, last);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(hamon::from_range_t, R&& rg)
		: flat_multimap(hamon::from_range, hamon::forward<R>(rg), key_compare())
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(hamon::from_range_t, R&& rg, key_compare const& comp)
		: flat_multimap(comp)
	{
		this->insert_range(hamon::forward<R>(rg));
	}

	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		std::initializer_list<value_type> il,
		key_compare const& comp = key_compare())
		: flat_multimap(il.begin(), il.end(), comp)
	{}

	HAMON_CXX14_CONSTEXPR
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
		>::value>>
	HAMON_CXX14_CONSTEXPR explicit
	flat_multimap(Alloc const& a)
		: flat_multimap(key_compare(), a)
	{}

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(key_compare const& comp, Alloc const& a)
		: c{hamon::make_obj_using_allocator<key_container_type>(a),
			hamon::make_obj_using_allocator<mapped_container_type>(a)}
		, compare(comp)
	{}

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		key_container_type const& key_cont,
		mapped_container_type const& mapped_cont,
		Alloc const& a)
		: flat_multimap(key_cont, mapped_cont, key_compare(), a)
	{}

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		key_container_type const& key_cont,
		mapped_container_type const& mapped_cont,
		key_compare const& comp,
		Alloc const& a)
		: c{hamon::make_obj_using_allocator<key_container_type>(a, key_cont),
			hamon::make_obj_using_allocator<mapped_container_type>(a, mapped_cont)}
		, compare(comp)
	{
		// [flat.multimap.overview]/9
		HAMON_ASSERT(c.keys.size() == c.values.size());

		// [flat.multimap.cons]/1
		this->sort();
	}

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		hamon::sorted_equivalent_t,
		key_container_type const& key_cont,
		mapped_container_type const& mapped_cont,
		Alloc const& a)
		: flat_multimap(hamon::sorted_equivalent, key_cont, mapped_cont, key_compare(), a)
	{}

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		hamon::sorted_equivalent_t,
		key_container_type const& key_cont,
		mapped_container_type const& mapped_cont,
		key_compare const& comp,
		Alloc const& a)
		: c{hamon::make_obj_using_allocator<key_container_type>(a, key_cont),
			hamon::make_obj_using_allocator<mapped_container_type>(a, mapped_cont)}
		, compare(comp)
	{
		// [flat.multimap.overview]/9
		HAMON_ASSERT(c.keys.size() == c.values.size());

		// [flat.multimap.overview]/10
		HAMON_ASSERT(this->is_sorted(c.keys));
	}

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(flat_multimap const& x, Alloc const& a)
		: c{hamon::make_obj_using_allocator<key_container_type>(a, x.c.keys),
			hamon::make_obj_using_allocator<mapped_container_type>(a, x.c.values)}
		, compare(x.compare)
	{}

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX20_CONSTEXPR
	flat_multimap(flat_multimap&& x, Alloc const& a)
#if !defined(HAMON_NO_EXCEPTIONS)
	try
#endif
		: c{hamon::make_obj_using_allocator<key_container_type>(a, hamon::move(x.c.keys)),
			hamon::make_obj_using_allocator<mapped_container_type>(a, hamon::move(x.c.values))}
		, compare(hamon::move(x.compare))
	{
		x.clear();
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	catch (...)
	{
		x.clear();
		throw;
	}
#endif

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		InputIterator first,
		InputIterator last,
		Alloc const& a)
		: flat_multimap(first, last, key_compare(), a)
	{}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		InputIterator first,
		InputIterator last,
		key_compare const& comp,
		Alloc const& a)
		: c{hamon::make_obj_using_allocator<key_container_type>(a),
			hamon::make_obj_using_allocator<mapped_container_type>(a)}
		, compare(comp)
	{
		this->insert(first, last);
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		hamon::sorted_equivalent_t,
		InputIterator first,
		InputIterator last,
		Alloc const& a)
		: flat_multimap(hamon::sorted_equivalent, first, last, key_compare(), a)
	{}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		hamon::sorted_equivalent_t,
		InputIterator first,
		InputIterator last,
		key_compare const& comp,
		Alloc const& a)
		: c{hamon::make_obj_using_allocator<key_container_type>(a),
			hamon::make_obj_using_allocator<mapped_container_type>(a)}
		, compare(comp)
	{
		this->insert(hamon::sorted_equivalent, first, last);
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		hamon::from_range_t, R&& rg,
		Alloc const& a)
		: flat_multimap(hamon::from_range, hamon::forward<R>(rg), key_compare(), a)
	{}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		hamon::from_range_t, R&& rg,
		key_compare const& comp,
		Alloc const& a)
		: c{hamon::make_obj_using_allocator<key_container_type>(a),
			hamon::make_obj_using_allocator<mapped_container_type>(a)}
		, compare(comp)
	{
		this->insert_range(hamon::forward<R>(rg));
	}

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		std::initializer_list<value_type> il,
		Alloc const& a)
		: flat_multimap(il.begin(), il.end(), a)
	{}

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		std::initializer_list<value_type> il,
		key_compare const& comp,
		Alloc const& a)
		: flat_multimap(il.begin(), il.end(), comp, a)
	{}

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		hamon::sorted_equivalent_t,
		std::initializer_list<value_type> il,
		Alloc const& a)
		: flat_multimap(hamon::sorted_equivalent, il.begin(), il.end(), a)
	{}

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		hamon::sorted_equivalent_t,
		std::initializer_list<value_type> il,
		key_compare const& comp,
		Alloc const& a)
		: flat_multimap(hamon::sorted_equivalent, il.begin(), il.end(), comp, a)
	{}

	HAMON_CXX14_CONSTEXPR flat_multimap&
	operator=(std::initializer_list<value_type> il)
	{
		this->clear();
		this->insert(il);
		return *this;
	}

	// iterators
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	begin() noexcept
	{
		return iterator(c.keys.begin(), c.values.begin());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr const_iterator
	begin() const noexcept
	{
		return const_iterator(c.keys.begin(), c.values.begin());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	end() noexcept
	{
		return iterator(c.keys.end(), c.values.end());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr const_iterator
	end() const noexcept
	{
		return const_iterator(c.keys.end(), c.values.end());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR reverse_iterator
	rbegin() noexcept
	{
		return reverse_iterator(this->end());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr const_reverse_iterator
	rbegin() const noexcept
	{
		return const_reverse_iterator(this->end());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR reverse_iterator
	rend() noexcept
	{
		return reverse_iterator(this->begin());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr const_reverse_iterator
	rend() const noexcept
	{
		return const_reverse_iterator(this->begin());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr const_iterator
	cbegin() const noexcept
	{
		return this->begin();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr const_iterator
	cend() const noexcept
	{
		return this->end();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr const_reverse_iterator
	crbegin() const noexcept
	{
		return const_reverse_iterator(this->end());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr const_reverse_iterator
	crend() const noexcept
	{
		return const_reverse_iterator(this->begin());
	}

	// capacity
	HAMON_NODISCARD	// nodiscard as an extension
	constexpr bool
	empty() const noexcept
	{
		return c.keys.empty();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr size_type
	size() const noexcept
	{
		return c.keys.size();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr size_type
	max_size() const noexcept
	{
		return hamon::min<size_type>(c.keys.max_size(), c.values.max_size());
	}

	// modifiers
	template <typename... Args,
		typename = hamon::enable_if_t<
			hamon::is_constructible<hamon::pair<key_type, mapped_type>, Args...>::value>>
	HAMON_CXX14_CONSTEXPR iterator
	emplace(Args&&... args)
	{
		hamon::pair<key_type, mapped_type> t(hamon::forward<Args>(args)...);	// may throw
		return this->try_emplace_impl(hamon::move(t.first), hamon::move(t.second));
	}

	template <typename... Args,
		typename = hamon::enable_if_t<
			hamon::is_constructible<hamon::pair<key_type, mapped_type>, Args...>::value>>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_hint(const_iterator position, Args&&... args)
	{
		hamon::pair<key_type, mapped_type> t(hamon::forward<Args>(args)...);	// may throw
		return this->try_emplace_hint_impl(position, hamon::move(t.first), hamon::move(t.second));
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(value_type const& x)
	{
		return this->emplace(x);
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(value_type&& x)
	{
		return this->emplace(hamon::move(x));
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, value_type const& x)
	{
		return this->emplace_hint(position, x);
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, value_type&& x)
	{
		return this->emplace_hint(position, hamon::move(x));
	}

	template <typename P,
		typename = hamon::enable_if_t<
			hamon::is_constructible<hamon::pair<key_type, mapped_type>, P>::value>>
	HAMON_CXX14_CONSTEXPR iterator
	insert(P&& x)
	{
		return this->emplace(hamon::forward<P>(x));
	}

	template <typename P,
		typename = hamon::enable_if_t<
			hamon::is_constructible<hamon::pair<key_type, mapped_type>, P>::value>>
	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, P&& x)
	{
		return this->emplace_hint(position, hamon::forward<P>(x));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void
	insert(InputIterator first, InputIterator last)
	{
		hamon::detail::reserve_append_size(this->c.keys, first, last);
		hamon::detail::reserve_append_size(this->c.values, first, last);
		this->append_sort_merge(hamon::move(first), hamon::move(last));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void
	insert(hamon::sorted_equivalent_t, InputIterator first, InputIterator last)
	{
		// TODO
		// assert is_sorted(first, last)

		hamon::detail::reserve_append_size(this->c.keys, first, last);
		hamon::detail::reserve_append_size(this->c.values, first, last);
		this->append_merge(hamon::move(first), hamon::move(last));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	HAMON_CXX14_CONSTEXPR void
	insert_range(R&& rg)
	{
		hamon::detail::reserve_append_size(this->c.keys, rg);
		hamon::detail::reserve_append_size(this->c.values, rg);
		this->append_sort_merge(hamon::ranges::begin(rg), hamon::ranges::end(rg));
	}

	HAMON_CXX14_CONSTEXPR void
	insert(std::initializer_list<value_type> il)
	{
		this->insert(il.begin(), il.end());
	}

	HAMON_CXX14_CONSTEXPR void
	insert(hamon::sorted_equivalent_t, std::initializer_list<value_type> il)
	{
		this->insert(hamon::sorted_equivalent, il.begin(), il.end());
	}

	HAMON_CXX14_CONSTEXPR containers
	extract() &&
	{
		auto gd = hamon::detail::make_scope_guard([&]() noexcept { clear(); });
		auto ret = hamon::move(c);
		return ret;
	}

	HAMON_CXX14_CONSTEXPR void
	replace(key_container_type&& key_cont, mapped_container_type&& mapped_cont)
	{
		HAMON_ASSERT(key_cont.size() == mapped_cont.size());
		HAMON_ASSERT(this->is_sorted(key_cont));

		auto gd = hamon::detail::make_exception_guard([&]() noexcept { clear(); });
		c.keys = hamon::move(key_cont);
		c.values = hamon::move(mapped_cont);
		gd.complete();
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(iterator position)
	{
		auto gd = hamon::detail::make_exception_guard([&]() noexcept { clear(); });
		auto key_iter    = c.keys.erase(position.m_key_iter);
		auto mapped_iter = c.values.erase(position.m_mapped_iter);
		gd.complete();
		return iterator(hamon::move(key_iter), hamon::move(mapped_iter));
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator position)
	{
		auto gd = hamon::detail::make_exception_guard([&]() noexcept { clear(); });
		auto key_iter    = c.keys.erase(position.m_key_iter);
		auto mapped_iter = c.values.erase(position.m_mapped_iter);
		gd.complete();
		return iterator(hamon::move(key_iter), hamon::move(mapped_iter));
	}

	HAMON_CXX14_CONSTEXPR size_type
	erase(key_type const& x)
	{
		auto r = this->equal_range(x);
		auto n = r.second - r.first;
		this->erase(r.first, r.second);
		return static_cast<size_type>(n);
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_CXX14_CONSTEXPR size_type
	erase(K&& x)
	{
		auto r = this->equal_range(hamon::forward<K>(x));
		auto n = r.second - r.first;
		this->erase(r.first, r.second);
		return static_cast<size_type>(n);
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator first, const_iterator last)
	{
		auto gd = hamon::detail::make_exception_guard([&]() noexcept { clear(); });
		auto key_iter    = c.keys.erase(first.m_key_iter, last.m_key_iter);
		auto mapped_iter = c.values.erase(first.m_mapped_iter, last.m_mapped_iter);
		gd.complete();
		return iterator(hamon::move(key_iter), hamon::move(mapped_iter));
	}

	HAMON_CXX14_CONSTEXPR void
	swap(flat_multimap& y) noexcept
	{
		hamon::ranges::swap(compare, y.compare);
		hamon::ranges::swap(c.keys, y.c.keys);
		hamon::ranges::swap(c.values, y.c.values);
	}

	HAMON_CXX14_CONSTEXPR void
	clear() noexcept
	{
		c.keys.clear();
		c.values.clear();
	}

	// observers
	HAMON_NODISCARD	// nodiscard as an extension
	constexpr key_compare
	key_comp() const
	{
		return this->compare;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr value_compare
	value_comp() const
	{
		return value_compare(this->compare);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr key_container_type const&
	keys() const noexcept
	{
		return c.keys;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr mapped_container_type const&
	values() const noexcept
	{
		return c.values;
	}

	// map operations
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	find(key_type const& x)
	{
		return find_impl(*this, x);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR const_iterator
	find(key_type const& x) const
	{
		return find_impl(*this, x);
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	find(K const& x)
	{
		return find_impl(*this, x);
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR const_iterator
	find(K const& x) const
	{
		return find_impl(*this, x);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR size_type
	count(key_type const& x) const
	{
		auto r = this->equal_range(x);
		return static_cast<size_type>(r.second - r.first);
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR size_type
	count(K const& x) const
	{
		auto r = this->equal_range(x);
		return static_cast<size_type>(r.second - r.first);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr bool
	contains(key_type const& x) const
	{
		return this->find(x) != this->end();
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	constexpr bool
	contains(K const& x) const
	{
		return this->find(x) != this->end();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	lower_bound(key_type const& x)
	{
		return binary_search(*this, hamon::ranges::lower_bound, x);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr const_iterator
	lower_bound(key_type const& x) const
	{
		return binary_search(*this, hamon::ranges::lower_bound, x);
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	lower_bound(K const& x)
	{
		return binary_search(*this, hamon::ranges::lower_bound, x);
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	constexpr const_iterator
	lower_bound(K const& x) const
	{
		return binary_search(*this, hamon::ranges::lower_bound, x);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	upper_bound(key_type const& x)
	{
		return binary_search(*this, hamon::ranges::upper_bound, x);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr const_iterator
	upper_bound(key_type const& x) const
	{
		return binary_search(*this, hamon::ranges::upper_bound, x);
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	upper_bound(K const& x)
	{
		return binary_search(*this, hamon::ranges::upper_bound, x);
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	constexpr const_iterator
	upper_bound(K const& x) const
	{
		return binary_search(*this, hamon::ranges::upper_bound, x);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, iterator>
	equal_range(key_type const& x)
	{
		return equal_range_impl(*this, x);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr hamon::pair<const_iterator, const_iterator>
	equal_range(key_type const& x) const
	{
		return equal_range_impl(*this, x);
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, iterator>
	equal_range(K const& x)
	{
		return equal_range_impl(*this, x);
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	constexpr hamon::pair<const_iterator, const_iterator>
	equal_range(K const& x) const
	{
		return equal_range_impl(*this, x);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr friend bool
	operator==(flat_multimap const& x, flat_multimap const& y)
	{
		return hamon::ranges::equal(x, y);
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_NODISCARD	// nodiscard as an extension
	constexpr friend auto
//	hamon::detail::synth_three_way_result<value_type>
	operator<=>(flat_multimap const& x, flat_multimap const& y)
	{
		return hamon::lexicographical_compare_three_way(
			x.begin(), x.end(),
			y.begin(), y.end(),
			hamon::detail::synth_three_way);
	}
#else
	HAMON_NODISCARD	// nodiscard as an extension
	constexpr friend bool
	operator!=(flat_multimap const& x, flat_multimap const& y)
	{
		return !(x == y);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr friend bool
	operator<(flat_multimap const& x, flat_multimap const& y)
	{
		return hamon::lexicographical_compare(
			x.begin(), x.end(),
			y.begin(), y.end());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr friend bool
	operator>(flat_multimap const& x, flat_multimap const& y)
	{
		return y < x;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr friend bool
	operator<=(flat_multimap const& x, flat_multimap const& y)
	{
		return !(x > y);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr friend bool
	operator>=(flat_multimap const& x, flat_multimap const& y)
	{
		return !(x < y);
	}
#endif

	HAMON_CXX14_CONSTEXPR friend void
	swap(flat_multimap& x, flat_multimap& y) noexcept
	{
		x.swap(y);
	}

private:
	template <typename K, typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	try_emplace_impl(K&& k, Args&&... args)
	{
		auto key_iter = hamon::ranges::upper_bound(c.keys, k, this->compare);
		auto mapped_iter = corresponding_mapped_it(*this, key_iter);
		return this->emplace_exact_pos(
			hamon::move(key_iter), hamon::move(mapped_iter),
			hamon::move(k), hamon::forward<Args>(args)...);
	}

	template <typename K, typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	try_emplace_hint_impl(const_iterator hint, K&& k, Args&&... args)
	{
		auto prev_larger  = hint != cbegin() && this->compare(k, (hint - 1)->first);
		auto next_smaller = hint != cend() && this->compare(hint->first, k);

		auto key_iter = this->c.keys.begin() + (hint - this->cbegin());

		if (HAMON_LIKELY(!prev_larger && !next_smaller))
		{
			// hint correct, just use exact hint iterators
		}
		else if (prev_larger && !next_smaller)
		{
			key_iter = hamon::upper_bound(this->c.keys.begin(), key_iter, k, this->compare);
		}
		else
		{
			key_iter = hamon::lower_bound(key_iter, this->c.keys.end(), k, this->compare);
		}

		auto mapped_iter = corresponding_mapped_it(*this, key_iter);

		return this->emplace_exact_pos(
			hamon::move(key_iter), hamon::move(mapped_iter),
			hamon::move(k), hamon::forward<Args>(args)...);
	}

	template <typename KeyIter, typename MappedIter, typename K, typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_exact_pos(KeyIter&& key_iter, MappedIter&& mapped_iter, K&& k, Args&&... args)
	{
		//auto __on_key_failed = hamon::detail::make_exception_guard([&]() noexcept {
		//	using _KeyContainer = typename _Map::key_container_type;
		//	if constexpr (__container_traits<_KeyContainer>::__emplacement_has_strong_exception_safety_guarantee)
		//	{
		//		// Nothing to roll back!
		//	}
		//	else
		//	{
		//		// we need to clear both because we don't know the state of our keys anymore
		//		__map.clear();
		//	}
		//});
		key_iter = this->c.keys.emplace(key_iter, hamon::forward<K>(k));
		//__on_key_failed.complete();

//		auto __on_value_failed = hamon::detail::make_exception_guard([&]() noexcept {
//			using _MappedContainer = typename _Map::mapped_container_type;
//			if constexpr (!__container_traits<_MappedContainer>::__emplacement_has_strong_exception_safety_guarantee)
//			{
//				// we need to clear both because we don't know the state of our values anymore
//				__map.clear();
//			}
//			else
//			{
//				// In this case, we know the values are just like before we attempted emplacement,
//				// and we also know that the keys have been emplaced successfully. Just roll back the keys.
//#  if _LIBCPP_HAS_EXCEPTIONS
//				try
//				{
//#  endif // _LIBCPP_HAS_EXCEPTIONS
//					__map.c.keys.erase(key_iter);
//#  if _LIBCPP_HAS_EXCEPTIONS
//				}
//				catch (...)
//				{
//					// Now things are funky for real. We're failing to rollback the keys.
//					// Just give up and clear the whole thing.
//					//
//					// Also, swallow the exception that happened during the rollback and let the
//					// original value-emplacement exception propagate normally.
//					__map.clear();
//				}
//#  endif // _LIBCPP_HAS_EXCEPTIONS
//			}
//		});
		mapped_iter = this->c.values.emplace(mapped_iter, hamon::forward<Args>(args)...);
//		__on_value_failed.complete();

		return iterator(hamon::move(key_iter), hamon::move(mapped_iter));
	}

	HAMON_CXX14_CONSTEXPR bool
	is_sorted(key_container_type const& key_cont) const
	{
		return hamon::ranges::is_sorted(key_cont, this->compare);
	}

	HAMON_CXX14_CONSTEXPR void
	sort()
	{
		// [flat.multimap.cons]/1
		auto zv = hamon::views::zip(c.keys, c.values);
		hamon::ranges::sort(zv, this->value_comp());
	}

	template <typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void
	append(Iterator first, Sentinel last)
	{
		for (; first != last; ++first)
		{
			value_type value = *first;
			c.keys.emplace(c.keys.end(), hamon::move(value.first));
			c.values.emplace(c.values.end(), hamon::move(value.second));
		}
	}

	template <typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void
	append_merge(Iterator first, Sentinel last)
	{
		// TODO: strong exception safety guarantee

		auto const old_size = c.keys.size();
		this->append(first, last);
		auto zv = hamon::views::zip(c.keys, c.values);
		auto const middle_offset = static_cast<hamon::ranges::range_difference_t<decltype(zv)>>(old_size);
		hamon::ranges::inplace_merge(zv, zv.begin() + middle_offset, this->value_comp());
	}

	template <typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void
	append_sort_merge(Iterator first, Sentinel last)
	{
		// TODO: strong exception safety guarantee

		auto const old_size = c.keys.size();
		this->append(first, last);
		auto zv = hamon::views::zip(c.keys, c.values);
		auto const middle_offset = static_cast<hamon::ranges::range_difference_t<decltype(zv)>>(old_size);
		hamon::ranges::sort(zv | hamon::views::drop(middle_offset), this->value_comp());
		hamon::ranges::inplace_merge(zv, zv.begin() + middle_offset, this->value_comp());
	}

	template <typename Self, typename KeyIter>
	static HAMON_CXX14_CONSTEXPR typename hamon::ranges::iterator_t<Self>::mapped_iterator
	corresponding_mapped_it(Self&& self, KeyIter&& key_iter)
	{
		using Difference = hamon::ranges::range_difference_t<mapped_container_type>;
		return self.c.values.begin() +
			static_cast<Difference>(hamon::ranges::distance(self.c.keys.begin(), key_iter));
	}

	template <typename Self, typename K, typename It = hamon::ranges::iterator_t<Self>>
	static HAMON_CXX14_CONSTEXPR It
	find_impl(Self&& self, K const& x)
	{
		auto it = self.lower_bound(x);
		if (it == self.end() || self.compare(x, it->first))
		{
			return self.end();
		}
		return it;
	}

	template <typename Self, typename F, typename K, typename It = hamon::ranges::iterator_t<Self>>
	static HAMON_CXX14_CONSTEXPR It
	binary_search(Self&& self, F search_fn, K const& x)
	{
		auto key_iter = search_fn(self.c.keys, x, self.compare);
		auto mapped_iter = corresponding_mapped_it(self, key_iter);
		return It(hamon::move(key_iter), hamon::move(mapped_iter));
	}

	template <typename Self, typename K, typename It = hamon::ranges::iterator_t<Self>>
	static HAMON_CXX14_CONSTEXPR hamon::pair<It, It>
	equal_range_impl(Self&& self, K const& k)
	{
		auto ret = hamon::ranges::equal_range(self.c.keys, k, self.compare);

		return hamon::pair<It, It>
		{
			It(ret.begin(), corresponding_mapped_it(self, ret.begin())),
			It(ret.end(), corresponding_mapped_it(self, ret.end()))
		};
	}

private:
	containers c;               // exposition only
	key_compare compare;        // exposition only
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <
	typename KeyContainer,
	typename MappedContainer,
	typename Compare = hamon::less<typename KeyContainer::value_type>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<KeyContainer>>,
		hamon::negation<hamon::detail::simple_allocator_t<MappedContainer>>,
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>,
		hamon::is_invocable<Compare const&,
			typename KeyContainer::value_type const&,
			typename KeyContainer::value_type const&>
	>::value>
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
	typename KeyContainer,
	typename MappedContainer,
	typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<KeyContainer>>,
		hamon::negation<hamon::detail::simple_allocator_t<MappedContainer>>,
		std::uses_allocator<KeyContainer, Allocator>,
		std::uses_allocator<MappedContainer, Allocator>
	>::value>
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
	typename KeyContainer,
	typename MappedContainer,
	typename Compare,
	typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<KeyContainer>>,
		hamon::negation<hamon::detail::simple_allocator_t<MappedContainer>>,
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>,
		std::uses_allocator<KeyContainer, Allocator>,
		std::uses_allocator<MappedContainer, Allocator>,
		hamon::is_invocable<Compare const&,
			typename KeyContainer::value_type const&,
			typename KeyContainer::value_type const&>
	>::value>
>
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
	typename KeyContainer,
	typename MappedContainer,
	typename Compare = hamon::less<typename KeyContainer::value_type>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<KeyContainer>>,
		hamon::negation<hamon::detail::simple_allocator_t<MappedContainer>>,
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>,
		hamon::is_invocable<Compare const&,
			typename KeyContainer::value_type const&,
			typename KeyContainer::value_type const&>
	>::value>
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
	typename KeyContainer,
	typename MappedContainer,
	typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<KeyContainer>>,
		hamon::negation<hamon::detail::simple_allocator_t<MappedContainer>>,
		std::uses_allocator<KeyContainer, Allocator>,
		std::uses_allocator<MappedContainer, Allocator>
	>::value>
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
	typename KeyContainer,
	typename MappedContainer,
	typename Compare,
	typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<KeyContainer>>,
		hamon::negation<hamon::detail::simple_allocator_t<MappedContainer>>,
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>,
		std::uses_allocator<KeyContainer, Allocator>,
		std::uses_allocator<MappedContainer, Allocator>,
		hamon::is_invocable<Compare const&,
			typename KeyContainer::value_type const&,
			typename KeyContainer::value_type const&>
	>::value>
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
	typename InputIterator,
	typename Compare = hamon::less<hamon::detail::iter_key_type<InputIterator>>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::detail::cpp17_input_iterator_t<InputIterator>,
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>
	>::value>
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
	typename InputIterator,
	typename Compare = hamon::less<hamon::detail::iter_key_type<InputIterator>>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::detail::cpp17_input_iterator_t<InputIterator>,
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>
	>::value>
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
	typename Compare = hamon::less<hamon::detail::range_key_type<R>>,
	typename Allocator = hamon::allocator<hamon::byte>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>,
		hamon::detail::simple_allocator_t<Allocator>
	>::value>
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
	typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::detail::simple_allocator_t<Allocator>
	>::value>
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
	typename Key,
	typename T,
	typename Compare = hamon::less<Key>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>
	>::value>
>
flat_multimap(
	std::initializer_list<hamon::pair<Key, T>>,
	Compare = Compare())
->flat_multimap<
	Key,
	T,
	Compare>;

template <
	typename Key,
	typename T,
	typename Compare = hamon::less<Key>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>
	>::value>
>
flat_multimap(
	hamon::sorted_equivalent_t,
	std::initializer_list<hamon::pair<Key, T>>,
	Compare = Compare())
->flat_multimap<
	Key,
	T,
	Compare>;

#endif

// [flat.multimap.erasure], erasure for flat_multimap
template <typename Key, typename T, typename Compare, typename KeyContainer, typename MappedContainer, typename Predicate>
HAMON_CXX14_CONSTEXPR typename flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>::size_type
erase_if(flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>& c, Predicate pred);

}	// namespace hamon

namespace std
{

template <typename Key, typename T, typename Compare, typename KeyContainer, typename MappedContainer, typename Allocator>
struct uses_allocator<hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>, Allocator>
	: hamon::bool_constant<
		std::uses_allocator<KeyContainer, Allocator>::value &&
		std::uses_allocator<MappedContainer, Allocator>::value>
{};

}	// namespace std

#endif

#endif // HAMON_FLAT_MAP_FLAT_MULTIMAP_HPP
