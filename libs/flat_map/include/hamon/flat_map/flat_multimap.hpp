/**
 *	@file	flat_multimap.hpp
 *
 *	@brief	flat_multimap の定義
 */

#ifndef HAMON_FLAT_MAP_FLAT_MULTIMAP_HPP
#define HAMON_FLAT_MAP_FLAT_MULTIMAP_HPP

#include <hamon/flat_map/flat_multimap_fwd.hpp>
#include <hamon/flat_map/config.hpp>
#include <hamon/container/sorted_equivalent.hpp>

#if !defined(HAMON_USE_STD_FLAT_MAP)

#include <hamon/flat_map/detail/flat_map_iterator.hpp>
#include <hamon/algorithm/lexicographical_compare.hpp>
#include <hamon/algorithm/lexicographical_compare_three_way.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/algorithm/ranges/equal_range.hpp>
#include <hamon/algorithm/ranges/inplace_merge.hpp>
#include <hamon/algorithm/ranges/is_sorted.hpp>
#include <hamon/algorithm/ranges/lower_bound.hpp>
#include <hamon/algorithm/ranges/sort.hpp>
#include <hamon/algorithm/ranges/upper_bound.hpp>
#include <hamon/algorithm/remove_if.hpp>
#include <hamon/compare/detail/synth_three_way.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/swap.hpp>
#include <hamon/container/detail/alloc_rebind.hpp>
#include <hamon/container/detail/container_compatible_range.hpp>
#include <hamon/container/detail/has_is_transparent.hpp>
#include <hamon/container/detail/iter_key_type.hpp>
#include <hamon/container/detail/iter_mapped_type.hpp>
#include <hamon/container/detail/range_key_type.hpp>
#include <hamon/container/detail/range_mapped_type.hpp>
#include <hamon/container/detail/reserve_append_size.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/detail/exception_guard.hpp>
#include <hamon/detail/scope_guard.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/detail/cpp17_random_access_iterator.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/iterator/ranges/prev.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/pair.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory/detail/simple_allocator.hpp>
#include <hamon/memory/make_obj_using_allocator.hpp>
#include <hamon/memory/uses_allocator.hpp>
#include <hamon/ranges/adaptors/drop_view.hpp>
#include <hamon/ranges/adaptors/zip_view.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/vector.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

namespace hamon
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

template <typename Key, typename T, typename Compare, typename KeyContainer, typename MappedContainer>
class flat_multimap
{
private:
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

		HAMON_CXX11_CONSTEXPR
		value_compare(key_compare c)
			: comp(c)
		{}

