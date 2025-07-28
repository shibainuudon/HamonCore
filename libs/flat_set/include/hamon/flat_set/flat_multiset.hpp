/**
 *	@file	flat_multiset.hpp
 *
 *	@brief	flat_multiset の定義
 */

#ifndef HAMON_FLAT_SET_FLAT_MULTISET_HPP
#define HAMON_FLAT_SET_FLAT_MULTISET_HPP

#include <hamon/flat_set/flat_multiset_fwd.hpp>
#include <hamon/flat_set/config.hpp>
#include <hamon/container/sorted_equivalent.hpp>

#if !defined(HAMON_USE_STD_FLAT_SET)

#include <hamon/flat_set/detail/flat_set_iterator.hpp>
#include <hamon/algorithm/lexicographical_compare_three_way.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/algorithm/ranges/equal_range.hpp>
#include <hamon/algorithm/ranges/inplace_merge.hpp>
#include <hamon/algorithm/ranges/is_sorted.hpp>
#include <hamon/algorithm/ranges/lexicographical_compare.hpp>
#include <hamon/algorithm/ranges/lower_bound.hpp>
#include <hamon/algorithm/ranges/sort.hpp>
#include <hamon/algorithm/ranges/upper_bound.hpp>
#include <hamon/algorithm/remove_if.hpp>
#include <hamon/compare/detail/synth_three_way.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/swap.hpp>
#include <hamon/container/detail/alloc_rebind.hpp>
#include <hamon/container/detail/container_compatible_range.hpp>
#include <hamon/container/detail/has_is_transparent.hpp>
#include <hamon/container/detail/iter_value_type.hpp>
#include <hamon/container/detail/reserve_append_size.hpp>
#include <hamon/detail/exception_guard.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/detail/scope_guard.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/ranges/prev.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory/detail/simple_allocator.hpp>
#include <hamon/memory/make_obj_using_allocator.hpp>
#include <hamon/memory/uses_allocator.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/ranges/adaptors/drop_view.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/as_const.hpp>
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

// 23.6.12 Class template flat_multiset[flat.multiset]

template <typename Key, typename Compare, typename KeyContainer>
class flat_multiset
{
public:
	// types
	using key_type                  = Key;
	using value_type                = Key;
	using key_compare               = Compare;
	using value_compare             = Compare;
	using reference                 = value_type&;
	using const_reference           = value_type const&;
	using size_type                 = typename KeyContainer::size_type;
	using difference_type           = typename KeyContainer::difference_type;
	using iterator                  = hamon::detail::flat_set_iterator<flat_multiset, KeyContainer>;
	using const_iterator            = hamon::detail::flat_set_iterator<flat_multiset, KeyContainer>;
	using reverse_iterator          = hamon::reverse_iterator<iterator>;
	using const_reverse_iterator    = hamon::reverse_iterator<const_iterator>;
	using container_type            = KeyContainer;

