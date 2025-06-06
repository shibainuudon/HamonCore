/**
 *	@file	flat_map.hpp
 *
 *	@brief	flat_map の定義
 */

#ifndef HAMON_FLAT_MAP_FLAT_MAP_HPP
#define HAMON_FLAT_MAP_FLAT_MAP_HPP

#include <hamon/flat_map/flat_map_fwd.hpp>
#include <hamon/flat_map/sorted_unique.hpp>
#include <hamon/flat_map/config.hpp>

#if !defined(HAMON_USE_STD_FLAT_MAP)

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
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/pair.hpp>
#include <hamon/memory.hpp>
#include <hamon/ranges.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
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
struct flat_map_iterator;

}	// namespace detail

template <
	typename Key,
	typename T,
	typename Compare = hamon::less<Key>,
	typename KeyContainer = hamon::vector<Key>,
	typename MappedContainer = hamon::vector<T>
>
class flat_map
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
	using iterator               = hamon::detail::flat_map_iterator<KeyContainer, MappedContainer, false>;
	using const_iterator         = hamon::detail::flat_map_iterator<KeyContainer, MappedContainer, true>;
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

	// [flat.map.cons], constructors
	constexpr
	flat_map()
		: flat_map(key_compare())
	{}

	constexpr explicit
	flat_map(key_compare const& comp)
		: c(), compare(comp)
	{}

	constexpr
	flat_map(
		key_container_type key_cont,
		mapped_container_type mapped_cont,
		key_compare const& comp = key_compare())
		// [flat.map.cons]/1
		: c{hamon::move(key_cont), hamon::move(mapped_cont)}
		, compare(comp)
	{
		// [flat.map.cons]/1
		auto zv = hamon::views::zip(c.keys, c.values);
		hamon::ranges::sort(zv, this->value_comp());
		auto it = hamon::ranges::unique(zv, key_equiv(this->compare)).begin();
		auto dist = hamon::distance(zv.begin(), it);
		c.keys.erase(c.keys.begin() + dist, c.keys.end());
		c.values.erase(c.values.begin() + dist, c.values.end());
	}

	constexpr
	flat_map(
		hamon::sorted_unique_t,
		key_container_type key_cont,
		mapped_container_type mapped_cont,
		key_compare const& comp = key_compare())
		// [flat.map.cons]/3
		: c{hamon::move(key_cont), hamon::move(mapped_cont)}
		, compare(comp)
	{
		// TODO
		// assert is_sorted_and_unique(c.keys)
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	constexpr
	flat_map(
		InputIterator first,
		InputIterator last,
		key_compare const& comp = key_compare())
		: c(), compare(comp)
	{
		insert(first, last);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	constexpr
	flat_map(
		hamon::sorted_unique_t,
		InputIterator first,
		InputIterator last,
		key_compare const& comp = key_compare())
		: c(), compare(comp)
	{
		insert(hamon::sorted_unique, first, last);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	constexpr
	flat_map(hamon::from_range_t, R&& rg)
		: flat_map(hamon::from_range, hamon::forward<R>(rg), key_compare())
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	constexpr
	flat_map(hamon::from_range_t, R&& rg, key_compare const& comp)
		: flat_map(comp)
	{
		insert_range(hamon::forward<R>(rg));
	}

	constexpr
	flat_map(
		std::initializer_list<value_type> il,
		key_compare const& comp = key_compare())
		: flat_map(il.begin(), il.end(), comp)
	{}

	constexpr
	flat_map(
		hamon::sorted_unique_t,
		std::initializer_list<value_type> il,
		key_compare const& comp = key_compare())
		: flat_map(hamon::sorted_unique, il.begin(), il.end(), comp)
	{}

	// [flat.map.cons.alloc], constructors with allocators

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.map.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr explicit
	flat_map(Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.map.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_map(key_compare const& comp, Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.map.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_map(
		key_container_type const& key_cont,
		mapped_container_type const& mapped_cont,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.map.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_map(
		key_container_type const& key_cont,
		mapped_container_type const& mapped_cont,
		key_compare const& comp,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.map.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_map(
		hamon::sorted_unique_t,
		key_container_type const& key_cont,
		mapped_container_type const& mapped_cont,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.map.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_map(
		hamon::sorted_unique_t,
		key_container_type const& key_cont,
		mapped_container_type const& mapped_cont,
		key_compare const& comp,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.map.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_map(flat_map const&, Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.map.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_map(flat_map&&, Alloc const& a);

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.map.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_map(
		InputIterator first,
		InputIterator last,
		Alloc const& a);

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.map.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_map(
		InputIterator first,
		InputIterator last,
		key_compare const& comp,
		Alloc const& a);

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.map.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_map(
		hamon::sorted_unique_t,
		InputIterator first,
		InputIterator last,
		Alloc const& a);

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.map.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_map(
		hamon::sorted_unique_t,
		InputIterator first,
		InputIterator last,
		key_compare const& comp,
		Alloc const& a);

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.map.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_map(
		hamon::from_range_t, R&& rg,
		Alloc const& a);

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.map.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_map(
		hamon::from_range_t, R&& rg,
		key_compare const& comp,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.map.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_map(
		std::initializer_list<value_type> il,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.map.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_map(
		std::initializer_list<value_type> il,
		key_compare const& comp,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.map.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_map(
		hamon::sorted_unique_t,
		std::initializer_list<value_type> il,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.map.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>
	>
	constexpr
	flat_map(
		hamon::sorted_unique_t,
		std::initializer_list<value_type> il,
		key_compare const& comp,
		Alloc const& a);

	constexpr flat_map&
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

	// [flat.map.capacity], capacity
	constexpr bool
	empty() const noexcept;

	constexpr size_type
	size() const noexcept
	{
		// [flat.map.capacity]/1
		return c.keys.size();
	}

	constexpr size_type
	max_size() const noexcept
	{
		// [flat.map.capacity]/1
		return hamon::min<size_type>(c.keys.max_size(), c.values.max_size());
	}

	// [flat.map.access], element access
	constexpr mapped_type&
	operator[](key_type const& x)
	{
		// [flat.map.access]/1
		return try_emplace(x).first->second;
	}

	constexpr mapped_type&
	operator[](key_type&& x)
	{
		// [flat.map.access]/2
		return try_emplace(hamon::move(x)).first->second;
	}

	template <typename K,
		// [flat.map.access]/3
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)
	>
	constexpr mapped_type&
	operator[](K&& x)
	{
		// [flat.map.access]/4
		return try_emplace(hamon::forward<K>(x)).first->second;
	}

	constexpr mapped_type&
	at(key_type const& x)
	{
		auto it = this->find(x);
		if (it == this->end())
		{
			// [flat.map.access]/6
			hamon::detail::throw_out_of_range("flat_map::at(key_type const&)");
		}

		// [flat.map.access]/5
		return it->second;
	}

	constexpr mapped_type const&
	at(key_type const& x) const
	{
		auto it = this->find(x);
		if (it == this->end())
		{
			// [flat.map.access]/6
			hamon::detail::throw_out_of_range("flat_map::at(key_type const&) const");
		}

		// [flat.map.access]/5
		return it->second;
	}

	template <typename K,
		// [flat.map.access]/8
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)
	>
	constexpr mapped_type&
	at(K const& x)
	{
		auto it = this->find(x);
		if (it == this->end())
		{
			// [flat.map.access]/11
			hamon::detail::throw_out_of_range("flat_map::at(K const&)");
		}

		// [flat.map.access]/10
		return it->second;
	}

	template <typename K,
		// [flat.map.access]/8
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)
	>
	constexpr mapped_type const&
	at(K const& x) const
	{
		auto it = this->find(x);
		if (it == this->end())
		{
			// [flat.map.access]/11
			hamon::detail::throw_out_of_range("flat_map::at(K const&) const");
		}

		// [flat.map.access]/10
		return it->second;
	}

	// [flat.map.modifiers], modifiers
	template <typename... Args,
		typename = hamon::enable_if_t<	// [flat.map.modifiers]/1
			hamon::is_constructible<hamon::pair<key_type, mapped_type>, Args...>::value
		>
	>
	constexpr hamon::pair<iterator, bool>
	emplace(Args&&... args)
	{
		// [flat.map.modifiers]/2

		// TODO: strong exception safety guarantee

		hamon::pair<key_type, mapped_type> t(hamon::forward<Args>(args)...);

		auto key_it = hamon::ranges::upper_bound(c.keys, t.first, this->compare);
		auto value_it = c.values.begin() + hamon::distance(c.keys.begin(), key_it);

		bool inserted = false;
		if (!c.keys.contains(t.first))
		{
			c.keys.insert(key_it, hamon::move(t.first));
			c.values.insert(value_it, hamon::move(t.second));
			inserted = true;
		}

		return hamon::pair<iterator, bool>{
			iterator{hamon::move(key_it), hamon::move(value_it)},
			inserted};
	}

	template <typename... Args>
	constexpr iterator
	emplace_hint(const_iterator position, Args&&... args);

	constexpr hamon::pair<iterator, bool>
	insert(value_type const& x)
	{
		return emplace(x);
	}

	constexpr hamon::pair<iterator, bool>
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

	template <typename P,
		typename = hamon::enable_if_t<	// [flat.map.modifiers]/4
			hamon::is_constructible<hamon::pair<key_type, mapped_type>, P>::value
		>
	>
	constexpr hamon::pair<iterator, bool>
	insert(P&& x)
	{
		// [flat.map.modifiers]/5
		return emplace(hamon::forward<P>(x));
	}

	template <typename P,
		typename = hamon::enable_if_t<	// [flat.map.modifiers]/4
			hamon::is_constructible<hamon::pair<key_type, mapped_type>, P>::value
		>
	>
	constexpr iterator
	insert(const_iterator position, P&& x)
	{
		// [flat.map.modifiers]/5
		return emplace_hint(position, hamon::forward<P>(x));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	constexpr void
	insert(InputIterator first, InputIterator last)
	{
		// [flat.map.modifiers]/6

		// TODO: strong exception safety guarantee

		// TODO
		//if constexpr (hamon::sized_sentinel_for<InputIterator, InputIterator>)
		//{
		//	__reserve(last - first);
		//}

		auto const old_size = c.keys.size();

		// Adds elements to c
		for (; first != last; ++first)
		{
			value_type value = *first;
			c.keys.insert(c.keys.end(), hamon::move(value.first));
			c.values.insert(c.values.end(), hamon::move(value.second));
		}

		// TODO
		//if (c.keys.size() == old_size)
		//{
		//	return;
		//}

		auto zv = hamon::views::zip(c.keys, c.values);

		// Then, sorts the range of newly inserted elements with respect to value_comp()
		hamon::ranges::sort(zv.begin() + old_size, zv.end(), this->value_comp());

		// merges the resulting sorted range and the sorted range of pre-existing elements into a single sorted range
		hamon::ranges::inplace_merge(zv.begin(), zv.begin() + old_size, zv.end(), this->value_comp());

		// and finally erases the duplicate elements
		auto it = hamon::ranges::unique(zv, key_equiv(this->compare)).begin();
		auto dist = hamon::distance(zv.begin(), it);
		c.keys.erase(c.keys.begin() + dist, c.keys.end());
		c.values.erase(c.values.begin() + dist, c.values.end());
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	constexpr void
	insert(hamon::sorted_unique_t, InputIterator first, InputIterator last)
	{
		// [flat.map.modifiers]/9

		// TODO: strong exception safety guarantee

		// TODO
		//if constexpr (hamon::sized_sentinel_for<InputIterator, InputIterator>)
		//{
		//	__reserve(last - first);
		//}

		// TODO
		// assert is_sorted_and_unique(first, last)

		auto const old_size = c.keys.size();

		// Adds elements to c
		for (; first != last; ++first)
		{
			value_type value = *first;
			c.keys.insert(c.keys.end(), hamon::move(value.first));
			c.values.insert(c.values.end(), hamon::move(value.second));
		}

		auto zv = hamon::views::zip(c.keys, c.values);

		// Then, merges the sorted range of newly added elements and the sorted range of pre-existing elements
		// into a single sorted range
		hamon::ranges::inplace_merge(zv.begin(), zv.begin() + old_size, zv.end(), this->value_comp());

		// and finally erases the duplicate elements
		auto it = hamon::ranges::unique(zv, key_equiv(this->compare)).begin();
		auto dist = hamon::distance(zv.begin(), it);
		c.keys.erase(c.keys.begin() + dist, c.keys.end());
		c.values.erase(c.values.begin() + dist, c.values.end());
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	constexpr void
	insert_range(R&& rg)
	{
		// [flat.map.modifiers]/12

		// TODO: strong exception safety guarantee

		// TODO
		//if constexpr (hamon::ranges::sized_range<R>)
		//{
		//	__reserve(hamon::ranges::size(rg));
		//}

		auto const old_size = c.keys.size();

		// Adds elements to c
		for (const auto& e : rg)
		{
			c.keys.insert(c.keys.end(), e.first);
			c.values.insert(c.values.end(), e.second);
		}

		auto zv = hamon::views::zip(c.keys, c.values);

		// Then, sorts the range of newly inserted elements with respect to value_comp()
		hamon::ranges::sort(zv.begin() + old_size, zv.end(), this->value_comp());

		// merges the resulting sorted range and the sorted range of pre-existing elements into a single sorted range
		hamon::ranges::inplace_merge(zv.begin(), zv.begin() + old_size, zv.end(), this->value_comp());

		// and finally erases the duplicate elements
		auto it = hamon::ranges::unique(zv, key_equiv(this->compare)).begin();
		auto dist = hamon::distance(zv.begin(), it);
		c.keys.erase(c.keys.begin() + dist, c.keys.end());
		c.values.erase(c.values.begin() + dist, c.values.end());
	}

	constexpr void
	insert(std::initializer_list<value_type> il)
	{
		insert(il.begin(), il.end());
	}

	constexpr void
	insert(hamon::sorted_unique_t, std::initializer_list<value_type> il)
	{
		insert(hamon::sorted_unique, il.begin(), il.end());
	}

	constexpr containers
	extract() &&
	{
		// [flat.map.modifiers]/34
		// TODO:
		// *this is emptied, even if the function exits via an exception.

		// [flat.map.modifiers]/35
		hamon::move(c);
	}

	constexpr void
	replace(key_container_type&& key_cont, mapped_container_type&& mapped_cont)
	{
		// [flat.map.modifiers]/36
		// TODO:
		// key_cont.size() == mapped_cont.size() is true,
		// the elements of key_cont are sorted with respect to compare,
		// and key_cont contains no equal elements.

		// [flat.map.modifiers]/37
		c.keys = hamon::move(key_cont);
		c.values = hamon::move(mapped_cont);
	}

	template <typename... Args,
		typename = hamon::enable_if_t<	// [flat.map.modifiers]/15
			hamon::is_constructible<mapped_type, Args...>::value
		>
	>
	constexpr hamon::pair<iterator, bool>
	try_emplace(key_type const& k, Args&&... args)
	{
		// [flat.map.modifiers]/16

		// TODO: strong exception safety guarantee

		auto key_it = hamon::ranges::upper_bound(c.keys, k, this->compare);
		auto value_it = c.values.begin() + hamon::distance(c.keys.begin(), key_it);

		bool inserted = false;
		if (!c.keys.contains(k))
		{
			c.keys.insert(key_it, hamon::forward<decltype(k)>(k));
			c.values.emplace(value_it, hamon::forward<Args>(args)...);
		}

		return hamon::pair<iterator, bool>{
			iterator{hamon::move(key_it), hamon::move(value_it)},
			inserted};
	}

	template <typename... Args,
		typename = hamon::enable_if_t<	// [flat.map.modifiers]/15
			hamon::is_constructible<mapped_type, Args...>::value
		>
	>
	constexpr hamon::pair<iterator, bool>
	try_emplace(key_type&& k, Args&&... args)
	{
		// [flat.map.modifiers]/16

		// TODO: strong exception safety guarantee

		auto key_it = hamon::ranges::upper_bound(c.keys, k, this->compare);
		auto value_it = c.values.begin() + hamon::distance(c.keys.begin(), key_it);

		bool inserted = false;
		if (!c.keys.contains(k))
		{
			c.keys.insert(key_it, hamon::forward<decltype(k)>(k));
			c.values.emplace(value_it, hamon::forward<Args>(args)...);
		}

		return hamon::pair<iterator, bool>{
			iterator{hamon::move(key_it), hamon::move(value_it)},
			inserted};
	}

	template <typename K, typename... Args,
		// [flat.map.modifiers]/19
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare),	// [flat.map.modifiers]/19.1
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_constructible<key_type, K>,							// [flat.map.modifiers]/19.2
			hamon::is_constructible<mapped_type, Args...>,					// [flat.map.modifiers]/19.3
			hamon::negation<hamon::is_convertible<K&&, const_iterator>>,	// [flat.map.modifiers]/19.4
			hamon::negation<hamon::is_convertible<K&&, iterator>>
		>::value>
	>
	constexpr hamon::pair<iterator, bool>
	try_emplace(K&& k, Args&&... args);

	template <typename... Args,
		typename = hamon::enable_if_t<	// [flat.map.modifiers]/15
			hamon::is_constructible<mapped_type, Args...>::value
		>
	>
	constexpr iterator
	try_emplace(const_iterator hint, key_type const& k, Args&&... args);

	template <typename... Args,
		typename = hamon::enable_if_t<	// [flat.map.modifiers]/15
			hamon::is_constructible<mapped_type, Args...>::value
		>
	>
	constexpr iterator
	try_emplace(const_iterator hint, key_type&& k, Args&&... args);

	template <typename K, typename... Args,
		// [flat.map.modifiers]/19
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare),	// [flat.map.modifiers]/19.1
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_constructible<key_type, K>,							// [flat.map.modifiers]/19.2
			hamon::is_constructible<mapped_type, Args...>					// [flat.map.modifiers]/19.3
		>::value>
	>
	constexpr iterator
	try_emplace(const_iterator hint, K&& k, Args&&... args);

	template <typename M,
		// [flat.map.modifiers]/24
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_assignable<mapped_type&, M>,
			hamon::is_constructible<mapped_type, M>
		>::value>>
	constexpr hamon::pair<iterator, bool>
	insert_or_assign(key_type const& k, M&& obj);

	template <typename M,
		// [flat.map.modifiers]/24
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_assignable<mapped_type&, M>,
			hamon::is_constructible<mapped_type, M>
		>::value>>
	constexpr hamon::pair<iterator, bool>
	insert_or_assign(key_type&& k, M&& obj);

	template <typename K, typename M,
		// [flat.map.modifiers]/28
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare),	// [flat.map.modifiers]/28.1
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_constructible<key_type, K>,				// [flat.map.modifiers]/28.2
			hamon::is_assignable<mapped_type&, M>,				// [flat.map.modifiers]/28.3
			hamon::is_constructible<mapped_type, M>				// [flat.map.modifiers]/28.4
		>::value>>
	constexpr hamon::pair<iterator, bool>
	insert_or_assign(K&& k, M&& obj);

	template <typename M,
		// [flat.map.modifiers]/24
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_assignable<mapped_type&, M>,
			hamon::is_constructible<mapped_type, M>
		>::value>>
	constexpr iterator
	insert_or_assign(const_iterator hint, key_type const& k, M&& obj);

	template <typename M,
		// [flat.map.modifiers]/24
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_assignable<mapped_type&, M>,
			hamon::is_constructible<mapped_type, M>
		>::value>>
	constexpr iterator
	insert_or_assign(const_iterator hint, key_type&& k, M&& obj);

	template <typename K, typename M,
		// [flat.map.modifiers]/28
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare),	// [flat.map.modifiers]/28.1
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_constructible<key_type, K>,				// [flat.map.modifiers]/28.2
			hamon::is_assignable<mapped_type&, M>,				// [flat.map.modifiers]/28.3
			hamon::is_constructible<mapped_type, M>				// [flat.map.modifiers]/28.4
		>::value>>
	constexpr iterator
	insert_or_assign(const_iterator hint, K&& k, M&& obj);

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
	swap(flat_map& y) noexcept
	{
		// [flat.map.modifiers]/33
		hamon::ranges::swap(compare, y.compare);
		hamon::ranges::swap(c.keys, y.c.keys);
		hamon::ranges::swap(c.values, y.c.values);
	}

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
	operator==(flat_map const& x, flat_map const& y);

	constexpr friend
	hamon::detail::synth_three_way_result<value_type>
	operator<=>(flat_map const& x, flat_map const& y);

	constexpr friend void
	swap(flat_map& x, flat_map& y) noexcept
	{
		x.swap(y);
	}

private:
	containers c;               // exposition only
	key_compare compare;        // exposition only

	struct key_equiv	// exposition only
	{
		constexpr
		key_equiv(key_compare c)
			: comp(c)
		{}

		constexpr bool
		operator()(const_reference x, const_reference y) const
		{
			return !comp(x.first, y.first) && !comp(y.first, x.first);
		}

		key_compare comp;
	};
};

template <
	class KeyContainer,
	class MappedContainer,
	class Compare = hamon::less<typename KeyContainer::value_type>
>
flat_map(
	KeyContainer,
	MappedContainer,
	Compare = Compare())
->flat_map<
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
flat_map(
	KeyContainer,
	MappedContainer,
	Allocator)
->flat_map<
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
flat_map(
	KeyContainer,
	MappedContainer,
	Compare,
	Allocator)
->flat_map<
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
flat_map(
	hamon::sorted_unique_t,
	KeyContainer,
	MappedContainer,
	Compare = Compare())
->flat_map<
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
flat_map(
	hamon::sorted_unique_t,
	KeyContainer,
	MappedContainer,
	Allocator)
->flat_map<
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
flat_map(
	hamon::sorted_unique_t,
	KeyContainer,
	MappedContainer,
	Compare,
	Allocator)
->flat_map<
	typename KeyContainer::value_type,
	typename MappedContainer::value_type,
	Compare,
	KeyContainer,
	MappedContainer>;

template <
	class InputIterator,
	class Compare = hamon::less<hamon::detail::iter_key_type<InputIterator>>
>
flat_map(
	InputIterator,
	InputIterator,
	Compare = Compare())
->flat_map<
	hamon::detail::iter_key_type<InputIterator>,
	hamon::detail::iter_mapped_type<InputIterator>,
	Compare>;

template <
	class InputIterator,
	class Compare = hamon::less<hamon::detail::iter_key_type<InputIterator>>
>
flat_map(
	hamon::sorted_unique_t,
	InputIterator,
	InputIterator,
	Compare = Compare())
->flat_map<
	hamon::detail::iter_key_type<InputIterator>,
	hamon::detail::iter_mapped_type<InputIterator>,
	Compare>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	class Compare = hamon::less<hamon::detail::range_key_type<R>>,
	class Allocator = hamon::allocator<byte>
>
flat_map(
	hamon::from_range_t, R&&,
	Compare = Compare(),
	Allocator = Allocator())
->flat_map<
	hamon::detail::range_key_type<R>,
	hamon::detail::range_mapped_type<R>,
	Compare,
	hamon::vector<hamon::detail::range_key_type<R>, hamon::detail::alloc_rebind<Allocator, hamon::detail::range_key_type<R>>>,
	hamon::vector<hamon::detail::range_mapped_type<R>, hamon::detail::alloc_rebind<Allocator, hamon::detail::range_mapped_type<R>>>>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	class Allocator
>
flat_map(
	hamon::from_range_t, R&&,
	Allocator)
->flat_map<
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
flat_map(
	std::initializer_list<hamon::pair<Key, T>>,
	Compare = Compare())
->flat_map<
	Key,
	T,
	Compare>;

template <
	class Key,
	class T,
	class Compare = hamon::less<Key>
>
flat_map(
	hamon::sorted_unique_t,
	std::initializer_list<hamon::pair<Key, T>>,
	Compare = Compare())
->flat_map<
	Key,
	T,
	Compare>;

//template <class Key, class T, class Compare, class KeyContainer, class MappedContainer, class Allocator>
//struct uses_allocator<flat_map<Key, T, Compare, KeyContainer, MappedContainer>, Allocator>
//	: hamon::bool_constant<uses_allocator_v<KeyContainer, Allocator> && uses_allocator_v<MappedContainer, Allocator>> {};

// [flat.map.erasure], erasure for flat_map
template <class Key, class T, class Compare, class KeyContainer, class MappedContainer, class Predicate>
constexpr typename flat_map<Key, T, Compare, KeyContainer, MappedContainer>::size_type
erase_if(flat_map<Key, T, Compare, KeyContainer, MappedContainer>& c, Predicate pred);

}	// namespace hamon

#endif

#endif // HAMON_FLAT_MAP_FLAT_MAP_HPP
