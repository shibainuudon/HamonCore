/**
 *	@file	hive.hpp
 *
 *	@brief	hive の定義
 */

#ifndef HAMON_HIVE_HIVE_HPP
#define HAMON_HIVE_HIVE_HPP

#include <hamon/hive/hive_fwd.hpp>
#include <hamon/hive/hive_limits.hpp>
#include <hamon/hive/config.hpp>

#if !defined(HAMON_USE_STD_HIVE)

#include <hamon/hive/detail/hive_iterator.hpp>

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/container/detail/container_compatible_range.hpp>
#include <hamon/container/detail/iter_value_type.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>

#include <hamon/iterator.hpp>
#include <hamon/functional.hpp>
#include <hamon/memory.hpp>
#include <hamon/ranges.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

namespace hamon
{

// 23.3.8 Header <hive> synopsis[hive.syn]


template <typename T, typename Allocator>
void swap(hive<T, Allocator>& x, hive<T, Allocator>& y)
noexcept(noexcept(x.swap(y)));

template <typename T, typename Allocator, typename U = T>
typename hive<T, Allocator>::size_type
erase(hive<T, Allocator>& c, const U& value);

template <typename T, typename Allocator, typename Predicate>
typename hive<T, Allocator>::size_type
erase_if(hive<T, Allocator>& c, Predicate pred);

//namespace pmr {
//template <typename T>
//using hive = std::hive<T, polymorphic_allocator<T>>;
//}

// 23.3.9 Class template hive[hive]

template <typename T, typename Allocator/* = hamon::allocator<T>*/>
class hive
{
public:
	// types
	using value_type             = T;
	using allocator_type         = Allocator;
	using pointer                = typename allocator_traits<Allocator>::pointer;
	using const_pointer          = typename allocator_traits<Allocator>::const_pointer;
	using reference              = value_type&;
	using const_reference        = const value_type&;
	using size_type              = typename allocator_traits<Allocator>::size_type;			// implementation-defined;  // see [container.requirements]
	using difference_type        = typename allocator_traits<Allocator>::difference_type;	// implementation-defined;  // see [container.requirements]
	using iterator               = hamon::detail::hive_iterator<T, false>;					// implementation-defined;  // see [container.requirements]
	using const_iterator         = hamon::detail::hive_iterator<T, true>;					// implementation-defined;  // see [container.requirements]
	using reverse_iterator       = hamon::reverse_iterator<iterator>;													// see [container.requirements]
	using const_reverse_iterator = hamon::reverse_iterator<const_iterator>;												// see [container.requirements]

	// [hive.cons], construct/copy/destroy
	constexpr
	hive() noexcept(noexcept(Allocator()))
		: hive(Allocator()) {}

	constexpr explicit
	hive(Allocator const&) noexcept;

	constexpr explicit
	hive(hive_limits block_limits)
		: hive(block_limits, Allocator()) {}

	constexpr
	hive(hive_limits block_limits, Allocator const&);

	constexpr explicit
	hive(size_type n, Allocator const& = Allocator());

	constexpr
	hive(size_type n, hive_limits block_limits, Allocator const& = Allocator());

	constexpr
	hive(size_type n, T const& value, Allocator const& = Allocator());

	constexpr
	hive(size_type n, T const& value, hive_limits block_limits, Allocator const& = Allocator());

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	constexpr
	hive(InputIterator first, InputIterator last, Allocator const& = Allocator());

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	constexpr
	hive(InputIterator first, InputIterator last, hive_limits block_limits, Allocator const& = Allocator());

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	constexpr
	hive(hamon::from_range_t, R&& rg, Allocator const& = Allocator());

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	constexpr
	hive(hamon::from_range_t, R&& rg, hive_limits block_limits, Allocator const& = Allocator());

	constexpr
	hive(hive const& x);

	constexpr
	hive(hive&&) noexcept;

	constexpr
	hive(hive const& x, hamon::type_identity_t<Allocator> const& alloc);

	constexpr
	hive(hive&&, hamon::type_identity_t<Allocator> const& alloc);

	constexpr
	hive(std::initializer_list<T> il, Allocator const& = Allocator());

	constexpr
	hive(std::initializer_list<T> il, hive_limits block_limits, Allocator const& = Allocator());

	HAMON_CXX20_CONSTEXPR
	~hive();

	HAMON_CXX14_CONSTEXPR hive&
	operator=(hive const& x);

	HAMON_CXX14_CONSTEXPR hive&
	operator=(hive&& x) noexcept(
		hamon::allocator_traits<Allocator>::propagate_on_container_move_assignment::value ||
		hamon::allocator_traits<Allocator>::is_always_equal::value);