	public:
		HAMON_CXX11_CONSTEXPR bool
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
	HAMON_CXX11_CONSTEXPR
	flat_multimap() HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_default_constructible<KeyContainer>::value &&
		hamon::is_nothrow_default_constructible<MappedContainer>::value &&
		hamon::is_nothrow_default_constructible<Compare>::value)
		: c(), compare()
	{}

	flat_multimap(flat_multimap const&) = default;

	HAMON_CXX14_CONSTEXPR
	flat_multimap(flat_multimap&& other) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<KeyContainer>::value &&
		hamon::is_nothrow_move_constructible<MappedContainer>::value &&
		hamon::is_nothrow_move_constructible<Compare>::value)
		: c(hamon::move(other).extract())
		, compare(hamon::move(other.compare))
	{}

	HAMON_CXX11_CONSTEXPR explicit
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
		this->insert(hamon::move(first), hamon::move(last));
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
		this->insert(hamon::sorted_equivalent, hamon::move(first), hamon::move(last));
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
			hamon::uses_allocator<key_container_type, Alloc>,
			hamon::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR explicit
	flat_multimap(Alloc const& a)
		: flat_multimap(key_compare(), a)
	{}

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			hamon::uses_allocator<key_container_type, Alloc>,
			hamon::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(key_compare const& comp, Alloc const& a)
		: c{hamon::make_obj_using_allocator<key_container_type>(a),
			hamon::make_obj_using_allocator<mapped_container_type>(a)}
		, compare(comp)
	{}

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			hamon::uses_allocator<key_container_type, Alloc>,
			hamon::uses_allocator<mapped_container_type, Alloc>
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
			hamon::uses_allocator<key_container_type, Alloc>,
			hamon::uses_allocator<mapped_container_type, Alloc>
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
			hamon::uses_allocator<key_container_type, Alloc>,
			hamon::uses_allocator<mapped_container_type, Alloc>
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
			hamon::uses_allocator<key_container_type, Alloc>,
			hamon::uses_allocator<mapped_container_type, Alloc>
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
			hamon::uses_allocator<key_container_type, Alloc>,
			hamon::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(flat_multimap const& x, Alloc const& a)
		: c{hamon::make_obj_using_allocator<key_container_type>(a, x.c.keys),
			hamon::make_obj_using_allocator<mapped_container_type>(a, x.c.values)}
		, compare(x.compare)
	{}

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			hamon::uses_allocator<key_container_type, Alloc>,
			hamon::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(flat_multimap&& x, Alloc const& a)
		: c(hamon::move(x).extract_using_allocator(a))
		, compare(hamon::move(x.compare))
	{}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			hamon::uses_allocator<key_container_type, Alloc>,
			hamon::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		InputIterator first,
		InputIterator last,
		Alloc const& a)
		: flat_multimap(hamon::move(first), hamon::move(last), key_compare(), a)
	{}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			hamon::uses_allocator<key_container_type, Alloc>,
			hamon::uses_allocator<mapped_container_type, Alloc>
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
		this->insert(hamon::move(first), hamon::move(last));
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			hamon::uses_allocator<key_container_type, Alloc>,
			hamon::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		hamon::sorted_equivalent_t,
		InputIterator first,
		InputIterator last,
		Alloc const& a)
		: flat_multimap(hamon::sorted_equivalent, hamon::move(first), hamon::move(last), key_compare(), a)
	{}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			hamon::uses_allocator<key_container_type, Alloc>,
			hamon::uses_allocator<mapped_container_type, Alloc>
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
		this->insert(hamon::sorted_equivalent, hamon::move(first), hamon::move(last));
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R),
		typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			hamon::uses_allocator<key_container_type, Alloc>,
			hamon::uses_allocator<mapped_container_type, Alloc>
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
			hamon::uses_allocator<key_container_type, Alloc>,
			hamon::uses_allocator<mapped_container_type, Alloc>
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
			hamon::uses_allocator<key_container_type, Alloc>,
			hamon::uses_allocator<mapped_container_type, Alloc>
		>::value>>
	HAMON_CXX14_CONSTEXPR
	flat_multimap(
		std::initializer_list<value_type> il,
		Alloc const& a)
		: flat_multimap(il.begin(), il.end(), a)
	{}

	template <typename Alloc,
		typename = hamon::enable_if_t<hamon::conjunction<		// [flat.multimap.cons.alloc]/1
			hamon::uses_allocator<key_container_type, Alloc>,
			hamon::uses_allocator<mapped_container_type, Alloc>
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
			hamon::uses_allocator<key_container_type, Alloc>,
			hamon::uses_allocator<mapped_container_type, Alloc>
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
			hamon::uses_allocator<key_container_type, Alloc>,
			hamon::uses_allocator<mapped_container_type, Alloc>
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

	HAMON_CXX14_CONSTEXPR flat_multimap&
	operator=(flat_multimap const& other)
	{
		auto gd = hamon::detail::make_exception_guard([&]() noexcept { clear(); });
		this->c       = other.c;
		this->compare = other.compare;
		gd.complete();
		return *this;
	}

	HAMON_CXX14_CONSTEXPR flat_multimap&
	operator=(flat_multimap&& other) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_assignable<KeyContainer>::value &&
		hamon::is_nothrow_move_assignable<MappedContainer>::value &&
		hamon::is_nothrow_move_assignable<Compare>::value)
	{
		auto gd = hamon::detail::make_exception_guard([&]() noexcept { clear(); });
		this->c       = hamon::move(other).extract();
		this->compare = hamon::move(other.compare);
		gd.complete();
		return *this;
	}

	// iterators
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	begin() HAMON_NOEXCEPT
	{
		return iterator(c.keys.begin(), c.values.begin());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	begin() const HAMON_NOEXCEPT
	{
		return const_iterator(c.keys.begin(), c.values.begin());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	end() HAMON_NOEXCEPT
	{
		return iterator(c.keys.end(), c.values.end());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	end() const HAMON_NOEXCEPT
	{
		return const_iterator(c.keys.end(), c.values.end());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR reverse_iterator
	rbegin() HAMON_NOEXCEPT
	{
		return reverse_iterator(this->end());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reverse_iterator
	rbegin() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(this->end());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR reverse_iterator
	rend() HAMON_NOEXCEPT
	{
		return reverse_iterator(this->begin());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reverse_iterator
	rend() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(this->begin());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	cbegin() const HAMON_NOEXCEPT
	{
		return this->begin();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	cend() const HAMON_NOEXCEPT
	{
		return this->end();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reverse_iterator
	crbegin() const HAMON_NOEXCEPT
	{
		return this->rbegin();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reverse_iterator
	crend() const HAMON_NOEXCEPT
	{
		return this->rend();
	}

	// capacity
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool
	empty() const HAMON_NOEXCEPT
	{
		return c.keys.empty();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type
	size() const HAMON_NOEXCEPT
	{
		return c.keys.size();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type
	max_size() const HAMON_NOEXCEPT
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
		return this->try_emplace_hint_impl(hamon::move(position), hamon::move(t.first), hamon::move(t.second));
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
		return this->emplace_hint(hamon::move(position), x);
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, value_type&& x)
	{
		return this->emplace_hint(hamon::move(position), hamon::move(x));
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
		return this->emplace_hint(hamon::move(position), hamon::forward<P>(x));
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
		return hamon::move(c);
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
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare),
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::negation<hamon::is_convertible<K&&, const_iterator>>,
			hamon::negation<hamon::is_convertible<K&&, iterator>>
		>::value>>
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
	swap(flat_multimap& y) HAMON_NOEXCEPT
	{
		hamon::ranges::swap(compare, y.compare);
		hamon::ranges::swap(c.keys, y.c.keys);
		hamon::ranges::swap(c.values, y.c.values);
	}

	HAMON_CXX14_CONSTEXPR void
	clear() HAMON_NOEXCEPT
	{
		c.keys.clear();
		c.values.clear();
	}

	// observers
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR key_compare
	key_comp() const
	{
		return this->compare;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR value_compare
	value_comp() const
	{
		return value_compare(this->compare);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR key_container_type const&
	keys() const HAMON_NOEXCEPT
	{
		return c.keys;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR mapped_container_type const&
	values() const HAMON_NOEXCEPT
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
	HAMON_CXX11_CONSTEXPR bool
	contains(key_type const& x) const
	{
		return this->find(x) != this->end();
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool
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
	HAMON_CXX11_CONSTEXPR const_iterator
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
	HAMON_CXX11_CONSTEXPR const_iterator
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
	HAMON_CXX11_CONSTEXPR const_iterator
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
	HAMON_CXX11_CONSTEXPR const_iterator
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
	HAMON_CXX11_CONSTEXPR hamon::pair<const_iterator, const_iterator>
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
	HAMON_CXX11_CONSTEXPR hamon::pair<const_iterator, const_iterator>
	equal_range(K const& x) const
	{
		return equal_range_impl(*this, x);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR friend bool
	operator==(flat_multimap const& x, flat_multimap const& y)
	{
		return hamon::ranges::equal(x, y);
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR friend auto
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
	HAMON_CXX11_CONSTEXPR friend bool
	operator!=(flat_multimap const& x, flat_multimap const& y)
	{
		return !(x == y);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR friend bool
	operator<(flat_multimap const& x, flat_multimap const& y)
	{
		return hamon::lexicographical_compare(
			x.begin(), x.end(),
			y.begin(), y.end());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR friend bool
	operator>(flat_multimap const& x, flat_multimap const& y)
	{
		return y < x;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR friend bool
	operator<=(flat_multimap const& x, flat_multimap const& y)
	{
		return !(x > y);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR friend bool
	operator>=(flat_multimap const& x, flat_multimap const& y)
	{
		return !(x < y);
	}
#endif

	HAMON_CXX14_CONSTEXPR friend void
	swap(flat_multimap& x, flat_multimap& y) HAMON_NOEXCEPT
	{
		x.swap(y);
	}

private:
	template <typename Self, typename KeyIter>
	static HAMON_CXX14_CONSTEXPR typename hamon::ranges::iterator_t<Self>::mapped_iterator
	corresponding_mapped_it(Self&& self, KeyIter&& key_iter)
	{
		using Difference = hamon::ranges::range_difference_t<mapped_container_type>;
		return self.c.values.begin() +
			static_cast<Difference>(hamon::ranges::distance(self.c.keys.begin(), key_iter));
	}

	template <typename Range>
	HAMON_CXX14_CONSTEXPR bool
	is_sorted(Range const& rg) const
	{
		return hamon::ranges::is_sorted(rg, this->compare);
	}

	HAMON_CXX14_CONSTEXPR void
	sort()
	{
		// [flat.multimap.cons]/1
		auto zv = hamon::views::zip(c.keys, c.values);
		hamon::ranges::sort(zv, this->value_comp());

		// ### flat_map, flat_multimap のソートは安定ソートなのか？
		// 
		// C++ の規格書を見ても単にソートされると書いてあるだけで安定ソートとは書いていない。
		// libcxx の実装も ranges::sort を呼び出している。(stable_sort ではない)
		// (ただし、ソートアルゴリズムの関係なのか実際には安定ソートになっており、それに依存したテストを書いてしまっている)
		//
		// * 安定ソートのほうが計算量もしくはメモリ使用量が大きい
		// * 安定ソートにしてしまうとそれに依存したコードを書きがち
		// という点を踏まえ、安定ソートは使わない。
		//
		// 規格上、安定ソートであることがわかったら(もしくは変更されたら)、安定ソートを使う。
		// 2025/7/25
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
		auto gd = hamon::detail::make_exception_guard([&]() noexcept { clear(); });
		using difference_t = hamon::ranges::range_difference_t<decltype(c.keys)>;
		auto const m = static_cast<difference_t>(c.keys.size());
		this->append(first, last);
		HAMON_ASSERT(this->is_sorted(c.keys | hamon::views::drop(m)));
		auto zv = hamon::views::zip(c.keys, c.values);
		hamon::ranges::inplace_merge(zv, zv.begin() + m, this->value_comp());
		gd.complete();
	}

	template <typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void
	append_sort_merge(Iterator first, Sentinel last)
	{
		auto gd = hamon::detail::make_exception_guard([&]() noexcept { clear(); });
		using difference_t = hamon::ranges::range_difference_t<decltype(c.keys)>;
		auto const m = static_cast<difference_t>(c.keys.size());
		this->append(first, last);
		auto zv = hamon::views::zip(c.keys, c.values);
		hamon::ranges::sort(zv | hamon::views::drop(m), this->value_comp());
		hamon::ranges::inplace_merge(zv, zv.begin() + m, this->value_comp());
		gd.complete();
	}

	template <typename K, typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	try_emplace_impl(K&& k, Args&&... args)
	{
		auto key_iter = hamon::ranges::upper_bound(c.keys, k, this->compare);
		auto mapped_iter = corresponding_mapped_it(*this, key_iter);
		return this->emplace_exact_pos(
			hamon::move(key_iter), hamon::move(mapped_iter),
			hamon::forward<K>(k), hamon::forward<Args>(args)...);
	}

	template <typename K, typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	try_emplace_hint_impl(const_iterator hint, K&& k, Args&&... args)
	{
		auto prev_larger  = hint != cbegin() && this->compare(k, hamon::ranges::prev(hint)->first);
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
			hamon::forward<K>(k), hamon::forward<Args>(args)...);
	}

	template <typename KeyIter, typename MappedIter, typename K, typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_exact_pos(KeyIter&& key_iter, MappedIter&& mapped_iter, K&& k, Args&&... args)
	{
		auto gd = hamon::detail::make_exception_guard([&]() noexcept { clear(); });
		key_iter = this->c.keys.emplace(key_iter, hamon::forward<K>(k));
		mapped_iter = this->c.values.emplace(mapped_iter, hamon::forward<Args>(args)...);
		gd.complete();

		return iterator(hamon::move(key_iter), hamon::move(mapped_iter));
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

	template <typename Allocator>
	HAMON_CXX14_CONSTEXPR containers
	extract_using_allocator(Allocator const& alloc) &&
	{
		auto gd = hamon::detail::make_scope_guard([&]() noexcept { clear(); });
		return containers
		{
			hamon::make_obj_using_allocator<key_container_type>(alloc, hamon::move(c.keys)),
			hamon::make_obj_using_allocator<mapped_container_type>(alloc, hamon::move(c.values))
		};
	}

private:
	containers c;

#if !(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 130000))
	HAMON_NO_UNIQUE_ADDRESS	// gcc12 で no_unique_address を指定すると constexpr にならなくなってしまう 
#endif
	key_compare compare;
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
		hamon::uses_allocator<KeyContainer, Allocator>,
		hamon::uses_allocator<MappedContainer, Allocator>
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
		hamon::uses_allocator<KeyContainer, Allocator>,
		hamon::uses_allocator<MappedContainer, Allocator>,
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
		hamon::uses_allocator<KeyContainer, Allocator>,
		hamon::uses_allocator<MappedContainer, Allocator>
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
		hamon::uses_allocator<KeyContainer, Allocator>,
		hamon::uses_allocator<MappedContainer, Allocator>,
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
	InputIterator, InputIterator,
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
	InputIterator, InputIterator,
	Compare = Compare())
->flat_multimap<
	hamon::detail::iter_key_type<InputIterator>,
	hamon::detail::iter_mapped_type<InputIterator>,
	Compare>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Key = hamon::detail::range_key_type<R>,
	typename Compare = hamon::less<Key>,
	typename Allocator = hamon::allocator<hamon::byte>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>,
		hamon::detail::simple_allocator_t<Allocator>
	>::value>,
	typename T = hamon::detail::range_mapped_type<R>
>
flat_multimap(
	hamon::from_range_t, R&&,
	Compare = Compare(),
	Allocator = Allocator())
->flat_multimap<
	Key, T, Compare,
	hamon::vector<Key, hamon::detail::alloc_rebind<Allocator, Key>>,
	hamon::vector<T, hamon::detail::alloc_rebind<Allocator, T>>>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::detail::simple_allocator_t<Allocator>
	>::value>,
	typename Key = hamon::detail::range_key_type<R>,
	typename T = hamon::detail::range_mapped_type<R>
>
flat_multimap(hamon::from_range_t, R&&, Allocator)
->flat_multimap<
	Key, T, hamon::less<Key>,
	hamon::vector<Key, hamon::detail::alloc_rebind<Allocator, Key>>,
	hamon::vector<T, hamon::detail::alloc_rebind<Allocator, T>>>;

template <
	typename Key, typename T, typename Compare = hamon::less<Key>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>
	>::value>
>
flat_multimap(
	std::initializer_list<hamon::pair<Key, T>>,
	Compare = Compare())
->flat_multimap<Key, T, Compare>;

template <
	typename Key, typename T, typename Compare = hamon::less<Key>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>
	>::value>
>
flat_multimap(
	hamon::sorted_equivalent_t,
	std::initializer_list<hamon::pair<Key, T>>,
	Compare = Compare())
->flat_multimap<Key, T, Compare>;

#endif

// [flat.multimap.erasure], erasure for flat_multimap
template <typename Key, typename T, typename Compare, typename KeyContainer, typename MappedContainer, typename Predicate>
HAMON_CXX14_CONSTEXPR typename flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>::size_type
erase_if(flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>& c, Predicate pred)
{
	auto original_size = c.size();
	//for (auto i = c.cbegin(); i != c.cend(); )
	//{
	//	if (pred(*i))
	//	{
	//		i = c.erase(i);
	//	}
	//	else
	//	{
	//		++i;
	//	}
	//}
	{
		using Reference      = hamon::pair<Key&,       T&>;
		using ConstReference = hamon::pair<Key const&, T const&>;

		struct F
		{
			Predicate m_pred;

			HAMON_CXX14_CONSTEXPR bool
			operator()(Reference t) const
			{
				return m_pred(ConstReference(t.first, t.second));
			}
		};

		auto cont = hamon::move(c).extract();
		auto zv = hamon::views::zip(cont.keys, cont.values);
		auto it = hamon::remove_if(zv.begin(), zv.end(), F{pred});
		auto offset = it - zv.begin();
		cont.keys.erase(cont.keys.begin() + offset, cont.keys.end());
		cont.values.erase(cont.values.begin() + offset, cont.values.end());
		c.replace(hamon::move(cont.keys), hamon::move(cont.values));
	}
	return original_size - c.size();
}

HAMON_WARNING_POP()

}	// namespace hamon

#include <memory>
#include <type_traits>

namespace std
{

template <typename Key, typename T, typename Compare, typename KeyContainer, typename MappedContainer, typename Allocator>
struct uses_allocator<hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>, Allocator>
	: public std::integral_constant<bool,
		std::uses_allocator<KeyContainer, Allocator>::value &&
		std::uses_allocator<MappedContainer, Allocator>::value>
{};

}	// namespace std

#endif

#endif // HAMON_FLAT_MAP_FLAT_MULTIMAP_HPP
