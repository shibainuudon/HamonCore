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
		auto zv = hamon::views::zip(c.keys, c.values);
		hamon::ranges::sort(zv, this->value_comp());
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

		// TODO
		// assert is_sorted(c.keys, this->compare)
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
	constexpr explicit
	flat_multimap(Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	constexpr
	flat_multimap(
		key_compare const& comp,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	constexpr
	flat_multimap(
		key_container_type const& key_cont,
		mapped_container_type const& mapped_cont,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
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
		>::value>>
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
		>::value>>
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
		>::value>>
	constexpr
	flat_multimap(
		flat_multimap const&,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
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
		>::value>>
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
		>::value>>
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
		>::value>>
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
		>::value>>
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
		>::value>>
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
		>::value>>
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
		>::value>>
	constexpr
	flat_multimap(
		std::initializer_list<value_type> il,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	constexpr
	flat_multimap(
		std::initializer_list<value_type> il,
		key_compare const& comp,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	constexpr
	flat_multimap(
		hamon::sorted_equivalent_t,
		std::initializer_list<value_type> il,
		Alloc const& a);

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			std::uses_allocator<key_container_type, Alloc>,
			std::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	constexpr
	flat_multimap(
		hamon::sorted_equivalent_t,
		std::initializer_list<value_type> il,
		key_compare const& comp,
		Alloc const& a);

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
	emplace(Args&&... args);

	template <typename... Args,
		typename = hamon::enable_if_t<
			hamon::is_constructible<hamon::pair<key_type, mapped_type>, Args...>::value>>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_hint(const_iterator position, Args&&... args);

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
//		if constexpr (hamon::sized_sentinel_for<InputIterator, InputIterator>)
//		{
//			__reserve(last - first);
//		}

//		__append_sort_merge</*WasSorted = */ false>(hamon::move(first), hamon::move(last));

//		auto __on_failure     = std::__make_exception_guard([&]() noexcept { clear() /* noexcept */; });

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

		using Diff = hamon::ranges::range_difference_t<decltype(zv)>;

		// Then, sorts the range of newly inserted elements with respect to value_comp()
		hamon::ranges::sort(zv.begin() + static_cast<Diff>(old_size), zv.end(), this->value_comp());

		// merges the resulting sorted range and the sorted range of pre-existing elements into a single sorted range
		hamon::ranges::inplace_merge(zv.begin(), zv.begin() + static_cast<Diff>(old_size), zv.end(), this->value_comp());
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void
	insert(hamon::sorted_equivalent_t, InputIterator first, InputIterator last);
//	{
//		if constexpr (hamon::sized_sentinel_for<InputIterator, InputIterator>)
//		{
////			__reserve(last - first);
//		}
//
//		__append_sort_merge</*WasSorted = */ true>(hamon::move(first), hamon::move(last));
//	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	HAMON_CXX14_CONSTEXPR void
	insert_range(R&& rg);
	//{
	//	if constexpr (hamon::ranges::sized_range<R>)
	//	{
	//		//__reserve(hamon::ranges::size(rg));
	//	}

	//	__append_sort_merge</*WasSorted = */ false>(ranges::begin(rg), ranges::end(rg));
	//}

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
		// TODO
//		auto __guard = std::__make_scope_guard([&]() noexcept { clear() /* noexcept */; });
		auto ret = hamon::move(c);
		return ret;
	}

	HAMON_CXX14_CONSTEXPR void
	replace(key_container_type&& key_cont, mapped_container_type&& mapped_cont)
	{
		// TODO
//		_LIBCPP_ASSERT_VALID_INPUT_RANGE(__key_cont.size() == __mapped_cont.size(), "flat_multimap keys and mapped containers have different size");
//		_LIBCPP_ASSERT_SEMANTIC_REQUIREMENT(__is_sorted(__key_cont), "Key container is not sorted");
//		auto __guard         = std::__make_exception_guard([&]() noexcept { clear() /* noexcept */; });
		c.keys = hamon::move(key_cont);
		c.values = hamon::move(mapped_cont);
//		__guard.__complete();
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(iterator position)
	{
		// TODO
//		auto on_failure  = std::__make_exception_guard([&]() noexcept { clear() /* noexcept */; });
		auto key_iter    = c.keys.erase(position.m_key_iter);
		auto mapped_iter = c.values.erase(position.m_mapped_iter);
//		on_failure.__complete();
		return iterator(hamon::move(key_iter), hamon::move(mapped_iter));
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator position)
	{
		// TODO
//		auto on_failure  = std::__make_exception_guard([&]() noexcept { clear() /* noexcept */; });
		auto key_iter    = c.keys.erase(position.m_key_iter);
		auto mapped_iter = c.values.erase(position.m_mapped_iter);
//		on_failure.__complete();
		return iterator(hamon::move(key_iter), hamon::move(mapped_iter));
	}

	HAMON_CXX14_CONSTEXPR size_type
	erase(key_type const& x)
	{
		auto r = this->equal_range(x);
		auto n = r.second - r.first;
		this->erase(r.first, r.second);
		return n;
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
		HAMON_CXX14_CONSTEXPR size_type
	erase(K&& x)
	{
		auto r = this->equal_range(hamon::forward<K>(x));
		auto n = r.second - r.first;
		this->erase(r.first, r.second);
		return n;
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator first, const_iterator last)
	{
		// TODO
//		auto on_failure = std::__make_exception_guard([&]() noexcept { clear() /* noexcept */; });
		auto key_iter     = c.keys.erase(first.m_key_iter, last.m_key_iter);
		auto mapped_iter  = c.values.erase(first.m_mapped_iter, last.m_mapped_iter);
//		on_failure.__complete();
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
		auto it = this->lower_bound(x);
		if (it == this->end() || this->compare(x, it->first))
		{
			return this->end();
		}
		return it;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR const_iterator
	find(key_type const& x) const
	{
		auto it = this->lower_bound(x);
		if (it == this->end() || this->compare(x, it->first))
		{
			return this->end();
		}
		return it;
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	find(K const& x)
	{
		auto it = this->lower_bound(x);
		if (it == this->end() || this->compare(x, it->first))
		{
			return this->end();
		}
		return it;
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR const_iterator
	find(K const& x) const
	{
		auto it = this->lower_bound(x);
		if (it == this->end() || this->compare(x, it->first))
		{
			return this->end();
		}
		return it;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR size_type
	count(key_type const& x) const
	{
		auto r = this->equal_range(x);
		return r.second - r.first;
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR size_type
	count(K const& x) const
	{
		auto r = this->equal_range(x);
		return r.second - r.first;
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
		return binary_search<iterator>(*this, hamon::ranges::lower_bound, x);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr const_iterator
	lower_bound(key_type const& x) const
	{
		return binary_search<const_iterator>(*this, hamon::ranges::lower_bound, x);
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	lower_bound(K const& x)
	{
		return binary_search<iterator>(*this, hamon::ranges::lower_bound, x);
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	constexpr const_iterator
	lower_bound(K const& x) const
	{
		return binary_search<const_iterator>(*this, hamon::ranges::lower_bound, x);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	upper_bound(key_type const& x)
	{
		return binary_search<iterator>(*this, hamon::ranges::upper_bound, x);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr const_iterator
	upper_bound(key_type const& x) const
	{
		return binary_search<const_iterator>(*this, hamon::ranges::upper_bound, x);
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	upper_bound(K const& x)
	{
		return binary_search<iterator>(*this, hamon::ranges::upper_bound, x);
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	constexpr const_iterator
	upper_bound(K const& x) const
	{
		return binary_search<const_iterator>(*this, hamon::ranges::upper_bound, x);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, iterator>
	equal_range(key_type const& x);
	//{
	//	return equal_range_impl<iterator>(*this, x);
	//}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr hamon::pair<const_iterator, const_iterator>
	equal_range(key_type const& x) const;
	//{
	//	return equal_range_impl<const_iterator>(*this, x);
	//}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, iterator>
	equal_range(K const& x);
	//{
	//	return equal_range_impl<iterator>(*this, x);
	//}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	constexpr hamon::pair<const_iterator, const_iterator>
	equal_range(K const& x) const;
	//{
	//	return equal_range_impl<const_iterator>(*this, x);
	//}

	HAMON_NODISCARD	// nodiscard as an extension
	constexpr friend bool
	operator==(flat_multimap const& x, flat_multimap const& y)
	{
		return hamon::ranges::equal(x, y);
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_NODISCARD	// nodiscard as an extension
	constexpr friend
	hamon::detail::synth_three_way_result<value_type>
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