	HAMON_CXX14_CONSTEXPR hive&
	operator=(std::initializer_list<T>);

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void
	assign(InputIterator first, InputIterator last);

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR void
	assign_range(R&& rg);

	HAMON_CXX14_CONSTEXPR void
	assign(size_type n, T const& t);

	HAMON_CXX14_CONSTEXPR void
	assign(std::initializer_list<T>);

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

	HAMON_CXX14_CONSTEXPR reverse_iterator
	rbegin() noexcept;

	constexpr const_reverse_iterator
	rbegin() const noexcept;

	HAMON_CXX14_CONSTEXPR reverse_iterator
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

	// [hive.capacity], capacity
	constexpr bool
	empty() const noexcept;

	constexpr size_type
	size() const noexcept;

	constexpr size_type
	max_size() const noexcept;

	constexpr size_type
	capacity() const noexcept;

	HAMON_CXX14_CONSTEXPR void
	reserve(size_type n);

	HAMON_CXX14_CONSTEXPR void
	shrink_to_fit();

	HAMON_CXX14_CONSTEXPR void
	trim_capacity() noexcept;

	HAMON_CXX14_CONSTEXPR void
	trim_capacity(size_type n) noexcept;

	constexpr hive_limits
	block_capacity_limits() const noexcept;

	static constexpr hive_limits
	block_capacity_default_limits() noexcept;

	static constexpr hive_limits
	block_capacity_hard_limits() noexcept;

	HAMON_CXX14_CONSTEXPR void
	reshape(hive_limits block_limits);

	// [hive.modifiers], modifiers
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace(Args&&... args);

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_hint(const_iterator hint, Args&&... args);

	HAMON_CXX14_CONSTEXPR iterator
	insert(T const& x)
	{
		// [hive.modifiers]/6
		return this->emplace(x);
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(T&& x)
	{
		// [hive.modifiers]/6
		return this->emplace(hamon::move(x));
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator hint, T const& x)
	{
		// [hive.modifiers]/6
		(void)hint;
		return this->emplace(x);
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator hint, T&& x)
	{
		// [hive.modifiers]/6
		(void)hint;
		return this->emplace(hamon::move(x));
	}

	HAMON_CXX14_CONSTEXPR void
	insert(std::initializer_list<T> il);

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR void
	insert_range(R&& rg);

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void
	insert(InputIterator first, InputIterator last);

	HAMON_CXX14_CONSTEXPR void
	insert(size_type n, T const& x);

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator position);

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator first, const_iterator last);

	HAMON_CXX14_CONSTEXPR void
	swap(hive&) noexcept(
		hamon::allocator_traits<Allocator>::propagate_on_container_swap::value ||
		hamon::allocator_traits<Allocator>::is_always_equal::value);

	HAMON_CXX14_CONSTEXPR void
	clear() noexcept;

	// [hive.operations], hive operations
	HAMON_CXX14_CONSTEXPR void
	splice(hive& x);

	HAMON_CXX14_CONSTEXPR void
	splice(hive&& x);

	template <typename BinaryPredicate = hamon::equal_to<T>>
	HAMON_CXX14_CONSTEXPR size_type
	unique(BinaryPredicate binary_pred = BinaryPredicate());

	template <typename Compare = hamon::less<T>>
	HAMON_CXX14_CONSTEXPR void
	sort(Compare comp = Compare());

	HAMON_CXX14_CONSTEXPR iterator
	get_iterator(const_pointer p) noexcept;

	constexpr const_iterator
	get_iterator(const_pointer p) const noexcept;

private:
//	hive_limits current-limits = implementation-defined;     // exposition only
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	typename Allocator = hamon::allocator<hamon::detail::iter_value_type<InputIterator>>>
hive(InputIterator, InputIterator, Allocator = Allocator())
->hive<hamon::detail::iter_value_type<InputIterator>, Allocator>;

template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	typename Allocator = hamon::allocator<hamon::detail::iter_value_type<InputIterator>>>
hive(InputIterator, InputIterator, hive_limits, Allocator = Allocator())
->hive<hamon::detail::iter_value_type<InputIterator>, Allocator>;

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Allocator = hamon::allocator<hamon::ranges::range_value_t<R>>>
hive(hamon::from_range_t, R&&, Allocator = Allocator())
->hive<hamon::ranges::range_value_t<R>, Allocator>;

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Allocator = hamon::allocator<hamon::ranges::range_value_t<R>>>
hive(hamon::from_range_t, R&&, hive_limits, Allocator = Allocator())
->hive<hamon::ranges::range_value_t<R>, Allocator>;

#endif

}	// namespace hamon

#endif

#endif // HAMON_HIVE_HIVE_HPP