	// [flat.multiset.cons], constructors
	HAMON_CXX11_CONSTEXPR
	flat_multiset() HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_default_constructible<KeyContainer>::value &&
		hamon::is_nothrow_default_constructible<Compare>::value)
		: c(), compare()
	{}

	flat_multiset(flat_multiset const&) = default;

	HAMON_CXX14_CONSTEXPR
	flat_multiset(flat_multiset&& other) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<KeyContainer>::value &&
		hamon::is_nothrow_move_constructible<Compare>::value)
		: c(hamon::move(other).extract())
		, compare(hamon::move(other.compare))
	{}

	HAMON_CXX14_CONSTEXPR explicit
	flat_multiset(key_compare const& comp)
		: c(), compare(comp)
	{}

	HAMON_CXX14_CONSTEXPR explicit
	flat_multiset(container_type cont, key_compare const& comp = key_compare())
		: c(hamon::move(cont)), compare(comp)
	{
		// [flat.multiset.cons]/1
		this->sort();
	}

	HAMON_CXX14_CONSTEXPR
	flat_multiset(hamon::sorted_equivalent_t, container_type cont, key_compare const& comp = key_compare())
		: c(hamon::move(cont)), compare(comp)
	{
		// [flat.multiset.overview]/9
		HAMON_ASSERT(this->is_sorted(c));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	flat_multiset(InputIterator first, InputIterator last, key_compare const& comp = key_compare())
		: c(), compare(comp)
	{
		this->insert(hamon::move(first), hamon::move(last));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	flat_multiset(hamon::sorted_equivalent_t, InputIterator first, InputIterator last, key_compare const& comp = key_compare())
		: c(), compare(comp)
	{
		this->insert(hamon::sorted_equivalent, hamon::move(first), hamon::move(last));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	HAMON_CXX14_CONSTEXPR
	flat_multiset(hamon::from_range_t, R&& rg)
		: flat_multiset(hamon::from_range, hamon::forward<R>(rg), key_compare())
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	HAMON_CXX14_CONSTEXPR
	flat_multiset(hamon::from_range_t, R&& rg, key_compare const& comp)
		: flat_multiset(comp)
	{
		this->insert_range(hamon::forward<R>(rg));
	}

	HAMON_CXX14_CONSTEXPR
	flat_multiset(std::initializer_list<value_type> il, key_compare const& comp = key_compare())
		: flat_multiset(il.begin(), il.end(), comp)
	{}

	HAMON_CXX14_CONSTEXPR
	flat_multiset(hamon::sorted_equivalent_t, std::initializer_list<value_type> il, key_compare const& comp = key_compare())
		: flat_multiset(hamon::sorted_equivalent, il.begin(), il.end(), comp)
	{}

	// [flat.multiset.cons.alloc], constructors with allocators

	template <typename Alloc,
		typename = hamon::enable_if_t<
			hamon::uses_allocator<container_type, Alloc>::value>>		// [flat.set.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR explicit
	flat_multiset(Alloc const& a)
		: flat_multiset(key_compare(), a)
	{}

	template <typename Alloc,
		typename = hamon::enable_if_t<
			hamon::uses_allocator<container_type, Alloc>::value>>		// [flat.set.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	flat_multiset(key_compare const& comp, Alloc const& a)
		: c(hamon::make_obj_using_allocator<container_type>(a))
		, compare(comp)
	{}

	template <typename Alloc,
		typename = hamon::enable_if_t<
			hamon::uses_allocator<container_type, Alloc>::value>>		// [flat.set.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	flat_multiset(container_type const& cont, Alloc const& a)
		: flat_multiset(cont, key_compare(), a)
	{}

	template <typename Alloc,
		typename = hamon::enable_if_t<
			hamon::uses_allocator<container_type, Alloc>::value>>		// [flat.set.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	flat_multiset(container_type const& cont, key_compare const& comp, Alloc const& a)
		: c(hamon::make_obj_using_allocator<container_type>(a, cont))
		, compare(comp)
	{
		this->sort();
	}

	template <typename Alloc,
		typename = hamon::enable_if_t<
			hamon::uses_allocator<container_type, Alloc>::value>>		// [flat.set.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	flat_multiset(hamon::sorted_equivalent_t, container_type const& cont, Alloc const& a)
		: flat_multiset(hamon::sorted_equivalent, cont, key_compare(), a)
	{}

	template <typename Alloc,
		typename = hamon::enable_if_t<
			hamon::uses_allocator<container_type, Alloc>::value>>		// [flat.set.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	flat_multiset(hamon::sorted_equivalent_t, container_type const& cont, key_compare const& comp, Alloc const& a)
		: c(hamon::make_obj_using_allocator<container_type>(a, cont))
		, compare(comp)
	{
		// [flat.multiset.overview]/9
		HAMON_ASSERT(this->is_sorted(c));
	}

	template <typename Alloc,
		typename = hamon::enable_if_t<
			hamon::uses_allocator<container_type, Alloc>::value>>		// [flat.set.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	flat_multiset(flat_multiset const& x, Alloc const& a)
		: c(hamon::make_obj_using_allocator<container_type>(a, x.c))
		, compare(x.compare)
	{}

	template <typename Alloc,
		typename = hamon::enable_if_t<
			hamon::uses_allocator<container_type, Alloc>::value>>		// [flat.set.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	flat_multiset(flat_multiset&& x, Alloc const& a)
		: c(hamon::move(x).extract_using_allocator(a))
		, compare(hamon::move(x.compare))
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc,
		typename = hamon::enable_if_t<
			hamon::uses_allocator<container_type, Alloc>::value>>		// [flat.set.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	flat_multiset(InputIterator first, InputIterator last, Alloc const& a)
		: flat_multiset(hamon::move(first), hamon::move(last), key_compare(), a)
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc,
		typename = hamon::enable_if_t<
			hamon::uses_allocator<container_type, Alloc>::value>>		// [flat.set.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	flat_multiset(InputIterator first, InputIterator last, key_compare const& comp, Alloc const& a)
		: c(hamon::make_obj_using_allocator<container_type>(a))
		, compare(comp)
	{
		this->insert(hamon::move(first), hamon::move(last));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc,
		typename = hamon::enable_if_t<
			hamon::uses_allocator<container_type, Alloc>::value>>		// [flat.set.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	flat_multiset(hamon::sorted_equivalent_t, InputIterator first, InputIterator last, Alloc const& a)
		: flat_multiset(hamon::sorted_equivalent, hamon::move(first), hamon::move(last), key_compare(), a)
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc,
		typename = hamon::enable_if_t<
			hamon::uses_allocator<container_type, Alloc>::value>>		// [flat.set.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	flat_multiset(hamon::sorted_equivalent_t, InputIterator first, InputIterator last, key_compare const& comp, Alloc const& a)
		: c(hamon::make_obj_using_allocator<container_type>(a))
		, compare(comp)
	{
		this->insert(hamon::sorted_equivalent, hamon::move(first), hamon::move(last));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R),
		typename Alloc,
		typename = hamon::enable_if_t<
			hamon::uses_allocator<container_type, Alloc>::value>>		// [flat.set.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	flat_multiset(hamon::from_range_t, R&& rg, Alloc const& a)
		: flat_multiset(hamon::from_range, hamon::forward<R>(rg), key_compare(), a)
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R),
		typename Alloc,
		typename = hamon::enable_if_t<
			hamon::uses_allocator<container_type, Alloc>::value>>		// [flat.set.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	flat_multiset(hamon::from_range_t, R&& rg, key_compare const& comp, Alloc const& a)
		: c(hamon::make_obj_using_allocator<container_type>(a))
		, compare(comp)
	{
		this->insert_range(hamon::forward<R>(rg));
	}

	template <typename Alloc,
		typename = hamon::enable_if_t<
			hamon::uses_allocator<container_type, Alloc>::value>>		// [flat.set.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	flat_multiset(std::initializer_list<value_type> il, Alloc const& a)
		: flat_multiset(il.begin(), il.end(), a)
	{}

	template <typename Alloc,
		typename = hamon::enable_if_t<
			hamon::uses_allocator<container_type, Alloc>::value>>		// [flat.set.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	flat_multiset(std::initializer_list<value_type> il, key_compare const& comp, Alloc const& a)
		: flat_multiset(il.begin(), il.end(), comp, a)
	{}

	template <typename Alloc,
		typename = hamon::enable_if_t<
			hamon::uses_allocator<container_type, Alloc>::value>>		// [flat.set.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	flat_multiset(hamon::sorted_equivalent_t, std::initializer_list<value_type> il, Alloc const& a)
		: flat_multiset(hamon::sorted_equivalent, il.begin(), il.end(), a)
	{}

	template <typename Alloc,
		typename = hamon::enable_if_t<
			hamon::uses_allocator<container_type, Alloc>::value>>		// [flat.set.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	flat_multiset(hamon::sorted_equivalent_t, std::initializer_list<value_type> il, key_compare const& comp, Alloc const& a)
		: flat_multiset(hamon::sorted_equivalent, il.begin(), il.end(), comp, a)
	{}

	HAMON_CXX14_CONSTEXPR flat_multiset&
	operator=(std::initializer_list<value_type> il)
	{
		this->clear();
		this->insert(il);
		return *this;
	}

	HAMON_CXX14_CONSTEXPR flat_multiset&
	operator=(flat_multiset const& other)
	{
		auto gd = hamon::detail::make_exception_guard([&]() noexcept { clear(); });
		this->c       = other.c;
		this->compare = other.compare;
		gd.complete();
		return *this;
	}

	HAMON_CXX14_CONSTEXPR flat_multiset&
	operator=(flat_multiset&& other) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_assignable<KeyContainer>::value &&
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
		return iterator(hamon::as_const(c).begin());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	begin() const HAMON_NOEXCEPT
	{
		return const_iterator(c.begin());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	end() HAMON_NOEXCEPT
	{
		return iterator(hamon::as_const(c).end());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	end() const HAMON_NOEXCEPT
	{
		return const_iterator(c.end());
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
		return c.empty();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type
	size() const HAMON_NOEXCEPT
	{
		return c.size();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type
	max_size() const HAMON_NOEXCEPT
	{
		return c.max_size();
	}

	// [flat.multiset.modifiers], modifiers
	template <typename... Args,
		typename = hamon::enable_if_t<
			hamon::is_constructible<value_type, Args...>::value>>
	HAMON_CXX14_CONSTEXPR iterator
	emplace(Args&&... args)
	{
		return this->emplace_impl(hamon::forward<Args>(args)...);
	}

	template <typename... Args,
		typename = hamon::enable_if_t<
			hamon::is_constructible<value_type, Args...>::value>>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_hint(const_iterator position, Args&&... args)
	{
		return this->emplace_hint_impl(hamon::move(position), hamon::forward<Args>(args)...);
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

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void
	insert(InputIterator first, InputIterator last)
	{
		hamon::detail::reserve_append_size(this->c, first, last);
		this->append_sort_merge(hamon::move(first), hamon::move(last));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void
	insert(hamon::sorted_equivalent_t, InputIterator first, InputIterator last)
	{
		hamon::detail::reserve_append_size(this->c, first, last);
		this->append_merge(hamon::move(first), hamon::move(last));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, value_type, R)>
	HAMON_CXX14_CONSTEXPR void
	insert_range(R&& rg)
	{
		hamon::detail::reserve_append_size(this->c, rg);
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

	HAMON_CXX14_CONSTEXPR container_type
	extract() &&
	{
		auto gd = hamon::detail::make_scope_guard([&]() noexcept { clear(); });
		return hamon::move(c);
	}

	HAMON_CXX14_CONSTEXPR void
	replace(container_type&& cont)
	{
		HAMON_ASSERT(this->is_sorted(cont));

		auto gd = hamon::detail::make_exception_guard([&]() noexcept { clear(); });
		c = hamon::move(cont);
		gd.complete();
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(iterator position)
	{
		auto gd = hamon::detail::make_exception_guard([&]() noexcept { clear(); });
		auto key_iter = c.erase(position.base());
		gd.complete();
		return iterator(hamon::move(key_iter));
	}

	template <typename I = const_iterator,
		typename = hamon::enable_if_t<
			!hamon::same_as_t<I, iterator>::value>>
	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator position)
//		requires (!hamon::same_as<iterator, const_iterator>)
	{
		auto gd = hamon::detail::make_exception_guard([&]() noexcept { clear(); });
		auto key_iter = c.erase(position.base());
		gd.complete();
		return iterator(hamon::move(key_iter));
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
			hamon::negation<hamon::is_convertible<K&&, iterator>>,
			hamon::negation<hamon::is_convertible<K&&, const_iterator>>
		>::value>
	>
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
		auto key_iter = c.erase(first.base(), last.base());
		gd.complete();
		return iterator(hamon::move(key_iter));
	}

	HAMON_CXX14_CONSTEXPR void
	swap(flat_multiset& y) HAMON_NOEXCEPT
	{
		hamon::ranges::swap(compare, y.compare);
		hamon::ranges::swap(c, y.c);
	}

	HAMON_CXX14_CONSTEXPR void
	clear() HAMON_NOEXCEPT
	{
		c.clear();
	}

	// observers
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR key_compare
	key_comp() const
	{
		return compare;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR value_compare
	value_comp() const
	{
		return compare;
	}

	// set operations
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	find(key_type const& x)
	{
		return find_impl(*this, x);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
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
	HAMON_CXX11_CONSTEXPR const_iterator
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
		return iterator(hamon::ranges::lower_bound(c, x, compare));
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	lower_bound(key_type const& x) const
	{
		return const_iterator(hamon::ranges::lower_bound(c, x, compare));
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	lower_bound(K const& x)
	{
		return iterator(hamon::ranges::lower_bound(c, x, compare));
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	lower_bound(K const& x) const
	{
		return const_iterator(hamon::ranges::lower_bound(c, x, compare));
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	upper_bound(key_type const& x)
	{
		return iterator(hamon::ranges::upper_bound(c, x, compare));
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	upper_bound(key_type const& x) const
	{
		return const_iterator(hamon::ranges::upper_bound(c, x, compare));
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	upper_bound(K const& x)
	{
		return iterator(hamon::ranges::upper_bound(c, x, compare));
	}

	template <typename K,
		HAMON_CONSTRAINED_PARAM_D(hamon::detail::has_is_transparent, C, Compare)>
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	upper_bound(K const& x) const
	{
		return const_iterator(hamon::ranges::upper_bound(c, x, compare));
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
	operator==(flat_multiset const& x, flat_multiset const& y)
	{
		return hamon::ranges::equal(x, y);
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR friend auto
//	hamon::detail::synth_three_way_result<value_type>
	operator<=>(flat_multiset const& x, flat_multiset const& y)
	{
		return hamon::lexicographical_compare_three_way(
			x.begin(), x.end(),
			y.begin(), y.end(),
			hamon::detail::synth_three_way);
	}
#else
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR friend bool
	operator!=(flat_multiset const& x, flat_multiset const& y)
	{
		return !(x == y);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR friend bool
	operator<(flat_multiset const& x, flat_multiset const& y)
	{
		return hamon::ranges::lexicographical_compare(
			x.begin(), x.end(),
			y.begin(), y.end());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR friend bool
	operator>(flat_multiset const& x, flat_multiset const& y)
	{
		return y < x;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR friend bool
	operator<=(flat_multiset const& x, flat_multiset const& y)
	{
		return !(x > y);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR friend bool
	operator>=(flat_multiset const& x, flat_multiset const& y)
	{
		return !(x < y);
	}
#endif

	HAMON_CXX14_CONSTEXPR friend void
	swap(flat_multiset& x, flat_multiset& y) HAMON_NOEXCEPT
	{
		x.swap(y);
	}

private:
	template <typename Range>
	HAMON_CXX14_CONSTEXPR bool
	is_sorted(Range const& rg) const
	{
		return hamon::ranges::is_sorted(rg, this->compare);
	}

	HAMON_CXX14_CONSTEXPR void
	sort()
	{
		hamon::ranges::sort(c, this->compare);
	}

	template <typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void
	append(Iterator first, Sentinel last)
	{
		for (; first != last; ++first)
		{
			c.emplace(c.end(), hamon::move(*first));
		}
	}

	template <typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void
	append_merge(Iterator first, Sentinel last)
	{
		auto gd = hamon::detail::make_exception_guard([&]() noexcept { clear(); });
		using difference_t = hamon::ranges::range_difference_t<decltype(c)>;
		auto const m = static_cast<difference_t>(c.size());
		this->append(hamon::move(first), hamon::move(last));
		HAMON_ASSERT(this->is_sorted(c | hamon::views::drop(m)));
		hamon::ranges::inplace_merge(c, c.begin() + m, this->compare);
		gd.complete();
	}

	template <typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void
	append_sort_merge(Iterator first, Sentinel last)
	{
		auto gd = hamon::detail::make_exception_guard([&]() noexcept { clear(); });
		using difference_t = hamon::ranges::range_difference_t<decltype(c)>;
		auto const m = static_cast<difference_t>(c.size());
		this->append(hamon::move(first), hamon::move(last));
		hamon::ranges::sort(c | hamon::views::drop(m), this->compare);
		hamon::ranges::inplace_merge(c, c.begin() + m, this->compare);
		gd.complete();
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_impl(Args&&... args)
	{
		return this->emplace_impl2(hamon::detail::overload_priority<1>{}, hamon::forward<Args>(args)...);
	}

	template <typename Arg,
		typename = hamon::enable_if_t<
			hamon::is_same<hamon::remove_cvref_t<Arg>, Key>::value>>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_impl2(hamon::detail::overload_priority<1>, Arg&& arg)
	{
		return this->try_emplace_impl(hamon::forward<Arg>(arg));
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_impl2(hamon::detail::overload_priority<0>, Args&&... args)
	{
		return this->try_emplace_impl(Key(hamon::forward<Args>(args)...));
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_hint_impl(const_iterator position, Args&&... args)
	{
		return this->emplace_hint_impl2(hamon::detail::overload_priority<1>{}, hamon::move(position), hamon::forward<Args>(args)...);
	}

	template <typename Arg,
		typename = hamon::enable_if_t<
			hamon::is_same<hamon::remove_cvref_t<Arg>, Key>::value>>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_hint_impl2(hamon::detail::overload_priority<1>, const_iterator position, Arg&& arg)
	{
		return this->try_emplace_hint_impl(hamon::move(position), hamon::forward<Arg>(arg));
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_hint_impl2(hamon::detail::overload_priority<0>, const_iterator position, Args&&... args)
	{
		return this->try_emplace_hint_impl(hamon::move(position), Key(hamon::forward<Args>(args)...));
	}

	template <typename K>
	HAMON_CXX14_CONSTEXPR iterator
	try_emplace_impl(K&& k)
	{
		auto key_iter = this->upper_bound(k);
		return this->emplace_exact_pos(hamon::move(key_iter), hamon::forward<K>(k));
	}

	template <typename K, typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	try_emplace_hint_impl(const_iterator hint, K&& k)
	{
		auto prev_larger  = hint != cbegin() && this->compare(k, *hamon::ranges::prev(hint));
		auto next_smaller = hint != cend() && this->compare(*hint, k);

		if (HAMON_LIKELY(!prev_larger && !next_smaller))
		{
			// hint correct, just use exact hint iterators
		}
		else if (prev_larger && !next_smaller)
		{
			hint = hamon::ranges::upper_bound(this->begin(), hint, k, this->compare);
		}
		else
		{
			hint = hamon::ranges::lower_bound(hint, this->end(), k, this->compare);
		}

		return this->emplace_exact_pos(hamon::move(hint), hamon::forward<K>(k));
	}

	template <typename K>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_exact_pos(iterator key_iter, K&& k)
	{
		auto gd = hamon::detail::make_exception_guard([&]() noexcept { clear(); });
		key_iter = iterator{c.emplace(key_iter.base(), hamon::forward<K>(k))};
		gd.complete();

		return hamon::move(key_iter);
	}

	template <typename Self, typename K, typename It = hamon::ranges::iterator_t<Self>>
	HAMON_CXX14_CONSTEXPR static It
	find_impl(Self&& self, K const& k)
	{
		auto it = self.lower_bound(k);
		if (it == self.end() || self.compare(k, *it))
		{
			return self.end();
		}
		return it;
	}

	template <typename Self, typename K, typename It = hamon::ranges::iterator_t<Self>>
	static HAMON_CXX14_CONSTEXPR hamon::pair<It, It>
	equal_range_impl(Self&& self, K const& k)
	{
		auto ret = hamon::ranges::equal_range(self.c, k, self.compare);
		return hamon::pair<It, It>{ It(ret.begin()), It(ret.end()) };
	}

	template <typename Allocator>
	HAMON_CXX14_CONSTEXPR container_type
	extract_using_allocator(Allocator const& alloc) &&
	{
		auto gd = hamon::detail::make_scope_guard([&]() noexcept { clear(); });
		return hamon::make_obj_using_allocator<container_type>(alloc, hamon::move(c));
	}

private:
	container_type c;           // exposition only
	key_compare compare;        // exposition only
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <
	typename KeyContainer,
	typename Compare = hamon::less<typename KeyContainer::value_type>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<KeyContainer>>,
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>,
		hamon::is_invocable<Compare const&,
			typename KeyContainer::value_type const&,
			typename KeyContainer::value_type const&>
	>::value>
>
flat_multiset(KeyContainer, Compare = Compare())
->flat_multiset<
	typename KeyContainer::value_type,
	Compare,
	KeyContainer>;

template <
	typename KeyContainer,
	typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<KeyContainer>>,
		hamon::uses_allocator<KeyContainer, Allocator>
	>::value>
>
flat_multiset(KeyContainer, Allocator)
->flat_multiset<
	typename KeyContainer::value_type,
	hamon::less<typename KeyContainer::value_type>,
	KeyContainer>;

template <
	typename KeyContainer,
	typename Compare,
	typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<KeyContainer>>,
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>,
		hamon::uses_allocator<KeyContainer, Allocator>,
		hamon::is_invocable<Compare const&,
			typename KeyContainer::value_type const&,
			typename KeyContainer::value_type const&>
	>::value>
>
flat_multiset(KeyContainer, Compare, Allocator)
->flat_multiset<
	typename KeyContainer::value_type,
	Compare,
	KeyContainer>;

template <
	typename KeyContainer,
	typename Compare = hamon::less<typename KeyContainer::value_type>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<KeyContainer>>,
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>,
		hamon::is_invocable<Compare const&,
			typename KeyContainer::value_type const&,
			typename KeyContainer::value_type const&>
	>::value>
>
flat_multiset(hamon::sorted_equivalent_t, KeyContainer, Compare = Compare())
->flat_multiset<
	typename KeyContainer::value_type,
	Compare,
	KeyContainer>;

template <
	typename KeyContainer,
	typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<KeyContainer>>,
		hamon::uses_allocator<KeyContainer, Allocator>
	>::value>
>
flat_multiset(hamon::sorted_equivalent_t, KeyContainer, Allocator)
->flat_multiset<
	typename KeyContainer::value_type,
	hamon::less<typename KeyContainer::value_type>,
	KeyContainer>;

template <
	typename KeyContainer,
	typename Compare,
	typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<KeyContainer>>,
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>,
		hamon::uses_allocator<KeyContainer, Allocator>,
		hamon::is_invocable<Compare const&,
			typename KeyContainer::value_type const&,
			typename KeyContainer::value_type const&>
	>::value>
>
flat_multiset(hamon::sorted_equivalent_t, KeyContainer, Compare, Allocator)
->flat_multiset<
	typename KeyContainer::value_type,
	Compare,
	KeyContainer>;

template <
	typename InputIterator,
	typename Compare = hamon::less<hamon::detail::iter_value_type<InputIterator>>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::detail::cpp17_input_iterator_t<InputIterator>,
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>
	>::value>
>
flat_multiset(InputIterator, InputIterator, Compare = Compare())
->flat_multiset<hamon::detail::iter_value_type<InputIterator>, Compare>;

template <
	typename InputIterator,
	typename Compare = hamon::less<hamon::detail::iter_value_type<InputIterator>>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::detail::cpp17_input_iterator_t<InputIterator>,
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>
	>::value>
>
flat_multiset(hamon::sorted_equivalent_t, InputIterator, InputIterator, Compare = Compare())
->flat_multiset<hamon::detail::iter_value_type<InputIterator>, Compare>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Compare = hamon::less<ranges::range_value_t<R>>,
	typename Allocator = hamon::allocator<ranges::range_value_t<R>>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>,
		hamon::detail::simple_allocator_t<Allocator>
	>::value>
>
flat_multiset(hamon::from_range_t, R&&, Compare = Compare(), Allocator = Allocator())
->flat_multiset<
	ranges::range_value_t<R>,
	Compare,
	hamon::vector<ranges::range_value_t<R>, hamon::detail::alloc_rebind<Allocator, ranges::range_value_t<R>>>>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::detail::simple_allocator_t<Allocator>
	>::value>
>
flat_multiset(hamon::from_range_t, R&&, Allocator)
->flat_multiset<
	ranges::range_value_t<R>,
	hamon::less<ranges::range_value_t<R>>,
	hamon::vector<ranges::range_value_t<R>, hamon::detail::alloc_rebind<Allocator, ranges::range_value_t<R>>>>;

template <
	typename Key,
	typename Compare = hamon::less<Key>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>
	>::value>
>
flat_multiset(std::initializer_list<Key>, Compare = Compare())
->flat_multiset<Key, Compare>;

template <
	typename Key,
	typename Compare = hamon::less<Key>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>
	>::value>
>
flat_multiset(hamon::sorted_equivalent_t, std::initializer_list<Key>, Compare = Compare())
->flat_multiset<Key, Compare>;

#endif

// 23.6.12.6 Erasure[flat.multiset.erasure]

template <typename Key, typename Compare, typename KeyContainer, typename Predicate>
HAMON_CXX14_CONSTEXPR typename flat_multiset<Key, Compare, KeyContainer>::size_type
erase_if(flat_multiset<Key, Compare, KeyContainer>& c, Predicate pred)
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
		auto cont = hamon::move(c).extract();
		cont.erase(hamon::remove_if(cont.begin(), cont.end(),
			[&](Key const& e) { return static_cast<bool>(pred(e)); }), cont.end());
		c.replace(hamon::move(cont));
	}
	return original_size - c.size();
}

HAMON_WARNING_POP()

}	// namespace hamon

#include <memory>
#include <type_traits>

namespace std
{

template <typename Key, typename Compare, typename KeyContainer, typename Allocator>
struct uses_allocator<hamon::flat_multiset<Key, Compare, KeyContainer>, Allocator>
	: public std::integral_constant<bool,
		std::uses_allocator<KeyContainer, Allocator>::value>
{};

}	// namespace std

#endif

#endif // HAMON_FLAT_SET_FLAT_MULTISET_HPP
